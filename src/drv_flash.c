#include "../inc/drv_common.h"
#include "../inc/drv_flash.h"

//擦除操作
void flash_erase_block(uint16_t flashAddr) {
    bool state = INTCONbits.GIE;
    //选择闪存程序存储器
    NVMCON1bits.NVMREGS = 0;
    //选择地址
    NVMADR = flashAddr;
    //选择擦除操作
    NVMCON1bits.FREE = 1;
    //擦除使能
    NVMCON1bits.WREN = 1;
    //禁止全局中断
    INTCONbits.GIE = 0;
    //解锁序列
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    NOP();
    NOP();
    //禁止擦除操作
    NVMCON1bits.WREN = 0;
    //全局中断使能
    INTCONbits.GIE = state;
}
//读操作
uint8_t flash_readByte(uint16_t flashAddr) {
    //选择闪存程序存储器
    
}
//写操作
