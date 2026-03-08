#!/bin/bash

# AI 3D Shape Generator Demo
# Demonstrates the AI-powered shape generation capabilities

echo "=== AI 3D Shape Generator Demo ==="
echo "This demo shows how the AI analyzes descriptions to generate advanced 3D shapes."
echo ""

cd /workspaces/Qubitry/OneCoreAI/shaper

# Demo 1: Sphere
echo "Demo 1: Generating a smooth sphere"
echo "Description: 'a very smooth round ball'"
./shape_gen "a very smooth round ball" sphere
echo ""

# Demo 2: Cylinder
echo "Demo 2: Generating a tall cylinder"
echo "Description: 'a tall thin column'"
./shape_gen "a tall thin column" cylinder
echo ""

# Demo 3: Torus
echo "Demo 3: Generating a thick torus"
echo "Description: 'a large thick donut'"
./shape_gen "a large thick donut" torus
echo ""

# Demo 4: Cone
echo "Demo 4: Generating a sharp cone"
echo "Description: 'a sharp pointed mountain'"
./shape_gen "a sharp pointed mountain" cone
echo ""

# Demo 5: Cube
echo "Demo 5: Generating a small cube"
echo "Description: 'a small compact box'"
./shape_gen "a small compact box" cube
echo ""

echo "=== Demo Complete ==="
echo "Generated shapes are saved in the 'output/' directory."
echo "Use 'node shaper.js' for interactive shape generation with 3D visualization."
echo ""
echo "Supported shapes: cube, sphere, cylinder, cone, torus, octahedron"
echo "AI analyzes: size (small/large), shape characteristics (smooth, tall, sharp, thick)"