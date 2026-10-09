#pragma once
#include <stdint.h>

void toggleI2C1PeripheralEnable(uint8_t PEbit);
void configureDigitalNoiseFilter(uint8_t minKerCkPeriods);
void configureAnalogNoiseFilter(uint8_t ANFOFFBit);
uint8_t getTFilterNanoSec();
uint8_t getTI2CClkNanoSec();