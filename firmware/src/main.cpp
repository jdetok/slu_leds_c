#include "slu_leds.h"

// global LED brightness struct
// brightness Brightness;
LED_Brightness* LEDS = new LED_Brightness(255, 155);

// global buttons state
BTN_State* BTNS = new BTN_State();

void setup() {
    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low

    LEDS->onoff = true;
    leds_onoff(LEDS->onoff);
    
    // set default min/max brightness & starting pulse direction
    
}

void loop() {
    // check if power switch is switched
    bool newOnOff = check_pwr_sw(LEDS->onoff, LEDS->lvl);
    if (newOnOff != LEDS->onoff) {
        Serial.println("onoff");
        leds_onoff(newOnOff);
    }

    BTNS->update();

    LEDS->adjust(0, 4, BTNS->raw);

    // Serial.print("button state: ");
    // printB(BTN_STATE->persist);
    
    // if (BTN_STATE->persist > 0) {
//     pulse(BRT);    
    // }

    delay(100);
    // delayMicroseconds(1);
}