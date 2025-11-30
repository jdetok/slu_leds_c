#include "slu_leds.h"

Control::Control(
    Buttons* b, 
    Lights* l, 
    LCD595* lc,
    uint8_t pwr_sw
) : btns(b), leds(l), lcd(lc), pwr_sw(pwr_sw), sr_bits(0), total_bits(NUM_SR * 8) {};

void Control::Set() {
    int sw_status = digitalRead(pwr_sw);
    if (sw_status == LOW) {
        onoff_now = false;
        if (onoff_last) {
            Serial.println("off");
            lcd->clear();
            lcd->setCursor(0,0);
            lcd->print("LEDs off");
            leds->ic->empty();
            leds->off();
        }
        onoff_last = false;
        return;
    } else {
        onoff_now = true;
        if (!(onoff_last)) {
            Serial.println("on");
            lcd->clear();
            lcd->setCursor(0,0);
            lcd->print("LEDs on");
            leds->ic->fill();
        }
        onoff_last = true;
    }
    btns->update();
    printB(btns->persist);
    set_brightness();    
    if ((btns->pressed(btns->mode1))) {
        Serial.println("pulse on");
        delay_time = 10;
        leds->pulse();
    } else {
        delay_time = 75;
    }
    if ((btns->pressed(btns->mode2))) {
        Serial.println("chaser on");
        delay_time = 100;
        bit_chaser(false);
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
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("brt up x");
    lcd->print(String(amt));
    lcd->setCursor(0,1);
    lcd->print("level: ");
    lcd->print(String(leds->lvl));
}
void Control::brt_down(int amt) {
    if ((leds->lvl + amt) <= 255) {
        leds->lvl += amt;
    }
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("brt down x");
    lcd->print(String(amt));
    lcd->setCursor(0,1);
    lcd->print("level: ");
    lcd->print(String(leds->lvl));
}

void Control::dly() {
    delay(delay_time);
}

void Control::bit_chaser(bool rev) {
    uint8_t total_bits = NUM_SR * 8;

    for (uint8_t step = 0; step < total_bits; step++) {
        btns->update();
        if (btns->changed()) {
            return;
        }
        set_brightness();
        
        uint8_t pos = rev ? (total_bits - 1 - step) : step;
        sr_bits = (1UL << pos);
        
        shift_frame();
        dly();
    }
}

void Control::shift_frame() {
    for (int8_t i = 31; i >= 0; i--) {
        if (sr_bits & (1UL << i)) {
            PORTD |= (1 << leds->ic->data);
        } else {
            PORTD &= ~( 1 << leds->ic->data);
        }
        leds->ic->pulse_pin(0); // clock pulse
    }
    leds->ic->pulse_pin(1); // latch pulse
}