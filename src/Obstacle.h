//
// Created by WILL on 2021/11/15.
//

#ifndef INC_3GC3_FINAL_OBSTACLE_H
#define INC_3GC3_FINAL_OBSTACLE_H

#include "Object.h"


class Obstacle : public Object
{
public:
    Obstacle(float x = 0, float y = 0, float z = 0, int color = 0);
    void render();
    void set_color(int color);
    int get_color();
    void render_prototype(int width);

private:
    int color;
};


#endif //INC_3GC3_FINAL_OBSTACLE_H
