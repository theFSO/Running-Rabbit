//
// Created by WILL on 2021/11/13.
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

const float light_1[3][3] = {{1.0f,1.0f,1.0f}, // amb
                             {0.5f,0.5f,0.5f}, // dif
                             {0.1f,0.1f,0.1f}};// spec

lighting::lighting(int type, float* pos) {// 1 for white light
    this->position[0] = pos[0];
    this->position[1] = pos[1];
    this->position[2] = pos[2];
    switch (type) {
        case 1:
            for (int i = 0; i < 3; i++) {
                this->amb[i] = light_1[0][i];
                this->dif[i] = light_1[1][i];
                this->spec[i] = light_1[2][i];
            }
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}


void lighting::draw_light(int light_number) {
    int target = 0x4000 + light_number;
    if (!glIsEnabled(target)){ glEnable(target);}
    glLightfv(target, GL_POSITION, this->position);
    glLightfv(target, GL_AMBIENT, this->amb);
    glLightfv(target, GL_DIFFUSE, this->dif);
    glLightfv(target, GL_SPECULAR, this->spec);
}


