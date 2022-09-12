//
// Created by WILL on 2021/11/14.
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "lighting.h"
#include <vector>

std::vector<lighting> lights = {};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glLoadIdentity();
    gluLookAt(8, 8, 10, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
//    glTranslated(0,0,0);
    glColor3f(0.0f, 1.0f, 1.0f);
    glutSolidSphere(2.0f,10,10);
    glPopMatrix();
    glutSwapBuffers();
}

void init(){
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("light demo");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 500);
    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);

    float pos[3] = {10,10,10};
    lighting temp = lighting(1, pos);
    lights.push_back(temp);
}

void handleReshape(int w, int h) {// no use currently, just copied from tut4
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (GLfloat)w / (GLfloat)h , 1, 500);
    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
//    showMenu();
    glutReshapeFunc(handleReshape);
//    glutKeyboardFunc(kbd);
    glutDisplayFunc(display);
//    glutSpecialFunc(spcialkbd);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    lights[0].draw_light(0);
//    glutTimerFunc(1000 / fps, animation, 0);
    glutMainLoop();
    return 0;
}