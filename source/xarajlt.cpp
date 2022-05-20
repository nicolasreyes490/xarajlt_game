
#include "../header/xarajlt.hpp"

Xarajlt::Xarajlt(){            // constructors and desctructors methods

}

Xarajlt::~Xarajlt(){

}

double Xarajlt::timeCalculate(struct timeval *init_time, struct timeval *end_time)   // measurement time method 
{
    return (double)(init_time->tv_sec + (double)init_time->tv_usec/1000000) -  (double)(end_time->tv_sec + (double)end_time->tv_usec/1000000);
}

void Xarajlt::showIntro(){       // print intro game xarajlt

    std::cout << "\x1B[2J\x1B[H";
    std::cout<<"\n#####################################################\n";
    std::cout<<"#################   Xarajlt Game    #################\n";
    std::cout<<"#####################################################\n";

    std::cout<<"-----------------------------------------------------\n";
    std::cout<<"|  Main Instructions:                               |\n";
    std::cout<<"|---------------------------------------------------|\n";
    std::cout<<"| X: Kids player                                    |\n";
    std::cout<<"| O: Lambs player                                   |\n";
    std::cout<<"| (row column): piece position, for example 4 1     |\n";
    std::cout<<"-----------------------------------------------------\n";
    std::cout<<"\n  Star Xarajlt Game.......\n";
    std::cout<<"=====================================================\n";

}

void Xarajlt::showEndGame(){    // print end game xarajlt

    this->nro_lambs = this->stateGame.getMaxs();
    this->nro_kids = this->stateGame.getMins();
    
    if (this->nro_lambs!=0)
    {
        std::cout << "\x1B[2J\x1B[H";
        std::cout<<"\n#####################################################\n";
        std::cout<<"#################   Lamb Win Game   #################\n";
        std::cout<<"#####################################################\n";
        std::cout<<"-----------------------------------------------------\n";
        std::cout<<"|  Main Statistics:                                 |\n";
        std::cout<<"|---------------------------------------------------|\n";
        std::cout<<"| "<<this->nro_lambs<<": Lamb player                                    |\n";
        std::cout<<"| "<<this->nro_kids<<": Kid player                                     |\n";
        std::cout<<"-----------------------------------------------------\n";
    }
    else{
        if (this->nro_kids!=0)
        {
            std::cout << "\x1B[2J\x1B[H";
            std::cout<<"\n#####################################################\n";
            std::cout<<"#################   Kid Win Game    #################\n";
            std::cout<<"#####################################################\n";
            std::cout<<"-----------------------------------------------------\n";
            std::cout<<"|  Main Statistics:                                 |\n";
            std::cout<<"|---------------------------------------------------|\n";
            std::cout<<"| "<<this->nro_kids<<": Kid player                                     |\n";
            std::cout<<"| "<<this->nro_lambs<<": Lamb player                                    |\n";
            std::cout<<"-----------------------------------------------------\n";
        }
        
    }

    this->stateGame.showBoard();
    
}

int Xarajlt::negamax(State stateGame, unsigned int depth, Move &moveBot){     // negamax method

    if (stateGame.endGame() || depth==0)    // find terminal state or reach the maximum depth
    {
        return stateGame.evalFunctionOp01(stateGame);     // evaluation heuristic function call
        ////return stateGame.evalFunctionOp02(stateGame);
    }

    int bestScore = -1000000000;   // defined minimu score and move instance
    Move bestMove;

    std::vector<Move> validMove = stateGame.queryValidMove();     // query valid o legal move for player (MAX or MIN)

    this->nro_totalnodes = this->nro_totalnodes + validMove.size();   // statistics of negamax calls save
    if (this->max_branching < validMove.size())
    {
       this->max_branching = validMove.size();
    }

    for (unsigned int i = 0; i < validMove.size(); i++)     // test every valid move
    {
        stateGame.performMove(validMove[i]);
        int score = - negamax(stateGame, depth-1, moveBot);    // recursive negamax call with depth = depth -1
        stateGame.revertMove(validMove[i]);
        
        if (score > bestScore)
        {
            bestScore = score;         // replace for current score and move
            bestMove = validMove[i];
        }
                
    }
    
    moveBot = bestMove;    // best move stored in movebot
    return bestScore;
}

