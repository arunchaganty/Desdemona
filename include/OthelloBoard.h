#ifndef OTHELLOBOARD_H
#define OTHELLOBOARD_H

/**
 * @brief OthelloBoard Class for the Othello board 
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-01-27
 */

#include "Othello.h"
#include <exception>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

namespace Desdemona
{
    typedef Turn Coin;

    class OthelloBoard
    {
        static const int BOARD_SIZE = 8;

        public:

        /**
         * Default constructor
         */
        OthelloBoard();

        /**
         * Destructor
         */
        virtual ~OthelloBoard();

        /**
         * Copy constructor
         * @param other Reference on object to copy.
         */
        OthelloBoard( const OthelloBoard& other );

        /** 
         * Assignment operator
         * @param other Reference on object to copy.
         * @return Reference on initialisated object.
         */
        OthelloBoard& operator=( const OthelloBoard& other );

        /**
         * Applies a move on the board
         * @param turn Color of piece to be played
         * @param x X coordinate
         * @param y Y coordinate
         */
        void makeMove( Turn turn, int x, int y );

        /**
         * Applies a move on the board
         * @param turn Color of piece to be played
         * @param move Move data structure
         */
        void makeMove( Turn turn, Move move );

        /**
         * Prints board on console
         * Can be overridden to replace output format
         */
        virtual void print();

        private:
        /**
         * Internal storage for the positions
         */
        Coin board[BOARD_SIZE][BOARD_SIZE];
    };

    class InvalidMoveException: public exception
    {
        static const int MAX_MSG_LEN = 50;
        public:
        Move move;

        InvalidMoveException( const Move& move ): move(move) 
        {
            snprintf( expl, MAX_MSG_LEN, "Invalid Move(%c%d)", ('a'+move.x), move.y );
        }

        const char* what() const throw ()
        {
            return expl;
        }

        private:
            char expl[MAX_MSG_LEN];
    };

}

#endif /* #ifndef OTHELLOBOARD_H */
