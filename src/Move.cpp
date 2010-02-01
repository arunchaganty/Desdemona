/**
* @file Move.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-01
* Defines operators for moves
*/
#include "Move.hpp"

Move::Move( int x, int y )
{
    this->x = x;
    this->y = y;
}

Move::~Move()
{
  // cleanup
}

bool Move::operator==( const Move& other )
{
    return ( this->x == other.x ) && ( this->y == other.y );
}
