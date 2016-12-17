#include "rtl8195am_pwm.h"

#ifdef CONFIG_PWM_EN
#include "rtl8195a_pwm.h"
#include "hal_pwm.h"

extern HAL_PWM_ADAPTER PWMPin[];

extern HAL_TIMER_OP HalTimerOp;

/**
 * @brief  Configure a G-Timer to generate a tick with certain time.
 *
 * @param  pwm_id: the PWM pin index
 * @param  tick_time: the time (micro-second) of a tick
 *
 * @retval None
 */
void
Pwm_SetTimerTick_8195a(
    HAL_PWM_ADAPTER *pPwmAdapt,
    u32 tick_time
)
{
  TIMER_ADAPTER TimerAdapter;

  if (tick_time <= MIN_GTIMER_TIMEOUT)
  {
    tick_time = MIN_GTIMER_TIMEOUT;
  }
  else
  {
    tick_time = (((tick_time-1)/TIMER_TICK_US)+1) * TIMER_TICK_US;
  }

  // Initial a G-Timer for the PWM pin
  if (pPwmAdapt->tick_time != tick_time)
  {
    TimerAdapter.IrqDis = 1;    // Disable Irq
    TimerAdapter.IrqHandle.IrqFun = (IRQ_FUN) NULL;
    TimerAdapter.IrqHandle.IrqNum = TIMER2_7_IRQ;
    TimerAdapter.IrqHandle.Priority = 10;
    TimerAdapter.IrqHandle.Data = (u32)NULL;
    TimerAdapter.TimerId = pPwmAdapt->gtimer_id;
    TimerAdapter.TimerIrqPriority = 0;
    TimerAdapter.TimerLoadValueUs = tick_time-1;
    TimerAdapter.TimerMode = 1;// auto-reload with user defined value

    HalTimerOp.HalTimerInit((VOID*) &TimerAdapter);
    pPwmAdapt->tick_time = tick_time;
    DBG_PWM_INFO("%s: Timer_Id=%d Count=%d\n", __FUNCTION__, pPwmAdapt->gtimer_id, tick_time);
  }

}

/**
 * @brief  Set the duty ratio of the PWM pin.
 *
 * @param  pwm_id: the PWM pin index
 * @param  period: the period time, in micro-second.
 * @param  pulse_width: the pulse width time, in micro-second.
 *
 * @retval None
 */
void
HAL_Pwm_SetDuty_8195a(
    HAL_PWM_ADAPTER *pPwmAdapt,
    u32 period,
    u32 pulse_width
)
{
  u32 RegAddr;
  u32 RegValue;
  u32 period_tick;
  u32 pulsewidth_tick;
  u32 tick_time;
  u8 timer_id;
  u8 pwm_id;

  pwm_id = pPwmAdapt->pwm_id;
  // Adjust the tick time to a proper value
  if (period < (MIN_GTIMER_TIMEOUT*2))
  {
    DBG_PWM_ERR ("HAL_Pwm_SetDuty_8195a: Invalid PWM period(%d), too short!!\n", period);
    tick_time = MIN_GTIMER_TIMEOUT;
    period = MIN_GTIMER_TIMEOUT*2;
  }
  else
  {
    tick_time = period / 0x3fc; // a duty cycle be devided into 1020 ticks
    if (tick_time < MIN_GTIMER_TIMEOUT)
    {
      tick_time = MIN_GTIMER_TIMEOUT;
    }
  }

  Pwm_SetTimerTick_8195a(pPwmAdapt, tick_time);
  tick_time = pPwmAdapt->tick_time;
#if 0
  // Check if current tick time needs adjustment
  if ((pPwmAdapt->tick_time << 12) <= period)
  {
    // need a longger tick time
  }
  else if ((pPwmAdapt->tick_time >> 2) >= period)
  {
    // need a shorter tick time
  }
#endif
  period_tick = period/tick_time;
  if (period_tick == 0)
  {
    period_tick = 1;
  }

  if (pulse_width >= period)
  {
//        pulse_width = period-1;
    pulse_width = period;
  }
  pulsewidth_tick = pulse_width/tick_time;
  if (pulsewidth_tick == 0)
  {
//        pulsewidth_tick = 1;
  }

  timer_id = pPwmAdapt->gtimer_id;

  pPwmAdapt->period = period_tick & 0x3ff;
  pPwmAdapt->pulsewidth = pulsewidth_tick & 0x3ff;

  RegAddr = REG_PERI_PWM0_CTRL + (pwm_id*4);
  RegValue = BIT31 | (timer_id<<24) | (pulsewidth_tick<<12) | period_tick;

  HAL_WRITE32(PERI_ON_BASE, RegAddr, RegValue);
}

/**
 * @brief  Initializes and enable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 * @param  sel: pin mux selection
 * @param  timer_id: the G-timer index assigned to this PWM
 *
 * @retval HAL_STATUS
 */
HAL_STATUS
HAL_Pwm_Init_8195a(
    HAL_PWM_ADAPTER *pPwmAdapt
)
{
  u32 pwm_id;
  u32 pin_sel;

  pwm_id = pPwmAdapt->pwm_id;
  pin_sel = pPwmAdapt->sel;
  // Initial a G-Timer for the PWM pin
  Pwm_SetTimerTick_8195a(pPwmAdapt, MIN_GTIMER_TIMEOUT);

  // Set default duty ration
  HAL_Pwm_SetDuty_8195a(pPwmAdapt, 20000, 10000);

  // Configure the Pin Mux
  PinCtrl((PWM0+pwm_id), pin_sel, 1);

  return HAL_OK;
}

