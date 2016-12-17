#ifndef __RTL8195AM_CONSOL_H__
#define __RTL8195AM_CONSOL_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

#define CONSOLE_PREFIX	"#"


#define KB_ASCII_NUL    0x00
#define KB_ASCII_BS     0x08
#define KB_ASCII_TAB    0x09
#define KB_ASCII_LF     0x0A
#define KB_ASCII_CR     0x0D
#define KB_ASCII_ESC    0x1B
#define KB_ASCII_SP     0x20
#define KB_ASCII_BS_7F  0x7F
#define KB_ASCII_LBRKT  0x5B         //[

#define KB_SPACENO_TAB  1


#ifdef CONFIG_DEBUG_LOG
#define _ConsolePrint  DiagPrintf
#else
#define _ConsolePrint
#endif

#ifndef CONSOLE_PREFIX
#define CONSOLE_PREFIX	"<RTL8195A>"
#endif

#define CONSOLE_8195A(...)     do {\
    _ConsolePrint("\r"CONSOLE_PREFIX __VA_ARGS__);\
}while(0)

_LONG_CALL_ VOID
RtlConsolInit( IN u32 Boot, IN u32 TBLSz,
IN VOID *pTBL );

#if defined(CONFIG_KERNEL)
_LONG_CALL_ VOID
RtlConsolTaskRam(
    VOID *Data
);
#endif

_LONG_CALL_ VOID
RtlConsolTaskRom(
VOID *Data );

_LONG_CALL_ u32
Strtoul( IN const u8 *nptr, IN u8 **endptr, IN u32 base );

void console_init( void );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_CONSOL_H__ */
