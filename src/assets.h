#include "bmp.h"
#include "types.h"


#ifndef ASSETS_H_INCLUDED
#define ASSETS_H_INCLUDED

#define MAIN_SPRITE_MAP     "w:\\dos-tank\\build\\sprites.bmp" // TODO: debug with absolute path
#define SPRITE_WIDTH        16
#define SPRITE_HEIGHT       16

#define TANK_COLORS_COUNT 4
#define TANK_SIZES_COUNT 8
#define TANK_ANIMFRAMES_COUNT 2

typedef enum tagTankColor {
    TANK_YELLOW = 0, TANK_SILVER = 1, TANK_GREEN = 2, TANK_PURPLE = 3
} TankColor;

void Assets_LoadAll();
BMP* Assets_GetTank(TankColor color, byte size, Direction dir, byte animFrame);

#endif
