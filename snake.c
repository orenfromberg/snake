#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "snake.h"

gamestate * createGamestate(int max_length, int x, int y) {
    gamestate * state = (gamestate*)malloc(sizeof(gamestate));
    state->max_length = max_length;
    state->cur_length = 1;
    state->head = createNode(x,y);
    state->tail = state->head;
    state->dir = NONE;

    // printSnake(state);
    return state;    
}

void destroyGamestate(gamestate* state) {
    destroyList(state->head);
}

void printNode(Node * node) {
    printf("addr=%p, next=%p, prev=%p, (%d, %d)\n", node, node->next, node->prev, node->x, node->y);
}

void draw(SDL_Renderer * renderer, gamestate* state) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGBA: Red, Green, Blue, Alpha
    SDL_RenderClear(renderer);

    drawBorder(renderer,WINDOW_WIDTH,WINDOW_HEIGHT);
    drawSnake(renderer, state);

    // Update the screen
    SDL_RenderPresent(renderer);

}

void drawNode(SDL_Renderer* renderer, Node * node) {
    // Create a rectangle
    SDL_Rect rect;
    rect.x = node->x*10;  // X position of the top-left corner
    rect.y = node->y*10;  // Y position of the top-left corner
    rect.w = 10;  // Width of the rectangle
    rect.h = 10;  // Height of the rectangle
        // Fill the rectangle with the current draw color (red)
    SDL_RenderFillRect(renderer, &rect);

}

void drawBorder(SDL_Renderer* renderer, int width, int height) {
    // Set the color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // RGBA: Red, Green, Blue, Alpha
    
    int borderWidth = 10;
    int screenWidth = width; // Your window width
    int screenHeight = height; // Your window height

    // Top border
    SDL_Rect topBorder = { 0, 0, screenWidth, borderWidth };
    SDL_RenderFillRect(renderer, &topBorder);

    // Bottom border
    SDL_Rect bottomBorder = { 0, screenHeight - borderWidth, screenWidth, borderWidth };
    SDL_RenderFillRect(renderer, &bottomBorder);

    // Left border
    SDL_Rect leftBorder = { 0, 0, borderWidth, screenHeight };
    SDL_RenderFillRect(renderer, &leftBorder);

    // Right border
    SDL_Rect rightBorder = { screenWidth - borderWidth, 0, borderWidth, screenHeight };
    SDL_RenderFillRect(renderer, &rightBorder);
}

void drawSnake(SDL_Renderer* renderer, gamestate * state) {
    // Set the color to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // RGBA: Red, Green, Blue, Alpha

    Node * cur = state->head;
    drawNode(renderer, cur);

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // RGBA: Red, Green, Blue, Alpha

    while(cur->next) {
        cur = cur->next;
        drawNode(renderer, cur);
    }
}

void printSnake(gamestate * state) {
    // print all nodes
    printf("current snake:\n");
    Node * cur = state->head;
    printf("head v\n");
    printNode(cur);
    while (cur->next) {
        cur = cur->next;
        printNode(cur);
    }
    printf("tail ^\n");
}

void update(gamestate * state) {
    // create a new node for the new head
    // in the direction the snake is heading
    // lets assume its heading to the right

    // check the state to see which button is pressed
    int dx = 0, dy = 0;
    switch(state->dir) {
        case UP:
            dy--;
            break;
        case DOWN:
            dy++;
            break;
        case RIGHT:
            dx++;
            break;
        case LEFT:
            dx--;
            break;
        default:
            break;
    }

    // create a new head
    Node * new = createNode(state->head->x+dx,state->head->y+dy);

    // new head must point to the old head
    new->next = state->head;

    // the old head must point back to the new
    state->head->prev = new;

    // make the new node the head
    state->head = new;

    // increment the current length of the snake
    state->cur_length++;

    // cull 
    if (state->cur_length > state->max_length) {
        // make new tail point to prev
        Node * tail = state->tail;
        state->tail = state->tail->prev;

        // make tail next point to NULL
        state->tail->next = NULL;
        destroyNode(tail);
    }

    // display snake
    // printSnake(state);
}
