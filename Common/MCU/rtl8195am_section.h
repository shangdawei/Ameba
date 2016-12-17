#ifndef __RTL8195AM_MISC_H__
#define __RTL8195AM_MISC_H__

#ifdef __cplusplus
extern "C"
{ 
#endif /* __cplusplus */
  
#include "rtl8195am_macro.h"
  
#define RAM_DEDECATED_VECTOR_TABLE_SECTION                    SECTION(".ram_dedecated_vector_table")
#define RAM_USER_IRQ_FUN_TABLE_SECTION                        SECTION(".ram_user_define_irq_table")
#define RAM_USER_IRQ_DATA_TABLE_SECTION                       SECTION(".ram_user_define_data_table")
  
// Timer Section
#define SECTION_RAM_TIMER2TO7_VECTOR_TABLE                    SECTION(".timer2_7_vector_table.data")
#define SECTION_RAM_BSS_TIMER_RECORDER_TABLE                  SECTION(".timer.ram.data")
#define TIMER_ROM_TEXT_SECTION                                SECTION(".timer.rom.text")
#define TIMER_ROM_DATA_SECTION                                SECTION(".timer.rom.rodata")
#define TIMER_RAM_TEXT_SECTION                                SECTION(".timer.ram.text")
#define TIMER_RAM_DATA_SECTION                                SECTION(".timer.ram.data")
  
// Wifi Section
#define WIFI_ROM_TEXT_SECTION                                 SECTION(".wifi.rom.text")
#define WIFI_ROM_DATA_SECTION                                 SECTION(".wifi.rom.rodata")
#define WIFI_RAM_TEXT_SECTION                                 SECTION(".wifi.ram.text")
#define WIFI_RAM_DATA_SECTION                                 SECTION(".wifi.ram.data")
  
// Hal Section
#define HAL_ROM_TEXT_SECTION                                  SECTION(".hal.rom.text")
#define HAL_ROM_DATA_SECTION                                  SECTION(".hal.rom.rodata")
#define HAL_RAM_TEXT_SECTION                                  SECTION(".hal.ram.text")
#define HAL_FLASH_TEXT_SECTION                                SECTION(".hal.flash.text")
#define HAL_FLASH_DATA_SECTION                                SECTION(".hal.flash.data")
#define HAL_SDRC_TEXT_SECTION                                 SECTION(".hal.sdrc.text")
#define HAL_SDRC_DATA_SECTION                                 SECTION(".hal.sdrc.data")
#define HAL_CUT_B_RAM_DATA_SECTION                            SECTION(".cutb.ram.data")
#define HAL_CUT_C_RAM_DATA_SECTION                            SECTION(".cutc.ram.data")
#define HAL_RAM_DATA_SECTION                                  SECTION(".hal.ram.data")
#define HAL_RAM_BSS_SECTION                                   SECTION(".hal.ram.bss")
#define HAL_ROM_OP_SECTION                                    SECTION(".halop.rom.rodata")
#define HAL_GPIO_TEXT_SECTION                                 SECTION(".hal.gpio.text")
#define HAL_GPIO_DATA_SECTION                                 SECTION(".hal.gpio.data")
#define FWU_DATA_SECTION                                      SECTION(".fwu.data")
#define FWU_RODATA_SECTION                                    SECTION(".fwu.rodata")
#define FWU_TEXT_SECTION                                      SECTION(".fwu.text")
  
// C-Cut ROM Patch/New functions location
#define C_CUT_ROM_TEXT_SECTION                                SECTION(".cutc.rom.text")
#define C_CUT_ROM_RODATA_SECTION                              SECTION(".cutc.rom.rodata")
#define C_CUT_ROM_DATA_SECTION                                SECTION(".cutc.ram.data")
  
// No ROM code changed for D_Cut, so no D-Cut section
// E-Cut ROM Patch/New functions location
#define E_CUT_ROM_TEXT_SECTION                                SECTION(".cute.rom.text")
#define E_CUT_ROM_RODATA_SECTION                              SECTION(".cute.rom.rodata")
#define E_CUT_ROM_DATA_SECTION                                SECTION(".cute.ram.data")
  
  //#define FWUROM_DATA_SECTION                  //           SECTION(".fwurom.data")
//#define FWUROM_RODATA_SECTION                  //         SECTION(".fwurom.rodata")
#define FWUROM_TEXT_SECTION                                   SECTION(".fwurom.text")
#define XMPORT_ROM_TEXT_SECTION                               SECTION(".xmportrom.text")
#define XDMROM_TEXT_SECTION                                   SECTION(".xmodemrom.text")
  
// Store the Image 1 validate code
#define IMAGE1_VALID_PATTEN_SECTION                           SECTION(".image1.validate.rodata")
#define IMAGE2_VALID_PATTEN_SECTION                           SECTION(".image2.validate.rodata")
  
// Infra Section
#define INFRA_ROM_TEXT_SECTION                                SECTION(".infra.rom.text")
#define INFRA_ROM_DATA_SECTION                                SECTION(".infra.rom.rodata")
#define INFRA_RAM_TEXT_SECTION                                SECTION(".infra.ram.text")
#define INFRA_RAM_DATA_SECTION                                SECTION(".infra.ram.data")
#define INFRA_RAM_BSS_SECTION                                 SECTION(".infra.ram.bss")
#define INFRA_START_SECTION                                   SECTION(".infra.ram.start")
  
// Pin Mutex  Section
#define PINMUX_ROM_TEXT_SECTION                               SECTION(".hal.rom.text")
#define PINMUX_ROM_DATA_SECTION                               SECTION(".hal.rom.rodata")
#define PINMUX_RAM_TEXT_SECTION                               SECTION(".hal.ram.text")
#define PINMUX_RAM_DATA_SECTION                               SECTION(".hal.ram.data")
#define PINMUX_RAM_BSS_SECTION                                SECTION(".hal.ram.bss")
  
// Monitor App Section
#define MON_ROM_TEXT_SECTION                                  SECTION(".mon.rom.text")
#define MON_ROM_DATA_SECTION                                  SECTION(".mon.rom.rodata")
#define MON_RAM_TEXT_SECTION                                  SECTION(".mon.ram.text")
#define MON_RAM_DATA_SECTION                                  SECTION(".mon.ram.data")
#define MON_RAM_BSS_SECTION                                   SECTION(".mon.ram.bss")
  
// SDIO Section
#define SECTION_SDIO_RAM
#define SECTION_SDIO_ROM
#define SDIO_ROM_BSS_SECTION                                  SECTION(".sdio.rom.bss")
#define SDIO_ROM_TEXT_SECTION                                 SECTION(".sdio.rom.text")
  
// SRAM Config Section
#define SRAM_BD_DATA_SECTION                                  SECTION(".bdsram.data")
#define SRAM_BF_DATA_SECTION                                  SECTION(".bfsram.data")
#define START_RAM_FUN_SECTION                                 SECTION(".start.ram.data")
#define START_RAM_FUN_A_SECTION                               SECTION(".start.ram.data.a")
#define START_RAM_FUN_B_SECTION                               SECTION(".start.ram.data.b")
#define START_RAM_FUN_C_SECTION                               SECTION(".start.ram.data.c")
#define START_RAM_FUN_D_SECTION                               SECTION(".start.ram.data.d")
#define START_RAM_FUN_E_SECTION                               SECTION(".start.ram.data.e")
  
  //Non-Flash Boot Section
#define NON_FLASH_BOOT_DATA_SECTION                           SECTION(".nonflash.data")
#define NON_FLASH_BOOT_HEAP_SECTION                           SECTION(".nonflash.heap")
  
// USB OTG Section
#define OTG_ROM_BSS_SECTION                                   SECTION(".otg.rom.bss")
  
#if  defined(CONFIG_CHIP_E_CUT) || defined(CONFIG_USB_BOOT_SIM)
#define OTG_ROM_TEXT_SECTION                                  SECTION(".otg.rom.text")
#define OTG_ROM_DATA_SECTION                                  SECTION(".otg.rom.rodata")
#define START_OTG_RAM_FUN_SECTION                             SECTION(".ram.otg.data.a")
#define START_OTG_RAM_DATA_SECTION                            SECTION(".ram.otg.data.b")
#else
#define OTG_ROM_TEXT_SECTION                                  // SECTION(".otg.ram.text")
#define OTG_ROM_DATA_SECTION                                  // SECTION(".otg.ram.rodata")
#define START_OTG_RAM_FUN_SECTION                             // SECTION(".ram.otg.data.a")
#define START_OTG_RAM_DATA_SECTION                            // SECTION(".ram.otg.data.b")
#endif
  
// Image2 and SDRAM Data Section
#define IMAGE2_START_RAM_FUN_SECTION                          SECTION(".image2.ram.data")
#define SDRAM_DATA_SECTION                                    SECTION(".sdram.data")
  
// Wlan  Section
#define WLAN_ROM_TEXT_SECTION                                 SECTION(".wlan.rom.text")
#define WLAN_ROM_DATA_SECTION                                 SECTION(".wlan.rom.rodata")
#define WLAN_RAM_MAP_SECTION                                  SECTION(".wlan_ram_map")
  
// Apple  Section
#define APPLE_ROM_TEXT_SECTION                                SECTION(".apple.rom.text")
#define APPLE_ROM_DATA_SECTION                                SECTION(".apple.rom.rodata")
  
// Libc Section
#define LIBC_ROM_TEXT_SECTION                                 SECTION(".libc.rom.text")
#define LIBC_ROM_DATA_SECTION                                 SECTION(".libc.rom.rodata")
#define LIBC_RAM_BSS_SECTION                                  SECTION(".libc.ram.bss")
  
// SSL  Section
#define SSL_ROM_TEXT_SECTION                                  SECTION(".ssl.rom.text")
#define SSL_ROM_DATA_SECTION                                  SECTION(".ssl.rom.rodata")
#define SSL_RAM_MAP_SECTION                                   SECTION(".ssl_ram_map")
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_MISC_H__ */
