#include "snake.h"

Game * createGame(int max_length, int x, int y) {
    Game * g = (Game*)malloc(sizeof(Game));
    g->max_length = max_length;
    g->cur_length = 1;
    g->head = createNode(x,y);
    g->tail = g->head;
    g->dir = NONE;

    // printSnake(g);
    return g;    
}

void destroyGame(Game* g) {
    destroyList(g->head);
}

void printNode(Node * node) {
    printf("addr=%p, next=%p, prev=%p, (%d, %d)\n", node, node->next, node->prev, node->x, node->y);
}

void draw(SDL_Renderer * r, Game* g) {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // RGBA: Red, Green, Blue, Alpha
    SDL_RenderClear(r);

    drawBorder(r,WINDOW_WIDTH,WINDOW_HEIGHT);
    drawSnake(r, g);

    // Update the screen
    SDL_RenderPresent(r);

}

void drawNode(SDL_Renderer* r, Node * node) {
    // Create a rectangle
    SDL_Rect rect;
    rect.x = node->x*10;  // X position of the top-left corner
    rect.y = node->y*10;  // Y position of the top-left corner
    rect.w = 10;  // Width of the rectangle
    rect.h = 10;  // Height of the rectangle
        // Fill the rectangle with the current draw color (red)
    SDL_RenderFillRect(r, &rect);

}

void drawBorder(SDL_Renderer* r, int width, int height) {
    // Set the color to blue
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255); // RGBA: Red, Green, Blue, Alpha
    
    int borderWidth = 10;
    int screenWidth = width; // Your window width
    int screenHeight = height; // Your window height

    // Top border
    SDL_Rect topBorder = { 0, 0, screenWidth, borderWidth };
    SDL_RenderFillRect(r, &topBorder);

    // Bottom border
    SDL_Rect bottomBorder = { 0, screenHeight - borderWidth, screenWidth, borderWidth };
    SDL_RenderFillRect(r, &bottomBorder);

    // Left border
    SDL_Rect leftBorder = { 0, 0, borderWidth, screenHeight };
    SDL_RenderFillRect(r, &leftBorder);

    // Right border
    SDL_Rect rightBorder = { screenWidth - borderWidth, 0, borderWidth, screenHeight };
    SDL_RenderFillRect(r, &rightBorder);
}

void drawSnake(SDL_Renderer* r, Game * g) {
    // Set the color to green
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255); // RGBA: Red, Green, Blue, Alpha

    Node * cur = g->head;
    drawNode(r, cur);

    SDL_SetRenderDrawColor(r, 0, 128, 0, 255); // RGBA: Red, Green, Blue, Alpha

    while(cur->next) {
        cur = cur->next;
        drawNode(r, cur);
    }
}

void printSnake(Game * g) {
    // print all nodes
    printf("current snake:\n");
    Node * cur = g->head;
    printf("head v\n");
    printNode(cur);
    while (cur->next) {
        cur = cur->next;
        printNode(cur);
    }
    printf("tail ^\n");
}

void update(Game * g) {
    int dx = 0, dy = 0;
    switch(g->dir) {
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
    Node * new = createNode(g->head->x+dx,g->head->y+dy);

    // new head must point to the old head
    new->next = g->head;

    // the old head must point back to the new
    g->head->prev = new;

    // make the new node the head
    g->head = new;

    // increment the current length of the snake
    g->cur_length++;

    // cull 
    if (g->cur_length > g->max_length) {
        // make new tail point to prev
        Node * tail = g->tail;
        g->tail = g->tail->prev;

        // make tail next point to NULL
        g->tail->next = NULL;
        destroyNode(tail);
    }
}
