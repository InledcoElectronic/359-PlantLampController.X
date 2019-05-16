#include "../inc/drv_common.h"
#include "../inc/drv_pcf8563.h"
#include "../inc/drv_iic.h"

data_time_t data_time;

static uint8_t hexToBcd(uint8_t hex_data) {
    uint8_t temp; 
    temp = hex_data / 10 * 16 + hex_data % 10; 
    return temp; 
}

static uint8_t bcdToHex(uint8_t bcd_data) {
    uint8_t temp; 
    temp = bcd_data / 16 * 10 + bcd_data % 16; 
    return temp; 
}

void pcf8563_init() {
    iic_writeByte(RTC_ADDR,RTC_STAT1_ADDR,0x00);                //RTC正常模式
    iic_writeByte(RTC_ADDR,RTC_STAT2_ADDR,0x00);
    iic_writeByte(RTC_ADDR,RTC_CLKOUT_ADDR,0x03);               //禁止CLKOUT输出 1Hz
    iic_writeByte(RTC_ADDR,RTC_TIMERC_ADDR,0x03);               //定时器无效 1/60Hz
}

void rtc_operation_register(uint8_t regAddr,uint8_t len,uint8_t mode) {
    uint8_t time_register[7] = {0};
    if(mode) {                          //读寄存器
        iic_readBuffer(RTC_ADDR,regAddr,time_register,len);
        //将值复制到结构体
        data_time.second = bcdToHex(time_register[0] & RTC_EFFECTIVE_SEC);
        data_time.minute = bcdToHex(time_register[1] & RTC_EFFECTIVE_MIN);
        data_time.hour = bcdToHex(time_register[2] & RTC_EFFECTIVE_HOUR);
        data_time.day = bcdToHex(time_register[3] & RTC_EFFECTIVE_DAY);
        data_time.weekday = bcdToHex(time_register[4] & RTC_EFFECTIVE_WEEKDAY);
        data_time.month = bcdToHex(time_register[5] & RTC_EFFECTIVE_MONTH);
        data_time.year = bcdToHex(time_register[6]);
    } else {                            //写寄存器
        //将结构体中的数据写入寄存器
        time_register[0] = hexToBcd(data_time.second);
        time_register[1] = hexToBcd(data_time.minute);   
        time_register[2] = hexToBcd(data_time.hour);   
        time_register[3] = hexToBcd(data_time.day);   
        time_register[4] = hexToBcd(data_time.weekday);   
        time_register[5] = hexToBcd(data_time.month);   
        time_register[6] = hexToBcd(data_time.year);   
        //写寄存器
        iic_writeBuffer(RTC_ADDR,regAddr,time_register,len);
    }
}

void rtc_readOrWrite_time(uint8_t mode) {
    if(mode) {
        rtc_operation_register(RTC_SEC_ADDR,7,1);
    } else {
        rtc_operation_register(RTC_SEC_ADDR,7,0);
    }
}

void rtc_init() {
    //初始化寄存器
    data_time.second = 0x00;
    data_time.minute = 0x00;
    data_time.hour = 0x00;
    data_time.day = 0x00;
    data_time.weekday = 0x00;
    data_time.month = 0x00;
    data_time.year = 0x00;
    
    rtc_readOrWrite_time(0);
}