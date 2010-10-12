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
    while( ( opt = getopt( argc, argv, "strvh" ) ) != -1 )
    {
        switch( opt ) 
        {
            case 't':
                g_Options.mode = TEST;
                break;
            case 'r':
                g_Options.mode = REPLAY;
                break;
            case 's':
                g_Options.shouldStep = true;
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
                fprintf( stderr, "\t-s \t--\t Step through a game\n" );
                exit( EXIT_FAILURE );
        }
    }

    if( (g_Options.mode == REPLAY) && ( argc - optind == 1 ) )
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
    // Load bots
    OthelloPlayer* player1_ptr = NULL;
    OthelloPlayer* player2_ptr = NULL;
    try
    {
        player1_ptr = loadBot( blackBotPath, BLACK );
    }
    catch(exception e)
    {
        cout << "DQ1" << endl;
        return;
    }
    try
    {
        player2_ptr = loadBot( redBotPath, RED );
    }
    catch(exception e)
    {
        cout << "DQ2" << endl;
        return;
    }

    OthelloPlayer& player1 = *player1_ptr;
    OthelloPlayer& player2 = *player2_ptr;
    LoggedOthelloGame game( "game.log", player1, player2 );

    game.printState();

    try
    {
        int margin = game.startGame();

        if( margin == 0 )
        {
            cerr << "[Draw]" << endl;
        }
        else
        {
            string playerStr = ( margin > 0 ) ? "Red" : "Black";
            cerr << "[Win]: " + playerStr << endl;
        }
        
        cout << margin << endl;
    }
    catch( BotInvalidMoveException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cerr << "[Invalid Move]: " << playerStr << endl;
        if( e.player.turn == BLACK )
        {
            cout << "DQ1" << endl;
        }
        else
        {
            cout << "DQ2" << endl;
        }
    }
    catch( TimeoutException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cerr << "[Timeout]: " << playerStr << endl;
        if( e.player.turn == BLACK )
        {
            cout << "TO1" << endl;
        }
        else
        {
            cout << "TO2" << endl;
        }
        cerr << "[Timeout]: " << playerStr << endl;
    }
    catch( BotException& e )
    {
        string playerStr = (e.player.turn == BLACK) ? "Black" : "Red" ;
        cerr << "[Unhandled Exception]: " << playerStr << endl;
        if( e.player.turn == BLACK )
        {
            cout << "CR1" << endl;
        }
        else
        {
            cout << "CR2" << endl;
        }
    }
    catch( exception& e )
    {
        cout << "ERR" << endl;
    }
}

