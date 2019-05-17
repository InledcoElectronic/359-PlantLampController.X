#include "../inc/drv_common.h"
#include "../inc/drv_tmr2.h"

tmr2_handler_t tmr2_isr_handler;
//定时器2初始化
void tmr2_init(tmr2_clk_cs_t cs,tmr2_ckps_t ckps,tmr2_outps_t outps,tmr2_mode_t mode,tmr2_rsel_t rsel) {
    //配置时钟源寄存器
    T2CLKCONbits.CS = cs;
    //配置控制器寄存器
    T2CONbits.CKPS = ckps;
    T2CONbits.OUTPS = outps;
    //配置工作模式寄存器
    T2HLTbits.PSYNC = 1;                //预分频同步使能
    T2HLTbits.CKPOL = 0;                //极性使能,上升沿计数
    T2HLTbits.CKSYNC = 1;               //时钟同步使能
    T2HLTbits.MODE = mode;              //模式选择
    //配置复位源
    T2RSTbits.RSEL = rsel;
    
    PR2 = 249;
	PIE4bits.TMR2IE = 1;
}
//定时器使能
void tmr2_start() {
    T2CONbits.ON = 1;
}
//禁止定时器
void tmr2_stop() {
    T2CONbits.ON = 0; 
}
//定时器中断使能
void tmr2_isr_enable() {
    PIE4bits.TMR2IE = 1;
}
//禁止定时器中断
void tmr2_isr_disable() {
    PIE4bits.TMR2IE = 0;
}
//设置中断服务函数
void tmr2_setInterruptHandler(tmr2_handler_t handler) {
    tmr2_isr_handler = handler;
}
//中断服务函数
void tmr2_isr() {
    PIR4bits.TMR2IF = 0;
    if(tmr2_isr_handler != NULL) {
        tmr2_isr_handler();
    }
}