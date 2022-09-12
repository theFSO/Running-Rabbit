// Standard C++ library imports
#include <stdio.h>
// OpenGL and GLUT imports
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/freeglut.h>
#endif

// Import header file
#include "object.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "utli.h"

/**
 * @brief Generic object constructor (set coordinates)
 * 
 * @param x the x-coordinate
 * @param y the y-coordinate
 * @param z the z-coordinate
 * @param color the color of that object
 */
Object::Object(float x, float y, float z, int color)
{
	this->positionX = x;
	this->positionY = y;
	this->positionZ = z;
	this->color = color;
}

void Object::apply_obj_mat() {
	switch (this->obj_mat)
	{
	case BLUE_RUBBER:
		setAmb(0.0f,0.05f,0.0f,1.0f);
		setDiff(0.4f,0.5f,0.4f,1.0f);
		setSpec(0.04f,0.7f,0.7f,1.0f);
		setShin(10.0f);
		break;
	case BRASS:
		setAmb(0.329412f, 0.223529f, 0.027451f, 1.0f);
		setDiff(0.780392f, 0.568627f, 0.113725f, 1.0f);
		setSpec(0.992157f, 0.941176f, 0.807843f, 1.0f);
		setShin(27.8974f);
		break;
	case BRONZE:
		setAmb(0.25f, 0.148f, 0.06475f, 1.0f);
		setDiff(0.4f, 0.2368f, 0.1036f, 1.0f);
		setSpec(0.774597f, 0.458561f, 0.200621f, 1.0f);
		setShin(76.8f);
		break;
	case GOLD:
		setAmb(0.24725f, 0.1995f, 0.0745f, 1.0f);
		setDiff(0.75164f, 0.60648f, 0.22648f, 1.0f);
		setSpec(0.628281f, 0.555802f, 0.366065f, 1.0f);
		setShin(51.2f);
		break;
	case COPPER:
		setAmb(0.2295f, 0.08825f, 0.0275f, 1.0f);
		setDiff(0.5508f, 0.2118f, 0.066f, 1.0f);
		setSpec(0.580594f, 0.223257f, 0.0695701f, 1.0f);
		setShin(51.2f);
		break;
	case CYAN_PLASTIC:
		setAmb(0.0f, 0.1f, 0.06f, 1.0f);
		setDiff(0.0f, 0.50980392f, 0.50980392f, 1.0f);
		setSpec(0.50196078f, 0.50196078f, 0.50196078f, 1.0f);
		setShin(32.0f);
		break;
	case RUBY:
		setAmb(0.05f,0.0f,0.0f,1.0f);
		setDiff(0.5f,0.4f,0.4f,1.0f);
		setSpec(0.7f,0.04f,0.04f,1.0f);
		setShin(10.0f);
		break;
	case GREEN_RUBBER:
		setAmb(0.0f,0.05f,0.0f,1.0f);
		setDiff(0.4f,0.5f,0.4f,1.0f);
		setSpec(0.04f,0.7f,0.04f,1.0f);
		setShin(10.0f);
		break;
    case NO:
        setAmb(1.0f,1.0f,1.0f,1.0f);
        setDiff(1.0f,1.0f,1.0f,1.0f);
        setSpec(1.0f,1.0f,1.0f,1.0f);
        setShin(10.0f);
	default:
		break;
	}
}

void Object::setAmb(float x, float y, float z, float a) {
	float mat_ambient[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);

}

void Object::setDiff(float x, float y, float z, float a) {
	float mat_diffuse[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_diffuse);

}

void Object::setSpec(float x, float y, float z, float a) {
	float mat_specular[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_specular);

}

void Object::setShin(float s)
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);
}

/**
 * @brief Generic object renderer (obj loader logic)
 * 
 */
void Object::obj_render(int counter) {
    this->obj_mat = NO;
    // TODO: implement render method
    apply_obj_mat();
	glPushMatrix();
    glTranslatef(this->positionX, this->positionY, this->positionZ);
    glPushMatrix();
    glScalef(0.25f,0.25f,0.25f);
	glColor3fv(utli::get_color(this->color));
    switch (counter) {
        case 0:
        case 4:
            glCallList(this->list1);
            break;
        case 1:
        case 3:
            glCallList(this->list2);
            break;
        case 2:
            glCallList(this->list3);
            break;
        default:
            break;
    }
	glPopMatrix();
    glPopMatrix();
}

/**
 * @brief Load the mesh of an object
 * 
 * @param path The path of the mash file
 * @return true if the mesh loads successfully
 * @return false if an error occurs.
 */
bool Object::load_obj(const char *path, int list) {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream in;
    in.open(path);
    while (in.peek() != EOF) {
        std::getline(in, line);
        lines.push_back(line);
    }
    in.close();
    float a, b, c;
    for (std::string &line : lines) {
        if (line[0] == 'v') {
            if (line[1] == ' ') {
                sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
                this->veI.push_back(new float[3]{a, b, c});
            } else if (line[1] == 't') {
                sscanf(line.c_str(), "vt %f %f", &a, &b);
                this->uvI.push_back(new float[2]{a, b});
            } else if (line[1] == 'n') {
                sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                this->noI.push_back(new float[3]{a, b, c});
            }
        } else if (line[0] == 'f') {
            int v0, v1, v2, v3, t0, t1, t2, t3, n;
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n, &v3, &t3, &n);
            int *v = new int[4]{v0 - 1, v1 - 1, v2 - 1, v3 - 1};
            int *t = new int[4]{t0 - 1, t1 - 1, t2 - 1, t3 - 1};
            this->faces.push_back(Face(4, v, t, n - 1));
        }
    }
    switch (list) {
        case 1:
            this->list1 = glGenLists(1);
            glNewList(list1, GL_COMPILE);
            break;
        case 2:
            this->list2 = glGenLists(1);
            glNewList(list2, GL_COMPILE);
            break;
        case 3:
            this->list3 = glGenLists(1);
            glNewList(list3, GL_COMPILE);
            break;
        default:
            break;

    }
    for (Face &face : this->faces) {
        if (face.normal != -1)
            glNormal3fv(this->noI[face.normal]);
        else
            glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        for (int i = 0; i < face.edge; i++){
            glVertex3fv(this->veI[face.vertices[i]]);
            glTexCoord2fv(this->uvI[face.texcoords[i]]);
        }
        glEnd();
        if (face.normal == -1)
            glEnable(GL_LIGHTING);
    }
    glEndList();
    for (float *f : this->veI)
        delete f;
    this->veI.clear();
    for (float *f : this->uvI)
        delete f;
    this->uvI.clear();
    for (float *f : this->noI)
        delete f;
    this->noI.clear();
    faces.clear();
    return true;
}





// Obstacle constructor (parent constructor, rocket type identifier)


