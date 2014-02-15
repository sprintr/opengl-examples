#include <iostream>
#include <gl/glut.h>

using namespace std;

struct Point {
	int x;
	int y;
};

Point p = {280, 190};

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(5.0f);
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

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

void draw_square(Point a, GLint length) {
	Point b = {a.x + length, a.y},
		c = {b.x,	b.y+length},
		d = {c.x-length, c.y};

	draw_dda(a, b);
	draw_dda(b, c);
	draw_dda(c, d);
	draw_dda(d, a);	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_square(p, 100);
	glEnd();
	glFlush();
}

void onKeyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'W': case 'w':
			p.y+=10;
			break;
		case 'A': case 'a':
			p.x-=10;
			break;
		case 'S': case 's':
			p.y-=10;
			break;
		case 'D': case 'd':
			p.x+=10;
			break;
	}

	if(p.x > 640) {
		p.x = 0;
	}
	if(p.x < 0) {
		p.x = 640;
	}
	if(p.y > 480) {
		p.y = 0;
	}
	if(p.y < 0) {
		p.y = 480;
	}

	display();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("OpenGL");
	init();
	glutKeyboardFunc(onKeyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}