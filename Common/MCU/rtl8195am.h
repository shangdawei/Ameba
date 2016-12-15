#ifndef __RTL8195AM_H__
#define __RTL8195AM_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

 /**
  * @brief RTL8195AM Standard Peripherals Library version number V1.0.0
    */
 #define __RTL8195AM_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
 #define __RTL8195AM_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
 #define __RTL8195AM_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
 #define __RTL8195AM_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
 #define __RTL8195AM_STDPERIPH_VERSION        ( ( __RTL8195AM_STDPERIPH_VERSION_MAIN << 24 ) \
                                              | ( __RTL8195AM_STDPERIPH_VERSION_SUB1 << 16 ) \
                                              | ( __RTL8195AM_STDPERIPH_VERSION_SUB2 <<  8 ) \
                                              | ( __RTL8195AM_STDPERIPH_VERSION_RC ) )

/**
 * @brief Configuration of the Cortex-M3 Processor and Core Peripherals
 */

#define __CM3_REV                      0x0200    /**< Core revision r0p0 */
#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         1         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  0         /*!< No FPU */

/**
 * @brief RTL8195AM Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

  /******  RTL8195A Specific Interrupt Numbers ************/

  SYSTEM_ON_IRQ               =  0,
  WDG_IRQ                     =  1,
  TIMER0_IRQ                  =  2,
  TIMER1_IRQ                  =  3,
  I2C3_IRQ                    =  4,
  TIMER2_7_IRQ                =  5,
  SPI0_IRQ                    =  6,
  GPIO_IRQ                    =  7,
  UART0_IRQ                   =  8,
  SPI_FLASH_IRQ               =  9,
  USB_OTG_IRQ                 =  10,
  SDIO_HOST_IRQ               =  11,
  SDIO_DEVICE_IRQ             =  12,
  I2S0_PCM0_IRQ               =  13,
  I2S1_PCM1_IRQ               =  14,
  WL_DMA_IRQ                  =  15,
  WL_PROTOCOL_IRQ             =  16,
  CRYPTO_IRQ                  =  17,
  GMAC_IRQ                    =  18,
  PERIPHERAL_IRQ              =  19,  // Handle IRQ[32..63]
  GDMA0_CHANNEL0_IRQ          =  20,
  GDMA0_CHANNEL1_IRQ          =  21,
  GDMA0_CHANNEL2_IRQ          =  22,
  GDMA0_CHANNEL3_IRQ          =  23,
  GDMA0_CHANNEL4_IRQ          =  24,
  GDMA0_CHANNEL5_IRQ          =  25,
  GDMA1_CHANNEL0_IRQ          =  26,
  GDMA1_CHANNEL1_IRQ          =  27,
  GDMA1_CHANNEL2_IRQ          =  28,
  GDMA1_CHANNEL3_IRQ          =  29,
  GDMA1_CHANNEL4_IRQ          =  30,
  GDMA1_CHANNEL5_IRQ          =  31,

  /******  RTL8195A PERIPHERAL_IRQ Numbers : Status and Mask ************/
  I2C0_IRQ                    =  64,
  I2C1_IRQ                    =  65,
  I2C2_IRQ                    =  66,
  DUMMY0_IRQ                  =  67,
  DUMMY1_IRQ                  =  68,
  DUMMY2_IRQ                  =  69,
  DUMMY3_IRQ                  =  70,
  DUMMY4_IRQ                  =  71,
  SPI1_IRQ                    =  72,
  SPI2_IRQ                    =  73,
  DUMMY5_IRQ                  =  74,
  DUMMY6_IRQ                  =  75,
  DUMMY7_IRQ                  =  76,
  DUMMY8_IRQ                  =  77,
  DUMMY9_IRQ                  =  78,
  DUMMY10_IRQ                 =  79,
  UART1_IRQ                   =  80,
  UART2_IRQ                   =  81,
  DUMMY11_IRQ                 =  82,
  DUMMY12_IRQ                 =  83,
  DUMMY13_IRQ                 =  84,
  DUMMY14_IRQ                 =  85,
  DUMMY15_IRQ                 =  86,
  DUMMY16_IRQ                 =  87,
  UART_LOG_IRQ                =  88,
  ADC_IRQ                     =  89,
  DUMMY17_IRQ                 =  90,
  DAC0_IRQ                    =  91,
  DAC1_IRQ                    =  92,
  LP_EXTENSION_IRQ            =  93,  // Handle IRQ[96..127]
  DUMMY18_IRQ                 =  94,
  PTA_TRX_IRQ                 =  95,

  /******  RTL8195A LP_EXTENSION_IRQ Numbers : Status and Mask ************/
  RXI300_IRQ                  =  96,
  NFC_IRQ                     =  97,
  LAST_IRQ                    =  127

} IRQn_Type;

