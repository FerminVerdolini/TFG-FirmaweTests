#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"


void kmain(void) {
    uart_tx_enable();
    uart_rx_enable();
    
    uart_loopback_enable();
    char test_char = 'X';
    outchar(test_char);

    int32_t recv_char = -1;
    int timeout = 100000;

    while (timeout-- && recv_char == -1) {
        recv_char = getcar();
    }

    if (recv_char == test_char) {
        print("UART loopback test PASSED\n");
    } else {
        print("UART loopback test FAILED\n");
        print("Received: ");
        outchar((char)recv_char);
        print("\n");
    }    
}