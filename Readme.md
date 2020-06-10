# Problem1 - Circle Drawer

# Introduction
This code creates an App that allows user to create circle by drag and release.

# Algorithm - Breshenham Circle Draw
For activating the points to represent the circle breshenham circle drawing algorithm was used.
- Set initial values of (xc, yc) and (x, y)
- Set decision parameter d to d = 3 – (2 * r).
- call drawCircle(int xc, int yc, int x, int y) function.
- Repeat steps 5 to 8 until x < = y
- Increment value of x.
- If d < 0, set d = d + (4*x) + 6
- Else, set d = d + 4 * (x – y) + 10 and decrement y by 1.
- call drawCircle(int xc, int yc, int x, int y) function

credits: https://www.tutorialspoint.com/computer_graphics/circle_generation_algorithm.htm

# GUI
The interface used is wxWidgets to create the GUI which is platform agnostic.

## Getting Started

These instructions is to help you get started,

### Prerequisites

- g++ Compiler
- wxWidgets

### How To Use
- The Executable Provided is meant to be run in Linux Platforms. The GUI is used is plaform agnostic and can run in Windows, Mac and Linux.

## Versioning
- 1.0
    - First Release
    - Known Bug
        - The screen resets on increasing or decreasing size of the window


## Authors

* **Subhransu Mahapatra** 



 
