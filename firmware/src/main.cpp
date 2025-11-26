#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

// arduino pins for 74HC595 (lights)
#define PIN_ICO_SE 2
#define PIN_ICO_OE 3
#define PIN_ICO_LA 4
#define PIN_ICO_CL 5

// arduino pins for 74HC165 (buttons)
#define PIN_ICI_PL 6
#define PIN_ICI_CP 7
#define PIN_ICI_SE 8
#define PIN_ICI_CE 9

// arduino pins for 74HC595 (optional external LCD)
#define PIN_LCD_LA 10
#define PIN_LCD_CL 11
#define PIN_LCD_SE 12

// arduino pins for power switch
#define PIN_PWR_SW 13

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}