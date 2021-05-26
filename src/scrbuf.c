#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "vga.h"


byte *screenBuffer;


void ScrBuf_PutPixBuf(byte *pixBuf, word x, word y, word width, word height) {
    word h;

    for (h = 0; h < height; h++) {
        memcpy(
            &screenBuffer[VGA_SCREEN_WIDTH * (y + h) + x],
            &pixBuf[h * width],
            width
        );
    }
}

void ScrBuf_Clear() {
    word i;
    for (i = 0; i < VGA_MEMBLOCK_SIZE; i++) {
        screenBuffer[i] = 0;
    }
}

void ScrBuf_Init() {
    screenBuffer = (byte *)malloc(VGA_MEMBLOCK_SIZE);
    ScrBuf_Clear();
}

void ScrBuf_Destroy() {
    free(screenBuffer);
}

void ScrBuf_FlushToVga() {
    memcpy(VGA, screenBuffer, VGA_MEMBLOCK_SIZE);
    memset(screenBuffer, 0 , VGA_MEMBLOCK_SIZE);
}
