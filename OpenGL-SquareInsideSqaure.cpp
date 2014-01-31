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
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0f);
	gluOrtho2D(0.0, 640, 0.0, 480);
}

void display(void) {
	// Sqaure Coordinates
	Point p1 = {200, 200},
		  p2 = {400, 200},
		  p3 = {400, 400},
		  p4 = {200, 400},

		// Inside diagnol square
		p5 = {200, 300},
		p6 = {300, 200},
		p7 = {400, 300},
		p8 = {300, 400};

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

		// External Square
		draw_dda(p1, p2);
		draw_dda(p2, p3);
		draw_dda(p3, p4);
		draw_dda(p4, p1);

		// Internal Square
		draw_dda(p5, p6);
		draw_dda(p6, p7);
		draw_dda(p7, p8);
		draw_dda(p8, p5);

	glEnd();
	glFlush();

}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Square");
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}