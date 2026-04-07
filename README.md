# Osmosis

A terminal-based C++ implementation of **Osmosis**, a solitaire-style card game built as a class project. The game runs in the console and uses object-oriented design to model cards, stockpiles, foundations, and overall game flow.

## Overview

This project recreates the card game **Osmosis** in a text-based interface. The player manages stockpiles, a waste/discard pile, and four foundation piles while following the game's suit-building and rank-propagation rules.

The program includes:
- shuffled 52-card deck generation
- terminal-based game board display
- stockpile, waste pile, and foundation mechanics
- command-driven gameplay
- rule validation for legal moves
- redeal / peel game actions
- help and instruction text files loaded from the project

## Rules Summary

Osmosis is a solitaire game where cards are moved onto four foundations.

- The **top foundation** starts with one face-up card.
- The other foundations begin empty.
- Cards placed on a foundation must match that foundation's **suit**.
- Lower foundations also follow the **osmosis rule**: a rank can only be played if that same rank has already appeared in the top foundation.
- Empty lower foundations may be started with a new suit that has not already been used in another foundation, but the card must still satisfy the osmosis rule.
- The goal is to move all cards onto the foundations.

## Project Structure

```text
card.h / card.cpp           Card representation (rank and suit)
stockpile.h / stockpile.cpp Stockpile behavior and card access
foundation.h / foundation.cpp Foundation logic and osmosis rule handling
game.h / game.cpp           Main game state, layout, input, and gameplay loop
main.cpp                    Program entry point
instructions.txt            In-game instructions
about.txt                   Project info / author info
osmosis.txt                 Title / text asset
makefile                    Build file
```

## Build and Run

### Requirements
- `g++`
- a terminal that supports ANSI escape codes for colored suit output

### Build
From the project directory:

```bash
g++ -pedantic-errors -g main.cpp card.cpp stockpile.cpp foundation.cpp game.cpp -o osmosis
```

Or, using the included makefile:

```bash
make
```

### Run
```bash
./osmosis
```

Note: depending on your current makefile target, the compiled output may be named `main`. If so, run:

```bash
./main
```

## Concepts Demonstrated

This project demonstrates several core C++ topics:
- classes and object-oriented design
- inheritance and polymorphism
- operator overloading
- dynamic memory management
- vectors, sets, and maps from the STL
- file input for loading project text assets
- game-state validation and command processing



## Author

**Caio Souza**  
Created for **CSCI201**  

