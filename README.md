#### **README.md**
```markdown
# Lego-Style Block Construction System

This C++ console application is a structural simulation of building with blocks (similar to Lego). It focuses heavily on **Operator Overloading**, allowing the user to "build" or "modify" structures using standard mathematical symbols.

## 🏗️ Project Overview
The system allows users to define individual `Block` objects with specific shapes (Simple, ObliquedL, ObliquedR) and colors. These blocks are then combined into a `Build` object, representing a larger structure with dimensions (Height, Width, Depth).

## 💎 Core OOP Concepts
- **Operator Overloading**: This is the highlight of the project. It redefines:
  - `+` and `+=` to combine two builds/blocks.
  - `-` and `-=` to remove structural components.
  - `^` and `^=` for vertical stacking (increasing height).
  - `*`, `/`, and `%` for repetitive building patterns.
- **Friend Functions**: Used for advanced operator overloading to allow interaction between different classes and stream objects.
- **Constructor Delegation**: Provides default and parameterized constructors to handle various block types and colors.

## ✨ Key Features
- **Structural Arithmetic**: Treat physical building like math. Adding a block to a build automatically updates the building's dimensions.
- **Validation**: Strict input handling ensures only valid shapes (ObliquedL/R, Simple) and colors (Red, White) can be created.
- **Visual Feedback**: A custom overloaded `<<` operator allows you to print the state of a complex building directly to the console.
- **Stacking Logic**: Specialized "XOR" (`^`) operator logic specifically handles the vertical placement of blocks.

## 🚀 How to Run
1. Ensure you have a C++ compiler installed.
2. Compile the file:
   ```bash
   g++ Q1.cpp -o LegoBuild
3. Run the application:
  ```bash
  ./LegoBuild
