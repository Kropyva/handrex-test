#include "../inc/motor.h"
#include "../inc/power.h"
#include "../inc/led.h"
#include "../inc/utils.h"

volatile static motor_delay_t current_delay;
volatile static motor_level_t current_level;
volatile static motor_level_t previous_level;
volatile static uint8_t porta_input_status;

static motor_delay_t delay_table[] = {
    [MOTOR_LEVEL_1] = MOTOR_DELAY_1,
    [MOTOR_LEVEL_2] = MOTOR_DELAY_2,
    [MOTOR_LEVEL_3] = MOTOR_DELAY_3,
    [MOTOR_LEVEL_4] = MOTOR_DELAY_4,
    [MOTOR_LEVEL_5] = MOTOR_DELAY_5,
};

void motor_init(void) {
    /* Sets pins as input. */
    TRISA |= PLUS_TRISA | MINUS_TRISA;
    TRISC |= FILTER_TRISC;

    /* Set pins as output. */
    TRISA &= ~(OUT1_TRISA | OUT2_TRISA);
    PORTA &= ~(OUT1_PORTA | OUT2_PORTA);

    /* Initialze pins as digital I/O. */
    ANSEL &= ~(_ANSEL_ANS0_MASK | _ANSEL_ANS1_MASK | _ANSEL_ANS2_MASK | _ANSEL_ANS7_MASK);

    /* Save the current state of the input pins at the initialization time. */
    porta_input_status |= (PORTA & PLUS_PORTA) | (PORTA & MINUS_PORTA);

    /* Enable detecting interrupt. */
    INTCON |= _INTCON_RABIE_MASK | _INTCON_GIE_MASK;
    IOCA |= _IOCA_IOCA0_MASK | _IOCA_IOCA3_MASK;

    current_delay = MOTOR_DELAY_MAX;
    current_level = MOTOR_LEVEL_MAX;
    previous_level = MOTOR_LEVEL_MAX;
}

void motor_reset_delay(void) {
    current_delay = MOTOR_DELAY_0;
}

void motor_restore_delay(void) {
    if (current_delay > delay_table[current_level]) {
        --current_delay; 
    } else if (current_delay < delay_table[current_level]) {
        ++current_delay;
    }
}

void motor_reset_level(void) {
    uint8_t tmp = porta_input_status ^ (PLUS_PORTA | MINUS_PORTA);

    switch (tmp) {
        case PLUS_PORTA:
            current_level = MOTOR_LEVEL_5;
            break;
        case MINUS_PORTA:
            current_level = MOTOR_LEVEL_1;
            break;
        case PLUS_PORTA | MINUS_PORTA:
            /* fallthrough */
        default:
            current_level = MOTOR_LEVEL_3;
            break;
    }

    motor_reset_delay();
}

void motor_decrease_level(void) {
    uint8_t tmp = PORTA & MINUS_PORTA;

    if ((current_level > MOTOR_LEVEL_1) && ((porta_input_status & MINUS_PORTA) < tmp)) {
        --current_level;
    }

    porta_input_status = (porta_input_status & ~(MINUS_PORTA)) | tmp;
}

void motor_increase_level(void) {
    uint8_t tmp = PORTA & PLUS_PORTA;

    if ((current_level < MOTOR_LEVEL_5) && ((porta_input_status & PLUS_PORTA) < tmp)) {
        ++current_level;
    }

    porta_input_status = (porta_input_status & ~(PLUS_PORTA)) | tmp;
}


void motor_filter(void) {
    if (!IS_FILTER_OFF) {
        motor_reset_delay();

        while (!IS_FILTER_OFF && !IS_POWER_OFF) {
            led_acquire_all();
            delay_ms(500);
            led_release();
            delay_ms(500);
        }
    }
}

void motor_rotate(void) {
    if (previous_level != current_level) {
        previous_level = current_level;

        led_acquire_all();
        led_release();
    }

    if (IS_FILTER_OFF && !IS_POWER_OFF) {
        if (zero_crossing_detected) {
            zero_crossing_detected = 0;

            delay_ms(PULSE_DELAY_PERCENT(current_delay));

            PORTA |= OUT1_PORTA | OUT2_PORTA;
            __delay_us(PULSE_DURATION);
            PORTA &= ~(OUT1_PORTA | OUT2_PORTA);

            motor_restore_delay();
        }
    }
}

motor_level_t motor_get_current_level(void) {
    return current_level;
}
