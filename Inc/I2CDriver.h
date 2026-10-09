#pragma once
#include <stdint.h>

void toggleI2C1PeripheralEnable(uint8_t PEbit);
void configureDigitalNoiseFilter(uint8_t minKerCkPeriods);