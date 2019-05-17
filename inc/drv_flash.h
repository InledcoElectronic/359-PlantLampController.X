/* 
 * File:   drv_flash.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月16日, 下午3:27
 */

#ifndef DRV_FLASH_H
#define	DRV_FLASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#define END_FLASH                       0x1FFF
#define ERASE_FLASH_BLOCKSIZE           32
#define WRITE_FLASH_BLOCKSIZE           32
    
#define HEF_START                       0x1F80
    
    extern uint8_t flash_readByte(uint16_t flashAddr);
    extern void flash_readBuffer(uint16_t flashAddr, uint8_t *pbuf, uint8_t len);
    extern uint8_t flash_writeBlock(uint16_t flashAddr, uint8_t *pbuf);
    extern void flash_write_byte(uint16_t flashAddr, uint8_t *rambuf, uint8_t byte);


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_FLASH_H */

