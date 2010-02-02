/**
 * @file OthelloPlayer.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Class for the Othello board 
 */

#include "OthelloPlayer.h"
using namespace Desdemona;

OthelloPlayer::OthelloPlayer( Turn turn ) :
    turn( turn )
{
}

Move OthelloPlayer::play( const OthelloBoard& board )
{
    return Move::empty();
}

