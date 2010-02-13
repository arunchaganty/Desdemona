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

// TODO: Make this defined in a config file somewhere
#define BOT_TIMEOUT 2

enum ExceptionFlags
{
    EFLAGS_NONE,
    EFLAGS_TIMEOUT=0x1,
    EFLAGS_UNHANDLED=0x2
};
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

Turn OthelloGame::startGame()
{
    printState();

    do
    {
        Move move = Move::empty();

        if( !board.getValidMoves( turn ).empty() )
        {
            // Make a copy of the board for security purposes
            OthelloBoard boardCopy = board;

            // Spawn a thread to set up an execution environment for the player.
            try
            {
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
            catch( InvalidMoveException& e )
            {
                OthelloPlayer& player = (turn == BLACK) ? player1 : player2;
                throw BotInvalidMoveException( player, e.move );
            }
        }
        else
        {
            Move passMove = Move::pass();
            postPlayActions( passMove );
        }

        // Change the turn
        turn = other( turn );
        printState();
    } while( !isGameOver() );

    cout << "Game Over" << endl;

    if( board.getRedCount() > board.getBlackCount() )
    {
        return RED;
    }
    else if( board.getRedCount() < board.getBlackCount() )
    {
        return BLACK;
    }
    else 
    {
        return EMPTY; // Alias for a draw
    }
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
 * \struct BotEnvironment
 * Store arguments to be passed to thread
 */
struct BotEnvironment
{
    OthelloPlayer& player;
    OthelloBoard& board;
    Move& move;
    ExceptionFlags flags;

    BotEnvironment( OthelloPlayer& player, OthelloBoard& board, Move& move ) :
        player( player ), board( board ), move( move ) {}

};

struct TimeoutClosure
{
    pthread_t tid;
    BotEnvironment& environ;

    TimeoutClosure( pthread_t tid, BotEnvironment& environ):
        tid( tid ), environ( environ ) {}
};

typedef void* (*start_routine) (void *);
static void createEnvironment( BotEnvironment& environ );


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
static void handleTimeout( sigval_t val )
{
    TimeoutClosure *closure = (TimeoutClosure*) val.sival_ptr;
    pthread_cancel( closure->tid );

    closure->environ.flags = EFLAGS_TIMEOUT;

    delete closure;
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

    // Create a timer
    evt.sigev_notify = SIGEV_THREAD;
    evt.sigev_signo = 0;
    evt.sigev_value.sival_ptr = new TimeoutClosure( pthread_self(), environ );
    evt.sigev_notify_function = handleTimeout;
    evt.sigev_notify_attributes = NULL;

    // Using _POSIX_THREAD_CPUTIME is fairer to the bot because it counts only
    // the time it's thread (i.e. it) gets.
    timer_create( _POSIX_THREAD_CPUTIME, &evt, &timerid );

    // Push a handler that will delete the timer
    pthread_cleanup_push( timerCleanup, timerid );

    // Setup the timer for X seconds.
    its.it_value.tv_sec = BOT_TIMEOUT;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime( timerid, 0, &its, NULL );

    // Finally let the bot play
    try {
        environ.move = environ.player.play( environ.board );
    }
    catch(exception& e)
    {
        environ.flags = EFLAGS_UNHANDLED;
    }

    // Remove aforementioned handler
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

    // Launch a thread
    pthread_attr_init( &attr );
    s = pthread_create( &t_id, &attr, (start_routine) createEnvironment, &environ ) != 0;
    if( s != 0 )
    {
        errno = s;
        perror( "pthread_create" );
    }

    pthread_join( t_id, NULL );

    // Check environ flags for exceptions
    switch( environ.flags )
    {
        case EFLAGS_TIMEOUT:
            throw TimeoutException( environ.player );
            break;
        case EFLAGS_UNHANDLED:
            throw BotException( environ.player );
            break;
        case EFLAGS_NONE:
        default:;
    }

    return move;
}

