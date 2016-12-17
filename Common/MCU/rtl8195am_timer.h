#ifndef __RTL8195AM_TIMER_H__
#define __RTL8195AM_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"
#include "rtl8195am_irq.h"

#define TIMER_TICK_US               31

#define TIMER_LOAD_COUNT_OFF        0x00
#define TIMER_CURRENT_VAL_OFF       0x04
#define TIMER_CTL_REG_OFF           0x08
#define TIMER_EOI_OFF               0x0c
#define TIMER_INT_STATUS_OFF        0x10
#define TIMER_INTERVAL              0x14
#define TIMERS_INT_STATUS_OFF       0xa0
#define TIMERS_EOI_OFF              0xa4
#define TIMERS_RAW_INT_STATUS_OFF   0xa8
#define TIMERS_COMP_VER_OFF         0xac

#define MAX_TIMER_VECTOR_TABLE_NUM  6

#define HAL_TIMER_READ32(addr)            \
  (*((volatile uint32_t*)(TIMER_REG_BASE + addr))) // HAL_READ32(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE32(addr, value)    \
  ((*((volatile uint32_t*)(TIMER_REG_BASE + addr))) = value) // HAL_WRITE32(TIMER_REG_BASE, addr, value)
#define HAL_TIMER_READ16(addr)            \
  (*((volatile u16*)(TIMER_REG_BASE + addr))) // HAL_READ16(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE16(addr, value)    \
  ((*((volatile u16*)(TIMER_REG_BASE + addr))) = value) // HAL_WRITE16(TIMER_REG_BASE, addr, value)
#define HAL_TIMER_READ8(addr)             \
  (*((volatile uint8_t*)(TIMER_REG_BASE + addr))) // HAL_READ8(TIMER_REG_BASE, addr)
#define HAL_TIMER_WRITE8(addr, value)     \
  ((*((volatile uint8_t*)(TIMER_REG_BASE + addr))) = value) // HAL_WRITE8(TIMER_REG_BASE, addr, value)

typedef enum _TIMER_MODE_
{
  FREE_RUN_MODE = 0,
  USER_DEFINED = 1
} TIMER_MODE, *PTIMER_MODE;

typedef struct _TIMER_ADAPTER_
{
  uint32_t TimerLoadValueUs;
  uint32_t TimerIrqPriority;
  TIMER_MODE TimerMode;
  IRQ_HANDLE IrqHandle;
  uint8_t TimerId;
  uint8_t IrqDis;

} TIMER_ADAPTER, *PTIMER_ADAPTER;

typedef struct _HAL_TIMER_OP_
{
  uint32_t (*HalGetTimerId)( uint32_t *TimerId );
  BOOL (*HalTimerInit)( void *Data );
  uint32_t (*HalTimerReadCount)( uint32_t TimerId );
  void (*HalTimerIrqClear)( uint32_t TimerId );
  void (*HalTimerDis)( uint32_t TimerId );
  void (*HalTimerEn)( uint32_t TimerId );
  void (*HalTimerDumpReg)( uint32_t TimerId );
} HAL_TIMER_OP, *PHAL_TIMER_OP;

void HalTimerOpInit_Patch( IN void *Data );
HAL_STATUS HalCommonInit( void );

// ======================================================
// ROM Function prototype
_LONG_CALL_ void HalTimerOpInitV02( IN void *Data );
_LONG_CALL_ uint32_t HalGetTimerIdRtl8195a( IN uint32_t *TimerID );
_LONG_CALL_ BOOL HalTimerInitRtl8195a( IN void *Data );
_LONG_CALL_ uint32_t HalTimerReadCountRtl8195a( IN uint32_t TimerId );
_LONG_CALL_ void HalTimerIrqClearRtl8195a( IN uint32_t TimerId );
_LONG_CALL_ void HalTimerDisRtl8195a( IN uint32_t TimerId );
_LONG_CALL_ void HalTimerEnRtl8195a( IN uint32_t TimerId );
_LONG_CALL_ void HalTimerDumpRegRtl8195a( IN uint32_t TimerId );

