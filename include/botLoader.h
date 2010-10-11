#ifndef BOTLOADER_H
#define BOTLOADER_H

/**
 * @brief BotLoader Loads a bot
 * @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
 * @date 2010-01-27
 */

#include "Othello.h"
#include "OthelloPlayer.h"

using namespace Desdemona;

void loadInit();
OthelloPlayer* loadBot( string botPath, Turn turn );

#endif /* #ifndef BOTLOADER_H */
