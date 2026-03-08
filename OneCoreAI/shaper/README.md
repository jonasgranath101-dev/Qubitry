# AI 3D Shape Generator

A simple 3D shaping program that uses artificial intelligence to generate advanced geometric shapes from natural language descriptions.

## Features

- **AI-Powered Generation**: Analyzes text descriptions to determine optimal shape parameters
- **Advanced Shapes**: Supports cube, sphere, cylinder, cone, torus, and octahedron
- **3D Visualization**: Interactive Plotly.js visualization of generated shapes
- **OBJ Export**: Generates standard OBJ files for use in other 3D applications
- **Batch Processing**: Demo script shows multiple shape generation

## Quick Start

### Interactive Mode
```bash
cd OneCoreAI/shaper
node shaper.js
```
Then follow the prompts to specify shape type and description.

### Demo Mode
```bash
cd OneCoreAI/shaper
./demo.sh
```
Generates 5 different shapes with AI analysis.

### Direct Generation
```bash
cd OneCoreAI/shaper
./shape_gen "a smooth round sphere" sphere
```

## AI Characteristics Analysis

The AI system analyzes your description for these characteristics:

### Size Modifiers
- **"small" or "tiny"** → Reduces scale by 50%
- **"large" or "big"** → Doubles the scale

### Shape-Specific Characteristics

#### Spheres
- **"smooth"** → Increases mesh density for smoother appearance

#### Cylinders
- **"tall"** → Doubles the height

#### Cones
- **"sharp" or "pointed"** → Increases height by 50%

#### Tori
- **"thick"** → Increases minor radius by 50%

## How It Works

1. **Input Analysis**: AI scans description for keywords and patterns
2. **Parameter Generation**: Determines scale, shape-specific parameters, and mesh density
3. **Geometry Creation**: Generates 3D vertices and faces using mathematical formulas
4. **OBJ Export**: Saves geometry in standard OBJ format
5. **Visualization**: Node.js parses OBJ and displays in interactive 3D plot

## Example Outputs

```
Demo 1: 'a very smooth round ball'
→ Sphere: scale=2.72, stacks=15, slices=19

Demo 2: 'a tall thin column'
→ Cylinder: scale=2.72, height=14.14, slices=15

Demo 3: 'a large thick donut'
→ Torus: scale=5.44, minor_radius=2.04, segments=19

Demo 4: 'a sharp pointed mountain'
→ Cone: scale=2.72, height=10.61, slices=15

Demo 5: 'a small compact box'
→ Cube: scale=1.36
```

## Files

- `shape_generator.c` - C program with AI parameter generation
- `shaper.js` - Node.js interface and visualization
- `graph.html` - 3D visualization template
- `demo.sh` - Batch demonstration script
- `output/` - Generated OBJ files and point data

## Dependencies

- GCC compiler
- Node.js
- Plotly.js (loaded from CDN)

## Architecture

This implementation demonstrates a simplified AI approach that could be extended with:
- Machine learning models for better parameter prediction
- More sophisticated NLP for description analysis
- Integration with full OneCoreAI framework for advanced training
- Additional shape types and modifiers

The system shows how AI can bridge natural language descriptions with precise 3D geometry generation.