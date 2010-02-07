/**
 * @file OthelloGame.cpp
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-02-01
 * Simulates the execution of the game
 */
#include <iostream>
#include <fstream>
#include <cerrno>

#include <time.h>
#include <signal.h>
#include <sys/types.h>
using namespace std;

#include "OthelloGame.h"
using namespace Desdemona;

/**
 * \struct BotEnvironment
 * Store arguments to be passed to thread
 */
struct BotEnvironment
{
    OthelloPlayer& player;
    OthelloBoard& board;
    Move& move;

    BotEnvironment( OthelloPlayer& player, OthelloBoard& board, Move& move ) :
        player( player ), board( board ), move( move ) {}

};

typedef void* (*start_routine) (void *);
static void createEnvironment( BotEnvironment& environ );
static Move launchEnvironment( OthelloPlayer& player, OthelloBoard& board );

OthelloGame::OthelloGame( OthelloPlayer& player1, OthelloPlayer& player2 ) : 
    player1(player1), player2(player2)
{
    turn = BLACK;
}

Turn OthelloGame::getTurn()
{
    return turn;
}

bool OthelloGame::validateMove( const Move& move )
{
    try
    {
        board.makeMove( turn, move );
        return true;
    }
    catch( InvalidMoveException& e )
    {
        return false;
    }
}

void OthelloGame::makeMove( const Move& move )
{
    board.makeMove( turn, move );
}

void OthelloGame::printState()
{
    board.print( turn );
}

void OthelloGame::startGame()
{
    while( !isGameOver() )
    {
        Move move = Move::empty();

        printState();

        if( !board.getValidMoves( turn ).empty() )
        {
            // Make a copy of the board for security purposes
            OthelloBoard boardCopy = board;

            // Spawn a thread to set up an execution environment for the player.
            if( turn == BLACK )
            {
                move = launchEnvironment( player1, boardCopy );
            }
            else if( turn == RED )
            {
                move = launchEnvironment( player2, boardCopy );
            }
            makeMove( move );

            // Do any actions
            postPlayActions( move );
        }
        else
        {
            Move passMove = Move::pass();
            postPlayActions( passMove );
        }

        // Change the turn
        turn = other( turn );
    }
    cout << "Game Over" << endl;
    printState();
}

void OthelloGame::replayGame( string filename )
{
    fstream input( filename.c_str(), fstream::in );
    while( !isGameOver() )
    {
        char x; int y;

        // Read a move from the file
        input >> x >> y;
        makeMove( Move( x - 'a', y ) );
        // Change the turn
        turn = other( turn );
    }
    input.close();
}

bool OthelloGame::isGameOver()
{
    // The game is over when there are no valid moves remaining
    return ( board.getValidMoves( turn ).empty() && board.getValidMoves( other( turn ) ).empty() );
}

void OthelloGame::postPlayActions( Move& move )
{

}

/* Static functions */

/**
* Is a thread cancel function to delete an installed timer
*/
static void timerCleanup( void* arg )
{
    timer_t timerid = (timer_t) arg;
    timer_delete( timerid );
}


/**
* Is called when the player's thread times out
*/
static void killEnvironment( sigval_t val )
{
    pthread_t tid = val.sival_int;
    pthread_cancel( tid );
}

/**
 * Setup environ for player to play.
 * Runs in new thread context
 */
static void createEnvironment( BotEnvironment& environ )
{
    // Setup timers, etc.
    timer_t timerid;
    struct itimerspec its;
    struct sigevent evt;

    // Setup thread to allow it to be cancelled
    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, NULL );
    pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, NULL );

    evt.sigev_notify = SIGEV_THREAD;
    evt.sigev_signo = 0;
    evt.sigev_value.sival_int = pthread_self();
    evt.sigev_notify_function = killEnvironment;
    evt.sigev_notify_attributes = NULL;
    timer_create( _POSIX_THREAD_CPUTIME, &evt, &timerid );

    pthread_cleanup_push( timerCleanup, timerid );

    its.it_value.tv_sec = 2;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime( timerid, 0, &its, NULL );

    environ.move = environ.player.play( environ.board );

    pthread_cleanup_pop( true );
}

/**
 * Setup a thread, and call player.play
 * @param player - Player to play
 */
static Move launchEnvironment( OthelloPlayer& player, OthelloBoard& board )
{
    int s;
    pthread_t t_id;
    pthread_attr_t attr;
    Move move = Move::empty();
    BotEnvironment environ( player, board, move );

    // Setup attributes to catch signals

    pthread_attr_init( &attr );

    s = pthread_create( &t_id, &attr, (start_routine) createEnvironment, &environ ) != 0;
    if( s != 0 )
    {
        errno = s;
        perror("pthread_create");
    }

    pthread_join( t_id, NULL );

    return move;
}

