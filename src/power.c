#include <xc.h>

#include "../inc/motor.h"
#include "../inc/power.h"
#include "../inc/led.h"
#include "../inc/utils.h"

volatile uint8_t zero_crossing_detected;
volatile static uint8_t zero_crossing_status;

void power_init(void) {
    /* Sets pin as input. */
    TRISC |= POWER_TRISC;
    TRISB |= ZERO_TRISB;

    /* Sets pin as output. */
    TRISC &= ~PIT_TRISC;

    /* Initialze pins as digital I/O. */
    ANSEL &= ~(_ANSEL_ANS6_MASK);
    ANSELH &= ~(_ANSELH_ANS9_MASK | _ANSELH_ANS11_MASK);

    /* Enable detecting interrupt. */
    INTCON |= _INTCON_RABIE_MASK | _INTCON_GIE_MASK;
    IOCB |= _IOCB_IOCB5_MASK;
}

void power_produce_pulse(void) {
    PORTC |= PIT_PORTC;
    __delay_us(PULSE_DURATION);
    PORTC &= ~PIT_PORTC;
}

void power_detect_zero_crossing(void) {
    uint8_t tmp = ZERO_TRISB & ZERO_PORTB;

    if (zero_crossing_status != tmp) {
        zero_crossing_status = !zero_crossing_status;
        zero_crossing_detected = 1;

        if (!IS_POWER_OFF) {
            /* Maybe it isn't the right place, because waiting inside interrput is bad. */
            power_produce_pulse();
        }
    }
}

void power_shutdown(void) {
    if (IS_POWER_OFF) {
        led_acquire_all();
        motor_reset_delay();

        while (IS_POWER_OFF) {
            /* Stay in "safe mode". */
            if (zero_crossing_detected) {
                zero_crossing_detected = 0;

                delay_ms(PULSE_DELAY_PERCENT(PULSE_DELAY_PERIPHERAL));
                power_produce_pulse();
            }
        }

        motor_reset_level();
        led_release();
    }
}
