#include "rtl8195am_spic.h"

// =================================================================================================
// The below parts are based on the flash characteristics
// SpicInitPara.flashtype for E_CUT_ROM_DOMAIN
//
#define FLASH_OTHERS            0
#define FLASH_MXIC              1
#define FLASH_MXIC_4IO          2
#define FLASH_WINBOND           3
#define FLASH_MICRON            4
#define FLASH_EON               5

// ====== Flash Command Definition  ================================================================
//
#if ( FLASH_VENDOR_TYPE_NO == FLASH_MICRON_N25Q512A )

/*Common command*/
#define FLASH_CMD_WRSR          0x01            // write status register
#define FLASH_CMD_PP            0x02            // Page Program
#define FLASH_CMD_READ          0x03            // read data
#define FLASH_CMD_WRDI          0x04            // write disable
#define FLASH_CMD_RDSR          0x05            // read status register
#define FLASH_CMD_WREN          0x06            // write enable
#define FLASH_CMD_FREAD         0x0B            // fast read data
#define FLASH_CMD_SE            0x20            // Sector Erase
#define FLASH_CMD_QPP           0x32            // 1-1-4
#define FLASH_CMD_4PP           0x38            // quad page program 1-4-4
#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command 1-1-2
#define FLASH_CMD_RDSFDP        0x5A            // Read SFDP
#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command 1-1-4
#define FLASH_CMD_RDID          0x9F            // read idenfication
#define FLASH_CMD_DPP           0xA2            // 1-1-2
#define FLASH_CMD_RDP           0xAB            // Release from Deep Power-Down
#define FLASH_CMD_DP            0xB9            // Deep Power Down
#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command 1-2-2
#define FLASH_CMD_CE            0xC7            // Chip Erase(or 0xC7)
#define FLASH_CMD_2PP           0xD2            // 1-2-2
#define FLASH_CMD_BE            0xD8            // Block Erase(or 0x52)
#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command 1-4-4

/*Micron Special command*/
#define FLASH_CMD_4PP2          0x12
#define FLASH_CMD_ENQUAD        0x35
#define FLASH_CMD_CFSR          0x50
#define FLASH_CMD_WEVCR         0x61
#define FLASH_CMD_REVCR         0x65
#define FLASH_CMD_RFSR          0x70
#define FLASH_CMD_WVCR          0x81
#define FLASH_CMD_RVCR          0x85
#define FLASH_CMD_WNCR          0xB1
#define FLASH_CMD_RNCR          0xB5
#define FLASH_CMD_DE            0xC4
#define FLASH_CMD_WEAR          0xC5
#define FLASH_CMD_REAR          0xC8
#define FLASH_CMD_EXQUAD        0xF5

/*MXIC Special command*/
#define FLASH_CMD_RDCR          0x15            // read configurate register
#define FLASH_CMD_RDSCUR        0x2B            // read security register
#define FLASH_CMD_WRSCUR        0x2F            // write security register
#define FLASH_CMD_ENSO          0xB1            // enter secured OTP
#define FLASH_CMD_EXSO          0xC1            // exit secured OTP
#define FLASH_CMD_REMS4         0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_REMS2         0xEF            // read ID for 2x I/O mode

#elif ( FLASH_VENDOR_TYPE_NO == FLASH_MXIC_MX25L4006E )

#define FLASH_CMD_WRSR          0x01            // write status register
#define FLASH_CMD_PP            0x02            // Page Program
#define FLASH_CMD_READ          0x03            // read data
#define FLASH_CMD_WRDI          0x04            // write disable
#define FLASH_CMD_RDSR          0x05            // read status register
#define FLASH_CMD_WREN          0x06            // write enable
#define FLASH_CMD_FREAD         0x0B            // fast read data
#define FLASH_CMD_RDCR          0x15            // read configurate register
#define FLASH_CMD_SE            0x20            // Sector Erase
#define FLASH_CMD_RDSCUR        0x2B            // read security register
#define FLASH_CMD_WRSCUR        0x2F            // write security register
#define FLASH_CMD_4PP           0x38            // quad page program
#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command
#define FLASH_CMD_RDSFDP        0x5A            // Read SFDP
#define FLASH_CMD_CE            0x60            // Chip Erase(or 0xC7)
#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command
#define FLASH_CMD_REMS          0x90            // Read Electronic Manufacturer & Device ID
#define FLASH_CMD_RDID          0x9F            // read idenfication
#define FLASH_CMD_RES           0xAB            // Read Electronic ID
#define FLASH_CMD_RDP           0xAB            // Release from Deep Power-Down
#define FLASH_CMD_ENSO          0xB1            // enter secured OTP
#define FLASH_CMD_DP            0xB9            // Deep Power Down
#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command
#define FLASH_CMD_EXSO          0xC1            // exit secured OTP
#define FLASH_CMD_BE            0xD8            // Block Erase(or 0x52)
#define FLASH_CMD_REMS4         0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command
#define FLASH_CMD_REMS2         0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_FF            0xFF            // Release Read Enhanced

