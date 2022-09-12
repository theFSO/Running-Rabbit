//
// Created by WILL on 2021/11/15.
//

#include "utli.h"
#include <cstdlib>
#include <ctime>

const float red_lane[3] {0.7f,0.7f,0.7f};
const float green_lane[3] {0.7f,0.7f,0.7f};
const float blue_lane[3] {0.7f,0.7f,0.7f};
const float red_obs[3] {0.9f, 0.4f, 0.1f};
const float green_obs[3] {0.1f, 1.0f, 0.6f};
const float blue_obs[3] {0.1f, 0.4f, 1.0f};
const float red_player[3] {0.95f, 0.38f, 0.12f};
const float green_player[3] {0.25f, 1.0f, 0.5f};
const float blue_player[3] {0.3f, 0.6f, 0.95f};

int utli::random_int(int low, int up) {
    return low + rand() % (up - low + 1);
}

void utli::init() {
    srand(time(nullptr));
}

float utli::random_float(float low, float up) {
    return static_cast <float> (low + (rand()) / static_cast <float> (RAND_MAX/(up - low)));
}

float *utli::get_color(int color) {
    switch (color) {
        case 1:
            return const_cast<float *>(red_lane);
        case 2:
            return const_cast<float *>(green_lane);
        case 3:
            return const_cast<float *>(blue_lane);
        case 4:
            return const_cast<float *>(red_obs);
        case 5:
            return const_cast<float *>(green_obs);
        case 6:
            return const_cast<float *>(blue_obs);
        case 7:
            return const_cast<float *>(red_player);
        case 8:
            return const_cast<float *>(green_player);
        case 9:
            return const_cast<float *>(blue_player);
        
        default:
            break;
    }

    return nullptr;
}
