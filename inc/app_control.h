/* 
 * File:   app_control.h
 * Author: liruya
 *
 * Created on 2019年5月15日, 上午11:14
 */

#ifndef APP_CONTROL_H
#define	APP_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define MAX_CHANNEL_COUNT   6
    
    typedef struct {
        uint16_t turnonTime;
        uint8_t brights[MAX_CHANNEL_COUNT];
    } timepoint_t;
    
    typedef union {
        struct {
            //0x00-0x0F
            uint8_t rsv0;
            uint8_t year;
            uint8_t month;
            uint8_t day;
            uint8_t week;
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
            uint8_t rsv1[8];
            //0x10-0x1F
            bool power;
            uint16_t brights[MAX_CHANNEL_COUNT];
            uint8_t rsv2[3];
            //0x20-0x2F
            uint16_t turnoffTime[8];
            //0x30-0x6F
            timepoint_t timepoints[8];
        };
        uint8_t array[112];
    } register_t;
    
    extern register_t mRegister;
    
    extern void app_control_init();
    extern void app_control_ramp();
    extern void app_control_process();
    extern void app_control_param_changed_cb(uint8_t start, uint8_t cnt, uint8_t *pdata);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_CONTROL_H */

