#ifndef __RTL8195AM_CONF_H__
#define __RTL8195AM_CONF_H__

//==================================================================================================
// Chip Cut Select
//
#define CONFIG_CHIP_A_CUT                       ( 0 )   //
#define CONFIG_CHIP_B_CUT                       ( 1 )   // what changed?
#define CONFIG_CHIP_C_CUT                       ( 2 )   // add ...V02  from B to C
#define CONFIG_CHIP_D_CUT                       ( 2 )   // change nothing from C to D
#define CONFIG_CHIP_E_CUT                       ( 4 )   // add ...V04  from D to E
//
//#define CONFIG_CHIP_X_CUT                     CONFIG_CHIP_A_CUT
//#define CONFIG_CHIP_X_CUT                     CONFIG_CHIP_B_CUT
//#define CONFIG_CHIP_X_CUT                     CONFIG_CHIP_C_CUT
//#define CONFIG_CHIP_X_CUT                     CONFIG_CHIP_D_CUT
#define CONFIG_CHIP_X_CUT                       CONFIG_CHIP_E_CUT

//==================================================================================================
// Flash Chip Select
//
#define FLASH_UNKNOWN_UNKNOWN                   0
#define FLASH_MICRON_N25Q512A                   1
#define FLASH_MXIC_MX25L4006E                   2
#define FLASH_MXIC_MX25L8073E                   3
//
//#define FLASH_VENDOR_TYPE_NO                  FLASH_UNKNOWN_UNKNOWN
//#define FLASH_VENDOR_TYPE_NO                  FLASH_MICRON_N25Q512A
//#define FLASH_VENDOR_TYPE_NO                  FLASH_MXIC_MX25L8073E
#define FLASH_VENDOR_TYPE_NO                    FLASH_MXIC_MX25L4006E

//==================================================================================================
// Clock Select ( Can we do it By Chip?)
//
#define PLATFORM_CLOCK                          ( 166666666 )
#define SYSTEM_CLK                              ( PLATFORM_CLOCK )
#define TIMER_CLK                               ( 32*1000 )
#define GTIMER_CLK_HZ                           ( 32768 )
#define GTIMER_TICK_US                          ( 1000000 / GTIMER_CLK_HZ )

//==================================================================================================
// Debug Configuration: CONFIG_DEBUG_LOG : Global
//
// 0 -- CONFIG_DEBUG_ERROR, CONFIG_DEBUG_WARN, CONFIG_DEBUG_INFO Disabled
// 1 -- CONFIG_DEBUG_ERROR, CONFIG_DEBUG_WARN, CONFIG_DEBUG_INFO Enabled individual
//
#define CONFIG_DEBUG_LOG                        ( 1 )

#define CONFIG_DEBUG_ERROR                      ( 1 )
#define CONFIG_DEBUG_WARN                       ( 1 )
#define CONFIG_DEBUG_INFO                       ( 1 )
#define CONFIG_DEBUG_ERR_MSG                    ( 1 )

//==================================================================================================
// Peripheral Configuration
//
#define CONFIG_ADC_EN                           ( 1 )
#define CONFIG_DAC_EN                           ( 1 )
#define CONFIG_GDMA_EN                          ( 1 )
#define CONFIG_GPIO_EN                          ( 1 )
#define CONFIG_I2C_EN                           ( 1 )
#define CONFIG_I2S_EN                           ( 1 )
#define CONFIG_MII_EN                           ( 1 )
#define CONFIG_NFC_EN                           ( 1 )
#define CONFIG_PWM_EN                           ( 1 )
#define CONFIG_SSI_EN                           ( 1 )
#define CONFIG_UART_EN                          ( 1 )
#define CONFIG_USB_EN                           ( 1 )
#define CONFIG_WDG_EN                           ( 1 )
#define CONFIG_CRYPTO_EN                        ( 1 )
#define CONFIG_EFUSE_EN                         ( 1 )
#define CONFIG_SDR_EN                           ( 1 )
#define CONFIG_SPIC_EN                          ( 1 )
#define CONFIG_TIMER_EN                         ( 1 )
#define CONFIG_WIFI_EN                          ( 1 )

