#include "slu_leds.h"


void Lights::chase_around(uint8_t pos) {
    ic->clear();

    uint8_t real_pos = pos;
    uint8_t end_pos = 0;
    uint8_t end_pos_2 = 15;
    uint8_t end_pos_3 = 23;
    uint8_t end_pos_4 = 31;
    
    if ((pos > end_pos_2 && pos <= end_pos_3) || 
        (pos >= total_bits && pos < (total_bits + 8))
    ) {
        end_pos = end_pos_4;
    } else if ((pos > end_pos_3 && pos <= end_pos_4) || pos >= total_bits + 8) {
        end_pos = end_pos_3;
    }

    if (end_pos > 0) {
        real_pos = (end_pos - pos % 8);
    }

    ic->set_bit(real_pos, 0);
    ic->shift();
}