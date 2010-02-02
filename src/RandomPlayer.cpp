/**
 * @file RandomPlayer.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Class for the Othello board 
 */

#include "RandomPlayer.h"
#include <cstdlib>
using namespace Desdemona;

RandomPlayer::RandomPlayer( Turn turn ):
    OthelloPlayer( turn )
{
}

Move RandomPlayer::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    int randNo = rand() % moves.size();
    list<Move>::iterator it = moves.begin();

    for(int i=0; i < randNo; it++, i++);
    return *it;
}

