#include "../inc/drv_common.h"
#include "../inc/drv_flash.h"

void flash_erase_block(uint16_t flashAddr) {
	bool state = INTCONbits.GIE;
	//选择地址
	NVMADR = flashAddr;
	//选择闪存程序存储器
	NVMCON1bits.NVMREGS = 0;
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

//读一个字节
uint8_t flash_readByte(uint16_t flashAddr) {
	//选择地址
	NVMADR = flashAddr;
	//选择闪存程序存储器
	NVMCON1bits.NVMREGS = 0;
	//使能读操作
	NVMCON1bits.RD = 1;

	return NVMDATL;
}

void flash_readBuffer(uint16_t flashAddr, uint8_t *pbuf, uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		*(pbuf + i) = flash_readByte(flashAddr++);
	}
}

uint8_t flash_writeBlock(uint16_t flashAddr, uint8_t *pbuf) {
	uint16_t blockStartAddr = (uint16_t) (flashAddr & (END_FLASH ^ (ERASE_FLASH_BLOCKSIZE - 1)));
	uint8_t state = INTCONbits.GIE;
	if (flashAddr != blockStartAddr) {
		return -1;
	}
	//擦除一行
	flash_erase_block(flashAddr);
	//开始写操作
	NVMCON1bits.NVMREGS = 0;
	NVMCON1bits.FREE = 0;
	//装入写寄存器
	NVMCON1bits.LWLO = 1;
	NVMCON1bits.WREN = 1;

	for (uint8_t i = 0; i < WRITE_FLASH_BLOCKSIZE; i++) {
		NVMADR = flashAddr;
		NVMDATL = *(pbuf + i);
		if (i == (WRITE_FLASH_BLOCKSIZE - 1)) {
			//写入闪存
			NVMCON1bits.LWLO = 0;
		}
		//禁止全局中断
		INTCONbits.GIE = 0;
		//解锁序列
		NVMCON2 = 0x55;
		NVMCON2 = 0xAA;
		NVMCON1bits.WR = 1;
		NOP();
		NOP();
		INTCONbits.GIE = state;
		flashAddr++;
	}
	NVMCON1bits.WREN = 0;

	return 0;
}

void flash_write_byte(uint16_t flashAddr, uint8_t *rambuf, uint8_t byte) {
	uint16_t blockStartAddr = (uint16_t) (flashAddr & (END_FLASH ^ (ERASE_FLASH_BLOCKSIZE - 1)));
	uint8_t offset = (uint16_t) (flashAddr & (ERASE_FLASH_BLOCKSIZE - 1));

	for (uint8_t i = 0; i < ERASE_FLASH_BLOCKSIZE; i++) {
		rambuf[i] = flash_readByte(blockStartAddr++);
	}
	rambuf[offset] = byte;
	flash_writeBlock(blockStartAddr, rambuf);
}
