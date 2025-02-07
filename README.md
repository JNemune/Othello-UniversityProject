# Othello Game AI  

This project implements an **AI-powered Othello (Reversi) game** with **multiple difficulty levels** and **cross-platform support** for **Windows and Linux**.  

## 📌 Features  
- **Game Modes:**  
  - **Two-player mode** (Human vs. Human)  
  - **AI difficulty levels**: Easy, Normal, Hard  
- **AI Strategies:**  
  - **Easy**: Random moves  
  - **Normal**: Greedy algorithm (maximizes immediate gains)  
  - **Hard**: Advanced heuristic-based decision making  
- **Customizable Board Size** (4×4 to 20×20)  
- **Graphical Board Display** with ASCII-based UI  
- **Cross-Platform Compatibility**  
  - **Windows**: Uses `Windows.h` for console output  
  - **Linux**: Uses `unistd.h` for Unix-based console operations  

---

## 🏗️ Project Structure  
```
OthelloGameAI/
│── Linux/                    # Linux-specific files  
│   │── ai_main               # Compiled AI binary for Linux  
│   │── ai_main.cpp           # AI logic implementation  
│   │── SourceLinux.cpp       # Game logic for Linux  
│   └── .vscode/              # VSCode settings  
│       ├── c_cpp_properties.json  
│       ├── launch.json  
│       ├── settings.json  
│       ├── tasks.json  
│  
│── Windows/                  # Windows-specific files  
│   │── Othello.exe           # Precompiled Windows executable  
│   │── SourceWindows.cpp     # Game logic for Windows  
│  
│── README.md                 # Documentation  
```

---

## 🔧 Installation & Compilation  
### **1️⃣ Linux (Ubuntu, Debian, Arch, etc.)**  
**Install `g++` if not already installed:**  
```bash
sudo apt update && sudo apt install g++
```
**Compile and Run:**  
```bash
cd Linux
g++ -o othello SourceLinux.cpp ai_main.cpp -std=c++11
./othello
```

### **2️⃣ Windows (MinGW or Visual Studio)**  
#### **Using MinGW (Command Line Compilation)**
**Install `g++` for Windows** ([MinGW-w64](https://www.mingw-w64.org/)):  
```powershell
winget install -e --id MSYS2.MSYS2
```
**Compile the Game:**  
```powershell
cd Windows
g++ -o Othello.exe SourceWindows.cpp ai_main.cpp -std=c++11
./Othello.exe
```
#### **Using Visual Studio**  
1. Open **Visual Studio**  
2. Create a **New C++ Console Project**  
3. Copy **`SourceWindows.cpp`** and **`ai_main.cpp`** into the project  
4. Build and Run  

---

## 🎮 How to Play  
### **Main Menu Options**
```
Welcome to THE BEST OTHELLO GAME!  
1. New Game  
2. Change Board Size  
3. Demo Mode  
4. Exit  
```
- **Select an option by typing `1`, `2`, `3`, or `4`.**  

### **Game Controls**
- Enter your **move coordinates** (row, column) when prompted.  
- Available moves are marked with a **dot (.)**.  
- The game will update and display the board after each move.  
- The game **ends when no legal moves remain**.  

### **AI Difficulty Levels**
```
1. Two-Player Mode  
2. CPU: Easy (Random Moves)  
3. CPU: Normal (Greedy Algorithm)  
4. CPU: Hard (Heuristic AI)  
```

---

## 🏗️ Development Plan  
✅ **Current Features**  
- **Basic game mechanics** (move validation, flipping pieces)  
- **Two-player and AI modes**  
- **Board visualization with ASCII-based UI**  

🚀 **Planned Features**  
- **Minimax Algorithm with Alpha-Beta Pruning** for smarter AI  
- **Graphical User Interface (GUI) with SDL or OpenGL**  
- **Networked Multiplayer Support**  

---

## 🏆 AI Strategy Breakdown  
| Difficulty | Strategy Description |
|------------|----------------------|
| **Easy** | Selects **random valid moves** |
| **Normal** | Uses a **greedy algorithm** (chooses move with max immediate gains) |
| **Hard** | Uses **heuristics** (prioritizes corners, edges, and minimizing opponent's moves) |

---

## 📝 Notes  
- The **Linux and Windows versions are separate**, but both share similar game logic.  
- The **game runs entirely in the terminal** (no GUI).  
- The **hard AI mode** is **not fully optimized yet**—planned improvements include **Minimax-based AI**.  

---

## 📧 Contact  
For questions, bug reports, or feature requests, feel free to contribute!  

📌 **Developed for AI-based Othello Game with Cross-Platform Support**  