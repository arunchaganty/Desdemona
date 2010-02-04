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
#include <dlfcn.h>
#include <string>

#include "Othello.h"
#include "OthelloGame.h"
#include "LoggedOthelloGame.h"
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
OthelloPlayer& loadBot();
OthelloPlayer& loadBot( string botPath, Turn turn );

typedef OthelloPlayer* ( *CreateBotFn ) ( Turn turn );

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
                OthelloPlayer player1 = OthelloPlayer( BLACK );
                OthelloPlayer player2 = OthelloPlayer( RED );
                OthelloGame game( player1, player2 );
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
            OthelloPlayer player1 = OthelloPlayer( BLACK );
            OthelloPlayer player2 = OthelloPlayer( RED );
            OthelloGame game( player1, player2 );
            game.replayGame( filename );
        }
    }
    else if( mode == NORMAL && ( argc - optind == 2 ) )
    {
        string blackBotPath = string( argv[ optind + 0 ] );
        string redBotPath = string( argv[ optind + 1 ] );

        // Load bots
        OthelloPlayer& player1 = loadBot( blackBotPath, BLACK );
        OthelloPlayer& player2 = loadBot( redBotPath, RED );
        LoggedOthelloGame game( "game.log", player1, player2 );

        game.printState();
        game.startGame();

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
    HumanPlayer hPlayer1 = HumanPlayer( BLACK );
    HumanPlayer hPlayer2 = HumanPlayer( RED );
    OthelloPlayer& player1 = hPlayer1;
    OthelloPlayer& player2 = hPlayer2;
    LoggedOthelloGame game( "game.log", player1, player2 );

    game.printState();
    game.startGame();
}

OthelloPlayer& loadBot( string botPath, Turn turn )
{
    // First of all open paths to the bots
    void* botMod;
    OthelloPlayer* bot;
    CreateBotFn createBotFn;

    cerr << "Loading libOthello..." << endl;
    botMod = dlopen( "lib/libOthello.so", RTLD_NOW );
    if( botMod == NULL )
    {
        char* error = dlerror();
        cerr << error << endl;
        // "Could not load bot";
        throw exception();
        //throw InvalidBotModule( "Could not load bot" );
    }

    cerr << "Loading bot..." << endl;
    botMod = dlopen( botPath.c_str(), RTLD_NOW );
    if( botMod == NULL )
    {
        char* error = dlerror();
        cerr << error << endl;
        // "Could not load bot";
        throw exception();
        //throw InvalidBotModule( "Could not load bot" );
    }

    createBotFn = (CreateBotFn) dlsym( botMod, "createBot" );
    if( createBotFn == NULL )
    {
        char* error = dlerror();
        cerr << error << endl;
        throw exception();
    }

    bot = createBotFn( turn );

    return *bot;
}

