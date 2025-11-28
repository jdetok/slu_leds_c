#include "slu_leds.h"

// global Lightsrightness struct
// brightness Brightness;
Lights* LEDS = new Lights(255, 155);

// global buttons state
Buttons* BTNS = new Buttons();

void setup() {
    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low

    LEDS->onoff = true;
    leds_onoff(LEDS->onoff);
}

void loop() {
    BTNS->update();
    LEDS->adjust(3, 2, BTNS->raw);
    
    // Serial.print("button state: ");
    // printB(Buttons>persist);

    delay(100);
    // delayMicroseconds(1);
}