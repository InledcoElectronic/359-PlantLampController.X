/* 
 * File:   drv_tmr0.h
 * Author: liruya
 *
 * Created on 2019年5月16日, 下午3:22
 */

#ifndef DRV_TMR0_H
#define	DRV_TMR0_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef void (*tmr0_interrupt_callback_t)();
    
    extern void tmr0_init();
    extern void tmr0_start();
    extern void tmr0_isr();
    extern void tmr0_set_interrupt_callback(tmr0_interrupt_callback_t callback);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR0_H */

