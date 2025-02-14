#include "snake.h"

void get_random_location(Vec2* loc) {
    loc->x = (rand() % (GRID_WIDTH-2))+1;
    loc->y = (rand() % (GRID_HEIGHT-2))+1;
}

void food_init(Game * g) {
    for (int i = 0; i < FOOD_LEN; i++) {
        get_random_location(&(g->food[i]));
    }
}

void reset_game(Game * g, int x, int y) {
    g->snake_length = 1;
    g->snake[0].x = x;
    g->snake[0].y = y;
    g->dir = NONE;
    g->state = PLAYING;
    g->score = 0;
    g->cur_pos.x = x;
    g->cur_pos.y = y;
    food_init(g);
}

Game * create_game(int x, int y) {
    Game * g = (Game*)malloc(sizeof(Game));
    g->top_score = 0;
    reset_game(g, x, y);
    g->state = TITLE;
    return g;    
}

void destroyGame(Game* g) {
    free(g);
}

void draw_died(SDL_Renderer* r, Game* g) {
    draw_playing(r,g);
    SDL_Color foreground = { 255, 255, 255, 255 };
    SDL_Surface * s_text = TTF_RenderText_Solid(g->font, "You died! Press space to play again.", foreground);
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
    char c_top_score[20];
    sprintf(c_score, "%05d", g->score);
    sprintf(c_top_score, "Top score: %05d", g->top_score);
    SDL_Color foreground = { 255, 255, 255, 255 };
    SDL_Surface * score = TTF_RenderText_Solid(g->font, c_score, foreground);
    SDL_Surface * top_score = TTF_RenderText_Solid(g->font, c_top_score, foreground);
    SDL_Texture* text = SDL_CreateTextureFromSurface(r, score);
    SDL_Texture* top_score_text = SDL_CreateTextureFromSurface(r, top_score);
    SDL_Rect dest;
    dest.x = 320 - (score->w / 2.0f);
    dest.y = .75*480;
    dest.w = score->w;
    dest.h = score->h;
    SDL_FreeSurface(score);
    SDL_RenderCopy(r, text, NULL, &dest);
    // dest.x = 320 - (top_score->w / 2.0f);
    dest.x = 0;
    dest.y = 0;
    dest.w = top_score->w;
    dest.h = top_score->h;
    SDL_FreeSurface(top_score);
    SDL_RenderCopy(r, top_score_text, NULL, &dest);
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
        draw_square(r, g->food[i].x, g->food[i].y, 10.0f);
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

void draw_square(SDL_Renderer* r, float x, float y, float size) {
    // Create a rectangle
    SDL_FRect rect;
    rect.x = x*10.0f;  // X position of the top-left corner
    rect.y = y*10.0f;  // Y position of the top-left corner
    rect.w = size;  // Width of the rectangle
    rect.h = size;  // Height of the rectangle
        // Fill the rectangle with the current draw color (red)
    // SDL_RenderFillRect(r, &rect);
    SDL_RenderFillRectF(r, &rect);
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

void increment_score(Game * g) {
    g->score++;
    if (g->score > g->top_score) {
        g->top_score = g->score;
    }
}

void draw_snake(SDL_Renderer* r, Game * g) {
    SDL_SetRenderDrawColor(r, 0, 128, 0, 255); // RGBA: Red, Green, Blue, Alpha

    for (int i = 1; i < g->snake_length; i++) {
        draw_square(r, g->snake[i].x, g->snake[i].y, 10.0f);
    }
        // Set the color to green
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255); // RGBA: Red, Green, Blue, Alpha

    // draw head
    // draw_square(r, g->snake[0].x, g->snake[0].y);
    draw_square(r, g->cur_pos.x, g->cur_pos.y, 10.0f);
}

void print_snake(Game * g) {
    for (int i = 0; i<g->snake_length; i++) {
        printf("%f,%f\n",g->snake[i].x,g->snake[i].y);
    }
}

float distance(Vec2 * a, Vec2 * b) {
    return sqrtf((b->x-a->x)*(b->x-a->x)+(b->y-a->y)*(b->y-a->y));
}

void update_playing(Game * g, float d) {
    // if it hasn't reached its destination yet
    if (g->cur_pos.x != (float)(g->snake[0].x) || g->cur_pos.y != (float)(g->snake[0].y)) {
        float dxf = (float)g->snake[0].x - g->cur_pos.x;
        float dyf = (float)g->snake[0].y - g->cur_pos.y;
        Vec2 next;
        float speed = 0.01f;
        next.x = (g->cur_pos.x + (dxf != 0 ? 1 : 0)*(dxf > 0 ? 1 : -1) * d * speed);
        next.y = (g->cur_pos.y + (dyf != 0 ? 1 : 0)*(dyf > 0 ? 1 : -1) * d * speed);

        // if the distance between cur_pos and next is > distance between curpos and snake[0]
        // set curpos to snake[0]
        if (distance(&(g->cur_pos),&next) > distance(&(g->cur_pos), &(g->snake[0]))) {
            g->cur_pos.x = g->snake[0].x;
            g->cur_pos.y = g->snake[0].y;
        } else {
            g->cur_pos.x = next.x;
            g->cur_pos.y = next.y;
        }
        return;
    }

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

    // check for collisions with food
    for(int i = 0; i < FOOD_LEN; i++) {
        if (g->snake[0].x == g->food[i].x && 
            g->snake[0].y == g->food[i].y) {
                g->snake_length++;
                get_random_location(&(g->food[i]));
                increment_score(g);
            }
    }

    // iterate over snake
    for (int i = g->snake_length-1; i > 0; i--) {
        g->snake[i].x = g->snake[i-1].x;
        g->snake[i].y = g->snake[i-1].y;
    }
    // update head
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
}

void update(Game * g, float delta) {
    if(g->state == PLAYING) {
        update_playing(g, delta);
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
                    game->dir = UP;
                    break;
                case SDLK_DOWN:
                    game->dir = DOWN;
                    break;
                case SDLK_LEFT:
                    game->dir = LEFT;
                    break;
                case SDLK_RIGHT:
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
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:  // Check for Escape key
                    reset_game(game, (GRID_WIDTH/2)-1, (GRID_HEIGHT/2)-1);
                    return 0;
                case SDLK_ESCAPE:
                    return 1;
            }
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