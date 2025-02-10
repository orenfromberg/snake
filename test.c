#include <stdio.h>
#include <assert.h>
#include "snake.h"

// void test_mult() {
//     Matrix3x3 m = scale(10,14);
//     Matrix3x3 n = translate(3,2);
//     Matrix3x3 result = multiply_matrices(&m, &n);
//     print_matrix(&result);
// }

// void test_entity() {
//     Entity * board = create_entity();
// }

void square_init(void * e) {
    Entity * square = (Entity *)e;
    scale_mat(&(square->transform), 2, 2);
}

int main(int argc, char ** argv) {
    printf("%d, %p\n",argc,argv);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
        SDL_Log("Error initializing SDL_image: %s\n", IMG_GetError());
		return false;
	}

    if (TTF_Init() < 0) {
        SDL_Log("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Game * game = create_game((GRID_WIDTH/2)-1,(GRID_HEIGHT/2-1));

    Entity * square = create_entity();
    square->init = square_init;
    if (square->init != NULL) {
        square->init(square);
    }    // while (1) {
    //     // if (square->(*process_input)(square)) {
    //     //     break;
    //     // }

    //     // square->(*update)(square);

    //     // square->(*draw)(r, square);

    //     SDL_Delay(64);
    // }

    destroy_entity(square);
    SDL_DestroyRenderer(r);
    r = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    // TTF_Quit();
	// IMG_Quit();
    SDL_Quit();
    return 0;
}
