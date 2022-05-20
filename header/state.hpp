#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../header/move.hpp"

const unsigned short int nRows = 5;             // dimension board and players values
const unsigned short int nCols = 3;
const short int MIN = -1;
const short int MAX = 1;
const short int empty = 0;
const short int move[4][2] = {{-1, 0},{0, 1},{1, 0},{0, -1}};      // reference move (up, right, down, left)

class State
{
private:
    short int board[nRows][nCols];          // board and current player move
    short int to_move;

public:
    State();                // constructor and destructor
    ~State();

    void initState();       // initial state game, shows board and check end game methods
    void showBoard();
    bool endGame();
    std::vector<Move> queryValidMove();     // query and return valid moves in a game state
    void performMove(Move playerMove);      // make a move on the board
    void revertMove(Move playerMove);       // reverses the executed movement
    int evalFunctionOp01(State state);      // game state evaluation function
    int evalFunctionOp02(State state);
    short int getTomove();                  // return current move
    void setTomove(short int to_move);      // set current move
    unsigned short int getMaxs();
    unsigned short int getMins();
};

#endif