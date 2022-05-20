#ifndef TT_H
#define TT_H

#include <iostream>
#include <map>
#include "../header/state.hpp"
#include "../header/move.hpp"

const unsigned int size = 100;
class TT
{
private:
    std::map<std::string, int, int, Move> Entry;

public:
    TT();
    ~TT();

    void store(State stateGame, int depth, int value, Move move);
    TT lookup(State stateGame);  
};

#endif