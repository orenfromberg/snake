#ifndef SNAKE_H
#define SNAKE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "snake_math.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GRID_WIDTH (WINDOW_WIDTH/10)
#define GRID_HEIGHT (WINDOW_HEIGHT/10)
#define MAX_SNAKE_LEN (WINDOW_WIDTH*WINDOW_HEIGHT)
#define FOOD_LEN 10

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
    float x;
    float y;
} Vec2;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} RGBA;

typedef struct {
    Vec2 snake[MAX_SNAKE_LEN];
    int snake_length;
    Vec2 food[FOOD_LEN];
    int score;
    int top_score;
    Direction dir;
    State state;

    //TODO add window height, width
    // TODO add framerate speed/delay
    SDL_Texture * title_screen;
    SDL_Texture * title_text;
    SDL_Surface * text_surf;
    TTF_Font* font;
} Game;

typedef struct {
    Vec2 position;
    RGBA color;
} Vertex;

// snake, food, gameboard,
// current score, top score
typedef struct {
    Matrix3x3 transform;
    Vertex verts[MAX_SNAKE_LEN];
    void (*init)(void *);
    void (*process_input)(void *);
    void (*draw)(SDL_Renderer * r, void *);
    void (*update)(void *);
    // RGBA colors[MAX_SNAKE_LEN];
} Entity;

void food_init(Game *);

Game* create_game(int,int);

void destroyGame(Game*);

void update(Game *);

void draw(SDL_Renderer *, Game*);

void draw_food(SDL_Renderer *, Game*);

void draw_playing(SDL_Renderer *, Game*);

void draw_title(SDL_Renderer *, Game*);

void draw_snake(SDL_Renderer *, Game *);

void draw_border(SDL_Renderer *,int,int);

void draw_square(SDL_Renderer *,int,int);

int process_input(Game *);

int process_input_playing(Game *);

int process_input_init(Game *);

Entity * create_entity();
void destroy_entity();

#endif