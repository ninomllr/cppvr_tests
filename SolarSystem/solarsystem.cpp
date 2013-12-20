/////////////////////////////////////////////////////////////////////////////////////////
// Assignment: CG-02.03A - Solar System (Ver 2.0)                                      //
/////////////////////////////////////////////////////////////////////////////////////////

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

#include "zpr.h"
#include <math.h>       /* sin */

// undefine Microsoft specific keywords
#undef near
#undef far

bool ANIMATION_RUNNING = true;

float SUN_ROTATION = 0.0;
float PLANET1_POSITION = 0.0;
float PLANET1_ROTATION = 0.0;
float MOON1_POSITION = 0.0;
float MOON1_ROTATION = 0.0;
float PLANET2_POSITION = 0.0;
float PLANET2_ROTATION = 0.0;
float PLANET2_ROTATION2 = 0.0;

void checkErrorCode()
/////////////////////////////////////////////////////////////////////////////////////////
{
	GLenum errCode;
	const GLubyte *errString;

	if ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		cout << "OpenGL Error Code: " << errCode << " (" << errString << ")"
				<< endl;
	}
}

void animation(int i) {
	SUN_ROTATION += 0.2;
	PLANET1_POSITION++;
	PLANET1_ROTATION += 0.5;
	PLANET2_POSITION+= 1.2;
	PLANET2_ROTATION += 1;
	PLANET2_ROTATION2 += 0.1;
	MOON1_POSITION+=1.3;
	MOON1_ROTATION+=1.3;

	// reset timer if the animation is running
	if (ANIMATION_RUNNING)
		glutTimerFunc(10, animation, 0);

	glutPostRedisplay();
}

void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// draw sun
	glRotatef(SUN_ROTATION, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(2.0, 30, 20);

	glPopMatrix();
	glPushMatrix();

	// draw planet 1
	glRotatef(PLANET1_POSITION, 0.0, 0.0, 1.0);
	glTranslatef(4.0, 0.0, 0.0);
	glRotatef(PLANET1_ROTATION, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.8, 30, 20);

	// draw moon 1
	glRotatef(MOON1_POSITION, 0.0, 0.0, 1.0);
	glTranslatef(1.4, 0.0, 0.0);
	glRotatef(MOON1_ROTATION, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glutSolidSphere(0.2, 30, 20);

	glPopMatrix();
	glPushMatrix();

	// draw planet 2
	glRotatef(PLANET2_POSITION, 0.0, 0.0, 1.0);
	glTranslatef(6.0, 0.0, sin (PLANET2_POSITION/180));
	glRotatef(PLANET2_ROTATION, 0.0, 0.0, 0.0);
	glColor3f(0.3, 1.0, 1.0);
	glutSolidTeapot(0.5);
	//glutSolidSphere(0.6, 30, 20);

	glPopMatrix();

	glutSwapBuffers();

	checkErrorCode();
}

void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(10, animation, 0);
}

void Menu1(int item)
/////////////////////////////////////////////////////////////////////////////////////////
		{
	switch (item) {
	case 0: {
		exit(0);
		break;
	}
	case 1: {
		glutChangeToMenuEntry(1, "Stop Animation", 2);
		ANIMATION_RUNNING = true;
		break;
	}
	case 2: {
		glutChangeToMenuEntry(1, "Start Animation", 1);
		ANIMATION_RUNNING = false;
		break;
	}
	default: {
		// reset settings
	}
	}
	glutPostRedisplay();
}

void initMenu()
/////////////////////////////////////////////////////////////////////////////////////////
{
	// create menu
	glutCreateMenu(Menu1);
	glutAddMenuEntry("Start Animation", 1);
	glutAddMenuEntry("Exit", 0);

	// attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboard(unsigned char key, int x, int y)
/////////////////////////////////////////////////////////////////////////////////////////
		{
	switch (key) {
	case 27: {
		exit(0);
		break;
	}
	case ' ': {
		if (ANIMATION_RUNNING) {
			Menu1(2);
		} else {
			Menu1(1);
		}
		break;
	}
	}
}

int main(int argc, char *argv[])
/////////////////////////////////////////////////////////////////////////////////////////
		{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");
	initRendering();
	initMenu();
	zprInit();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
