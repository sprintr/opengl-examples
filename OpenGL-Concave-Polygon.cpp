#include <iostream>
#include <gl/glut.h>

using namespace std;

struct Point {
	int x;
	int y;
};

//////////////////////////////////////////////////////////////////////////

#define VERTEX_COUNT 5

Point points[VERTEX_COUNT] = {
	100, 350,
	100, 100,
	300, 100,
	150, 200,
	250, 200
};

//////////////////////////////////////////////////////////////////////////

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

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(1.0f);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	Point stPoint = points[0];

	for(int i = 1; i < VERTEX_COUNT; i++) {
		draw_dda(stPoint, points[i]);
		stPoint = points[i];
	}
	draw_dda(stPoint, points[0]);

	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("OpenGL");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}