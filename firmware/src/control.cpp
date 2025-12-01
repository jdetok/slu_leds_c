#include "slu_leds.h"

Control::Control(
    Buttons* b, 
    Lights* l, 
    LCD595* lc,
    uint8_t pwr_sw
) : btns(b), leds(l), lcd(lc), pwr_sw(pwr_sw), sr_bits(0), 
    total_bits(NUM_SR * 8), chase_idx(0),
    mode_solid(0b00111000),
    mode_pulse(0b00100000),
    mode_chase(0b00010000) {};

void Control::Run() {
// power switch off
    if (!digitalRead(pwr_sw)) {
        Serial.println("switched off");
        onoff_now = false;
        if (onoff_last) {
            Serial.println("off");
            leds->ic->empty();
            leds->off();
        }
        onoff_last = false;
        return;
    }
    // power switch on
    onoff_now = true;
    if (!(onoff_last)) {
        leds->ic->fill();
        Serial.println("turned on");

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("LEDs on");
    }
    onoff_last = true;
    
    // READ BUTTONS
    btns->update();
    printB(btns->persist);

    // buttons 345 not pressed
    if (!(btns->persist & mode_solid)) {
        Serial.println("normal mode")   ;
        set_brightness();
        leds->out();
    }

    if (btns->persist & (1 << btns->mode1)) {
        Serial.println("pulse on");
        leds->pulse();
        leds->out();
    }
    
    if (btns->persist & (1 << btns->mode2)) {
        Serial.println("chaser on");
        bit_chaser_2(btns->persist & (1 << btns->rev));
        set_brightness();
        leds->out();
    }
    // run delay
    set_speed();
    Serial.println(delay_time);
    dly();
}

void Control::Set() {
    // power switch off
    if (!digitalRead(pwr_sw)) {
        Serial.println("switched off");
        onoff_now = false;
        if (onoff_last) {
            Serial.println("off");
            leds->ic->empty();
            leds->off();
        }
        onoff_last = false;
        return;
    }
    // power switch on
    onoff_now = true;
    if (!(onoff_last)) {
        Serial.println("on");
        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("LEDs on");
        leds->ic->fill();
    }
    onoff_last = true;
    
    btns->update();
    printB(btns->persist);

    // check for normal mode
    if (!(btns->persist & mode_solid)) {
        Serial.println("normal mode")   ;
        set_brightness();
        leds->out();
    }

    if (btns->persist & (1 << btns->mode1)) {
        Serial.println("pulse on");
        leds->pulse();
    }
    if (btns->persist & (1 << btns->mode2)) {
        Serial.println("chaser on");
        bit_chaser(false);
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

void Control::bit_chaser(bool rev) {
    uint8_t total_bits = NUM_SR * 8;

    for (uint8_t step = 0; step < total_bits; step++) {
        btns->update();
        if (btns->changed()) {
            return;
        }
        
        uint8_t pos = rev ? (total_bits - 1 - step) : step;

        leds->ic->set_bit(pos);

        // leds->ic->mask = (1UL << pos);
        
        leds->ic->shift_frame();

        set_brightness();
        leds->out();

        dly();
    }
}
void Control::bit_chaser_2(bool rev) {
    leds->ic->set_bit(chase_idx);
    leds->ic->shift_frame();

    if (rev) {
        if (chase_idx == 0) {
            chase_idx = total_bits;
        }
        chase_idx--;
    } else {
        chase_idx++;
        if (chase_idx >= total_bits) {
            chase_idx = 0;
        }
    }
}