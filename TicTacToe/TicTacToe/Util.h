#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Util
{
public:
    static void drawPiece(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int row, int col, const char* piece);
    static void drawStatus(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* status);
    static void drawFillRect(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
};
