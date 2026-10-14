#pragma once
#include <stdint.h>

void toggleI2C1PeripheralEnable(uint8_t PEbit);
void configureDigitalNoiseFilter(uint8_t minKerCkPeriods);
void configureAnalogNoiseFilter(uint8_t ANFOFFBit);
uint32_t getTFilterNanoSec(void);
uint8_t getTI2CClkNanoSec(void);
void setSCLHighPeriod(uint8_t period);
void setSCLLowPeriod(uint8_t period);