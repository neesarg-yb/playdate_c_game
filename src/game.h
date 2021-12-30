#pragma once

typedef struct Game
{
	// Call after game_common global g_pd var is initialized
	void	( *init ) ( );
	
	// Call every frame
	void	( *update )( float deltaSeconds );
	void	( *render )( );

	// Call before shutting down the game
	void	( *terminate ) ( );
} Game;


Game*	createGame();				// Gives you a Game pointer with above structure func pointers set up
void	destroyGame( Game** game );	// Deletes the provided game & clears its pointer
