
#include "../header/state.hpp"

State::State(){             //  state game constructors

    this->initState();      
    this->to_move = MAX;   // first move MAX player
}

State::~State(){          // state game destructor

}

short int State::getTomove(){       // return current move
    return this->to_move;
}

void State::setTomove(short int to_move){     // set current move 
    this->to_move = to_move;
}

void State::initState(){                     // game board initialization

    for (unsigned int i = 0; i < nRows; i++)
    {
        for (unsigned int j = 0; j < nCols; j++)
        {
            if (i<2)
            {
                this->board[i][j] = MIN;
            }
            else{
                if (i>=3)
                {
                    this->board[i][j] = MAX;
                }
                else{
                    this->board[i][j] = empty;
                }
                
            }
            
        }
    }

}


void State::showBoard(){             // state board show by terminal with O =MAX y X = MIN

    for (unsigned int i = 0; i < nRows; i++)
    {
        for (unsigned int j = 0; j < nCols; j++)
        {
            if (this->board[i][j]==MAX)
            {
                std::cout<<" O ";
            }
            else{
                if (this->board[i][j]==MIN)
                {
                    std::cout<<" X ";
                }
                else{
                    std::cout<<"   ";
                }
            }
            if(j<(nCols-1)){
                std::cout<<"-";
            }
        }
        std::cout<<"\n";
        if (i<(nRows-1))
        {
            for (unsigned int j = 0; j < nCols; j++)
            {
                std::cout<<" |  ";
            }
            std::cout<<"\n";
        }
        
    }
    
}

std::vector<Move> State::queryValidMove(){            // query and return valid moves of current turn player

    std::vector<Move> validMove;

    for (short int row = 0; row < nRows; row++)
    {
        for (short int col = 0; col < nCols; col++)
        {
            if(this->board[row][col]==MAX && this->to_move==MAX){     // if player position and current turn is of MAX
                for (unsigned int i = 0; i < 4; i++)
                {
                    if ((row + move[i][0]) >= 0 && (row + move[i][0]) < nRows && (col + move[i][1]) >= 0 && (col + move[i][1]) < nCols)   // if it inside the board
                    {
                        if (this->board[row + move[i][0]][col + move[i][1]]==empty && move[i][0]!=1)   // if position move is empty and not down move 
                        {
                            validMove.push_back(Move(row, col, move[i][0], move[i][1]));
                        }
                        else{
                            if ((row + (2*move[i][0])) >= 0 && (row + (2*move[i][0])) < nRows && (col + (2*move[i][1])) >= 0 && (col + (2*move[i][1])) < nCols){    // if not empty position, move two position eliminating rival pieces 
                                if (this->board[row + move[i][0]][col + move[i][1]]==MIN && this->board[row + (2*move[i][0])][col + (2*move[i][1])]==empty)
                                {
                                    validMove.push_back(Move(row, col, (short)(2*move[i][0]), (short)(2*move[i][1])));
                                }
                    
                            }
                        }
            
                    }   
                }
            }
            else
            {
                if (this->board[row][col]==MIN && this->to_move==MIN)    // if player position and current turn is of MIN
                {
                    for (unsigned int i = 0; i < 4; i++)
                    {
                        if ((row - move[i][0]) >= 0 && (row - move[i][0]) < nRows && (col - move[i][1]) >= 0 && (col - move[i][1]) < nCols)    // if it inside the board
                        {
                            if (this->board[row - move[i][0]][col - move[i][1]]==empty && move[i][0]!=1)      // if position move is empty and not down move 
                            {
                                validMove.push_back(Move(row, col, (short)(-1*move[i][0]), (short)(-1*move[i][1])));    
                            }
                            else{
                                if ((row - (2*move[i][0])) >= 0 && (row - (2*move[i][0])) < nRows && (col - (2*move[i][1])) >= 0 && (col - (2*move[i][1])) < nCols){    // if not empty position, move two position eliminating rival pieces 
                                    if (this->board[row - move[i][0]][col - move[i][1]]==MAX && this->board[row-(2*move[i][0])][col - (2*move[i][1])]==empty)
                                    {
                                        validMove.push_back(Move(row, col, (short)(-2*move[i][0]), (short)(-2*move[i][1])));
                                    }
                    
                                }
                            }   

                        }
                    }
                }
                
            }
        }
    }

    return validMove;
    
}

