#ifndef __SYSTEM_RTL8195AM_H__
#define __SYSTEM_RTL8195AM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include <rtl8195am_types.h>


extern uint32_t SystemCoreClock;

extern void SystemPrepare( void );

extern void SystemInit( void );

extern void SystemCoreClockUpdate( void );

extern void SystemCoreClockSetup( uint32_t NewSystemCoreClock );

extern uint32_t SystemCoreClockGet( void );

extern void SystemDelayUs( uint32_t Us );

#ifdef __cplusplus
}

#endif

#endif /*__SYSTEM_RTL8195AM_H__ */