#include "core_cm3.h"            /* Cortex-M3 processor and core peripherals */
#include "system_rtl8195am.h"    /* RTL8195AM System Header */
#include <stdint.h>



/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief Analog to Digital Converter
  */
typedef struct
{
  __IO uint32_t CR;
} ADC_TypeDef;

/**
  * @brief Digital to Analog Converter
  */
typedef struct
{
  __IO uint32_t CR;
} DAC_TypeDef;

/**
  * @brief GDMA Controller
  */
typedef struct
{
  __IO uint32_t CR;
} GDMA_TypeDef;

/**
  * @brief GPIO General Purpose I/O
  */
typedef struct
{
  __IO uint32_t CR;
} GPIO_TypeDef;

/**
  * @brief I2C Inter-integrated Circuit Interface
  */
typedef struct
{
  __IO uint32_t CR;
} I2C_TypeDef;

/**
  * @brief I2S Inter Inter-Iintegrated Circuit Sound Interface
  */
typedef struct
{
  __IO uint32_t CR;
} I2S_TypeDef;

/**
  * @brief MII Interface
  */
typedef struct
{
  __IO uint32_t CR;
} MII_TypeDef;

/**
  * @brief NFC Interface
  */
typedef struct
{
  __IO uint32_t CR;
} NFC_TypeDef;

/**
  * @brief PCM Interface
  */
typedef struct
{
  __IO uint32_t CR;
} PCM_TypeDef;

/**
  * @brief PWM Interface
  */
typedef struct
{
  __IO uint32_t CR;
} PWM_TypeDef;


/**
  * @brief SSI Interface
  */
typedef struct
{
  __IO uint32_t CR;
} SSITypeDef;

/**
  * @brief UART Interface
  */
typedef struct
{
  __IO uint32_t CR;
} UART_TypeDef;

/**
  * @brief USB Interface
  */

/**
  * @brief WDT Interface
  */
typedef struct
{
  __IO uint32_t CR;
} WDT_TypeDef;

// ---------------------------------------------------------------------------------------------------------------------
// hal_platform.h
// ---------------------------------------------------------------------------------------------------------------------

#define ROM_BASE                  ((uint32_t)0x00000000) /*!< ROM base address in the alias region */
#define SRAM_BASE                 ((uint32_t)0x10000000) /*!< SRAM base address in the alias region */
#define TCM_BASE                  ((uint32_t)0x1FFF0000) /*!< TCM base address in the alias region */
#define SDRAM_BASE                ((uint32_t)0x30000000) /*!< SDRAM base address in the alias region */
#define PERIPH_BASE               ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define FLASH_BASE                ((uint32_t)0x98000000) /*!< FLASH base address in the alias region */

#define SRAM_BB_BASE              ((uint32_t)0x00000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE            ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */


