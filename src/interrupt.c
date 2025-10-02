#include <xc.h>

#include "../inc/motor.h"
#include "../inc/power.h"

void __interrupt() isr(void) {
    if (INTCON & _INTCON_RABIF_MASK) {
        power_detect_zero_crossing();
        motor_decrease_level();
        motor_increase_level();
        INTCON &= ~(_INTCON_RABIF_MASK);
    }
}
