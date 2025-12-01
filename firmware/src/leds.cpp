#include "slu_leds.h"

Lights::Lights(ico* ic, int min_brt, int max_brt)
    : ic(ic), minm(min_brt), maxm(max_brt), dir(-1), lvl(255), onoff(true)
{}

void Lights::out() {
    analogWrite(ic->out, lvl);
}

void Lights::off() {
    ic->empty();
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

void Lights::chase(uint8_t pos) {
    ic->clear();
    ic->set_bit(pos);
    ic->shift();
}
void Lights::chase4(uint8_t pos) {
    ic->clear();
    ic->set_bit(pos % ic->total_bits);
    ic->add_bit((pos + 2) % ic->total_bits);
    ic->add_bit((pos + 4) % ic->total_bits);
    ic->add_bit((pos + 6) % ic->total_bits);
    ic->shift();
}