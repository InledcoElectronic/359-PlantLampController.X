/* 
 * File:   app_protocol.h
 * Author: liruya
 *
 * Created on 2019年5月15日, 上午10:53
 */

#ifndef APP_PROTOCOL_H
#define	APP_PROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef struct {
        uint8_t index;
        union {
            struct {
                uint8_t group;
                uint8_t address;
                uint8_t command;
                uint8_t regAddress;
                uint8_t regCount;
                uint8_t data[112];
            };
            uint8_t array[120];
        };
    } frame_t;


    typedef bool (*app_protocol_write_data_check_cb_t)(uint8_t start, uint8_t cnt, uint8_t *pdata);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_PROTOCOL_H */

