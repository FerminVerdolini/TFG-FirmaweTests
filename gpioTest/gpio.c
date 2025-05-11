#include <stdint.h>

#include "gpio.h"

volatile uint32_t *gpio_regs = (uint32_t *)0xFC083000;
//volatile uint32_t *gpio_regs = (uint32_t *)0x10012000;

uint32_t gpio_read()
{
   return gpio_regs[INPUT_REG];
}

void gpio_write( uint32_t val )
{
   gpio_regs[OUTPUT_REG]  = val;
}
 
void gpio_dir_write( uint32_t val )
{
   gpio_regs[DIR_REG]  = val;
}

uint32_t gpio_dir_read()
{
   return gpio_regs[DIR_REG];
}

