# Minesweeper Console Edition (C++)

A command-line implementation of the classic Minesweeper game, written in C++. This project features a fully playable 9x9 grid with randomized mine placement, player-controlled digging, and dynamic board updating.

## Features

- **Dynamic 9x9 Game Board:**  
  Mines and safe spots are initialized randomly at runtime.

- **Safe First Move:**  
  Guarantees that the player's first selection is never a mine.

- **Recursive Digging:**  
  Automatically uncovers adjacent blank cells using a flood-fill approach.

- **Victory and Defeat Conditions:**  
  Win by uncovering all non-mine tiles, or lose instantly on uncovering a mine.

- **User Input Validation:**  
  Ensures entered coordinates are within valid bounds.

## Technical Details

- Written entirely in **C++** using **standard libraries** (`<iostream>`, `<vector>`, `<algorithm>`).
- Utilizes **object-oriented design** via a `Board` class managing the game state and player actions.
- Randomized mine placement and neighboring bomb calculations are handled programmatically.
- Recursive logic ensures efficient blank space reveal without redundant operations.

## How to Run

1. Compile the program:
   ```bash
   g++ -o minesweeper minesweeper.cpp
   ```
2. Run the executable:
   ```bash
   ./minesweeper
   ```
