// #ifndef SLU_LEDS_H
#define SLU_LEDS_H
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

const int PINS_IN[] = { PIN_ICI_SE, PIN_PWR_SW };
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
