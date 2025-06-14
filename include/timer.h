#ifndef	_TIMER_H
#define	_TIMER_H

// GRLIB TIMER
#define GR_TIMER_IRQ    (2)
#define GR_TIMER_COUNT  (2)

#define CPU_CLK         10000000 

/* GPTimer Config register fields */
#define GPTIMER_ENABLE      (1 << 0)
#define GPTIMER_RESTART     (1 << 1)
#define GPTIMER_LOAD        (1 << 2)
#define GPTIMER_INT_ENABLE  (1 << 3)
#define GPTIMER_INT_PENDING (1 << 4)
#define GPTIMER_CHAIN       (1 << 5) /* Not supported */
#define GPTIMER_DEBUG_HALT  (1 << 6) /* Not supported */

/* Memory mapped register offsets */
#define SCALER_OFFSET         0x00
#define SCALER_RELOAD_OFFSET  0x04
#define CONFIG_OFFSET         0x08
#define COUNTER_OFFSET        0x00
#define COUNTER_RELOAD_OFFSET 0x04
#define TIMER_BASE            0x10

#define SCALER_IDX            0
#define SCALER_RELOAD_IDX     1
#define CONFIG_IDX            2

#define COUNTER1_IDX          4
#define COUNTER1_RELOAD_IDX   5
#define COUNTER1_CONTROL_IDX  6

#define COUNTER2_IDX          8
#define COUNTER2_RELOAD_IDX   9
#define COUNTER2_CONTROL_IDX  10

void timer_set_scaler(  uint32_t scaler );
void timer_set_scaler_reload( uint32_t reload );
void timer_set_configuration( uint32_t conf );

void timer1_set_counter( uint32_t count );
void timer1_set_reload( uint32_t reload );
void timer1_set_control( uint32_t control );
void timer1_clear_pending();

#endif /* _TIMER_H */

