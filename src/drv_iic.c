#include "../inc/drv_common.h"
#include "../inc/drv_iic.h"

#if defined(_XTAL_FREQ) && defined (IIC_BAUDRATE)
#define IIC_BAUDRATE_VALUE          ((uint16_t)(_XTAL_FREQ / 4 / IICBAUDRATE - 1))
#else
#define IIC_BUADTATE_VALUE          9              //16M  400K
#endif

#define ERROR_COUNT                 5

void iic_init() {
    //配置MSSP状态寄存器
    SSP1STATbits.SMP = 1;                       //标准模式下禁止压摆率
    SSP1STATbits.CKE = 0;                       //禁止SMBus特定输入
    //配置控制寄存器
    SSP1CON1bits.SSPEN = 1;                     //使能串口
    SSP1CON1bits.SSPM = 0x08;                   //时钟 = FOSC / (4 * (SSP1ADD+1))
    SSP1CON3bits.SDAHT = 1;                     //在SCL的下降沿之后，在SDA上最少有300ns的保持时间
    //设置传输熟虑
    SSP1ADD = IIC_BUADTATE_VALUE;
}
//IIC启动
static void iic_start() {
    SSP1CON2bits.SEN = 1;
}
//IIC停止
static void iic_stop() {
    SSP1CON2bits.PEN = 1;
}
//IIC重复启动
static void iic_reStart() {
    SSP1CON2bits.RSEN = 1;
}
//使能接受
static void iic_receive_enable() {
    SSP1CON2bits.RCEN = 1;
}
static void iic_checkSSPIF() {
    while(!PIR3bits.SSP1IF);
    PIR3bits.SSP1IF = 0;
}
//IIC发送一个字节
void iic_writeByte(uint8_t slaveAddr,uint8_t regAddr,uint8_t byte) {
    uint8_t cnt = 0;
    //发送启动条件
    iic_start();
    iic_checkSSPIF();
    
    //发送从机地址
    SSP1BUF = slaveAddr;
    iic_checkSSPIF();
    while(SSP1CON2bits.ACKSTAT) {
        cnt++;
        if(cnt >= ERROR_COUNT) {
            return;
        }
        iic_start();
        iic_checkSSPIF();
        SSP1BUF = slaveAddr;
        iic_checkSSPIF();
    }
    SSP1BUF = regAddr;
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return ;
    }
    SSP1BUF = byte;
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return ;
    }
    
    //发送停止条件
    iic_stop();
    iic_checkSSPIF();
}
//写一个字符串
void iic_writeBuffer(uint8_t slaveAddr,uint8_t regAddr,uint8_t *buf,uint8_t len) {
    uint8_t cnt = 0;
    //发送启动条件
    iic_start();
    iic_checkSSPIF();
    
    //发送从机地址
    SSP1BUF = slaveAddr;
    iic_checkSSPIF();
    while(SSP1CON2bits.ACKSTAT) {
        cnt++;
        if(cnt >= ERROR_COUNT) {
            return;
        }
        iic_start();
        iic_checkSSPIF();
        SSP1BUF = slaveAddr;
        iic_checkSSPIF();
    }
    SSP1BUF = regAddr;
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return ;
    }
    for(uint8_t i = 0; i < len; i++) {
        SSP1BUF = *(buf + i);
        iic_checkSSPIF();
        if(SSP1CON2bits.ACKSTAT) {
            return ;
        }
    }
    
    //发送停止条件
    iic_stop();
    iic_checkSSPIF();
}
//读取一个字节
uint8_t iic_readByte(uint8_t slaveAddr,uint8_t regAddr) {
    uint8_t byte;
    uint8_t cnt = 0;
    //启动条件
    iic_start();
    iic_checkSSPIF();
  
    //发送从机地址
    SSP1BUF = slaveAddr;
    iic_checkSSPIF();
    while(SSP1CON2bits.ACKSTAT) {
        cnt++;
        if(cnt > ERROR_COUNT) {
            return 0;
        }
        iic_start();
        iic_checkSSPIF();
        
        SSP1BUF = slaveAddr;
        iic_checkSSPIF();
    }
    SSP1BUF = regAddr;
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return 0;
    }
    //重复启动
    iic_reStart();
    iic_checkSSPIF();
    //发送从机地址  读数据
    SSP1BUF = slaveAddr + 1;            //读数据
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return 0;
    }
    //使能接受
    iic_receive_enable();
    iic_checkSSPIF();
    byte = SSP1BUF;
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    iic_checkSSPIF();
    
    //发送停止条件
    iic_stop();
    iic_checkSSPIF();
    
    return byte;
}
//地区一个字符串
void iic_readBuffer(uint8_t slaveAddr,uint8_t regAddr,uint8_t *buf,uint8_t len) {
    uint8_t cnt = 0;
    //启动条件
    iic_start();
    iic_checkSSPIF();
  
    //发送从机地址
    SSP1BUF = slaveAddr;
    iic_checkSSPIF();
    while(SSP1CON2bits.ACKSTAT) {
        cnt++;
        if(cnt > ERROR_COUNT) {
            return ;
        }
        iic_start();
        iic_checkSSPIF();
        
        SSP1BUF = slaveAddr;
        iic_checkSSPIF();
    }
    SSP1BUF = regAddr;
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return ;
    }
    //重复启动
    iic_reStart();
    iic_checkSSPIF();
    //发送从机地址  读数据
    SSP1BUF = slaveAddr + 1;            //读数据
    iic_checkSSPIF();
    if(SSP1CON2bits.ACKSTAT) {
        return ;
    }
    for(uint8_t i = 0; i < len - 1; i++) {
        iic_receive_enable();
        iic_checkSSPIF();
        *(buf + i) = SSP1BUF;
        SSP1CON2bits.ACKDT = 0;
        SSP1CON2bits.ACKEN = 1;
        iic_checkSSPIF();
    }
    iic_receive_enable();
    iic_checkSSPIF();
    *(buf + len - 1) = SSP1BUF;
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    iic_checkSSPIF();
    
    //发送停止条件
    iic_stop();
    iic_checkSSPIF();
}

