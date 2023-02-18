#include "gameState.h"

using namespace std;

Point::Point(bool p_is_life, int xt, int yt)
{
    point_is_life = p_is_life;
    x = xt;
    y = yt;
}

GameState::GameState(string file_name)
{
    ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(file_name.c_str());
    if (!fin.is_open())
        exit(1);

    regex universeNameRegex("[#N ]([A-Za-z]*)");
    regex rulesRegex("(#R )(B[0-9]+\/S[0-9]+)");
    regex sizeRegex("[#Size ]([0-9]+) ([0-9]+)");
    regex digits("[0-9]+");
    regex letters("[A-Za-z ]+");
    smatch s;

    char temp[256];

    //Read a name of universe
    fin.getline(temp, 256);
    if (std::regex_search(temp, universeNameRegex))
    {
        this->universeName = temp;
        this->universeName.erase(this->universeName.find("#N "), 3);
    }

    //Read rules of the game
    fin.getline(temp, 256);
    if (std::regex_search(temp, rulesRegex))
    {
        string str(temp);
        auto iter = sregex_iterator(str.begin(), str.end(), digits);
        s = *iter;
        this->gameRules = s.str();
        s = *(++iter);
        this->survivalRules = s.str();
    }

    //Read size of field
    fin.getline(temp, 256);
    if (std::regex_search(temp, sizeRegex))
    {
        std::string str(temp);
        auto iter = sregex_iterator(str.begin(), str.end(), digits);
        s = *iter;
        this->world_w = std::stol(s.str());
        s = *(++iter);
        this->world_h = std::stol(s.str());
    }

    //Read coordinates of cells
    int x, y;
    while (!fin.eof())
    {
        fin >> x >> y;
        this->cellsCoordinates.push_back(Point(true, x, y));
    }

}
