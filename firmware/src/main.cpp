#include "slu_leds.h"

bool ONOFF;

uint8_t BRT;
uint8_t MIN_BRT = 255;
uint8_t MAX_BRT = 155;
int DIR = -1;

// bool CURRENT;


void setup() {
    setup_pins(PINS_IN,  PINS_IN_COUNT,  INPUT);
    setup_pins(PINS_OUT, PINS_OUT_COUNT, OUTPUT);
    Serial.begin(9600);

    analogWrite(PIN_ICO_OE, 100); // set oe low
    // CURRENT = true; 
    ONOFF = true;
    leds_onoff(ONOFF);
    
    BRT = MIN_BRT; 
}

void loop() {
    pulse();

    // check if power switch is switched
    bool newOnOff = check_pwr_sw(ONOFF, BRT);
    if (newOnOff != ONOFF) {
        leds_onoff(newOnOff);
    }

    // Serial.print("brightness: ");
    // Serial.println(BRT); 
    
    uint8_t state = button_state();

    // Serial.print("button state: ");
    // Serial.println(state); 

    bool btn_state = check_button(state, 0);
    Serial.print("button is ");
    Serial.println(btn_state ? "on" : "off");


    delayMicroseconds(1);
}

void setup_pins(const int* pins_arr, size_t count, uint8_t mode) {
    for (size_t i = 0; i < count; i++) {
        pinMode(pins_arr[i], mode);
    }
}


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

void pulse() {
    if (BRT >= MIN_BRT) {
        DIR = -1;
    } else if (BRT == MAX_BRT) {
        DIR = 1;
    }
    BRT += DIR;
    analogWrite(PIN_ICO_OE, BRT);
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