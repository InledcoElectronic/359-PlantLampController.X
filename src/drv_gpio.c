#include "../inc/drv_common.h"
#include "../inc/drv_gpio.h"

void gpio_init() {
    //配置GPIOA
    TRISA = 0x3F;           //RA0 RA1 RA2 RA3 RA4 RA5配置为输入
    ANSELA = 0x00;          //配置为数字IO口
    WPUA = 0x00;            //禁止弱上拉
    ODCONA = 0x00;          //标准推挽驱动
    SLRCONA = 0xFF;         //压摆率最大
    INLVLA = 0x00;          //TTL输入
    //配置GPIOB
    LATB = 0x0F;            //RBO RB1 RB2 RB3输出高电平
    TRISB = 0x30;           //RB0 RB1 RB2 RB3配置为输出； RB4 RB5配置为输入
    ANSELB = 0x00;          //配置为数字IO口
    WPUB = 0x00;            //禁止弱上拉
    ODCONB = 0x00;          //标准推挽驱动
    SLRCONB = 0xFF;         //压摆率最大
    INLVLB = 0x00;          //TTL输入
    //配置GPIOC
	ANSELC = 0x00; //配置位数字IO口
    LATC = 0x40;            //RC0 RC3 RC4 RC5输出低电平 RC6输出高电平
    TRISC = 0x86;           //RC1 RC2配置为SDA SCL  RC4配置为PWM5 RC5配置为输出 RC6配置为TX  RC7配置为RX
    WPUC = 0x00;            //禁止弱上拉
    ODCONC = 0x00;          //标准推挽驱动
    SLRCONC = 0xFF;         //压摆率最大
    INLVLC = 0x00;          //TTL输入

    //配置PPS
    bool state = INTCONbits.GIE;
    //禁止全局中断
    GlobalInterruptDisable();
    //使能PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;
    RB0PPS = 0x09;              //CCP1
    RB1PPS = 0x0A;              //CCP2
    RB2PPS = 0x0B;              //PWM3
    RB3PPS = 0x0C;              //PWM4
    RC6PPS = 0x0F;              //TX
    RX1DTPPS = 0x17;            //RX
    SSP1CLKPPS = 0x12;          //SCL
    RC1PPS = 0x16;              //SDA
    RC2PPS = 0x15;              //SCL
    SSP1DATPPS = 0x11;          //SDA
    //禁止PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
    INTCONbits.GIE = state;
}



