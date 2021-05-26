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
    word keyPressed = 0;
    GObj *gObjs[MAX_GOBJS_COUNT];
    byte gObjCount = 1, i;
    Timer timer;

    gObjs[0] = Obj_NewTank(50, 50, DIR_UP, TANK_GREEN, 1);
    Obj_SetSpeed(gObjs[0], 1.25, 1);

    gameState.player = gObjs[0];
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
            gObjs[i]->renderer(gObjs[i]);
            if (gObjs[i]->canMove) {
                Obj_Move(gObjs[i]);
            }
        }

        // printf("%d\n", Timer_ElapsedMs(&timer));
        ScrBuf_FlushToVga();

    } while(gameState.isRunning == TRUE);

    for (i = 0; i < gObjCount; i++) {
        
        gObjs[i]->renderer(gObjs[i]);
        if (gObjs[i]->canMove) {
            Obj_Move(gObjs[i]);
        }
    }

}
