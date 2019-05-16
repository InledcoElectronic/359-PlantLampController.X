/* 
 * File:   drv_pcf8563.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月15日, 上午10:18
 */

#ifndef DRV_PCF8563_H
#define	DRV_PCF8563_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define RTC_ADDR                        0xA2
//#define RTC_WRITE_ADDR                  0xA2                //写
//#define RTC_READ_ADDR                   0xA3                //读

/* 寄存器地址 */
#define RTC_STAT1_ADDR                  0x00
#define RTC_STAT2_ADDR                  0x01
#define RTC_SEC_ADDR                    0x02
#define RTC_MIN_ADDR                    0x03
#define RTC_HOUR_ADDR                   0x04
#define RTC_DAY_ADDR                    0x05
#define RTC_WEEKDAY_ADDR                0x06
#define RTC_MONTH_ADDR                  0x07
#define RTC_YEAR_ADDR                   0x08
#define RTC_ALRM_MIN_ADDR               0x09
#define RTC_ALRM_HOUR_ADDR              0x0A
#define RTC_ALRM_DAY_ADDR               0x0B
#define RTC_ALRM_WEEKDAY_ADDR           0x0C
#define RTC_CLKOUT_ADDR                 0x0D
#define RTC_TIMERC_ADDR                 0x0E
#define RTC_TIMER_ADDR                  0x0F
    
/* 有效数据位 */
#define RTC_EFFECTIVE_SEC               0x7F
#define RTC_EFFECTIVE_MIN               0x7F
#define RTC_EFFECTIVE_HOUR              0x3F
#define RTC_EFFECTIVE_DAY               0x3F
#define RTC_EFFECTIVE_WEEKDAY           0x07
#define RTC_EFFECTIVE_MONTH             0x1F
/*时钟完整性*/
#define SEC_INTEGRITY_YES               0x00            //保证时钟完整性
#define SEC_INTEGRITY_NO                0x80            //不保证时钟完整性
    
    typedef union {
        struct {
            uint8_t year;
            uint8_t month;
            uint8_t day;
            uint8_t weekday;
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
        };
        uint8_t array[7];
    }data_time_t;
    
    extern data_time_t data_time;
    extern void pcf8563_init();
    extern void rtc_readOrWrite_time(uint8_t mode);
    extern void rtc_init();

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PCF8563_H */

