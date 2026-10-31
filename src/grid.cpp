#include<raylib.h>
#include "grid.hpp"
#include "config.hpp"
#include<iostream>

using namespace config;
using namespace std;

void Grid::Draw()
{
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            // cout << cells[i][j] << '\n';
            Color color = (cells[i][j] == 1) ? Color{0 , 255 , 0 , 255} : Color{55 , 55 , 55 , 255};
            DrawRectangle(j * cell_size , i * cell_size , cell_size - 1 , cell_size - 1 , color);
        }
    }
}
bool Grid::check(int row , int col){
    return (row >= 0 && row < rows && col >= 0 && col < collums);
}

void Grid::SetValue(int row , int col , int value)
{
    if (check(row , col)){
        cells[row][col] = value;
    }

}

int Grid::GetValue(int row , int col){
    if (check(row , col)){
        return cells[row][col];
    }
    return 0;
}

int Grid::CountLiveNeighbour(int row , int col){
    int count = 0;
    for (int i = 0 ; i < 8 ; i++){
        int new_row = (row + d_row[i] + rows) % rows;
        int new_col = (col + d_col[i] + collums) % collums;
        count += GetValue(new_row , new_col);
    }
    return count;
}
bool Grid::check_state(int row , int col){
    int LiveNeighbour = CountLiveNeighbour(row , col);
    if (cells[row][col] == 1){
        return (LiveNeighbour == 2 || LiveNeighbour == 3);
    }
    else{
        return (LiveNeighbour == 3);
    }
    return 0;
}
void Grid::Update_Live_cells(){
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            if (cells[i][j] == 1) live_cells.push_back({i , j});
        }
    }
}
void Grid::Count_Dead_Live_neighbour(){
    for (auto i : live_cells){
        int row = i[0];
        int col = i[1];
        for (int dir = 0 ; dir < 8 ; dir++){
            int new_row = (row + d_row[dir] + rows) % rows;
            int new_col = (col + d_col[dir] + collums) % collums;
            if (GetValue(new_row , new_col) == 0){
              count_for_dead[new_row][new_col]++;  
            }
        }
    }
}
void Grid::Reset_Dead_count(){
    for (auto i : live_cells){
        int row = i[0];
        int col = i[1];
        for (int dir = 0 ; dir < 8 ; dir++){
            int new_row = (row + d_row[dir] + rows) % rows;
            int new_col = (col + d_col[dir] + collums) % collums;
            if (GetValue(new_row , new_col) == 0){
                // cout << count_for_dead[new_row][new_col] << '\n';
                count_for_dead[new_row][new_col] = 0;
            }
        }
    }
}

void Grid::Update(){
    Update_Live_cells();
    Count_Dead_Live_neighbour();
    visited.assign(rows , vector<int> (collums , 0));
    state.assign(rows , vector<int> (collums , 0));

    for (int i = live_cells.size() - 1 ; i >= 0 ; i--){
        int row = live_cells[i][0];
        int col = live_cells[i][1];
        for (int dir = 0 ; dir < 8 ; dir++){
            int new_row = (row + d_row[dir] + rows) % rows;
            int new_col = (col + d_col[dir] + collums) % collums;
            if (GetValue(new_row , new_col) == 0 && visited[new_row][new_col] == 0){
                if (count_for_dead[new_row][new_col] == 3){
                    state[new_row][new_col] = 1;
                    visited[new_row][new_col] = 1;
                }
                else{
                    state[new_row][new_col] = 0;
                }
            }
        }

        if (CountLiveNeighbour(row , col) == 2 || CountLiveNeighbour(row , col) == 3){
            state[row][col] = 1;
        }
        else{
            state[row][col] = 0;
        }


    }

    count_for_dead.assign(rows , vector<int> (collums , 0));

    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            cells[i][j] = state[i][j];
        }
    }

    live_cells.clear();
}

void Grid::Fill_Random(){
    if (!live_cells.empty()) live_cells.clear();
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            int value = (GetRandomValue(0 , 4) == 4) ? 1 : 0;
            cells[i][j] = value;
        }
    }
}

void Grid::Update_direction(int d_row1 , int d_col1){
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            int new_row = (i + d_row1 + rows) % rows;
            int new_col = (j + d_col1 + collums) % collums;
            state[new_row][new_col] = cells[i][j];
        }
    }

    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            cells[i][j] = state[i][j];
        }
    }
}