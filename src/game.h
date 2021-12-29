#pragma once

typedef struct
{
	int ( *update )( void* ud );
} Game;

Game*	initGame();						// Call to initialize above structure & get its pointer
void	terminateGame( Game** game );	// Call on exiting the game, to cleanup the provided struct & its memory
