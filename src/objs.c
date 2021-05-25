#include <stdio.h>
#include "objs.h"
#include "timer.h"
#include "types.h"
#include "assets.h"


void Obj_StartMove(GObj *obj) {
    if (obj->canMove) {
        Timer_Init(&obj->motion.timer);
        obj->motion.start.x = obj->coord.x;
        obj->motion.start.y = obj->coord.y;
        obj->motion.velocity = (obj->motion.speed.sprite * SPRITE_HEIGHT) / (obj->motion.speed.sec * 1000);
        obj->motion.isMoving = TRUE;
    }
}

void Obj_Move(GObj *obj) {
    double mx = 0.0, my = 0.0;
    double d = 0.0;

    if (!obj->canMove || !obj->motion.isMoving) {
        return;
    }
    switch (obj->direction)
    {
        case DIR_UP:
            my = -1.0;
            break;
        case DIR_DOWN:
            my = 1.0;
            break;
        case DIR_LEFT:
            mx = -1.0;
            break;
        case DIR_RIGHT:
            mx = 1.0;
            break;
    }
    d = obj->motion.velocity * Timer_ElapsedMs(&obj->motion.timer);

    obj->motion.granularCoord.x = (double)obj->motion.start.x + mx * d;
    obj->motion.granularCoord.y = (double)obj->motion.start.y + my * d;
    obj->coord.x = (word)(obj->motion.granularCoord.x + 0.5);
    obj->coord.y = (word)(obj->motion.granularCoord.y + 0.5);
}


void Obj_RenderTank(GObj *obj) {
    TankState *state = (TankState *)obj->state;
    BMP_Render(
        Assets_GetTank(state->color, state->size, obj->direction, obj->animFrame),
        obj->coord.x, obj->coord.y
    );
}
