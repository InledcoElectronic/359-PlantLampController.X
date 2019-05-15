/* 
 * File:   drv_iic.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月14日, 下午3:59
 */

#ifndef DRV_IIC_H
#define	DRV_IIC_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern void iic_init();
    extern void iic_writeByte(uint8_t slaveAddr,uint8_t regAddr,uint8_t byte);
    extern void iic_writeBuffer(uint8_t slaveAddr,uint8_t regAddr,uint8_t *buf,uint8_t len);
    extern uint8_t iic_readByte(uint8_t slaveAddr,uint8_t regAddr);
    extern void iic_readBuffer(uint8_t slaveAddr,uint8_t regAddr,uint8_t *buf,uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_IIC_H */

