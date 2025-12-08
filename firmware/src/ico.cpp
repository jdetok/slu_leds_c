#include "slu_leds.h"

ico::ico() : data(PIN_ICO_SE), out(PIN_ICO_OE), latch(PIN_ICO_LA), 
    clock(PIN_ICO_CL) 
{ memset(bitmask, 0, NUM_SR); }

void ico::shift() {
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

bool ico::is_full() {
    for (int8_t i = 0; i < NUM_SR; i++) {
        if (bitmask[i] < 0xFF) {
            return false;
        }
    }
    return true;
}

void ico::clear() {
    memset(bitmask, 0, NUM_SR);
}

void ico::empty() {
    Serial.println("emptying");
    memset(bitmask, 0, NUM_SR);
    shift();
}

void ico::fill() {
    Serial.println("filling");
    memset(bitmask, 0xFF, NUM_SR);
    shift();
}

// 0 for clock, 1 for latch
void ico::pulse_pin(uint8_t clk_latch) {
    switch (clk_latch) {
    case 0:
        PORTD |= (1 << clock);
        PORTD &= ~(1 << clock);
        break;
    case 1:
        PORTD |= (1 << latch);
        PORTD &= ~(1 << latch);
        break;
    }
}
void ico::set_bit(uint8_t pos, bool add) {
    uint8_t byte_idx = pos / 8;
    uint8_t bit_idx = pos % 8;
    Serial.println(bit_idx);
    if (add) {
        bitmask[byte_idx] |= (1 << bit_idx);
    } else {
        bitmask[byte_idx] = (1 << bit_idx);
    }
}

void ico::set_byte(uint8_t pos) {
    uint8_t byte_idx = pos / 8;
    uint8_t bit_idx = pos % 8;
    for (int8_t i = 0; i < 16; i++) {    
        if ((bit_idx + i) < 8) {
            bitmask[byte_idx] |= (1 << (bit_idx + i));
        } else {
            bitmask[byte_idx + 1] |= (1 << (bit_idx + i));
        }
    }
}