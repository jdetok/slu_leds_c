#include "slu_leds.h"

Lights::Lights(ico* ic) : ic(ic), minm(255), maxm(0),
    dir(-1), lvl(254), total_bits(NUM_SR * 8), max_chase_idx(80)
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
    int real_max = 0;
    if (maxm > real_max) {
        maxm -= amt;
        if (maxm < real_max) {
            maxm = real_max;
        }
    }
    lvl = maxm;
}

void Lights::pulse_brt_down(int amt) {
    int real_min = 255;
    if (maxm < real_min) {
        maxm += amt;
        if (maxm > real_min) {
            maxm = real_min;
        }
    }
    lvl = maxm;
}

void Lights::pulse() {
    if (lvl >= minm) {
        dir = -1;
    } else if (lvl == maxm) {
        dir = 1;
    }
    if (lvl < 50) {
        lvl += dir * 4;
    } else if (lvl < 125) {
        lvl += dir * 2;
    } else {
        lvl += dir;
    }
}