void State::revertMove(Move playerMove){     // revert move by player MAX or MIN

    if (this->to_move==MAX)        //  MAX move
    {
        this->board[(playerMove.getXpiece()) + playerMove.getXmove()][(playerMove.getYpiece()) + playerMove.getYmove()] = empty;   // mark empty
        this->board[playerMove.getXpiece()][playerMove.getYpiece()] = MAX;    // position mark MAX player

        if (playerMove.getXmove()%2==0 && playerMove.getYmove()%2==0)     // if eliminating rival pieces, revert action
        {
            this->board[(playerMove.getXpiece()) + (playerMove.getXmove()/2)][(playerMove.getYpiece()) + (playerMove.getYmove()/2)] = MIN;
        }
        
    }
    else{       // MIN move

        this->board[(playerMove.getXpiece()) + playerMove.getXmove()][(playerMove.getYpiece()) + playerMove.getYmove()] = empty;  // mark empty in position
        this->board[playerMove.getXpiece()][playerMove.getYpiece()] = MIN; 

        if (playerMove.getXmove()%2==0 && playerMove.getYmove()%2==0)    // if eliminating rival pieces, revert action
        {
            this->board[(playerMove.getXpiece()) + (playerMove.getXmove()/2)][(playerMove.getYpiece()) + (playerMove.getYmove()/2)] = MAX;
        }
    }
    
    this->to_move = -1 * this->to_move;     // alternate move MAX-MIN player
}

void State::performMove(Move playerMove){     // make move by player MAX or MIN

    if (this->to_move==MAX)      // MAX move  
    {
        this->board[(playerMove.getXpiece()) + playerMove.getXmove()][(playerMove.getYpiece()) + playerMove.getYmove()] = MAX;    // mark position move with MAX
        this->board[playerMove.getXpiece()][playerMove.getYpiece()] = empty;

        if (playerMove.getXmove()%2==0 || playerMove.getYmove()%2==0)    // in case of eliminating rival pieces
        {
            this->board[(playerMove.getXpiece()) + (playerMove.getXmove()/2)][(playerMove.getYpiece()) + (playerMove.getYmove()/2)] = empty;  // mark empty position rival pieces
        }
        
    }
    else{

        this->board[(playerMove.getXpiece()) + playerMove.getXmove()][(playerMove.getYpiece()) + playerMove.getYmove()] = MIN;   // mark position move with MIN
        this->board[playerMove.getXpiece()][playerMove.getYpiece()] = empty;   

        if (playerMove.getXmove()%2==0 || playerMove.getYmove()%2==0)    // in case of eliminating rival pieces
        {
            this->board[(playerMove.getXpiece()) + (playerMove.getXmove()/2)][(playerMove.getYpiece()) + (playerMove.getYmove()/2)] = empty; // mark empty position rival pieces
        }
        
    }

    this->to_move = -1 * this->to_move;  // alternate move MAX-MIN player
    
}

int State::evalFunctionOp01(State state){   // game state evaluation function

    short int score = 0;
    short int nro_max = 0;
    short int nro_min = 0;
    
    if (state.getTomove()==MAX)               // MAX turn move 
    {
        for (unsigned int i = 0; i < nRows; i++)
        {
            for (unsigned int j = 0; j < nCols; j++)
            {
                if (state.board[i][j]==MAX)
                {
                    nro_max = nro_max + 1;
                }
                else{
                    if (state.board[i][j]==MIN)
                    {
                        nro_min = nro_min + 1;
                    }
                }
            }
        }
        if ((nro_max-nro_min)>0)                     // difference material ** 2
        {
            score = std::pow((nro_max-nro_min),2);     
            
            return score;
        }
        else{
            if ((nro_min-nro_max)>0)
            {
                score = -1 * std::pow((nro_min-nro_max),2);
            
                return score;
            }
            else{
                score = 0;
                return score;
            }
            
        }
    }
    else{
        if (state.getTomove()==MIN)       // MIN turn move
        {
            for (unsigned int i = 0; i < nRows; i++)
            {
                for (unsigned int j = 0; j < nCols; j++)
                {
                    if (state.board[i][j]==MAX)
                    {
                        nro_max = nro_max + 1;
                    }
                    else{
                        if (state.board[i][j]==MIN)
                        {
                            nro_min = nro_min + 1;
                        }
                    }
                }
            }
            if ((nro_max-nro_min)>0)           // difference material ** 2
            {
                score = std::pow((nro_max-nro_min),2);
            
                return score;
            }
            else{
                if ((nro_min-nro_max)>0)
                {
                    score = -1 * std::pow((nro_min-nro_max),2);
                    return score;
                }
                else{
                    score = 0;
                    return score;
                }
            
            }
        }
    }
    return score;
}

