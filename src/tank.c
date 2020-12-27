#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "vga.h"
#include "bmp.h"

void main() {
    BMP bmp, bmpRect;
    BMP_Meta bmpMeta;
    int i;

    bmp.meta = &bmpMeta;

    BMP_LoadMeta("SPRITES.BMP", bmp.meta);

    VGA_Init(VGA_320x200x256);

    VGA_SetBmpPalette(bmp.meta);
    VGA_DrawPalette(0);
    BMP_LoadData(&bmp);
    // bmpRect = BMP_CopyDataRect(&bmp, 20, 20, 45, 45);
    BMP_Render(&bmp, 0, 0);

    BMP_FreeMeta(bmp.meta);
    
    getch();
    VGA_Init(VGA_TEXT);
}
