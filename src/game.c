#pragma once
#include "game.h"
#include "pd_api.h"
#include "game_common.h"

// Declarations
static void	initGame();
static int	updateGame( void* ud );
static void terminateGame();

// Exposed functions
Game* createGame()
{
	Game* newGame = g_pd->system->realloc( NULL, sizeof( Game ) );
	newGame->update		= updateGame;
	newGame->init		= initGame;
	newGame->terminate	= terminateGame;

	return newGame;
}

void destroyGame( Game** game )
{
	g_pd->system->realloc( *game, 0U );
	*game = NULL;
}

// Internal functions
static int updateGame(  void* ud )
{
	( void ) ud;

	g_pd->graphics->clear( kColorWhite );
	g_pd->graphics->drawText( "Sheep Game!", strlen( "Sheep Game!" ), kASCIIEncoding, (int)(LCD_COLUMNS * 0.5f), (int)(LCD_ROWS * 0.5f) );

	g_pd->system->drawFPS( 0, 0 );

	return 1;
}

static void initGame()
{
	g_pd->display->setRefreshRate( 20 );

	g_font = g_pd->graphics->loadFont( "/System/Fonts/Asheville-Sans-14-Bold.pft", NULL );
	g_pd->graphics->setFont( g_font );
}

static void terminateGame()
{
	g_font = NULL;
}
