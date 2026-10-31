#pragma once
#include<raylib.h>

namespace config{
    inline constexpr int SCREEN_WIDTH = 1000;
    inline constexpr int SCREEN_HEIGHT = 1000;
    inline constexpr int cell_size = 25;
    inline Color grey = {29 , 29 , 29 , 255};
    inline Color green = {0 , 255 , 0 , 255};
    inline constexpr int d_row[8] = {-1, 1,  0, 0, -1, -1,  1, 1};
    inline constexpr int d_col[8] = { 0, 0, -1, 1, -1,  1, -1, 1};
    inline int update_state = 0;
}
