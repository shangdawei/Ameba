#ifndef __RTL8195AM_WIFI_H__
#define __RTL8195AM_WIFI_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

struct _rom_wlan_ram_map
{
  unsigned char * (*rtw_malloc)( unsigned int sz );
  void (*rtw_mfree)( unsigned char *pbuf, unsigned int sz );
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_WIFI_H__ */
