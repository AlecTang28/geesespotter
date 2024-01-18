#include <iostream>
#include "geesespotter_lib.h"

//FUNCTION 1
char *createBoard(std::size_t xdim, std::size_t ydim)
{
    char *board;
    board = new char[xdim*ydim];

    for(int i = 0; i < (xdim*ydim) - 1; ++i){
        board[i] = 0;
    }

    return board;
}

//FUNCTION 2
void cleanBoard(char *board)
{
    delete[] board;
    board = nullptr;
}    

//FUNCITON 3
void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for(int i=0; i < xdim*ydim; ++i){
    
        //move to new row
        if( (i!= 0) && (i % xdim == 0) ){
            std::cout << std::endl;
        }

        //if a field is marked
        if(board[i] & markedBit() ){
            std::cout << "M";
        }
        //if a field is hidden
        else if(board[i] & hiddenBit() ){
            std::cout << "*";
        }   
        //if a field is revealed
        else{
            std::cout << ( (board[i] << 4) >> 4);
        } 
    }
    std::cout << std::endl;
}

//FUNCTION 4
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{

    for(int i = 0; i < xdim*ydim; ++i){
        if(board[i] == 9){
            
            //top left corner
            if(i == 0){
                //std::cout << "top left"<<std::endl;
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i + xdim + 1] != 9) ++board[i + xdim + 1];
            }

            //top right corner
            else if(i == xdim - 1){
                //std::cout << "top right"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i + xdim - 1] != 9) ++board[i + xdim - 1];
            }

            //bot left corner
            else if(i == xdim*ydim - xdim){
                //std::cout << "bot left"<<std::endl;
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i - xdim + 1] != 9) ++board[i - xdim + 1];
            }

            //bot right corner
            else if(i == xdim*ydim - 1){
                //std::cout << "bot right"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i - xdim - 1] != 9) ++board[i - xdim - 1];
            }

            //top row
            else if(1 <= i && i < xdim - 1){
                //std::cout << "top row"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i + xdim + 1] != 9) ++board[i + xdim + 1];
                if(board[i + xdim - 1] != 9) ++board[i + xdim - 1];
            }

            //bot row
            else if(xdim*ydim - xdim < i && i < xdim*ydim - 1){
                //std::cout << "bot row"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i - xdim + 1] != 9) ++board[i - xdim + 1];
                if(board[i - xdim - 1] != 9) ++board[i - xdim - 1];
            }

            //left column
            else if( i % xdim == 0 && i != 0 && i != xdim*ydim - xdim){
                //std::cout << "left col"<<std::endl;
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i - xdim + 1] != 9) ++board[i - xdim + 1];
                if(board[i + xdim + 1] != 9) ++board[i + xdim + 1];
            }

            //right column
            else if((i+1) % xdim == 0 && i != xdim - 1 && i != xdim*ydim - 1){
                //std::cout << "right col"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i - xdim - 1] != 9) ++board[i - xdim - 1];
                if(board[i + xdim - 1] != 9) ++board[i + xdim - 1];
            }

            else{
                //std::cout << "middle"<<std::endl;
                if(board[i - 1] != 9) ++board[i - 1];
                if(board[i + 1] != 9) ++board[i + 1];
                if(board[i - xdim] != 9) ++board[i - xdim];
                if(board[i + xdim] != 9) ++board[i + xdim];
                if(board[i - xdim + 1] != 9) ++board[i - xdim + 1];
                if(board[i - xdim - 1] != 9) ++board[i - xdim - 1];
                if(board[i + xdim + 1] != 9) ++board[i + xdim + 1];
                if(board[i + xdim - 1] != 9) ++board[i + xdim - 1];
            }

        }
    }
}

//FUNCTION 5
void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    for(int i = 0; i < (xdim*ydim); ++i){
        board[i] ^= hiddenBit();
    }
}

