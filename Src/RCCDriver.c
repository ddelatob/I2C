#include "RCCDriver.h"
#include <stdint.h>
#include "stm32l432xx.h"
#include "pins.h"

void enableAPB1I2CClk(uint8_t I2CNum, uint8_t enableBit) {
    uint8_t offset = 20U;
    RCC->APB1ENR1 &= ~(0x3UL << (offset + I2CNum));
    RCC->APB1ENR1 |= (enableBit << (offset + I2CNum));
}
/**
 * @brief Allows setting of clock range with MSIRANGE[3:0] in RCC_CSR register or RCC_CR register.
 * 
 * Write 0 has no effect, MSIRGSEL at 0 after standby or reset.
 * 
 * @param bitState 0 MSI range provided by RCC_CSR register, 1 MSI range provided by RCC_CR register.
 * 
 */
void setMSIRGSEL(uint8_t bitState)
{
    RCC->CR |= (0x1UL << 3U);
}
/**
 * @brief Sets MSIRANGE dynamically (NOT MSISRANGE)
 * 
 * @pre To modifyy MSIRANGE, MSI must be off (MSION=0) or MSI must be ready
 *  (MSIRDY=1). MSIRANGE must not be modified when MSI is on and NOT ready
 *  (MISON=1) and (MSIRDY=0).
 */
void setMSIRANGE(uint8_t setting)
{
    if (!(RCC->CR & (0x1UL << 1U)) && (RCC->CR & (0x1UL << 0U))) {return;}
    
    uint8_t setting = 0;
    if (RCC->CR & (0x1UL << 3U))
    {
        RCC->CR &= ~(0xFUL << 4U);
        RCC->CR |= (setting << 4U);
    }
}

uint8_t getSysClkNanoSec() 
{
    // Need to complete other clocks.
    uint8_t SW = RCC->CFGR & (0x3UL << 0U);
    uint8_t clkSpdMHz = 0U;
    switch (SW)
    {
    case 0x0UL:
        //HSI16
        clkSpdMHz = 0;
        break;
    case 0x1UL:
        clkSpdMHz = getMSIMHz();
        break;
    case 0x2UL:
        //HSE
        clkSpdMHz = 0;
        break;
    case 0x3UL:
        clkSpdMHz = 0;
        break;
    }
    return clkSpdMHz;
}

//fix
uint8_t getMSIMHz()
{
    uint8_t range = RCC->CR & (0xFUL << 4U);
    switch (range)
    {
    case 0x0UL:
        return 1U;
    case 0x1UL:
        return 1U;
    case 0x2UL:
        return 1U;
    case 0x3UL:
        return 1U;
    case 0x4UL:
        return 1U;
    case 0x5UL:
        return 2U;
    case 0x6UL:
        return 4U;
    case 0x7UL:
        return 8U;
    case 0x8UL:
        return 16U;
    case 0x9UL:
        return 24U;
    case 0xAUL:
        return 32U;
    case 0xBUL:
        return 48U;
    }
}