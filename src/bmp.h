#include <stdio.h>
#include "types.h"

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

typedef struct BMPMetaTag {
    word width;
    word height;
    dword colors;
    byte *palette;
    word dataOffset;
    FILE *fp;
} BMP_Meta;

typedef struct BMPTag {
    BMP_Meta *meta;
    byte *data;
} BMP;


void BMP_LoadMeta(char *file, BMP_Meta *bmp);
void BMP_FreeMeta(BMP_Meta *meta);
void BMP_LoadData(BMP *bmp);
void BMP_CopyDataRect(BMP *bmpSrc, BMP *bmpDest, word x, word y, word x2, word y2);
void BMP_Render(BMP *bmp, word x, word y);

#endif // BMP_H_INCLUDED
