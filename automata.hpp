#pragma once
#include <vector>
#include <functional>
#include <unordered_set>
#include <string>
enum Cell
{
    DEAD,
    ALIVE,
    DYING
};
using Board = std::vector<std::vector<Cell>>;
using Rule = std::function<Cell(int, int)>;
class CellularAutomata
{
public:
    Board next;
    Rule apply;
    Board &board;
    std::unordered_set<int> born;
    std::unordered_set<int> survive;
    std::unordered_set<int> dying;
    bool stop = true;
    int w, h;
    CellularAutomata(Board &board, unsigned int w = 10, unsigned int h = 10) : board(board), w(w), h(h) {}
    bool setRule(char *rule);
    Cell evolve(int x, int y);
    void simulate();
};
