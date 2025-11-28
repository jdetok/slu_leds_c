#ifndef SLU_LEDS_H
#define SLU_LEDS_H

#include <Arduino.h>
#include "lcd.h"

// arduino pins for 74HC595 (lights)
#define PIN_ICO_SE 2 // IC pin 14 (SERIAL)
#define PIN_ICO_OE 3 // IC pin 13 (OUTPUT ENABLE)
#define PIN_ICO_LA 4 // IC pin 12 (RCLK)
#define PIN_ICO_CL 5 // IC pin 11 (SRCLK)


// arduino pins for 74HC165 (buttons)
#define PIN_ICI_PL 6 // IC pin 1 
#define PIN_ICI_CP 7 // IC pin 2
#define PIN_ICI_SE 8 // IC pin 7 (QH)
#define PIN_ICI_CE 9 // IC pin 15 


// arduino pins for 74HC595 (optional external LCD)
#define PIN_LCD_LA 10 // IC pin 12 (RCLK)
#define PIN_LCD_CL 11 // IC pin 11 (SRCLK)
#define PIN_LCD_SE 12 // IC pin 14 (SERIAL)

// arduino pins for power switch
#define PIN_PWR_SW 13

// number of shift registers
#define NUM_SR 4

// arrays and sizes for pin setup
extern const int PINS_IN[];;
extern const size_t PINS_IN_COUNT;
extern const int PINS_OUT[];
extern const size_t PINS_OUT_COUNT ;

// 74HC165
struct ico {
    uint8_t data;
    uint8_t out;
    uint8_t latch;
    uint8_t clock;

    // ico(int se, int oe, int la, int cl);
    ico() : data(PIN_ICO_SE), out(PIN_ICO_OE), latch(PIN_ICO_LA), clock(PIN_ICO_CL) {};
    void empty();
    void fill();
};
// 74HC165
struct ici {
    uint8_t load;
    uint8_t cp;
    uint8_t data;
    uint8_t ce;
    // ici(int pl, int cp, int se, int ce);
    ici() : load(PIN_ICI_PL), cp(PIN_ICI_CP), data(PIN_ICI_SE), ce(PIN_ICI_CE) {};
    uint8_t read();
};

// Lightsrightness control
class Lights {
public: 
    ico* ic;
    uint8_t minm; // minimum brightness (0-255, higher the number, LOWER the brighness)
    uint8_t maxm; // maximum brightness (0-255, lower the brighter)
    int dir; // direction for pulse (1 or -1)
    uint8_t lvl; // brightness level
    bool onoff;

    Lights(ico* ic, int min_brt, int max_brt);
    void off();
    void out();
    void pulse();
    void bit_chaser(bool rev);
};

// EIGHT BUTTONS - state is stored in a uint8_t, each bit used as a flag
class Buttons {
public:    
    ici* ic;
    uint8_t persist;
    uint8_t raw;
    uint8_t last;

    uint8_t brt_up;
    uint8_t brt_dn;
    uint8_t mode1;
    uint8_t mode2;
    uint8_t mode3;
    uint8_t mult1;
    uint8_t mult2;
    uint8_t rev;

    Buttons(ici* ic);
    void update();
    bool pressed(int btn);
};

class Control {
public:
    Buttons* btns;
    Lights* leds;
    LCD595* lcd;

    int pwr_sw;

    bool onoff_now;
    bool onoff_last;

    int delay_time;

    Control(Buttons* b, Lights* l, LCD595* lc, uint8_t pwr_sw);
    void Set();
    void set_brightness();
    int amt_to_change();
    void brt_up(int amt);
    void brt_down(int amt);

};

// pin setup - uses arrays and sizes from above
void setup_pins(const int* pins_arr, size_t count, uint8_t mode);

void printB(uint8_t b);

#endif