void HalTimerIrqEnRtl8195a( IN uint32_t TimerId );
void HalTimerIrqDisRtl8195a( IN uint32_t TimerId );
void HalTimerClearIsrRtl8195a( IN uint32_t TimerId );
void HalTimerEnRtl8195a_Patch( IN uint32_t TimerId );
void HalTimerDisRtl8195a_Patch( IN uint32_t TimerId );
void HalTimerDeInitRtl8195a_Patch( IN void *Data );

#if ( CONFIG_CHIP_X_CUT >= CONFIG_CHIP_C_CUT )
__weak _LONG_CALL_ void HalTimerIrq2To7HandleV02( IN void *Data );
__weak _LONG_CALL_ROM_ HAL_STATUS HalTimerIrqRegisterRtl8195aV02( IN void *Data );
__weak _LONG_CALL_ HAL_STATUS HalTimerInitRtl8195aV02( IN void *Data );
__weak _LONG_CALL_ uint32_t HalTimerReadCountRtl8195aV02( IN uint32_t TimerId );
__weak _LONG_CALL_ void HalTimerReLoadRtl8195aV02( IN uint32_t TimerId, IN uint32_t LoadUs );
__weak _LONG_CALL_ROM_ HAL_STATUS HalTimerIrqUnRegisterRtl8195aV02( IN void *Data );
__weak _LONG_CALL_ void HalTimerDeInitRtl8195aV02( IN void *Data );
#endif

#if (CONFIG_CHIP_X_CUT >= CONFIG_CHIP_E_CUT )
_LONG_CALL_ void HalTimerReLoadRtl8195a_V04( IN uint32_t TimerId, IN uint32_t LoadUs );
_LONG_CALL_ HAL_STATUS HalTimerInitRtl8195a_V04( IN void *Data );
#endif

// ROM Code patch
HAL_STATUS HalTimerInitRtl8195a_Patch( IN void *Data );
uint32_t HalTimerReadCountRtl8195a_Patch( IN uint32_t TimerId );
void HalTimerReLoadRtl8195a_Patch( IN uint32_t TimerId, IN uint32_t LoadUs );
uint32_t HalTimerReadCountRtl8195a_Patch( IN uint32_t TimerId );

// #define HalTimerOpInit      HalTimerOpInit_Patch
void HalTimerOpInit( void *Data );

void HalTimerEnable( uint32_t TimerId );
void HalTimerDisable( uint32_t TimerId );
void HalTimerReLoad( uint32_t TimerId, uint32_t LoadUs );
void HalTimerDeInit( void *Data );
HAL_STATUS HalTimerInit( void *Data );

__STATIC_INLINE HAL_STATUS HalTimerInit( IN void *Data )
{
#if (CONFIG_CHIP_X_CUT >= CONFIG_CHIP_E_CUT )
  return ( HalTimerInitRtl8195a_V04( Data ) );
#else
  return ( HalTimerInitRtl8195a_Patch( Data ) );
#endif
}

__STATIC_INLINE void HalTimerEnable( IN uint32_t TimerId )
{
  HalTimerIrqEnRtl8195a( TimerId );
  HalTimerEnRtl8195a_Patch( TimerId );
}

__STATIC_INLINE void HalTimerDisable( IN uint32_t TimerId )
{
  HalTimerDisRtl8195a_Patch( TimerId );
}

__STATIC_INLINE void HalTimerClearIsr( IN uint32_t TimerId )
{
  HalTimerClearIsrRtl8195a( TimerId );
}

__STATIC_INLINE void HalTimerReLoad( IN uint32_t TimerId, IN uint32_t LoadUs )
{
#if (CONFIG_CHIP_X_CUT >= CONFIG_CHIP_E_CUT )
  HalTimerReLoadRtl8195a_V04( TimerId, LoadUs );
#else
  HalTimerReLoadRtl8195a_Patch( TimerId, LoadUs );
#endif
}

#if ( CONFIG_CHIP_X_CUT >= CONFIG_CHIP_C_CUT )
__STATIC_INLINE void HalTimerDeInit( IN void *Data )
{
  HalTimerDeInitRtl8195aV02( Data );
}
#else
__STATIC_INLINE void HalTimerDeInit( IN void *Data )
{
  HalTimerDeInitRtl8195a_Patch( Data );
}
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_TIMER_H__ */