/**
 * @brief  Enable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 *
 * @retval None
 */
void
HAL_Pwm_Enable_8195a(
    HAL_PWM_ADAPTER *pPwmAdapt
)
{
  u32 pwm_id;

  pwm_id = pPwmAdapt->pwm_id;
  // Configure the Pin Mux
  if (!pPwmAdapt->enable)
  {
    PinCtrl((PWM0+pwm_id), pPwmAdapt->sel, 1);
    HalTimerOp.HalTimerEn(pPwmAdapt->gtimer_id);
    pPwmAdapt->enable = 1;
  }
}

/**
 * @brief  Disable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 *
 * @retval None
 */
void
HAL_Pwm_Disable_8195a(
    HAL_PWM_ADAPTER *pPwmAdapt
)
{
  u32 pwm_id;

  pwm_id = pPwmAdapt->pwm_id;
  // Configure the Pin Mux
  if (pPwmAdapt->enable)
  {
    PinCtrl((PWM0+pwm_id), pPwmAdapt->sel, 0);
    HalTimerOp.HalTimerDis(pPwmAdapt->gtimer_id);
    pPwmAdapt->enable = 0;
  }
}

#endif  //CONFIG_PWM_EN

#ifdef CONFIG_PWM_EN
#include "hal_pwm.h"
#include "hal_timer.h"

const u8 PWMTimerIdx[MAX_PWM_CTRL_PIN]=
{ 3,4,5,2};  // the G-timer ID used for PWM pin 0~3

/**
 * @brief  Initializes and enable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 * @param  sel: pin mux selection
 *
 * @retval HAL_STATUS
 */
HAL_STATUS
HAL_Pwm_Init(
    HAL_PWM_ADAPTER *pPwmAdapt,
    u32 pwm_id,
    u32 sel
)
{
  u32 timer_id;

  if (NULL == pPwmAdapt)
  {
    DBG_PWM_ERR ("HAL_Pwm_Init: NULL adapter\n");
    return HAL_ERR_PARA;
  }

  if ((pwm_id >= MAX_PWM_CTRL_PIN) || (sel > 3))
  {
    DBG_PWM_ERR ("HAL_Pwm_Init: Invalid PWM index(%d), sel(%d)\n", pwm_id, sel);
    return HAL_ERR_PARA;
  }

  pPwmAdapt->pwm_id = pwm_id;
  pPwmAdapt->sel = sel;
  timer_id = PWMTimerIdx[pwm_id];
  pPwmAdapt->gtimer_id = timer_id;

  if (_FALSE == FunctionChk((pPwmAdapt->pwm_id+PWM0), pPwmAdapt->sel))
  {
    return HAL_ERR_HW;
  }

#ifndef CONFIG_CHIP_E_CUT
  return HAL_Pwm_Init_8195a(pPwmAdapt);
#else
  return HAL_Pwm_Init_8195a_V04(pPwmAdapt);
#endif
}

/**
 * @brief  Disable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 *
 * @retval None
 */
void
HAL_Pwm_Enable(
    HAL_PWM_ADAPTER *pPwmAdapt
)
{
  if (NULL == pPwmAdapt)
  {
    DBG_PWM_ERR ("HAL_Pwm_Enable: NULL adapter\n");
    return;
  }

#ifndef CONFIG_CHIP_E_CUT
  HAL_Pwm_Enable_8195a(pPwmAdapt);
#else
  HAL_Pwm_Enable_8195a_V04(pPwmAdapt);
#endif
}

/**
 * @brief  Disable a PWM control pin.
 *
 * @param  pwm_id: the PWM pin index
 *
 * @retval None
 */
void
HAL_Pwm_Disable(
    HAL_PWM_ADAPTER *pPwmAdapt
)
{
  if (NULL == pPwmAdapt)
  {
    DBG_PWM_ERR ("HAL_Pwm_Disable: NULL adapter\n");
    return;
  }

#ifndef CONFIG_CHIP_E_CUT
  HAL_Pwm_Disable_8195a(pPwmAdapt);
#else
  HAL_Pwm_Disable_8195a_V04(pPwmAdapt);
#endif
}

/**
 * @brief  Set the duty ratio of the PWM pin.
 *
 * @param  pwm_id: the PWM pin index
 * @param  period: the period time, in micro-second.
 * @param  pulse_width: the pulse width time, in micro-second.
 *
 * @retval None
 */
void
HAL_Pwm_SetDuty(
    HAL_PWM_ADAPTER *pPwmAdapt,
    u32 period,
    u32 pulse_width
)
{
  if (NULL == pPwmAdapt)
  {
    DBG_PWM_ERR ("HAL_Pwm_SetDuty: NULL adapter\n");
    return;
  }

#ifndef CONFIG_CHIP_E_CUT
  HAL_Pwm_SetDuty_8195a(pPwmAdapt, period, pulse_width);
#else
  HAL_Pwm_SetDuty_8195a_V04(pPwmAdapt, period, pulse_width);
#endif
}

#endif  // end of "#ifdef CONFIG_PWM_EN"
