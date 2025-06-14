#include <stdint.h>

#include "uart.h"


//Estructura de datos que permite acceder a los registros de la //UART de LEON3

struct UART_regs
{
	/** \brief UART  Data Register */
	volatile uint32_t Data;   	/* 0x80000100 */
	/** \brief UART  Status Register */
	volatile uint32_t Status; 	/* 0x80000104 */
	/** \brief UART  Control Register */
	volatile uint32_t Ctrl; 	/* 0x80000108 */
	/** \brief UART  Scaler Register */
	volatile uint32_t Scaler; 	/* 0x8000010C */
};

//********************************************************
//STATUS REGISTER MASKS

//!LEON3 UART DATA READY
#define riscv_UART_DR  (0x01)

//!LEON3 UART A TX FIFO is full
#define riscv_UART_TFF (0x200)

//!LEON3 UART A TX FIFO is empty
#define riscv_UART_TFE  (0x004)

#define LEON_UART_RE    0x00000001 /* RX enable */
#define LEON_UART_TE    0x00000002 /* TX enable */
#define LEON_UART_LB 	0x00000080 /* Loop Back enable */
#define LEON_UART_RI    0x00000004 /* Receiver interrupt enable */

volatile struct UART_regs * const pUART_REGS= (struct UART_regs *)0xFC001000;

//**********************************************************************************
//#define riscv_UART_TF_IS_FULL()

#define riscv_UART_TF_IS_FULL() (riscv_UART_TFF & pUART_REGS->Status)


void uart_tx_enable()
{
	pUART_REGS->Ctrl |= LEON_UART_TE;
}

void uart_rx_enable()
{
	pUART_REGS->Ctrl |= LEON_UART_RE;
}
 
void uart_rx_irq_enable()
{
	pUART_REGS->Ctrl |= LEON_UART_RI;
}

void uart_rx_irq_disable()
{
	pUART_REGS->Ctrl &= ~LEON_UART_RI;
}

void uart_loopback_enable()
{
	pUART_REGS->Ctrl |= LEON_UART_LB;
}
 
void outchar(char c) {
	uint32_t write_timeout=0;

	while( (riscv_UART_TF_IS_FULL()) && (write_timeout < 0xAAAAA))
	{
		write_timeout++;
	}

	if(write_timeout <  0xAAAAA)
		pUART_REGS->Data=c;

	return;
}

int32_t getcar() {
	int32_t uart_rx_data;
	
	if ( riscv_UART_DR & pUART_REGS->Status)
	{
		uart_rx_data=pUART_REGS->Data;
	}
	else
	{
		uart_rx_data= -1;
	}

 	return uart_rx_data;
}

void print(const char *s) {
    while(*s != '\0') {
        outchar(*s);
        s++;
    }
}

void print32(uint32_t data) {

uint32_t mask = 0xF0000000;
uint8_t  digit;
int i;
    
    for (i=7;i>=0;i--)
    {   
        digit = (data & mask) >> (i*4);
        
        if ( digit < 10 )
        {
            outchar( digit + '0' );
        }
        else
        {
            outchar( (digit - 10) + 'A' );
        }
        
        mask = mask >> 4;       
    }
}

