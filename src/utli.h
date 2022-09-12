//
// Created by WILL on 2021/11/15.
//

#ifndef INC_3GC3_FINAL_UTLI_H
#define INC_3GC3_FINAL_UTLI_H


class utli {
public:
    static int random_int(int low, int up);
    static float random_float(float low, float up);
    static void init();
    static float* get_color(int color);
private:
    utli();
};


#endif //INC_3GC3_FINAL_UTLI_H
