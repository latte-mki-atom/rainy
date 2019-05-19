using namespace std;

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "data.h"

GLuint circle;
GLuint square;
GLuint triangle;
GLfloat c = 0.7;
GLfloat s = 0.7;
GLfloat t = 0.7;
GLfloat c1 = -0.1;
GLfloat s1 = -0.5;
GLfloat t1 = 0.3;
GLfloat v1 = -0.1;
GLfloat v2 = -0.1;
GLfloat v3 = 0.07;

GLvoid BuildList(){
    circle = glGenLists(3);
    square = circle + 1;
    triangle = circle + 2;

    glNewList(circle,GL_COMPILE);
        glColor3f(0.3, 0.4, 0.5);
        glutSolidSphere(0.1,10,10);
    glEndList();

    glNewList(square,GL_COMPILE);
        glColor3f(0.5, 0.4, 0.3);
        glRectf(0.1,0.1,-0.1,-0.1);
    glEndList();

    glNewList(triangle,GL_COMPILE);
        glColor3f(0.1, 0.2, 0.8);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.1f, -0.1f, 0.0f);
            glVertex3f(0.0f, 0.1f, 0.0f);
            glVertex3f(-0.1f, -0.1f, 0.0f);
        glEnd();
    glEndList();
}

static void reshapeScene(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


static void animate()
{

    glutPostRedisplay();
}

static void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.4, 0.3, 0.9);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
        glVertex3d(-0.8,0.8,0);
        glVertex3d(0.8,0.8,0);
        glVertex3d(0.8,-0.8,0);
        glVertex3d(-0.8,-0.8,0);
    glEnd();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslated(s1,s,0);
    s-=0.03;
    s1+=v1;
    glCallList(square);

    glLoadIdentity();

    glTranslated(t1,t,0);
    t-=0.01;
    t1+=v2;
    glCallList(triangle);

    glLoadIdentity();

    glTranslated(c1,c,0);
    c-=0.02;
    c1+=v3;
    glCallList(circle);
    if (s<=-0.7) glDeleteLists(square,1);
    if (c<=-0.7) glDeleteLists(circle,1);
    if (t<=-0.7) glDeleteLists(triangle,1);
    if (s1*s1>=0.49) v1*=-1;
    if (c1*c1>=0.49) v3*=-1;
    if (t1*t1>=0.49) v2*=-1;


    Sleep(100);
    glutSwapBuffers();
}



int main(int argc, char **argv) {
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Figures rain");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeScene);
    glutIdleFunc(animate);
    BuildList();
	glutMainLoop();
	return 0;
}
