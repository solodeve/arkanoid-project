# Arkanoid Game - LDP2 Project

![Language](https://img.shields.io/badge/Language-C++-blue.svg)
![Graphics](https://img.shields.io/badge/Graphics-Allegro%205-green.svg)
![Standard](https://img.shields.io/badge/C++-20/23-orange.svg)

A modern implementation of the classic Arkanoid/Breakout game written in C++ using the Allegro 5 graphics library.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Game Controls](#game-controls)
- [Power-ups](#power-ups)
- [Installation](#installation)
- [Building the Project](#building-the-project)
- [Running the Game](#running-the-game)
- [Project Structure](#project-structure)
- [Game Mechanics](#game-mechanics)
- [Levels](#levels)
- [Technical Details](#technical-details)
- [Development](#development)
- [Contributors](#contributors)

## 🎮 Overview

This is a classic Arkanoid-style breakout game where the player controls a paddle (Vaus) to bounce a ball and destroy bricks. The game features multiple levels, various power-ups, different brick types, and a scoring system with high score tracking.

## ✨ Features

- **Multiple Levels**: 9 unique levels with different brick layouts
- **Power-up System**: Various power-ups that enhance gameplay
  - Laser shooting capability
  - Paddle expansion
  - Ball catching ability
  - Ball slow down
  - Interruption power
- **Brick Types**: 
  - Regular bricks (destructible)
  - Gold bricks (indestructible)
  - Multi-hit bricks
- **Scoring System**: Points awarded for destroying bricks
- **High Score Tracking**: Persistent high score storage
- **Lives System**: Player starts with 3 lives
- **Mouse and Keyboard Controls**: Flexible input options
- **Collision Detection**: Accurate ball-to-brick and ball-to-paddle physics

## 🎮 Game Controls

### Keyboard Controls
- **Arrow Keys** or **A/D**: Move paddle left/right
- **Space**: 
  - Release caught ball (when catch power-up is active)
  - Fire laser (when laser power-up is active)
- **ESC**: Exit game

### Mouse Controls
- **Mouse Movement**: Control paddle position
- **Left Click**: 
  - Release caught ball
  - Fire laser

## 🔋 Power-ups

The game features several power-ups that appear when certain bricks are destroyed:

| Power-up | Effect | Description |
|----------|--------|-------------|
| **Laser** | 🔫 | Allows the paddle to shoot lasers that can destroy bricks |
| **Expand** | ↔️ | Increases the paddle width for easier ball control |
| **Ball Catch** | 🎯 | Allows the paddle to catch and hold the ball before releasing |
| **Slow Down** | 🐌 | Reduces ball speed for better control |
| **Interruption** | ⏸️ | Temporarily disables other power-ups |
| **Player** | 👤 | Grants an extra life |

## 🛠️ Installation

### Prerequisites

- **C++ Compiler**: Supporting C++20/23 (GCC recommended)
- **Allegro 5**: Graphics and multimedia library
- **pkg-config**: For library configuration
- **Make**: Build system

### Installing Dependencies

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install liballegro5-dev
sudo apt-get install pkg-config
```

#### macOS (with Homebrew):
```bash
brew install allegro
brew install pkg-config
```

#### Windows:
- Install MSYS2 or use Visual Studio with vcpkg
- Install Allegro 5 development libraries

## 🔨 Building the Project

1. **Clone or download the project**
2. **Navigate to the project directory**
3. **Build using Make**:

```bash
make
```

This will:
- Compile all source files
- Link with Allegro libraries
- Create the executable `main`

### Build Commands

- `make` or `make all`: Build the project
- `make run`: Build and run the game
- `make clean`: Clean build files

## 🚀 Running the Game

After building, run the game with:

```bash
./main
```

Or use the Make target:

```bash
make run
```

## 📁 Project Structure

```
projet-ldp2-arkanoid/
├── src/                    # Source code
│   ├── main.cpp           # Main game loop
│   ├── controller/        # Input handling
│   ├── model/             # Game logic
│   │   ├── ball.cpp/hpp   # Ball physics and collision
│   │   ├── brick.hpp      # Brick definitions
│   │   ├── game.cpp/hpp   # Game state management
│   │   ├── level.cpp/hpp  # Level loading and management
│   │   ├── power_up.cpp/hpp # Power-up system
│   │   ├── vaus.cpp/hpp   # Paddle (Vaus) logic
│   │   └── ...
│   └── view/              # Rendering
│       ├── draw.cpp/hpp   # Main drawing functions
│       └── allegro_draw.cpp/hpp # Allegro-specific rendering
├── level/                 # Level definition files
│   ├── level1.txt
│   ├── level2.txt
│   └── ...
├── build/                 # Compiled object files
├── Makefile              # Build configuration
├── highScore.txt         # High score storage
└── README.md            # This file
```

## 🎯 Game Mechanics

### Ball Physics
- Realistic collision detection with bricks and paddle
- Ball speed increases over time
- Collision angles depend on where the ball hits the paddle

### Scoring System
- Different bricks award different points
- Bonus points for consecutive hits
- High score persistence across game sessions

### Lives System
- Player starts with 3 lives
- Life lost when ball falls below paddle
- Game over when all lives are lost

### Level Progression
- 9 levels total
- Each level has unique brick arrangements
- Progress automatically to next level when all destructible bricks are cleared

## 📊 Levels

The game includes 9 pre-designed levels stored in text files (`level1.txt` to `level9.txt`). Each level file defines:
- Brick positions (x, y coordinates)
- Brick colors
- Power-up assignments
- Brick durability

### Level Format
```
x,y,COLOR,PowerUp
50,50,COLOR_WHITE,None
120,50,COLOR_RED,laser
...
```

## 🔧 Technical Details

### Architecture
- **Model-View-Controller (MVC)**: Clean separation of concerns
- **Object-Oriented Design**: Encapsulated game entities
- **Modern C++**: Utilizing C++20/23 features

### Key Classes
- **Game**: Main game state and logic management
- **Ball**: Ball physics, movement, and collision detection
- **Vaus**: Paddle control and properties
- **PowerUp**: Power-up system and effects
- **Level**: Level loading and brick management
- **Draw**: Rendering and graphics

### Libraries Used
- **Allegro 5**: Graphics, input, and system functions
- **Standard Template Library (STL)**: Data structures and algorithms

## 🚧 Development

### Current Status
The game is fully playable with all core features implemented.

### Known Issues
- Some collision detection edge cases with gold bricks
- Code cleanup and documentation in progress

### Future Improvements
- Enhanced visual effects
- Sound system integration
- Additional power-ups
- Level editor
- Multiplayer support

## 👥 Contributors

This project was developed as part of the LDP2 (Langages de Programmation 2) course.

## 📄 License

This project is developed for educational purposes as part of university coursework.