#pragma once

typedef struct
{
	void	( *init ) ( );				// Call after game_common global g_pd var is initialized
	int		( *update )( void* ud );	// Call every frame
	void	( *terminate ) ( );			// Call before shutting down the game
} Game;

// Gives you a Game pointer which has all the above structure func pointers set up
Game*	createGame();

// Deletes the provided game & clears its pointer
void	destroyGame( Game** game );
