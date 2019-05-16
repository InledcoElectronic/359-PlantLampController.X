#include "../inc/drv_common.h"
#include "../inc/drv_tmr0.h"

tmr0_handler_t tmr0_isr_handler;

void tmr0_init(tmr0_clk_cs_t cs,tmr0_ckps_t ckps,tmr0_outps_t outps) {
    //配置定时器
    T0CON0bits.T016BIT = 0;                 //设置8位定时器
    T0CON0bits.T0OUTPS = outps;             //设置后分频
    
    T0CON1bits.T0CS = cs;                   //设置时钟源
    T0CON1bits.T0ASYNC = 0;                 //输入同步
    T0CON1bits.T0CKPS = ckps;               //设置预分频
    
    //初始化定时器
    TMR0L = 0x00;
    TMR0H = 0x00;
}
//开启定时器
void tmr0_start() {
    T0CON0bits.T0EN = 1;                
}
//关闭定时器
void tmr0_stop() {
    T0CON0bits.T0EN = 0;            
}
//使能中断
void tmr0_isr_enable() {
    PIE0bits.TMR0IE = 1;          
}
//禁止中断
void tmr0_isr_disable() {
    PIE0bits.TMR0IE = 0;     
}
//装载寄存器
void tmr0_reload_value(uint8_t value) {
    TMR0H = value;
}
//设置中断服务函数
void tmr0_setInterruptHandler(tmr0_handler_t handler) {
    tmr0_isr_handler = handler;
}
//中断服务函数
void tmr0_isr() {
    PIR0bits.TMR0IF = 0;
    if(tmr0_isr_handler != NULL) {
        tmr0_isr_handler();
    }
}