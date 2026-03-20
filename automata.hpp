#pragma once
#include <vector>
#include <functional>
enum Cell
{
    DEAD,
    ALIVE,
    DYING
};
enum Automata
{
    GAME_OF_LIFE
};
using Board = std::vector<std::vector<Cell>>;
using Rule = std::function<Cell(int, int)>;
class CellularAutomata
{
public:
    Board next;
    Rule apply;
    Board &board;
    bool stop = true;
    int w, h;
    CellularAutomata(Board &board, unsigned int w = 10, unsigned int h = 10) : board(board), w(w), h(h) {}
    void setRule(Automata alg)
    {
        switch (alg)
        {
        case GAME_OF_LIFE:
            apply = [this](int x, int y)
            {
                int live = 0;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int nx = (x + dx + w) % w;
                        int ny = (y + dy + h) % h;
                        if (board[ny][nx] == ALIVE)
                            live++;
                    }
                }
                if (board[y][x] == ALIVE)
                    return (live == 2 || live == 3) ? ALIVE : DEAD;
                else
                    return (live == 3) ? ALIVE : DEAD;
            };
            break;

        default:
            break;
        }
    }
    inline void setStop(bool val) { stop = val; }
    void simulate();
};
