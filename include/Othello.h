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
             * @param player - Coin colour
             * @param x - X Coordinate
             * @param y - Y Coordinate
             */
            Move( int x, int y ): x(x), y(y) {}

            /**
             * Equality
             *
             * @param other - 
             */
            bool operator==( const Move& other );

            static Move empty()
            {
                return Move( 0, 0 );
            }

            static Move parse( string moveStr )
            {
                int x;
                int y;

                if( moveStr.length() != 2 )
                {
                    throw exception();
                }
                x = moveStr[0] - 'a';
                y = moveStr[1] - '0';

                return Move( x, y );
            }

            /**
             * Input from a stream
             *
             * @param inp - Input stream
             */
            friend istream& operator>>( istream& inp, Move& move );

            /**
             * Output to a stream
             *
             * @param out - Output stream
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

