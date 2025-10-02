#include <xc.h>

#include "../inc/motor.h"
#include "../inc/power.h"
#include "../inc/led.h"
#include "../inc/utils.h"

void led_init(void) {
    /* Set pins as output. */
    TRISA &= ~(LED1_TRISA | LED5_TRISA);
    TRISC &= ~(LED2_TRISC | LED3_TRISC);
    TRISB &= ~(LED4_TRISB | LEDP_TRISB);

    /* Set pins as digit output. */
    ANSEL &= ~(_ANSEL_ANS3_MASK);
    ANSELH &= ~(_ANSELH_ANS10_MASK);
}

void led_acquire_all(void) {
    PORTA |= LED1_PORTA | LED5_PORTA;
    PORTC |= LED2_PORTC | LED3_PORTC;
    PORTB |= LED4_PORTB;
}

void led_release_all(void) {
    PORTA &= ~(LED1_PORTA | LED5_PORTA);
    PORTC &= ~(LED2_PORTC | LED3_PORTC);
    PORTB &= ~(LED4_PORTB);
}

void led_release(void) {
    switch(motor_get_current_level()) {
        case MOTOR_LEVEL_1:
            PORTA &= ~(LED1_PORTA);
            break;
        case MOTOR_LEVEL_2:
            PORTC &= ~(LED2_PORTC);
            break;
        case MOTOR_LEVEL_3:
            PORTC &= ~(LED3_PORTC);
            break;
        case MOTOR_LEVEL_4:
            PORTB &= ~(LED4_PORTB);
            break;
        case MOTOR_LEVEL_5:
            PORTA &= ~(LED5_PORTA);
            break;
        default:
            break;
    }
}

void led_p_acquire(void) {
    PORTB &= ~(LEDP_PORTB);
}

void led_p_release(void) {
    PORTB |= LEDP_PORTB;
}

void led_blink(uint8_t seconds) {
    /* Blink using all available LEDs. */
    uint8_t total_iter = seconds * 1000 / HALF_CYCLE - 1;
    uint8_t iter = total_iter;

    unsigned step = map(PULSE_DELAY_PERIPHERAL, 0, PULSE_DELAY_PERIPHERAL, 0, total_iter);

    /* Aqua LED should be always turned on, because the pulse regulates its brightness. */
    led_p_release();
    led_release_all();

    while (iter) {
        if (zero_crossing_detected) {
            zero_crossing_detected = 0;

            unsigned percent = map(step, 0, total_iter, 0, PULSE_DELAY_PERIPHERAL);

            delay_ms(PULSE_DELAY_PERCENT(percent));
            power_produce_pulse();

            if (iter > total_iter / 2) {
                step += 2;
            } else {
                step -= 2;
            }

            --iter;
        }
    }

    /* By default, motor control LEDs are turned off. */
    led_acquire_all();
}
