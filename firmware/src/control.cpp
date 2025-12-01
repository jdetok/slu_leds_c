#include "slu_leds.h"

Control::Control(Buttons* b, Lights* l, LCD595* lc, uint8_t sw) : 
    btns(b), leds(l), lcd(lc), pwr_sw(sw), 
    speeds({
        1000, 400, 250, 175, 125, 90, 65, 40, 20, 1
    }), speed_opts(sizeof(speeds) / sizeof(speeds[0])),
    speed_now(5), chase_idx(0)
{}
 
void Control::set_brightness() {
    int amt = amt_to_change();
    if (btns->raw & (1 << btns->brt_up)) {
        Serial.println("up");
        if (btns->persist & (1 << btns->mode1)) { 
            leds->pulse_brt_up(amt);
        } else {
            leds->brt_up(amt);
        }
    }
    if (btns->raw & (1 << btns->brt_dn)) {
        Serial.println("down");
        if (btns->persist & (1 << btns->mode1)) { 
            leds->pulse_brt_down(amt);
        } else {
            leds->brt_down(amt);
        }
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

void Control::set_speed_2() {
    if (btns->raw & (1 << btns->spd_up)) {
        Serial.println("speed up");
        if (speed_now >= speed_opts - 1) {
            if (speed_now > speed_opts) {
                speed_now = speed_opts - 1;
            }
        } else {
            speed_now += 1;
        }
    } else if (btns->raw & (1 << btns->spd_dn)) {
        Serial.println("speed down");
        if (speed_now > 0) {
            speed_now -= 1;
        }
    }

    if (delay_time != speeds[speed_now]) {
        delay_time = speeds[speed_now];
    }
}

void Control::set_speed() {

    int amt = 100;
    if (btns->raw & (1 << btns->spd_up)) {
        Serial.println("up");
        spd_up(amt);
    }
    if (btns->raw & (1 << btns->spd_dn)) {
        Serial.println("down");
        spd_down(amt);
    }
}
void Control::spd_up(int amt) {
    // if (speed_now == speed) {
    //     return;
    // }
    if ((delay_time - amt) >= 0) {
        delay_time -= amt;
    } else if (delay_time > 0 && amt > delay_time) {
        delay_time -= 1;
    }
}
void Control::spd_down(int amt) {
    if ((delay_time + amt) <= 100000) {
        delay_time += amt;
    }
}

void Control::dly() {
    Serial.println(delay_time);
    delay(delay_time);
}

void Control::update_chase_idx(bool rev) {
    if (rev) {
        if (chase_idx == 0) {
            chase_idx = leds->total_bits;
        }
        chase_idx--;
    } else {
        chase_idx++;
        if (chase_idx >= leds->total_bits) {
            chase_idx = 0;
        }
    }
}