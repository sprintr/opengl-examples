#include <iostream>
#include <cmath>
#include <gl/glut.h>

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
} Color;

typedef struct {
	int   x;
	int   y;
	bool  itouch;
	bool  otouch;
	float angle;
	float radius;
	Color color;
} Point;

float dRadius = 2.10;

Point centerPt = {320, 240};
//  x, y, itouch,otouch, angle, radii, R, G, B
Point points[12] = {
	0, 0,  true, false,   0,   1, 127,   0, 255,
	0, 0, false,  true,  24, 200,  31,   0, 255,
	0, 0,  true, false,  48,   1,   0,  63, 255,
	0, 0, false,  true,  72, 200,   0, 159, 255,
	0, 0,  true, false,  96,   1,   0, 255, 255,
	0, 0, false,  true, 120, 200,   0, 255, 159,
	0, 0,  true, false, 144,   1,   0, 255,  63,
	0, 0, false,  true, 168, 200,  31, 255,   0,
	0, 0,  true, false, 192,   1, 127, 255,   0,
	0, 0, false,  true, 216, 200, 223, 255,   0,
	0, 0,  true, false, 240,   1, 255, 191,   0,
	0, 0, false,  true, 264, 200, 255,  95,   0
};

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPointSize(6.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480);
}

void calc() {
	for(int i = 0; i <= 11; i++) {
		points[i].x = centerPt.x + points[i].radius * cos(points[i].angle);
		points[i].y = centerPt.y + points[i].radius * sin(points[i].angle);

		if(points[i].itouch == true) {
			points[i].radius += dRadius;
		}
		else if(points[i].otouch == true) {
			points[i].radius -= dRadius;
		}

		if(points[i].radius <= 0) {
			points[i].itouch = true;
			points[i].otouch = false;
		}
		else if(points[i].radius >= 200) {
			points[i].otouch = true;
			points[i].itouch = false;
		}
	}
}

void display() {
	calc();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		for(int i = 0; i <= 11; i++) {
			glColor3f(points[i].color.red/255, points[i].color.green/255, points[i].color.blue/255);
			glVertex2i(points[i].x, points[i].y);
		}
	glEnd();
	glFlush();
}

void Timer(int value) {
	glutTimerFunc(10, Timer, 0);
	glutPostRedisplay();
}

void onMouseClick(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		centerPt.x = x;
		centerPt.y = 480 - y;
	}
	return;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutCreateWindow("OpenGL - Animation");
	init();
	Timer(0);
	glutMouseFunc(onMouseClick);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
