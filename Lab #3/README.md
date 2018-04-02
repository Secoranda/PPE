
# Laboratory work analysis
## Description 
That's a Windows application.
 
Main idea of the app is to create GDI Primitives based on Mouse Moving. Was implemented buttons for drawing lines, ellipses, rectangles 
and a button for a simple pen. Also, on Bezier button, will be drawn only a bezie curve on the static points, not on mouse move.
Pressig on checkboxes with colors, the pen color will change. 

Pressing on button Fill, the figures will be filled with the same chosen color.
It doesn't influence the border. So the border and the inside color will be the same. Is possible o choose between green, red, blue and black.

Default width size is 4. User can change it in the size box and pressing on OK button, new size will be saved. 

A particular feature is function SetROP2(). Using it, the foreground will change the color in its inverse color. In such a way is possible
to visualize the possibilty of changing the color.

Code was implemented in C++...


## Was implemented
### Mandatory Objectives
1. Draw few lines of different colors and weights
2. Draw a Bezier curve
3. Draw few plane objects (ex. circle, square, pie, polygon...) of different colors, weights, filled and not
4. Draw 2 different objects using mouse

### Objectives with points
1. Add a switch (button, select list...) that will change mouse ability to draw objects (2 pt)
