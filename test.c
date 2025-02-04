#include <stdio.h>
#include <assert.h>
#include "snake.h"

void main(int argc, char * argv) {
    Game * _game = create_game(3,640,480);

    for (int i = 0; i < 10; i++) {
        update(_game);
    }

    // destroyList(head);
    destroyGame(_game);
    return 0;
}
