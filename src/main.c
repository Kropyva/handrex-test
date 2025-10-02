#include <builtins.h>
#include <pic.h>
#include <xc.h>
#include <pic16f690.h>

#include "../inc/motor.h"
#include "../inc/power.h"
#include "../inc/led.h"

#pragma config FOSC = INTRCIO   /* Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN) */
#pragma config WDTE = OFF       /* Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register) */
#pragma config PWRTE = OFF      /* Power-up Timer Enable bit (PWRT disabled) */
#pragma config MCLRE = OFF      /* MCLR Pin Function Select bit (MCLR pin function is MCLR) */
#pragma config CP = OFF         /* Code Protection bit (Program memory code protection is disabled) */
#pragma config CPD = OFF        /* Data Code Protection bit (Data memory code protection is disabled) */
#pragma config BOREN = ON       /* Brown-out Reset Selection bits (BOR enabled) */
#pragma config IESO = ON        /* Internal External Switchover bit (Internal External Switchover mode is enabled) */
#pragma config FCMEN = OFF      /* Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled) */

/** Wait for N seconds before start-up application. */
#define MAIN_SECONDS_WAIT (2)

int main(void) {
    power_init();
    led_init();
    motor_init();

    led_blink(MAIN_SECONDS_WAIT);
    motor_reset_level();

    while (1) {
        power_shutdown();
        motor_filter();
        motor_rotate();
    }
}
