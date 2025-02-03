#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "snake.h"

SDL_Texture *texture;
TTF_Font* font;

int main(int argc, char* argv[]) {
    printf("%d,%p",argc,argv);

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

    // load resources

    SDL_Surface* buffer = IMG_Load("title.png");
	if ( !buffer ) {
		SDL_Log("Error loading image test.png: %s\n", SDL_GetError());
        return 1;
	}

    texture = SDL_CreateTextureFromSurface( r, buffer );
	SDL_FreeSurface( buffer );
	buffer = NULL;
	if ( !texture ) {
        SDL_Log("Error creating texture: %s\n", SDL_GetError());
        return 1;
	}

    font = TTF_OpenFont("DejaVuSansMono.ttf", 24);
    if ( !font ) {
        SDL_Log("Failed to load font: %s\n", TTF_GetError()); 
    }

    SDL_Color foreground = { 255, 255, 255, 255 };

    SDL_Surface* text_surf = TTF_RenderText_Solid(font, "press any key to begin", foreground);
	SDL_Texture* text = SDL_CreateTextureFromSurface(r, text_surf);

    // Update the screen
    SDL_RenderPresent(r);

    Game * game = createGame(10,(WINDOW_WIDTH/20)-1,(WINDOW_HEIGHT/20-1));

    game->title_screen = texture;
    game->title_text = text;
    game->font = font;
    game->text_surf = text_surf;

    while (1) {
        if (process_input(game)) {
            break;
        }

        update(game);

        draw(r, game);

        SDL_Delay(32);
    }

    destroyGame(game);
    TTF_CloseFont( font );
    SDL_DestroyTexture( texture );
    SDL_DestroyTexture( text );
	texture = NULL;
    text = NULL;
    SDL_DestroyRenderer(r);
    r = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    TTF_Quit();
	IMG_Quit();
    SDL_Quit();
    return 0;
}