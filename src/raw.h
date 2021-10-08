#include <stdint.h>

uint8_t * store_word(uint8_t * buffer, uint8_t * data);
uint8_t * store_half_word(uint8_t * buffer, uint8_t * data);
uint8_t * store_byte(uint8_t * buffer, uint8_t * data);
void unpack_section(uint8_t * raw_buffer, uint8_t * out_buffer);