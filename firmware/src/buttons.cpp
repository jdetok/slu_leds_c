#include "slu_leds.h"

ici::ici() : load(PIN_ICI_PL), cp(PIN_ICI_CP), data(PIN_ICI_SE), ce(PIN_ICI_CE) 
{}

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
    lastp = persist; // capture last persist
    raw = ic->read(); // current ic reading
    uint8_t rising = (raw & ~last); // bits currently 1, 0 last time 
    persist ^= rising; // xor flip the rising bits
    last = raw;
}