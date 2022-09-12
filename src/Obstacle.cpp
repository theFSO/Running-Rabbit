//
// Created by WILL on 2021/11/15.
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/freeglut.h>
#endif

#include "Obstacle.h"
#include "utli.h"
#include "math.h"
Obstacle::Obstacle(float x, float y, float z, int color) : Object(x, y, z, color)
{
    this->type = OBSTACLE;
}

// Obstacle renderer (parent renderer with parameters)

GLfloat cubeVertices[8][3] = {
    { -1, 1, -1 },
    { -1, -1, -1 },
    { 1, -1, -1 },
    { 1, 1, -1 },


    { -1, 1, 1 },
    { -1, -1, 1 },
    { 1, -1, 1 },
    { 1, 1, 1 },
};

unsigned int cubeTriangles[12][3] = {
    // Back face
    { 0, 2, 1 },
    { 0, 3, 2 },

    // Left face
    { 0, 1, 4 },
    { 1, 5, 4 },

    // Front face
    { 4, 5, 6 },
    { 4, 6, 7 },

    // Right face
    { 6, 3, 7 },
    { 2, 3, 6 },

    // Top face
    { 0, 4, 3 },
    { 3, 4, 7 },

    // Bottom face
    { 1, 2, 5 },
    { 2, 6, 5 }
};

// CALCULATE NORMALS AND PUT THEM HERE
GLfloat cubeNormals[6][3] = {
    { 0, 0, -1},
    { -1, 0, 0},
    { 0, 0, 1},
    { 1, 0, 0},
    { 0, 1, 0},
    { 0, -1, 0}
};

void drawCube() {
    glFrontFace(GL_CCW);

    glBegin(GL_TRIANGLES);
    // Render each triangle
    for (int i = 0; i < 12; i++) {
        // Specify the normal for this triangle.
        // We only need six normals since each face of the cube is composed of
        // two triangles.

        /* PUT NORMALS HERE */


        if (i % 2 == 0) {
            glNormal3f(cubeNormals[int(i/2)][0], cubeNormals[int(i/2)][1], cubeNormals[int(i/2)][2]);
        }

        if (i % 2 == 1) {
            glNormal3f(cubeNormals[int((i-1) / 2)][0], cubeNormals[int((i-1) / 2)][1], cubeNormals[int((i-1) / 2)][2]);
        }

        // Render the three vertices of each triangle
        for (int j = 0; j < 3; j++) {
            glVertex3fv(cubeVertices[cubeTriangles[i][j]]);
        }
    }
    glEnd();
}


void Obstacle::render_prototype(int width) {
    glCullFace(GL_BACK);
    glPushMatrix();

    if(this->color == 4){
        this->obj_mat = RUBY;
    }
    if(this->color == 5){
        this->obj_mat = GREEN_RUBBER;
    }
    if(this->color == 6){
        this->obj_mat = BLUE_RUBBER;
    }
    apply_obj_mat();
    glTranslated(this->positionX,(float ) width / 2,this->positionZ);
    glScalef((float)width /2, (float)width /2,(float)width /2);
    drawCube();
    glPopMatrix();
}

void Obstacle::set_color(int color) {
    this->color = color;
}

int Obstacle::get_color() {
    return this->color;
}
