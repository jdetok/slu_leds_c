#include "slu_leds.h"

// input pins
const int PINS_IN[] = {
    PIN_ICI_SE,
    PIN_PWR_SW
};

// output pins
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

// counts 
const size_t PINS_IN_COUNT = sizeof(PINS_IN) / sizeof(PINS_IN[0]);
const size_t PINS_OUT_COUNT = sizeof(PINS_OUT) / sizeof(PINS_OUT[0]);

// run pinMode on each set of pins
void setup_pins(const int* pins_arr, size_t count, uint8_t mode) {
    for (size_t i = 0; i < count; i++) {
        pinMode(pins_arr[i], mode);
    }
}
