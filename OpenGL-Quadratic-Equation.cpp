#include <gl/glut.h>

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 480, 0, 640);
	glViewport(10, 10, 620, 460);
}

void display() {
	GLfloat a = 3;
	GLfloat b = 8;
	GLfloat c = 8;
	GLfloat midY = 240;
	GLfloat midX = 320;
	GLfloat y = 0;
	GLfloat x = 0;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		for(GLfloat x = -10; x <= 10; x+=0.01) {
			y = midY + a*(x*x)+(b*x)+c;
			glVertex2f(midX + x, y);
		}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 400);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Quadratic Formula");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
