#pragma once
#include<vector>
#include<map>
using namespace std;

class Grid{
    public:
        Grid(int width , int height , int cell_size)
            : rows(height/cell_size) , collums(width/cell_size) , cell_size(cell_size) , cells(rows, vector<int> (collums , 0)) 
            , state(rows , vector<int> (collums , 0)) , count_for_dead(rows , vector<int> (collums , 0)){}
        // vector<int> (a , 0) {0 , 0 , 0 ... 0 (a phần tử 0 được khởi tạo vào vector)}
        void Draw();
        bool check(int row , int col);
        void SetValue(int row , int col , int value);
        int GetValue(int row , int col);
        int CountLiveNeighbour(int row , int col);
        bool check_state(int row , int col);
        void Update();
        void Fill_Random();
        void Update_direction(int d_row1 , int d_col1);
        void Count_Dead_Live_neighbour();
        void Update_Live_cells();
        void Reset_Dead_count();

    private:
        int rows;
        int collums;
        int cell_size;
        vector<vector<int>> cells;
        vector<vector<int>> state;
        vector<vector<int>> live_cells;
        vector<vector<int>> visited;
        vector<vector<int>> count_for_dead;
};