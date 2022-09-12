//
// Created by WILL on 2021/11/15.
//

#include "object.h"

#ifndef INC_3GC3_FINAL_PLAYER_H
#define INC_3GC3_FINAL_PLAYER_H


class Player : public Object
{
public:
    Player(float x = 0, float y = 0, float z = 0, int color = 0);
    int hp;
    int speed = 1;
    float dir_y = 1;
    void move();
    void render();
    void jump();
    void apply_grav(float grav);
    void reset();
    void set_color(int in_color);
};


#endif //INC_3GC3_FINAL_PLAYER_H
#pragma once
