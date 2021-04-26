#include <stdio.h>
#include "types.h"
#include "keyboard.h"
#include "bmp.h"
#include "game.h"
#include "assets.h"
#include "objs.h"
#include "timer.h"


#define MAX_GOBJS_COUNT 255

typedef struct tagGameState {
    bool isRunning;
    bool isPaused;
    GObj *player;
} GameState;


void Game_HandleKeyPressed(word key, GameState *state) {
    switch (key) {
        case KEY_ESC:
            state->isRunning = FALSE;
            break;

        case KEY_UP:
            if (state->player->direction != DIR_UP) {
                state->player->direction = DIR_UP;
            } else {
                state->player->coord.y--;
            }
            break;
        case KEY_DOWN:
            state->player->direction = DIR_DOWN;
            break;
        case KEY_LEFT:
            state->player->direction = DIR_LEFT;
            break;
        case KEY_RIGHT:
            state->player->direction = DIR_RIGHT;
            break;
    }
}

void Game_MainLoop() {
    GameState gameState;
    TankState tankState;
    word keyPressed = 0;
    GObj gObjs[MAX_GOBJS_COUNT];
    byte gObjCount = 1, i;
    Timer timer;

    tankState.color = TANK_PURPLE;
    tankState.size = 1;

    gObjs[0].coord.x = 100;
    gObjs[0].coord.y = 100;
    gObjs[0].direction = DIR_UP;
    gObjs[0].state = &tankState;
    gObjs[0].renderer = Obj_RenderTank;

    gameState.player = &gObjs[0];



    gameState.isRunning = TRUE;
    gameState.isPaused = FALSE;

    Timer_Init(&timer);
    do {
        // handles keyboard
        if (keyPressed = Keyb_GetKeyIfPressed()) {
            Game_HandleKeyPressed(keyPressed, &gameState);
        }

        // renders GObjs
        for (i = 0; i < gObjCount; i++) {
            gObjs[i].renderer(&gObjs[i]);
        }

        printf("%d\n", Timer_ElapsedMs(&timer));

    } while(gameState.isRunning == TRUE);
}
