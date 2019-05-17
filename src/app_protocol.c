#include "../inc/app_protocol.h"
#include "../inc/drv_eusart.h"

typedef struct {
	uint8_t poly;			//多项式
	uint8_t init;			//初始值
	uint8_t xorout;			//输出异或
	bool	refin;			//输入反转
	bool	refout;			//输出反转
} crc8_type_t;

#define	CTRL				LATCbits.LATC5

#define	FRAME_MIN_LENGTH	6
#define	CMD_READ			0x03
#define	CMD_WRITE			0x10

const crc8_type_t crc8_maxim = {
	0x31,
	0x00,
	0x00,
	true,
	true
};

static uint8_t mGroup;
static uint8_t mAddress;
static uint8_t *pRegister;
static uint8_t mRegCount;
static app_protocol_write_data_cb_t write_data_cb;

frame_t mFrame;

void app_protocol_init(uint8_t group, uint8_t address, uint8_t *reg, uint8_t regCount) {
	if (group != 0 && address != 0 && reg != NULL && regCount <= 112) {
		mGroup = group;
		mAddress = address;
		pRegister = reg;
		mRegCount = regCount;
	}
}

static void rs485_write_start() {
	CTRL = 1;
	__delay_us(100);
}

static void rs485_write_stop() {
	while (!TXSTA1bits.TRMT);
	__delay_us(100);
	CTRL = 0;
}

static uint8_t reflect(uint8_t data) {
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		result <<= 1;
		if (data & (1 << i)) {
			result |= 0x01;
		}
	}
	return result;
}

static uint8_t getChecksum(crc8_type_t *type, uint8_t *pdata, uint8_t len) {
	uint8_t i, j;
	uint8_t crc = type->init;
	uint8_t poly = 0;
	if (type->refin) {
		poly = reflect(type->poly);
		for (i = 0; i < len; i++) {
			crc ^= pdata[i];
			for (j = 0; j < 8; j++) {
				if (crc & 0x01) {
					crc = (crc >> 1) ^ poly;
				} else {
					crc >>= 1;
				}
			}
		}
	} else {
		poly = type->poly;
		for (i = 0; i < len; i++) {
			crc ^= pdata[i];
			for (j = 0; j < 8; j++) {
				if (crc & 0x80) {
					crc = (crc << 1) ^ poly;
				} else {
					crc <<= 1;
				}
			}
		}
	}
	if (type->refin ^ type->refout) {
		crc = reflect(crc);
	} else {
		crc ^= type->xorout;
	}
	return crc;
}

static void app_protocol_read_ack(uint8_t start, uint8_t cnt) {
	if (pRegister == NULL || start >= mRegCount || start+cnt > mRegCount) {
		return;
	}
	rs485_write_start();
	for (uint8_t i = 0; i < cnt; i++) {
		mFrame.data[i] = *(pRegister+start+i);
	}
	mFrame.array[cnt+5] = getChecksum(&crc8_maxim, mFrame.array, cnt+5);
	eusart_write_buffer(mFrame.array, cnt+6);
	rs485_write_stop();
}

static void app_protocol_write_ack() {
	rs485_write_start();
	mFrame.array[5] = getChecksum(&crc8_maxim, mFrame.array, 5);
	eusart_write_buffer(mFrame.array, 6);
	rs485_write_stop();
}

void app_protocol_receive(uint8_t rcv) {
	if (mFrame.index >= sizeof(mFrame.array)) {
		mFrame.index = 0;
	}
	mFrame.array[mFrame.index++] = rcv;
}

void app_protocol_decode() {
	if (mGroup == 0 || mAddress == 0 || pRegister == NULL) {
		return;
	}
	if (mFrame.index < FRAME_MIN_LENGTH) {
		return;
	}
	bool match = false;
	bool ack = false;
	uint8_t group = mFrame.group;
	uint8_t address = mFrame.address;
	uint8_t start = mFrame.regAddress;
	uint8_t cnt = mFrame.regCount;
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
	if (getChecksum(&crc8_maxim, mFrame.array, mFrame.index) != 0) {
		return;
	}
	if (address >= mRegCount || address+cnt > mRegCount) {
		return;
	}
	switch (mFrame.command) {
		case CMD_READ:
			if (ack) {
				app_protocol_read_ack(start, cnt);
			}
			break;
		case CMD_WRITE:
			if (cnt+6 != mFrame.index) {
				return;
			}
			if (write_data_cb == NULL) {
				return;
			}
			write_data_cb(start, cnt, mFrame.data);
			if (ack) {
				app_protocol_write_ack();
			}
			break;
		default:
			break;
	}
}

void app_protocol_clear() {
	mFrame.index = 0;
}

void app_protocol_set_write_data_cb(app_protocol_write_data_cb_t callback) {
	write_data_cb = callback;
}