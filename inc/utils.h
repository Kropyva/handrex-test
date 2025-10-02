#pragma once

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/** Default frequency of the MCU. */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ (4000000)
#endif

static inline void delay_ms(unsigned milliseconds) {
   while(milliseconds > 0) {
        --milliseconds;
        __delay_us(990);
   }
}

static inline unsigned map(unsigned x, unsigned in_min, unsigned in_max, unsigned out_min, unsigned out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#ifdef	__cplusplus
}
#endif /* __cplusplus */
