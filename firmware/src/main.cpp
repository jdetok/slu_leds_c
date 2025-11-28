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

// selector
Control* CTRL = new Control(BTNS, LEDS);

void setup() {
    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low

    CTRL->btn_brt_down = 2;
    CTRL->btn_brt_up = 3;
}

void loop() {
    CTRL->btns->update();
    CTRL->adjust_brightness();

    delay(100);
}