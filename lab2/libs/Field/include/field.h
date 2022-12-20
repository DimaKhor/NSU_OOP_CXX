#ifndef field_h
#define field_h

#include <string>
#include <iostream>
#include <unistd.h>
#include "gameState.h"

class Field
{
public:
    Field()= default;
    Field(GameState& _game);
    GameState* game;
    ~Field() = default;
    std::vector< std::vector<point> > world;

    void initWorld();
    void nextWorld();
    void printWorld();
    void showRules();
    void saveField(std::string outputFile);
private:
    bool should_be_born(int x);
    bool should_survive(int x);
};

#endif
