#include "rtl8195am_system.h"

void CPURegBackUp( void )
{
  // ToDo
}

void SYS_PinMux( SYS_PINMUX_ID Id, SYS_PINMUX_LOC Loc, uint32_t OnOff )
{
  extern _LONG_CALL_ uint8_t HalPinCtrlRtl8195A( IN uint32_t Function, IN uint32_t PinLocation,
    IN uint32_t Operation );

  HalPinCtrlRtl8195A( Id, Loc, OnOff );
}
