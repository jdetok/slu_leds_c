#include "slu_leds.h"

BTN_State::BTN_State() : persist(0), raw(0), last(0) {}

// read byte from 74HC165
uint8_t BTN_State::read() {
    digitalWrite(PIN_ICI_PL, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ICI_PL, HIGH);
    delayMicroseconds(5);

    digitalWrite(PIN_ICI_CP, HIGH);
    digitalWrite(PIN_ICI_CE, LOW);
    uint8_t incoming = shiftIn(PIN_ICI_SE, PIN_ICI_CP, MSBFIRST);
    digitalWrite(PIN_ICI_CE, HIGH);
    return ~incoming;
}

// find bits which went from 0 to 1, flip only those bits in persisted state
void BTN_State::update() {
    raw = read();
    uint8_t rising = raw & ~last;
    persist ^= rising;
    last = raw;
}

bool BTN_State::pressed(int btn) {
    return persist & (1 << btn);
}


// print all 8 bits in a byte
void printB(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        Serial.print((b >> i) & 1);
    }
    Serial.println();
}