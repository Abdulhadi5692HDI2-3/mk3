#pragma once

#include <stdint.h>

typedef void (*isr_t)();
void InitIDT();
void IdtRegisterHandler(uint8_t Number, isr_t Handler);