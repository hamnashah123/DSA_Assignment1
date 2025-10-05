
# DSA Assignment 1 – Hamna Shah

## Introduction

This repository includes solutions to three core Data Structures and Algorithms (DSA) assignment problems. Each task has been developed in **C++**, demonstrating the use of **object-oriented programming principles** such as abstraction, encapsulation, and modular design.

---

## Approach

The assignment is composed of **three independent problems**, each designed using `.h` and `.cpp` files to ensure separation between implementation and interface. The focus throughout was to maintain clean structure, logical flow, and hidden internal details.

### 1. Polynomial Abstract Data Type (ADT)

* Implemented using logic similar to **linked lists**, allowing dynamic management of polynomial terms.
* Features include **insertion, printing, addition, multiplication, and differentiation** of polynomials.
* Edge cases such as **duplicate exponents**, **zero or negative coefficients**, and **term merging** were handled effectively.

### 2. Text Editor Simulation

* A **cursor-based text editor** designed using two **stacks** — one for text to the left of the cursor and one for text to the right.
* Supports operations like **inserting characters**, **deleting text**, and **moving the cursor** left or right.
* Safeguards added for scenarios such as **deleting from an empty editor**, **cursor movement beyond limits**, and **invalid input handling**.

### 3. UNO Card Game Simulation

* A simplified **UNO card game** that supports **2–4 players**.
* Implements a **76-card deck** (standard UNO without wild cards) and ensures a fair game start using a **fixed random seed (1234)** for deterministic shuffling.
* Includes full logic for **Skip, Reverse, and Draw Two** cards, with correct turn order and direction handling.
* Handles rare edge cases like **deck depletion**, **stalemates**, and **Reverse card behavior in 2-player mode**.

---

## Challenges Faced

### 1. **Maintaining Abstraction with Locked Header Files**

* The `.h` files could not be modified, so implementation details were carefully hidden using **maps**, **helper structs**, and **private data encapsulation** in `.cpp` files.
* This required maintaining a strict boundary between the class interface and its internal logic.

### 2. **Polynomial Edge Case Handling**

* Duplicate powers were merged efficiently during insertion and addition.
* Zero coefficient terms were automatically removed to prevent redundancy.
* Special attention was given to negative exponents and large coefficients during multiplication and differentiation.

### 3. **Text Editor Cursor Logic**

* Synchronizing cursor movement with both stacks without losing characters was challenging.
* Ensuring deletion operations behaved correctly at text boundaries required additional condition checks.
* Managing undo-like behavior through stack transitions tested control flow precision.

### 4. **UNO Game Mechanics**

* Implementing realistic card-playing logic with action cards required multi-step validation.
* Special rule management (like **Reverse acting as Skip** in a 2-player game) demanded conditional branching.
* Deck reusability and graceful termination in case of stalemate were important to avoid runtime issues.

### 5. **Technical and GitHub Management**

* Configuring `.gitignore` to avoid tracking temporary and compiled files (like `.o`, `.DS_Store`, etc.) was essential.
* Regular commits ensured version control, and all unnecessary build artifacts were cleaned to keep the repository organized.
* Compilation issues (especially on macOS with `arm64` architecture) were handled using consistent build flags.

---

## GitHub Repository
[https://github.com/hamnashah123/DSA_Assignment1/tree/main]
[https://github.com/hamnashah123/DSA_Assignment1.git]