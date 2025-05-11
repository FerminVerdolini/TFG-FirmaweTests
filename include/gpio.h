#ifndef	_GPIO_H
#define	_GPIO_H

#include <stdint.h> 

#define INPUT_REG  0
#define OUTPUT_REG 1
#define DIR_REG    2

#define SW_0_MASK 0x00000001 // First  switch
#define SW_1_MASK 0x00000002 // Second switch
#define SW_2_MASK 0x00000004 // Third  switch
#define SW_3_MASK 0x00000008 // Fourth switch

#define LED_0_MASK 0x00010000 // First  led
#define LED_1_MASK 0x00020000 // Second led
#define LED_2_MASK 0x00040000 // Third  led
#define LED_3_MASK 0x00080000 // Fourth led


uint32_t gpio_read();
void gpio_write( uint32_t val );
void gpio_dir_write( uint32_t val );
uint32_t gpio_dir_read();

#endif /* _GPIO_H */

