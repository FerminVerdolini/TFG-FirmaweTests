#ifndef	_UART_H
#define	_UART_H

#define CR  0
#define CSR 0x14
#define RHR 0x18
#define THR 0x1C

#define RXRDY 1

//#define SIFIVE_E_UART0_IRQ 3
#define GR_UART_IRQ     (1)

// GRLIB TIMER
#define GR_TIMER_IRQ    (2)
#define GR_TIMER_COUNT  (2)

void uart_tx_enable();
void uart_rx_enable();
void outchar(char c);
void uart_rx_irq_enable();

//void _putc ( void* p, char c);

int32_t getcar();
 
void print(const char *s);

void print32(uint32_t data);

#endif /* _UART_H */

