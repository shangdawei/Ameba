#ifndef __RTL8195AM_EFUSE_H__
#define __RTL8195AM_EFUSE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

_LONG_CALL_ROM_ extern VOID HalEFUSEPowerSwitch8195AROM( IN u8 bWrite, IN u8 PwrState,
  IN u8 L25OutVoltage );
extern u32 HALEFUSEOneByteReadRAM( IN u32 CtrlSetting, IN u16 Addr, OUT u8 *Data,
  IN u8 L25OutVoltage );
extern u32 HALEFUSEOneByteWriteRAM( IN u32 CtrlSetting, IN u16 Addr, IN u8 Data,
  IN u8 L25OutVoltage );

#define EFUSERead8     HALEFUSEOneByteReadRAM
#define EFUSEWrite8    HALEFUSEOneByteWriteRAM

#define L25EOUTVOLTAGE	7

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_EFUSE_H__ */
