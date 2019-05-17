#include "../inc/drv_common.h"
#include "../inc/drv_pcf8563.h"
#include "../inc/drv_iic.h"

static uint8_t hexToBcd(uint8_t hex) {
    return ((hex/10)<<4) + hex%10;
}

static uint8_t bcdToHex(uint8_t bcd) {
    return (bcd>>4)*10 + (bcd&0x0F);
}

void pcf8563_init() {
    iic_writeByte(RTC_ADDR,RTC_STAT1_ADDR, 0x00);                //RTC正常模式
    iic_writeByte(RTC_ADDR,RTC_STAT2_ADDR, 0x00);
    iic_writeByte(RTC_ADDR,RTC_CLKOUT_ADDR, 0x03);               //禁止CLKOUT输出 1Hz
    iic_writeByte(RTC_ADDR,RTC_TIMERC_ADDR, 0x03);               //定时器无效 1/60Hz
}

/**
 * year month day week hour min second
 * @param ptime
 */
void pcf8563_get_time(uint8_t *ptime) {
	//sec min hour day week month year
	uint8_t time[7];
	iic_readBuffer(RTC_ADDR, RTC_SEC_ADDR, time, 7);
	*ptime = bcdToHex(time[6]);						//year
	*(ptime+1) = bcdToHex(time[5]&MASK_MONTH);		//month
	*(ptime+2) = bcdToHex(time[3]&MASK_DAY);		//day
	*(ptime+3) = bcdToHex(time[4]&MASK_WEEKDAY);	//week
	*(ptime+4) = bcdToHex(time[2]&MASK_HOUR);		//hour
	*(ptime+5) = bcdToHex(time[1]&MASK_MIN);		//min
	*(ptime+6) = bcdToHex(time[0]&MASK_SEC);		//sec
}

/**
 * year month day week hour min second
 * @param ptime
 */
void pcf8563_set_time(uint8_t *ptime) {
	//sec min hour day week month year
	uint8_t time[7];
	time[0] = hexToBcd(*(ptime+6));		//sec
	time[1] = hexToBcd(*(ptime+5));		//min
	time[2] = hexToBcd(*(ptime+4));		//hour
	time[3] = hexToBcd(*(ptime+2));		//day
	time[4] = hexToBcd(*(ptime+3));		//week
	time[5] = hexToBcd(*(ptime+1));		//month
	time[6] = hexToBcd(*ptime);			//year
	iic_writeBuffer(RTC_ADDR, RTC_SEC_ADDR, time, 7);
}
