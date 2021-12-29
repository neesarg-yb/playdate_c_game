#pragma once

// Forward declarations
struct PlaydateAPI;
struct LCDFont;
struct Game;

// Global vars
extern PlaydateAPI*	g_pd;			// Set before game is created!
extern Game*		g_game;			// Created on kEventInit
extern LCDFont*		g_font;			// Created on g_game->init()
