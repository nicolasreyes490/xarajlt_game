#ifndef MOVE_H
#define MOVE_H

/*
*   class that represents the movement of a player .hpp
*/

class Move
{
private:
    unsigned short int x_piece;              // current position and move
    unsigned short int y_piece;
    short int x_move;
    short int y_move;

public:
    Move();                                 // constructor, destr., getter and setter methods
    ~Move();

    Move(unsigned short int x_piece, unsigned short int y_piece, short int x_move, short int y_move);

    unsigned short int getXpiece();
    unsigned short int getYpiece();
    short int getXmove();
    short int getYmove();
};

#endif