#include "../inc/app_control.h"
#include "../inc/drv_pwm.h"

#define	INDEX_YEAR		1
#define	INDEX_MONTH		2
#define	INDEX_DAY		3
#define	INDEX_WEEK		4
#define	INDEX_HOUR		5
#define	INDEX_MINUTE	6
#define	INDEX_SECOND	7

#define	STEP_RAMP		1

register_t mRegister;

uint16_t mTargetBrights[MAX_CHANNEL_COUNT];
uint16_t mCurrentBrights[MAX_CHANNEL_COUNT];

void app_control_update() {
	uint8_t i;
	if (mRegister.power) {
		for (i = 0; i < MAX_CHANNEL_COUNT; i++) {
			mTargetBrights[i] = mRegister.brights[i];
		}
	} else {
		for (i = 0; i < MAX_CHANNEL_COUNT; i++) {
			mTargetBrights[i] = 0;
		}
	}
	pwm1_load_duty(mCurrentBrights[0]);
	pwm2_load_duty(mCurrentBrights[1]);
	pwm3_load_duty(mCurrentBrights[2]);
	pwm4_load_duty(mCurrentBrights[3]);
}

void app_control_set_time(uint8_t *ptime) {

}

void app_control_ramp() {
	for (uint8_t i = 0; i < MAX_CHANNEL_COUNT; i++) {
		if (mCurrentBrights[i] + STEP_RAMP < mTargetBrights[i]) {
			mCurrentBrights[i] += STEP_RAMP;
		} else if (mCurrentBrights[i] > mTargetBrights[i] + STEP_RAMP) {
			mCurrentBrights[i] -= STEP_RAMP;
		}
	}
	
}

void app_control_process() {
	uint8_t i, j;
	uint8_t hour = mRegister.hour;
	uint8_t minute = mRegister.minute;
	uint8_t sec = mRegister.second;
	if (hour > 23 || minute > 59) {
		return;
	}
	uint16_t tm = hour*60u+minute;
	if (sec == 0) {
		for (i = 0; i < 8; i++) {
			if (mRegister.turnoffTime[i] > 1439) {
				break;
			}
			if (tm == mRegister.turnoffTime[i]) {
				mRegister.power = false;
				app_control_update();
				break;
			}
		}
		for (i = 0; i < 8; i++) {
			if (mRegister.timepoints[i].turnonTime > 1439) {
				break;
			}
			if (tm == mRegister.timepoints[i].turnonTime) {
				mRegister.power = true;
				for (j = 0; j < MAX_CHANNEL_COUNT; j++) {
					mRegister.brights[j] = mRegister.timepoints[i].brights[j]*10;
				}
				app_control_update();
				break;
			}
		}
	}
}

void app_control_param_changed_cb(uint8_t start, uint8_t cnt, uint8_t *pdata) {
	if (start >= sizeof(register_t) || start+cnt > sizeof(register_t)) {
		return;
	}
	if (start == INDEX_YEAR && cnt == 7) {
		app_control_set_time(pdata);
		return;
	}
	for (uint8_t i = 0; i < cnt; i++) {
		mRegister.array[start+i] = *(pdata+i);
	}
	app_control_update();
}
