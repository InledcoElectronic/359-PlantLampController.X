/* 
 * File:   drv_eusart.h
 * Author: niumiaomiao
 *
 * Created on 2019年5月14日, 下午1:52
 */

#ifndef DRV_EUSART_H
#define	DRV_EUSART_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef void (*eusart_rcv_handler_t)(uint8_t rcv);
    extern void eusart_init();
    extern uint8_t eusart_write(uint8_t byte);
    extern void eusart_transmit_isr();
    extern void eusart_setReceiveHandler(eusart_rcv_handler_t handler);
    extern void eusart_receive_isr();

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_EUSART_H */

