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

    blackCount = 2;
    redCount = 2;
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

    blackCount = other.blackCount;
    redCount = other.redCount;
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
    blackCount = other.blackCount;
    redCount = other.redCount;

    return *this;
}

bool OthelloBoard::validateMove( Turn turn, int x, int y ) const
{
    // Check if it's a valid position
    if ( !validPosition( x, y ) )
    {
        return false;
    }

    // Ensure that the current box is empty
    if ( !( board[x][y] == EMPTY ) )
    {
        return false;
    }

    // Now scan in all directions to see if there is a sequence of pieces of
    // the opposite color followed by atleast one piece of the same color 
    for( int i = -1; i <= 1; i++ )
    {
        for( int j = -1; j <= 1; j++ )
        {
            // Ignore one case
            if( i == 0 && j == 0 ) continue;

            // Only explore directions which begin with a coin of opposite color
            if  (x+i < BOARD_SIZE && y+j < BOARD_SIZE && board[ x+i ][ y+j ] != other( turn ) ) continue;

            for( int k=1; validPosition( x+k*i, y+k*j ); k++ )
            {
                if( board[ x+k*i ][ y+k*j ] == other( turn ) ) continue;
                else if( board[ x+k*i ][ y+k*j ] == turn )
                {
                    return true;
                }
                else if( board[ x+k*i ][ y+k*j ] == EMPTY )
                {
                    break;
                }
            }
        }
    }

    return false;
}

bool OthelloBoard::validateMove( Turn turn, Move move ) const
{
    return validateMove( turn, move.x, move.y );
}


void OthelloBoard::makeMove( Turn turn, int x, int y )
{
    if ( !validateMove( turn, x, y ) )
    {
        throw InvalidMoveException( Move( x, y ) );
    }

    // Initial count is 1 for the new piece added
    int flippedCoins = 1;
    board[ x ][ y ] = turn;
    // Scan in all directions to see if there is a sequence of pieces of
    // the opposite color followed by atleast one piece of the same color 
    // If there is, flip all such coins.
    for( int i = -1; i <= 1; i++ )
    {
        for( int j = -1; j <= 1; j++ )
        {
            // Ignore one case
            if( i == 0 && j == 0 ) continue;

            // Only explore directions which begin with a coin of opposite color
            if ( x+i < BOARD_SIZE && y+j < BOARD_SIZE && board[ x+i ][ y+j ] != other( turn ) ) continue;

            bool valid = false;
            for( int k=1; validPosition( x+k*i, y+k*j ); k++ )
            {
                if( board[ x+k*i ][ y+k*j ] == other( turn ) ) continue;
                else if( board[ x+k*i ][ y+k*j ] == turn )
                {
                    valid = true;
                    break;
                }
                else if( board[ x+k*i ][ y+k*j ] == EMPTY )
                {
                    break;
                }
            }

            // If a valid move was found, actually flip coins
            if( valid )
            {
                for( int k=1; validPosition( x+k*i, y+k*j ); k++ )
                {
                    if( board[ x+k*i ][ y+k*j ] == other( turn ) )
                    {
                        board[ x+k*i ][ y+k*j ] = turn;
                    }
                    else if( board[ x+k*i ][ y+k*j ] == turn )
                    {
                        valid = true;
                        flippedCoins += (k-1);
                        break;
                    }
                }
            }
        }
    }
    // Update the counts
    blackCount += ( turn == BLACK ) ? flippedCoins : -(flippedCoins-1);
    redCount += ( turn == RED ) ? flippedCoins : -(flippedCoins-1);
}

void OthelloBoard::makeMove( Turn turn, Move move )
{
    makeMove( turn, move.x, move.y );
}

void OthelloBoard::print( Turn turn ) const 
{
    for( int j=0; j<19; j++ ) printf( "=" ); printf( "\n" );

    printf( "|%c|", ( turn == BLACK ) ? 'X' : ( ( turn == RED ) ? 'O' : ' ' ) ); 
    for (int i=0; i<BOARD_SIZE; i++)
    {
        printf( "%d|", i );
    }
    printf( "\n" );

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
    for( int j=0; j<19; j++ ) printf( "=" ); printf( "\n" );
    printf( "Blacks: %02d Reds: %02d\n", blackCount, redCount );
}

void OthelloBoard::print() const 
{
    print( EMPTY );
}

bool inline OthelloBoard::validPosition( int x, int y )
{
    return ( ( x >= 0 ) && ( x < BOARD_SIZE ) && ( y >= 0 ) && ( y < BOARD_SIZE ) );
}

list<Move> OthelloBoard::getValidMoves( Turn turn ) const
{
    list<Move> moves;

    // TODO: Refine to get better performance
    // Brute force approach
    for( int i = 0; i<BOARD_SIZE; i++ )
    {
        for( int j = 0; j<BOARD_SIZE; j++ )
        {
            if( validateMove( turn, i, j ) )
            {
                moves.push_back( Move( i, j ) );
            }
        }
    }

    return moves;
}

int OthelloBoard::getBlackCount() const
{
    return blackCount;
}

int OthelloBoard::getRedCount() const
{
    return redCount;
}

