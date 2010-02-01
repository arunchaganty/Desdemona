#ifndef DUMMYPLAYER_H
#define DUMMYPLAYER_H

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
    class DummyPlayer: public OthelloPlayer
    {
        public:

            /**
             * Default constructor
             */
            DummyPlayer();
            Move play( const OthelloBoard& board );

        private:

    };
}

#endif /* #ifndef DUMMYPLAYER_H */
