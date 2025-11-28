#include "slu_leds.h"

// shift register structs
// ici* ic_btns = new ici(PIN_ICI_PL, PIN_ICI_CP, PIN_ICI_SE, PIN_ICI_CE);
ici* ic_btns = new ici();
// ico* ic_leds = new ico(PIN_ICO_SE, PIN_ICO_OE, PIN_ICO_LA, PIN_ICO_CL);
ico* ic_leds = new ico();
// 
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

    CTRL->btns->brt_dn = 0;
    CTRL->btns->brt_up = 1;
    CTRL->btns->mode1 = 2;
    CTRL->btns->mode2 = 3;
    CTRL->btns->mode3 = 4;
    CTRL->btns->mult1 = 5;
    CTRL->btns->mult2 = 6;
    CTRL->btns->rev = 7;

    CTRL->leds->onoff = true;
    CTRL->leds->ic->fill();

    CTRL->delay_time = 100;

    CTRL->leds->lvl = 250;
    CTRL->leds->out();

    CTRL->lcd->begin();
    CTRL->lcd->setCursor(0,0);
    CTRL->lcd->print("HELLO");

    CTRL->lcd->setCursor(0,1); 
    CTRL->lcd->print("WORLD");

}

void loop() {
    CTRL->Set();
    delay(CTRL->delay_time);
}