#pragma once
#include <Arduino.h>

class LCD595 {
public:
    LCD595(uint8_t dataPin, uint8_t clkPin, uint8_t latchPin);

    void begin();
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void print_to_display(String s);
    void println(String s, int row);
    void printvar_i(String s, int v, int row);
    void printvar_u8(String s, uint8_t v, int row);
    void writeChar(uint8_t ch);

private:
    uint8_t _shadow = 0;   // add to class    
    void send(uint8_t value, bool rs);
    void write4(uint8_t nibble, bool rs);
    void shiftOutByte(uint8_t b);
    void pulseEnable();
    void shiftOutRaw(uint8_t b);

    uint8_t _data, _clk, _latch;
};

