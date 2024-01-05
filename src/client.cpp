#include <client.h>

int parceInt(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3){
    int command = r0 << 24;
    command |= r1 << 16;
    command |= r2 << 8;
    command |= r3;
    return command;
}