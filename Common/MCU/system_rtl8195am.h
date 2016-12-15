#ifndef __SYSTEM_RTL8195AM_H__
#define __SYSTEM_RTL8195AM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include <rtl8195am_types.h>

#define __HSI             ( 8000000UL)
#define __XTAL            ( 5000000UL)            /* Oscillator frequency             */
#define __SYSTEM_CLOCK    (200000000UL/6*5)       /* System Core frequency            */

extern uint32_t SystemCoreClock;

extern void SystemInit( void );

extern void SystemCoreClockUpdate( void );

extern uint32_t SystemCoreClockGet( void );

extern void SystemDelayUs( uint32_t Us );

#ifdef __cplusplus
}

#endif

#endif /*__SYSTEM_RTL8195AM_H__ */
