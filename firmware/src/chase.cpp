#include "slu_leds.h"

void Lights::set_bit_order() {
    uint8_t end_pos_2 = 15;
    uint8_t end_pos_3 = 23;
    uint8_t end_pos_4 = 31;

    for (uint8_t i = 0; i < max_chase_idx; i++) {
        uint8_t real_pos = i;
        uint8_t end_pos = 0;
        if ((i > end_pos_2 && i <= end_pos_3) || 
        (i >= total_bits && i < (total_bits + 8))
        ) {
            end_pos = end_pos_4;
        } else if ((i > end_pos_3 && i <= end_pos_4) || i >= total_bits + 8) {
            end_pos = end_pos_3;
        }

        if (end_pos > 0) {
            real_pos = (end_pos - i % 8);
        }

        bit_order[i] = real_pos;
        Serial.println(bit_order[i]);
    }
    Serial.println("done mapping custom order");
}

void Lights::chase(uint8_t pos, uint8_t lit_bits) {
    ic->clear();

    int add_bit_pos = 2;
    
    if (pos >= total_bits || (pos > 15 && pos < 32)) {
        add_bit_pos *= -1;
    }

    ic->set_bit(bit_order[pos], 0);

    for (uint8_t i = 0; i < lit_bits; i++) {
        ic->set_bit(bit_order[pos + (add_bit_pos * i)], 1);
    }

    ic->shift();
}