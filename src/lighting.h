//
// Created by WILL on 2021/11/13.
//

#ifndef INC_3GC3_FINAL_LIGHTING_H
#define INC_3GC3_FINAL_LIGHTING_H


class lighting {
    float position[3]{};
    float amb[3]{};
    float dif[3]{};
    float spec[3]{};
    public:
    lighting(int type, float* pos);
    void draw_light(int light_number);
    static void draw_all_light();

};


#endif //INC_3GC3_FINAL_LIGHTING_H
