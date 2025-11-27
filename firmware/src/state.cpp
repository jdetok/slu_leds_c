#include "slu_leds.h"

bool check_pwr_sw(bool current, uint8_t brt) {
    bool onoff = digitalRead(PIN_PWR_SW);
    if (onoff != current) {
        if (onoff) {
            analogWrite(PIN_ICO_OE, brt);
            Serial.println("turning ofn");
            leds_onoff(true);
            return true;
        } else {
            digitalWrite(PIN_ICO_OE, HIGH);
            Serial.println("turning off");
            leds_onoff(false);
            return false;
        }
    } else {
        return onoff;
    }
}


uint8_t button_state() {
    // pulse load pin
    digitalWrite(PIN_ICI_PL, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ICI_PL, HIGH);
    delayMicroseconds(5);
    
    digitalWrite(PIN_ICI_CP, HIGH);
    digitalWrite(PIN_ICI_CE, LOW);
    uint8_t incoming = shiftIn(PIN_ICI_SE, PIN_ICI_CP, MSBFIRST);
    digitalWrite(PIN_ICI_CE, HIGH);
    return incoming;
}

bool check_button(uint8_t state, int btn) {
    return state & (1 << btn);
}