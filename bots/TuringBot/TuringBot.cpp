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
 * @brief TuringBot Human player
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * If you were a computer program, a human player acted just like a bot, isn't
 * he/she a bot?
 */
class TuringBot: public OthelloPlayer
{
    public:

        /**
         * Default constructor
         */
        TuringBot( Turn turn );
        virtual ~TuringBot() {}
        Move play( const OthelloBoard& board );

    private:

};

TuringBot::TuringBot( Turn turn ):
    OthelloPlayer( turn )
{
}

Move TuringBot::play( const OthelloBoard& board )
{
    string move;
    cin >> move;
    return Move::parse( move );
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new TuringBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}


