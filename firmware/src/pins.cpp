#include "slu_leds.h"

const int PINS_IN[] = {
    PIN_ICI_SE,
    PIN_PWR_SW
};

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

const size_t PINS_IN_COUNT = sizeof(PINS_IN) / sizeof(PINS_IN[0]);
const size_t PINS_OUT_COUNT = sizeof(PINS_OUT) / sizeof(PINS_OUT[0]);

const int PINS_IN_PROTO[] = {
    PIN_PROTO_ICI_SE,
    PIN_PWR_SW
};

const int PINS_OUT_PROTO[] = {
    PIN_ICO_SE,
    PIN_ICO_OE,
    PIN_ICO_LA,
    PIN_ICO_CL,
    PIN_PROTO_ICI_PL,
    PIN_PROTO_ICI_CP,
    PIN_PROTO_ICI_CE,
    PIN_PROTO_LCD_LA,
    PIN_PROTO_LCD_CL,
    PIN_PROTO_LCD_SE
};

const size_t PINS_IN_COUNT_PROTO = sizeof(PINS_IN_PROTO) / sizeof(PINS_IN_PROTO[0]);
const size_t PINS_OUT_COUNT_PROTO = sizeof(PINS_OUT_PROTO) / sizeof(PINS_OUT_PROTO[0]);

void setup_pins(const int* pins_arr, size_t count, uint8_t mode) {
    for (size_t i = 0; i < count; i++) {
        pinMode(pins_arr[i], mode);
    }
}
