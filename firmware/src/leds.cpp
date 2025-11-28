#include "slu_leds.h"

Lights::Lights(ico* ic, int min_brt, int max_brt) {
    ic = ic;
    minm = min_brt;
    maxm = max_brt;
    dir = -1;
}

void Lights::solid() {
    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(PIN_ICO_SE, PIN_ICO_CL, MSBFIRST, 0xFF);
    }
    analogWrite(PIN_ICO_OE, lvl);
}

void Lights::pulse() {
    if (lvl >= minm) {
        dir = -1;
    } else if (lvl == maxm) {
        dir = 1;
    }
    lvl += dir;
    analogWrite(PIN_ICO_OE, lvl);
}