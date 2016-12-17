#ifndef __RTL8195AM_MACRO_H__
#define __RTL8195AM_MACRO_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdint.h>

#ifndef FAIL
#define FAIL                          ( -1 )
#define SUCCESS                       ( 0 )
#endif

#ifndef _FAIL
#define _FAIL                         ( 0 )
#define _SUCCESS                      ( 1 )
#endif

#define IN
#define OUT
#define INOUT

#define NDIS_OID                      uint32_t
#define NDIS_STATUS                   uint32_t

#ifndef FALSE
#define FALSE                         ( 0 )
#define TRUE                          (!FALSE)
#endif

#ifndef _FALSE
#define _TRUE                         TRUE
#define _FALSE                        FALSE
#endif

#ifndef NULL
#define NULL                          0
#endif

#ifndef VOID
#define VOID                          void
#endif

#ifndef _PTR
#define _PTR                          void *
#endif

#ifndef _AND
#define _AND                          ,
#endif

#define RARG                          struct _reent *reent_ptr,

#ifndef _NOARGS
#define _NOARGS                       void
#endif

#ifndef _CONST
#define _CONST                        const
#endif

#ifndef _VOLATILE
#define _VOLATILE                     volatile
#endif

#ifndef _SIGNED
#define _SIGNED                       signed
#endif

#ifndef _DOTS
#define _DOTS                         , ...
#endif

#ifndef _VOID
#define _VOID                         void
#endif

#define SIZE_PTR                      SIZE_T
#define SSIZE_PTR                     SSIZE_T

#define FIELD_OFFSET(s,field)         ((SSIZE_T)&((s*)(0))->field)

#define MEM_ALIGNMENT_OFFSET          (sizeof (SIZE_T))
#define MEM_ALIGNMENT_PADDING         (sizeof(SIZE_T) - 1)

#ifndef USED
#define USED( x )                     ( void )( x )
#endif

#define PLATFORM_LITTLE_ENDIAN        0
#define PLATFORM_BIG_ENDIAN           1

#define SYSTEM_ENDIAN                 PLATFORM_LITTLE_ENDIAN

#define ROMVERSION                    0x03
#define ROMINFORMATION                (ROMVERSION)

#define CHIP_ID_8711AM                0xFF
#define CHIP_ID_8195AM                0xFE
#define CHIP_ID_8711AF                0xFD
#define CHIP_ID_8710AF                0xFC
#define CHIP_ID_8711AN                0xFB
#define CHIP_ID_8710AM                0xFA

// firmware information, located at the header of Image2
#define FW_VERSION                    (0x0100)
#define FW_SUBVERSION                 (0x0001)

#define FW_CHIP_ID                    (0x8195)
#define FW_CHIP_VER                   (0x01)

#define FW_BUS_TYPE                   (0x01)          // the iNIC firmware type: USB/SDIO

#define FW_INFO_RSV1                  (0x00)          // the firmware information reserved
#define FW_INFO_RSV2                  (0x00)          // the firmware information reserved
#define FW_INFO_RSV3                  (0x00)          // the firmware information reserved
#define FW_INFO_RSV4                  (0x00)          // the firmware information reserved

#define FLASH_SECTOR_SIZE             0x1000
#define FLASH_RESERVED_DATA_BASE      0x8000          // reserve 32K for Image1

#define FLASH_SYSTEM_DATA_ADDR        0x9000          // reserve 32K+4K for Image1 + Reserved data
// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------
// 00009000 00 00 05 00 FF FF FF FF FF FF FF FF FF FF FF FF ................
// 00009010 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
//
// -------------------------------------------------------------------------------------------------
// SPIC Calibration Data
// -------------------------------------------------------------------------------------------------
#define FLASH_SPIC_PARA_OFFSET        0x80
#define FLASH_SPIC_PARA_BASE          ( FLASH_SYSTEM_DATA_ADDR+FLASH_SPIC_PARA_OFFSET)
// -------------------------------------------------------------------------------------------------
// 00009080 02 00 31 01 FD FF CE FE FF FF FF FF FF FF FF FF ..1.............
// 00009090 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// 000090A0 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// 000090B0 01 12 31 01 FE ED CE FE FF FF FF FF FF FF FF FF ..1.............
// 000090C0 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// 000090D0 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// -------------------------------------------------------------------------------------------------
// SDRC Calibration Data
// -------------------------------------------------------------------------------------------------
#define FLASH_SDRC_PARA_OFFSET        0x180
#define FLASH_SDRC_PARA_BASE          ( FLASH_SYSTEM_DATA_ADDR+FLASH_SDRC_PARA_OFFSET)
// -------------------------------------------------------------------------------------------------
// 00009180 01 FE FF FF 00 FF 06 F9 FF FF FF FF FF FF FF FF ................
//
// -------------------------------------------------------------------------------------------------
// ADC Calibration Data
// -------------------------------------------------------------------------------------------------
#define FLASH_ADC_PARA_OFFSET         0x200
#define FLASH_ADC_PARA_BASE           ( FLASH_SYSTEM_DATA_ADDR+FLASH_ADC_PARA_OFFSET)
// -------------------------------------------------------------------------------------------------
// 00009200 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// 00009210 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................

