<<<<<<< HEAD
#include "../inc/drv_tmr0.h"

tmr0_interrupt_callback_t tmr0_callback;

void tmr0_init() {
	T0CON0 = 0x04;			//TMR0 disabled 5后分频
	T0CON1 = 0x44;			//CLK:Fosc/4  预分频16
}

void tmr0_start() {
	if (T0CON0bits.T0EN) {
		T0CON0bits.T0EN = 0;
	}
	TMR0 = 0;
	T0CON0bits.T0EN = 1;
}

void tmr0_isr() {
	PIR0bits.TMR0IF = 0;
	T0CON0bits.T0EN = 0;
	if (tmr0_callback != NULL) {
		tmr0_callback();
	}
}

void tmr0_set_interrupt_callback(tmr0_interrupt_callback_t callback) {
	tmr0_callback = callback;
}
=======
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
>>>>>>> 61c9d203afad3756857c34e816409de748396cf4
