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
#include "OthelloPlayer.h"
#include "HumanPlayer.h"

using namespace std;
using namespace Desdemona;

extern int optind, opterr;

enum Mode
{
    NORMAL=0,
    REPLAY=1,
    TEST=2
};

void runTest();

int main( int argc, char* argv[] )
{
    int opt;
    Mode mode = NORMAL;

    // Parse command line options 
    while( ( opt = getopt( argc, argv, "trh" ) ) != -1 )
    {
        switch( opt ) 
        {
            case 't':
                mode = TEST;
                break;
            case 'r':
                mode = REPLAY;
                break;
            case 'h':
            default: /* '?' */
                OthelloPlayer player = OthelloPlayer();
                OthelloGame game( player, player );
                game.printState();

                fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
                fprintf( stderr, "Usage: %s -r <replay-file>\n", argv[ 0 ] );
                fprintf( stderr, "Options:\n" );
                fprintf( stderr, "\t-h \t--\t Print this message\n" );
                fprintf( stderr, "\t-r \t--\t Replay a game\n" );
                exit( EXIT_FAILURE );
        }
    }

    if( mode == REPLAY && ( argc - optind == 1 ) )
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
            OthelloPlayer player = OthelloPlayer();
            OthelloGame game( player, player );
            game.replayGame( filename );
        }
    }
    else if( mode == NORMAL && ( argc - optind == 2 ) )
    {
        string blackBotName = string( argv[ optind + 0 ] );
        string whiteBotName = string( argv[ optind + 1 ] );
        // Validate input
    }
    else if( mode == TEST )
    {
        runTest();
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

void runTest()
{
    HumanPlayer hPlayer1 = HumanPlayer();
    HumanPlayer hPlayer2 = HumanPlayer();
    OthelloPlayer& player1 = hPlayer1;
    OthelloPlayer& player2 = hPlayer2;
    OthelloGame game( player1, player2 );

    game.printState();
    game.startGame();
}

