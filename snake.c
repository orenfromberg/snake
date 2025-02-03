#include "snake.h"

void food_init(Game * g) {
    for (int i = 0; i < FOOD_LEN; i++) {
        g->food[i].x = rand() % GRID_WIDTH;
        g->food[i].y = rand() % GRID_HEIGHT;
        printf("food %d: (%d,%d)\n", i, g->food[i].x, g->food[i].y);
    }
}

void reset_game(Game * g, int snake_length, int x, int y) {
    g->snake_length = 1;
    for(int i = 0; i < snake_length; i++) {
        g->snake[i].x = x;
        g->snake[i].y = y;
    }
    g->dir = NONE;
    g->state = PLAYING;
    g->score = 0;
    food_init(g);
}

Game * createGame(int snake_length, int x, int y) {
    Game * g = (Game*)malloc(sizeof(Game));
    g->snake_length = snake_length;
    for(int i = 0; i < snake_length; i++) {
        g->snake[i].x = x;
        g->snake[i].y = y;
    }

    g->dir = NONE;
    g->state = TITLE;
    g->score = 0;
    food_init(g);

    print_snake(g);
    return g;    
}

void destroyGame(Game* g) {
    free(g);
}

void draw_died(SDL_Renderer* r, Game* g) {
    SDL_Color foreground = { 255, 255, 255, 255 };
    SDL_Surface * s_text = TTF_RenderText_Solid(g->font, "you died", foreground);
    SDL_Texture* t_text = SDL_CreateTextureFromSurface(r, s_text);
    SDL_Rect dest;
    dest.x = 320 - (s_text->w / 2.0f);
    dest.y = .5*480;
    dest.w = s_text->w;
    dest.h = s_text->h;
    SDL_FreeSurface(s_text);
    SDL_RenderCopy(r, t_text, NULL, &dest);
}

void draw_score(SDL_Renderer* r, Game* g) {
    char c_score[20];
    sprintf(c_score, "%05d", g->score);
    SDL_Color foreground = { 255, 255, 255, 255 };
    SDL_Surface * score = TTF_RenderText_Solid(g->font, c_score, foreground);
    SDL_Texture* text = SDL_CreateTextureFromSurface(r, score);
    SDL_Rect dest;
    dest.x = 320 - (score->w / 2.0f);
    dest.y = .75*480;
    dest.w = score->w;
    dest.h = score->h;
    SDL_FreeSurface(score);
    SDL_RenderCopy(r, text, NULL, &dest);
}

void draw_title(SDL_Renderer* r, Game* g) {
    SDL_RenderCopy(r, g->title_screen, NULL, NULL);
    SDL_Rect dest;
    dest.x = 320 - (g->text_surf->w / 2.0f);
    dest.y = .75*480;
    dest.w = g->text_surf->w;
    dest.h = g->text_surf->h;
    SDL_RenderCopy(r, g->title_text, NULL, &dest);
}

void draw_food(SDL_Renderer * r, Game* g) {
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255); // RGBA: Red, Green, Blue, Alpha
    for(int i = 0; i < FOOD_LEN; i++) {
        draw_square(r, g->food[i].x, g->food[i].y);
    }
}

void draw_playing(SDL_Renderer * r, Game* g) {
    draw_border(r,WINDOW_WIDTH,WINDOW_HEIGHT);
    draw_food(r, g);
    draw_snake(r, g);
    draw_score(r, g);
}

void draw(SDL_Renderer * r, Game* g) {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // RGBA: Red, Green, Blue, Alpha
    SDL_RenderClear(r);

    switch(g->state) {
        case TITLE:
            draw_title(r,g);
            break;
        case PLAYING:
            draw_playing(r,g);
            break;
        case DIED:
            draw_died(r,g);
            break;
    }

    // Update the screen
    SDL_RenderPresent(r);

}

void draw_square(SDL_Renderer* r, int x, int y) {
    // Create a rectangle
    SDL_Rect rect;
    rect.x = x*10;  // X position of the top-left corner
    rect.y = y*10;  // Y position of the top-left corner
    rect.w = 10;  // Width of the rectangle
    rect.h = 10;  // Height of the rectangle
        // Fill the rectangle with the current draw color (red)
    SDL_RenderFillRect(r, &rect);
}

void draw_border(SDL_Renderer* r, int width, int height) {
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

void draw_snake(SDL_Renderer* r, Game * g) {
    // Set the color to green
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255); // RGBA: Red, Green, Blue, Alpha

    draw_square(r, g->snake[0].x, g->snake[0].y);

    SDL_SetRenderDrawColor(r, 0, 128, 0, 255); // RGBA: Red, Green, Blue, Alpha

    for (int i = 1; i < g->snake_length; i++) {
        draw_square(r, g->snake[i].x, g->snake[i].y);
    }
}

void print_snake(Game * g) {
    for (int i = 0; i<g->snake_length; i++) {
        printf("%d,%d\n",g->snake[i].x,g->snake[i].y);
    }
}

void update_playing(Game * g) {
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

    // iterate over snake
    for (int i = g->snake_length-1; i > 0; i--) {
        g->snake[i].x = g->snake[i-1].x;
        g->snake[i].y = g->snake[i-1].y;
    }
    g->snake[0].x += dx;
    g->snake[0].y += dy;

    // check for collisions with border
    if(g->snake[0].x == 0 || g->snake[0].y == 0
        || g->snake[0].x == GRID_WIDTH-1 || g->snake[0].y == GRID_HEIGHT-1) {
        g->state = DIED;
        return;       
    }

    // check for collisions with snake
    for(int i = 1; i < g->snake_length; i++) {
        if (g->snake[0].x == g->snake[i].x && 
            g->snake[0].y == g->snake[i].y) {
                g->state = DIED;
                return;
            }
    }

    // check for collisions with food
    for(int i = 0; i < FOOD_LEN; i++) {
        if (g->snake[0].x == g->food[i].x && 
            g->snake[0].y == g->food[i].y) {
                g->snake_length++;
                g->food[i].x = rand() % GRID_WIDTH;
                g->food[i].y = rand() % GRID_HEIGHT;
                g->score++;
                break;
            }
    }
}

void update(Game * g) {
    switch(g->state) {
        case PLAYING:
            update_playing(g);
            break;
    }
}

int process_input_playing(Game * game) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return 1;
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
                    return 1;
                    break;
                default:
                    // Handle other key presses if needed.
                    break;
            }
        }
    }
    return 0;
}

int process_input_died(Game * game) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return 1;
        } else if (e.type == SDL_KEYDOWN) {
            reset_game(game, 1, (GRID_WIDTH/2)-1, (GRID_HEIGHT/2)-1);
            return 0;
        }
    }
    return 0;    
}

int process_input_init(Game * game) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return 1;
        } else if (e.type == SDL_KEYDOWN) {
            game->state = PLAYING;
            return 0;
        }
    }
    return 0;
}

int process_input(Game * g) {
    switch(g->state) {
        case TITLE:
            return process_input_init(g);
        case PLAYING:
            return process_input_playing(g);
        case DIED:
            return process_input_died(g);
    }
    return 0;
}