# ICT289 Obstacle Course - Donic the Ledge Hog
## About
A simple 3D obstacle course game. Jump between platforms. Dodge or ride the mooving platforms. Collect coins. Beware of the breaking platforms.

# Controls
- WASD for movement
- Spacebar to jump (hold longer to go up longer)
- Q to reset course
- N to turn on wind
- M to toggle moonjump cheat
- P to show credentials, then click screen to quit

# Build Instructions
## Visual Studio 2019
### Requirements
- CMake extension
### Steps
1. `git submodule update --init --recursive --depth 1`
1. Open repository as folder in VS 2019
1. Right-click `CMakeLists.txt` in root folder  and click "Generate Cache for ICT289"
1. Set "ICT289.exe" as startup item
## Visual Studio Code
### Requirements
- [CMake tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension
### Steps
1. `git submodule update --init --recursive --depth 1`
1. Open repository in Visual Studio Code
1. Navigate to the "CMake" activity on the activity bar on the far left
1. Click "Configure All Projects" and select a "kit" (toolchain)
1. Right-click the "ICT289" target and click "Run in Terminal"

