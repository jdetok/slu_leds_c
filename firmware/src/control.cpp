#include "slu_leds.h"

Control::Control(Buttons* b, Lights* l, LCD595* lc, uint8_t sw) : 
    btns(b), leds(l), lcd(lc), pwr_sw(sw), 
    speeds({
        500, 350, 250, 150, 125, 100, 75, 50, 25, 1
    }), speed_opts(sizeof(speeds) / sizeof(speeds[0])),
    speed_now(5), chase_idx(0), chase_modes(16), current_chase(0)
{}

void Control::set_chase_mode() {
    if (btns->raw & (1 << btns->mode3)) {
        if (current_chase >= chase_modes) {
            current_chase = 0;
        } else {
            current_chase += 1;
        }
    }
}

void Control::set_brightness() {
    int amt = amt_to_change();
    if (btns->raw & (1 << btns->brt_up)) {
        if (btns->persist & (1 << btns->mode1)) { 
            leds->pulse_brt_up(amt);
        } else {
            leds->brt_up(amt);
        }
    }
    if (btns->raw & (1 << btns->brt_dn)) {
        if (btns->persist & (1 << btns->mode1)) { 
            leds->pulse_brt_down(amt);
        } else {
            leds->brt_down(amt);
        }
    }
    leds->out();
}

void Control::set_speed() {
    if (btns->raw & (1 << btns->spd_up)) {
        if (speed_now >= speed_opts - 1) {
            if (speed_now > speed_opts) {
                speed_now = speed_opts - 1;
            }
        } else {
            speed_now += 1;
        }
    } else if (btns->raw & (1 << btns->spd_dn)) {
        if (speed_now > 0) {
            speed_now -= 1;
        }
    }

    if (delay_time != speeds[speed_now]) {
        delay_time = speeds[speed_now];
    }
}

int Control::amt_to_change() {
    int amt = 1;
    int lvl = leds->lvl;
    if (lvl < 125) {
        amt *= 25;
    } else if (lvl < 170) {
        amt *= 15;
    } else if (lvl < 200) {
        amt *= 10;
    } else if (lvl < 220) {
        amt *= 5;
    } else if (lvl < 240) {
        amt *= 2;
    }
    return amt;
}

void Control::dly() {
    delay(delay_time);
}