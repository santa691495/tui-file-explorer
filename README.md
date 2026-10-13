# TUI File Explorer
A simple file explorer written in C++ that runs inside your terminal!

---
## Usage
`./file-mgr-app <path>`

## Go into directories
Enter and view the contents of a directory. Options marked with
`[DIR]` can be entered using *arrow right*. Scroll using *arrow up* and *arrow down* 
to view more files for big directories. CTRL + C to stop program.

## Tech Stack & Notable Libraries Used
- The **Ncurses** library was used for TUI creation & window management
- **std::filesystem** for managing directories and file paths
- **CMake** for build automation

## Build & Run
*Note: Only works for Linux*

### Dependencies
**Debain/Ubuntu**
*Install Ncurses library:* `sudo apt install libncurses-dev`  
*Install CMake:* `sudo apt install cmake`

**Fedora/RHEL**
*Install Ncurses library:* `sudo dnf install ncurses-devel`  
*Install CMake:* `sudo dnf install cmake`

**Arch**
*Install Ncurses library:* `sudo pacman -S ncurses`  
*Install CMake:* `sudo pacman -S cmake`

### Build
1. **Go to project root:** `cd tui-file-explorer`
2. **Create build directory:** `mkdir build/`
3. **Generate build system:** `cmake -S . -B build/ -G "Unix Makefiles" #Or generator of your choice`
4. **Run:** `./build/file-mgr-app ~ #Or other paths`
