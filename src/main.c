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

static void init()
{
	g_game = createGame();
	g_game->init();

	g_pd->system->setUpdateCallback( g_game->update, NULL );
}

static void terminate()
{
	g_game->terminate();
	destroyGame( &g_game );
}

DllExport int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	(void)arg;

	if ( event == kEventInit )
	{
		g_pd = playdate;
		init();
	}
	else if( event == kEventTerminate )
	{
		terminate();
		g_pd = NULL;
	}
	
	return 0;
}
