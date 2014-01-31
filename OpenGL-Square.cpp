#include <gl/glut.h>
#include <math.h>

struct Point {
	GLint x;
	GLint y;
};

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
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
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

void display(void) {
	Point p1 = {100, 100};
	GLint length = 100; // size of square

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_square(p1, length);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}