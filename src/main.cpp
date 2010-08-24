/**
* @file main.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-01-27
* Desdemona - an Othello Competition Framework
*/

#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string>

#include "Othello.h"
#include "OthelloGame.h"
#include "LoggedOthelloGame.h"
#include "OthelloPlayer.h"
#include "botLoader.h"

using namespace std;
using namespace Desdemona;

extern int optind, opterr;

Options g_Options;

static void runGame( string blackBotPath, string redBotPath );

int main( int argc, char* argv[] )
{
    int opt;

    loadInit();

    // Parse command line options 
    while( ( opt = getopt( argc, argv, "trvh" ) ) != -1 )
    {
        switch( opt ) 
        {
            case 't':
                g_Options.mode = TEST;
                break;
            case 'r':
                g_Options.mode = REPLAY;
                break;
            case 'v':
                g_Options.isVerbose = true;
                break;
            case 'h':
            default: /* '?' */
                OthelloPlayer player1 = OthelloPlayer( BLACK );
                OthelloPlayer player2 = OthelloPlayer( RED );
                OthelloGame game( player1, player2 );
                game.printState();

                fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
                fprintf( stderr, "Usage: %s -r <replay-file>\n", argv[ 0 ] );
                fprintf( stderr, "Options:\n" );
                fprintf( stderr, "\t-h \t--\t Print this message\n" );
                fprintf( stderr, "\t-v \t--\t Verbose (print all game states)\n" );
                fprintf( stderr, "\t-r \t--\t Replay a game\n" );
                exit( EXIT_FAILURE );
        }
    }

    if( g_Options.mode == REPLAY && ( argc - optind == 1 ) )
    {
        string filename = string( argv[ optind + 0 ] );

        // Validate input
        struct stat st;
        if( stat( filename.c_str(), &st ) != 0 || !S_ISREG( st.st_mode ) ) 
        {
            fprintf( stderr, "Error loading file: %s\n", filename.c_str() );
            exit( EXIT_FAILURE );
        }
        else
        {
            OthelloPlayer player1 = OthelloPlayer( BLACK );
            OthelloPlayer player2 = OthelloPlayer( RED );
            OthelloGame game( player1, player2 );
            game.replayGame( filename );
        }
    }
    else if( g_Options.mode == NORMAL && ( argc - optind == 2 ) )
    {
        string blackBotPath = string( argv[ optind + 0 ] );
        string redBotPath = string( argv[ optind + 1 ] );

        runGame( blackBotPath, redBotPath );
    }
    else if( g_Options.mode == TEST )
    {
        // Currently does nothing
        //runTest();
    }
    else
    {
        fprintf( stderr, "Bots not specified.\n" );
        fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
        fprintf( stderr, "Usage: %s -r <replay-file>\n", argv[ 0 ] );
        exit( EXIT_FAILURE );
    }

    return 0;
}

static void runGame( string blackBotPath, string redBotPath )
{
    Turn winner;

    // Load bots
    OthelloPlayer& player1 = loadBot( blackBotPath, BLACK );
    OthelloPlayer& player2 = loadBot( redBotPath, RED );
    LoggedOthelloGame game( "game.log", player1, player2 );

    game.printState();

    try
    {
        winner = game.startGame();

        if( winner == EMPTY )
        {
            cout << "[Draw]" << endl;
        }
        else
        {
            string playerStr = ( winner == BLACK ) ? "Black" : "Red";
            cout << "[Win]: " + playerStr << endl;
        }
    }
    catch( BotInvalidMoveException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cout << "[Invalid Move]: " << playerStr << endl;
    }
    catch( TimeoutException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cout << "[Timeout]: " << playerStr << endl;
    }
    catch( BotException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cout << "[Unhandled Exception]: " << playerStr << endl;
    }
}