int Xarajlt::alphaBeta(State stateGame, unsigned int depth, int alpha, int beta, Move &moveBot){    // alpha beta method

    if (stateGame.endGame() || depth==0)    // find terminal state or reach maximum depth
    {
        return stateGame.evalFunctionOp01(stateGame);        // evaluation heuristic function call
        ////return stateGame.evalFunctionOp02(stateGame);
    }

    int bestScore = -1000000000;     // defined minimum score and move instance
    Move bestMove;

    std::vector<Move> validMove = stateGame.queryValidMove();      // query valid o legal move for player (MAX or MIN)

    this->nro_totalnodes = this->nro_totalnodes + validMove.size();      // statistics info is save
    if (this->max_branching < validMove.size())
    {
        this->max_branching = validMove.size();
    }

    for (unsigned int i = 0; i < validMove.size(); i++)
    {
        stateGame.performMove(validMove[i]);
        int score = - alphaBeta(stateGame, depth-1, (-1)*beta, (-1)*alpha, moveBot);
        stateGame.revertMove(validMove[i]);

        if (score > bestScore)
        {
            bestScore = score;     // replace for current score and move 
            bestMove = validMove[i];
            if (bestScore > alpha)
            {
                alpha = bestScore;
            }
            if (alpha >= beta)   // pruning is done
            {
                this->alfabeta_cuts = this->alfabeta_cuts + 1;
                break;
            }
            
        }
                
    }

    moveBot = bestMove;    // best move is stored in movebot
    return bestScore;
    
}

int Xarajlt::alphaBetaCT(State stateGame, unsigned int depth, int alpha, int beta, Move &moveBot, struct timeval start_time, double time_limit){    // alpha beta method with tiem limit (for iterative deepening)

    struct timeval current_time;          // calculate elapsed tiem, if time limit is most low, evaluate function
    gettimeofday(&current_time, NULL);
    double elapsed_time = this->timeCalculate(&current_time, &start_time)*1000;   // check elapsed time in milisecs

    if (stateGame.endGame() || depth==0 || (elapsed_time >= time_limit))   // find terminal state, depth=0 or time limit is overcome
    {
        return stateGame.evalFunctionOp01(stateGame);          // evaluation heuristic function call
        ////return stateGame.evalFunctionOp02(stateGame);
    }

    int bestScore = -1000000000;    // defined minimum score and move
    Move bestMove;

    std::vector<Move> validMove = stateGame.queryValidMove();     // query valid or legal move (MAX or MIN)

    this->nro_totalnodes = this->nro_totalnodes + validMove.size();   // statistics info is save
    if (this->max_branching < validMove.size())
    {
        this->max_branching = validMove.size();
    }

    for (unsigned int i = 0; i < validMove.size(); i++)
    {
        stateGame.performMove(validMove[i]);
        int score = - alphaBetaCT(stateGame, depth-1, (-1)*beta, (-1)*alpha, moveBot, start_time, time_limit);
        stateGame.revertMove(validMove[i]);

        if (score > bestScore)
        {
            bestScore = score;    // replace current score and move
            bestMove = validMove[i];
            if (bestScore > alpha)
            {
                alpha = bestScore;
            }
            if (alpha >= beta)    // pruning is done
            {
                this->alfabeta_cuts = this->alfabeta_cuts + 1;
                break;
            }
            
        }
                
    }

    moveBot = bestMove;   // best move is stored in movebot
    return bestScore;
    
}

int Xarajlt::iterativeDeepeningST(State stateGame, Move &bestMove){   // iterative deepening (no time limit)

    int score = 0;               // defined score, minimum best score and move
    int bestScore = -1000000000;
    Move moveBot;

    std::cout<<"+-------------------------------------------------------------------------------------------------------+\n";
    std::cout<<"Depth   "<<"Total Nodes     "<<"Max. branch      "<<"Alpba-Beta Cuts\n";

    for (unsigned int depth = 2; depth <= this->maxDepth; depth+=2)    // iterative cycle with different depths
    {
        score = this->alphaBeta(stateGame, depth, this->alpha, this->beta, moveBot);
        if (score >= bestScore)
        {
            bestScore = score;    // replace current score and move
            bestMove = moveBot;
        }

        //this->nro_totalnodes = 0;   // reset statistics info for each iteration
        //this->max_branching = 0;
        
        std::cout<<depth<<"\t"<<this->nro_totalnodes<<"         \t "<<this->max_branching<<"    \t\t"<<this->alfabeta_cuts<<"\n";
        
        this->nro_totalnodes = 0;
        this->alfabeta_cuts = 0;
        this->max_branching = 0;
    }
    std::cout<<"+-------------------------------------------------------------------------------------------------------+\n\n";
    return bestScore;   // return best score
}

