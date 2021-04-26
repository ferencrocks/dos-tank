#include <stdio.h>
#include "assets.h"
#include "vga.h"
#include "env.h"
#include "game.h"


BMP spriteMap;
BMP_Meta spriteMapMeta;
bool spriteMapLoaded = FALSE;

// dimensions: Color, Size, Direction, AnimFrame
BMP Assets_Tank[TANK_COLORS_COUNT][TANK_SIZES_COUNT][DIRECTIONS_COUNT][TANK_ANIMFRAMES_COUNT];


void Assets_loadSpriteMap() {
    if (spriteMapLoaded == FALSE) {
        spriteMap.meta = &spriteMapMeta;
        BMP_LoadMeta(MAIN_SPRITE_MAP, &spriteMapMeta);
        // palette manipulation breaks Watcom Debugger's colors too
        #ifndef DEBUG
        VGA_SetBmpPalette(&spriteMapMeta);
        #endif
        BMP_LoadData(&spriteMap);
    }
}

void Assets_LoadTanks() {
    byte color, size, direction, animFrame;
    word spriteBlockX, spriteBlockY, spriteBlOffsX, spriteBlOffsY;

    for (color = 0; color < TANK_COLORS_COUNT; color++) {
        spriteBlockX = (color % 2) * DIRECTIONS_COUNT * TANK_ANIMFRAMES_COUNT * SPRITE_WIDTH;
        spriteBlockY = (int)(color / 2) * TANK_SIZES_COUNT * SPRITE_HEIGHT;

        for (size = 0; size < TANK_SIZES_COUNT; size++) {
            for (direction = 0; direction < DIRECTIONS_COUNT; direction++) {
                for (animFrame = 0; animFrame < TANK_ANIMFRAMES_COUNT; animFrame++) {
                    spriteBlOffsX = (direction * 2 + animFrame) * SPRITE_WIDTH;
                    spriteBlOffsY = size * SPRITE_HEIGHT;

                    BMP_CopyDataRect(
                        &spriteMap,
                        &Assets_Tank[color][size][direction][animFrame],
                        spriteBlockX + spriteBlOffsX,
                        spriteBlockY + spriteBlOffsY,
                        spriteBlockX + spriteBlOffsX + SPRITE_WIDTH,
                        spriteBlockY + spriteBlOffsY + SPRITE_HEIGHT
                    );
                }
            }
        }
    }
}

BMP* Assets_GetTank(TankColor color, byte size, Direction dir, byte animFrame) {
    return &Assets_Tank[color][size][dir][animFrame];
}

void Assets_LoadAll() {
    Assets_loadSpriteMap();
    Assets_LoadTanks();
}

void Assets_UnloadAll() {
    
}
