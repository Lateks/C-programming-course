#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BYTEMASK 0xffL

char* byte_to_binary(unsigned int byte) {
    char* binary = calloc(9, sizeof(char));
    if (!binary) {
        fprintf(stderr, "Ran out of memory.\n");
        exit(1);
    }
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
    for (int i = 0; i < 4; i++)
        free(bytes[i]);
}

// Ex. 2
uint16_t make_16bit(uint8_t least_significant, uint8_t most_significant) {
    return ((uint16_t) most_significant) << 8 | least_significant;
}

// Ex. 3
uint32_t make_32bit(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    return ((uint32_t) make_16bit(byte3, byte4)) << 16 | make_16bit(byte1, byte2);
}

// Ex. 4
uint8_t read_lsb(FILE* f) {
    uint8_t byte = fgetc(f);
    return byte & 1;
}

// Ex. 5
uint8_t extract_byte(FILE* f) {
    uint8_t lsbyte = 0;
    for (int i = 0; i < 8; i++)
        lsbyte |= read_lsb(f) << i;
    return lsbyte;
}

// Ex. 6
uint32_t read_uint32(FILE* f) {
    uint8_t bytes[4];

    for (int i = 0; i < 4; i++)
        bytes[i] = fgetc(f);

    return make_32bit(bytes[0], bytes[1], bytes[2], bytes[3]);
}

// Ex. 7
uint32_t read_pixel_offset(FILE* f) {
    fseek(f, 0xa, SEEK_SET);

    return read_uint32(f);
}

// Ex. 8
void print_hidden_message(FILE* f) {
    uint32_t offset = read_pixel_offset(f);
    fseek(f, offset, SEEK_SET);

    uint8_t byte = extract_byte(f);
    while (byte) {
        printf("%c", byte);
        byte = extract_byte(f);
    }
    printf("\n");
}

int main(void) {
    print_bin(0);
    print_bin(1);
    print_bin(2);
    print_bin(43);
    print_bin(123456789);

    print_bin(make_16bit(7, 1));
    print_bin(make_32bit(1, 2, 3, 4));

    FILE* picture = fopen("whoa.bmp", "r");
    if (!picture)
        fprintf(stderr, "Could not open the picture file.\n");

    printf("extracted byte: %d\n", extract_byte(picture));
    printf("pixel offset: %d\n", read_pixel_offset(picture));

    print_hidden_message(picture);
    fclose(picture);

    exit(0);
}
