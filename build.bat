@echo off
echo Compiling project...

REM Compile all source files
g++ App/Main.cpp Core/GameLoop.cpp Core/MainRenderer.cpp -IC:/mingw64/include -ICore -LC:/mingw64/lib -lfreeglut -lopengl32 -lgdi32 -lglu32 -o game.exe

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build successful! Output: game.exe
pause
