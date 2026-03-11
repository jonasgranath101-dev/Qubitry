# Getting Started - AI 3D Shape Generator

Quick reference for running the project in the terminal.

##  Fastest Way to Start

### Option 1: Interactive Launcher (Recommended)
```bash
cd OneCoreAI/shaper
make run
```
This launches an interactive menu with all options.

---

## 📋 Quick Commands

### One-Time Setup
```bash
make setup  # Compiles the program and shows you what's next
```

### Generate Shapes
```bash
make sphere     # Quick sphere
make cube       # Quick cube
make torus      # Quick torus (donut)
make cylinder   # Quick cylinder
make cone       # Quick cone
make octahedron # Quick octahedron
```

### See Results
```bash
make view   # List all generated shapes
```

### Run Examples
```bash
make demo   # Generate 5 example shapes
```

---

##  Usage Examples

### Example 1: Generate a Smooth Sphere
```bash
cd OneCoreAI/shaper
./shape_gen "a very smooth large sphere" sphere
```

### Example 2: Generate Multiple Shapes
```bash
make sphere    # Sphere
make cube      # Cube
make torus     # Torus
make view      # See all 3 in output/
```

### Example 3: Custom Description
```bash
./shape_gen "a small tiny compact box" cube
```

### Example 4: View a Generated Shape
```bash
cat output/shape_*.obj | head -50
```

---

##  Output Files

All generated shapes are saved in `output/`:
- **shape_[timestamp].obj** - The 3D model (Wavefront format)
- **points.txt** - Coordinate data

View file sizes:
```bash
ls -lh output/
```

---

## 🔧 Troubleshooting

### "shape_gen: command not found"
→ Run `make build` first to compile

### "demo.sh: Permission denied"
→ Run `chmod +x *.sh` to make scripts executable

### Need help?
```bash
make help      # Show all commands
make docs      # View documentation
```

---

## 📚 Full Command Reference

| Command | What It Does |
|---------|------------|
| `make help` | Show all available commands |
| `make build` | Compile the C program |
| `make run` | Launch interactive interface |
| `make demo` | Run 5-shape demo |
| `make sphere` | Generate a sphere |
| `make cube` | Generate a cube |
| `make torus` | Generate a torus |
| `make cylinder` | Generate a cylinder |
| `make cone` | Generate a cone |
| `make octahedron` | Generate an octahedron |
| `make view` | List all generated shapes |
| `make docs` | View documentation |
| `make clean` | Delete all generated shapes |

---

## 💡 Tips

1. **Experiment with descriptions**: Try different adjectives to modify shapes
   ```bash
   ./shape_gen "a tiny cube" cube
   ./shape_gen "a large smooth sphere" sphere
   ./shape_gen "a thick donut" torus
   ```

2. **Batch generation**: Run `make demo` to generate 5 shapes at once

3. **View coordinates**: Examine raw OBJ output
   ```bash
   head -20 output/shape_*.obj
   ```

4. **See all shapes**: Check output directory
   ```bash
   make view
   ```

---

## 🎓 Learning

To understand how the program works:
1. Read `README.md` (quick overview)
2. Check `QUICK_REFERENCE.md` (test results)
3. Study `TEST_REPORT.md` (technical details)

---

**Quick Start**: `cd OneCoreAI/shaper && make run`
