#pragma once

#include <stdint.h>

void SendEOI(uint8_t Irq);
void RemapPIC(int offset1, int offset2);
void DisablePIC(void);