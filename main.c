#include <SDL2/SDL.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "snake.h"

int main(int argc, char* argv[]) {
    printf("%d,%p",argc,argv);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Use hardware acceleration if available
    if (r == NULL) {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Update the screen
    SDL_RenderPresent(r);

    Game * game = createGame(10,(WINDOW_WIDTH/20)-1,(WINDOW_HEIGHT/20-1));

    while (1) {
        if (process_input(game)) {
            break;
        }

        update(game);

        draw(r, game);

        SDL_Delay(32);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}