#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>
#include "Board.h"

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	bool quit;

	Board board;
	bool state;
	bool humanTurn;
	BOARD_PIECE humanPiece, botPiece;

	void restartGame();

public:
	static const int SCREEN_WIDTH = 600;
	static const int SCREEN_HEIGHT = 600;

	Game();

	bool initWindow();
	void destroyWindow();
	void processEvent(SDL_Event event);
	void drawFrame();
	bool getQuit() { return quit; };
};

