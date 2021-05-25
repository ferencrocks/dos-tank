#include "types.h"
#include "bmp.h"

#ifndef VGA_H_INCLUDED
#define VGA_H_INCLUDED

#define VGA_320x200x256     0x13 // 256 colors
#define VGA_SCREEN_WIDTH    320  // px
#define VGA_SCREEN_HEIGHT   200 // px
#define VGA_MEMBLOCK_SIZE   VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT // byte
#define VGA_TEXT            0x03 // text mode

#define PALETTE_MASK        0x3C6
#define PALETTE_READ        0x3C7
#define PALETTE_WRITE       0x3C8
#define PALETTE_DATA        0x3C9


byte *VGA = (byte *)0xA0000;

void VGA_Init(unsigned char mode);
void VGA_SetBmpPalette(BMP_Meta *meta);
void VGA_PutPixel(word x, word y, byte c);
void VGA_DrawPalette(word xOffset);

#endif // VGA_H_INCLUDED
