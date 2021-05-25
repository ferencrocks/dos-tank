#include <stdio.h>
#include <string.h>
#include "vga.h"
#include "game.h"
#include "assets.h"
#include "scrbuf.h"


void main(int argc, char *argv[]) {
    VGA_Init(VGA_320x200x256);
    ScrBuf_Init();

    Assets_LoadAll();

    Game_MainLoop();

    VGA_Init(VGA_TEXT);
    ScrBuf_Destroy();
}