// -------------------------------------------------------------------------------------------------
// Flash Map for Calibration data
// -------------------------------------------------------------------------------------------------
#define FLASH_CAL_DATA_BASE           0xA000
#define FLASH_CAL_DATA_SIZE           0x1000
#define FLASH_CAL_DATA_ADDR(ofs)      ( FLASH_CAL_DATA_BASE + (ofs) )
// -------------------------------------------------------------------------------------------------
// 0000A000 95 81 20 00 10 00 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D
// 0000A010 2D 02 FF FF FF FF C0 00 10 00 FF FF FF FF FF FF
// 0000A020 FF FF 20 20 1A 05 00 00 00 FF D0 00 10 00 3E 00
// 0000A030 01 02 23 00 00 FC 20 04 4C 02 11 87 21 02 E0 00
// 0000A040 10 00 0C 00 22 04 00 08 00 32 FF 21 02 0C 00 22
// 0000A050 2A 01 F0 00 10 00 01 00 00 00 00 00 00 00 00 00
// 0000A060 00 00 02 00 FF FF 00 01 10 00 00 00 00 00 00 00
// 0000A070 00 00 00 00 00 00 00 00 00 00 10 01 10 00 00 EB
// 0000A080 00 6E 01 00 00 00 00 FF FF FF FF FF FF FF 30 01
// 0000A090 10 00 FF 01 00 10 00 FF 00 FF 10 00 FF FF FF FF
// 0000A0A0 FF FF 20 00 10 00 20 20 20 21 21 21 26 26 26 28
// 0000A0B0 28 13 FF FF FF FF C0 00 10 00 FF FF FF FF FF FF
// 0000A0C0 FF FF 22 06 1A 05 00 00 00 FF D0 00 10 00 3E 00
// 0000A0D0 01 02 23 00 00 FC 20 04 4C 02 11 87 21 02 E0 00
// 0000A0E0 10 00 0C 00 22 04 00 08 00 32 FF 21 02 0C 00 22
// 0000A0F0 2A 01 F0 00 10 00 01 00 00 00 00 00 00 00 00 00
// 0000A100 00 00 02 00 FF FF 00 01 10 00 FF 00 00 00 00 00
// 0000A110 00 00 00 00 00 00 00 00 00 00 10 01 10 00 00 00
// 0000A120 EB 00 6E 01 00 00 00 00 A0 0A BF 1B 57 91 30 01
// 0000A130 10 00 FF FF 01 00 10 00 FF 00 FF 10 00 FF FF FF
// 0000A140 FF FF 20 00 10 00 20 20 20 21 21 21 26 26 26 28
// 0000A150 28 13 FF FF FF FF C0 00 10 00 FF FF FF FF FF FF
// 0000A160 FF FF 22 06 1A 05 00 00 00 FF D0 00 10 00 3E 00
// 0000A170 01 02 23 00 00 FC 20 04 4C 02 11 87 21 02 E0 00
// 0000A180 10 00 0C 00 22 04 00 08 00 32 FF 21 02 0C 00 22
// 0000A190 2A 01 F0 00 10 00 01 00 00 00 00 00 00 00 00 00
// 0000A1A0 00 00 02 00 FF FF 00 01 10 00 FF 00 00 00 00 00
// 0000A1B0 00 00 00 00 00 00 00 00 00 00 10 01 10 00 00 00
// 0000A1C0 EB 00 6E 01 00 00 00 00 A0 0A BF 1B 57 AD 30 01
// 0000A1D0 10 00 FF FF 01 00 10 00 FF 00 FF 10 00 FF FF FF
// 0000A1E0 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
// 0000A1F0 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
// 0000A200 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
// 0000A210 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

