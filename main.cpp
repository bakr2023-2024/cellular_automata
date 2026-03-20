#include <raylib.h>
#include <iostream>
#include <format>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "automata.hpp"
float screenWidth = 1280, screenHeight = 720;
Rectangle canvas = {0, 0, screenWidth * 0.8f, screenHeight};
float controlsWidth = screenWidth - canvas.width, controlsHeight = 20;
float controlsOffset = 40;
unsigned int mapWidth = 10;
unsigned int mapHeight = 10;
float cellWidth = canvas.width / mapWidth;
float cellHeight = canvas.height / mapHeight;
float zoom = 1.0f;
Vector2 offset = {0, 0};
Board board = {};
Color liveColor = WHITE, dyingColor = GRAY, deadColor = BLACK;
void renderBoard()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (board[i][j] == DEAD)
                continue;
            Color color = board[i][j] == ALIVE ? liveColor : dyingColor;
            DrawRectangle(offset.x + j * cellWidth * zoom + 1, offset.y + i * cellHeight * zoom + 1, cellWidth * zoom - 1, cellHeight * zoom - 1, color);
        }
    }
}
int main(void)
{
    const char *algs = "Game of Life;Brian's Brain;Seeds;Day and Night;Diamoeba";
    InitWindow(screenWidth, screenHeight, "Cellular Automata");
    int editMapWidth = mapWidth;
    int editMapHeight = mapHeight;
    bool editMapWidthMode = false;
    bool editMapHeightMode = false;
    int algChoice = 0;
    bool editAlgChoiceMode = false;
    float buttonWidth = controlsWidth / 2;
    float buttonXOffset = (controlsWidth - buttonWidth) / 2;
    float pickerSize = controlsWidth / 2;
    SetTargetFPS(60);
    // SetTraceLogLevel(LOG_NONE);
    int yGap = 10;
    CellularAutomata automata{board};
    automata.setRule((Automata)algChoice);
    while (!WindowShouldClose())
    {
        bool boardReady = !board.empty();
        BeginDrawing();
        ClearBackground(deadColor);
        if (boardReady)
        {
            renderBoard();
            if (IsKeyPressed(KEY_I))
                zoom *= 1.1f;
            if (IsKeyPressed(KEY_O))
                zoom *= 0.9f;
            zoom = zoom < 1.0f ? 1.0f : zoom > 10.0f ? 10.0f
                                                     : zoom;
            if (IsKeyPressed(KEY_R))
            {
                offset.x = 0;
                offset.y = 0;
                zoom = 1.0f;
            }
            Vector2 mouse = GetMousePosition();
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(mouse, canvas))
            {
                Vector2 delta = GetMouseDelta();
                offset.x += delta.x;
                offset.y += delta.y;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, canvas))
            {
                int x = (mouse.x - offset.x) / (cellWidth * zoom);
                int y = (mouse.y - offset.y) / (cellHeight * zoom);
                if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
                {
                    int val = board[y][x];
                    board[y][x] = val == ALIVE ? DYING : val == DYING ? DEAD
                                                                      : ALIVE;
                }
            }
        }
        DrawRectangle(canvas.width, 0, screenWidth - controlsWidth, screenHeight, BLACK);
        float y = 0;
        GuiLabel({canvas.width + controlsOffset, y, controlsWidth, controlsHeight}, "Live");
        y += controlsHeight;
        GuiColorPicker({canvas.width + controlsOffset, y, pickerSize, pickerSize}, NULL, &liveColor);
        y += pickerSize + yGap;
        GuiLabel({canvas.width + controlsOffset, y, controlsWidth, controlsHeight}, "Dying");
        y += controlsHeight;
        GuiColorPicker(
            {canvas.width + controlsOffset, y, pickerSize, pickerSize},
            NULL, &dyingColor);
        y += pickerSize + yGap;
        GuiLabel({canvas.width + controlsOffset, y, controlsWidth, controlsHeight}, "Dead");
        y += controlsHeight;
        GuiColorPicker(
            {canvas.width + controlsOffset, y, pickerSize, pickerSize},
            NULL, &deadColor);
        y += pickerSize + yGap;
        if (GuiSpinner({canvas.width + controlsOffset, y, controlsWidth - controlsOffset, controlsHeight}, "Width", &editMapWidth, 5, canvas.width, editMapWidthMode))
            editMapWidthMode = !editMapWidthMode;
        y += controlsHeight;
        if (GuiSpinner({canvas.width + controlsOffset, y, controlsWidth - controlsOffset, controlsHeight}, "Height", &editMapHeight, 5, canvas.height, editMapHeightMode))
            editMapHeightMode = !editMapHeightMode;
        y += controlsHeight;
        if (GuiButton({canvas.width + buttonXOffset, y, buttonWidth, controlsHeight}, "Generate"))
        {
            automata.stop = true;
            mapWidth = editMapWidth;
            mapHeight = editMapHeight;
            board = std::vector{mapHeight, std::vector{mapWidth, DEAD}};
            cellWidth = canvas.width / mapWidth;
            cellHeight = screenHeight / mapHeight;
            automata.w = mapWidth;
            automata.h = mapHeight;
            automata.next = std::vector{mapHeight, std::vector{mapWidth, DEAD}};
        }
        y += controlsHeight;
        if (!boardReady)
            GuiDisable();
        if (editAlgChoiceMode)
            GuiLock();
        if (GuiButton({canvas.width + buttonXOffset, y + controlsHeight, buttonWidth, controlsHeight}, "Start"))
            automata.stop = false;
        y += controlsHeight;
        if (GuiButton({canvas.width + buttonXOffset, y + controlsHeight, buttonWidth, controlsHeight}, "Stop"))
            automata.stop = true;
        y += controlsHeight;
        if (editAlgChoiceMode)
            GuiUnlock();
        if (GuiDropdownBox({canvas.width + controlsOffset, y - 2 * controlsHeight, controlsWidth - controlsOffset, controlsHeight}, algs, &algChoice, editAlgChoiceMode))
            editAlgChoiceMode = !editAlgChoiceMode;
        if (!boardReady)
            GuiEnable();
        if (!automata.stop)
            automata.simulate();
        EndDrawing();
    }
}