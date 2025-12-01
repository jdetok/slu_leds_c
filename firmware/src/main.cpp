#include "slu_leds.h"

// shift register structs
ici* ic_btns = new ici();
ico* ic_leds = new ico();

// led control
Lights* LEDS = new Lights(ic_leds, 255, 155);

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

    CTRL->delay_time = 100;
    CTRL->leds->lvl = 250;

    CTRL->lcd->begin();
    CTRL->lcd->setCursor(0,0);
    CTRL->lcd->print("HELLO");

    CTRL->lcd->setCursor(0,1); 
    CTRL->lcd->print("WORLD");
}

void loop() {
    CTRL->run();
}