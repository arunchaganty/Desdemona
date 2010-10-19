#ifndef OTHELLOBOARD_H
#define OTHELLOBOARD_H

/**
 * @brief OthelloBoard Class for the Othello board 
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-01-27
 */

#include <exception>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <list>
using namespace std;

#include "Othello.h"

namespace Desdemona
{
    typedef Turn Coin;

    class OthelloBoard
    {
        static const int BOARD_SIZE = 8;
        /**
         * Function to check if position is within the board
         */
        static bool inline validPosition( int x, int y );

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
         * Checks if a move on the board is valid
         * @param turn Color of piece to be played
         * @param x X coordinate
         * @param y Y coordinate
         */
        bool validateMove( Turn turn, int x, int y ) const;

        /**
         * Checks if a move on the board is valid
         * @param turn Color of piece to be played
         * @param move X,Y coordinates
         */ 
        bool validateMove( Turn turn, Move move ) const;

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
         * Gets all valid moves that can be made by a particular turn
         * @param turn Color of piece to be played
         *
         * @return List of all valid moves
         */
        list<Move> getValidMoves( Turn turn ) const;

        /**
         * Get a count of number of reds
         */
        int getRedCount() const;

        /**
         * Get a count of number of blacks
         */
        int getBlackCount() const;

        /**
         * Prints board on console
         * Can be overridden to replace output format
         * @param turn - Prints out some indicator of whose turn it is
         */
        virtual void print( Turn turn ) const;

        /**
         * Prints board on console
         * Can be overridden to replace output format
         */
        virtual void print() const;

        inline Coin get(int x, int y) const
        {
            return board[x][y];
        }

        private:
        /**
         * Internal storage for the positions
         */
        Coin board[BOARD_SIZE][BOARD_SIZE];
        /**
         * Count of black coins. Present to help player writers
         */
        int blackCount;
        /**
         * Count of red coins. Present to help player writers
         */
        int redCount;

        /**
         * Allow players to inspect the board
         */
        friend class OthelloPlayer;
    };

    class InvalidMoveException: public exception
    {
        public:
        Move move;

        InvalidMoveException( const Move& move ): move(move) 
        {
            if( move == Move::pass() )
            {
                expl = "Invalid Move(pass)";
            }
            else
            {
                char posID[3];
                posID[0] = (char) ('a'+move.x);
                posID[1] = (char) ('0'+move.y);
                posID[2] = '\0';

                expl = "Invalid Move(" + string(posID) + ")";
            }
        }

        ~InvalidMoveException() throw() {}

        const char* what() const throw ()
        {
            return expl.c_str();
        }

        private:
            string expl;
    };
}

#endif /* #ifndef OTHELLOBOARD_H */
