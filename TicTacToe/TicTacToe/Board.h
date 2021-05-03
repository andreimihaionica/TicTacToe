#pragma once
#include <SDL2/SDL.h>
#include "Util.h"

enum class BOARD_PIECE { PIECE_EMPTY, PIECE_X, PIECE_O };

class Board
{
private:
	BOARD_PIECE m[3][3];
	int occupiedPlaces;

	void renderBoard(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const;
	void renderPieces(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const;

	bool checkRows() const;
	bool checkColumns() const;
	bool checkDiagonals() const;
public:
	Board();
	void render(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const;
	void restart();
	bool hasWinner() const { return (checkRows() || checkColumns() || checkDiagonals()); };		// check for win conditions
	BOARD_PIECE winner();
	bool isDraw() const { return occupiedPlaces == 9; };
	void place(int row, int col, BOARD_PIECE piece);
	bool isFieldEmpty(int row, int col) { return m[row][col] == BOARD_PIECE::PIECE_EMPTY; };	// return whether the (row,col) spot is empty
};
