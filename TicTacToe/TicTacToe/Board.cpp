#include "Board.h"

Board::Board() { restart(); }

// render the board and game pieces to the window
void Board::render(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const
{
    renderBoard(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderPieces(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

// clear the game board
void Board::restart()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = BOARD_PIECE::PIECE_EMPTY;

    occupiedPlaces = 0;
}

// determinate who is the winner
BOARD_PIECE Board::winner()
{
    if (checkRows())
    {
        if (m[0][0] == m[0][1] && m[0][1] == m[0][2] && m[0][2] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else if (m[1][0] == m[1][1] && m[1][1] == m[1][2] && m[1][2] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else if (m[2][0] == m[2][1] && m[2][1] == m[2][2] && m[2][2] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else
            return BOARD_PIECE::PIECE_X;
    }

    if (checkColumns())
    {
        if (m[0][0] == m[1][0] && m[1][0] == m[2][0] && m[2][0] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else if (m[0][1] == m[1][1] && m[1][1] == m[2][1] && m[2][1] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else if (m[0][2] == m[1][2] && m[1][2] == m[2][2] && m[2][2] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else
            return BOARD_PIECE::PIECE_X;
    }

    if (checkDiagonals())
    {
        if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[2][2] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else if (m[0][2] == m[1][1] && m[1][1] == m[2][0] && m[2][0] == BOARD_PIECE::PIECE_O)
            return BOARD_PIECE::PIECE_O;
        else
            return BOARD_PIECE::PIECE_X;

    }

    return BOARD_PIECE::PIECE_EMPTY;
}

// place a piece (human/bot) at (row,col) spot in the board
void Board::place(int row, int col, BOARD_PIECE piece)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && occupiedPlaces < 9)
    {
        m[row][col] = piece;
        occupiedPlaces++;
    }
}

// render board lines
void Board::renderBoard(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const
{
    // set the drawing color to black
    SDL_SetRenderDrawColor(windowRenderer, 0x00, 0x00, 0x00, 0xFF);

    // vertical lines
    SDL_RenderDrawLine(windowRenderer,
        SCREEN_WIDTH / 3, 0,
        SCREEN_WIDTH / 3, SCREEN_HEIGHT);

    SDL_RenderDrawLine(windowRenderer,
        SCREEN_WIDTH / 3 * 2, 0,
        SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT);

    // horizontal lines
    SDL_RenderDrawLine(windowRenderer,
        0, SCREEN_HEIGHT / 3,
        SCREEN_WIDTH, SCREEN_HEIGHT / 3);

    SDL_RenderDrawLine(windowRenderer,
        0, SCREEN_HEIGHT / 3 * 2,
        SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2);
}

// render player pieces
void Board::renderPieces(SDL_Renderer* windowRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) const
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            switch (m[i][j])
            {
            case BOARD_PIECE::PIECE_X:
                Util::drawPiece(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, i, j, "assets/cross.png");
                break;
            case BOARD_PIECE::PIECE_O:
                Util::drawPiece(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, i, j, "assets/circle.png");
                break;
            default:
                break;
            }
        }
}

// check row win conditions
bool Board::checkRows() const
{
    if (m[0][0] == m[0][1] && m[0][1] == m[0][2] && m[0][2] != BOARD_PIECE::PIECE_EMPTY)
        return true;
    else if (m[1][0] == m[1][1] && m[1][1] == m[1][2] && m[1][2] != BOARD_PIECE::PIECE_EMPTY)
        return true;
    else if (m[2][0] == m[2][1] && m[2][1] == m[2][2] && m[2][2] != BOARD_PIECE::PIECE_EMPTY)
        return true;

    return false;
}

// check column win conditions
bool Board::checkColumns() const
{
    if (m[0][0] == m[1][0] && m[1][0] == m[2][0] && m[2][0] != BOARD_PIECE::PIECE_EMPTY)
        return true;
    else if (m[0][1] == m[1][1] && m[1][1] == m[2][1] && m[2][1] != BOARD_PIECE::PIECE_EMPTY)
        return true;
    else if (m[0][2] == m[1][2] && m[1][2] == m[2][2] && m[2][2] != BOARD_PIECE::PIECE_EMPTY)
        return true;

    return false;
}

// check diagonal win conditions
bool Board::checkDiagonals() const
{
    if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[2][2] != BOARD_PIECE::PIECE_EMPTY)
        return true;
    else if (m[0][2] == m[1][1] && m[1][1] == m[2][0] && m[2][0] != BOARD_PIECE::PIECE_EMPTY)
        return true;

    return false;
}