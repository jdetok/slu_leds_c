#include "slu_leds.h"

Control::Control(Buttons* b, Lights* l, uint8_t pwr_sw) : btns(b), leds(l), pwr_sw(pwr_sw) {};

void Control::Set() {
    if (digitalRead(pwr_sw) == LOW) {
        leds->off();
        return;
    }
    btns->update();
    if (!btns->pressed(btns->mode1)) {
        adjust_brightness();
    } else {
        leds->pulse();
    }
    
}

void Control::adjust_brightness() {
    int amt = amt_to_change();
    if (btns->raw & (1 << btns->brt_up)) {
        brt_up(amt);
    }
    if (btns->raw & (1 << btns->brt_dn)) {
        brt_down(amt);
    }
    analogWrite(PIN_ICO_OE, leds->lvl);
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

void Control::brt_up(int amt) {
    if ((leds->lvl - amt) >= 0) {
        leds->lvl -= amt;
    } else if (leds->lvl > 0 && amt > leds->lvl) {
        leds->lvl -= 1;
    }
}
void Control::brt_down(int amt) {
    if ((leds->lvl + amt) <= 255) {
        leds->lvl += amt;
    }
}