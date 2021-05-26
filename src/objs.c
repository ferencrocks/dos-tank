#include <stdlib.h>
#include "objs.h"
#include "types.h"
#include "assets.h"


void Obj_Destroy(GObj *obj) {
    free(obj->state);
    free(obj);
}

GObj* Obj_NewTank(word x, word y, Direction dir, TankColor color, byte size) {
    GObj *tank = (GObj *)malloc(sizeof(GObj));
    TankState *state;

    // GObj properties
    tank->coord.x = x;
    tank->coord.y = y;
    tank->coordBottomRight.x = x + SPRITE_WIDTH;
    tank->coordBottomRight.y = y + SPRITE_HEIGHT;
    tank->direction = dir;
    tank->renderer = Obj_RenderTank;
    tank->canMove = TRUE;
    // state
    state = (TankState *)malloc(sizeof(TankState));
    state->color = TANK_PURPLE;
    state->size = 1;
    tank->state = state;

    return tank;
}

void Obj_RenderTank(GObj *obj) {
    TankState *state = (TankState *)obj->state;
    BMP_Render(
        Assets_GetTank(state->color, state->size, obj->direction, obj->animFrame),
        obj->coord.x, obj->coord.y
    );
}
