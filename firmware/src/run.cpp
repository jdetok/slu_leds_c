#include "slu_leds.h"

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

    Serial.print(leds->lvl);
    Serial.print(" | ");
    Serial.println(leds->maxm);
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