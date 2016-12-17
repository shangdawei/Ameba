#ifndef __RTL8195AM_ROM_H__
#define __RTL8195AM_ROM_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdint.h>

#if ( 0 )

  extern uint32_t __vectors_table[ 32 ];                      // 0x00000000
  extern uint32_t NewVectorTable[ 32 ];                       // 0x10000000
  extern uint32_t UserIrqFunTable[ 32 ];                      // 0x10000100
  extern uint32_t UserIrqDataTable[ 32 ];                     // 0x10000200
  extern uint32_t CfgSysDebugWarn;                            // 0x10000300
  extern uint32_t CfgSysDebugInfo;                            // 0x10000304
  extern uint32_t CfgSysDebugErr;                             // 0x10000308
  extern uint32_t ConfigDebugWarn;                            // 0x1000030C
  extern uint32_t ConfigDebugInfo;                            // 0x10000310
  extern uint32_t ConfigDebugErr;                             // 0x10000314
  extern HAL_TIMER_OP HalTimerOp;                             // 0x10000318
  extern uint16_t GPIOState[ 11 ];                            // 0x10000334
  extern uint32_t gTimerRecord;                               // 0x1000034C
  extern uint32_t SSI_DBG_CONFIG;                             // 0x10000350
  extern _pHAL_Gpio_Adapter _pHAL_Gpio_Adapter;               // 0x10000354
  extern IRQ_FUN Timer2To7VectorTable[ 6 ];                   // 0x10000358
  extern UART_LOG_CTL UartLogCtl;                             // 0x10000384
  extern UartLogBuf UartLogBuf;                               // 0x100003ac
  extern uint8_t UartLogHistoryBuf[ 5 ][ 127 ];               // 0x1000042c
  extern volatile UART_LOG_CTL* pUartLogCtl;                  // 0x100006a8
  extern uint8_t * ArgvArray[ 10 ];                           // 0x100006ac
  extern _rom_wlan_ram_map rom_wlan_ram_map;                  // 0x100006d4
  extern FALSE_ALARM_STATISTICS FalseAlmCnt;                  // 0x100006e0
  extern ROM_INFO ROMInfo;                                    // 0x10000720
  extern CFO_TRACKING DM_CfoTrack;                            // 0x10000738
  extern _rom_libgloss_ram_map rom_libgloss_ram_map;          // 0x10000760
  extern uint32_t __rtl_errno;                                // 0x10000bc4

#endif

#if (0)
  extern uint32_t __first;                                    // 0x10000370
  extern uint32_t __z1;                                       // 0x10000374
  extern uint32_t __z2;                                       // 0x10000378
  extern uint32_t __z3;                                       // 0x1000037C
  extern uint32_t __z4;                                       // 0x10000380

  extern mbinptr __rtl_malloc_av_[258];                       // 0x10000780
  extern uint32_t __rtl_malloc_trim_threshold;                // 0x10000B88
  extern uint32_t __rtl_malloc_top_pad;                       // 0x10000B8C
  extern uint32_t __rtl_malloc_sbrk_base;                     // 0x10000B90
  extern uint32_t __rtl_malloc_max_sbrked_mem;                // 0x10000B94
  extern uint32_t __rtl_malloc_max_total_mem;                 // 0x10000B98
  extern __rtl_malloc_current_mallinfo mallinfo;              // 0x10000B9C
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_ROM_H__ */
