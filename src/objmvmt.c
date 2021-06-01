#include "timer.h"
#include "types.h"
#include "objs.h"


void Obj_StartMove(GObj *obj) {
    DirectionVector vect = Type_DirToVect(obj->direction);

    Timer_Init(&obj->motion.timer);
    obj->motion.start.x = obj->coord.x;
    obj->motion.start.y = obj->coord.y;
    obj->motion.dest.x = obj->coord.x + vect.x * OBJ_MVMT_UNIT;
    obj->motion.dest.y = obj->coord.y + vect.y * OBJ_MVMT_UNIT;

    obj->motion.velocity = (obj->motion.speed.sprite * SPRITE_HEIGHT) / (obj->motion.speed.sec * 1000);
    obj->motion.isMoving = TRUE;
}


void Obj_StopMove(GObj *obj) {
    obj->motion.isMoving = FALSE;
}


void Obj_Move(GObj *obj) {
    double d = 0.0;
    DirectionVector vect = Type_DirToVect(obj->direction);

    if (!obj->canMove || !obj->motion.isMoving) {
        return;
    }
    
    d = obj->motion.velocity * Timer_ElapsedMs(&obj->motion.timer);

    obj->motion.granularCoord.x = (double)obj->motion.start.x + vect.x * d;
    obj->motion.granularCoord.y = (double)obj->motion.start.y + vect.y * d;
    obj->coord.x = (word)obj->motion.granularCoord.x;
    obj->coord.y = (word)obj->motion.granularCoord.y;

    if (Obj_didArriveToDestination(obj)) {
        Obj_StopMove(obj);
    }
}


void Obj_SetSpeed(GObj *obj, double sprite, word sec) {
    obj->motion.speed.sprite = sprite;
    obj->motion.speed.sec = sec;
}


bool Obj_SetDirection(GObj *obj, Direction dir) {
    bool directionChange = obj->direction != dir;
    obj->direction = dir;
    return directionChange;
}


bool Obj_didArriveToDestination(GObj *obj) {
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
