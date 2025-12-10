#include "slu_leds.h"

// 0 for prod board, 1 for prototype board
const bool PROTO = 0;

ici* ic_btns = new ici();
ico* ic_leds = new ico();
Lights* LEDS = new Lights(ic_leds);
Buttons* BTNS = new Buttons(ic_btns);
LCD595* LCD = new LCD595(PIN_LCD_SE, PIN_LCD_CL, PIN_LCD_LA);
Control* CTRL = new Control(BTNS, LEDS, LCD, PIN_PWR_SW);

void setup() {
    Serial.begin(9600);

    if (PROTO) {
        setup_pins(PINS_IN_PROTO,  PINS_IN_COUNT_PROTO,  INPUT);
        setup_pins(PINS_OUT_PROTO, PINS_OUT_COUNT_PROTO, OUTPUT);    
    } else {
        setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
        setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    }

    CTRL->leds->off();
    CTRL->leds->set_bit_order();

    CTRL->lcd->begin();
    CTRL->lcd->println("startup complete", 0);
}

void loop() {
    CTRL->run();
}

void Control::run() {
    if (!digitalRead(pwr_sw)) {
        lcd->clear();
        lcd->println("leds off", 0);
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

    lcd->clear();

    set_brightness();
    lcd->printvar_u8("brt: ", (uint8_t)~leds->lvl, 0); 

    set_speed();
    lcd->printvar_i("spd: ", delay_time, 1);

    dly();
}