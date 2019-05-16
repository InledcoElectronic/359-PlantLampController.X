#include "../inc/drv_common.h"
#include "../inc/drv_osc.h"

void osc_init() {
    //配置新振荡器
    OSCCON1bits.NOSC = 0x06;        //内部高速时钟
    OSCCON1bits.NDIV = 0x00;        //1分频
    //OSCCON3
    OSCCON3bits.CSWHOLD = 0;        //禁止时钟暂停
    OSCCON3bits.SOSCPWR = 0;        //低功耗模式
    //OSCEN
    OSCENbits.EXTOEN = 0;           //EXTOSC可由另一个模块使能
    OSCENbits.HFOEN = 1;            //明确使能使能HFINTOSC
    //高速振荡器频率选择位
    OSCFRQbits.HFFRQ = 0x05;        //16M
    //内部高速时钟调节
    OSCTUNEbits.HFTUN = 0x00;       //中心频率
}

