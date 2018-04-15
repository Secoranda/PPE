
# Laboratory work analysis
## Description 
That's a Windows application.
 
The purposeof this laboratory work is to create a Windows Timer which involves some animated objects. Classic objects used are 
circle and rectangle. 

Code was implemented in C++...


## Was implemented
### Mandatory Objectives
1. Create an animation based on Windows timer which involves at least 5 different drawn objects. 

On each press of right button of mouse will be created a circle that will move on windows margins. To not have infite objects on the screen, there's a limit of 100 objects given from the start (depends only on the array given from the start). And each object has a random color set on its launch on the window.

### Objectives with points
1. Increase and decrease animation speed using mouse wheel (2pt)

Is possbile to increase and decrease animation speed using mouse wheel. However, this action affects all objects from the window. This is done by message WM_MOUSEWHEEL.
Also, when screen is maximized, objects can move through each space, and when minimized they came back minimized window limits.

2. Solve flickering problem (2 pt) please describe in your readme/report how you did it

Here are some approaches that I found on internet. To draw without flickering is possible to use BitBlt function. As per definition: The BitBlt function performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.

To be more specific: was created a "memory" device context using CreateCompatibleDC(hdc) and all the drawings was done on that device context, then was copied the invalidated portions of the window to the actual device context when appropriate, using the BitBlt() function after which the "memory" created was destroyed.

Also,was needed to disable background clearing (handle WM_ERASEBKGND window message appropriately) before the draw happens

3. Add animated objects which interact with each other (2-6 pt)

When circles hit the right and bottom margins (possible to change margins) of the window they change their shape in rectangles. 
When objects hit the left and right margins of the window they increase their speed and decrease when hit top and bottom.
In case objects (cirlces or rectangles) hit once each other, they earliest launched object on the window will change its color in black.
The latest object will mantain its color until other object won't be launched.

Also, using message WM_KEYDOWN, objects' speed can be changed using VK_DOWN- which will slow down the objects and VK_UP- which will speed up the objects. Another case is space button, using VK_SPACE, a new circle will be launched with a increase speed already.

### Disadvantages in the program

1. All objects are launched on the same angle, depends only the mouse position, or in case of VK_SPACE, there's a random spin for object coordinates.
2. Objects change shapes after one interation (remain in rectagles)
3. Was not implemented: Animate a Nyan Cat that leaves a rainbow tail
