#include <iostream>
#include <raylib.h>
int main()
{
    InitWindow(800,600,"Tactics Game");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    return 0;
}