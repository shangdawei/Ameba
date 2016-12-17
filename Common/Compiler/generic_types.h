#ifndef __GENERIC_TYPES_H__
#define __GENERIC_TYPES_H__

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
#define __I     volatile              /*!< Defines 'read only' permissions */
#else
#define __I     volatile const        /*!< Defines 'read only' permissions */
#endif
#define __O     volatile              /*!< Defines 'write only' permissions */
#define __IO    volatile              /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */

#define __IM     volatile const       /*! Defines 'read only' structure member permissions */
#define __OM     volatile             /*! Defines 'write only' structure member permissions */
#define __IOM    volatile             /*! Defines 'read / write' structure member permissions */

#endif /* __I */

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

typedef uint32_t ULONG;
typedef uint32_t UINT;
typedef uint16_t USHORT;
typedef uint8_t UCHAR;

typedef uint64_t QWORD;               // 64-bit unsigned
typedef uint32_t DWORD;               // 32-bit unsigned
typedef uint16_t WORD;                // 16-bit unsigned
typedef uint8_t BYTE;                 // 8-bit unsigned

typedef int64_t LONGLONG;             // 64-bit signed
typedef int32_t LONG;                 // 32-bit signed
typedef int16_t SHORT;                // 16-bit signed
typedef int8_t CHAR;                  // 8-bit signed

typedef uint64_t UINT64;              // 64-bit unsigned
typedef uint32_t UINT32;              // 32-bit unsigned
typedef uint16_t UINT16;              // 16-bit unsigned
typedef uint8_t UINT8;                // 8-bit unsigned

typedef int64_t INT64;                // 64-bit signed
typedef int32_t INT32;                // 32-bit signed
typedef int16_t INT16;                // 16-bit signed
typedef int8_t INT8;                  // 8-bit signed

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

typedef union
{
  BYTE Val;
  struct
  {
    uint8_t b0 :1;
    uint8_t b1 :1;
    uint8_t b2 :1;
    uint8_t b3 :1;
    uint8_t b4 :1;
    uint8_t b5 :1;
    uint8_t b6 :1;
    uint8_t b7 :1;
  } bits;
} BYTE_VAL, BYTE_BITS, UINT8_VAL, UINT8_BITS;

typedef union
{
  WORD Val;
  BYTE v[ 2 ];
  struct
  {
    BYTE LB;
    BYTE HB;
  } byte;
  struct
  {
    uint8_t b0 :1;
    uint8_t b1 :1;
    uint8_t b2 :1;
    uint8_t b3 :1;
    uint8_t b4 :1;
    uint8_t b5 :1;
    uint8_t b6 :1;
    uint8_t b7 :1;
    uint8_t b8 :1;
    uint8_t b9 :1;
    uint8_t b10 :1;
    uint8_t b11 :1;
    uint8_t b12 :1;
    uint8_t b13 :1;
    uint8_t b14 :1;
    uint8_t b15 :1;
  } bits;
} WORD_VAL, WORD_BITS, UINT16_VAL, UINT16_BITS;

typedef union
{
  DWORD Val;
  WORD w[ 2 ];
  BYTE v[ 4 ];
  struct
  {
    WORD LW;
    WORD HW;
  } word;
  struct
  {
    BYTE LB;  // Low
    BYTE HB;  // High
    BYTE UB;  // Upper
    BYTE MB;  // Most
  } byte;
  struct
  {
    WORD_VAL low;
    WORD_VAL high;
  } wordUnion;
  struct
  {
    uint8_t b0 :1;
    uint8_t b1 :1;
    uint8_t b2 :1;
    uint8_t b3 :1;
    uint8_t b4 :1;
    uint8_t b5 :1;
    uint8_t b6 :1;
    uint8_t b7 :1;
    uint8_t b8 :1;
    uint8_t b9 :1;
    uint8_t b10 :1;
    uint8_t b11 :1;
    uint8_t b12 :1;
    uint8_t b13 :1;
    uint8_t b14 :1;
    uint8_t b15 :1;
    uint8_t b16 :1;
    uint8_t b17 :1;
    uint8_t b18 :1;
    uint8_t b19 :1;
    uint8_t b20 :1;
    uint8_t b21 :1;
    uint8_t b22 :1;
    uint8_t b23 :1;
    uint8_t b24 :1;
    uint8_t b25 :1;
    uint8_t b26 :1;
    uint8_t b27 :1;
    uint8_t b28 :1;
    uint8_t b29 :1;
    uint8_t b30 :1;
    uint8_t b31 :1;
  } bits;
} DWORD_VAL, UINT32_VAL;

