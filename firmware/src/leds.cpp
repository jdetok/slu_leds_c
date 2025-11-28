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
        printB(0xFF);
    }
    digitalWrite(latch, HIGH);
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
    out();
}

void Lights::bit_chaser(bool rev) {
    uint8_t total_bits = NUM_SR * 8;
    uint8_t bytes[NUM_SR];

    for (uint8_t step = 0; step < total_bits; step++) {
        uint8_t bit_pos = rev ? (total_bits - 1 - step) : step;

        for (uint8_t i = 0; i < NUM_SR; i++) {
            bytes[i] = 0;
        }

         uint8_t byte_index = bit_pos / 8;
        uint8_t bit_index  = 7 - (bit_pos % 8);

        bytes[byte_index] |= (1 << bit_index);

        digitalWrite(ic->latch, LOW);

        for (int8_t b = NUM_SR - 1; b >= 0; b--) {
            out();
            shiftOut(ic->data, ic->clock, MSBFIRST, bytes[b]);
        }

        digitalWrite(ic->latch, HIGH);
    }
}
