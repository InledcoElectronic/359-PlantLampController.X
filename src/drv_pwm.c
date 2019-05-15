#include "../inc/drv_common.h"
#include "../inc/drv_pwm.h"

void pwm1_init() {
    //配置CCP1CON寄存器
    CCP1CONbits.EN = 0;             //禁止CCP1
    CCP1CONbits.FMT = 1;            //左对齐
    CCP1CONbits.MODE = 0x0F;        //PWM模式
    //初始化占空比
    CCPR1H = 0x00;
    CCPR1L = 0x00;
    //使能PWM
    CCP1CONbits.EN = 1;
}
void pwm1_load_duty(uint16_t duty) {
    CCPR1H = duty >> 2;
    CCPR1L = (duty & 0x03) << 6;
}
void pwm2_init() {
    //配置CCP1CON寄存器
    CCP2CONbits.EN = 0;             //禁止CCP2
    CCP2CONbits.FMT = 1;            //左对齐
    CCP2CONbits.MODE = 0x0F;        //PWM模式
    //初始化占空比
    CCPR2H = 0x00;
    CCPR2L = 0x00;
    //使能PWM
    CCP2CONbits.EN = 1;
}
void pwm2_load_duty(uint16_t duty) {
    CCPR2H = duty >> 2;
    CCPR2L = (duty & 0x03) << 6;
}
void pwm3_init() {
    //配置PWM寄存器
    PWM3CONbits.EN = 0;             //禁止PWM
    PWM3CONbits.POL = 0;            //高电平有效
    //初始化占空比
    PWM3DCH = 0x00;
    PWM3DCL = 0x00;
    //使能PWM
    PWM3CONbits.EN = 1;             //使能PWM
}
void pwm3_load_duty(uint16_t duty) {
    PWM3DCH = duty >> 2;
    PWM3DCL = (duty & 0x03) << 6;
}
void pwm4_init() {
    //配置PWM寄存器
    PWM4CONbits.EN = 1;             //禁止PWM
    PWM4CONbits.POL = 0;            //高电平有效
    //初始化占空比
    PWM4DCH = 0x00;
    PWM4DCL = 0x00;
    //使能PWM
    PWM4CONbits.EN = 1;             //使能PWM
}
void pwm4_load_duty(uint16_t duty) {
    PWM4DCH = duty >> 2;
    PWM4DCL = (duty & 0x03) << 6;
}
