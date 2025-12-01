
#include "slu_leds.h"

// print all 8 bits in a byte
void printB(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        Serial.print((b >> i) & 1);
    }
    Serial.println();
}

void print_mask(uint8_t mask[NUM_SR]) {
    for (int8_t i = 0; i < NUM_SR; i++) {
        for (int8_t b = 7; b >= 0; b--) {
            Serial.print((mask[i] >> b) & 1);
        }
    }
    Serial.println();
}
