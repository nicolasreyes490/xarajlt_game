#ifndef XARAJLT_H
#define XARAJLT_H

#include <tuple>
#include <chrono>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "../header/state.hpp"

class Xarajlt
{
private:
    const short int lamb = 1;            // defined values pieces for gmae init, depth, alpha, beta, etc
    const short int kid = -1;
    unsigned short int nro_lambs = 6;
    unsigned short int nro_kids = 6;
    unsigned short int depth = 6;
    const unsigned int maxDepth = 20;
    const int alpha = -1000000000;
    const int beta = 1000000000;    
    State stateGame;                   // state game with board, MAX - MIN values and current move

    unsigned int nro_totalnodes = 0;    // statistics values
    double nro_nodestime = 0;
    float factor_branchave = 0;
    unsigned int max_branching = 0;
    unsigned int alfabeta_cuts = 0;

public:
    Xarajlt();                    // constructors and destructors classs xarajlt
    ~Xarajlt();

    void showIntro();            // methods for print intro, enf game, and start game run 
    void startGame();
    void showEndGame();
    int negamax(State stateGame, unsigned int depth, Move &moveBot);         // negamax method 
    int alphaBeta(State stateGame, unsigned int depth, int alpha, int beta, Move &moveBot);      // alpha beta method (no time limit) 
    int alphaBetaCT(State stateGame, unsigned int depth, int alpha, int beta, Move &moveBot, struct timeval start_time, double time_limit);    // alpha beta method (with time limit)
    int iterativeDeepeningST(State stateGame, Move &bestMove);        // iterative deepening method no time limit (no time limit alpha beta method)
    int iterativeDeepeningCT(State stateGame, Move &bestMove);         // iterative deepening method with time limit (with time limit alpha beta method)
    double timeCalculate(struct timeval *init_time, struct timeval *end_time);     // method to measure execution time
};

#endif
