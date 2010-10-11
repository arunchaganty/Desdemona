/**
 * @file LoggedOthelloGame.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Simulates the execution of the game
 */
#include <iostream>
#include <fstream>
using namespace std;

#include "LoggedOthelloGame.h"
using namespace Desdemona;

LoggedOthelloGame::LoggedOthelloGame( string logfile, OthelloPlayer& player1, OthelloPlayer& player2 ) : 
    OthelloGame( player1, player2 ), log( logfile.c_str(), fstream::out )
{
}

LoggedOthelloGame::~LoggedOthelloGame()
{
    log.close();
}

void LoggedOthelloGame::postPlayActions( Move& move )
{
    if( move == Move::pass() )
    {
        log << (char) 'p' << 0 << endl;
    }
    else
    {
        log << (char) ('a' + move.x) << move.y << endl;
    }
}

