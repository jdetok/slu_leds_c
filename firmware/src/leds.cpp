#include "slu_leds.h"

void leds_onoff(bool on) {
    digitalWrite(PIN_ICO_LA, LOW); // latch low
    int mask = on ? 0xFF : 0x00; 

    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(PIN_ICO_SE, PIN_ICO_CL, MSBFIRST, mask);
    }
    digitalWrite(PIN_ICO_LA, HIGH); // latch high (output the bits)
    // delay(1000);
}

void pulse(brightness* BRT) {
    if (BRT->lvl >= BRT->min) {
        BRT->dir = -1;
    } else if (BRT->lvl == BRT->max) {
        BRT->dir = 1;
    }
    BRT->lvl += BRT->dir;
    analogWrite(PIN_ICO_OE, BRT->lvl);
}