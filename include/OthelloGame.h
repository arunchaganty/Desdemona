#ifndef OTHELLOGAME_H
#define OTHELLOGAME_H

/**
 * @brief OthelloGame Stores the current state of a game
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-01-27
 */

#include "OthelloPlayer.h"
#include "Othello.h"
#include <string>
using namespace std;

namespace Desdemona
{
    class OthelloGame
    {
        public:

            /**
             * Start a game with two players
             */
            OthelloGame( OthelloPlayer& player1, OthelloPlayer& player2 );

            Turn getTurn();
            bool validateMove( const Move& move );
            void makeMove( const Move& move );

            void printState();
            void startGame();
            void replayGame( string filename );

        protected:
            OthelloPlayer& player1;
            OthelloPlayer& player2;
            OthelloBoard board;
            Turn turn;

            /**
             * Allows inheriters to define actions that should be performed
             * after a move is played.
             */
            virtual void postPlayActions( Move& move );

            bool isGameOver( );
    };
}

#endif /* #ifndef OTHELLOGAME_H */
