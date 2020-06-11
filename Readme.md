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

# Walkthrough
The GUI interface used is wxWidgets to create the GUI which is platform agnostic. The interface can be installed in Windows, Linux and Mac.
1. The bacground dot grid is constructed with small rectangles that activate and deactivate based on mouse clicks.
2. Drag and Release is used to select the circle center and radius.
3. Once that is done we draw the digitized circle based on Breshenham algorithm. This is also used to determine max radius and min radius.
4. We draw the circles based on this data using wxWidgets DC class members.
5. To refresh the window we can click on the screen.

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
Credits: https://www.binarytides.com/install-wxwidgets-ubuntu/
#### Windows
- A nice intro to setup wxWidgets Video: https://www.youtube.com/watch?v=sRhoZcNpMb4
- Download the Windows zip file - https://www.wxwidgets.org/downloads/
- Unpack it
- Go to build -> msw -> vx_vc16.sln 
- Select compile mode (32 bit / 64 bit) and build
- Restart Visual Studio
- To manual setup refer ~/docs/msw/install.md
- For Auto setup use the property sheet. 


It Takes about 20 mins to build.


### How To Use
- After the prerequisites are done download the github repository
-  $ make (type make to invoke the make file)
- ./CircleDraw

## Test Cases
### Manual Testing
- Constructing Different size circles (small to large)
- Closing and opening the application
- Checking mouse click to activate the desired grid points (Corners and center locations)
- Left click refresh
### Unit Testing
- TODO

## Versioning
- 1.0
    - First Release
    - Known Bug
        - The screen resets on increasing or decreasing size of the window
        - Activation of gridpoints near midway of 2 gridpoints is left biased. 


## Authors

* **Subhransu Mahapatra** 



 
