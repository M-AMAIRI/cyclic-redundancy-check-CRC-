#include <stdio.h>
#include <stdint.h>
#include <string.h>

void crc8PushByte(uint8_t *crc, uint8_t ch) {
    uint8_t i;

    *crc = *crc ^ ch;

    for (i=0; i<8; i++) {
        if (*crc & 1) {
            *crc = (*crc >> 1) ^0x8c;
        }
        else {
            *crc = (*crc >> 1);
        }
    }
}

uint8_t crc8PushBlock(uint8_t *pcrc, uint8_t *block, uint16_t count) {
    uint8_t crc = pcrc ? *pcrc : 0;

    for (; count>0; --count, block++) {
        crc8PushByte(&crc, *block);
    }
    if (pcrc) *pcrc = crc;

    return crc;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        int len = strlen(argv[i]);
        uint8_t* buffer = new uint8_t[len];
        memcpy(buffer, argv[i], len);
        printf("%s %d\n", argv[i], crc8PushBlock(0, buffer, len));
    }
}
