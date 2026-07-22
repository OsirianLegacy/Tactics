#include <iostream>
#include <raylib.h>
#include "Game.h"
#include "UI.h"
#include "Options.h"
int main()
{
    Game game;
    InitWindow(VIRTUAL_RESOLUTION.x,VIRTUAL_RESOLUTION.y,"Tactics Game");
    UI ui(game);
    ui.LoadData();
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        ui.Draw();
        EndDrawing();
    }
    return 0;
}