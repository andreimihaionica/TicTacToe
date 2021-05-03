#include "Util.h"

// render piece on board field (row, col)
void Util::drawPiece(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int row, int col, const char* piece)
{
	int fieldW = SCREEN_WIDTH / 3;
	int fieldH = SCREEN_HEIGHT / 3;

	SDL_Rect src, dest;
	src.x = src.y = 0;
	src.w = dest.w = 128;
	src.h = dest.h = 128;

	dest.x = col * fieldW + 32;
	dest.y = row * fieldH + 32;

	SDL_Surface* tempSurface = IMG_Load(piece);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(windowRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	SDL_RenderCopy(windowRenderer, tex, &src, &dest);
}

// render piece over the board
void Util::drawStatus(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* status)
{
	drawFillRect(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Rect src, dest;
	src.x = src.y = 0;
	src.w = dest.w = 300;
	src.h = dest.h = 300;

	dest.x = SCREEN_WIDTH / 2 - 150;
	dest.y = SCREEN_HEIGHT / 2 - 150;

	SDL_Surface* tempSurface = IMG_Load(status);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(windowRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	SDL_RenderCopy(windowRenderer, tex, &src, &dest);
}

// render fill rect
void Util::drawFillRect(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	SDL_Rect r;
	r.x = 0;
	r.y = SCREEN_HEIGHT / 4;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT / 2;
	SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(windowRenderer, &r);
}
