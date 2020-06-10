# Program1 - Circle Drawer

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
The interface used is wxWidgets to create the GUI which is platform agnostic. The interface can be installed in Windows, Linux and Mac.


## Getting Started

These instructions is to help you get started,

### Prerequisites

- g++ Compiler
- wxWidgets

### Installing wxWidgets 
#### Linux
- $ sudo apt-get install libgtk-3-dev build-essential checkinstall
- Download and Extract wxWidget. https://www.wxwidgets.org/downloads/
- $ mkdir gtk-build
- $ cd gtk-build/
- $ ../configure --disable-shared --enable-unicode
- $ make
It Takes about 20 mins to build.
Credits: https://www.binarytides.com/install-wxwidgets-ubuntu/

### How To Use
- After the prerequisites are done download the github repository
-  $ make (type make to invoke the make file)
- ./CircleDrawer

## Versioning
- 1.0
    - First Release
    - Known Bug
        - The screen resets on increasing or decreasing size of the window


## Authors

* **Subhransu Mahapatra** 



 
