#include <stdio.h>
#include <assert.h>
#include "snake.h"
#include "linkedlist.h"

void main(int argc, char * argv) {
    gamestate * state = createGamestate(3);

    for (int i = 0; i < 10; i++) {
        update(state);
    }

    // destroyList(head);
    destroyGamestate(state);
    return 0;
}
