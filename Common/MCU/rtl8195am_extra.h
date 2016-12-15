#ifndef __RTL8195AM_EXTRA_H__
#define __RTL8195AM_EXTRA_H__

#define FW_VERSION                  (0x0100)
#define FW_SUBVERSION               (0x0001)

#define FW_CHIP_ID                  (0x8195)
#define FW_CHIP_VER                 (0x01)

#define FW_BUS_TYPE                 (0x01)          // the iNIC firmware type: USB/SDIO

#define FW_INFO_RSV1                (0x00)          // the firmware information reserved
#define FW_INFO_RSV2                (0x00)          // the firmware information reserved
#define FW_INFO_RSV3                (0x00)          // the firmware information reserved
#define FW_INFO_RSV4                (0x00)          // the firmware information reserved

#define FLASH_SECTOR_SIZE           0x1000
#define FLASH_RESERVED_DATA_BASE    0x8000          // reserve 32K for Image1

#define FLASH_SYSTEM_DATA_ADDR      0x9000          // reserve 32K+4K for Image1 + Reserved data
// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------
// 00009000 00 00 05 00 FF FF FF FF FF FF FF FF FF FF FF FF ................
// 00009010 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
//
// -------------------------------------------------------------------------------------------------
// SPIC Calibration Data
// -------------------------------------------------------------------------------------------------
#define FLASH_SPIC_PARA_OFFSET      0x80
#define FLASH_SPIC_PARA_BASE        (FLASH_SYSTEM_DATA_ADDR+FLASH_SPIC_PARA_OFFSET)
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
#define FLASH_SDRC_PARA_OFFSET      0x180
#define FLASH_SDRC_PARA_BASE        (FLASH_SYSTEM_DATA_ADDR+FLASH_SDRC_PARA_OFFSET)
// -------------------------------------------------------------------------------------------------
// 00009180 01 FE FF FF 00 FF 06 F9 FF FF FF FF FF FF FF FF ................
//
// -------------------------------------------------------------------------------------------------
// ADC Calibration Data
// -------------------------------------------------------------------------------------------------
#define FLASH_ADC_PARA_OFFSET       0x200
#define FLASH_ADC_PARA_BASE         (FLASH_SYSTEM_DATA_ADDR+FLASH_ADC_PARA_OFFSET)
// -------------------------------------------------------------------------------------------------
// 00009200 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................
// 00009210 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF ................

// -------------------------------------------------------------------------------------------------
// Flash Map for Calibration data
// -------------------------------------------------------------------------------------------------
#define FLASH_CAL_DATA_BASE         0xA000
#define FLASH_CAL_DATA_SIZE         0x1000
#define FLASH_CAL_DATA_ADDR(ofs)    (FLASH_CAL_DATA_BASE + (ofs) )
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

#endif






