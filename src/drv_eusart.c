#include "../inc/drv_common.h"
#include "../inc/drv_eusart.h"

#ifndef EUSART_TX_BUFFER_SIZE
#define EUSART_TX_BUFFER_SIZE           32
#endif

#if defined(_XTAL_FREQ) && defined(EUSART_BAUDRATE)
#define EUSART_BRG_VALUE    ((uint16_t)(_XTAL_FREQ / 4 / EUSART_BAUDRATE - 1))
#else
#define EUSART_BRG_VALUE    416                     //16M       9600
#endif

eusart_rcv_handler_t eusart_rcv_handler;
static uint8_t tx_buffer[EUSART_TX_BUFFER_SIZE];
static uint8_t tx_head;
static uint8_t tx_tail;
static uint8_t tx_remain;

void eusart_init() {
    //配置发送寄存器
    TX1STAbits.TX9 = 0;             //选择8位发送
    TX1STAbits.TXEN = 1;            //发送使能
    TX1STAbits.SYNC = 0;            //异步发送
    TX1STAbits.SENDB = 0;           //禁止同步字符发送
    TX1STAbits.BRGH = 1;            //高速模式
    //配置接收寄存器
    RC1STAbits.SPEN = 1;            //使能串口
    RC1STAbits.RX9 = 0;             //选择8位接收
    RC1STAbits.CREN = 1;            //使能接收
    //波特率设置
    BAUD1CONbits.BRG16 = 1;         //使能16位波特发生器
    SP1BRG = EUSART_BRG_VALUE;
    
    tx_head = 0;
    tx_tail = 0;
    tx_remain = sizeof(tx_buffer);
}
void putch(char c) {
    while(tx_remain == 0);
    if(PIE3bits.TX1IE == 0) {
        TX1REG = c;
    } else {
        PIE3bits.TX1IE = 0;
        tx_buffer[tx_head++] = c;
        if(tx_head >= sizeof(tx_buffer)) {
            tx_head = 0;
        }
        tx_remain--;
    }
    //发送使能
    PIE3bits.TX1IE = 1;
}
//发送一个字节
uint8_t eusart_write(uint8_t byte) {
    putch(byte);
    return byte;
}
//发送中断使能
void eusart_transmit_isr() {
    if(tx_remain < sizeof(tx_buffer)) {
        TX1REG = tx_buffer[tx_tail++];
        if(tx_tail >= sizeof(tx_buffer)) {
            tx_tail = 0;
        }
        tx_remain++;
    } else {
        PIE3bits.TX1IE = 0;
    }
}
//设置中断服务函数
void eusart_setReceiveHandler(eusart_rcv_handler_t handler) {
    eusart_rcv_handler = handler;
}
//接收中断服务函数
void eusart_receive_isr() {
    uint8_t rcv = RC1REG;
    if(eusart_rcv_handler != NULL) {
        eusart_rcv_handler(rcv);
    }
}

