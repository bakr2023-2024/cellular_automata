#include <iostream>
#include "raygui.h"
float sw = 1280, sh = 720;
int main(void)
{
    InitWindow(sw, sh, "Cellular Automata");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        EndDrawing();
    }
}