//==================================================================================================
// Module Configuration
//
#define CONFIG_CRYPTO_MODULE                    ( 1 )
#define CONFIG_CRYPTO_NORMAL                    ( 1 )
#define CONFIG_EFUSE_MODULE                     ( 1 )
#define CONFIG_EFUSE_NORMAL                     ( 1 )
#define CONFIG_GDMA_MODULE                      ( 1 )
#define CONFIG_GDMA_NORMAL                      ( 1 )
#define CONFIG_GPIO_MODULE                      ( 1 )
#define CONFIG_GPIO_NORMAL                      ( 1 )
#define CONFIG_I2C_MODULE                       ( 1 )
#define CONFIG_I2C_NORMAL                       ( 1 )
#define CONFIG_I2S_MODULE                       ( 1 )
#define CONFIG_I2S_NORMAL                       ( 1 )
#define CONFIG_NFC_MODULE                       ( 1 )
#define CONFIG_NFC_NORMAL                       ( 1 )
#define CONFIG_NORMALL_MODE                     ( 1 )
#define CONFIG_PWM_MODULE                       ( 1 )
#define CONFIG_PWM_NORMAL                       ( 1 )
#define CONFIG_RTLIB_MODULE                     ( 1 )
#define CONFIG_RTLIB_NORMAL                     ( 1 )
#define CONFIG_SDIO_DEVICE_MODULE               ( 1 )
#define CONFIG_SDIO_DEVICE_NORMAL               ( 1 )
#define CONFIG_SDR_MODULE                       ( 1 )
#define CONFIG_SDR_NORMAL                       ( 1 )
#define CONFIG_SOC_PS_MODULE                    ( 1 )
#define CONFIG_SOC_PS_NORMAL                    ( 1 )
#define CONFIG_SPI_COM_MODULE                   ( 1 )
#define CONFIG_SPI_COM_NORMAL                   ( 1 )
#define CONFIG_SPIC_MODULE                      ( 1 )
#define CONFIG_SPIC_NORMAL                      ( 1 )
#define CONFIG_TIMER_MODULE                     ( 1 )
#define CONFIG_TIMER_NORMAL                     ( 1 )
#define CONFIG_UART_MODULE                      ( 1 )
#define CONFIG_UART_NORMAL                      ( 1 )
#define CONFIG_USB_MODULE                       ( 1 )
#define CONFIG_WDG_NORMAL                       ( 1 )
#define CONFIG_WIFI_MODULE                      ( 1 )
#define CONFIG_WIFI_NORMAL                      ( 1 )

#define CONFIG_RTLIB_EN                         ( 1 )
#define CONFIG_SDIO_DEVICE_EN                   ( 1 )
#define CONFIG_SDIO_HOST_EN                     ( 1 )
#define CONFIG_SOC_PS_EN                        ( 1 )
#define CONFIG_SPI_COM_EN                       ( 1 )

#define CONFIG_BOOT_FROM_JTAG                   ( 1 )
#define CONFIG_BOOT_PROCEDURE                   ( 1 )
#define CONFIG_BOOT_TO_UPGRADE_IMG2             ( 1 )

#define CONFIG_CONSOLE_VERIFY_MODE              ( 1 )
#define CONFIG_CPU_166_6MHZ                     ( 1 )
#define CONFIG_CPU_CLK                          ( 1 )

#define CONFIG_IMAGE_PAGE_LOAD                  ( 1 )
#define CONFIG_IMAGE_SEPARATE                   ( 1 )

#define CONFIG_KERNEL                           ( 1 )
#define CONFIG_LINK_ROM_LIB                     ( 1 )
#define CONFIG_NETWORK                          ( 1 )
#define CONFIG_NOR_FLASH                        ( 1 )
#define CONFIG_RELEASE_BUILD_RAM_ALL            ( 1 )
#define CONFIG_RTL8195A                         ( 1 )
#define RTL8195A                                ( 1 )

#define CONFIG_SDR_100MHZ                       ( 1 )
#define CONFIG_SDR_CLK                          ( 1 )

#define CONFIG_UART_LOG_HISTORY                 ( 1 )
#define CONFIG_USB_HOST_ONLY                    ( 1 )
#define CONFIG_USB_TEST                         ( 1 )
#define CONFIG_USB_VERIFY                       ( 1 )

#define CONFIG_WDG                              ( 1 )
#define CONFIG_WITHOUT_MONITOR                  ( 1 )

#define DWC_DEVICE_ONLY                         ( 1 )
#define DWC_HOST_ONLY                           ( 1 )

#define PLATFORM_FREERTOS                       ( 1 )

#define SDR_CLOCK_SEL_VALUE                     ( 0 )

#define TASK_SCHEDULER_DISABLED                 ( 0 )

#define CPU_CLOCK_SEL_VALUE                     ( 0 )

#endif

