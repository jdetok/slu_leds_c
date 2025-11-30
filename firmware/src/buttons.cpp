#include "slu_leds.h"

// ici::ici(int pl, int cp, int se, int ce) : load(pl), cp(cp), data(se), ce(ce) {}; 

Buttons::Buttons(ici* ic) : ic(ic), persist(0), raw(0), last(0) {};

// read byte from 74HC165
uint8_t ici::read() {
    digitalWrite(load, LOW);
    delayMicroseconds(5);
    digitalWrite(load, HIGH);
    delayMicroseconds(5);

    digitalWrite(cp, HIGH);
    digitalWrite(ce, LOW);
    uint8_t incoming = shiftIn(data, cp, MSBFIRST);
    digitalWrite(ce, HIGH);
    return ~incoming;
}

// find bits which went from 0 to 1, flip only those bits in persisted state
void Buttons::update() {
    raw = ic->read();
    lastp = persist; // capture last persist
    uint8_t rising = raw & ~last;
    persist ^= rising;
    last = raw;
}

bool Buttons::pressed(int btn) {
    return persist & (1 << btn);
}

// print all 8 bits in a byte
void printB(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        Serial.print((b >> i) & 1);
    }
    Serial.println();
}

bool Buttons::changed() {
    return persist != lastp;
}