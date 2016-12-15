#ifndef __RTL8195AM_TYPES_H__
#define __RTL8195AM_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>

// ---------------------------------------------------------------------------------------------------------------------
// basic_types.h
// ---------------------------------------------------------------------------------------------------------------------
#ifndef __I

// define in core_cm3.h
#ifdef __cplusplus
#define __I     volatile             /*!< Defines 'read only' permissions */
#else
#define __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define __O     volatile             /*!< Defines 'write only' permissions */
#define __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */

#define __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define __OM     volatile            /*! Defines 'write only' structure member permissions */
#define __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#endif /* __I */

typedef const uint32_t ULONG;
typedef const uint32_t UINT;
typedef const uint16_t USHORT;
typedef const uint8_t UCHAR;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;

typedef unsigned int uint;
typedef signed int sint;

typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus_TypeDef, ITStatus_TypeDef;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState_TypeDef;

typedef enum
{
  OFF = 0,
  ON = 1
} OnOffState_TypeDef;

typedef enum
{
  SUCCESS = 0,
  FAIL = !SUCCESS
} ErrorStatus_TypeDef;

typedef unsigned char BOOL;

#define IN
#define OUT
#define INOUT

#define NDIS_OID        uint
#define NDIS_STATUS     uint

#ifndef FALSE
#define FALSE           ( 0 )
#define TRUE            (!FALSE)
#endif

#ifndef _FALSE
#define _TRUE           TRUE
#define _FALSE          FALSE
#endif

#ifndef NULL
#define NULL            0
#endif

#ifndef VOID
#define VOID            void
#endif

#ifndef PVOID
typedef VOID *          PVOID;
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_TYPES_H__ */
