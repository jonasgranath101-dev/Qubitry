const readline = require('readline');
const { execSync, exec } = require('child_process');
const fs = require('fs');
const path = require('path');

function runCore(shapeDescription, shapeType) {
    try {
        execSync(
            `./main "${shapeDescription.replace(/"/g, '\\"')}" "${shapeType.replace(/"/g, '\\"')}"`,
            { cwd: path.join(__dirname, '..'), stdio: 'inherit' }
        );
        console.log('OBJ generated successfully.');
    } catch (error) {
        console.error('Error running main.c:', error.message);
    }
}

function parseObjVertices(objData) {
    const vertices = [];
    const lines = objData.split('\n');

    for (const line of lines) {
        if (!line.startsWith('v ')) continue;
        const parts = line.trim().split(/\s+/);
        if (parts.length < 4) continue;

        const x = parseFloat(parts[1]);
        const y = parseFloat(parts[2]);
        const z = parseFloat(parts[3]);

        if (Number.isFinite(x) && Number.isFinite(y) && Number.isFinite(z)) {
            vertices.push({ x, y, z });
        }
    }
    return vertices;
}

function getLatestObjPath() {
    const srcDir = path.join(__dirname, '..', '.src');
    if (!fs.existsSync(srcDir)) {
        return null;
    }
    const files = fs
        .readdirSync(srcDir)
        .filter(f => f.startsWith('example_') && f.endsWith('.obj'))
        .sort();

    if (!files.length) return null;
    return path.join(srcDir, files[files.length - 1]);
}

function updateGraphHtml(vertices) {
    const graphHtmlPath = path.join(__dirname, 'graph.html');
    let graphHtml = fs.readFileSync(graphHtmlPath, 'utf8');

    const geometryJson = JSON.stringify(vertices);
    const placeholder = '// __GEOMETRY_DATA_PLACEHOLDER__';
    const injected = `const GEOMETRY_POINTS = ${geometryJson};`;

    const placeholderIndex = graphHtml.indexOf(placeholder);
    if (placeholderIndex === -1) {
        console.warn('Geometry placeholder not found in graph.html, skipping update.');
        return;
    }

    // Replace any previous injected geometry block, keeping file structure stable.
    const afterPlaceholder = graphHtml.slice(placeholderIndex + placeholder.length);
    const traceIndex = afterPlaceholder.indexOf('const trace');
    if (traceIndex === -1) {
        console.warn('Could not find trace definition in graph.html.');
        return;
    }

    const before = graphHtml.slice(0, placeholderIndex + placeholder.length);
    const after = afterPlaceholder.slice(traceIndex);

    graphHtml = `${before}\n${injected}\n\n${after}`;
    fs.writeFileSync(graphHtmlPath, graphHtml);

    exec(`xdg-open "${graphHtmlPath}"`, err => {
        if (err) {
            console.log('Graph updated at:', graphHtmlPath);
        }
    });
}

Identify = function () {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.question(
        'Enter shape name OR a list of coordinates (e.g. "cube" OR "0,0,0;1,0,0;1,1,0"): ',
        input => {
            const trimmed = input.trim();
            if (!trimmed) {
                console.log('No input provided. Exiting.');
                rl.close();
                return;
            }

            const isCoords = trimmed.includes(',') || trimmed.includes(';');
            const shapeType = isCoords ? 'custom' : trimmed;
            const objDescription = isCoords ? trimmed : `A ${trimmed} is a three-dimensional geometric shape.`;

            console.log('Running with:', isCoords ? 'coordinates' : 'shape', shapeType);
            runCore(objDescription, shapeType);
            rl.close();
        }
    );
};

UI = function () {
    try {
        const utilityPath = path.join(__dirname, '..', '.bin', 'utility.txt');
        if (fs.existsSync(utilityPath)) {
            const utilityData = fs.readFileSync(utilityPath, 'utf8');
            console.log('Utility points:', utilityData);
        }

        const latestObjPath = getLatestObjPath();
        if (!latestObjPath) {
            console.log('No OBJ files found.');
            return;
        }

        const objData = fs.readFileSync(latestObjPath, 'utf8');
        const vertices = parseObjVertices(objData);
        console.log('Parsed vertices:', vertices.length);

        updateGraphHtml(vertices);
    } catch (err) {
        console.error('Error displaying UI:', err);
    }
};

module.exports = {
    UI,
    Identify
};

// Run the interactive UI when the script is invoked directly.
if (require.main === module) {
    UI();
}
