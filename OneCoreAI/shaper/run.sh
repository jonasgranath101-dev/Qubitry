#!/bin/bash

# AI 3D Shape Generator - Interactive Launcher
# Easy terminal interface for shape generation

show_menu() {
    clear
    echo "╔════════════════════════════════════════════════════════════════╗"
    echo "║        AI 3D Shape Generator - Interactive Interface           ║"
    echo "╚════════════════════════════════════════════════════════════════╝"
    echo ""
    echo "Choose an option:"
    echo ""
    echo "  1) Generate a custom shape (interactive)"
    echo "  2) Run demo (generate 5 example shapes)"
    echo "  3) Quick generate sphere"
    echo "  4) Quick generate cube"
    echo "  5) Quick generate torus"
    echo "  6) Quick generate cylinder"
    echo "  7) Quick generate cone"
    echo "  8) View generated shapes (list output/)"
    echo "  9) View documentation"
    echo ""
    echo "  0) Exit"
    echo ""
    read -p "Enter choice [0-9]: " choice
    echo ""
}

generate_custom() {
    echo "╔════════════════════════════════════════════════════════════════╗"
    echo "║                  Custom Shape Generation                       ║"
    echo "╚════════════════════════════════════════════════════════════════╝"
    echo ""
    echo "Available shapes: cube, sphere, cylinder, cone, torus, octahedron"
    echo ""
    read -p "Enter shape type: " shape_type
    read -p "Enter description (e.g., 'a smooth large sphere'): " description
    echo ""
    echo "Generating ${shape_type}..."
    ./shape_gen "$description" "$shape_type"
    echo ""
    echo "✓ Shape generated successfully!"
    read -p "Press Enter to continue..."
}

run_demo() {
    echo "╔════════════════════════════════════════════════════════════════╗"
    echo "║                      Running Demo Mode                         ║"
    echo "╚════════════════════════════════════════════════════════════════╝"
    echo ""
    ./demo.sh
    read -p "Press Enter to continue..."
}

quick_generate() {
    local description=$1
    local shape=$2
    echo "Generating ${shape}..."
    ./shape_gen "$description" "$shape"
    echo "✓ Generated: $shape"
    sleep 1
}

view_shapes() {
    clear
    echo "╔════════════════════════════════════════════════════════════════╗"
    echo "║                    Generated Shapes (output/)                  ║"
    echo "╚════════════════════════════════════════════════════════════════╝"
    echo ""
    if [ -d "output" ] && [ "$(ls -A output/ 2>/dev/null)" ]; then
        ls -lh output/
        echo ""
        read -p "Enter OBJ filename to view (or press Enter to skip): " filename
        if [ -n "$filename" ] && [ -f "output/$filename" ]; then
            echo ""
            echo "╔════════════════════════════════════════════════════════════════╗"
            echo "║  $(basename "output/$filename")"
            echo "╚════════════════════════════════════════════════════════════════╝"
            head -50 "output/$filename"
            echo ""
            echo "... ($(wc -l < "output/$filename") total lines)"
        fi
    else
        echo "No shapes generated yet. Generate some shapes first!"
    fi
    echo ""
    read -p "Press Enter to continue..."
}

view_docs() {
    clear
    echo "╔════════════════════════════════════════════════════════════════╗"
    echo "║                       Documentation                           ║"
    echo "╚════════════════════════════════════════════════════════════════╝"
    echo ""
    echo "Available documentation files:"
    echo ""
    echo "  1) README.md - Quick start guide"
    echo "  2) TEST_REPORT.md - Comprehensive technical analysis"
    echo "  3) QUICK_REFERENCE.md - Test results summary"
    echo "  4) SAMPLE_OUTPUTS.md - Generated coordinate examples"
    echo "  5) INDEX.md - Documentation index"
    echo ""
    read -p "Enter choice [1-5] or 0 to go back: " doc_choice
    
    case $doc_choice in
        1) less README.md ;;
        2) less TEST_REPORT.md ;;
        3) less QUICK_REFERENCE.md ;;
        4) less SAMPLE_OUTPUTS.md ;;
        5) less INDEX.md ;;
        0) return ;;
        *) echo "Invalid choice" ;;
    esac
}

# Main loop
while true; do
    show_menu
    
    case $choice in
        1)
            generate_custom
            ;;
        2)
            run_demo
            ;;
        3)
            quick_generate "a smooth large sphere" "sphere"
            sleep 2
            ;;
        4)
            quick_generate "a compact small cube" "cube"
            sleep 2
            ;;
        5)
            quick_generate "a large thick torus" "torus"
            sleep 2
            ;;
        6)
            quick_generate "a tall thin cylinder" "cylinder"
            sleep 2
            ;;
        7)
            quick_generate "a sharp pointed cone" "cone"
            sleep 2
            ;;
        8)
            view_shapes
            ;;
        9)
            view_docs
            ;;
        0)
            echo "Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            sleep 1
            ;;
    esac
done
