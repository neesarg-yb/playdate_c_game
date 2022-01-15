#pragma once
#include "game.h"
#include "pd_api.h"
#include "game_common.h"
#include "locomotion.h"
#include "flock_tracker.h"

// Declarations
static void	InitGame();
static void TerminateGame();

static void	UpdateGame( float deltaSeconds );
static void UpdateTargetPosition( float deltaSeconds );
static void UpdateDrawOffset();

static void RenderGame();
static void RenderLandField();
static void RenderSheep();
static void RenderDog();


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
Locomotion		c_dogLoc;
Vec2			c_sheepPos;
FlockTracker	c_flockTracker;

// Internal functions
static void InitGame()
{
	g_pd->display->setRefreshRate( 20 );

	g_font = g_pd->graphics->loadFont( "/System/Fonts/Asheville-Sans-14-Bold.pft", NULL );
	g_pd->graphics->setFont( g_font );

	// Game side variables
	c_sheepPos = MakeVec2( 0.f, 0.f );
	c_flockTracker = MakeFlockTracker( &c_sheepPos, 100.f, 90.f );

	c_dogLoc.position = MakeVec2( 0.f, 0.f );
	c_dogLoc.velocity = MakeVec2( 0.f, 0.f );
	c_dogLoc.maxSpeed = 60.f;
	c_dogLoc.destination = c_flockTracker.targetPos;

	// Init draw offset to center ship position
	c_drawOffsetX = ( LCD_COLUMNS * 0.5f ) - c_sheepPos.x;
	c_drawOffsetY = ( LCD_ROWS * 0.5f ) - c_sheepPos.y;
}

static void TerminateGame()
{
	g_font = NULL;
}

static void UpdateGame( float deltaSeconds )
{
	UpdateTargetPosition( deltaSeconds );
	c_dogLoc.destination = c_flockTracker.targetPos;

	UpdateLocomotion( &c_dogLoc, deltaSeconds );
	UpdateFlockTracker( &c_flockTracker );
	UpdateDrawOffset();
}

static void RenderGame()
{
	g_pd->graphics->clear( kColorWhite );
	g_pd->graphics->setDrawOffset( c_drawOffsetX, c_drawOffsetY );

	RenderLandField();
	RenderFlockTracker( &c_flockTracker );
	RenderSheep();
	RenderDog();

	g_pd->system->drawFPS( 0, 0 );
}

static void UpdateDrawOffset()
{
	Vec2 const dogToSheepHalfVec = ScaleVec2( SubVec2( c_sheepPos, c_dogLoc.position ), 0.5f );
	Vec2 const centerPos = AddVec2( c_dogLoc.position, dogToSheepHalfVec );

	c_drawOffsetX = ( LCD_COLUMNS * 0.5f ) - centerPos.x;
	c_drawOffsetY = ( LCD_ROWS * 0.5f ) - centerPos.y;
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

static void RenderLandField()
{
	// Visible screen right now is,
	//                             width                                      
	//   c_drawOffsetX |--------------------------| c_drawOffsetX + LCD_COLUMS
	//                                                                        
	//              --- c_drawOffsetY 
	//               |
	//             h |
	//             e |
	//             i |
	//             g |
	//             h |
	//             t |  c_drawOffsetY
	//               |       +
	//              ---   LCD_ROWS
	int const tileGap = 25;
	int const startColumn = -c_drawOffsetX + ( c_drawOffsetX % tileGap );
	for( int x = startColumn; x < startColumn + LCD_COLUMNS + tileGap; x = x + tileGap )
	{
		int const startRow = -c_drawOffsetY + ( c_drawOffsetY % tileGap );
		for( int y = startRow; y < startRow + LCD_ROWS + tileGap; y = y + tileGap )
		{
			g_pd->graphics->drawRect( x, y, 1, 1, kColorBlack );
		}
	}
}

static void RenderSheep()
{
	g_pd->graphics->drawText( "sheep", strlen( "sheep" ), kASCIIEncoding, ( int ) ( c_sheepPos.x - 20.f), ( int ) ( c_sheepPos.y + 8.f ) );
	g_pd->graphics->drawRect( c_sheepPos.x, c_sheepPos.y, 4, 6, kColorBlack );
}

static void RenderDog()
{
	g_pd->graphics->drawText( "dog!", strlen( "dog!" ), kASCIIEncoding, ( int ) ( c_dogLoc.position.x ), ( int ) ( c_dogLoc.position.y ) );
}
