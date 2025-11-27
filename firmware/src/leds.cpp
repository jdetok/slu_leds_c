#include "slu_leds.h"

LED_Brightness::LED_Brightness(int min_brt, int max_brt) {
    minm = min_brt;
    maxm = max_brt;
    dir = -1;
}

void leds_onoff(bool on) {
    digitalWrite(PIN_ICO_LA, LOW); // latch low
    int mask = on ? 0xFF : 0x00; 

    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(PIN_ICO_SE, PIN_ICO_CL, MSBFIRST, mask);
    }
    digitalWrite(PIN_ICO_LA, HIGH); // latch high (output the bits)
    // delay(1000);
}

void LED_Brightness::pulse() {
    if (lvl >= minm) {
        dir = -1;
    } else if (lvl == maxm) {
        dir = 1;
    }
    lvl += dir;
    analogWrite(PIN_ICO_OE, lvl);
}

bool check_pwr_sw(bool current, uint8_t brt) {
    bool onoff = digitalRead(PIN_PWR_SW);
    if (onoff != current) {
        if (onoff) {

            analogWrite(PIN_ICO_OE, brt);
            Serial.println("turning on");
            leds_onoff(true);
            return true;
        } else {
            analogWrite(PIN_ICO_OE, brt);
            Serial.println("turning off");
            leds_onoff(false);
            return false;
        }
    } else {
        return onoff;
    }
}

void LED_Brightness::adjust(int btn_up, int btn_down, uint8_t b) {
    int amt = 1;
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

    if (b & (1 << btn_up)) {
        Serial.println(lvl);
        if ((lvl - amt) >= 0) {
            lvl -= amt;
        } else if (lvl > 0 && amt > lvl) {
            lvl -= 1;
        }
    } else if (b & (1 << btn_down)) {
        Serial.println(lvl);
        if ((lvl + amt) <= 255) {
            Serial.println("ok");
            lvl += amt;
        }
    }
    analogWrite(PIN_ICO_OE, lvl);
}