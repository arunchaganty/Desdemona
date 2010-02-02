/**
 * @file OthelloGame.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Simulates the execution of the game
 */
#include <iostream>
#include <fstream>
using namespace std;

#include "OthelloGame.h"
using namespace Desdemona;

OthelloGame::OthelloGame( OthelloPlayer& player1, OthelloPlayer& player2 ) : 
    player1(player1), player2(player2)
{
    turn = BLACK;
}

Turn OthelloGame::getTurn()
{
    return turn;
}

bool OthelloGame::validateMove( const Move& move )
{
    try
    {
        board.makeMove( turn, move );
        return true;
    }
    catch( InvalidMoveException& e )
    {
        return false;
    }
}

void OthelloGame::makeMove( const Move& move )
{
    board.makeMove( turn, move );
}

void OthelloGame::printState()
{
    board.print( turn );
}

void OthelloGame::startGame()
{
    while( !isGameOver() )
    {
        Move move = Move::empty();

        printState();

        if( !board.getValidMoves( turn ).empty() )
        {
            // Make a copy of the board for security purposes
            OthelloBoard boardCopy = board;
            if( turn == BLACK )
            {
                move = player1.play( boardCopy );
            }
            else if( turn == RED )
            {
                move = player2.play( boardCopy );
            }
            makeMove( move );

            // Do any actions
            postPlayActions( move );
        }
        else
        {
            Move passMove = Move::pass();
            postPlayActions( passMove );
        }

        // Change the turn
        turn = other( turn );
    }
}

void OthelloGame::replayGame( string filename )
{
    fstream input( filename.c_str(), fstream::in );
    while( !isGameOver() )
    {
        char x; int y;

        // Read a move from the file
        input >> x >> y;
        makeMove( Move( x - 'a', y ) );
        // Change the turn
        turn = other( turn );
    }
    input.close();
}

bool OthelloGame::isGameOver()
{
    // The game is over when there are no valid moves remaining
    return ( board.getValidMoves( turn ).empty() && board.getValidMoves( other( turn ) ).empty() );
}

void OthelloGame::postPlayActions( Move& move )
{

}

