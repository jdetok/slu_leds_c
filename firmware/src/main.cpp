#include "slu_leds.h"

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

    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);

    CTRL->leds->lvl = 250;

    CTRL->lcd->print("startup complete");
}

void loop() {
    CTRL->run();
}