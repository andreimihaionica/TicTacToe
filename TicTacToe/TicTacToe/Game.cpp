#include "Game.h"

Game::Game()
{
    srand((unsigned int)time(NULL));
    window = nullptr;
    windowRenderer = nullptr;
    restartGame();
}

bool Game::initWindow()
{
    bool success = true;

    // Try to initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else 
    {
        // Try to create the window
        window = SDL_CreateWindow("Tic Tac Toe",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == nullptr) 
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else 
        {
            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            if (windowRenderer == nullptr) {

                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

void Game::destroyWindow()
{
    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

void Game::processEvent(SDL_Event event)
{
    // User requests quit
    if (event.type == SDL_QUIT)
        quit = true;

    if (state)
    {
        bool successfulPlay = false;
        if (humanTurn)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int row = y / (SCREEN_HEIGHT / 3);
                int col = x / (SCREEN_WIDTH / 3);

                if (board.isFieldEmpty(row, col))
                {
                    board.place(row, col, humanPiece);
                    humanTurn = false;
                    successfulPlay = true;
                }
            }
        }
        else
        {
            int row = rand() % 3;
            int col = rand() % 3;
            while (!board.isFieldEmpty(row, col))
            {
                row = rand() % 3;
                col = rand() % 3;
            }
            board.place(row, col, botPiece);
            humanTurn = true;
            successfulPlay = true;
        }

        if (successfulPlay)
            SDL_Delay(200);

        if (board.hasWinner())
        {
            BOARD_PIECE winner = board.winner();
            if (winner == humanPiece)
            {
                std::cout << "YOU WIN!" << std::endl;
                std::cout << "Press R to restart the game!" << std::endl;
                state = false;
            }
            else
            {
                std::cout << "YOU LOSE!" << std::endl;
                std::cout << "Press R to restart the game!" << std::endl;
                state = false;
            }
        }
        else
        {
            if (board.isDraw())
            {
                std::cout << "DRAW!" << std::endl;
                std::cout << "Press R to restart the game!" << std::endl;
                state = false;
            }
        }

    }


    // Keyboard event
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
            system("CLS");
            std::cout << "Thanks for playing! Bye!" << std::endl;
            quit = true;
            break;
        }
        case SDLK_r:
        {
            restartGame();
            std::cout << "Game restarted!" << std::endl;
            break;
        }

        default:
            break;
        }
    }
}

void Game::drawFrame()
{
    // clear background
    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(windowRenderer);

    // draw the scene
    board.render(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (board.hasWinner())
    {
        BOARD_PIECE winner = board.winner();
        if (winner == humanPiece)
            Util::drawStatus(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, "assets/YouWin.png");
        else
            Util::drawStatus(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, "assets/YouLose.png");
    }
    else
    {
        if (board.isDraw())
            Util::drawStatus(windowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, "assets/Draw.png");
    }

    // render to window
    SDL_RenderPresent(windowRenderer);
}

void Game::restartGame()
{
    system("CLS");
    board.restart();

    quit = false;
    state = true;

    humanTurn = (rand() & 1) ? true : false;
    if (rand() % 1)
    {
        humanPiece = BOARD_PIECE::PIECE_O;
        botPiece = BOARD_PIECE::PIECE_X;
    }
    else
    {
        humanPiece = BOARD_PIECE::PIECE_X;
        botPiece = BOARD_PIECE::PIECE_O;
    }
}