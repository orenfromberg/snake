#ifndef SNAKE_H
#define SNAKE_H

#include "linkedlist.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef enum {
    NONE = 0,  // No arrow key pressed
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

typedef struct {
    Node * head;
    Node * tail;
    int max_length;
    int cur_length;
    direction dir;
} gamestate;

gamestate* createGamestate(int,int,int);

void destroyGamestate(gamestate*);

void update(gamestate *);

void draw(SDL_Renderer *, gamestate*);

void drawSnake(SDL_Renderer *, gamestate *);

void drawBorder(SDL_Renderer *,int,int);

#endif