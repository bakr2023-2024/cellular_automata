#include "automata.hpp"
#include <iostream>
bool CellularAutomata::setRule(char *rule)
{
    born = {};
    survive = {};
    dying = {};
    std::string str = rule;
    if (str.empty())
        return false;
    int delimIdx = str.find('/');
    std::string bornStr = str.substr(1, delimIdx - 1);
    std::string surviveStr = str.substr(delimIdx + 2);
    for (char c : bornStr)
        born.insert(c - '0');
    for (char c : surviveStr)
        survive.insert(c - '0');
    return true;
};
Cell CellularAutomata::evolve(int x, int y)
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
    int val = board[y][x];
    bool isBorn = val == DEAD && born.count(live);
    bool isSurvive = val == ALIVE && survive.count(live);
    return isBorn || isSurvive ? ALIVE : DEAD;
};
void CellularAutomata::simulate()
{
    if (stop)
        return;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            next[i][j] = evolve(j, i);
        }
    }
    std::swap(board, next);
};