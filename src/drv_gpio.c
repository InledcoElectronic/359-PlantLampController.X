#include "../inc/drv_common.h"
#include "../inc/drv_gpio.h"

void gpio_init() {
    //配置GPIOA
    TRISA = 0x3F;           //RA0 RA1 RA2 RA3 RA4 RA5配置为输入
    ANSELA = 0x00;          //配置为数字IO口
    WPUA = 0x00;            //禁止弱上拉
    ODCONA = 0x00;          //标准推挽驱动
    SLRCONA = 0x00;         //压摆率最大
    INLVLA = 0x00;          //TTL输入
    //配置GPIOB
    TRISB = 0x30;           //RB0 RB1 RB2 RB3配置为输出； RB4 RB5配置为输入
    LATB = 0x0F;            //RBO RB1 RB2 RB3输出高电平
    ANSELB = 0x00;          //配置为数字IO口
    WPUB = 0x00;            //禁止弱上拉
    ODCONB = 0x00;          //标准推挽驱动
    SLRCONB = 0x00;         //压摆率最大
    INLVLB = 0x00;          //TTL输入
    //配置GPIOC
    TRISC = 0x86;           //RC1 RC2配置为SDA SCL  RC4配置为PWM5 RC5配置为输出 RC6配置为TX  RC7配置为RX
    LATC = 0x60;            //RC0 RC3 RC4输出低电平 RC5 RC6输出高电平
    WPUC = 0x00;            //禁止弱上拉
    ODCONC = 0x03;          //RC1 RC2配置为漏极开漏使能
    SLRCONC = 0x00;         //压摆率最大
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
    SSP1DATPPS = 0x11;          //SDA
    SSP1CLKPPS = 0x12;          //SCL
    //禁止PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
    INTCONbits.GIE = state;
}



