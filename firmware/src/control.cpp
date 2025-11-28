#include "slu_leds.h"

Control::Control(Buttons* b, Lights* l, uint8_t pwr_sw) : btns(b), leds(l), pwr_sw(pwr_sw) {};

void Control::Set() {
    int sw_status = digitalRead(pwr_sw);
    if (sw_status == LOW) {
        onoff_now = false;
        if (onoff_last) {
            Serial.println("off");
            leds->ic->empty();
            leds->off();
        }
        onoff_last = false;
        return;
    } else {
        onoff_now = true;
        if (!(onoff_last)) {
            Serial.println("on");
            leds->ic->fill();
        }
        onoff_last = true;
    }
    btns->update();
    set_brightness();    
    if ((btns->pressed(btns->mode1))) {
        Serial.println("pulse on");
        delay_time = 10;
        leds->pulse();
    } else {
        delay_time = 75;
    }
    
}

void Control::set_brightness() {
    int amt = amt_to_change();
    if (btns->raw & (1 << btns->brt_up)) {
        Serial.println("up");
        brt_up(amt);
    }
    if (btns->raw & (1 << btns->brt_dn)) {
        Serial.println("down");
        brt_down(amt);
    }
    leds->out();
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