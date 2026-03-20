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
    GAME_OF_LIFE,
    BRIAN,
    SEEDS,
    DAY_AND_NIGHT,
    DIAMOEBA,
    LIFE_WITHOUT_DEATH,
    HIGHLIFE
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
    Cell life(int x, int y);
    Cell brian(int x, int y);
    Cell seeds(int x, int y);
    Cell dayAndNight(int x, int y);
    Cell diamoeba(int x, int y);
    Cell lifeWithoutDeath(int x, int y);
    Cell highlife(int x, int y);
    void setRule(Automata alg)
    {
        switch (alg)
        {
        case GAME_OF_LIFE:
            apply = [this](int x, int y)
            { return life(x, y); };
            break;
        case BRIAN:
            apply = [this](int x, int y)
            { return brian(x, y); };
            break;
        case SEEDS:
            apply = [this](int x, int y)
            { return seeds(x, y); };
            break;
        case DAY_AND_NIGHT:
            apply = [this](int x, int y)
            { return dayAndNight(x, y); };
            break;
        case DIAMOEBA:
            apply = [this](int x, int y)
            { return diamoeba(x, y); };
            break;
        case LIFE_WITHOUT_DEATH:
            apply = [this](int x, int y)
            { return lifeWithoutDeath(x, y); };
            break;
        case HIGHLIFE:
            apply = [this](int x, int y)
            { return highlife(x, y); };
            break;
        default:
            break;
        }
    }
    inline void setStop(bool val) { stop = val; }
    void simulate();
};
