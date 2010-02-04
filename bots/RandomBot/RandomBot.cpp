/**
* @file RandomBot.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Bot that randomly chooses a move to play with you
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class RandomBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
         * This could do anything from open up a cache of "best moves" to
         * spawning a background processing thread. 
         */
        RandomBot( Turn turn );
        virtual ~RandomBot() {}

        /**
         * Play something 
         */
        virtual Move play( const OthelloBoard& board );
    private:
};

RandomBot::RandomBot( Turn turn ) :
    OthelloPlayer( turn )
{
}

Move RandomBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    int randNo = rand() % moves.size();
    list<Move>::iterator it = moves.begin();

    for(int i=0; i < randNo; it++, i++);
    return *it;
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new RandomBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}


