#ifndef __RTL8195AM_IRQ_H__
#define __RTL8195AM_IRQ_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

extern uint32_t __vectors_table[ 32 ];                      /* 0x00000000 */
extern uint32_t NewVectorTable[ 32 ];                       /* 0x10000000 */
extern uint32_t UserIrqFunTable[ 32 ];                      /* 0x10000100 */
extern uint32_t UserIrqDataTable[ 32 ];                     /* 0x10000200 */

// CORE: 64 vectors = 64 bytes from 0x00 to 0x3F
//
// MCU Peripherals: 85 vectors = 340 bytes from 0x40 to ...
// Total: 128 vectors = 512 bytes (0x200) to be reserved in RAM 0x1000-0000..0x1000-01FF
#define NVIC_NUM_VECTORS            128
#define NVIC_USER_IRQ_OFFSET        64

#define PERIPHERAL_IRQ_BASE_NUM     64
#define PERIPHERAL_IRQ_ALL_LEVEL    0
#define PERIPHERAL_IRQ_STATUS       0x04
#define PERIPHERAL_IRQ_MODE         0x08
#define PERIPHERAL_IRQ_EN           0x0C

#define LP_PERI_EXT_IRQ_STATUS      0x24
#define LP_PERI_EXT_IRQ_MODE        0x28
#define LP_PERI_EXT_IRQ_EN          0x2C

#define InterruptForOSInit          VectorTableInitForOSRtl8195A
#define InterruptRegister           VectorIrqRegisterRtl8195A
#define InterruptUnRegister         VectorIrqUnRegisterRtl8195A
#define InterruptEn                 VectorIrqEnRtl8195A
#define InterruptDis                VectorIrqDisRtl8195A

typedef void (*HAL_VECTOR_FUN)( void );

typedef enum _VECTOR_TABLE_TYPE_
{
  DEDECATED_VECTRO_TABLE,
  PERIPHERAL_VECTOR_TABLE
} VECTOR_TABLE_TYPE, *PVECTOR_TABLE_TYPE;

typedef void (*IRQ_FUN)( void *Data );

typedef struct _IRQ_HANDLE_
{
  IRQ_FUN IrqFun;
  IRQn_Type IrqNum;
  u32 Data;
  u32 Priority;
} IRQ_HANDLE, *PIRQ_HANDLE;

extern _LONG_CALL_ROM_ VOID VectorTableInitRtl8195A( IN u32 StackP );
extern _LONG_CALL_ void VectorTableInitForOSRtl8195A( IN void *PortSVC, IN void *PortPendSVH,
  IN void *PortSysTick );
extern _LONG_CALL_ BOOL VectorIrqRegisterRtl8195A( IN PIRQ_HANDLE pIrqHandle );
extern _LONG_CALL_ BOOL VectorIrqUnRegisterRtl8195A( IN PIRQ_HANDLE pIrqHandle );
extern _LONG_CALL_ void VectorIrqEnRtl8195A( IN PIRQ_HANDLE pIrqHandle );
extern _LONG_CALL_ void VectorIrqDisRtl8195A( IN PIRQ_HANDLE pIrqHandle );

extern _LONG_CALL_ROM_ VOID HalPeripheralIntrHandle( VOID );

void NVIC_SetVector( IRQn_Type IRQn, uint32_t vector );
uint32_t NVIC_GetVector( IRQn_Type IRQn );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_IRQ_H__ */