#elif ( FLASH_VENDOR_TYPE_NO ==  FLASH_MXIC_MX25L8073E )

#define FLASH_CMD_WRSR          0x01            // write status register
#define FLASH_CMD_PP            0x02            // Page Program
#define FLASH_CMD_READ          0x03            // read data
#define FLASH_CMD_WRDI          0x04            // write disable
#define FLASH_CMD_RDSR          0x05            // read status register
#define FLASH_CMD_WREN          0x06            // write enable
#define FLASH_CMD_FREAD         0x0B            // fast read data
#define FLASH_CMD_SE            0x20            // Sector Erase
#define FLASH_CMD_RDSCUR        0x2B            // read security register
#define FLASH_CMD_WRSCUR        0x2F            // write security register
#define FLASH_CMD_4PP           0x38            // quad page program
#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command
#define FLASH_CMD_BE            0x52            // Block Erase
#define FLASH_CMD_RDSFDP        0x5A            // Read SFDP
#define FLASH_CMD_CE            0x60            // Chip Erase(or 0xC7)
#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command
#define FLASH_CMD_REMS          0x90            // Read Electronic Manufacturer & Device ID
#define FLASH_CMD_RDID          0x9F            // read idenfication
#define FLASH_CMD_RES           0xAB            // Read Electronic ID
#define FLASH_CMD_RDP           0xAB            // Release from Deep Power-Down
#define FLASH_CMD_ENSO          0xB1            // enter secured OTP
#define FLASH_CMD_DP            0xB9            // Deep Power Down
#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command
#define FLASH_CMD_EXSO          0xC1            // exit secured OTP
#define FLASH_CMD_REMS4         0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command
#define FLASH_CMD_REMS2         0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_FF            0xFF            // Release Read Enhanced

#else

#define FLASH_CMD_WRSR          0x01            // write status register
#define FLASH_CMD_PP            0x02            // Page Program
#define FLASH_CMD_READ          0x03            // read data
#define FLASH_CMD_WRDI          0x04            // write disable
#define FLASH_CMD_RDSR          0x05            // read status register
#define FLASH_CMD_WREN          0x06            // write enable
#define FLASH_CMD_FREAD         0x0B            // fast read data
#define FLASH_CMD_SE            0x20            // Sector Erase
#define FLASH_CMD_RDSCUR        0x2B            // read security register
#define FLASH_CMD_WRSCUR        0x2F            // write security register
#define FLASH_CMD_4PP           0x38            // quad page program
#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command
#define FLASH_CMD_BE            0x52            // Block Erase
#define FLASH_CMD_RDSFDP        0x5A            // Read SFDP
#define FLASH_CMD_CE            0x60            // Chip Erase(or 0xC7)
#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command
#define FLASH_CMD_REMS          0x90            // Read Electronic Manufacturer & Device ID
#define FLASH_CMD_RDID          0x9F            // read idenfication
#define FLASH_CMD_RES           0xAB            // Read Electronic ID
#define FLASH_CMD_RDP           0xAB            // Release from Deep Power-Down
#define FLASH_CMD_ENSO          0xB1            // enter secured OTP
#define FLASH_CMD_DP            0xB9            // Deep Power Down
#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command
#define FLASH_CMD_EXSO          0xC1            // exit secured OTP
#define FLASH_CMD_REMS4         0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command
#define FLASH_CMD_REMS2         0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_FF            0xFF            // Release Read Enhanced

#endif

#if (0)

#define FLASH_CMD_ENQUAD        0x35
#define FLASH_CMD_ENSO          0xB1            // enter secured OTP
#define FLASH_CMD_EXQUAD        0xF5
#define FLASH_CMD_EXSO          0xC1            // exit secured OTP
#define FLASH_CMD_FF            0xFF            // Release Read Enhanced
#define FLASH_CMD_FREAD         0x0B            // fast read data
#define FLASH_CMD_PP            0x02            // Page Program
#define FLASH_CMD_QPP           0x32            // 1-1-4

