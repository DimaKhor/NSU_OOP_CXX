#include "field.h"

using namespace std;

Field::Field(GameState& _game)
{
    game = &_game;
}

bool Field::should_be_born(int x)
{
    size_t found = game->gameRules.find(to_string(x));
    if (found != std::string::npos)
        return true;
    else
        return false;
}
bool Field::should_survive(int x)
{
    size_t found = game->survivalRules.find(to_string(x));
    if (found != std::string::npos)
        return true;
    else
        return false;
}

void Field::showRules()
{
    cout << "This universe have these Rules: " << endl;
    cout << "#N " << game->universeName << endl;
    cout << "#R " << "#B" << game->gameRules << "/" << "S" << game->survivalRules << endl;
    cout << "#S " << game->world_w << " " << game->world_h << endl;
    sleep(3);
}

void Field::saveField(string outputFile)
{
    std::ofstream fout(outputFile);
    fout << "#N " << game->universeName << endl;
    fout << "#R " << "#B" << game->gameRules << "/" << "S" << game->survivalRules << endl;
    fout << "#S " << game->world_w << " " << game->world_h << endl;

    for (size_t y = 0; y < game->world_h; y++)
    {
        for (size_t i = 0; i < game->world_w; i++)
        {
            if (world[i][y].point_is_life)
                fout << "* ";
            else
                fout << "  ";
        }
        fout << std::endl;
    }

}

void Field::nextWorld()
{
    vector<point> temp;

    int neighbours = 0, _x, _y, x_, y_; //x and y on top and bottom(left and right for x axis)
    for (int y = 0; y < game->world_h; y++)
    {
        for (int i = 0; i < game->world_w; i++)
        {
            neighbours = 0;
            bool isAlive = world[i][y].point_is_life;

            _x = (i + game->world_w - 1) % game->world_w;
            x_ = (i + game->world_w + 1) % game->world_w;
            _y = (y + game->world_h - 1) % game->world_h;
            y_ = (y + game->world_h + 1) % game->world_h;

            neighbours += world[_x][_y].point_is_life + world[i][_y].point_is_life + world[x_][_y].point_is_life +
                    world[_x][y].point_is_life + world[x_][y].point_is_life +
                    world[_x][y_].point_is_life + world[i][y_].point_is_life + world[x_][y_].point_is_life;

            if (should_be_born(neighbours) && !isAlive)
                temp.push_back(point( true, i, y ));

            if (should_survive(neighbours) && isAlive)
                temp.push_back(point( true, i, y ));

            if (!should_survive(neighbours) && isAlive)
                temp.push_back(point( false, i, y ));

        }
    }
    for (auto& x : temp)
    {
        if (x.point_is_life)
            this->world[x.x][x.y].point_is_life = true;
        else
            this->world[x.x][x.y].point_is_life = false;
    }
    temp.resize(0);
}

void Field::initWorld()
{
    vector<point> temp;
    world.reserve(game->world_h);

    for (size_t y = 0; y < game->world_h; y++)
    {
        temp.resize(0);
        for (size_t i = 0; i < game->world_w; i++)
        {
            point z( 0, 0, 0 );
            temp.push_back(z);
        }
        world.push_back(temp);
    }

    for (auto &x : this->game->cellsCoordinates)
    {
        temp.reserve(game->world_w);
        world[x.x][x.y] = point( true, x.x, x.y );
    }

}

void Field::printWorld()
{
    for (int y = 0; y < game->world_h; y++)
    {
        for (int x = 0; x < game->world_w; x++)
        {
            if (world[x][y].point_is_life)
            {
                cout << "* ";
            }
            else
                cout << "  ";
        }
        cout << endl;
    }
}