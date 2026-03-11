#!/bin/bash

# Quick setup script - run this once to set everything up

echo "╔════════════════════════════════════════════════════════════╗"
echo "║           AI 3D Shape Generator - Terminal Setup           ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

# Make scripts executable
echo "1/3: Making scripts executable..."
chmod +x run.sh demo.sh aliases.sh
echo "    ✓ Scripts ready to run"
echo ""

# Compile if needed
if [ ! -f "shape_gen" ]; then
    echo "2/3: Compiling shape_generator.c..."
    gcc -o shape_gen shape_generator.c -lm
    echo "    ✓ Compiled successfully"
else
    echo "2/3: shape_gen already compiled"
fi
echo ""

echo "3/3: Setup complete!"
echo ""
echo "╔════════════════════════════════════════════════════════════╗"
echo "║                   You're ready to go!                      ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""
echo "Quick start options:"
echo ""
echo "  Option A - Interactive menu (recommended):"
echo "    $ make run"
echo ""
echo "  Option B - Run examples:"
echo "    $ make demo"
echo ""
echo "  Option C - Generate specific shape:"
echo "    $ make sphere"
echo "    $ make cube"
echo "    $ make torus"
echo ""
echo "  Option D - Setup bash aliases (optional):"
echo "    $ source aliases.sh"
echo ""
echo "  Option E - View help:"
echo "    $ make help"
echo ""
echo "Documentation available:"
echo "  • TERMINAL_GUIDE.md - Quick reference for terminal"
echo "  • GETTING_STARTED.md - Step-by-step guide"
echo "  • README.md - Project overview"
echo "  • TEST_REPORT.md - Technical details"
echo ""
