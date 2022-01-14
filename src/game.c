#pragma once
#include "game.h"
#include "pd_api.h"
#include "game_common.h"
#include "locomotion.h"
#include "vector.h"

// Declarations
static void	InitGame();
static void TerminateGame();
static void	UpdateGame( float deltaSeconds );
static void RenderGame();

static void UpdateDrawOffset();
static void UpdateTargetPosition( float deltaSeconds );

// Exposed functions
Game* CreateGame()
{
	Game* newGame = g_pd->system->realloc( NULL, sizeof( Game ) );
	newGame->Init		= InitGame;
	newGame->Update		= UpdateGame;
	newGame->Render		= RenderGame;
	newGame->Terminate	= TerminateGame;

	return newGame;
}

void DestroyGame( Game** game )
{
	g_pd->system->realloc( *game, 0U );
	*game = NULL;
}

int c_drawOffsetX = 0;
int c_drawOffsetY = 0;
Locomotion	c_dogLoc;
Vec2		c_sheepPos;

// Internal functions
static void InitGame()
{
	g_pd->display->setRefreshRate( 20 );

	g_font = g_pd->graphics->loadFont( "/System/Fonts/Asheville-Sans-14-Bold.pft", NULL );
	g_pd->graphics->setFont( g_font );

	// Game side variables
	c_sheepPos = MakeVec2( LCD_COLUMNS * 0.5f, LCD_ROWS * 0.5f );

	c_dogLoc.position = MakeVec2( 0.f, 0.f );
	c_dogLoc.velocity = MakeVec2( 0.f, 0.f );
	c_dogLoc.maxSpeed = 25.f;
	c_dogLoc.destination = c_sheepPos;
}

static void TerminateGame()
{
	g_font = NULL;
}

static void UpdateGame( float deltaSeconds )
{
	UpdateTargetPosition( deltaSeconds );
	c_dogLoc.destination = c_sheepPos;

	UpdateLocomotion( &c_dogLoc, deltaSeconds );
	//updateDrawOffset();
}

static void RenderGame()
{
	g_pd->graphics->clear( kColorWhite );

	g_pd->graphics->setDrawOffset( c_drawOffsetX, c_drawOffsetY );
	g_pd->graphics->drawText( "dog!", strlen( "dog!" ), kASCIIEncoding, ( int ) ( c_dogLoc.position.x ), ( int ) ( c_dogLoc.position.y ) );

	g_pd->graphics->drawText( "sheep", strlen( "sheep" ), kASCIIEncoding, ( int ) ( c_sheepPos.x ), ( int ) ( c_sheepPos.y + 16.f ) );
	g_pd->graphics->drawRect( c_sheepPos.x - 8, c_sheepPos.y, 4, 6, kColorBlack );

	g_pd->system->drawFPS( 0, 0 );
}

static void UpdateDrawOffset()
{
	int const cameraSpeed = -3;
	PDButtons currentDownButtons = 0U;
	g_pd->system->getButtonState( &currentDownButtons, NULL, NULL );

	int dx = 0;
	{
		if( currentDownButtons & kButtonLeft )
			dx += 1;
		if( currentDownButtons & kButtonRight )
			dx -= 1;
	}
	c_drawOffsetX += ( dx * cameraSpeed );

	int dy = 0;
	{
		if( currentDownButtons & kButtonUp )
			dy += 1;
		if( currentDownButtons & kButtonDown )
			dy -= 1;
	}
	c_drawOffsetY += ( dy * cameraSpeed );
}

static void UpdateTargetPosition( float deltaSeconds )
{
	float const targetMaxSpeed = 50.f;
	PDButtons currentDownButtons = 0U;
	g_pd->system->getButtonState( &currentDownButtons, NULL, NULL );

	float dx = 0.f;
	{
		if( currentDownButtons & kButtonLeft )
			dx -= 1.f;
		if( currentDownButtons & kButtonRight )
			dx += 1.f;
	}

	float dy = 0.f;
	{
		if( currentDownButtons & kButtonUp )
			dy -= 1.f;
		if( currentDownButtons & kButtonDown )
			dy += 1.f;
	}

	c_sheepPos.x += ( dx * targetMaxSpeed * deltaSeconds );
	c_sheepPos.y += ( dy * targetMaxSpeed * deltaSeconds );
}
