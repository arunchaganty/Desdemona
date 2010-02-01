/**
 * @file OthelloBoard.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Class for the Othello board 
 */

#include "OthelloBoard.h"
#include <iostream>
using namespace Desdemona;
using namespace std;

OthelloBoard::OthelloBoard()
{
    for( int i = 0; i<BOARD_SIZE; i++ )
    {
        for( int j = 0; j<BOARD_SIZE; j++ )
        {
            if( ( i == BOARD_SIZE/2 && j == BOARD_SIZE/2 ) || ( i == BOARD_SIZE/2 -1 && j == BOARD_SIZE/2 -1 ) )
            {
                board[i][j] = BLACK;
            }
            else if( ( i == BOARD_SIZE/2 && j == BOARD_SIZE/2 -1 ) || ( i == BOARD_SIZE/2 -1 && j == BOARD_SIZE/2 ) )
            {
                board[i][j] = RED;
            }
            else
            {
                board[i][j] = EMPTY;
            }
        }
    }
}

OthelloBoard::~OthelloBoard()
{
    // cleanup
}

OthelloBoard::OthelloBoard( const OthelloBoard& other )
{
    for( int i = 0; i<BOARD_SIZE; i++ )
    {
        for( int j = 0; j<BOARD_SIZE; j++ )
        {
            board[i][j] = other.board[i][j];
        }
    }
}

OthelloBoard& OthelloBoard::operator=( const OthelloBoard& other )
{
    if (this != &other){  // no self-assignment
        for( int i = 0; i<BOARD_SIZE; i++ )
        {
            for( int j = 0; j<BOARD_SIZE; j++ )
            {
                board[i][j] = other.board[i][j];
            }
        }
    }
    return *this;
}

void OthelloBoard::makeMove( Turn turn, int x, int y )
{
    //
}

void OthelloBoard::makeMove( Turn turn, Move move )
{
    makeMove( turn, move.x, move.y );
}

void OthelloBoard::print()
{
    for(int j=0;j<19;j++)printf("="); printf("\n");

    printf("| |");
    for (int i=0; i<BOARD_SIZE; i++)
    {
        printf("%d|",i);
    }
    printf("\n");

    for (int i=0; i<BOARD_SIZE; i++)
    {
        printf("|%c|", 'a'+i);
        for (int j=0; j<BOARD_SIZE; j++)
        {
            switch(board[i][j])
            {
                case BLACK:
                    printf("X|");
                    break;
                case EMPTY:
                    printf(" |");
                    break;
                case RED:
                    printf("O|");
                    break;
                default:
                    throw ("Invalid Coin");
            }
        }
        printf("\n");
    }
    for(int j=0;j<19;j++)printf("="); printf("\n");
}


