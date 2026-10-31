#pragma once
#include "grid.hpp"

class Simulation{
    public:
        Simulation(int width , int height , int cell_size)
        : grid(width , height , cell_size){}
        void Draw();
        void SetCellValue(int row , int col , int value);
        int GetCellValue(int row , int col);
        int countLiveNeighbours(int row , int col);
        void Update();
        void Fill_Random();
        void Update_direction(int d_row1 , int d_col1);
        bool IsRunning() {return is_running;}
        void Start() {is_running = true;}
        void Stop() {is_running = false;}
    private:
        Grid grid;
        bool is_running = false;
};