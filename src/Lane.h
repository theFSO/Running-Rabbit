//
// Created by WILL on 2021/11/15.
//

#ifndef INC_3GC3_FINAL_LANE_H
#define INC_3GC3_FINAL_LANE_H

#include "object.h"
#include "list"
#include "Obstacle.h"

struct lane_color{
    float start_pos;
    float end_pos;
    int color;
};

class Lane : public Object
{
public:
    Lane(float x, float y = 0, float z = 0, int color = 0);
    void init(int input_width, int amount, float min_length, float max_length, float total_length);
    void render(float player_z);
    bool detect_collision(float positionX, float positionY, int color);

private:
    std::list<lane_color> l_color;
    std::list<Obstacle> obs;
    int width;
    void init_Obstacle(int amount, int total_length);
    void set_width (int input_width);
    void lane_init(float min_length, float max_length, float total_length);
};



#endif //INC_3GC3_FINAL_LANE_H
