#include "objs.h"

void Obj_RenderTank(GObj *obj) {
    TankState *state = (TankState *)obj->state;
    BMP_Render(
        Assets_GetTank(state->color, state->size, obj->direction, obj->animFrame),
        obj->coord.x, obj->coord.y
    );
}
