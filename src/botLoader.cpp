/**
* @file botLoader.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-01-27
* Contains functions to handle loading of bots
*/

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <dlfcn.h>
using namespace std;

#include "botLoader.h"
using namespace Desdemona;

typedef OthelloPlayer* ( *CreateBotFn ) ( Turn turn );

void loadInit()
{
    cerr << "Loading libOthello..." << endl;
    if( (dlopen( "lib/libOthello.so", RTLD_NOW) == NULL ) )
    {
        char* error = dlerror();
        cerr << error << endl;
        throw exception();
    }
}

OthelloPlayer& loadBot( string botPath, Turn turn )
{
    void* botMod;
    OthelloPlayer* bot;
    CreateBotFn createBotFn;

    // TODO: Security checks

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

