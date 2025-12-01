#include "slu_leds.h"

Buttons::Buttons(ici* ic) : ic(ic), persist(0), raw(0), last(0),
    brt_dn(0), brt_up(1), mode1(2), mode2(3), mode3(4), spd_dn(5),
    spd_up(6), rev(7)
{}

// read byte from 74HC165
uint8_t ici::read() {
    digitalWrite(load, LOW);
    digitalWrite(load, HIGH);
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

// exclude brightness/speed buttons
bool Buttons::pressed(int btn) {
    return raw & (1 << btn);
}

// need to ignore 0 and 1
bool Buttons::changed() {
    uint8_t ignore = 0b11000000;
    return (persist & ~ignore) != (lastp & ~ignore);
}