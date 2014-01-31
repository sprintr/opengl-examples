Explaination of all the functions and what they do in an opengl program.
Wish you best of luck.

-- Amin Ullah Khan
![Good Luck](http://3.bp.blogspot.com/-REDqXibYh9Y/UbuHUvAD8FI/AAAAAAAAA6c/gKJZpqTHgrY/s1600/Good%2BLuck.gif)

[Program Here](https://gist.github.com/beingaminullah/8419228/raw/2d1ea9f9afc50ebe7efe5061988408eb0022d353/OpenGL-Square.cpp)

Include all the headers required.
```cpp
#include <gl/glut.h>
#include <math.h>
```

Define a structure that caries x and y coordinates of a point in 2d plane.
```cpp
struct Point {
	GLint x;
	GLint y;
};
```

This function draws a line from `p1` to `p2`
```cpp
void draw_dda(Point p1, Point p2) {
```

Calculate the change between the two points
```cpp
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;
```

Initial point from which the drawing will be started
```cpp
	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;
```

How much to increment on each iteration
```cpp
	GLfloat step = 0;
```

if |dx| is more than |dy|, then step = |dx|
else step = |dy|
```cpp
	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}
```	

Increments in x and y, which the line is being drawn
```cpp
	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;
```

The loop that will draw the line
```cpp
	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}
```

Initialize OpenGL
```cpp
void init() {
```

Clear the screen with with white, **1.0, 1.0, 1.0** is for white color
```cpp
	glClearColor(1.0, 1.0, 1.0, 0.0);
```

Set the drawing color to black, **0.0, 0.0, 0.0** is for black color
```cpp
	glColor3f(0.0, 0.0, 0.0);
```

The point size is 1 pixel
```cpp
	glPointSize(1.0);
```

Current drawing matrix
```cpp
	glMatrixMode(GL_PROJECTION);
```

Load the identity matrix to draw on
```cpp
	glLoadIdentity();
```

Set drawing canvas 


1. starting x **left**
2. ending x	  **right**
3. starting y **bottom**
4. ending y   **top**

```cpp
	gluOrtho2D(0, 640, 0, 480);
}
```

Function that draws a square
**Point a**: bottom-left vectex of a square
**GLint length**: Length of each side

```cpp
void draw_square(Point a, GLint length) {
```

Point a is provided, the other three will be calculated.
```cpp
	Point b = {a.x + length, a.y},
		c = {b.x,	b.y+length},
		d = {c.x-length, c.y};
```

Draw Points
```cpp
	draw_dda(a, b);
	draw_dda(b, c);
	draw_dda(c, d);
	draw_dda(d, a);	
}
```

Display function will be called by `glutDisplayFunc()`
```cpp
void display(void) {
```

Point p1: The starting bottom-left vertex of the square
```cpp
	Point p1 = {100, 100};
```

Length of each side
```cpp
	GLint length = 100; // size of square
```

Clear the frame buffer
```cpp
	glClear(GL_COLOR_BUFFER_BIT);
```

Tell opengl, we are drawing in points
```cpp
	glBegin(GL_POINTS);
```

Draw your square
```cpp
		draw_square(p1, length);
```
End your drawing
```cpp
	glEnd();
```

Flush the output to the display
```cpp
	glFlush();
}
```

Your `main()` function
```cpp
int main(int argc, char** argv)
{
```

Initialize GLUT (OpenGL Utility Kit)
```cpp
	glutInit(&argc, argv);
```

Set display mode of the output.
We are drawing in black and white so GLUT_SINGLE is ok, we can also draw in RGB using GLUT_RGB
```cpp
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
```

Width and height of the window respectively
```
	glutInitWindowSize(640, 480);
```

Margins of your glut window from left and top respectively
```cpp
	glutInitWindowPosition(200, 200);
```

Create your window with a title
```cpp
	glutCreateWindow("Open GL");
```

Call your `init()` function
```cpp
	init();
```

Provide GLUT your `display()` function
```cpp
	glutDisplayFunc(display);
```

Run a main loop, this acts like `system("pause")` in console application, it doesn't let a program quit.
```cpp
	glutMainLoop();
```

Return 0 as your program output
```cpp
	return 0;
}
```