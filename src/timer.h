#include "types.h"


#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#define TIMER_TICKS_PER_DAY 1572480
#define TIMER_TICKS_MS 54.925

word *clock = (word *)0x046C; // BIOS 18.2hz ticks (every 54.925 ms)

// more stuff will come (?)
typedef struct tagTimer {
    word lastTicks;
} Timer;

void Timer_Init(Timer *timer);
word Timer_ElapsedTicks(Timer *timer);
word Timer_ElapsedMs(Timer *timer);

#endif // TIMER_H_INCLUDED
