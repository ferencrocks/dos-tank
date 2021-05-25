#include "assets.h"
#include "timer.h"


#ifndef OBJS_H_INCLUDED
#define OBJS_H_INCLUDED


typedef void (*GObjRenderer)(struct tagGObj *gObj);

typedef struct tagGObjMotion {
    bool isMoving;
    Coord dest;
    Speed *speed;
    Timer timer;
} GObjMotion;

typedef struct tagGObj {
    Coord coord;
    Direction direction;
    bool killable;
    byte animFrame;

    bool canMove;
    GObjMotion motion;

    // pointer to any struct holding object-specific custom state
    void *state;
    // pointer to the game object's renderer function
    // it receives as argument a pointer to the game object itself
    GObjRenderer renderer;
} GObj;

typedef struct tagTankState {
    TankColor color;
    byte size;
    Speed speed;
} TankState;


void Obj_RenderTank(GObj *obj);

#endif // OBJS_H_INCLUDED
