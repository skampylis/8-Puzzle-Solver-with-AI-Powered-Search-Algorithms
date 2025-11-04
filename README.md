# **8 Puzzle Solver with AI-Powered Search Algorithms**

## **Description**

A **C++** program that solves the **8-puzzle** using four search algorithms (**DFS, BFS, Best-FS, A***).
It employs **heuristic strategies** (Manhattan distance) and **data structures** (stack, queue, priority queue) to find the optimal sequence of moves — demonstrating the efficiency of **AI algorithms** in combinatorial problem solving.

---

### 🚀 **Project Overview**

This project implements **four search algorithms** — DFS, BFS, Best FS, and A* — to solve the classic **8-puzzle problem**, where the goal is to arrange tiles in a 3×3 grid using the fewest possible moves.

* **Main challenge**: Move the tiles around the empty space (0) to reach the target configuration.
* **AI Application**: Analyze the behavior and efficiency of different search algorithms in combinatorial problems.

---

### 🔍 **Key Features**

* **Supported Algorithms**:

  * **DFS & BFS** – Linear search algorithms using stack/queue structures.
  * **Best FS** – Greedy strategy guided by the **Manhattan distance heuristic**.
  * **A*** – Combines path cost and heuristic evaluation for **optimal performance**.
* **Data Structures**: Uses priority queues, hash maps, and closed-set management for efficient state exploration.
* **Efficient Modeling**: A `State` class models puzzle configurations, possible moves, and heuristic computations.

---

### 🛠️ **Technical Highlights**

* **Heuristic Functions**:

  * **Manhattan Distance** – Calculates the total distance of all tiles from their target positions.
  * **A* Optimization** – Balances path depth (g-cost) and heuristic (h-cost) to minimize total cost (f = g + h).
* **Dynamic Expansion**: Automatically generates child states by sliding tiles **up, down, left, or right**.

---

### 📂 **Code Structure**

* **`main.cpp`** – Handles user input/output and algorithm selection.
* **`State.h / State.cpp`** – Defines the `State` class for representing puzzle states, moves, and heuristic functions.

---

**🏷️ Tags**: `AI`, `Search Algorithms`, `8-Puzzle`, `C++`, `Manhattan Distance`, `Pathfinding`
**🌟 Concept**: *"An educational tool designed to explore the hierarchy and efficiency of search algorithms in Artificial Intelligence."*
