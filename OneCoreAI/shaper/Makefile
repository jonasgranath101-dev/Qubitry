.PHONY: help run demo clean build compile shapes view docs

# AI 3D Shape Generator - Makefile

help:
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║    AI 3D Shape Generator - Available Commands              ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Setup:"
	@echo "  make build              - Compile the C program"
	@echo "  make setup              - Get started (one-time setup)"
	@echo ""
	@echo "Run:"
	@echo "  make run                - Launch interactive interface"
	@echo "  make demo               - Run 5-shape demo"
	@echo "  make clean              - Remove generated shapes"
	@echo ""
	@echo "Quick Generators:"
	@echo "  make sphere             - Generate a sphere"
	@echo "  make cube               - Generate a cube"
	@echo "  make torus              - Generate a torus (donut)"
	@echo "  make cylinder           - Generate a cylinder"
	@echo "  make cone               - Generate a cone"
	@echo "  make octahedron         - Generate an octahedron"
	@echo ""
	@echo "View:"
	@echo "  make view               - List all generated shapes"
	@echo "  make docs               - View documentation"
	@echo ""
	@echo "Example usage:"
	@echo "  make run                - Start interactive launcher"
	@echo "  make demo               - See example outputs"
	@echo ""

build: shape_generator.c
	@echo "Compiling shape_generator.c..."
	@gcc -o shape_gen shape_generator.c -lm
	@echo "✓ Build complete! Run 'make run' to start."

run: shape_gen
	@./run.sh

demo: shape_gen
	@./demo.sh

sphere: shape_gen
	@./shape_gen "a smooth large sphere" sphere

cube: shape_gen
	@./shape_gen "a compact cube" cube

torus: shape_gen
	@./shape_gen "a thick torus" torus

cylinder: shape_gen
	@./shape_gen "a tall cylinder" cylinder

cone: shape_gen
	@./shape_gen "a sharp cone" cone

octahedron: shape_gen
	@./shape_gen "an octahedron" octahedron

view:
	@echo "Generated shapes in output/:"
	@ls -lh output/ 2>/dev/null || echo "  (No shapes generated yet)"

docs:
	@echo "Available documentation:"
	@ls -lh *.md | awk '{print "  " $$NF " (" $$5 ")"}'

clean:
	@rm -rf output/*
	@echo "✓ Cleaned output directory"

setup: build
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║           Setup Complete! You're ready to go.              ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Next steps:"
	@echo "  1. Run interactive launcher:"
	@echo "     make run"
	@echo ""
	@echo "  2. Try a quick demo:"
	@echo "     make demo"
	@echo ""
	@echo "  3. Generate specific shapes:"
	@echo "     make sphere"
	@echo "     make cube"
	@echo "     make torus"
	@echo ""
	@echo "  4. View generated shapes:"
	@echo "     make view"
	@echo ""
	@echo "  5. Read documentation:"
	@echo "     make docs"
	@echo ""
