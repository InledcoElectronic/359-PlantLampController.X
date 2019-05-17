#include "../inc/drv_tmr0.h"

tmr0_interrupt_callback_t tmr0_callback;

void tmr0_init() {
	T0CON0 = 0x04;			//TMR0 disabled 5后分频
	T0CON1 = 0x44;			//CLK:Fosc/4  预分频16
	
	PIE0bits.TMR0IE = 1;
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
