#ifndef OTHELLOPLAYER_H
#define OTHELLOPLAYER_H

/**
 * @brief OthelloPlayer Class that defines interface for all bots
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 */

#include "Othello.h"
#include "OthelloBoard.h"

namespace Desdemona
{
    class OthelloPlayer
    {
        public:

            /**
             * Default constructor
             */
            OthelloPlayer();

            virtual Move play( const OthelloBoard& board );

        private:

    };
}

#endif /* #ifndef OTHELLOPLAYER_H */
