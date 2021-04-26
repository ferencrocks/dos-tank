#include "keyboard.h"
#include "types.h"

word Keyb_GetKeyIfPressed() {
    word keyPressed;

    if (kbhit()) {
        keyPressed = (word)getch();
        if (keyPressed == 0) {
            keyPressed = getch() << 8;
        }
        return keyPressed;
    }
    return 0;
}
