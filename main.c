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

    SDL_Event e;

    Game * game = createGame(10,(WINDOW_WIDTH/20)-1,(WINDOW_HEIGHT/20-1));

    // process_input();

    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        printf("Up arrow pressed!\n");
                        game->dir = UP;
                        break;
                    case SDLK_DOWN:
                        printf("Down arrow pressed!\n");
                        game->dir = DOWN;
                        break;
                    case SDLK_LEFT:
                        printf("Left arrow pressed!\n");
                        game->dir = LEFT;
                        break;
                    case SDLK_RIGHT:
                        printf("Right arrow pressed!\n");
                        game->dir = RIGHT;
                        break;
                    case SDLK_ESCAPE:  // Check for Escape key
                        printf("Escape key pressed. Exiting.\n");
                        quit = true;
                        break;
                    default:
                        // Handle other key presses if needed.
                        break;
                }
            }
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