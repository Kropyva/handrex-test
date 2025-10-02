#pragma once

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include <xc.h>

#define PLUS_TRISA   (_TRISA_TRISA0_MASK)
#define MINUS_TRISA  (_TRISA_TRISA3_MASK)
#define FILTER_TRISC (_TRISC_TRISC3_MASK)
#define OUT1_TRISA   (_TRISA_TRISA2_MASK)
#define OUT2_TRISA   (_TRISA_TRISA1_MASK)

#define PLUS_PORTA   (_PORTA_RA0_MASK)
#define MINUS_PORTA  (_PORTA_RA3_MASK)
#define FILTER_PORTC (_PORTC_RC3_MASK)
#define OUT1_PORTA   (_PORTA_RA2_MASK)
#define OUT2_PORTA   (_PORTA_RA1_MASK)

#define IS_FILTER_OFF (PORTC & FILTER_PORTC)

/** Delay time in percent. */
typedef enum motor_delay_e {
    MOTOR_DELAY_0   = 85,
    MOTOR_DELAY_1   = 78,
    MOTOR_DELAY_2   = 69,
    MOTOR_DELAY_3   = 61,
    MOTOR_DELAY_4   = 53,
    MOTOR_DELAY_5   = 45,
    MOTOR_DELAY_MAX = 0xFF
} __attribute__((packed)) motor_delay_t;

/** Amount of motor levels. */
typedef enum motor_level_e {
    MOTOR_LEVEL_1   = 0,
    MOTOR_LEVEL_2   = 1,
    MOTOR_LEVEL_3   = 2,
    MOTOR_LEVEL_4   = 3,
    MOTOR_LEVEL_5   = 4,
    MOTOR_LEVEL_MAX = 0xFF
} __attribute__((packed)) motor_level_t;

void motor_init(void);
void motor_decrease_level(void);
void motor_increase_level(void);
void motor_reset_level(void);
void motor_reset_delay(void);
void motor_restore_delay(void);
void motor_filter(void);
void motor_rotate(void);
motor_level_t motor_get_current_level(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */
