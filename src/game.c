#pragma once
#include "game.h"
#include "pd_api.h"
#include "game_common.h"

// Declarations
static void	initGame();
static void terminateGame();
static void	updateGame( float deltaSeconds );
static void renderGame();

static void updateDrawOffset();

// Exposed functions
Game* createGame()
{
	Game* newGame = g_pd->system->realloc( NULL, sizeof( Game ) );
	newGame->init		= initGame;
	newGame->update		= updateGame;
	newGame->render		= renderGame;
	newGame->terminate	= terminateGame;

	return newGame;
}

void destroyGame( Game** game )
{
	g_pd->system->realloc( *game, 0U );
	*game = NULL;
}

// Internal functions
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

int drawOffsetX = 0;
int drawOffsetY = 0;

static void updateGame( float deltaSeconds )
{
	updateDrawOffset();
}

static void updateDrawOffset()
{
	int const cameraSpeed = -3;
	unsigned int currentDownButtons = 0U;
	g_pd->system->getButtonState( &currentDownButtons, NULL, NULL );

	int dx = 0;
	{
		if( currentDownButtons & kButtonLeft )
			dx += 1;
		if( currentDownButtons & kButtonRight )
			dx -= 1;
	}
	drawOffsetX += ( dx * cameraSpeed );

	int dy = 0;
	{
		if( currentDownButtons & kButtonUp )
			dy += 1;
		if( currentDownButtons & kButtonDown )
			dy -= 1;
	}
	drawOffsetY += ( dy * cameraSpeed );

	g_pd->system->logToConsole( "dx = %d, dy = %d", dx, dy );
}

static void renderGame()
{
	g_pd->graphics->clear( kColorWhite );

	g_pd->graphics->setDrawOffset( drawOffsetX, drawOffsetY );
	g_pd->graphics->drawText( "Sheep Game!", strlen( "Sheep Game!" ), kASCIIEncoding, ( int ) ( LCD_COLUMNS * 0.5f ), ( int ) ( LCD_ROWS * 0.5f ) );

	g_pd->system->drawFPS( 0, 0 );
}
