#include "timer.h"

void Timer_Init(Timer *timer) {
    timer->lastTicks = *clock;
}

word Timer_ElapsedTicks(Timer *timer) {
    word ticksNow;
    word lastTicks;

    ticksNow = *clock;
    lastTicks = timer->lastTicks;
    // the last tick was before midnight
    if (ticksNow < lastTicks) {
        lastTicks = TIMER_TICKS_PER_DAY - lastTicks + ticksNow;
    }
    return ticksNow - lastTicks;
}

word Timer_ElapsedMs(Timer *timer) {
    return Timer_ElapsedTicks(timer) * TIMER_TICKS_MS;
}
