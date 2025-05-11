#include "gpio.h"

#define GPIO_PIN      22
#define GPIO_PIN_MASK (1U << GPIO_PIN)

void delay(void) {
    for (volatile int i = 0; i < 10000; ++i) { }
}

void exit(int code) {
    // syscall exit (for QEMU `-semihosting`)
    asm volatile("mv a0, %0\n\t"
                 "li a7, 93\n\t"
                 "ecall"
                 :
                 : "r"(code)
                 : "a0", "a7");
    __builtin_unreachable();
}

void kmain(void) {
    // Configura el pin como salida
    uint32_t dir = gpio_dir_read();
    dir |= GPIO_PIN_MASK;
    gpio_dir_write(dir);

    // Escribe 1 y espera
    uint32_t val = gpio_read();
    val |= GPIO_PIN_MASK;
    gpio_write(val);
    delay();

    uint32_t input = gpio_read();
    if ((input & GPIO_PIN_MASK) == 0) {
        exit(1); // Falla: no se lee alto
    }

    // Escribe 0 y espera
    val &= ~GPIO_PIN_MASK;
    gpio_write(val);
    delay();

    input = gpio_read();
    if (input & GPIO_PIN_MASK) {
        exit(2); // Falla: no se lee bajo
    }

    exit(0); // Test OK
}
