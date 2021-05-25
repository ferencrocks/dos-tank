#include <stdio.h>
#include "types.h"
#include "keyboard.h"
#include "bmp.h"
#include "game.h"
#include "assets.h"
#include "objs.h"
#include "timer.h"
#include "scrbuf.h"


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
            state->player->direction = DIR_UP;
            Obj_StartMove(state->player);
            break;
        case KEY_DOWN:
            state->player->direction = DIR_DOWN;
            Obj_StartMove(state->player);
            break;
        case KEY_LEFT:
            state->player->direction = DIR_LEFT;
            Obj_StartMove(state->player);
            break;
        case KEY_RIGHT:
            state->player->direction = DIR_RIGHT;
            Obj_StartMove(state->player);
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

    gObjs[0].canMove = TRUE;
    gObjs[0].motion.speed.sprite = 1;
    gObjs[0].motion.speed.sec = 1;

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
            if (gObjs[i].canMove) {
                Obj_Move(&gObjs[i]);
            }
        }

        // printf("%d\n", Timer_ElapsedMs(&timer));
        ScrBuf_FlushToVga();

    } while(gameState.isRunning == TRUE);
}
