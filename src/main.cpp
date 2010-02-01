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
#include "DummyPlayer.h"

using namespace std;
using namespace Desdemona;

extern int optind, opterr;

enum Mode
{
    NORMAL=0,
    REPLAY=1
};

int main( int argc, char* argv[] )
{
    int opt;
    Mode mode = NORMAL;

    // Parse command line options 
    while( ( opt = getopt( argc, argv, "rh" ) ) != -1 )
    {
        switch( opt ) 
        {
            case 'r':
                mode = REPLAY;
            case 'h':
            default: /* '?' */
                DummyPlayer player = DummyPlayer();
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
            DummyPlayer player = DummyPlayer();
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
    else
    {
        fprintf( stderr, "Bots not specified.\n" );
        fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
        fprintf( stderr, "Usage: %s -r <replay-file>\n", argv[ 0 ] );
        exit( EXIT_FAILURE );
    }

    return 0;
}


