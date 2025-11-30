#include "slu_leds.h"

// Lights::Lights(ico* ic, int min_brt, int max_brt) {
//     ic = ic;
//     minm = min_brt;
//     maxm = max_brt;
//     dir = -1;
// }
Lights::Lights(ico* ic, int min_brt, int max_brt)
    : ic(ic), minm(min_brt), maxm(max_brt), dir(-1), lvl(255), onoff(true)
{}

void Lights::out() {
    analogWrite(ic->out, lvl);
}

void ico::empty() {
    Serial.println("emptying");
    digitalWrite(latch, LOW);
    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(data, clock, MSBFIRST, 0x00);
    }
    digitalWrite(latch, HIGH);
}
void ico::fill() {
    Serial.println("filling");
    digitalWrite(latch, LOW);
    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(data, clock, MSBFIRST, 0xFF);
        // printB(0xFF);
    }
    digitalWrite(latch, HIGH);
}

// 0 for clock, 1 for latch
void ico::pulse_pin(uint8_t clk_latch) {
    switch (clk_latch) {
    case 0: // clock pin
        PORTD |= (1 << clock);
        PORTD &= ~(1 << clock);
        break;
    case 1: // latch pin
        PORTD |= (1 << latch);
        PORTD &= ~(1 << latch);
        break;
    }
}

void Lights::off() {
    lvl = 255;
    out();
}

void Lights::pulse() {
    if (lvl >= minm) {
        dir = -1;
    } else if (lvl == maxm) {
        dir = 1;
    }
    lvl += dir;
    ic->fill();
    out();
}

