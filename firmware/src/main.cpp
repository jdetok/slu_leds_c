#include <Arduino.h>
#include "slu_leds.h"


 
bool ONOFF;
bool CURRENT;

void setup_pins(int pins_arr[], int* inout) {
    for (int i = 0; i < (sizeof(pins_arr)) / sizeof(pins_arr[0]); i++) {
        pinMode(pins_arr[i], inout);
    }
}

void leds_onoff(bool on) {
    digitalWrite(PIN_ICO_LA, LOW); // latch low
    int mask = on ? 0xFF : 0x00; 

    for (int i = 0; i < NUM_SR; i++) {
        shiftOut(PIN_ICO_SE, PIN_ICO_CL, MSBFIRST, mask);
    }
    digitalWrite(PIN_ICO_LA, HIGH); // latch high (output the bits)
    delay(1000);
}

bool check_pwr_sw(bool current) {
    bool onoff = digitalRead(PIN_PWR_SW);
    if (onoff != current) {
        if (onoff) {
            Serial.println("turning ofn");
            leds_onoff(true);
            return true;
        } else {
            Serial.println("turning off");
            leds_onoff(false);
            return false;
        }
    } else {
        return onoff;
    }
}

void setup() {
    setup_pins(PINS_IN, INPUT);
    setup_pins(PINS_OUT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low
    CURRENT, ONOFF = true;
    leds_onoff(CURRENT);
}

void loop() {
    Serial.println("testing");
    ONOFF = check_pwr_sw(CURRENT);
}