//FUNCTION 6
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    int location = (xdim*yloc) + xloc;
    
    // If the field is marked, the function returns the value 1
    if(board[location] & markedBit() ){
        return 1;
    }

    //if the location is hidden and unmarked
    else if( (board[location] & hiddenBit() ) && (board[location] ^ markedBit() ) ){

        // Reveal a field if it is hidden and unmarked -> Set the hiddenBit to zero
        // hidden  = 1   unmarked = 0
        board[location] &= ~hiddenBit();

        // If there is a goose in the field the function reveals the field and then returns the value 9.
        if( int{board[location] & valueMask()} == 9){
            return 9;
        }
        // For all other cases, the function returns the value 0
        else{

            if(int{board[location] & valueMask()} == 0){

                //top left corner
                if(location == 0){
                    board[1] &= ~hiddenBit();
                    board[xdim] &= ~hiddenBit();
                    board[xdim + 1] &= ~hiddenBit();
                }

                //top right corner
                else if(location == xdim - 1){
                    board[xdim - 2] &= ~hiddenBit();
                    board[(2*xdim) - 1] &= ~hiddenBit();
                    board[(2*xdim) - 2] &= ~hiddenBit();
                }
            
                //bottom left corner
                else if(location == (xdim*ydim) - xdim){
                    board[(xdim*ydim) - xdim + 1] &= ~hiddenBit();
                    board[xdim*(ydim-1) - xdim] &= ~hiddenBit();
                    board[xdim*(ydim-1) - xdim  + 1] &= ~hiddenBit();
                }

                //bottom right corner
                else if(location == (xdim*ydim) - 1){
                    board[xdim*(ydim-1) - 1] &= ~hiddenBit();
                    board[(xdim*ydim) - 2] &= ~hiddenBit();
                    board[xdim*(ydim-1) - 2] &= ~hiddenBit();
                }
                
                //top row
                else if( (1 <= location) && (location < xdim - 1) ){
                    board[location - 1] &= ~hiddenBit();
                    board[location + 1] &= ~hiddenBit();
                    board[location + xdim] &= ~hiddenBit();
                    board[location + xdim - 1] &= ~hiddenBit();
                    board[location + xdim + 1] &= ~hiddenBit();
                }

                //bottom row
                else if( ( (xdim*ydim) - xdim + 1 <= location) && (location < xdim*ydim - 1) ){
                    board[location - 1] &= ~hiddenBit();
                    board[location + 1] &= ~hiddenBit();
                    board[location - xdim] &= ~hiddenBit();
                    board[location - xdim - 1] &= ~hiddenBit();
                    board[location - xdim + 1] &= ~hiddenBit();
                }

                else if( (location != 0) && (location != xdim - 1) && (location != xdim*ydim - xdim) && (location != xdim*ydim - 1) ){
                    
                    //right column
                    if((location+1) % xdim == 0 && location != xdim - 1 && location != xdim*ydim - 1){
                        board[location - xdim] &= ~hiddenBit();
                        board[location + xdim] &= ~hiddenBit();
                        board[location - 1] &= ~hiddenBit();
                        board[location - xdim - 1] &= ~hiddenBit();
                        board[location + xdim - 1] &= ~hiddenBit();
                    }
                    
                    //left column
                    if(location % xdim == 0 && location != 0 && location != xdim*ydim - xdim){
                        board[location - xdim] &= ~hiddenBit();
                        board[location + xdim] &= ~hiddenBit();
                        board[location + 1] &= ~hiddenBit();
                        board[location - xdim + 1] &= ~hiddenBit();
                        board[location + xdim + 1] &= ~hiddenBit();
                    }
                }

                //middle position
                else{
                    board[location + 1] &= ~hiddenBit();
                    board[location - 1] &= ~hiddenBit();
                    board[location - xdim] &= ~hiddenBit();
                    board[location - xdim + 1] &= ~hiddenBit();
                    board[location - xdim - 1] &= ~hiddenBit();
                    board[location + xdim] &= ~hiddenBit();
                    board[location + xdim + 1] &= ~hiddenBit();
                    board[location + xdim - 1] &= ~hiddenBit();
                }
            }
            return 0;
        }
    } 

    // If the field is already revealed, the function returns the value 2
    else{
        return 2;
    }
}

//FUNCTION 7
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    int location = xdim*yloc + xloc;

    if(board[location] & hiddenBit() ){
        board[location] ^= markedBit();
        return 0;
    }
    else{
        return 2;
    }
}

//FUNCTION 8
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    bool isWon{true};
    for(int i = 0; i < xdim*ydim; ++i){
        if( (board[i] & valueMask() ) != 9 && board[i] & hiddenBit() ){
            isWon = false;
            break;
        }
    }
    return isWon;
}