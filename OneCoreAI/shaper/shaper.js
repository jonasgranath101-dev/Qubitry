const readline = require('readline');
const { execSync, exec } = require('child_process');
const fs = require('fs');
const path = require('path');

function runShaper(shapeDescription, shapeType) {
    try {
        execSync(
            `cd ${path.join(__dirname)} && ./shape_gen "${shapeDescription.replace(/"/g, '\\"')}" "${shapeType.replace(/"/g, '\\"')}"`,
            { stdio: 'inherit' }
        );
        console.log('AI-powered 3D shape generated successfully.');
    } catch (error) {
        console.error('Error running shape generator:', error.message);
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
    const outputDir = path.join(__dirname, 'output');
    if (!fs.existsSync(outputDir)) {
        return null;
    }
    const files = fs
        .readdirSync(outputDir)
        .filter(f => f.startsWith('shape_') && f.endsWith('.obj'))
        .sort();

    if (!files.length) return null;
    return path.join(outputDir, files[files.length - 1]);
}

function updateGraphHtml(vertices) {
    const graphHtmlPath = path.join(__dirname, 'graph.html');
    let graphHtml = fs.readFileSync(graphHtmlPath, 'utf8');

    const geometryJson = JSON.stringify(vertices);
    const placeholder = '// __GEOMETRY_DATA_PLACEHOLDER__';
    const injected = `const GEOMETRY_POINTS = ${geometryJson};`;

    if (!graphHtml.includes(placeholder)) {
        console.warn('Geometry placeholder not found in graph.html, skipping update.');
        return;
    }

    graphHtml = graphHtml.replace(placeholder, `${placeholder}\n${injected}`);
    fs.writeFileSync(graphHtmlPath, graphHtml);

    exec(`xdg-open "${graphHtmlPath}"`, err => {
        if (err) {
            console.log('3D Shape displayed at:', graphHtmlPath);
        }
    });
}

function startShaping() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.question('Enter shape type (cube, sphere, cylinder, cone, torus, octahedron): ', shapeType => {
        rl.question('Describe the shape characteristics: ', description => {
            console.log(`Generating AI-powered ${shapeType} with description: "${description}"`);
            runShaper(description, shapeType.toLowerCase());
            rl.close();

            // Wait a bit for file generation, then display
            setTimeout(() => {
                const latestObjPath = getLatestObjPath();
                if (!latestObjPath) {
                    console.log('No shape files found.');
                    return;
                }

                const objData = fs.readFileSync(latestObjPath, 'utf8');
                const vertices = parseObjVertices(objData);
                console.log(`Parsed ${vertices.length} vertices from generated shape.`);

                updateGraphHtml(vertices);
            }, 2000);
        });
    });
}

// Export functions
module.exports = {
    startShaping
};

// Run if called directly
if (require.main === module) {
    startShaping();
}