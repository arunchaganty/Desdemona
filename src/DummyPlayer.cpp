/**
 * @file DummyPlayer.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Class for the Othello board 
 */

#include "DummyPlayer.h"
using namespace Desdemona;

DummyPlayer::DummyPlayer()
{
}

Move DummyPlayer::play( const OthelloBoard& board )
{
    return Move::empty();
}

