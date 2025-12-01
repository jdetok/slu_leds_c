#include "slu_leds.h"

Lights::Lights(ico* ic) : ic(ic), minm(255), maxm(0),
    dir(-1), lvl(250), total_bits(NUM_SR * 8)
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
    if ((lvl + amt) <= minm) {
        lvl += amt;
    }
}
void Lights::pulse_brt_up(int amt) {
    if ((maxm - amt) >= 0) {
        maxm -= amt;
    } else if (maxm > 0 && amt > maxm) {
        maxm -= 1;
    }
    if (lvl < maxm) {
        lvl = maxm;
    }
}
void Lights::pulse_brt_down(int amt) {
    if ((maxm + amt) <= 255) {
        maxm += amt;
    }
}
void Lights::pulse() {
    if (lvl >= minm) {
        dir = -1;
    } else if (lvl == maxm) {
        dir = 1;
    }
    if (lvl < 125) {
        lvl += dir * 2;
    } else {
        lvl += dir;
    }
    
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