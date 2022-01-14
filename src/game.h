#pragma once

typedef struct Game
{
	// Call after game_common global g_pd var is initialized
	void	( *Init ) ( );
	
	// Call every frame
	void	( *Update )( float deltaSeconds );
	void	( *Render )( );

	// Call before shutting down the game
	void	( *Terminate ) ( );
} Game;


Game*	CreateGame();				// Gives you a Game pointer with above structure func pointers set up
void	DestroyGame( Game** game );	// Deletes the provided game & clears its pointer
