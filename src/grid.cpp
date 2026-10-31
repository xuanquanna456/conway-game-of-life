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

void Grid::Update(){
    for (int i = 0 ; i < rows ;i++){
        for (int j = 0 ; j < collums ; j++){
            state[i][j] = check_state(i , j);
        }
    }

    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            cells[i][j] = state[i][j];
        }
    }
}

void Grid::Fill_Random(){
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < collums ; j++){
            int value = GetRandomValue(0 , 4);
            cells[i][j] = (value == 4) ? 1 : 0;
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