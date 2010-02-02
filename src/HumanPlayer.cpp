/**
 * @file HumanPlayer.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Class for the Othello board 
 */

#include "HumanPlayer.h"
using namespace Desdemona;

HumanPlayer::HumanPlayer()
{
}

Move HumanPlayer::play( const OthelloBoard& board )
{
    string move;
    cin >> move;
    return Move::parse( move );
}

