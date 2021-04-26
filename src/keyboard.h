#include <conio.h>
#include "types.h"

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#define KEY_ESC     27
#define KEY_ENTER   13
#define KEY_LEFT    0x4b00
#define KEY_RIGHT   0x4d00
#define KEY_DOWN    0x5000
#define KEY_UP      0x4800

word Keyb_GetKeyIfPressed();

#endif // KEYBOARD_H_INCLUDED
