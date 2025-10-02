#pragma once

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include <xc.h>

#define LED1_TRISA (_TRISA_TRISA4_MASK)
#define LED2_TRISC (_TRISC_TRISC5_MASK)
#define LED3_TRISC (_TRISC_TRISC4_MASK)
#define LED4_TRISB (_TRISB_TRISB7_MASK)
#define LED5_TRISA (_TRISA_TRISA5_MASK)
#define LEDP_TRISB (_TRISB_TRISB4_MASK)

#define LED1_PORTA (_PORTA_RA4_MASK)
#define LED2_PORTC (_PORTC_RC5_MASK)
#define LED3_PORTC (_PORTC_RC4_MASK)
#define LED4_PORTB (_PORTB_RB7_MASK)
#define LED5_PORTA (_PORTA_RA5_MASK)
#define LEDP_PORTB (_PORTB_RB4_MASK)

void led_init(void);
void led_acquire_all(void);
void led_release_all(void);
void led_release(void);
void led_p_acquire(void);
void led_p_release(void);
void led_blink(uint8_t seconds);

#ifdef	__cplusplus
}
#endif /* __cplusplus */
