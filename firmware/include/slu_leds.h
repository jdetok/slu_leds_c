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

// 74HC595
struct ico {
    uint8_t data;
    uint8_t out;
    uint8_t latch;
    uint8_t clock;

    uint8_t bitmask[NUM_SR];

    ico();
    bool is_full();
    void clear();
    void empty();
    void fill();
    void set_bit(uint8_t pos, bool add); // = vs. |=
    void shift();
    void pulse_pin(uint8_t clk_latch);
};

// Lights brightness control
class Lights {
public: 
    ico* ic;
    uint8_t minm; // minimum brightness (0-255, higher the number, LOWER the brighness)
    uint8_t maxm; // maximum brightness (0-255, lower the brighter)
    int dir; // direction for pulse (1 or -1)
    uint8_t lvl; // brightness level
    uint8_t pulse_max;
    uint8_t total_bits;

    Lights(ico* ic, int min_brt, int max_brt);
    void off();
    void out();
    void brt_up(int amt);
    void brt_down(int amt);
    void pulse_brt_up(int amt);
    void pulse_brt_down(int amt);
    void solid();
    void pulse();  
    void chase(uint8_t pos);
    void chase4(uint8_t pos);
};

// 74HC165
struct ici {
    uint8_t load;
    uint8_t cp;
    uint8_t data;
    uint8_t ce;

    ici();
    uint8_t read();
};

// EIGHT BUTTONS - state is stored in a uint8_t, each bit used as a flag
class Buttons {
public:    
    ici* ic;
    uint8_t persist;
    uint8_t lastp;
    uint8_t raw;
    uint8_t last;

    uint8_t brt_up;
    uint8_t brt_dn;
    uint8_t mode1;
    uint8_t mode2;
    uint8_t mode3;
    uint8_t spd_up;
    uint8_t spd_dn;
    uint8_t rev;

    Buttons(ici* ic);
    void update();
};

class Control {
public:
    Buttons* btns;
    Lights* leds;
    LCD595* lcd;
    int pwr_sw;

    int delay_time;

    uint8_t chase_idx;

    Control(Buttons* b, Lights* l, LCD595* lc, uint8_t pwr_sw);
    void run();
    void dly();
    int amt_to_change();
    void set_brightness();
    void set_speed();
    void spd_up(int amt);
    void spd_down(int amt);
    void update_chase_idx(bool rev);
};

// pin setup - uses arrays and sizes from above
void setup_pins(const int* pins_arr, size_t count, uint8_t mode);

void printB(uint8_t b);

#endif