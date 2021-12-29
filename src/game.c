#pragma once
#include "game.h"
#include "pd_api.h"
#include "game_common.h"

// Declarations
static int updateGame( void* ud );

// Definitions - Exposed
Game* initGame()
{
	Game* newGame = g_pd->system->realloc( NULL, sizeof( Game ) );
	newGame->update = updateGame;

	return newGame;
}

void terminateGame( Game** game )
{
	g_pd->system->realloc( *game, 0U );
	*game = NULL;
}

// Definitions - Unexposed
static int updateGame(  void* ud )
{
	( void ) ud;

	g_pd->graphics->clear( kColorWhite );
	g_pd->graphics->drawText( "Sheep Game!", strlen( "Sheep Game!" ), kASCIIEncoding, (int)(LCD_COLUMNS * 0.5f), (int)(LCD_ROWS * 0.5f) );

	g_pd->system->drawFPS( 0, 0 );

	return 1;
}
