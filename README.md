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
### Dependencies

### Build
**Go to project root:** `cd file-manager`
**Create build directory:** `mkdir build/`
**Generate build system:** `cmake -S . -B build/ -G "Unix Makefiles" #Or generator of your choice`
**Run:** `./build/file-mgr-app ~ #Or other paths`
