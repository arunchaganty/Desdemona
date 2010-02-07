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
            Turn turn;

            /**
             * Default constructor
             */
            OthelloPlayer( Turn turn );
            
            /**
             * Default destructor
             */
            virtual ~OthelloPlayer( ) {}

            virtual Move play( const OthelloBoard& board );

        private:

    };

    class BotException : public exception
    {
        const char* what() const throw()
        {
            return "Bot threw an unhandled exception.";
        }
    };
}

#endif /* #ifndef OTHELLOPLAYER_H */
