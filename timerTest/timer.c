#include <stdint.h>

#include "timer.h"

#define SCALER_IDX            0
#define SCALER_RELOAD_IDX     1
#define CONFIG_IDX            2

#define COUNTER1_IDX          4
#define COUNTER1_RELOAD_IDX   5
#define COUNTER1_CONTROL_IDX  6

volatile uint32_t * const timer_regs= (uint32_t *)0xFC000000;

void timer_set_scaler(  uint32_t scaler )
{
   timer_regs[ SCALER_IDX ] = scaler;
}

void timer_set_scaler_reload( uint32_t reload )
{
   timer_regs[ SCALER_RELOAD_IDX ] = reload;
}

void timer_set_configuration( uint32_t conf )
{
   timer_regs[ CONFIG_IDX ] = conf;
}

void timer1_set_counter( uint32_t count )
{
   timer_regs[ COUNTER1_IDX ] = count;
}

void timer1_set_reload( uint32_t reload )
{
   timer_regs[ COUNTER1_RELOAD_IDX ] = reload;
}

void timer1_set_control( uint32_t control )
{
   timer_regs[ COUNTER1_CONTROL_IDX ] = control;
}

void timer1_clear_pending()
{
   timer_regs[ COUNTER1_CONTROL_IDX ] |= GPTIMER_INT_PENDING;
}


