#include <stdint.h>
#include "uart.h"
#include "dispatch.h"
#include "riscv-csr.h"

char test_char = 'X';

void uart_rx_handler(void)
{
	char car = getcar();
    if (car == test_char) {
        uart_rx_irq_disable(); 
        print("\nUART irq loopback test PASSED\n");
    } else {
        print("UART loopback test FAILED\n");
        print("Received: ");
        outchar((char)car);
        print("\n");
    }   
    
}

void startup( void );


void kmain(void)
{
    startup();

    uart_tx_enable();
    uart_rx_enable();

    // print("🛠️ UART IRQ Test\n");
    syscall(1,2);

   	install_irq_handler( GR_UART_IRQ, uart_rx_handler );
    uart_rx_irq_enable();
	plic_irq_unmask( GR_UART_IRQ );  // PLIC UART irq unmask
	enable_ext_irq();    	                // Enable MIE.MEI
	enable_irq();	          // Global interrupt enable

    uart_loopback_enable();

    outchar(test_char);

    while (1) {
        asm volatile("wfi");
    }
}