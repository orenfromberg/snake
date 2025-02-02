#ifndef SNAKE_H
#define SNAKE_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "linkedlist.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480



typedef enum {
    NONE = 0,  // No arrow key pressed
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum {
    INIT = 0,
    PLAYING,
    DIED
} State;

typedef struct {
    Node * head;
    Node * tail;
    int max_length;
    int cur_length;
    Direction dir;
    State state;

    //TODO add window height, width
    // TODO add framerate speed/delay
} Game;

Game* createGame(int,int,int);

void destroyGame(Game*);

void update(Game *);

void draw(SDL_Renderer *, Game*);

void drawSnake(SDL_Renderer *, Game *);

void drawBorder(SDL_Renderer *,int,int);

int process_input(Game *);

#endif