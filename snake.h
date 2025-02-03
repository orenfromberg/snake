#ifndef SNAKE_H
#define SNAKE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GRID_WIDTH (WINDOW_WIDTH/10)
#define GRID_HEIGHT (WINDOW_HEIGHT/10)
#define MAX_SNAKE_LEN (WINDOW_WIDTH*WINDOW_HEIGHT)
#define FOOD_LEN 3

typedef enum {
    NONE = 0,  // No arrow key pressed
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum {
    TITLE = 0,
    PLAYING,
    DIED
} State;

typedef struct {
    int x;
    int y;
} Vec2;

typedef struct {
    // Node * head;
    // Node * tail;
    // int max_length;
    // int cur_length;
    Vec2 snake[MAX_SNAKE_LEN];
    int snake_length; // length of snake
    Vec2 food[FOOD_LEN];
    int score;
    Direction dir;
    State state;

    //TODO add window height, width
    // TODO add framerate speed/delay
    SDL_Texture * title_screen;
    SDL_Texture * title_text;
    SDL_Surface * text_surf;
    TTF_Font* font;
} Game;

void food_init(Game *);

Game* createGame(int,int,int);

void destroyGame(Game*);

void update(Game *);

void draw(SDL_Renderer *, Game*);

void draw_food(SDL_Renderer *, Game*);

void draw_playing(SDL_Renderer *, Game*);

void draw_title(SDL_Renderer *, Game*);

void draw_snake(SDL_Renderer *, Game *);

void draw_border(SDL_Renderer *,int,int);

int process_input(Game *);

int process_input_playing(Game *);

int process_input_init(Game *);

#endif