#include<raylib.h>
#include<iostream>
#include "config.hpp"
#include "grid.hpp"
#include "simulation.hpp"

using namespace std;

using namespace config;

int main(){
    InitWindow(SCREEN_WIDTH , SCREEN_HEIGHT , "Game of life");
    SetTargetFPS(60);
    // Grid grid = Grid(SCREEN_WIDTH , SCREEN_HEIGHT , cell_size);
    Simulation simulation(SCREEN_WIDTH , SCREEN_HEIGHT , cell_size);


    while(!WindowShouldClose()){
        // 1. Event Handling
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 position = GetMousePosition();
            simulation.SetCellValue(position.y / cell_size , position.x / cell_size , 1);
        }
        if (IsKeyPressed(KEY_ENTER)){
            // Start simulation
            simulation.Start();
        }
        if (IsKeyPressed(KEY_BACKSPACE)){
            simulation.Stop();
        }
        if (IsKeyPressed(KEY_UP)){
            simulation.Update_direction(-1 , 0);
        }
        if (IsKeyPressed(KEY_DOWN)){
            simulation.Update_direction(1 , 0);
        }
        if (IsKeyPressed(KEY_RIGHT)){
            simulation.Update_direction(0 , 1);
        }
        if (IsKeyPressed(KEY_LEFT)){
            simulation.Update_direction(0 , -1);
        }
        if (IsKeyPressed(KEY_F)){
            simulation.Fill_Random();
        }
        // 2. Updating State
        simulation.Update();

        // 3. Drawing
        BeginDrawing();
        ClearBackground(grey);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
}