const readline = require('readline');
const { execSync } = require('child_process');
const path = require('path');

Identify = function() {

      // Shape identification.

      // Search handler.

      const rl = readline.createInterface({
          input: process.stdin,
          output: process.stdout
      });

      rl.question('Shape to define: ', (shape) => {

          // Mock AI response for shape definition
          const text = `A ${shape} is a three-dimensional geometric shape with specific properties.`;

          const shape_data = text.split(' ');

          const definition = shape_data.filter(word => word.includes('shape') || word.includes('dimensional'));

          const obj = definition.join(' ');

          console.log('Shape definition:', obj);

          // Obj vertices algorithm identification to apply to /.src/main.c.

          // Run main.c

          try {
              execSync('./main "' + obj.replace(/"/g, '\\"') + '" "' + shape.replace(/"/g, '\\"') + '"', { cwd: path.join(__dirname, '..') });
              console.log('OBJ generated successfully.');
          } catch (error) {
              console.error('Error running main.c:', error.message);
          }

          rl.close();
      });

};




UI = function () {

      // Fetch and store variables from utility and obj file that is in /.bin

      // Display graph UI, data and nodes with /qubitry/graph.html with variables.

      const fs = require('fs');

      const path = require('path');

      try {

          const utilityPath = path.join(__dirname, '..', '.bin', 'utility.txt');

          const objPath = path.join(__dirname, '..', '.src', 'example.obj'); // or the latest

          if (fs.existsSync(utilityPath)) {

              const utilityData = fs.readFileSync(utilityPath, 'utf8');

              console.log('Utility points:', utilityData);

          }

          // Find the latest obj file

          const srcDir = path.join(__dirname, '..', '.src');

          const files = fs.readdirSync(srcDir).filter(f => f.startsWith('example_') && f.endsWith('.obj'));

          if (files.length > 0) {

              const latestObj = files.sort().pop();

              const objData = fs.readFileSync(path.join(srcDir, latestObj), 'utf8');

              console.log('OBJ data:', objData);

              // Parse OBJ to extract vertices

              const lines = objData.split('\n');

              const vertices = [];

              lines.forEach(line => {

                  if (line.startsWith('v ')) {

                      const parts = line.trim().split(/\s+/);

                      if (parts.length >= 4) {

                          vertices.push({

                              x: parseFloat(parts[1]),

                              y: parseFloat(parts[2]),

                              z: parseFloat(parts[3])

                          });

                      }

                  }

              });

              console.log('Parsed vertices:', vertices);

              // Update graph.html with vertices

              const graphHtmlPath = path.join(__dirname, 'graph.html');

              let graphHtml = fs.readFileSync(graphHtmlPath, 'utf8');

              // Extract x, y, z arrays

              const x = vertices.map(v => v.x);

              const y = vertices.map(v => v.y);

              const z = vertices.map(v => v.z);

              // Replace the trace in script

              const newTrace = `const trace = {

    x: [${x.join(', ')}],

    y: [${y.join(', ')}],

    z: [${z.join(', ')}],

    mode: 'markers',

    type: 'scatter3d',

    marker: { size: 4 }

};`;

              // Find the old trace and replace

              const traceRegex = /const trace = \{[\s\S]*?\};/;

              graphHtml = graphHtml.replace(traceRegex, newTrace);

              fs.writeFileSync(graphHtmlPath, graphHtml);

              console.log('Graph HTML updated with OBJ data.');

              // Open the graph in browser

              const { exec } = require('child_process');

              exec('xdg-open ' + graphHtmlPath, (err) => {

                  if (err) {

                      console.log('Could not open browser, graph updated at:', graphHtmlPath);

                  }

              });

          } else {

              console.log('No OBJ files found.');

          }

          console.log('Graph UI displayed with data and nodes.');

      } catch (err) {

          console.error('Error displaying UI:', err);

      }

};

module.exports = {
   UI,
   Identify
};
