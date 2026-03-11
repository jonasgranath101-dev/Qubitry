#!/bin/bash

# Setup quick shortcuts for the project
# Source this file in your .bashrc or .zshrc

export SHAPER_DIR="/workspaces/Qubitry/OneCoreAI/shaper"

# Main launcher
alias shaper="cd $SHAPER_DIR && ./run.sh"

# Quick shape generators
alias sphere="cd $SHAPER_DIR && ./shape_gen 'a smooth sphere' sphere"
alias cube="cd $SHAPER_DIR && ./shape_gen 'a cube' cube"
alias torus="cd $SHAPER_DIR && ./shape_gen 'a torus' torus"
alias cylinder="cd $SHAPER_DIR && ./shape_gen 'a cylinder' cylinder"
alias cone="cd $SHAPER_DIR && ./shape_gen 'a cone' cone"
alias octahedron="cd $SHAPER_DIR && ./shape_gen 'an octahedron' octahedron"

# Demo
alias demo="cd $SHAPER_DIR && ./demo.sh"

# View output
alias view-shapes="ls -lh $SHAPER_DIR/output/"

# View docs
alias docs-readme="less $SHAPER_DIR/README.md"
alias docs-test="less $SHAPER_DIR/TEST_REPORT.md"
alias docs-quick="less $SHAPER_DIR/QUICK_REFERENCE.md"

# Generate custom shape (example usage: gen-shape "a smooth large sphere" sphere)
gen-shape() {
    if [ $# -eq 2 ]; then
        cd "$SHAPER_DIR" && ./shape_gen "$1" "$2"
    else
        echo "Usage: gen-shape \"description\" shape_type"
        echo "Example: gen-shape \"a smooth large sphere\" sphere"
    fi
}

echo "✓ Shaper shortcuts loaded!"
echo ""
echo "Quick commands available:"
echo "  shaper              - Interactive launcher"
echo "  demo                - Run demo (5 shapes)"
echo "  sphere/cube/torus/cylinder/cone/octahedron - Quick generators"
echo "  gen-shape \"desc\" shape - Custom shape generation"
echo "  view-shapes         - List generated shapes"
echo "  docs-readme/test/quick - View documentation"
