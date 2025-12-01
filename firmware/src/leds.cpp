#include "slu_leds.h"

Lights::Lights(ico* ic, int min_brt, int max_brt) : ic(ic), minm(min_brt), 
    maxm(max_brt), dir(-1), lvl(255), pulse_max(0), total_bits(NUM_SR * 8)
{}

void Lights::out() {
    analogWrite(ic->out, lvl);
}

void Lights::off() {
    ic->empty();
    out();
}

void Lights::solid() {
    if (!ic->is_full()) {
        ic->fill();
    }
}

void Lights::brt_up(int amt) {
    if ((lvl - amt) >= 0) {
        lvl -= amt;
    } else if (lvl > 0 && amt > lvl) {
        lvl -= 1;
    }
}
void Lights::brt_down(int amt) {
    if ((lvl + amt) <= 255) {
        lvl += amt;
    }
}
void Lights::pulse_brt_up(int amt) {
    if ((pulse_max - amt) >= 0) {
        pulse_max -= amt;
    } else if (pulse_max > 0 && amt > pulse_max) {
        pulse_max -= 1;
    }
}
void Lights::pulse_brt_down(int amt) {
    if ((pulse_max + amt) <= 255) {
        pulse_max += amt;
    }
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
    ic->set_bit(pos, 0);
    ic->shift();
}

void Lights::chase4(uint8_t pos) {
    ic->clear();
    ic->set_bit(pos % total_bits, 0);
    ic->set_bit((pos + 2) % total_bits, 1);
    ic->set_bit((pos + 4) % total_bits, 1);
    ic->set_bit((pos + 6) % total_bits, 1);
    ic->shift();
}