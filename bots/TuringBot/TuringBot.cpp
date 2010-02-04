/**
 * @file TuringBot.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * If you were a computer program, a human player acted just like a bot, isn't
 * he/she a bot?
 */

#include <iostream>
using namespace std;

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
using namespace Desdemona;

/**
 * @brief DummyPlayer Class that makes dummy moves
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 */
class HumanPlayer: public OthelloPlayer
{
    public:

        /**
         * Default constructor
         */
        HumanPlayer( Turn turn );
        virtual ~HumanPlayer();
        Move play( const OthelloBoard& board );

    private:

};

HumanPlayer::HumanPlayer( Turn turn ):
    OthelloPlayer( turn )
{
}

Move HumanPlayer::play( const OthelloBoard& board )
{
    string move;
    cin >> move;
    return Move::parse( move );
}

