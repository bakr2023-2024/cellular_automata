#include "automata.hpp"
Cell CellularAutomata::life(int x, int y)
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
    bool livesOn = board[y][x] == ALIVE && (live == 2 || live == 3);
    bool reproduction = board[y][x] == DEAD && live == 3;
    return livesOn || reproduction ? ALIVE : DEAD;
}

void CellularAutomata::simulate()
{
    if (stop)
        return;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            next[i][j] = apply(j, i);
        }
    }
    std::swap(board, next);
};