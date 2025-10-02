#pragma once

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include <xc.h>

/** When 50 Hz is used, the half-cycle duration is 10 ms. */
#define HALF_CYCLE (10)

/* Pulse duration in microseconds. */
#define PULSE_DURATION (20)

/** Retrieves a pulse time after 0-point crossing. */
#define PULSE_DELAY_PERCENT(percent) (HALF_CYCLE * (percent) / 100)

/** Generate a pulse to produce the voltage required to enable the peripherals.
 *  Offset the pulse after 0-crossing detection, specified as a percentage.
 */
#define PULSE_DELAY_PERIPHERAL (66)

#define ZERO_TRISB  (_TRISB_TRISB5_MASK)
#define POWER_TRISC (_TRISC_TRISC2_MASK)
#define PIT_TRISC   (_TRISC_TRISC7_MASK)

#define ZERO_PORTB  (_PORTB_RB5_MASK)
#define POWER_PORTC (_PORTC_RC2_MASK)
#define PIT_PORTC   (_PORTC_RC7_MASK)

#define IS_POWER_OFF    (PORTC & POWER_PORTC)

extern volatile uint8_t zero_crossing_detected;

void power_init(void);
void power_produce_pulse(void);
void power_detect_zero_crossing(void);
void power_shutdown(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */
