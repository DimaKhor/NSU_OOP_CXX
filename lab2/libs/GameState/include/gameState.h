#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <fstream>
#include <regex>

struct point
{
    point() = default;
    point(bool p_is_life, int xt, int yt);
    bool point_is_life;
    int x = 0;
    int y = 0;
};

class GameState
{
public:
    GameState(std::string file_name);
    std::string universeName;
    std::string gameRules;
    std::string survivalRules;

    int world_h;
    int world_w;

    std::vector <point> cellsCoordinates;
};

#endif