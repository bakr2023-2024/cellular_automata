#include "automata.hpp"
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