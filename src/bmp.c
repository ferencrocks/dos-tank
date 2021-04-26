#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "vga.h"

#define BMP_HEADER_SIZE 14 // bytes


/* 256 color bitmap loader */
void BMP_LoadMeta(char *file, BMP_Meta *meta) {
    FILE *fp;
    long i;
    word dibSize;

    // Bitmap header
    fp = fopen(file, "rb");
    if (fp == NULL) {
        printf("BMP file not found!");
        exit(1);
    }
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M') { // checks first two bytes for 'BM'
        printf("Invalid BMP file!");
        exit(1);
    }
    fseek(fp, 8, SEEK_CUR);
    fread(&meta->dataOffset, sizeof(word), 1, fp);
    fseek(fp, 2, SEEK_CUR);
    fread(&dibSize, sizeof(word), 1, fp);
    fseek(fp, 2, SEEK_CUR);
    fread(&meta->width, sizeof(word), 1, fp);
    fseek(fp, 2, SEEK_CUR);
    fread(&meta->height, sizeof(word), 1, fp);
    fseek(fp, 22, SEEK_CUR);
    fread(&meta->colors, sizeof(dword), 1, fp);
    fseek(fp, 4, SEEK_CUR);

    // Bitmap palette
    if ((meta->palette = (byte *)malloc(meta->colors * sizeof(dword))) == NULL) {
        printf("Unable to allocate %u bytes for BMP palette!\n", meta->colors * sizeof(dword));
        exit(1);
    }
    fseek(fp, BMP_HEADER_SIZE + dibSize, SEEK_SET);
    for (i = 0; i < meta->colors * 4; i++) {
        meta->palette[i] = fgetc(fp);
    }

    meta->fp = fp;
}

void BMP_FreeMeta(BMP_Meta *meta) {
    free(meta->palette);
    if (meta->fp != NULL) {
        fclose(meta->fp);
    }
}

byte *BMP_allocateDataMem(word width, word height) {
    byte *data;
    if ((data = (byte *)malloc(width * height)) == NULL) {
        printf("Unable to allocate %u bytes for BMP data!\n", width * height);
        exit(1);
    }
    return data;
}

void BMP_LoadData(BMP *bmp) {
    long i, x;

    // Bitmap data
    bmp->data = BMP_allocateDataMem(bmp->meta->width, bmp->meta->height);
    fseek(bmp->meta->fp, bmp->meta->dataOffset, SEEK_SET);
    for (i = (bmp->meta->height - 1) * bmp->meta->width; i >= 0; i -= bmp->meta->width) {
        for (x = 0; x < bmp->meta->width; x++) {
            bmp->data[i + x] = fgetc(bmp->meta->fp);
        }
    }
}

void BMP_CopyDataRect(BMP *bmpSrc, BMP *bmpDest, word x, word y, word x2, word y2) {
    word h;
    short int rw = x2 - x; // rect width
    short int rh = y2 - y; // rect height

    // checks if the requested rectangle is smaller than the whole BMP
    if (rw < 0 || rw > bmpSrc->meta->width) {
        printf("x must be less than x2! x2 - x should be less or equal than the main bitmap's width!");
        exit(1);
    }
    if (rh < 0 || rh > bmpSrc->meta->height) {
        printf("y must be less than y2! y2 - y should be less or equal than the main bitmap's height!");
        exit(1);
    }

    // prepares the destination BMP
    bmpDest->meta->width = rw;
    bmpDest->meta->height = rh;
    bmpDest->meta->palette = bmpSrc->meta->palette;
    bmpDest->meta->colors = bmpSrc->meta->colors;
    bmpDest->meta->fp = NULL; // virtual bitmap, no file assigned
    bmpDest->data = BMP_allocateDataMem(rw, rh);

    for (h = 0; h < rh; h++) {
        memcpy(
            &bmpDest->data[h * rw],
            &bmpSrc->data[(y + h) * bmpSrc->meta->width + x],
            rw
        );
    }
}

void BMP_Render(BMP *bmp, word x, word y) {
    word h, bw, bh;

    bw = bmp->meta->width;
    bh = bmp->meta->height;

    for (h = 0; h < bh; h++) {
        memcpy(
            &VGA[VGA_SCREEN_WIDTH * (y + h) + x],
            &bmp->data[h * bmp->meta->width],
            bw
        );
    }
}