#define FLASH_CMD_RDCR          0x15            // read configurate register
#define FLASH_CMD_RDID          0x9F            // read idenfication
#define FLASH_CMD_RDP           0xAB            // Release from Deep Power-Down
#define FLASH_CMD_RDSCUR        0x2B            // read security register
#define FLASH_CMD_RDSFDP        0x5A            // Read SFDP
#define FLASH_CMD_RDSR          0x05            // read status register
#define FLASH_CMD_READ          0x03            // read data
#define FLASH_CMD_REAR          0xC8
#define FLASH_CMD_REMS          0x90            // Read Electronic Manufacturer & Device ID
#define FLASH_CMD_REMS2         0xEF            // read ID for 2x I/O mode
#define FLASH_CMD_REMS4         0xDF            // read ID for 4x I/O mode
#define FLASH_CMD_RES           0xAB            // Read Electronic ID
#define FLASH_CMD_REVCR         0x65
#define FLASH_CMD_RFSR          0x70
#define FLASH_CMD_RNCR          0xB5
#define FLASH_CMD_RVCR          0x85
#define FLASH_CMD_SE            0x20            // Sector Erase
#define FLASH_CMD_WEAR          0xC5
#define FLASH_CMD_WEVCR         0x61
#define FLASH_CMD_WNCR          0xB1
#define FLASH_CMD_WRDI          0x04            // write disable
#define FLASH_CMD_WREN          0x06            // write enable
#define FLASH_CMD_WRSCUR        0x2F            // write security register
#define FLASH_CMD_WRSR          0x01            // write status register
#define FLASH_CMD_WVCR          0x81
#define FLASH_CMD_CFSR          0x50
#define FLASH_CMD_DE            0xC4
#define FLASH_CMD_DP            0xB9            // Deep Power Down
#define FLASH_CMD_DPP           0xA2            // 1-1-2
#define FLASH_CMD_CE            0x60            // Chip Erase (or 0xC7)
//#define FLASH_CMD_CE          0xC7            // Chip Erase (or 0x60)
#define FLASH_CMD_BE            0x52            // Block Erase (or 0xD8)
//#define FLASH_CMD_BE          0xD8            // Block Erase (or 0x52)

#define FLASH_CMD_2PP           0xD2            // 1-2-2
#define FLASH_CMD_4PP2          0x12

#define FLASH_CMD_4PP           0x38            // quad page program
#define FLASH_CMD_4PP           0x38            // quad page program 1-4-4

#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command
#define FLASH_CMD_2READ         0xBB            // 2 x I/O read  command 1-2-2

#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command
#define FLASH_CMD_4READ         0xEB            // 4 x I/O read  command 1-4-4

#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command
#define FLASH_CMD_DREAD         0x3B            // Double Output Mode command 1-1-2

#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command
#define FLASH_CMD_QREAD         0x6B            // 1I / 4O read command 1-1-4

#endif

// =====  Flash Parameter Definition  ==============================================================
//
#if ( FLASH_VENDOR_TYPE_NO == FLASH_MICRON_N25Q512A )

#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          1
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          1
#define FLASH_WR_2IO_EN         1
#define FLASH_WR_2O_EN          1
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          1
#define FLASH_DM_CYCLE_2O       0x08 // 1-1-2
#define FLASH_DM_CYCLE_2IO      0x04 // 1-2-2
#define FLASH_DM_CYCLE_4O       0x08 // 1-1-4
#define FLASH_DM_CYCLE_4IO      0x08 // 1-4-4
#define FLASH_VLD_DUAL_CMDS     (BIT_WR_BLOCKING | BIT_RD_DUAL_I)// 1-1-2
#define FLASH_VLD_QUAD_CMDS     (BIT_WR_BLOCKING | BIT_RD_QUAD_IO)// 1-4-4
#define FLASH_VLD_QUAD_CMDS2    (BIT_WR_BLOCKING | BIT_RD_QUAD_O)// 1-1-4

#elif ( FLASH_VENDOR_TYPE_NO == FLASH_MXIC_MX25L4006E )

#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          0
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          0
#define FLASH_WR_2IO_EN         1
#define FLASH_WR_2O_EN          0
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          0

#define FLASH_DM_CYCLE_2O       0x04 // 1-1-2
#define FLASH_DM_CYCLE_2IO      0x08 // 1-2-2
#define FLASH_DM_CYCLE_4O       0x04 // 1-1-4
#define FLASH_DM_CYCLE_4IO      0x08 // 1-4-4
#define FLASH_VLD_DUAL_CMDS     (BIT_WR_BLOCKING | BIT_WR_DUAL_II | BIT_RD_DUAL_IO)
#define FLASH_VLD_QUAD_CMDS     (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)

#elif ( FLASH_VENDOR_TYPE_NO == FLASH_MXIC_MX25L8073E )

// This flash model is just for prototype, if you want to use it,
// the code MUST be rechecked according to the flash spec.
#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          0
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          0
#define FLASH_WR_2IO_EN         1
#define FLASH_WR_2O_EN          0
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          0

