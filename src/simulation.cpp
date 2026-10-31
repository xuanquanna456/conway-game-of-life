#include "simulation.hpp"

void Simulation::Draw(){
    grid.Draw();
}

void Simulation::SetCellValue(int row , int col , int value){
    grid.SetValue(row , col , value);
}

int Simulation::GetCellValue(int row , int col){
    return grid.GetValue(row , col);
}

int Simulation::countLiveNeighbours(int row , int col){
    return grid.CountLiveNeighbour(row , col);
}

void Simulation::Update(){
    if (is_running) grid.Update();
}

void Simulation::Fill_Random(){
    grid.Fill_Random();
}

void Simulation::Update_direction(int d_row1 , int d_col1){
    grid.Update_direction(d_row1 , d_col1);
}
