//#include <riscv_types.h>
#include <stddef.h>
#include <stdint.h>
#include "riscv-csr.h"
#include "plic.h"
#include "dispatch.h"
#include "clinc.h"

#include "uart.h"

// Function pointer type
typedef void (*handler_t)(void);

// 32 function pointer
handler_t __ext_handlers[32] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};  

// Timer function pointer
handler_t __local_timer_handler = NULL;

uint64_t timecmp_gap = 0;

void irq_dispatch(uint32_t code)
{
	if (code == RISCV_MACHINE_TIMER_IRQ)
	{
		/*
			mtime register contains the number of cycles counted from the
			system’s real-time clock, in SPIKE simulator runs at 10Mhz	
		*/

		*p_clinc_timecmp += timecmp_gap;	// Next time IRQ

		if (__local_timer_handler)
		{
			__local_timer_handler();
		}
	}
    else if (code == RISCV_MACHINE_EXTERNAL_IRQ)
	{
		// Get IRQ
		uint32_t source = p_plic_context[0].claim_complete;

		//print("IRQ dispatch: "); print32( source ); print("\n");

		// Do IRQ processing 
		if ( __ext_handlers[source] != NULL )
		{
			__ext_handlers[source](); // Call IRQ handler
		}

        p_plic_context[0].claim_complete = source;
    }
	else // TO COMPLETE: Add SW interrupt handling
	{
		//printf("IRQ code not implemented: %d\n", code );
		print("IRQ code not implemented: "); print32(code); print("\n");
    }
}

void syscall_dispatch(uint32_t trap, uint32_t param)
{
	// TO COMPLETE
	//printf("Syscall: %d dispatch Param: %d\n", trap, param);
	print("Syscall: "); print32( trap ); print(", "); print32( param ); print("\n");
}

void excepcion_dispatch(uint32_t code)
{
	// TO COMPLETE
	// printf("Exception: %d dispatch\n", code);
	print("Exception: "); print32( code ); print("\n");
}

void install_irq_handler( uint32_t irq_num, void (*f)(void) )
{
	if ( irq_num > 31 )
	{
//		printf("IRQ num too big: %d\n", irq_num);
		print("IRQ num too big: "); print32(irq_num); print("\n");
		return;
	}

	__ext_handlers[irq_num] = f;
}

void uninstall_irq_handler( uint32_t irq_num )
{
	if ( irq_num > 31 )
	{
		return;
	}

	__ext_handlers[irq_num] = NULL;
}

void install_local_timer_handler( void (*f)(void) )
{
	__local_timer_handler = f;
}

void uninstall_local_timer_handler()
{
	__local_timer_handler = NULL;
}

void local_timer_set_gap( uint64_t gap )
{
	*p_clinc_timecmp = *p_clinc_mtime + gap;
	timecmp_gap = gap;
}

void syscall(uint32_t N, uint32_t param )
{
	register uint32_t a0 asm ("a0") = N;
	register uint32_t a1 asm ("a1") = param;
	asm volatile("ecall" : : "r" (a0), "r" (a1) );
}
