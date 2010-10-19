#ifndef OTHELLO_H
#define OTHELLO_H

/**
 * @brief Common Othello primitives
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-01-27
 */

#include <iostream>
#include <cstring>
using namespace std;

namespace Desdemona
{
    enum Mode
    {
        NORMAL=0,
        REPLAY=1,
        TEST=2
    };

    struct Options
    {
        Mode mode;
        bool isVerbose;
        bool shouldStep;
        bool ignoreTime;

        Options()
        {
            mode = NORMAL;
            isVerbose = false;
        }

    };

    enum Coin
    {
        EMPTY,
        BLACK,
        RED
    };

    typedef Coin Turn;
    Turn inline other( Turn& turn )
    {
        switch( turn )
        {
            case BLACK:
                return RED;
            case RED:
                return BLACK;
            default:
                return EMPTY;
        }
    }

    class Move
    {
        public:
            int x;
            int y;

            /**
             * Default constructor
             *
             * @param x - X Coordinate
             * @param y - Y Coordinate
             */
            Move( int x, int y ): x(x), y(y) {}

            /**
             * Equality
             *
             * @param other - 
             */
            bool operator==( const Move other ) const;

            static Move empty()
            {
                return Move( 0, 0 );
            }

            static const Move pass()
            {
                return Move( -1, -1 );
            }

            static Move parse( string moveStr )
            {
                int x;
                int y;

                if( moveStr.length() == 1 && moveStr[0] == 'p' )
                {
                    return Move::pass();
                }
                else if( moveStr.length() == 2 )
                {
                    x = moveStr[0] - 'a';
                    y = moveStr[1] - '0';

                    return Move( x, y );
                }
                else
                {
                    throw exception();
                }
            }

            /**
             * Input from a stream
             *
             * @param inp - Input stream
             * @param move - Move taking input
             */
            friend istream& operator>>( istream& inp, Move& move );

            /**
             * Output to a stream
             *
             * @param out - Output stream
             * @param move - Move to be outputed
             */
            friend ostream& operator<<( ostream& out, const Move& move );
    };

    /**
     * \class MoveCmp
     * Required for maps
     */
    class MoveCmp
    {
        public:
            bool operator()(const Move& move, const Move& move_)
            {
                if (move.x == move_.x)
                    return move.y < move_.y;
                else
                    return move.x < move_.x;
            }
    };
}

#endif /* #ifndef OTHELLO_H */

