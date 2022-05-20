
#include "../header/move.hpp"

/*
*   class that represents the movement of a player - functionality methods
*/

// constructors and destructors
Move::Move(){

}

Move::~Move(){

}

Move::Move(unsigned short int x_piece, unsigned short int y_piece, short int x_move, short int y_move){

    this->x_piece = x_piece;
    this->y_piece = y_piece;
    this->x_move = x_move;
    this->y_move = y_move;
}

// getter and setter methods
unsigned short int Move::getXpiece(){
    return this->x_piece;
}

unsigned short int Move::getYpiece(){
    return this->y_piece;
}

short int Move::getXmove(){
    return this->x_move;
}

short int Move::getYmove(){
    return this->y_move;
}