#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "game.h"

#ifdef _WINDLL
#define DllExport __declspec(dllexport)
#else
#define DllExport
#endif

// Extern pointers exposed in game_common.h
PlaydateAPI*	g_pd	= NULL;
LCDFont*		g_font	= NULL;
Game*			g_game	= NULL;

static void init( PlaydateAPI* pd )
{
	// Setup device & fonts
	g_pd = pd;
	g_pd->display->setRefreshRate( 20 );
	g_font = g_pd->graphics->loadFont( "/System/Fonts/Asheville-Sans-14-Bold.pft", NULL );
	g_pd->graphics->setFont( g_font );

	// Setup game
	g_game = initGame();
	g_pd->system->setUpdateCallback( g_game->update, NULL );
}

static void terminate()
{
	terminateGame( &g_game );
}

DllExport int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	(void)arg;

	if ( event == kEventInit )
	{
		init( playdate );
	}
	else if( event == kEventTerminate )
	{
		terminate();
	}
	
	return 0;
}
