# 🛸 UFO

> A small 2D game about an alien, written in C/C++ as a coursework project on Object-Oriented Programming.

---

## 📖 Description

**UFO** is a small 2D game where you control an alien. The project is built in C/C++ using the [raylib](https://www.raylib.com/) graphics library, and demonstrates core OOP principles: encapsulation, inheritance, and polymorphism.

---

## 🗂️ Project Structure

```
Ufo-courcework/
├── src/          # Source files (.c / .cpp)
├── headers/      # Project header files (.h)
├── include/      # External library headers (raylib)
├── lib/          # External library binaries
├── data/         # Game assets (sprites, sounds, etc.)
├── .vscode/      # Visual Studio Code configuration
├── Ufo.exe       # Pre-built executable (Windows)
└── run.ps1       # PowerShell launch script
```

---

## 🚀 Getting Started

### Option 1 — Pre-built Executable

Just run `Ufo.exe` from the repository root. No installation required.

### Option 2 — Via PowerShell

```powershell
.\run.ps1
```

> **Note:** On first run, PowerShell may restrict script execution. Fix it with:
> ```powershell
> Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
> ```

### Option 3 — Build from Source (VSCode + GCC/MinGW)

1. Install **GCC** via [MinGW-w64](https://www.mingw-w64.org/).
2. Open the project folder in **Visual Studio Code**.
3. Use the build task (`Ctrl+Shift+B`) or compile manually:

```bash
gcc src/*.c -o Ufo.exe -I include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

---

## 🛠️ Tech Stack

| Component        | Details                                  |
|------------------|------------------------------------------|
| Language         | C / C++                                  |
| Graphics Library | [raylib](https://www.raylib.com/)        |
| Paradigm         | Object-Oriented Programming              |
| IDE              | Visual Studio Code                       |
| Platform         | Windows                                  |
| Scripting        | PowerShell                               |

---

## 📋 Requirements

- **OS:** Windows 7 / 10 / 11
- **To run `.exe`:** nothing extra needed — dependencies are bundled
- **To build from source:** GCC / MinGW-w64 and the `.dll` files from the `lib/` folder

---

## 🎓 Academic Context

This project was developed as a coursework assignment for the **Object-Oriented Programming** course. Key concepts applied:

- Class and object design
- Data encapsulation and method abstraction
- Game loop architecture
- User input handling
- 2D rendering with raylib

---

## 👤 Author

**Deokma** — [github.com/Deokma](https://github.com/Deokma)
