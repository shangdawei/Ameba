#ifndef __RTL8195AM_PWM_H__
#define __RTL8195AM_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

extern void
HAL_Pwm_SetDuty_8195a( HAL_PWM_ADAPTER *pPwmAdapt, u32 period, u32 pulse_width );

extern HAL_STATUS
HAL_Pwm_Init_8195a( HAL_PWM_ADAPTER *pPwmAdapt );

extern void
HAL_Pwm_Enable_8195a( HAL_PWM_ADAPTER *pPwmAdapt );

extern void
HAL_Pwm_Disable_8195a( HAL_PWM_ADAPTER *pPwmAdapt );

#ifdef CONFIG_CHIP_E_CUT
extern _LONG_CALL_ void
HAL_Pwm_SetDuty_8195a_V04(
    HAL_PWM_ADAPTER *pPwmAdapt,
    u32 period,
    u32 pulse_width
);

extern _LONG_CALL_ HAL_STATUS
HAL_Pwm_Init_8195a_V04(
    HAL_PWM_ADAPTER *pPwmAdapt
);

extern _LONG_CALL_ void
HAL_Pwm_Enable_8195a_V04(
    HAL_PWM_ADAPTER *pPwmAdapt
);

extern _LONG_CALL_ void
HAL_Pwm_Disable_8195a_V04(
    HAL_PWM_ADAPTER *pPwmAdapt
);
#endif

#define MAX_PWM_CTRL_PIN        4
// the minimum tick time for G-timer is 61 us (clock source = 32768Hz, reload value=1 and reload takes extra 1T)
//#define GTIMER_TICK_US            31   // micro-second, 1000000/32768 ~= 30.5
#define MIN_GTIMER_TIMEOUT    61  // in micro-sec, use this value to set the g-timer to generate tick for PWM. 61=(1000000/32768)*2
#define PWM_GTIMER_TICK_TIME    61  // in micro-sec, use this value to set the g-timer to generate tick for PWM. 61=(1000000/32768)*2

typedef struct _HAL_PWM_ADAPTER_
{
  u8 pwm_id;      // the PWM ID, 0~3
  u8 sel;         // PWM Pin selection, 0~3
  u8 gtimer_id;   // using G-Timer ID, there are 7 G-timer, but we prefer to use timer 3~6
  u8 enable;      // is enabled
//    u32 timer_value;    // the G-Timer auto-reload value, source clock is 32768Hz, reload will takes extra 1 tick. To set the time of a tick of PWM
  u32 tick_time;  // the tick time for the G-timer
  u32 period;    // the period of a PWM control cycle, in PWM tick
  u32 pulsewidth;// the pulse width in a period of a PWM control cycle, in PWM tick. To control the ratio
//    float duty_ratio;   // the dyty ratio = pulswidth/period
} HAL_PWM_ADAPTER, *PHAL_PWM_ADAPTER;

extern HAL_STATUS
HAL_Pwm_Init( HAL_PWM_ADAPTER *pPwmAdapt, u32 pwm_id, u32 sel );

extern void
HAL_Pwm_Enable( HAL_PWM_ADAPTER *pPwmAdapt );

extern void
HAL_Pwm_Disable( HAL_PWM_ADAPTER *pPwmAdapt );

extern void
HAL_Pwm_SetDuty( HAL_PWM_ADAPTER *pPwmAdapt, u32 period, u32 pulse_width );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_PWM_H__ */
