![alt text](.src/img.gif)

# Qubitry
3D open-source, algorithm grapher. Objective imaging.

Qubitry is an AI-powered 3D shape generation system that creates geometric objects using machine learning algorithms. The system trains AI cores to generate OBJ files for various 3D shapes like cubes and spheres, with an interactive Node.js-based UI for visualization.

## Core Fundamentals

• Geometrical AI solving write, as .obj file data.

• Graphing output.

• AI shape recognition.

• Logical interference.

## Screenshots

![alt text](.bin/Screenshot 2025-12-31 3.39.28 AM.png)

## Prerequisites

- GCC compiler
- Node.js (for UI components)
- Linux/macOS environment

## Build Instructions

1. Compile the C core:
```bash
gcc -o main .src/main.c AI/.core/init.c -lm
```

## Usage

### Generate 3D Shapes

Run the compiled program with shape parameters:
```bash
./main "shape description" "shape_type"
```

Examples:
```bash
# Generate a cube
./main "geometric cube" "cube"

# Generate a sphere
./main "perfect sphere" "sphere"
```

The program will:
1. Train an AI core with visualization
2. Generate an OBJ file in the `.src/` directory
3. Create utility points file in `.bin/utility.txt`

### Interactive UI

Launch the Node.js interface for shape identification and visualization:
```bash
node qubitry/node.js
```

The UI will:
- Prompt for shape identification
- Generate OBJ files based on input
- Update the 3D graph visualization
- Open the graph in your default browser

## Project Structure

- `.src/main.c` - Main C program for shape generation
- `AI/.core/` - AI core implementation and training logic
- `qubitry/node.js` - Node.js UI for shape identification and graphing
- `qubitry/graph.html` - 3D visualization interface
- `.bin/` - Generated utility files
- `.src/` - Generated OBJ files

## Output

Generated OBJ files contain:
- Vertex coordinates (v lines)
- Face definitions (f lines)
- Compatible with standard 3D modeling software

The system uses AI training to determine optimal scaling and positioning for generated shapes.
