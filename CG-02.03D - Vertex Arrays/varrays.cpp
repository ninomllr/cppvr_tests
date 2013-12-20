/////////////////////////////////////////////////////////////////////////////////////////
// Demo: CG-02.03D - Vertex Arrays (Based on OPG Example 02-09) (Ver 1.0)              //
/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif


    //#include <GL/freeglut.h>
    //#include <GL/gl.h>
    //#include <GL/glu.h>

#include "zpr.h"



void setupPointers()
/////////////////////////////////////////////////////////////////////////////////////////
{
	// definition of the cube vertices (X, Y, Z)
	static GLfloat vertices[] =
	{
		-5.0, -5.0, -5.0,
		 5.0, -5.0, -5.0,
		 5.0,  5.0, -5.0,
		-5.0,  5.0, -5.0,
		-5.0, -5.0,  5.0,
		 5.0, -5.0,  5.0,
		 5.0,  5.0,  5.0,
		-5.0,  5.0,  5.0
	};

	// definition of the colors,  each vertex has his own color definition (R, G, B)
	static GLfloat colors[] =
	{
		1.0, 0.2, 0.2,
		1.0, 0.2, 0.2,
		1.0, 0.2, 1.0,
		1.0, 0.2, 1.0,
		1.0, 1.0, 0.2,
		1.0, 1.0, 0.2,
		0.2, 0.2, 1.0,
		0.2, 0.2, 1.0
	};

	// 1st step: enable the desired arrays
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	// 2nd step: setup pointers to the vertices and color vectors
	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glColorPointer (3, GL_FLOAT, 0, colors);
}



void display()
/////////////////////////////////////////////////////////////////////////////////////////
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//* definition of face indices (for GL_QUADS from 0-7)
	static GLubyte indices[] =
	{
		4,5,6,7,
		0,3,2,1,
		1,2,6,5,
		0,4,7,3,
		0,1,5,4,
		2,3,7,6
	};
	//*/
	
	/* definition of face indices (two perpendicular planes)
	static GLubyte indices[] =
	{
		0,4,6,2,
		5,1,3,7
	};
	//*/

	// 3rd step: dereferencing the vertices and draw the geometry
	glDrawElements (GL_QUADS, 24, GL_UNSIGNED_BYTE, &indices[0]);

	glPopMatrix();
	glutSwapBuffers();
}



void initRendering()
/////////////////////////////////////////////////////////////////////////////////////////
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	setupPointers();
}



void resize(int w, int h)
/////////////////////////////////////////////////////////////////////////////////////////
{
	glViewport(0, 0, (GLsizei) w , (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, (GLdouble) w/h, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



void keyboard(unsigned char key, int x, int y)
/////////////////////////////////////////////////////////////////////////////////////////
{
    switch (key)
    {
        case 27:
		{
			exit(0);
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
    glutCreateWindow("Vertex Arrays");
    initRendering();
	zprInit();

	// register callbacks
    glutDisplayFunc(display);
    glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);

    glutMainLoop();
    return 0;
}
