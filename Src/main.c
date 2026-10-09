#include "main.h"
#include <stdint.h>
#include "stm32l4xx.h"
#include "RCCDriver.h"
#include "I2CDriver.h"

int main(void) {
    enableAPB1I2CClk(1U, 1U);
    configureDigitalNoiseFilter(1U);
    toggleI2C1PeripheralEnable(1U);
    
}