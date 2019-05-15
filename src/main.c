/*
 * File:   main.c
 * Author: niumiaomiao
 *
 * Created on 2019年5月10日, 下午5:41
 */

#include "../inc/drv_common.h"
#include "../inc/drv_osc.h"
#include "../inc/drv_gpio.h"
#include "../inc/drv_pwm.h"
#include "../inc/drv_tmr2.h"
#include "../inc/drv_eusart.h"
#include "../inc/drv_iic.h"
#include "../inc/app_protocol.h"
#include "../inc/app_control.h"

// CONFIG1
#pragma config FEXTOSC = ECH    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = ON        // WDT operating mode (WDT enabled regardless of sleep; SWDTEN ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration Register not write protected)
#pragma config WRTSAF = OFF     // Storage Area Flash Write Protection bit (SAF not write protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (UserNVM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

void main(void) {
    //初始化时钟
    osc_init();
    //初始化IO口
    gpio_init();
    //初始化PWM
    pwm1_init();
    pwm2_init();
    pwm3_init();
    pwm4_init();
    //初始化定时器
    tmr2_init(TMR2_CLK__FOSC_4,TMR2_CKPS_4,TMR2_OUTPS_8,TMR2_MODE_FREE_PERIOD_SW_GATE_CTRL,TMR2_RSEL_T2INPPS);
    tmr2_start();
    //串口初始化
    eusart_init();
    //IIC初始化
    iic_init();
    
    while(1) {
        CLRWDT();

    }
}

void interrupt ISR() {
    if(PIE4bits.TMR2IE && PIR4bits.TMR2IF) {
        tmr2_isr();
    } else if(PIE3bits.RC1IE && PIR3bits.RC1IF) {
        eusart_receive_isr();
    } else if(PIE3bits.TX1IE && PIR3bits.TX1IF) {
        eusart_transmit_isr();
    }
}
