#ifndef SLU_LEDS_H
#define SLU_LEDS_H

#include <Arduino.h>

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

extern const int PINS_IN[];;
extern const size_t PINS_IN_COUNT;
extern const int PINS_OUT[];
extern const size_t PINS_OUT_COUNT ;

void leds_onoff(bool on);
void setup_pins(const int* pins_arr, size_t count, uint8_t mode);
bool check_pwr_sw(bool current, uint8_t brt);
void pulse();
uint8_t button_state();
bool check_button(uint8_t state, int btn);
#endif