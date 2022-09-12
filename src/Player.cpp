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
#include "Player.h"
#include "utli.h"

/**
 * @brief Construct a new Player object
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param z the z coordinate
 * @param color the colour
 */
Player::Player(float x, float y, float z, int color) : Object(x, y, z, color)
{
    this->color = 7;
    this->type = PLAYER;
    this->hp = 3;
}

/**
 * @brief Player renderer
 * 
 */
void Player::render()
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glCullFace(GL_BACK);
    glPushMatrix();
    if(this->color == 7){
        this->obj_mat = RUBY;
    }
    if(this->color == 8){
        this->obj_mat = GREEN_RUBBER;
    }
    if(this->color == 9){
        this->obj_mat = BLUE_RUBBER;
    }
    glDisable(GL_LIGHTING);
    //glColor3fv(utli::get_color(this->color));
    glTranslatef(this->positionX, this->positionY, this->positionZ);
    glRotatef(90, 0, 1, 0);
    //glutWireTeapot(2);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Player::move() {
    this->positionZ += 1;
}

void Player::jump() {
    this->positionY = this->positionY + speed * dir_y;
    if (this->positionY <= 0) {
        this->positionY = 0;
        dir_y = 0;
    }
}

void Player::apply_grav(float grav) {
    dir_y -= grav;
}

void Player::reset() {
    dir_y = 1;
}

void Player::set_color(int in_color) {
    this->color = in_color;
}
