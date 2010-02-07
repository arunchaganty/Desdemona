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
#include <ctime>
using namespace std;
using namespace Desdemona;

class RandomBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
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
    time_t t;
    time( &t );
    srand( t );
}

Move RandomBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    int randNo = rand() % moves.size();
    list<Move>::iterator it = moves.begin();
    int tmp;

    for( int i = 0; i < 1000000; i++ )
        for( int j = 0; j < 1000; j++ )
            tmp = i + j;

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


