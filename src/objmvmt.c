#include "timer.h"
#include "types.h"
#include "objs.h"


void Obj_StartMove(GObj *obj) {
    Timer_Init(&obj->motion.timer);
    obj->motion.start.x = obj->coord.x;
    obj->motion.start.y = obj->coord.y;
    obj->motion.velocity = (obj->motion.speed.sprite * SPRITE_HEIGHT) / (obj->motion.speed.sec * 1000);
    obj->motion.isMoving = TRUE;
}


void Obj_StopMove(GObj *obj) {
    obj->motion.isMoving = FALSE;
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
    obj->coord.x = (word)obj->motion.granularCoord.x;
    obj->coord.y = (word)obj->motion.granularCoord.y;
}


void Obj_SetSpeed(GObj *obj, double sprite, word sec) {
    obj->motion.speed.sprite = sprite;
    obj->motion.speed.sec = sec;
}


bool didArriveToDestination(GObj *obj) {
    switch (obj->direction) {
        case DIR_UP:
            if (obj->coord.y <= obj->motion.dest.y) {
                return TRUE;
            }
            break;
        case DIR_DOWN:
            if (obj->coord.y >= obj->motion.dest.y) {
                return TRUE;
            }
            break;
        case DIR_LEFT:
            if (obj->coord.x <= obj->motion.dest.x) {
                return TRUE;
            }
            break;
        case DIR_RIGHT:
            if (obj->coord.x >= obj->motion.dest.x) {
                return TRUE;
            }
            break;
    }
    return FALSE;
}


void stopWhenArrivedToDestination(GObj *obj) {
    if (didArriveToDestination(obj)) {
        Obj_StopMove(obj);
    }
}