#define FLASH_DM_CYCLE_2O       0x08
#define FLASH_DM_CYCLE_2IO      0x04
#define FLASH_DM_CYCLE_4O       0x08
#define FLASH_DM_CYCLE_4IO      0x04

#define FLASH_VLD_DUAL_CMDS     (BIT_WR_BLOCKING | BIT_RD_DUAL_IO)
#define FLASH_VLD_QUAD_CMDS     (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)

#else

#define FLASH_RD_2IO_EN         1
#define FLASH_RD_2O_EN          0
#define FLASH_RD_4IO_EN         1
#define FLASH_RD_4O_EN          0
#define FLASH_WR_2IO_EN         1
#define FLASH_WR_2O_EN          0
#define FLASH_WR_4IO_EN         1
#define FLASH_WR_4O_EN          0

#define FLASH_DM_CYCLE_2O       0x08
#define FLASH_DM_CYCLE_2IO      0x04
#define FLASH_DM_CYCLE_4O       0x08
#define FLASH_DM_CYCLE_4IO      0x04

#define FLASH_VLD_DUAL_CMDS     (BIT_WR_BLOCKING | BIT_RD_DUAL_IO)
#define FLASH_VLD_QUAD_CMDS     (BIT_WR_BLOCKING | BIT_WR_QUAD_II | BIT_RD_QUAD_IO)

#endif

extern VOID SpicLoadInitParaFromClockRtl8195A( IN u8 CpuClkMode, IN u8 BaudRate,
    IN PSPIC_INIT_PARA pSpicInitPara );

VOID PatchSpicInitRtl8195A( IN u8 InitBaudRate, IN u8 SpicBitMode )
{

  u32 Value32;
  SPIC_INIT_PARA SpicInitPara;

#ifdef CONFIG_FPGA
  SpicInitPara.BaudRate = 1;// FPGASpicInitPara.BaudRate;
  SpicInitPara.RdDummyCyle = 1;// FPGASpicInitPara.RdDummyCyle;
  SpicInitPara.DelayLine = 0;// FPGASpicInitPara.DelayLine;
#else
  u8 CpuClk;
  CpuClk = ( ( (u8) ( HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_CLK_CTRL1) & ( 0x70 ) ) ) >> 4 );
  SpicLoadInitParaFromClockRtl8195A( CpuClk, InitBaudRate, &SpicInitPara );
#endif
  // Disable SPI_FLASH User Mode
  HAL_SPI_WRITE32( REG_SPIC_SSIENR, 0 );

  HAL_SPI_WRITE32( REG_SPIC_BAUDR, BIT_SCKDV( InitBaudRate ) );

  HAL_SPI_WRITE32( REG_SPIC_SER, BIT_SER );

  Value32 = HAL_SPI_READ32( REG_SPIC_AUTO_LENGTH );

  HAL_SPI_WRITE32( REG_SPIC_AUTO_LENGTH,
      ( ( Value32 & 0xFFFF0000 ) | BIT_RD_DUMMY_LENGTH( SpicInitPara.RdDummyCyle ) ) );

  HAL_WRITE32( PERI_ON_BASE, REG_PESOC_MEM_CTRL,
      ((HAL_READ32(PERI_ON_BASE, REG_PESOC_MEM_CTRL)&0xFFFFFF00)| SpicInitPara.DelayLine) );

  HAL_SPI_WRITE32( REG_SPIC_CTRLR1, BIT_NDF( 4 ) );

  switch ( SpicBitMode )
  {
    case SpicOneBitMode:
    HAL_SPI_WRITE32( REG_SPIC_CTRLR0,
        ( HAL_SPI_READ32( REG_SPIC_CTRLR0 ) & ( ~( BIT_ADDR_CH( 3 ) | BIT_DATA_CH( 3 ) ) ) ) );
    break;

    case SpicDualBitMode:
    HAL_SPI_WRITE32( REG_SPIC_CTRLR0,
        ( ( HAL_SPI_READ32( REG_SPIC_CTRLR0 ) & ( ~( BIT_ADDR_CH( 3 ) | BIT_DATA_CH( 3 ) ) ) ) | ( BIT_ADDR_CH( 1 ) | BIT_DATA_CH( 1 ) ) ) );

    break;

    case SpicQuadBitMode:
    HAL_SPI_WRITE32( REG_SPIC_CTRLR0,
        ( ( HAL_SPI_READ32( REG_SPIC_CTRLR0 ) & ( ~( BIT_ADDR_CH( 3 ) | BIT_DATA_CH( 3 ) ) ) ) | ( BIT_ADDR_CH( 2 ) | BIT_DATA_CH( 2 ) ) ) );
    break;

  }

  // Enable SPI_FLASH User Mode
// HAL_SPI_WRITE32(REG_SPIC_SSIENR, BIT_SPIC_EN);
}
