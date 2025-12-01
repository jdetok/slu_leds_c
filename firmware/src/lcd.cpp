#include "lcd.h"

#define RS_BIT 0
#define E_BIT  2
#define D4_BIT 4
#define D5_BIT 5
#define D6_BIT 6
#define D7_BIT 7

LCD595::LCD595(uint8_t dataPin, uint8_t clkPin, uint8_t latchPin)
    : _data(dataPin), _clk(clkPin), _latch(latchPin) {
        // begin();
        // setCursor(0, 0);
    }

void LCD595::begin() {
    pinMode(_data, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_latch, OUTPUT);

    delay(50);

    write4(0x03, false); delay(5);
    write4(0x03, false); delay(5);
    write4(0x03, false); delay(1);
    write4(0x02, false);

    send(0x28, false);
    send(0x0C, false);
    send(0x06, false);
    clear();
}

void LCD595::clear() {
    send(0x01, false);
    delay(2);
}

void LCD595::home() {
    send(0x02, false);
    delay(2);
}

void LCD595::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t row_addr[] = {0x00, 0x40};
    send(0x80 | (col + row_addr[row]), false);
}

void LCD595::print(const char* s) {
    while (*s) writeChar(*s++);
}

void LCD595::print(String s) {
    for (size_t i = 0; i < s.length(); i++)
        writeChar(s[i]);
}

void LCD595::writeChar(uint8_t ch) {
    send(ch, true);
}

void LCD595::send(uint8_t value, bool rs) {
    write4(value >> 4, rs);
    write4(value & 0x0F, rs);
}

void LCD595::write4(uint8_t nibble, bool rs) {
    uint8_t b = 0;

    if (rs) b |= (1 << RS_BIT);
    if (nibble & 0x1) b |= (1 << D4_BIT);
    if (nibble & 0x2) b |= (1 << D5_BIT);
    if (nibble & 0x4) b |= (1 << D6_BIT);
    if (nibble & 0x8) b |= (1 << D7_BIT);

    // store the data bits + RS in _shadow
    _shadow = b;

    // now pulse E while keeping data and RS
    pulseEnable();
}

void LCD595::pulseEnable() {
    // E high
    shiftOutRaw(_shadow | (1 << E_BIT));
    delayMicroseconds(1);

    // E low
    shiftOutRaw(_shadow & ~(1 << E_BIT));
    delayMicroseconds(40);  // command settle
}

void LCD595::shiftOutRaw(uint8_t b) {
    // just shift out without modifying _shadow
    digitalWrite(_latch, LOW);
    for (int i = 7; i >= 0; i--) {
        digitalWrite(_clk, LOW);
        digitalWrite(_data, (b >> i) & 1);
        digitalWrite(_clk, HIGH);
    }
    digitalWrite(_latch, HIGH);
}

void LCD595::shiftOutByte(uint8_t b) {
    _shadow = b;       // remember last state
    shiftOutRaw(b);
}
