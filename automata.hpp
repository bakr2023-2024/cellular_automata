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
    }
    inline void setStop(bool val) { stop = val; }
    void simulate();
};
