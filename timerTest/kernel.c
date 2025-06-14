#include <stdint.h>
#include "uart.h"
#include "dispatch.h"
#include "timer.h"
#include "riscv-csr.h"

volatile int irq_count = 0;

void gptimer_handler(void) {
    irq_count++;
    print("Tick!\n");
    timer1_clear_pending();
}

void startup( void );


int kmain(void) {

    startup();

    uart_tx_enable();
    uart_rx_enable();
    
    
    print("🕒 Starting Timer IRQ Test...\n");
    syscall(1,2);
    
    install_irq_handler( GR_TIMER_IRQ, gptimer_handler );	 
    plic_irq_unmask( GR_TIMER_IRQ );
    
    
    // Timer configurarion        
    timer_set_scaler_reload( 10 ); // timer clock is 10000000, 1us tick
    timer1_set_reload( 2000000 );
    timer1_set_control( GPTIMER_ENABLE | GPTIMER_RESTART | GPTIMER_INT_ENABLE );
    
    
    enable_ext_irq();    	          // Enable MIE.MEI
	enable_irq();    	          // Global interrupt enable
    

    print("⏳ Waiting for timer IRQs...\n");

    while (irq_count < 3) {
        asm volatile("wfi");
    }

    print("✅ Timer test PASSED\n");


    
    while (1) {
        asm volatile("wfi");
    }

    // return 0;
}