int Xarajlt::iterativeDeepeningCT(State stateGame, Move &bestMove){

    int score = 0;              // defined score, minimu score and move
    int bestScore = -1000000000;
    Move moveBot;
    float nodesptime = 0;

    std::cout<<"+-------------------------------------------------------------------------------------------------------+\n";
    std::cout<<"Depth   "<<"Total Nodes     "<<"Max. branch      "<<"Time (milisec)    "<<"Nodes/Time       "<<"Alpba-Beta Cuts\n";

    double time_limit = 500;     // defined time limt, and others structures times
    double elapsed_time = 0;
    struct timeval start_time, current_time;

    gettimeofday(&start_time, NULL);    // measurement start time

    for (unsigned int depth = 2; depth <= this->maxDepth; depth+=2)     // iteratve cycle with different depth
    {
        gettimeofday(&current_time, NULL);                                    // measurement current time 
        elapsed_time = this->timeCalculate(&current_time, &start_time)*1000;   // check time elapsed in milisecs

        if (elapsed_time >= time_limit)             // if time elapsed is most large that time limit, break process
        {
            break;
        }

        score = this->alphaBetaCT(stateGame, depth, this->alpha, this->beta, moveBot, current_time, (time_limit-elapsed_time));
        if (score >= bestScore)
        {
            bestScore = score;    // replace current score and move
            bestMove = moveBot;
        }
        
        //this->nro_totalnodes = 0;  // reset statistics info for each iteration
        //this->max_branching = 0;
        if(elapsed_time!=0){
            nodesptime = this->nro_totalnodes/elapsed_time;
        }
        else{
            nodesptime = this->nro_totalnodes;
        }
        std::cout<<depth<<"\t"<<this->nro_totalnodes<<"        \t "<<this->max_branching<<"         \t  "<<elapsed_time<<"\t\t  "<<nodesptime<<"    \t\t"<<this->alfabeta_cuts<<"\n";
        
        this->nro_totalnodes = 0;
        this->alfabeta_cuts = 0;
        this->max_branching = 0;


    }
    std::cout<<"+-------------------------------------------------------------------------------------------------------+\n\n";
    return bestScore;
}

void Xarajlt::startGame(){

    this->showIntro();              // print intro xarajlt game, move, and trun player
    unsigned short int to_move;
    bool turnLambs = true;
    struct timeval init_time, end_time;

    while (this->stateGame.endGame()==false)    // continue while endgame is false
    {
        if (turnLambs)           // lamb turn (MAX in state)
        {
            this->stateGame.showBoard();       // print board 
            std::vector<Move> validMove = this->stateGame.queryValidMove();   // query valid or legal moves (lamb/MAX)

            for (unsigned short int i = 0; i < validMove.size(); i++)   // print psoible moves for lamb/MAX (in this case human player)
            {
                std::cout<<" > Valid Move: "<<validMove[i].getXpiece()<<", "<<validMove[i].getYpiece()<<" : "<<validMove[i].getXmove()<<", "<<validMove[i].getYmove()<<"\n";
            }

            std::cout<<" > Choose move: ";   // choose move for terminal comand 
            std::cin>>to_move;

            this->stateGame.performMove(validMove[to_move-1]);    // make move for lamb/MAX (human player)
            turnLambs = false;                                  // alternate move
        }
        else{
            this->stateGame.showBoard();    // print board 

            Move moveBot;           // defined movebot and total time for move
            double total_time = 0;

            gettimeofday(&init_time, NULL);    // measurement initial time point

            /*
            *   CHOOSE ALGORITHM: 
            *   
            *       int score = negamax(this->stateGame, this->depth, moveBot);
            *       int score = alphaBeta(this->stateGame, this->depth, this->alpha, this->beta, moveBot);
            *       int score = iterativeDeepeningST(this->stateGame, moveBot);
            *       int score = iterativeDeepeningCT(this->stateGame, moveBot);
            */
            // EDIT: specific algorithm
            int score = alphaBeta(this->stateGame, this->depth, this->alpha, this->beta, moveBot);  // obtain the best move for algorithm 

            gettimeofday(&end_time, NULL);    // measurement end time point

            total_time = this->timeCalculate(&end_time, &init_time)*1000;   // calculate difference total time: init_time and end_time 
            
            this->nro_nodestime = (double)this->nro_totalnodes/total_time;   // calculate (total nodes / time)

            this->stateGame.performMove(moveBot);     //  make move for bot (kid/MIN player)
            turnLambs = true;                           // alternate move
            std::cout<<" Statistics info. "<<"\n";
            std::cout<<"+--------------------------------------+\n";
            std::cout<<" Nro Total Nodes:       "<<this->nro_totalnodes<<"\n";   // print statistics info
            std::cout<<" Max Branching:         "<<this->max_branching<<"\n";
            std::cout<<" Total Time (milisec):  "<<total_time<<"\n";
            std::cout<<" Nodes/Time (nodes/milisec):     "<<this->nro_nodestime<<"\n";
            std::cout<<" Alpha-Beta Cuts:       "<<this->alfabeta_cuts<<"\n";

            this->nro_totalnodes = 0;           // reset statistics info 
            this->max_branching = 0;
            this->alfabeta_cuts = 0;

        }
        std::cout<<"=====================================================\n";
        
    }
    this->showEndGame();
    
}
