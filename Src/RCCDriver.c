#include "RCCDriver.h"
#include <stdint.h>
#include "stm32l432xx.h"
#include "pins.h"

void enableAPB1I2CClk(uint8_t I2CNum, uint8_t enableBit) {
    uint8_t offset = 20U;
    RCC->APB1ENR1 &= ~(0x3UL << (offset + I2CNum));
    RCC->APB1ENR1 |= (enableBit << (offset + I2CNum));
}

