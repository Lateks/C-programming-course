#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTEMASK 0xffL

char* byte_to_binary(unsigned int byte) {
    char* binary = calloc(9, sizeof(char));
    binary += 8;
    *binary = '\0';

    for (int i = 0; i < 8; i++)
        *--binary = byte & 1 << i ? '1' : '0';
    
    return binary;
}

// Ex. 1
void print_bin(uint32_t number) {
    unsigned int byte;
    char* bytes[4];

    for (int i = 3; i >= 0; i--) {
        byte = number >> i*8 & BYTEMASK;
        bytes[i] = byte_to_binary(byte);
    }

    printf("%s %s %s %s\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}

// Ex. 2
uint16_t make_16bit(uint8_t least_significant, uint8_t most_significant) {
    return most_significant << 8 | least_significant;
}

// Ex. 3
uint32_t make_32bit(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    return make_16bit(byte3, byte4) << 16 | make_16bit(byte1, byte2);
}

int main(void) {
    print_bin(0);
    print_bin(1);
    print_bin(2);
    print_bin(43);
    print_bin(123456789);

    print_bin(make_16bit(7, 1));
    print_bin(make_32bit(1, 2, 3, 4));

    exit(0);
}
