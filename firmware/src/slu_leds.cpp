#include "slu_leds.h"


void leds_onoff(bool on) {
    digitalWrite(PIN_ICO_LA, LOW); // latch low
    int mask = on ? 0xFF : 0x00; 

    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(PIN_ICO_SE, PIN_ICO_CL, MSBFIRST, mask);
    }
    digitalWrite(PIN_ICO_LA, HIGH); // latch high (output the bits)
    // delay(1000);
}

const int PINS_IN[] = {
    PIN_ICI_SE,
    PIN_PWR_SW
};
const size_t PINS_IN_COUNT = sizeof(PINS_IN) / sizeof(PINS_IN[0]);

const int PINS_OUT[] = {
    PIN_ICO_SE,
    PIN_ICO_OE,
    PIN_ICO_LA,
    PIN_ICO_CL,
    PIN_ICI_PL,
    PIN_ICI_CP,
    PIN_ICI_CE,
    PIN_LCD_LA,
    PIN_LCD_CL,
    PIN_LCD_SE
};
const size_t PINS_OUT_COUNT = sizeof(PINS_OUT) / sizeof(PINS_OUT[0]);
