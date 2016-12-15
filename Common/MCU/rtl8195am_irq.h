#ifndef __RTL8195AM_IRQ_H__
#define __RTL8195AM_IRQ_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"

// CORE: 64 vectors = 64 bytes from 0x00 to 0x3F
// MCU Peripherals: 85 vectors = 340 bytes from 0x40 to ...
// Total: 128 vectors = 512 bytes (0x200) to be reserved in RAM
#define NVIC_NUM_VECTORS            128
#define NVIC_USER_IRQ_OFFSET        64

#define PERIPHERAL_IRQ_ALL_LEVEL    0

void NVIC_SetVector( IRQn_Type IRQn, uint32_t vector );
uint32_t NVIC_GetVector( IRQn_Type IRQn );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_IRQ_H__ */
