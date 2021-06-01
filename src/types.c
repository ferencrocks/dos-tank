#include "types.h"


DirectionVector Type_DirToVect(Direction dir) {
    DirectionVector vect;
    vect.x = 0;
    vect.y = 0;

    switch (dir) {
        case DIR_UP:
            vect.y = -1;
            break;
        case DIR_DOWN:
            vect.y = 1;
            break;
        case DIR_LEFT:
            vect.x = -1;
            break;
        case DIR_RIGHT:
            vect.x = 1;
            break;
    }
    return vect;
}
