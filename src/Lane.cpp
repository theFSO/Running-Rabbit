//
// Created by WILL on 2021/11/15.
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/freeglut.h>
#include <iostream>

#endif

#include "Lane.h"
#include "utli.h"

/**
 * @brief Construct a new Lane object
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param z the z coordinate
 * @param color the color of the lane
 */
Lane::Lane(float x, float y, float z, int color) : Object(x, y, z, color) {
    this->type = LANE;
}

/**
 * @brief Render the lane. We only render lanes that is less than 300 units ahead, or less than 100 units behind
 * 
 * @param player_z the z coordiante of the player
 */
void Lane::render(float player_z) {
    float s_pos; // The start of the lane
    float e_pos; // The end of the lane
    for (auto l:this->l_color){

        if (!(l.end_pos < player_z - 100 || l.start_pos > player_z + 500)){
            if (l.start_pos < player_z - 100) {
                s_pos = player_z - 100;
            }else{
                s_pos = l.start_pos;
            }
            if (l.end_pos > player_z + 500) {
                e_pos = player_z + 500;
            }else{
                e_pos = l.end_pos;
            }
            this->obj_mat = NO;
            apply_obj_mat();
            glBegin(GL_QUADS);
            glNormal3f(0.0f,1.0f,0.0f);
            glTexCoord2f(0,0);
            glVertex3f(this->positionX, 0, e_pos);
            glTexCoord2f(1,0);
            glVertex3f(this->positionX, 0, s_pos);
            glTexCoord2f(1,1);
            glVertex3f(this->positionX - (float) this->width, 0, s_pos);
            glTexCoord2f(0,1);
            glVertex3f(this->positionX - (float) this->width, 0, e_pos);
            glEnd();
        }
    }
    // render obstacles.
    glDisable(GL_TEXTURE_2D);
    for (auto o:this->obs) {
        if (o.positionZ < player_z + 500 && o.positionZ > player_z - 100) {
            o.render_prototype(this->width);
        }
    }
    glEnable(GL_TEXTURE_2D);
}

/**
 * @brief Add obstacles onto the lane
 * 
 * @param amount the number of obstacles on the lane
 * @param total_length the totle length of the lane part on which the obstacles will be set.
 */
void Lane::init_Obstacle(int amount, int total_length) {
    float interval = (float ) total_length / (float ) amount;
    for (int i = 0; i < amount; ++i) {
        float pos_z = utli::random_float(i*interval, (i + 1)*interval);
        Obstacle temp = Obstacle(this->positionX - ((float) this->width / 2), 0, pos_z);// todo static width
        temp.set_color(utli::random_int(4,6));
        this->obs.push_back(temp);
    }
}

/**
 * @brief Set the width of the lane
 * 
 * @param input_width the width of the lane
 */
void Lane::set_width(int input_width) {
    this->width = input_width;
}

/**
 * @brief Initialization of a lane itself
 * 
 * @param min_length the minimal length of a lane
 * @param max_length the maximal length of a lane
 * @param total_length the total length of all the lanes
 */
void Lane::lane_init(float min_length, float max_length, float total_length) {
    float current_pos = 0;
    float random_length;
    while (current_pos < total_length){
        random_length = utli::random_float(min_length, max_length);
        if (current_pos + random_length > total_length){
            random_length = total_length - current_pos;
        }
        lane_color temp{};
        temp.color = utli::random_int(1,3);
        temp.start_pos = current_pos;
        current_pos = current_pos + random_length;
        temp.end_pos = current_pos;
        this->l_color.push_back(temp);
    }
}

/**
 * @brief Initialization of a lane as well as all its features
 * 
 * @param input_width The width of the lane
 * @param amount the amount of obstacles on this lane
 * @param min_length the minimal length of a lane
 * @param max_length the maximal length of a lane
 * @param total_length the total length of all the lanes
 */
void Lane::init(int input_width, int amount, float min_length, float max_length, float total_length) {
    this->set_width(input_width);
    this->init_Obstacle(amount,(int) total_length);
    this->lane_init(min_length, max_length, total_length);
}

/**
 * @brief Detect if the player is collided with an obstacle on this lane
 * 
 * @param position_y the y position of the player
 * @param position_z the z position of the player
 * @param color the color of the player
 * @return true if the player collides with an obstacle
 * @return false if the player does not collodes
 */
bool Lane::detect_collision(float position_y, float position_z, int color) {
    for (auto o : this->obs) {
        if (o.positionZ -2 < position_z && position_z < o.positionZ + 2) {
            if (position_y < o.positionY + 2) {
                if (o.get_color() == 4 && color == 7){
                    continue;
                }
                if (o.get_color() == 5 && color == 8) {
                    continue;
                }
                if (o.get_color() == 6 && color == 9) {
                    continue;
                }
                return true;
            }
        }
    }
    return false;
}
