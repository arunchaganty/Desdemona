#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

/**
 * @brief DummyPlayer Class that makes dummy moves
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 */

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"

namespace Desdemona
{
    class RandomPlayer: public OthelloPlayer
    {
        public:

            /**
             * Default constructor
             */
            RandomPlayer( Turn turn );
            Move play( const OthelloBoard& board );

        private:

    };
}

#endif /* #ifndef RANDOMPLAYER_H */
