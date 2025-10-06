# GameProject

## Overview

This project is a 2D platformer built from scratch without using a pre-existing game engine. My goal for this project is to learn and experiment with:

1. **C++** – mastering classes, object-oriented design, memory management, and multi-threading.  
2. **.NET integration** – adding multiplayer support later using C#/.NET components <-- THIS IS HAPPENING LATER WAAAY LATER 
3. **OpenGL** – learning how to render 2D graphics, handle textures, and manage game loops manually.  
4. **Game design** – understanding physics, collisions, player movement, input handling, and level design.  

---

## Project Structure

GameProject/
│
├─ Core/ # Core game logic and assets
│ ├─ Levels/
│ │ ├─ FirstLevelRender.cpp
│ │ ├─ FirstLevelRender.h
│ ├─ Collisions.cpp
│ ├─ Collisions.h
│ ├─ GameLoop.cpp
│ ├─ GameLoop.h
│ ├─ Gravity.cpp
│ ├─ LoadTexture.cpp
│ ├─ LoadTexture.h
│ ├─ MainPlayer.cpp
│ ├─ MainPlayer.h
│ ├─ MainRenderer.cpp
│ ├─ MainRenderer.h
│ ├─ PlayerInputHandler.cpp
│ └─ stb_image.h
│
├─ Sprites/ # Game textures and sprites
│ └─ testSprite.png
│
├─App/ # Entry point for the game
│├─ Main.cpp
│
├─ Build.bat # Builds the game
│
└─ README.md

---

## Dependencies

- **C++17 or later**  
- **OpenGL** for rendering  
- **GLUT / FreeGLUT** for window management and input handling  
- **stb_image.h** for loading PNG textures  
- **Windows SDK** (for Sleep and threading; cross-platform threading can be added later)  

---

## Build Instructions (Windows, MinGW)

1. Ensure you have **MinGW** installed with OpenGL and FreeGLUT.  
2. Include the directories for OpenGL and GLUT headers/libs in your build script.  
3. Compile all `.cpp` files together:

Click the Build.bat file:

```bat
@echo off
echo Compiling project...

REM Compile all source files WILL ADD YOUR FILES TO THIS BEFORE TRYING TO BUILD!!!!!!!!!!
g++ App/Main.cpp Core/GameLoop.cpp Core/MainRenderer.cpp Core/Collisions.cpp Core/LoadTexture.cpp Core/MainPlayer.cpp Core/Gravity.cpp Core/PlayerInputHandler.cpp Core/Levels/FirstLevelRender.cpp -IC:/mingw64/include -ICore -LC:/mingw64/lib -lfreeglut -lopengl32 -lgdi32 -lglu32 -o game.exe

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build successful! Output: game.exe
pause
```

