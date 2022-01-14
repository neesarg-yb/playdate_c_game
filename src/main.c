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

static int RunFrame( void* ud )
{
	( void ) ud;

	g_game->Update( 0.05f );
	g_game->Render();

	return 1;
}

static void Init()
{
	g_game = CreateGame();
	g_game->Init();

	g_pd->system->setUpdateCallback( RunFrame, NULL );
}

static void Terminate()
{
	g_game->Terminate();
	DestroyGame( &g_game );
}

DllExport int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	(void)arg;

	if ( event == kEventInit )
	{
		g_pd = playdate;
		Init();
	}
	else if( event == kEventTerminate )
	{
		Terminate();
		g_pd = NULL;
	}
	
	return 0;
}
