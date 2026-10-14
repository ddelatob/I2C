#include "main.h"
#include <stdint.h>
#include "stm32l4xx.h"
#include "RCCDriver.h"
#include "I2CDriver.h"

int main(void) {
    enableAPB1I2CClk(1U, 1U);

    setI2C1ClockSource(2U);
    configureDigitalNoiseFilter(0U);
    configureAnalogNoiseFilter(0U);
    toggleI2C1PeripheralEnable(1U);
    
}