#include "gpio.h"
#include "uart.h"
#include <unistd.h>

#define GPIO_PIN      22
#define GPIO_PIN_MASK (1U << GPIO_PIN)

void delay(void) {
    for (volatile int i = 0; i < 10000; ++i) { }
}

void kmain(void) {
    uart_tx_enable();
    uart_rx_enable();
    print("GPIO test started\n");
    uint32_t dir = gpio_dir_read();
    dir |= GPIO_PIN_MASK;
    gpio_dir_write(dir);

    uint32_t val = gpio_read();
    val |= GPIO_PIN_MASK;
    gpio_write(val);
    delay();

    uint32_t input = gpio_read();
    if ((input & GPIO_PIN_MASK) == 0) {
        print("GPIO high test FAILED\n");
        return;
    }

    val &= ~GPIO_PIN_MASK;
    gpio_write(val);
    delay();

    input = gpio_read();
    if (input & GPIO_PIN_MASK) {
        print("GPIO low test FAILED\n");
        return;
    }

    print("GPIO test PASSED\n");
}