typedef union
{
  QWORD Val;
  DWORD d[ 2 ];
  WORD w[ 4 ];
  BYTE v[ 8 ];
  struct
  {
    DWORD LD;
    DWORD HD;
  } dword;
  struct
  {
    WORD LW;
    WORD HW;
    WORD UW;
    WORD MW;
  } word;
  struct
  {
    uint8_t b0 :1;
    uint8_t b1 :1;
    uint8_t b2 :1;
    uint8_t b3 :1;
    uint8_t b4 :1;
    uint8_t b5 :1;
    uint8_t b6 :1;
    uint8_t b7 :1;
    uint8_t b8 :1;
    uint8_t b9 :1;
    uint8_t b10 :1;
    uint8_t b11 :1;
    uint8_t b12 :1;
    uint8_t b13 :1;
    uint8_t b14 :1;
    uint8_t b15 :1;
    uint8_t b16 :1;
    uint8_t b17 :1;
    uint8_t b18 :1;
    uint8_t b19 :1;
    uint8_t b20 :1;
    uint8_t b21 :1;
    uint8_t b22 :1;
    uint8_t b23 :1;
    uint8_t b24 :1;
    uint8_t b25 :1;
    uint8_t b26 :1;
    uint8_t b27 :1;
    uint8_t b28 :1;
    uint8_t b29 :1;
    uint8_t b30 :1;
    uint8_t b31 :1;
    uint8_t b32 :1;
    uint8_t b33 :1;
    uint8_t b34 :1;
    uint8_t b35 :1;
    uint8_t b36 :1;
    uint8_t b37 :1;
    uint8_t b38 :1;
    uint8_t b39 :1;
    uint8_t b40 :1;
    uint8_t b41 :1;
    uint8_t b42 :1;
    uint8_t b43 :1;
    uint8_t b44 :1;
    uint8_t b45 :1;
    uint8_t b46 :1;
    uint8_t b47 :1;
    uint8_t b48 :1;
    uint8_t b49 :1;
    uint8_t b50 :1;
    uint8_t b51 :1;
    uint8_t b52 :1;
    uint8_t b53 :1;
    uint8_t b54 :1;
    uint8_t b55 :1;
    uint8_t b56 :1;
    uint8_t b57 :1;
    uint8_t b58 :1;
    uint8_t b59 :1;
    uint8_t b60 :1;
    uint8_t b61 :1;
    uint8_t b62 :1;
    uint8_t b63 :1;
  } bits;
} QWORD_VAL, UINT64_VAL;


#ifndef READ_REG

#define READ_REG(REG)                         ((REG))
#define CLEAR_REG(REG)                        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)                   ((REG) = (VAL))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)   \
  WRITE_REG( (REG), ( ( ( READ_REG(REG) ) & (~(CLEARMASK))) | (SETMASK) ) )

#endif

#ifndef READ_BIT

#define READ_BIT(REG, BIT)                    ( (REG) &   (BIT) )
#define SET_BIT(REG, BIT)                     ( (REG) |=  (BIT) )
#define CLEAR_BIT(REG, BIT)                   ( (REG) &= ~(BIT) )
#define ANY_BIT_SET(REG, BIT)               ( ( (REG) & (BITS) ) > 0 )
#define ALL_BIT_SET(REG, BIT)               ( ( (REG) & (BITS) ) == (BITS) )

#endif

#ifndef BIT_
#define BIT_(__n)                             ( 1<<(__n) )
#endif

#ifndef BIT
#define BIT(__n)                              ( 1<<(__n) )
#endif

#ifndef BIT0

#define BIT0                                  0x00000001
#define BIT1                                  0x00000002
#define BIT2                                  0x00000004
#define BIT3                                  0x00000008
#define BIT4                                  0x00000010
#define BIT5                                  0x00000020
#define BIT6                                  0x00000040
#define BIT7                                  0x00000080
#define BIT8                                  0x00000100
#define BIT9                                  0x00000200
#define BIT10                                 0x00000400
#define BIT11                                 0x00000800
#define BIT12                                 0x00001000
#define BIT13                                 0x00002000
#define BIT14                                 0x00004000
#define BIT15                                 0x00008000
#define BIT16                                 0x00010000
#define BIT17                                 0x00020000
#define BIT18                                 0x00040000
#define BIT19                                 0x00080000
#define BIT20                                 0x00100000
#define BIT21                                 0x00200000
#define BIT22                                 0x00400000
#define BIT23                                 0x00800000
#define BIT24                                 0x01000000
#define BIT25                                 0x02000000
#define BIT26                                 0x04000000
#define BIT27                                 0x08000000
#define BIT28                                 0x10000000
#define BIT29                                 0x20000000
#define BIT30                                 0x40000000
#define BIT31                                 0x80000000

#endif

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

#ifdef SUCCESS
#undef SUCCESS
#undef FAIL
#endif
typedef enum
{
  SUCCESS = 0,
  FAIL = !SUCCESS
} ErrorStatus_TypeDef;

#ifndef NULL
#define NULL            ( (void *)(0) )
#endif

#ifdef FALSE
#undef FALSE
#undef TRUE
#endif
typedef enum
{
  FALSE = 0,
  TRUE = !FALSE
}BOOL;

/* Alternate definitions */
#ifdef VOID
#undef VOID
#endif
typedef void VOID;

/* Alternate definitions */
#ifdef PVOID
#undef PVOID
#endif
typedef void * PVOID;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GENERIC_TYPES_H__ */
