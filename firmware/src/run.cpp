#include "slu_leds.h"

void Control::run() {
    if (!digitalRead(pwr_sw)) {
        Serial.println("off");
        leds->off();
        return;
    }

    btns->update();
    
    if (btns->persist & (1 << btns->mode1)) {
        leds->pulse();
    }
    if (btns->persist & (1 << btns->mode2)) {
        set_chase_mode();
        bit_chaser();
        update_chase_idx(btns->persist & (1 << btns->rev));
    } else {
        leds->solid();
    }
    print_mask(leds->ic->bitmask); 
    set_brightness();
    set_speed();
    
    lcd->clear();
    lcd->setCursor(0, 0); lcd->print("brt: "); lcd->print(String((uint8_t)~leds->lvl)); 
    lcd->setCursor(0, 1); lcd->print("spd: "); lcd->print(String(delay_time)); 

    dly();
}