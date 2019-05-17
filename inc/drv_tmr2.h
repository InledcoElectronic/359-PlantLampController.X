/* 
 * File:   drv_tmr2.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月11日, 下午2:40
 */

#ifndef DRV_TMR2_H
#define	DRV_TMR2_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum tmr2_clk_cs {
        TMR2_CLK_T2CKIPPS = 0,
        TMR2_CLK_FOSC_4,
        TMR2_CLK__FOSC,
        TMR2_CLK__HFINTOSC,                     //32MHz
        TMR2_CLK__LFINTOSC,
        TMR2_CLK__MFINTOSC_500,                 //500KHz
        TMR2_CLK__MFINTOSC_31,                  //31.25KHz     
        TMR2_CLK_SOSC,
        TMR2_CLK_CLKR,
        TMR2_CLK_NCO1_OUT,
        TMR2_CLK_ZCD1_OUT,
        TMR2_CLK_LC1_OUT,
        TMR2_CLK_LC2_OUT,
        TMR2_CLK_LC3_OUT,
        TMR2_CLK_LC4_OUT
    }tmr2_clk_cs_t;
    
    typedef enum tmr2_ckps {
        TMR2_CKPS_1 = 0,
        TMR2_CKPS_2,
        TMR2_CKPS_4,
        TMR2_CKPS_8,
        TMR2_CKPS_16,
        TMR2_CKPS_32,
        TMR2_CKPS_64,
        TMR2_CKPS_128   
    }tmr2_ckps_t;
    
    typedef enum tmr2_outps {
        TMR2_OUTPS_1 = 0,
        TMR2_OUTPS_2,
        TMR2_OUTPS_3,
        TMR2_OUTPS_4,
        TMR2_OUTPS_5,
        TMR2_OUTPS_6,
        TMR2_OUTPS_7,
        TMR2_OUTPS_8, 
        TMR2_OUTPS_9,  
        TMR2_OUTPS_10,  
        TMR2_OUTPS_11,  
        TMR2_OUTPS_12,  
        TMR2_OUTPS_13,  
        TMR2_OUTPS_14,  
        TMR2_OUTPS_15,
        TMR2_OUTPS_16       
    }tmr2_outps_t;
    
    typedef enum tmr2_mode {
        TMR2_MODE_FREE_PERIOD_SW_GATE_CTRL = 0,                     //软件门控
        TMR2_MODE_FREE_PERIOD_HW_GATE_CTRL_HV,                      //硬件门控高电平有效
        TMR2_MODE_FREE_PERIOD_HW_GATE_CTRL_LV,                      //硬件门控低电平有效
        TMR2_MODE_FREE_PERIOD_RST_RISE_OR_FALL,                     //上升沿和下降沿复位
        TMR2_MODE_FREE_PERIOD_RST_RISE,                             //上升沿复位
        TMR2_MODE_FREE_PERIOD_RST_FALL,                             //下降沿复位
        TMR2_MODE_FREE_PERIOD_RST_LV,                               //低电平复位
        TMR2_MODE_FREE_PERIOD_RST_HV,                               //高电平复位
        TMR2_MODE_SINGLE_EVENT_START_SW,                            //软件启动 
        TMR2_MODE_SINGLE_EVENT_START_RISE,                          //上升沿启动
        TMR2_MODE_SINGLE_EVENT_START_FALL,                          //下降沿启动
        TMR2_MODE_SINGLE_EVENT_START_RISE_OR_FALL,                  //上升和下降沿启动
        TMR2_MODE_SINGLE_EVENT_START_RISE_AND_RST_RISE,             //上升沿启动 上升沿复位        
        TMR2_MODE_SINGLE_EVENT_START_FALL_AND_RST_FALL,             //下降沿启动 下降沿复位
        TMR2_MODE_SINGLE_EVENT_START_RISE_AND_RST_LV,               //上升沿启动  低电平复位
        TMR2_MODE_SINGLE_EVENT_START_FALL_AND_RST_HV,               //下降沿启动  高电平复位
        TMR2_MODE_MONOSTABLE_START_RISE = 17,                       //上升沿启动                单稳态
        TMR2_MODE_MONOSTABLE_START_FALL,                            //下降沿启动                单稳态
        TMR2_MODE_MONOSTABLE_START_RISE_OR_FALL,                    //上升沿和下降沿启动        单稳态
        TMR2_MODE_SINGLE_EVENT_START_HV_AND_RST_LV = 22,            //高电平启动  低电平复位
        TMR2_MODE_SINGLE_EVENT_START_LV_AND_RST_HV                  //低电平启动  高电平复位
    }tmr2_mode_t;
    
    typedef enum tmr2_rsel {
        TMR2_RSEL_T2INPPS = 0,
        TMR2_RSEL_CCP1_OUT,
        TMR2_RSEL_CCP2_OUT,
        TMR2_RSEL_PWM3_OUT,
        TMR2_RSEL_PWM4_OUT,
        TMR2_RSEL_PWM5_OUT,
        TMR2_RSEL_PWM6_OUT,
        TMR2_RSEL_C1OUT_SYNC,
        TMR2_RSEL_C2OUT_SYNC,
        TMR2_RSEL_ZCD1_OUT,
        TMR2_RSEL_LC1_OUT,
        TMR2_RSEL_LC2_OUT,
        TMR2_RSEL_LC3_OUT,
        TMR2_RSEL_LC4_OUT
    }tmr2_rsel_t;

    typedef void (*tmr2_handler_t)();
    extern void tmr2_init(tmr2_clk_cs_t cs,tmr2_ckps_t ckps,tmr2_outps_t outps,tmr2_mode_t mode,tmr2_rsel_t rsel);
    extern void tmr2_start();
    extern void tmr2_stop();
    extern void tmr2_isr_enable();
    extern void tmr2_isr_disable();
    extern void tmr2_setInterruptHandler(tmr2_handler_t handler);
    extern void tmr2_isr();

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR2_H */

