#include "slu_leds.h"

// print all 8 bits in a byte
void printB(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        Serial.print((b >> i) & 1);
    }
    Serial.println();
}

void print_mask(uint8_t mask[NUM_SR]) {
    for (int8_t i = 0; i < NUM_SR; i++) {
        for (int8_t b = 7; b >= 0; b--) {
            Serial.print((mask[i] >> b) & 1);
        }
    }
    Serial.println();
}

Control::Control(Buttons* b, Lights* l, LCD595* lc, uint8_t pwr_sw) : 
    btns(b), leds(l), lcd(lc), pwr_sw(pwr_sw), chase_idx(0)
{}

void Control::run() {
// power switch off
    if (!digitalRead(pwr_sw)) {
        Serial.println("off");
        leds->off();
        return;
    }
    
    // current button reading
    btns->update();
    set_brightness();
    set_speed();
    // printB(btns->persist);
    
    if (btns->persist & (1 << btns->mode1)) {
        leds->pulse();
    } else if (btns->persist & (1 << btns->mode2)) {
        if (btns->persist & (1 << btns->mode3)) {
            leds->chase4(chase_idx);
        } else {
            leds->chase(chase_idx);
        }
        update_chase_idx(btns->persist & (1 << btns->rev));
    } else {
        leds->solid();
    }
    print_mask(leds->ic->bitmask); 
    leds->out();
    dly();
}

void Control::set_brightness() {
    int amt = amt_to_change();
    if (btns->raw & (1 << btns->brt_up)) {
        Serial.println("up");
        if (!(btns->persist & (1 << btns->mode1))) { 
            leds->brt_up(amt);
        } else {
            leds->pulse_brt_up(amt);
        }
    }
    if (btns->raw & (1 << btns->brt_dn)) {
        Serial.println("down");
        if (!(btns->persist & (1 << btns->mode1))) { 
            leds->brt_down(amt);
        } else {
            leds->pulse_brt_down(amt);
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

void Control::set_speed() {
    int amt = 10;
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
    if ((delay_time - amt) >= 0) {
        delay_time -= amt;
    } else if (delay_time > 0 && amt > delay_time) {
        delay_time -= 1;
    }
}
void Control::spd_down(int amt) {
    if ((delay_time + amt) <= 1000) {
        delay_time += amt;
    }
}

void Control::dly() {
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