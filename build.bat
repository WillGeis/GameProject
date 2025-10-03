@echo off
echo Compiling project...

g++ Main.cpp MainRenderer.cpp -IC:/mingw64/include -LC:/mingw64/lib -lfreeglut -lopengl32 -lgdi32 -o game.exe

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b %ERRORLEVEL%
)

echo Build successful! Output: blank.exe
pause
