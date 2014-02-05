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
	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}

void draw_circle(Point pC, GLfloat radius) {
	GLfloat step = 1/radius;
	GLfloat x, y;

	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
}

Point pC = {200, 200};
GLint radius = 150;

// radius of the needles from  the center
GLint hRadius = 120;
GLint mRadius = 130;
GLint sRadius = 140;

// angles of the three needles
double hDegree = 0;
double mDegree = 0;
double sDegree = 0;

void display(void) {
	// Terminal Points for Needle
	Point pHour, pMinute, pSecond;

	pHour.y = pC.y + (hRadius * sin(hDegree));
	pHour.x = pC.x + (hRadius * cos(hDegree));

	pMinute.y = pC.y + (mRadius * sin(mDegree));
	pMinute.x = pC.x + (mRadius * cos(mDegree));

	pSecond.y = pC.y + (sRadius * sin(sDegree));
	pSecond.x = pC.x + (sRadius * cos(sDegree));

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
	draw_circle(pC, radius);
	glColor3f(1.0, 0.0, 0.0);
	draw_dda(pC, pHour);

	glColor3f(0.0, 1.0, 0.0);
	draw_dda(pC, pMinute);

	glColor3f(0.0, 0.0, 1.0);
	draw_dda(pC, pSecond);
	glEnd();
	glFlush();

	mDegree -= 0.001333333;
	sDegree -= 0.08;
	hDegree -= 0.0002733333;

}

void Timer(int value) {
	glutTimerFunc(33, Timer, 0);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Square");
	glutDisplayFunc(display);
	init();
	Timer(0);
	glutMainLoop();

	return 0;
}