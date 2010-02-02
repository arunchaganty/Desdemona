#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

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
    class HumanPlayer: public OthelloPlayer
    {
        public:

            /**
             * Default constructor
             */
            HumanPlayer();
            Move play( const OthelloBoard& board );

        private:

    };
}

#endif /* #ifndef HUMANPLAYER_H */
