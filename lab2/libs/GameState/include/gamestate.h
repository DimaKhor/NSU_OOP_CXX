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
    std::string gameRools;
    std::string survivalRools;

    int world_h;
    int world_w;

    std::string fileName;
    std::string universeName;
    std::vector <point> cellsCoordinates;
};

#endif