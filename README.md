# Project README

## Overview
The project appears to be a C/C++ application that simulates a star field using various libraries. The code includes functionality for creating a window, rendering lines and circles, handling random numbers, and managing dynamic memory for storing star positions.

## Features
- Creates a window (Linux: X11, Windows: WINAPI)
- Renders stars as points or lines (based on comments in the code)
- Handles random number generation for star positions
- Dynamically manages memory for storing star data
- Supports multiple build targets:
  - Linux
  - Windows (using MinGW-w64)
  - Webassembly (via Emscripten)

## Project Structure
```
Gui_Starfield/
├── src/
│   ├── Main.c          # Entry point
│   └── *.h             # Standalone header files used by Main.c
├── Makefile.linux      # Linux build configuration
├── Makefile.windows    # Windows build configuration
├── Makefile.wine       # Wine build configuration for cross-compiling to Windows on Linux
├── Makefile.web        # Webassembly build configuration via Emscripten
└── README.md           # This file
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed for specific projects:
  - X11 for Linux GUI
  - MinGW-w64 for Windows cross-compilation
  - Emscripten for Webassembly

## Build & Run
### Building on Linux
To build the project on Linux, execute the following commands:
```sh
cd Gui_Starfield
make -f Makefile.linux all
```

### Running on Linux
After building, you can run the application with:
```sh
make -f Makefile.linux exe
```

### Building on Windows
To build the project for Windows using MinGW-w64 on Linux, execute:
```sh
cd Gui_Starfield
make -f Makefile.windows all
```

### Running on Windows
After building, you can run the application with:
```sh
make -f Makefile.windows exe
```

### Building for Webassembly
To build the project for Webassembly using Emscripten, execute:
```sh
cd Gui_Starfield
make -f Makefile.web all
```

Then, to serve and view the generated HTML file in a browser, run:
```sh
make -f Makefile.web exe
```
This will start an HTTP server on port 8080, allowing you to access the Webassembly application via a web browser.