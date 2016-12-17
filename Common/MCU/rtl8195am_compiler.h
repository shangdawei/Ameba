#ifndef __RTL8195AM_COMPILER_H__
#define __RTL8195AM_COMPILER_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef STRINGIFY
#define STRINGIFY(s)                            #s
#endif

#if defined (__ICCARM__)

#define __restrict
#define __extension__
#define __inline_definition
#define __inline__                              inline
#define __inline                                inline
#define _PACKED_                                __packed
#define _WEAK                                   __weak
#define SECTION(_name)                          _Pragma( STRINGIFY(location=_name))
#define ALIGNMTO(_bound)                        _Pragma( STRINGIFY(data_alignment=_bound))
#define RTW_PACK_STRUCT_BEGIN                   _Pragma( STRINGIFY(pack(1)))
#define RTW_PACK_STRUCT_STRUCT
#define RTW_PACK_STRUCT_END                     _Pragma( STRINGIFY(pack()))
#define _LONG_CALL_
#define _LONG_CALL_ROM_

#ifndef likely
#define likely(x)                               (x)
#define unlikely(x)                             (x)
#endif

typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;

#endif

#ifdef __GNUC__
#define __weak                                  __attribute__((weak))
#define likely(x)                               __builtin_expect ((x), 1)
#define unlikely(x)                             __builtin_expect ((x), 0)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_COMPILER_H__ */
