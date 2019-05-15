#include "../inc/app_protocol.h"
#include "../inc/app_control.h"
#include "../inc/drv_eusart.h"

#define	CTRL				LATCbits.LATC5

#define	FRAME_MIN_LENGTH	6
#define	CMD_READ			0x03
#define	CMD_WRITE			0x10

#define	REG_START			0x00
#define	REG_END				(sizeof(register_t)-1)

static uint8_t mGroup;
static uint8_t mAddress;
static uint8_t *pRegister;
static uint8_t mRegCount;
static app_protocol_write_data_check_cb_t write_data_check_cb;

frame_t mFrame;

void app_protocol_init(uint8_t group, uint8_t address, uint8_t *reg, uint8_t regCount) {
	if (group != 0 && address != 0 && reg != NULL && regCount <= 112) {
		mGroup = group;
		mAddress = address;
		pRegister = reg;
		mRegCount = regCount;
	}
}

uint8_t getChecksum(uint8_t *pdata, uint8_t len) {
	
	return 0;
}

static void rs485_write_start() {
	CTRL = 1;
	__delay_us(100);
}

static void rs485_write_stop() {
	while(!TXSTA1bits.TRMT);
	__delay_us(100);
	CTRL = 0;
}

static void app_protocol_read_ack(uint8_t start, uint8_t cnt) {
	if (pRegister == NULL || start >= mRegCount || start+cnt > mRegCount) {
		return;
	}
	rs485_write_start();
	for (uint8_t i = 0; i < cnt; i++) {
		mFrame.data[i] = *(pRegister+start+i);
	}
	mFrame.array[cnt+5] = getChecksum(mFrame.array, cnt+5);
	eusart_write_buffer(mFrame.array, cnt+6);
	rs485_write_stop();
}

static void app_protocol_write_ack() {
	rs485_write_start();
	mFrame.array[5] = getChecksum(mFrame.array, 5);
	eusart_write_buffer(mFrame.array, 6);
	rs485_write_stop();
}

void app_protocol_decode(frame_t *pframe) {
	if (mGroup == 0 || mAddress == 0 || pRegister == NULL) {
		return;
	}
	if (pframe == NULL || pframe->index < FRAME_MIN_LENGTH) {
		return;
	}
	bool match = false;
	bool ack = false;
	uint8_t group = pframe->group;
	uint8_t address = pframe->address;
	uint8_t start = pframe->regAddress;
	uint8_t cnt = pframe->regCount;
	if (group == 0 && address == 0) {
		match = true;
	} else if (group == mGroup && address == 0) {
		match = true;
	} else if (group == mGroup && address == mAddress) {
		match = true;
		ack = true;
	}
	if (match == false) {
		return;
	}
	if (getChecksum(pframe->array, pframe->index) != 0) {
		return;
	}
	if (address >= mRegCount || address+cnt > mRegCount) {
		return;
	}
	switch (pframe->command) {
		case CMD_READ:
			if (ack) {
				app_protocol_read_ack();
			}
			break;
		case CMD_WRITE:
			if (write_data_check_cb == NULL || write_data_check_cb(address, cnt, pframe->data) == false) {
				return;
			}
			if (ack) {
				app_protocol_write_ack();
			}
			break;
		default:
			break;
	}
}
