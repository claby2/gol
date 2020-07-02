// This program uses SDL2 library to preview Game of Life simulations

#define SDL_MAIN_HANDLED

#include "../single_include/gol/gol.hpp"
#include <SDL2/SDL.h> // Display graphics
#include <chrono>     // Keep track of time for iteration intervals

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int window_width = 640;
int window_height = 480;
int cell_size = 5;       // Height of each individual cell
int step_interval = 100; // Time between steps in milliseconds

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    gWindow = SDL_CreateWindow(
        "gol Previewer", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        window_width, 
        window_height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
    SDL_Quit();
}

int main(int argc, char *args[]) {
    gol::initRandom();

    init();

    bool quit = false;
    SDL_Event event;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Construct board based on window dimensions and cell size
    gol::Board board((int)(window_height / cell_size), (int)(window_width / cell_size));

    // Randomize initial board values
    for(int i = 0; i < board.height(); i++) {
        for(int j = 0; j < board.width(); j++) {
            board[i][j] = gol::getRandomBool();
        }
    }

    while(!quit) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
        if(elapsed_time % step_interval == 0) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // Draw background
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF); // Cell color
            for(int i = 0; i < board.height(); i++) {
                for(int j = 0; j < board.width(); j++) {
                    if(board[i][j] == true) {
                        // Render rect if cell is true
                        SDL_Rect cell = {(j * cell_size), (i * cell_size), cell_size, cell_size};
                        SDL_RenderFillRect(gRenderer, &cell);
                        SDL_RenderDrawRect(gRenderer, &cell);
                    }
                }
            }
            // Next iteration
            board.nextStep();
            SDL_RenderPresent(gRenderer);
        }
    }

    close();
    return 0;
}