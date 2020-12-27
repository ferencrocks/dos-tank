#include <i86.h>
#include <conio.h>
#include "vga.h"


void VGA_Init(unsigned char mode) {
    union REGS regs;
    regs.h.ah = 0x00; /* mode set */
    regs.h.al = mode;
    int386(0x10, &regs, &regs); /* 10h = BIOS video service interrupt */
}

void VGA_SetBmpPalette(BMP_Meta *meta) {
    word i;

    outp(PALETTE_MASK, 0xFF); // access all of the color registers for reading or writing
    outp(PALETTE_WRITE, 0);
    for (i = 0; i <= 255; i++) {
        outp(PALETTE_DATA, meta->palette[i * 4 + 2] >> 2); // red
        outp(PALETTE_DATA, meta->palette[i * 4 + 1] >> 2); // green
        outp(PALETTE_DATA, meta->palette[i * 4] >> 2); // blue
    }
}

void VGA_PutPixel(word x, word y, byte c) {
    VGA[(y << 8) + (y << 6) + x] = c;
}

void VGA_DrawPalette(word xOffset) {
    word c, col;

    for (c = 0; c < 256; c++) {
        for (col = 0; col < 100; col++) {
            VGA_PutPixel(xOffset + c, col, c);
        }
    }
}
