#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"


void kmain(void) {
int32_t car;

     uart_tx_enable();
     uart_rx_enable();
     
     print("Init kmain!\n");
     

     do {       
        do { car = getcar(); } while( car == -1 );
        
        outchar( (char)car );
     } while( car != 'q' );


     print("\nEnd kmain...\n");          
}
