/*
 * File:   drv_tmr0.h
<<<<<<< HEAD
 * Author: liruya
 *
 * Created on 2019年5月16日, 下午3:22
=======
 * Author: niumiaomiao
 *
 * Created on 2019年5月16日, 下午2:36
>>>>>>> 61c9d203afad3756857c34e816409de748396cf4
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

