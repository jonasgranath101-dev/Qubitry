# Terminal Quick Guide - Shape Generator

##  Start Here (Copy & Paste)

```bash
cd OneCoreAI/shaper && make run
```

That's it! This launches the interactive menu.

---

##  One-Line Commands

```bash
# Generate and view examples
make demo

# Generate individual shapes
make sphere
make cube
make torus
make cylinder
make cone

# Create custom shape
./shape_gen "a large smooth sphere" sphere

# View what you generated
make view

# See help
make help
```

---

##  Navigation

```bash
# Go to project folder
cd OneCoreAI/shaper

# All commands below assume you're in this folder
```

---

##  Interactive Menu

```bash
make run
```

Provides menu with options:
- Generate custom shape
- Run demo (5 examples)
- Quick generators (sphere, cube, etc.)
- View generated shapes
- Read documentation

---

## 🔧 Manual Commands

### Generate a Shape
```bash
./shape_gen "description" shape_type
```

**Examples**:
```bash
./shape_gen "a smooth sphere" sphere
./shape_gen "a small box" cube
./shape_gen "a thick donut" torus
./shape_gen "a tall column" cylinder
./shape_gen "a sharp peak" cone
./shape_gen "a crystal" octahedron
```

### View Generated Files
```bash
ls -lh output/          # List all shapes
head -50 output/shape_*.obj    # View first shape
wc -l output/shape_*.obj       # Count vertices
```

### Batch Operations
```bash
make demo               # Generate 5 examples
make clean              # Delete all outputs
```

---

## 📊 Current Status

```bash
# Check what's installed
make help              # Show all commands with descriptions
make view              # List generated shapes
make docs              # Show documentation files
```

---

## 📁 Where Everything Is

```
OneCoreAI/shaper/
├── run.sh              ← Interactive launcher (make run)
├── demo.sh             ← Example generator (make demo)
├── Makefile            ← All convenient commands
├── shape_gen           ← Compiled program
├── output/             ← Your generated shapes
├── GETTING_STARTED.md  ← This file
├── README.md           ← Original docs
├── TEST_REPORT.md      ← Technical details
└── INDEX.md            ← Full documentation index
```

---

## 💡 Most Used Commands

| What You Want | Run This |
|--------------|----------|
| Interactive menu | `make run` |
| See examples | `make demo` |
| Generate sphere | `make sphere` |
| Generate cube | `make cube` |
| List all shapes | `make view` |
| See help | `make help` |
| Clean up | `make clean` |

---

##  Keyword Tips

Words that affect output:

```bash
# Size
"small" or "tiny"     → Half size
"large" or "big"      → Double size

# Sphere
"smooth"              → More detail

# Torus
"thick"               → Thicker donut

# Cylinder
"tall"                → Taller shape

# Cone
"sharp" or "pointed"  → Sharper point
```

**Example**:
```bash
./shape_gen "a large smooth sphere" sphere        # Big detailed sphere
./shape_gen "a small compact cube" cube           # Tiny cube
./shape_gen "a large thick donut" torus          # Fat donut
```

---

##  Troubleshooting

| Problem | Solution |
|---------|----------|
| `make: command not found` | You need `make` installed (or use `./run.sh` directly) |
| `Permission denied` | Run `chmod +x *.sh` |
| `shape_gen not found` | Run `make build` or `gcc -o shape_gen shape_generator.c -lm` |
| Nothing generated | Check `make view` or `ls output/` |

---

##  Learn More

```bash
make docs              # Show doc files with sizes
less README.md         # Quick start
less QUICK_REFERENCE.md # Test results
less TEST_REPORT.md    # Technical deep dive
```

Or just: `make run` → Option 9 → View documentation

---

##  Pro Tips

### Bash Aliases (Optional)
```bash
# Source this once in your .bashrc or .zshrc:
source aliases.sh

# Then use shortcuts:
shaper              # Launch interactive menu
sphere              # Quick sphere
gen-shape "desc" type   # Custom shape
```

### One Command at a Time
```bash
make clean          # Clean old files
make demo           # Generate examples
make view           # See results
```

### Piping
```bash
# Count vertices in a shape
wc -l output/shape_*.obj | tail -1

# Find largest generated file
ls -S output/shape_*.obj | head -1

# Copy a shape for backup
cp output/shape_*.obj output/backup_$(date +%s).obj
```

---

## ✅ Verification

Check everything works:
```bash
make help    # Shows all commands
make build   # Compiles program
make demo    # Generates examples
make view    # Lists output
```

If all work, you're ready!

---

**TL;DR:**
```bash
cd OneCoreAI/shaper
make run
```

Then choose option from menu! 🎉