/*!< Peripheral memory map */
#define PERI_ON_BASE              ( PERIPH_BASE + 0x00000000 )
#define SYSTEM_CTRL_BASE          ( PERIPH_BASE + 0x00000000 )
#define SYS_REG_BASE              ( PERIPH_BASE + 0x00000000 )
#define GPIO_REG_BASE             ( PERIPH_BASE + 0x00001000 )
#define TIMER_REG_BASE            ( PERIPH_BASE + 0x00002000 )
#define NFC_INTERFACE_BASE        ( PERIPH_BASE + 0x00002400 )
#define VENDOR_REG_BASE           ( PERIPH_BASE + 0x00002800 )
#define LOG_UART_REG_BASE         ( PERIPH_BASE + 0x00003000 )
#define I2C2_REG_BASE             ( PERIPH_BASE + 0x00003400 )
#define I2C3_REG_BASE             ( PERIPH_BASE + 0x00003800 )
#define SDR_CTRL_BASE             ( PERIPH_BASE + 0x00005000 )
#define SPI_FLASH_CTRL_BASE       ( PERIPH_BASE + 0x00006000 )
#define ADC_REG_BASE              ( PERIPH_BASE + 0x00010000 )
#define DAC_REG_BASE              ( PERIPH_BASE + 0x00011000 )
#define UART0_REG_BASE            ( PERIPH_BASE + 0x00040000 )
#define UART1_REG_BASE            ( PERIPH_BASE + 0x00040400 )
#define UART2_REG_BASE            ( PERIPH_BASE + 0x00040800 )
#define SPI0_REG_BASE             ( PERIPH_BASE + 0x00042000 )
#define SPI1_REG_BASE             ( PERIPH_BASE + 0x00042400 )
#define SPI2_REG_BASE             ( PERIPH_BASE + 0x00042800 )
#define I2C0_REG_BASE             ( PERIPH_BASE + 0x00044000 )
#define I2C1_REG_BASE             ( PERIPH_BASE + 0x00044400 )
#define MII_REG_BASE              ( PERIPH_BASE + 0x00050000 )
#define SDIO_HOST_REG_BASE        ( PERIPH_BASE + 0x00058000 )
#define GDMA0_REG_BASE            ( PERIPH_BASE + 0x00060000 )
#define GDMA1_REG_BASE            ( PERIPH_BASE + 0x00061000 )
#define I2S0_REG_BASE             ( PERIPH_BASE + 0x00062000 )
#define I2S1_REG_BASE             ( PERIPH_BASE + 0x00063000 )
#define PCM0_REG_BASE             ( PERIPH_BASE + 0x00064000 )
#define PCM1_REG_BASE             ( PERIPH_BASE + 0x00065000 )
#define CRYPTO_REG_BASE           ( PERIPH_BASE + 0x00070000 )
#define WIFI_REG_BASE             ( PERIPH_BASE + 0x00080000 )
#define USB_OTG_REG_BASE          ( PERIPH_BASE + 0x000C0000 )


#define GDMA1_REG_OFF               0x1000
#define I2S1_REG_OFF                0x1000
#define PCM1_REG_OFF                0x1000
#define SSI_REG_OFF                 0x400
#define RUART_REG_OFF               0x400


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/* Includes ------------------------------------------------------------------*/
#include "rtl8195am_conf.h"

#include "rtl8195am_adc.h"
#include "rtl8195am_dac.h"
#include "rtl8195am_gdma.h"
#include "rtl8195am_gpio.h"
#include "rtl8195am_gspi.h"
#include "rtl8195am_i2c.h"
#include "rtl8195am_i2s.h"
#include "rtl8195am_irq.h"
#include "rtl8195am_mii.h"
#include "rtl8195am_misc.h"
#include "rtl8195am_nfc.h"
#include "rtl8195am_pcm.h"
#include "rtl8195am_peri_on.h"
#include "rtl8195am_pinmux.h"
#include "rtl8195am_pwm.h"
#include "rtl8195am_ssi.h"
#include "rtl8195am_util.h"
#include "rtl8195am_sdio.h"
#include "rtl8195am_sdio_host.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_sdr_controller.h"
#include "rtl8195am_spi_flash.h"
#include "rtl8195am_ssi.h"
#include "rtl8195am_sys_on.h"
#include "rtl8195am_timer.h"
#include "rtl8195am_uart.h"
#include "rtl8195am_log_uart.h"
#include "rtl8195am_usb.h"
#include "rtl8195am_wdt.h"

#include "rtl8195am_crypto.h"
#include "rtl8195am_efuse.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_spic.h"
#include "rtl8195am_wifi.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_H__ */


