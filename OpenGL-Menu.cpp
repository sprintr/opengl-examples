/*
 * Copyright (c) 2013 Amin Ullah Khan. All rights reserved.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 * Changelog
 * 1.1
 *	- Added support for ellipse
 */

#include <iostream>

#include <gl/glut.h>
#include <math.h>

struct Point {
	GLint x;
	GLint y;
};

struct GLColor {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

GLColor colors[6] = {
	{0.0f, 0.0f, 0.0f},	// Black
	{1.0f, 0.0f, 0.0f},	// Red
	{0.0f, 1.0f, 0.0f}, // Green
	{0.0f, 0.0f, 1.0f}, // Blue
	{1.0f, 1.0f, 0.0f}, // Yellow
	{1.0f, 0.0f, 1.0f}	// Purple
};

GLColor color = colors[0]; // Default: Black

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glColor3f(color.red, color.green, color.blue);
	glPointSize(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void) {

}

void draw_pixel(Point p) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}

void draw_dda(Point p1, Point p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat step = 0;

	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}

	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
	glEnd();
	glFlush();

}

void draw_circle(Point pC, GLfloat radius) {
	GLfloat step = 1/radius;
	GLfloat x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);

	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

void draw_ellipse(Point pC, GLfloat radiusY, GLfloat radiusX) {
	GLfloat step = 1/radiusX;
	GLfloat x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);
		for(GLfloat theta = 0; theta <= 360; theta += step) {
			x = pC.x + (radiusX * cos(theta));
			y = pC.y + (radiusY * sin(theta));
			glVertex2i(x, y);
		}
	glEnd();
	glFlush();
}

void mainMenuHandler(int choice) {
	Point p = {320, 240};	// draw_pixel
	Point p1 = {10, 100};	// draw_line
	Point p2 = {200, 100};	// --

	Point pC = {320, 240};	// Circle center point
	GLfloat radius = 200;	// Circle radius

	switch(choice) {
		case 1:	// Pixel
			draw_pixel(p);
			break;

		case 2:	// Line
			draw_dda(p1, p2);
			break;

		case 3:	// Circle
			draw_circle(pC, radius);
			break;

		case 4: // Ellipse
			draw_ellipse(pC, 60.0f, 200.0f);
			break;

		case 5:	// Exit
			exit(0);
			break;
	}
}

void subMenuHandler(int choice) {
	color = colors[choice];
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL Circle and Menus");
	glutDisplayFunc(display);
	init();

	int subMenu = glutCreateMenu(subMenuHandler);
	glutAddMenuEntry("Default", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Purple", 5);

	glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Change Color", subMenu);
	glutAddMenuEntry("Pixel", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Circle", 3);
	glutAddMenuEntry("Ellipse", 4);
	glutAddMenuEntry("Exit", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