#ifndef isprint
#define in_range(c, lo, up)                   ((u8)c >= lo && (u8)c <= up)
#define isprint(c)                            in_range(c, 0x20, 0x7f)
#define isdigit(c)                            in_range(c, '0', '9')
#define isodigit(c)                           in_range(c, '0', '7')
#define islower(c)                            in_range(c, 'a', 'z')
#define isxdigit(c)                           (isdigit(c) || in_range(c, 'a', 'f') || in_range(c, 'A', 'F'))
#define isspace(c)                            \
  (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == ',')
#endif

// Fast implementation of tolower() for internal usage. Do not use in your code.
#define _tolower(c)                           ( (c) | 0x20 )

#define SWAP32(x) ((u32)(                     \
      (((u32)(x) & (u32)0x000000ff) << 24) |  \
      (((u32)(x) & (u32)0x0000ff00) <<  8) |  \
      (((u32)(x) & (u32)0x00ff0000) >>  8) |  \
      (((u32)(x) & (u32)0xff000000) >> 24)))

#define SWAP16(x) ((u16)(                     \
      (((u16)(x) & (u16)0x00ff) <<  8) |      \
      (((u16)(x) & (u16)0xff00) >>  8)))

#ifndef rtk_le16_to_cpu
#define rtk_cpu_to_le32(x)                    ((u32)(x))
#define rtk_le32_to_cpu(x)                    ((u32)(x))
#define rtk_cpu_to_le16(x)                    ((u16)(x))
#define rtk_le16_to_cpu(x)                    ((u16)(x))
#define rtk_cpu_to_be32(x)                    SWAP32((x))
#define rtk_be32_to_cpu(x)                    SWAP32((x))
#define rtk_cpu_to_be16(x)                    WAP16((x))
#define rtk_be16_to_cpu(x)                    WAP16((x))
#endif

#define HAL_READ32(base, addr)                rtk_le32_to_cpu(*((volatile u32*)(base + addr)))
#define HAL_WRITE32(base, addr, value32)      ((*((volatile u32*)(base + addr))) = rtk_cpu_to_le32(value32))
#define HAL_READ16(base, addr)                rtk_le16_to_cpu(*((volatile u16*)(base + addr)))
#define HAL_WRITE16(base, addr, value)        ((*((volatile u16*)(base + addr))) = rtk_cpu_to_le16(value))
#define HAL_READ8(base, addr)                 (*((volatile u8*)(base + addr)))
#define HAL_WRITE8(base, addr, value)         ((*((volatile u8*)(base + addr))) = value)

//
// Byte Swapping routine.
//
#define EF1Byte                               (u8)
#define EF2Byte                               le16_to_cpu
#define EF4Byte                               le32_to_cpu

//
// Read LE format data from memory
//
#define ReadEF1Byte(_ptr)                     EF1Byte(*((u8 *)(_ptr)))
#define ReadEF2Byte(_ptr)                     EF2Byte(*((u16 *)(_ptr)))
#define ReadEF4Byte(_ptr)                     EF4Byte(*((u32 *)(_ptr)))

//
// Write LE data to memory
//
#define WriteEF1Byte(_ptr, _val)              (*((u8 *)(_ptr)))=EF1Byte(_val)
#define WriteEF2Byte(_ptr, _val)              (*((u16 *)(_ptr)))=EF2Byte(_val)
#define WriteEF4Byte(_ptr, _val)              (*((u32 *)(_ptr)))=EF4Byte(_val)

//
//  Example:
//    BIT_LEN_MASK_32(0) => 0x00000000
//    BIT_LEN_MASK_32(1) => 0x00000001
//    BIT_LEN_MASK_32(2) => 0x00000003
//    BIT_LEN_MASK_32(32) => 0xFFFFFFFF
//
#define BIT_LEN_MASK_32(__BitLen)                       (0xFFFFFFFF >> (32 - (__BitLen)))
//
//  Example:
//    BIT_OFFSET_LEN_MASK_32(0, 2) => 0x00000003
//    BIT_OFFSET_LEN_MASK_32(16, 2) => 0x00030000
//
#define BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen)   (BIT_LEN_MASK_32(__BitLen) << (__BitOffset))

//
//  Description:
//    Return 4-byte value in host byte ordering from
//    4-byte pointer in litten-endian system.
//
#define LE_P4BYTE_TO_HOST_4BYTE(__pStart)               (EF4Byte(*((u32 *)(__pStart))))

//
//  Description:
//    Translate subfield (continuous bits in little-endian) of 4-byte value in litten byte to
//    4-byte value in host byte ordering.
//
#define LE_BITS_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    ( LE_P4BYTE_TO_HOST_4BYTE(__pStart) >> (__BitOffset) ) \
    & \
    BIT_LEN_MASK_32(__BitLen) \
  )

