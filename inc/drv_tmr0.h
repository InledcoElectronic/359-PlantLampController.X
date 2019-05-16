/* 
 * File:   drv_tmr0.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月16日, 下午2:36
 */

#ifndef DRV_TMR0_H
#define	DRV_TMR0_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum tmr0_clk_cs {
        TMR0_CLK_T0CKIPPS_TRUE = 0,
        TMR0_CLK_T0CKIPPS_INVERTED,
        TMR0_CLK_FOSC_4,
        TMR0_CLK_HFINTOSC,
        TMR0_CLK_LFINTOSC,
        TMR0_CLK_MFINTOSC_500,
        TMR0_CLK_SOSC,  
        TMR0_CLK_LC1_OUT         
    }tmr0_clk_cs_t;
    
    typedef enum tmr0_ckps {
        TMR0_CKPS_1 = 0,
        TMR0_CKPS_2,
        TMR0_CKPS_4,
        TMR0_CKPS_8,
        TMR0_CKPS_16,
        TMR0_CKPS_32,
        TMR0_CKPS_64,
        TMR0_CKPS_128,
        TMR0_CKPS_256,
        TMR0_CKPS_512,
        TMR0_CKPS_1024,
        TMR0_CKPS_2048,
        TMR0_CKPS_4096,
        TMR0_CKPS_8192,   
        TMR0_CKPS_16384,
        TMR0_CKPS_32768 
    }tmr0_ckps_t;
    
    typedef enum tmr0_outps {
        TMR0_OUTPS_1 = 0,
        TMR0_OUTPS_2,
        TMR0_OUTPS_3,
        TMR0_OUTPS_4, 
        TMR0_OUTPS_5,
        TMR0_OUTPS_6, 
        TMR0_OUTPS_7,
        TMR0_OUTPS_8,
        TMR0_OUTPS_9,
        TMR0_OUTPS_10,
        TMR0_OUTPS_11, 
        TMR0_OUTPS_12,
        TMR0_OUTPS_13, 
        TMR0_OUTPS_14,
        TMR0_OUTPS_15, 
        TMR0_OUTPS_16        
    }tmr0_outps_t;
    
    typedef void(*tmr0_handler_t)();


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR0_H */

