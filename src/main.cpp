/**
* @file main.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-01-27
* Desdemona - an Othello Competition Framework
*/

#include <unistd.h>
#include <cstdlib>
#include <cstdio>

extern int optind, opterr;

void printHelp();

int main( int argc, char* argv[] )
{
    int opt;

    // Parse command line options 
    while( ( opt = getopt( argc, argv, "h" ) ) != -1 )
    {
        switch( opt ) 
        {
            case 'h':
            default: /* '?' */
                fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
                fprintf( stderr, "Options:\n" );
                fprintf( stderr, "\t-h \t--\t Print this message\n" );
                exit( EXIT_FAILURE );
        }
    }

    if( argc - optind != 2 )
    {
        fprintf( stderr, "Bots not specified.\n" );
        fprintf( stderr, "Usage: %s [options] <bot-black> <bot-white>\n", argv[ 0 ] );
        exit( EXIT_FAILURE );
    }

    return 0;
}

