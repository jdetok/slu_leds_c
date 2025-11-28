#include "slu_leds.h"

Lights::Lights(ico* ic, int min_brt, int max_brt) {
    ic = ic;
    minm = min_brt;
    maxm = max_brt;
    dir = -1;
}

void Lights::off() {
    // for (int i = 0; i < NUM_SR; i++) {
    //     shiftOut(ic->data, ic->clock, MSBFIRST, 0x00);
    // }
    analogWrite(ic->out, 255);
}

void Lights::solid() {
    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(ic->data, ic->clock, MSBFIRST, 0xFF);
    }
    analogWrite(ic->out, lvl);
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