#include "slu_leds.h"

// 0 for prod board, 1 for prototype board
const bool PROTO = 0;

// shift register structs
ici* ic_btns = new ici();
ico* ic_leds = new ico();

// led control
Lights* LEDS = new Lights(ic_leds);

// global buttons state
Buttons* BTNS = new Buttons(ic_btns);

// optional LCD screen
LCD595* LCD = new LCD595(PIN_LCD_SE, PIN_LCD_CL, PIN_LCD_LA);

// main control section
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
    CTRL->lcd->begin();
    CTRL->lcd->setCursor(0, 0);
    CTRL->lcd->print("startup complete");
}

void loop() {
    CTRL->run();
}
