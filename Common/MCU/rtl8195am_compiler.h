#ifndef __RTL8195AM_COMPILER_H__
#define __RTL8195AM_COMPILER_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdint.h>

#include "rtl8195am_conf.h"
// CONFIG_RELEASE_BUILD_LIBRARIES
// E_CUT_ROM_DOMAIN

#ifdef __GNUC__
#define __weak                  __attribute__((weak))
#define likely(x)               __builtin_expect ((x), 1)
#define unlikely(x)             __builtin_expect ((x), 0)
#endif

#if defined ( __ICCARM__ )
#define __inline__                      inline
#define __inline                        inline
#define __inline_definition     //In dialect C99, inline means that a function's definition is provided
                //only for inlining, and that there is another definition
                //(without inline) somewhere else in the program.
                //That means that this program is incomplete, because if
                //add isn't inlined (for example, when compiling without optimization),
                //then main will have an unresolved reference to that other definition.

                // Do not inline function is the function body is defined .c file and this
                // function will be called somewhere else, otherwise there is compile error
#elif defined ( __CC_ARM   )
#define __inline__      __inline  //__linine__ is not supported in keil compilor, use __inline instead
#define inline        __inline
#define __inline_definition     // for dialect C99
#elif defined   (  __GNUC__  )
#define __inline__                      inline
#define __inline                        inline
#define __inline_definition   inline
#endif


#if defined (__ICCARM__)

#ifndef STRINGIFY
#define STRINGIFY(s)            #s
#endif

#define SECTION(_name)          _Pragma( STRINGIFY(location=_name))
#define ALIGNMTO(_bound)        _Pragma( STRINGIFY(data_alignment=_bound))
#define _PACKED_                __packed
#define _WEAK                   __weak
#define _LONG_CALL_
#define _LONG_CALL_ROM_

#else

#define SECTION(_name)          __attribute__ ((__section__(_name)))
#define ALIGNMTO(_bound)        __attribute__ ((aligned (_bound)))
#define _PACKED_                __attribute__ ((packed))
#define _WEAK                   __attribute__ ((weak))

#ifdef CONFIG_RELEASE_BUILD_LIBRARIES

#define _LONG_CALL_
#define _LONG_CALL_ROM_         __attribute__ ((long_call))

#ifdef E_CUT_ROM_DOMAIN
#undef  _LONG_CALL_ROM_
#define _LONG_CALL_ROM_
#endif

#else

#define _LONG_CALL_             __attribute__ ((long_call))
#define _LONG_CALL_ROM_         _LONG_CALL_

#endif

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_COMPILER_H__ */