int State::evalFunctionOp02(State state){   // game state evaluation function

    short int score = 0;
    short int nro_max = 0;
    short int nro_min = 0;
    short int max_corner = 0;
    short int min_corner = 0;

    if (state.getTomove()==MAX)        // MAX turn move
    {
        for (unsigned int i = 0; i < nRows; i++)     // difference material and corner pieces
        {
            for (unsigned int j = 0; j < nCols; j++)
            {
                if (state.board[i][j]==MAX)
                {
                    nro_max = nro_max + 1;
                    if((i==0 && j==0) || (i==0 && j==(nCols-1)) || (i==(nRows-1) && j==0) || (i==(nRows-1) && j==(nCols-1))){
                        max_corner = max_corner + 1;
                    }
                }
                else{
                    if (state.board[i][j]==MIN)
                    {
                        nro_min = nro_min + 1;
                        if((i==0 && j==0) || (i==0 && j==(nCols-1)) || (i==(nRows-1) && j==0) || (i==(nRows-1) && j==(nCols-1))){
                            min_corner = min_corner + 1;
                        }
                    }
                }
            }
        }
        if ((nro_max-nro_min)>0)     // difference material**2 + corner pieces
        {
            score = std::pow((nro_max-nro_min),2);  
            if((max_corner-min_corner)>0){
                score = score + 1;
            }
            return score;
        }
        else{
            if ((nro_min-nro_max)>0)
            {
                score = -1 * std::pow((nro_min-nro_max),2);
                if((min_corner-max_corner)>0){
                    score = score - 1;
                }
            
                return score;
            }
            else{
                score = 0;
                return score;
            }
            
        }
    }
    else{
        if (state.getTomove()==MIN)              /// game state evaluation function
        {
            for (unsigned int i = 0; i < nRows; i++)       // difference material and corner pieces
            {
                for (unsigned int j = 0; j < nCols; j++)
                {
                    if (state.board[i][j]==MAX)
                    {
                        nro_max = nro_max + 1;
                        if((i==0 && j==0) || (i==0 && j==(nCols-1)) || (i==(nRows-1) && j==0) || (i==(nRows-1) && j==(nCols-1))){
                            max_corner = max_corner + 1;
                        }
                    }
                    else{
                        if (state.board[i][j]==MIN)
                        {
                            nro_min = nro_min + 1;
                            if((i==0 && j==0) || (i==0 && j==(nCols-1)) || (i==(nRows-1) && j==0) || (i==(nRows-1) && j==(nCols-1))){
                                min_corner = min_corner + 1;
                            }
                        }
                    }
                }
            }
            if ((nro_max-nro_min)>0)        // difference material**2 + corner pieces
            {
                score = std::pow((nro_max-nro_min),2);
                if((max_corner-min_corner)>0){
                    score = score + 1;
                }
            
                return score;
            }
            else{
                if ((nro_min-nro_max)>0)
                {
                    score = -1 * std::pow((nro_min-nro_max),2);

                    if((min_corner-max_corner)>0){
                        score = score - 1;
                    }
            
                    return score;
                }
                else{
                    score = 0;
                    return score;
                }
            
            }
        }
    }
    return score;
}

bool State::endGame(){    // check state end game

    unsigned short int nro_maxs = 0;    // number of pieces by player
    unsigned short int nro_mins = 0;

    for (unsigned short int i = 0; i < nRows; i++)    // total pieces count MAX and MIN player
    {
        for (unsigned short int j = 0; j < nCols; j++)
        {
            if (this->board[i][j]==MAX)
            {
                nro_maxs = nro_maxs + 1;
            }
            else{
                if (this->board[i][j]==MIN)
                {
                    nro_mins = nro_mins + 1;
                }
                
            }
            
        }
        
    }

    if (nro_maxs==0 || nro_mins==0)    // If the number of pieces is zero (MAX or MIN), the game ends. 
    {
        return true;
    }
    else{
        return false;
    }
    
}

unsigned short int State::getMaxs(){
    
    unsigned short int nro_max = 0;
    for (unsigned short int i = 0; i < nRows; i++)
    {
        for (unsigned short int j = 0; j < nCols; j++)
        {
            if (this->board[i][j]==MAX)
            {
                nro_max = nro_max + 1;
            }
        }
        
    }
    
    return nro_max;
}

unsigned short int State::getMins(){
    
    unsigned short int nro_min = 0;
    for (unsigned short int i = 0; i < nRows; i++)
    {
        for (unsigned short int j = 0; j < nCols; j++)
        {
            if (this->board[i][j]==MIN)
            {
                nro_min = nro_min + 1;
            }
        }
        
    }
    
    return nro_min;
}