//
//  Description:
//    Mask subfield (continuous bits in little-endian) of 4-byte value in litten byte oredering
//    and return the result in 4-byte value in host byte ordering.
//
#define LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    LE_P4BYTE_TO_HOST_4BYTE(__pStart) \
    & \
    ( ~ BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen) ) \
  )

//
//  Description:
//    Set subfield of little-endian 4-byte value to specified value.
//
#define SET_BITS_TO_LE_4BYTE(__pStart, __BitOffset, __BitLen, __Value) \
  *((u32 *)(__pStart)) = \
    EF4Byte( \
      LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
      | \
      ( (((u32)__Value) & BIT_LEN_MASK_32(__BitLen)) << (__BitOffset) ) \
    );

#define BIT_LEN_MASK_16(__BitLen) \
    (0xFFFF >> (16 - (__BitLen)))

#define BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen) \
  (BIT_LEN_MASK_16(__BitLen) << (__BitOffset))

#define LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
  (EF2Byte(*((u16 *)(__pStart))))

#define LE_BITS_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    ( LE_P2BYTE_TO_HOST_2BYTE(__pStart) >> (__BitOffset) ) \
    & \
    BIT_LEN_MASK_16(__BitLen) \
  )

#define LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
    & \
    ( ~ BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen) ) \
  )

#define SET_BITS_TO_LE_2BYTE(__pStart, __BitOffset, __BitLen, __Value) \
  *((u16 *)(__pStart)) = \
    EF2Byte( \
      LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
      | \
      ( (((u16)__Value) & BIT_LEN_MASK_16(__BitLen)) << (__BitOffset) ) \
    );

#define BIT_LEN_MASK_8(__BitLen) \
    (0xFF >> (8 - (__BitLen)))

#define BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen) \
  (BIT_LEN_MASK_8(__BitLen) << (__BitOffset))

#define LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
  (EF1Byte(*((u8 *)(__pStart))))

#define LE_BITS_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    ( LE_P1BYTE_TO_HOST_1BYTE(__pStart) >> (__BitOffset) ) \
    & \
    BIT_LEN_MASK_8(__BitLen) \
  )

#define LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
  ( \
    LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
    & \
    ( ~BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen) ) \
  )

#define SET_BITS_TO_LE_1BYTE(__pStart, __BitOffset, __BitLen, __Value) \
  *((u8 *)(__pStart)) = \
    EF1Byte( \
      LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
      | \
      ( (((u8)__Value) & BIT_LEN_MASK_8(__BitLen)) << (__BitOffset) ) \
    );

//pclint
#define LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
  ( \
    LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
  )

//pclint
#define SET_BITS_TO_LE_1BYTE_8BIT(__pStart, __BitOffset, __BitLen, __Value) \
{ \
  *((pu1Byte)(__pStart)) = \
    EF1Byte( \
      LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
      | \
      ((u1Byte)__Value) \
    ); \
}

// Get the N-bytes aligment offset from the current length
#define N_BYTE_ALIGMENT(__Value, __Aligment)                          \
  ( ( __Aligment == 1 ) ? (__Value) : ( ( (__Value + __Aligment - 1) / __Aligment) * __Aligment) )

#define TEST_FLAG(__Flag,__testFlag)          (((__Flag) & (__testFlag)) != 0)
#define SET_FLAG(__Flag, __setFlag)           ((__Flag) |= __setFlag)
#define CLEAR_FLAG(__Flag, __clearFlag)       ((__Flag) &= ~(__clearFlag))

#define TEST_FLAGS(__Flag, __testFlags)       (((__Flag) & (__testFlags)) == (__testFlags))
#define CLEAR_FLAGS(__Flag)                   ((__Flag) = 0)

#ifndef __LONG_MAX__
  /* Minimum and maximum values a 'signed long int' can hold.  (Same as 'int').  */

#if defined (__alpha__) || (defined (__sparc__) && defined(__arch64__)) || defined (__sparcv9) || defined (__s390x__)
#define __LONG_MAX__ 9223372036854775807L
#else
#define __LONG_MAX__ 2147483647L
#endif /* __alpha__ || sparc64 */

#endif

#undef LONG_MIN
#define LONG_MIN (-LONG_MAX-1)

#undef LONG_MAX
#define LONG_MAX __LONG_MAX__

  /* Maximum value an 'unsigned long int' can hold.  (Minimum is 0).  */
#undef ULONG_MAX
#define ULONG_MAX (LONG_MAX * 2UL + 1)

#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ 9223372036854775807LL
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_MACRO_H__ */
