/* 
 * File:   drv_common.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月10日, 下午7:42
 */

#ifndef DRV_COMMON_H
#define	DRV_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
    
#define _XTAL_FREQ                      16000000
    
//全局中断使能
#define GlobalInterruptEnable()         (INTCONbits.GIE = 1)
//禁止全局中断
#define GlobalInterruptDisable()        (INTCONbits.GIE = 0)
//外设中断使能
#define PeripheralInterruptEnable()     (INTCONbits.PEIE = 1)
//禁止外设中断使能
#define PerioheralInterruptDisable()    (INTCONbits.PEIE = 0)

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_COMMON_H */

