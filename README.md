# 🎮 Board Games Engine – CS213 Assignment 3

📚 **Course:** Object Oriented Programming (CS213)  
🏫 **Faculty:** Faculty of Computing and Artificial Intelligence – Cairo University  
👨‍🏫 **Instructor:** Dr. Mohamed El-Ramly  

---

## 📌 Project Overview

This project is a **Modular Board Games Engine** developed as part of **Assignment 3** for the CS213 (Object Oriented Programming) course.

The main goal of this assignment is to apply **Object-Oriented Programming principles** in a scalable game framework that supports multiple board game variants and intelligent computer players.

The project is fully implemented in **C++** and focuses on clean architecture, separation of responsibilities, extensibility, and algorithmic decision-making.

---

## 🎯 Objectives

- Apply core **OOP concepts** (encapsulation, abstraction, polymorphism, modularity)
- Design a reusable and extensible board game framework
- Implement multiple game rule variations
- Develop AI agents using **Minimax** and **Alpha-Beta pruning**
- Practice state-space exploration and heuristic evaluation
- Maintain structured and documented code using **Doxygen**

---

## 🧩 Project Structure

The project is divided into multiple components, each responsible for a specific role:

### 📂 Components Description

- **BoardGame_Classes**  
  Provides the core board abstractions and shared game logic.

- **Game Variants (Diamond, Inverse XO, Hidden, etc.)**  
  Implement specific rule sets while extending the base architecture.

- **Player (Human / Computer)**  
  Handles player behavior and interaction with the board.

- **AI Engine**  
  Implements decision-making using Minimax and Alpha-Beta pruning.

- **Menu System**  
  Manages user interaction and game selection.

- **Documentation (Doxygen)**  
  Auto-generated API documentation for all classes and components.

---

## ✨ Features

- 🎮 Multiple board game variants
- 🤖 Intelligent AI players
- 🔍 Minimax with Alpha-Beta pruning
- 🧠 Heuristic evaluation functions
- 🧱 Modular and reusable architecture
- 📚 Auto-generated documentation
- 🛠 CMake-based build system

---

## 🤖 AI Implementation

The project includes intelligent computer players across multiple game variants.

Some variants implement advanced search-based decision-making:

- **Inverse XO**  
  Full-depth Minimax with Alpha-Beta pruning (game-theoretically optimal play).

- **Diamond Variant**  
  Depth-limited Minimax with weighted heuristic evaluation and custom directional win detection.

Other supported games also include AI-driven gameplay adapted to their rule structures.

All AI-enabled variants perform full move simulation with proper state rollback to ensure correct board evaluation.

---

## 🛠 Technologies Used

- **C++**
- Object-Oriented Programming (OOP)
- Minimax Algorithm
- Alpha-Beta Pruning
- CMake
- Doxygen
- Git & GitHub

---

## 🚀 How to Build & Run

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/mohamedelgendy522/Assignment_3.git
cd Assignment_3
```

### 2️⃣ Build Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Run the generated executable.

---

## 📚 Documentation

Full API documentation is available here:

🔗 https://a200b5.github.io/Assignment_3/

---

## 👥 Team Members

- Ahmed Bakr
- Ahmed Mansour
- Mohamed Mahmoud
- Youssef Mohamed

---

## 📌 Key Learning Outcomes

- Designing scalable systems using OOP
- Implementing search algorithms in real applications
- Writing maintainable and documented C++ code
- Structuring collaborative Git-based projects
