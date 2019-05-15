/* 
 * File:   drv_pwm.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月11日, 下午2:18
 */

#ifndef DRV_PWM_H
#define	DRV_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern void pwm1_init();
    extern void pwm1_load_duty(uint16_t duty);
    extern void pwm2_init();
    extern void pwm2_load_duty(uint16_t duty);
    extern void pwm3_init();
    extern void pwm3_load_duty(uint16_t duty);
    extern void pwm4_init();
    extern void pwm4_load_duty(uint16_t duty);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PWM_H */

