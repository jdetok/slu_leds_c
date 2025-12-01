#include "slu_leds.h"

// Lights::Lights(ico* ic, int min_brt, int max_brt) {
//     ic = ic;
//     minm = min_brt;
//     maxm = max_brt;
//     dir = -1;
// }

ico::ico() : data(PIN_ICO_SE), out(PIN_ICO_OE), latch(PIN_ICO_LA), 
    clock(PIN_ICO_CL), bitmask({0}), total_bits(NUM_SR * 8) {};

Lights::Lights(ico* ic, int min_brt, int max_brt)
    : ic(ic), minm(min_brt), maxm(max_brt), dir(-1), lvl(255), onoff(true)
{}

void Lights::out() {
    analogWrite(ic->out, lvl);
}

bool ico::is_full() {
    for (int8_t i = 0; i < NUM_SR; i++) {
        if (bitmask[i] < 0xFF) {
            return false;
        }
    }
    return true;
}

void ico::empty() {
    Serial.println("emptying");
    digitalWrite(latch, LOW);
    for (int i = 0; i < NUM_SR; i++) {
        bitmask[i] = 0x00;
        shiftOut(data, clock, MSBFIRST, 0x00);
    }
    digitalWrite(latch, HIGH);
}
void ico::fill() {
    Serial.println("filling");
    digitalWrite(latch, LOW);
    for (int i = 0; i < NUM_SR; i++) {
        bitmask[i] = 0xFF;
        shiftOut(data, clock, MSBFIRST, 0xFF);
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

void ico::set_bit(uint8_t pos) {
    memset(bitmask, 0, NUM_SR);

    uint8_t byte_idx = pos / 8;
    uint8_t bit_idx = pos % 8;

    bitmask[byte_idx] = (1 << bit_idx);
}

void ico::shift_frame() {
    // Serial.println(sizeof(bitmask) / sizeof(bitmask[0]));

    for (int8_t i = NUM_SR - 1; i >= 0; i--) {
        for (int8_t b = 7; b >= 0; b--) {
            if (bitmask[i] & (1 << b)) {
                PORTD |= (1 << data);
            } else {
                PORTD &= ~(1 << data);
            }
            pulse_pin(0); // clock pulse
        }
    }
    pulse_pin(1); // latch pulse
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
    if (!ic->is_full()) {
        ic->fill();
    } 
}

