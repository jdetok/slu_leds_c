#include "slu_leds.h"

// global LED brightness struct
brightness Brightness;
brightness* BRT = &Brightness;

// global buttons state
state State = {0, 0, {0, 1, 2, 3, 4, 5, 6, 7}};
state* BTN_STATE = &State;

void setup() {
    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low
    // CURRENT = true; 
    BRT->onoff = true;
    leds_onoff(BRT->onoff);
    
    // set default min/max brightness & starting pulse direction
    BRT->min = 255;
    BRT->max = 155;
    BRT->dir = -1;
}

void loop() {
    pulse(BRT);

    // check if power switch is switched
    bool newOnOff = check_pwr_sw(BRT->onoff, BRT->lvl);
    if (newOnOff != BRT->onoff) {
        leds_onoff(newOnOff);
    }

    // Serial.print("brightness: ");
    // Serial.println(BRT); 
    
    uint8_t state = button_state();

    // Serial.print("button state: ");
    // Serial.println(state); 

    bool btn_state = check_button(state, BTN_STATE->buttons[3]);
    
    Serial.print("button ");
    Serial.print(BTN_STATE->buttons[3]);
    Serial.println(btn_state ? " on" : " off");


    delayMicroseconds(1);
}