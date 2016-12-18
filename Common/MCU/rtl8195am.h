#ifndef __RTL8195AM_H__
#define __RTL8195AM_H__

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// =================================================================================================
// Start of section using anonymous unions
//
#if defined(__ARMCC_VERSION)
#pragma push
#pragma anon_unions
#elif defined(__CWCC__)
#pragma push
#pragma cpp_extensions on
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
//  #pragma push
#pragma language=extended
#else
#error Not supported compiler type
#endif

// =================================================================================================
// Library_configuration_section
// RTL8195AM Standard Peripherals Library version number V1.0.0
//
#define __RTL_STDPERIPH_VERSION_MAIN   (0x01)       //  [31:24] main version
#define __RTL_STDPERIPH_VERSION_SUB1   (0x00)       //  [23:16] sub1 version
#define __RTL_STDPERIPH_VERSION_SUB2   (0x00)       //  [15:8]  sub2 version
#define __RTL_STDPERIPH_VERSION_RC     (0x00)       //  [7:0]  release candidate
#define __RTL_STDPERIPH_VERSION        ( ( __RTL_STDPERIPH_VERSION_MAIN << 24 )  \
                                       | ( __RTL_STDPERIPH_VERSION_SUB1 << 16 )  \
                                       | ( __RTL_STDPERIPH_VERSION_SUB2 <<  8 )  \
                                       | ( __RTL_STDPERIPH_VERSION_RC ) )

// =================================================================================================
// Configuration of the Cortex-M3 Processor and Core Peripherals
//
#define __CM3_REV                 0x0200    //  Core revision r0p0
#define __MPU_PRESENT             1         //  Defines if an MPU is present or not
#define __NVIC_PRIO_BITS          4         //  Number of priority bits implemented in the NVIC
#define __Vendor_SysTickConfig    1         //  Vendor specific implementation of SysTickConfig is defined
#define __FPU_PRESENT             0         //  No FPU

// =================================================================================================
// RTL8195AM Interrupt Number Definition
//
typedef enum IRQn
{
  // Cortex-M3 Processor Exceptions Numbers
  NonMaskableInt_IRQn = -14,              //  2 Non Maskable Interrupt
  MemoryManagement_IRQn = -12,            //  4 Cortex-M3 Memory Management Interrupt
  BusFault_IRQn = -11,                    //  5 Cortex-M3 Bus Fault Interrupt
  UsageFault_IRQn = -10,                  //  6 Cortex-M3 Usage Fault Interrupt
  SVCall_IRQn = -5,                       //  11 Cortex-M3 SV Call Interrupt
  DebugMonitor_IRQn = -4,                 //  12 Cortex-M3 Debug Monitor Interrupt
  PendSV_IRQn = -2,                       //  14 Cortex-M3 Pend SV Interrupt
  SysTick_IRQn = -1,                      //  15 Cortex-M3 System Tick Interrupt

  // RTL8195A Specific Interrupt Numbers

  SYSTEM_ON_IRQ = 0,
  WDG_IRQ = 1,
  TIMER0_IRQ = 2,
  TIMER1_IRQ = 3,
  I2C3_IRQ = 4,
  TIMER2_7_IRQ = 5,
  SPI0_IRQ = 6,
  GPIO_IRQ = 7,
  UART0_IRQ = 8,
  SPI_FLASH_IRQ = 9,
  USB_OTG_IRQ = 10,
  SDIO_HOST_IRQ = 11,
  SDIO_DEVICE_IRQ = 12,
  I2S0_PCM0_IRQ = 13,
  I2S1_PCM1_IRQ = 14,
  WL_DMA_IRQ = 15,
  WL_PROTOCOL_IRQ = 16,
  CRYPTO_IRQ = 17,
  GMAC_IRQ = 18,
  PERIPHERAL_IRQ = 19,  // Handle IRQ[64..95]
  GDMA0_CHANNEL0_IRQ = 20,
  GDMA0_CHANNEL1_IRQ = 21,
  GDMA0_CHANNEL2_IRQ = 22,
  GDMA0_CHANNEL3_IRQ = 23,
  GDMA0_CHANNEL4_IRQ = 24,
  GDMA0_CHANNEL5_IRQ = 25,
  GDMA1_CHANNEL0_IRQ = 26,
  GDMA1_CHANNEL1_IRQ = 27,
  GDMA1_CHANNEL2_IRQ = 28,
  GDMA1_CHANNEL3_IRQ = 29,
  GDMA1_CHANNEL4_IRQ = 30,
  GDMA1_CHANNEL5_IRQ = 31,

  // RTL8195A Unused Interrupt Numbers
  UNUSED_32_IRQ = 32,
  UNUSED_63_IRQ = 63,

  // RTL8195A PERIPHERAL_IRQ Numbers : Status and Mask
  I2C0_IRQ = 64,
  I2C1_IRQ = 65,
  I2C2_IRQ = 66,
  DUMMY0_IRQ = 67,
  DUMMY1_IRQ = 68,
  DUMMY2_IRQ = 69,
  DUMMY3_IRQ = 70,
  DUMMY4_IRQ = 71,
  SPI1_IRQ = 72,
  SPI2_IRQ = 73,
  DUMMY5_IRQ = 74,
  DUMMY6_IRQ = 75,
  DUMMY7_IRQ = 76,
  DUMMY8_IRQ = 77,
  DUMMY9_IRQ = 78,
  DUMMY10_IRQ = 79,
  UART1_IRQ = 80,
  UART2_IRQ = 81,
  DUMMY11_IRQ = 82,
  DUMMY12_IRQ = 83,
  DUMMY13_IRQ = 84,
  DUMMY14_IRQ = 85,
  DUMMY15_IRQ = 86,
  DUMMY16_IRQ = 87,
  UART_LOG_IRQ = 88,
  ADC_IRQ = 89,
  DUMMY17_IRQ = 90,
  DAC0_IRQ = 91,
  DAC1_IRQ = 92,
  LP_EXTENSION_IRQ = 93,  // Handle IRQ[96..127]
  DUMMY18_IRQ = 94,
  PTA_TRX_IRQ = 95,

  // RTL8195A LP_EXTENSION_IRQ Numbers : Status and Mask
  RXI300_IRQ = 96,
  NFC_IRQ = 97,
  LAST_IRQ = 127

} IRQn_Type, *PIRQn_Type;

#include "core_cm3.h"            // Cortex-M3 processor and core peripherals
#include "system_rtl8195am.h"    // RTL8195AM System Header
#include <stdint.h>

// =================================================================================================
// RTL8195AM Peripheral Registers Structures Definition
//

// =================================================================================================
// RTL8195AM System and Peripheral Controller
//
typedef struct
{
  __IO uint16_t PWR_CTRL;                                   // 0x0000
  __IO uint16_t ISO_CTRL;                                   // 0x0002
  __IO uint32_t Dummy0[ 1 ];                                // 0x0004 ****
  __IO uint32_t FUNC_EN;                                    // 0x0008
  __IO uint32_t Dummy1[ 1 ];                                // 0x000C ****

  __IO uint32_t CLK_CTRL0;                                  // 0x0010
  __IO uint32_t CLK_CTRL1;                                  // 0x0014
  __IO uint32_t Dummy2[ 1 ];                                // 0x0018 ****
  __IO uint32_t Dummy3[ 1 ];                                // 0x001C ****

  __IO uint32_t EFUSE_SYSCFG0;                              // 0x0020
  __IO uint32_t EFUSE_SYSCFG1;                              // 0x0024
  __IO uint32_t EFUSE_SYSCFG2;                              // 0x0028
  __IO uint32_t EFUSE_SYSCFG3;                              // 0x002C

  __IO uint32_t EFUSE_SYSCFG4;                              // 0x0030
  __IO uint32_t EFUSE_SYSCFG5;                              // 0x0034
  __IO uint32_t EFUSE_SYSCFG6;                              // 0x0038
  __IO uint32_t EFUSE_SYSCFG7;                              // 0x003C

  __IO uint32_t REGU_CTRL0;                                 // 0x0040
  __IO uint32_t Dummy4[ 1 ];                                // 0x0044 ****
  __IO uint32_t SWR_CTRL0;                                  // 0x0048
  __IO uint32_t SWR_CTRL1;                                  // 0x004C

  __IO uint32_t Dummy5[ 4 ];                                // 0x0050 ****

  __IO uint32_t XTAL_CTRL0;                                 // 0x0060
  __IO uint32_t XTAL_CTRL1;                                 // 0x0064
  __IO uint32_t Dummy6[ 1 ];                                // 0x0068 ****
  __IO uint32_t Dummy7[ 1 ];                                // 0x006C ****

  __IO uint32_t SYSPLL_CTRL0;                               // 0x0070
  __IO uint32_t SYSPLL_CTRL1;                               // 0x0074
  __IO uint32_t SYSPLL_CTRL2;                               // 0x0078
  __IO uint32_t Dummy8[ 1 ];                                // 0x007C ****

  __IO uint32_t Dummy9[ 4 ];                                // 0x0080 ****

  __IO uint32_t ANA_TIM_CTRL;                               // 0x0090
  union
  {
    __IO uint32_t REGU_CTRL1;                               // 0x0094
    __IO uint32_t DSLP_TIM_CTRL;                            // 0x0094
  };
  __IO uint32_t DSLP_TIM_CAL_CTRL;                          // 0x0098
  __IO uint32_t DummyA[ 1 ];                                // 0x009C ****

  __IO uint32_t DEBUG_CTRL;                                 // 0x00A0
  __IO uint32_t PINMUX_CTRL;                                // 0x00A4
  __IO uint32_t GPIO_DSTBY_WAKE_CTRL0;                      // 0x00A8
  __IO uint32_t GPIO_DSTBY_WAKE_CTRL1;                      // 0x00AC

  __IO uint32_t DummyB[ 3 ];                                // 0x00B0 ****
  __IO uint32_t DEBUG_REG;                                  // 0x00BC

  __IO uint32_t DummyC0[ 4 ];                               // 0x00C0 ****

  __IO uint32_t DummyC1[ 4 ];                               // 0x00D0 ****

  __IO uint32_t EEPROM_CTRL0;                               // 0x00E0
  __IO uint32_t EEPROM_CTRL1;                               // 0x00E4
  __IO uint32_t EFUSE_CTRL;                                 // 0x00E8
  __IO uint32_t EFUSE_TEST;                                 // 0x00EC

  __IO uint32_t DSTBY_INFO0;                                // 0x00F0
  __IO uint32_t DSTBY_INFO1;                                // 0x00F4
  __IO uint32_t DSTBY_INFO2;                                // 0x00F8
  __IO uint32_t DSTBY_INFO3;                                // 0x00FC

  __IO uint32_t SLP_WAKE_EVENT_MSK0;                        // 0x0100
  __IO uint32_t SLP_WAKE_EVENT_MSK1;                        // 0x0104
  __IO uint32_t SLP_WAKE_EVENT_STATUS0;                     // 0x0108
  __IO uint32_t SLP_WAKE_EVENT_STATUS1;                     // 0x010C

  __IO uint32_t SNF_WAKE_EVENT_MSK0;                        // 0x0110
  __IO uint32_t SNF_WAKE_EVENT_STATUS;                      // 0x0114
  __IO uint32_t PWRMGT_CTRL;                                // 0x0118
  __IO uint32_t DummyD[ 1 ];                                // 0x011C ****

  __IO uint32_t PWRMGT_OPTION;                              // 0x0120
  __IO uint32_t PWRMGT_OPTION_EXT;                          // 0x0124
  __IO uint32_t DummyE[ 1 ];                                // 0x0128 ****
  __IO uint32_t DummyF[ 1 ];                                // 0x012C ****

  __IO uint32_t DSLP_WEVENT;                                // 0x0130
  __IO uint32_t PERI_MONITOR;                               // 0x0134
  __IO uint32_t DummyG[ 1 ];                                // 0x0138 ****
  __IO uint32_t DummyH[ 1 ];                                // 0x013C ****

  __IO uint32_t DummyI[ 44 ];                               // 0x0140 ****

  __IO uint32_t SYSTEM_CFG0;                                // 0x01F0
  __IO uint32_t SYSTEM_CFG1;                                // 0x01F4
  __IO uint32_t SYSTEM_CFG2;                                // 0x01F8
  __IO uint32_t SYSTEM_CFG3;                                // 0x01FC

  __IO uint32_t PEON_PWR_CTRL;                              // 0x0200
  __IO uint32_t PEON_ISO_CTRL;                              // 0x0204
  __IO uint32_t DummyJ[ 1 ];                                // 0x0208****
  __IO uint32_t DummyK[ 1 ];                                // 0x020C ****

  __IO uint32_t SOC_FUNC_EN;                                // 0x0210
  __IO uint32_t SOC_HCI_COM_FUNC_EN;                        // 0x0214
  __IO uint32_t SOC_PERI_FUNC0_EN;                          // 0x0218
  __IO uint32_t SOC_PERI_FUNC1_EN;                          // 0x021C

  __IO uint32_t SOC_PERI_BD_FUNC0_EN;                       // 0x0220
  __IO uint32_t DummyL[ 3 ];                                // 0x0224 ****

  __IO uint32_t PESOC_CLK_CTRL;                             // 0x0230
  __IO uint32_t PESOC_PERI_CLK_CTRL0;                       // 0x0234
  __IO uint32_t PESOC_PERI_CLK_CTRL1;                       // 0x0238
  __IO uint32_t PESOC_CLK_CTRL3;                            // 0x023C

  __IO uint32_t PESOC_HCI_CLK_CTRL0;                        // 0x0240
  __IO uint32_t PESOC_COM_CLK_CTRL1;                        // 0x0244
  __IO uint32_t PESOC_HW_ENG_CLK_CTRL;                      // 0x0248
  __IO uint32_t DummyM[ 1 ];                                // 0x024C ****

  __IO uint32_t PESOC_CLK_SEL;                              // 0x0250
  __IO uint32_t DummyN[ 3 ];                                // 0x0254 ****

  __IO uint32_t DummyO[ 2 ];                                // 0x0260 ****
  __IO uint32_t DummyP[ 1 ];                                // 0x0268 ****
  __IO uint32_t SYS_ANACK_CAL_CTRL;                         // 0x026C

  __IO uint32_t OSC32K_CTRL;                                // 0x0270
  __IO uint32_t OSC32K_REG_CTRL0;                           // 0x0274
  __IO uint32_t OSC32K_REG_CTRL1;                           // 0x0278
  __IO uint32_t THERMAL_METER_CTRL;                         // 0x027C

  __IO uint32_t UART_MUX_CTRL;                              // 0x0280
  __IO uint32_t SPI_MUX_CTRL;                               // 0x0284
  __IO uint32_t I2C_MUX_CTRL;                               // 0x0288
  __IO uint32_t I2S_PCM_MUX_CTRL;                           // 0x028C

  __IO uint32_t DummyQ[ 4 ];                                // 0x0290 ****

  __IO uint32_t HCI_PINMUX_CTRL;                            // 0x02A0
  __IO uint32_t WLAN_NFC_PINMUX_CTRL;                       // 0x02A4
  __IO uint32_t BT_PINMUX_CTRL;                             // 0x02A8
  __IO uint32_t PWM_ETE_PINMUX_CTRL;                        // 0x02AC

  __IO uint32_t DummyR[ 4 ];                                // 0x02B0 ****

  __IO uint32_t CPU_PERIPHERAL_CTRL;                        // 0x02C0
  __IO uint32_t DummyS[ 3 ];                                // 0x02C4 ****

  __IO uint32_t DummyT[ 4 ];                                // 0x02D0 ****

  __IO uint32_t HCI_CTRL_STATUS_0;                          // 0x02E0
  __IO uint32_t HCI_CTRL_STATUS_1;                          // 0x02E4
  __IO uint32_t DummyU[ 1 ];                                // 0x02E8 ****
  __IO uint32_t DummyV[ 1 ];                                // 0x02EC ****

  __IO uint32_t DummyW[ 4 ];                                // 0x02F0 ****

  __IO uint32_t PESOC_MEM_CTRL;                             // 0x0300
  __IO uint32_t PESOC_SOC_CTRL;                             // 0x0304
  __IO uint32_t PESOC_PERI_CTRL;                            // 0x0308
  __IO uint32_t DummyX[ 1 ];                                // 0x030C ****

  __IO uint32_t DummyY[ 4 ];                                // 0x0310 ****

  __IO uint32_t GPIO_SHTDN_CTRL;                            // 0x0320
  __IO uint32_t GPIO_DRIVING_CTRL;                          // 0x0324
  __IO uint32_t DummyZ[ 2 ];                                // 0x0328 ****

  __IO uint32_t GPIO_PULL_CTRL0;                            // 0x0330
  __IO uint32_t GPIO_PULL_CTRL1;                            // 0x0334
  __IO uint32_t GPIO_PULL_CTRL2;                            // 0x0338
  __IO uint32_t GPIO_PULL_CTRL3;                            // 0x033C

  __IO uint32_t GPIO_PULL_CTRL4;                            // 0x0340
  __IO uint32_t GPIO_PULL_CTRL5;                            // 0x0344
  __IO uint32_t GPIO_PULL_CTRL6;                            // 0x0348
  __IO uint32_t DummyAA[ 1 ];                               // 0x034C ****

  __IO uint32_t DummyAB[ 4 ];                               // 0x0350 ****

  __IO uint32_t PERI_PWM0_CTRL;                             // 0x0360
  __IO uint32_t PERI_PWM1_CTRL;                             // 0x0364
  __IO uint32_t PERI_PWM2_CTRL;                             // 0x0368
  __IO uint32_t PERI_PWM3_CTRL;                             // 0x036C

  __IO uint32_t PERI_GTIM_EVT_CTRL;                         // 0x0370
  __IO uint32_t PERI_EGTIM_CTRL;                            // 0x0374
  __IO uint32_t DummyAC[ 2 ];                               // 0x0378 ****

  __IO uint32_t DummyAD[ 28 ];                              // 0x0380 ****

  __IO uint32_t PEON_CFG;                                   // 0x03F0
  __IO uint32_t PEON_STATUS;                                // 0x03F4
  __IO uint32_t DummyAE[ 2 ];                               // 0x03F8 ****

} RTL_SYS_TypeDef;

// =================================================================================================
// RTL8195AM Analog to Digital Converter SAR (ADC)
//
typedef struct
{
  __IO uint32_t FIFO_READ;                                  // 0x0000
  __IO uint32_t CONTROL;                                    // 0x0004
  __IO uint32_t INTR_EN;                                    // 0x0008
  __IO uint32_t INTR_STS;                                   // 0x000C

  __IO uint32_t COMP_VALUE_L;                               // 0x0010
  __IO uint32_t COMP_VALUE_H;                               // 0x0014
  __IO uint32_t COMP_SET;                                   // 0x0018
  __IO uint32_t POWER;                                      // 0x001C

  __IO uint32_t ANAPAR_AD0;                                 // 0x0020
  __IO uint32_t ANAPAR_AD1;                                 // 0x0024
  __IO uint32_t ANAPAR_AD2;                                 // 0x0028
  __IO uint32_t ANAPAR_AD3;                                 // 0x002C

  __IO uint32_t ANAPAR_AD4;                                 // 0x0030
  __IO uint32_t ANAPAR_AD5;                                 // 0x0034
  __IO uint32_t CALI_DATA;                                  // 0x0038
} RTL_ADC_TypeDef;

/**
 * @brief Digital to Analog Converter
 */
typedef struct
{
  __IO uint32_t FIFO_WR;                                    // 0x0000
  __IO uint32_t CTRL;                                       // 0x0004
  __IO uint32_t INTR_CTRL;                                  // 0x0008
  __IO uint32_t INTR_STS;                                   // 0x000C

  __IO uint32_t PWR_CTRL;                                   // 0x0010
  __IO uint32_t ANAPAR_DA0;                                 // 0x0014
  __IO uint32_t ANAPAR_DA1;                                 // 0x0018
} RTL_DAC_TypeDef;

/**
 * @brief GDMA Controller
 */
typedef struct
{
  __IO uint32_t CH_SAR;                                     // 0x0000
  __IO uint32_t Dummy0[ 1 ];                                // 0x0004 ****
  __IO uint32_t CH_DAR;                                     // 0x0008
  __IO uint32_t Dummy1[ 1 ];                                // 0x000C ****

  __IO uint32_t CH_LLP;                                     // 0x0010
  __IO uint32_t Dummy2[ 1 ];                                // 0x0014 ****
  __IO uint32_t CH_CTL;                                     // 0x0018
  __IO uint32_t Dummy3[ 1 ];                                // 0x001C ****

  __IO uint32_t CH_SSTAT;                                   // 0x0020
  __IO uint32_t Dummy4[ 1 ];                                // 0x0024 ****
  __IO uint32_t CH_DSTAT;                                   // 0x0028
  __IO uint32_t Dummy5[ 1 ];                                // 0x002C ****

  __IO uint32_t CH_SSTATAR;                                 // 0x0030
  __IO uint32_t Dummy6[ 1 ];                                // 0x0034 ****
  __IO uint32_t CH_DSTATAR;                                 // 0x0038
  __IO uint32_t Dummy7[ 1 ];                                // 0x003C ****

  __IO uint32_t CH_CFG;                                     // 0x0040
  __IO uint32_t Dummy8[ 1 ];                                // 0x0044 ****
  __IO uint32_t CH_SGR;                                     // 0x0048
  __IO uint32_t Dummy9[ 1 ];                                // 0x004C ****

  __IO uint32_t CH_DSR;                                     // 0x0050
  __IO uint32_t DummyA[ 1 ];                                // 0x0054 ****
  __IO uint32_t CH_OFF;                                     // 0x0058
  __IO uint32_t DummyB[ 1 ];                                // 0x005C ****

  __IO uint32_t DummyC[ 152 ];                              // 0x0060 ****

  union
  {
    __IO uint32_t RAW_INT_BASE;                             // 0x02C0
    __IO uint32_t RAW_INT_TFR;                              // 0x02C0
  };
  __IO uint32_t DummyD[ 1 ];                                // 0x02C4 ****
  __IO uint32_t RAW_INT_BLOCK;                              // 0x02C8
  __IO uint32_t DummyE[ 1 ];                                // 0x02CC ****

  __IO uint32_t RAW_INT_SRC_TRAN;                           // 0x02D0
  __IO uint32_t DummyF[ 1 ];                                // 0x02D4 ****
  __IO uint32_t RAW_INT_DST_TRAN;                           // 0x02D8
  __IO uint32_t DummyG[ 1 ];                                // 0x02DC ****

  __IO uint32_t RAW_INT_ERR;                                // 0x02E0
  __IO uint32_t DummyH[ 1 ];                                // 0x02E4 ****
  union
  {
    __IO uint32_t STATUS_INT_BASE;                          // 0x02E8
    __IO uint32_t STATUS_INT_TFR;                           // 0x02E8
  };
  __IO uint32_t DummyI[ 1 ];                                // 0x02EC ****

  __IO uint32_t STATUS_INT_BLOCK;                           // 0x02F0
  __IO uint32_t DummyJ[ 1 ];                                // 0x02F4 ****
  __IO uint32_t STATUS_INT_SRC_TRAN;                        // 0x02F8
  __IO uint32_t DummyK[ 1 ];                                // 0x02FC ****

  __IO uint32_t STATUS_INT_DST_TRAN;                        // 0x0300
  __IO uint32_t DummyL[ 1 ];                                // 0x0304 ****
  __IO uint32_t STATUS_INT_ERR;                             // 0x0308
  __IO uint32_t DummyM[ 1 ];                                // 0x030C ****

  union
  {
    __IO uint32_t MASK_INT_BASE;                            // 0x0310
    __IO uint32_t MASK_INT_TFR;                             // 0x0310
  };
  __IO uint32_t DummyN[ 1 ];                                // 0x0314 ****
  __IO uint32_t MASK_INT_BLOCK;                             // 0x0318
  __IO uint32_t DummyO[ 1 ];                                // 0x031C ****

  __IO uint32_t MASK_INT_SRC_TRAN;                          // 0x0320
  __IO uint32_t DummyP[ 1 ];                                // 0x0324 ****
  __IO uint32_t MASK_INT_DST_TRAN;                          // 0x0328
  __IO uint32_t DummyQ[ 1 ];                                // 0x032C ****

  __IO uint32_t MASK_INT_INT_ERR;                           // 0x0330
  __IO uint32_t DummyR[ 1 ];                                // 0x0334 ****
  union
  {
    __IO uint32_t CLEAR_INT_BASE;                           // 0x0338
    __IO uint32_t CLEAR_INT_TFR;                            // 0x0338
  };
  __IO uint32_t DummyS[ 1 ];                                // 0x033C ****

  __IO uint32_t CLEAR_INT_BLOCK;                            // 0x0340
  __IO uint32_t DummyT[ 1 ];                                // 0x0344 ****
  __IO uint32_t CLEAR_INT_SRC_TRAN;                         // 0x0348
  __IO uint32_t DummyU[ 1 ];                                // 0x034C ****

  __IO uint32_t CLEAR_INT_DST_TRAN;                         // 0x0350
  __IO uint32_t DummyV[ 1 ];                                // 0x0354 ****
  __IO uint32_t CLEAR_INT_ERR;                              // 0x0358
  __IO uint32_t DummyW[ 1 ];                                // 0x035C ****

  __IO uint32_t STATUS_INT;                                 // 0x0360
  __IO uint32_t DummyX[ 1 ];                                // 0x0364 ****
  __IO uint32_t REQ_SRC;                                    // 0x0368
  __IO uint32_t DummyY[ 1 ];                                // 0x036C ****

  __IO uint32_t REQ_DST;                                    // 0x0370
  __IO uint32_t DummyZ[ 1 ];                                // 0x0374 ****
  __IO uint32_t REQ_SGL_REQ;                                // 0x0378
  __IO uint32_t DummyAA[ 1 ];                               // 0x037C ****

  __IO uint32_t REQ_DST_REQ;                                // 0x0380
  __IO uint32_t DummyAB[ 1 ];                               // 0x0384 ****
  __IO uint32_t REQ_LST_SRC;                                // 0x0388
  __IO uint32_t DummyAC[ 1 ];                               // 0x038C ****

  __IO uint32_t REQ_LST_DST;                                // 0x0390
  __IO uint32_t DummyAD[ 1 ];                               // 0x0394 ****
  __IO uint32_t DMAC_CFG;                                   // 0x0398
  __IO uint32_t DummyAE[ 1 ];                               // 0x039C ****

  __IO uint32_t CH_EN;                                      // 0x03A0
  __IO uint32_t DummyAF[ 1 ];                               // 0x03A4 ****
  __IO uint32_t DMA_ID;                                     // 0x03A8
  __IO uint32_t DummyAG[ 1 ];                               // 0x03AC ****

  __IO uint32_t DMA_TEST;                                   // 0x03B0
  __IO uint32_t DummyAH[ 3 ];                               // 0x03B4 ****

  __IO uint32_t DummyAI[ 2 ];                               // 0x03C0 ****
  __IO uint32_t DMA_COM_PARAMS6;                            // 0x03C8
  __IO uint32_t DummyAJ[ 1 ];                               // 0x03CC ****

  __IO uint32_t DMA_COM_PARAMS5;                            // 0x03D0
  __IO uint32_t DummyAK[ 1 ];                               // 0x03D4 ****
  __IO uint32_t DMA_COM_PARAMS4;                            // 0x03D8
  __IO uint32_t DummyAL[ 1 ];                               // 0x03DC ****

  __IO uint32_t DMA_COM_PARAMS3;                            // 0x03E0
  __IO uint32_t DummyAM[ 1 ];                               // 0x03E4 ****
  __IO uint32_t DMA_COM_PARAMS2;                            // 0x03E8
  __IO uint32_t DummyAN[ 1 ];                               // 0x03EC ****

  __IO uint32_t DMA_COM_PARAMS1;                            // 0x03F0
  __IO uint32_t DummyAO[ 1 ];                               // 0x03F4 ****
  __IO uint32_t DMA_COM_PARAMS0;                            // 0x03F8
  __IO uint32_t DummyAP[ 1 ];                               // 0x03FC ****
} RTL_GDMA_TypeDef;

/**
 * @brief GPIO General Purpose I/O
 */
typedef struct
{
  __IO uint32_t PORTA_DR;                                   // 0x0000
  __IO uint32_t PORTA_DDR;                                  // 0x0004
  __IO uint32_t PORTA_CTRL;                                 // 0x0008
  __IO uint32_t PORTB_DR;                                   // 0x000C
  __IO uint32_t PORTB_DDR;                                  // 0x0010
  __IO uint32_t PORTB_CTRL;                                 // 0x0014
  __IO uint32_t PORTC_DR;                                   // 0x0018
  __IO uint32_t PORTC_DDR;                                  // 0x001C
  __IO uint32_t PORTC_CTRL;                                 // 0x0020
  __IO uint32_t PORTD_DR;                                   // 0x0024
  __IO uint32_t PORTD_DDR;                                  // 0x0028
  __IO uint32_t PORTD_CTRL;                                 // 0x002C

  __IO uint32_t INT_EN;                                     // 0x0030
  __IO uint32_t INT_MASK;                                   // 0x0034
  __IO uint32_t INT_TYPE;                                   // 0x0038
  __IO uint32_t INT_POLARITY;                               // 0x003C
  __IO uint32_t INT_STATUS;                                 // 0x0040
  __IO uint32_t INT_RAWSTATUS;                              // 0x0044

  __IO uint32_t DEBOUNCE;                                   // 0x0048
  __IO uint32_t PORTA_EOI;                                  // 0x004C

  __IO uint32_t EXT_PORTA;                                  // 0x0050
  __IO uint32_t EXT_PORTB;                                  // 0x0054
  __IO uint32_t EXT_PORTC;                                  // 0x0058
  __IO uint32_t Dummy2[ 1 ];                                // 0x005C ****

  __IO uint32_t INT_SYNC;                                   // 0x0060
} RTL_GPIO_TypeDef;

/**
 * @brief I2C Inter-integrated Circuit Interface
 */
typedef struct
{
  __IO uint32_t CON;                                        // 0x0000
  __IO uint32_t TAR;                                        // 0x0004
  __IO uint32_t SAR;                                        // 0x0008
  __IO uint32_t HS_MADDR;                                   // 0x000C

  __IO uint32_t DATA_CMD;                                   // 0x0010
  __IO uint32_t SS_SCL_HCNT;                                // 0x0014
  __IO uint32_t SS_SCL_LCNT;                                // 0x0018
  __IO uint32_t FS_SCL_HCNT;                                // 0x001C

  __IO uint32_t FS_SCL_LCNT;                                // 0x0020
  __IO uint32_t HS_SCL_HCNT;                                // 0x0024
  __IO uint32_t HS_SCL_LCNT;                                // 0x0028
  __IO uint32_t INTR_STAT;                                  // 0x002C

  __IO uint32_t INTR_MASK;                                  // 0x0030
  __IO uint32_t RAW_INTR_STAT;                              // 0x0034
  __IO uint32_t RX_TL;                                      // 0x0038
  __IO uint32_t TX_TL;                                      // 0x003C

  __IO uint32_t CLR_INTR;                                   // 0x0040
  __IO uint32_t CLR_RX_UNDER;                               // 0x0044
  __IO uint32_t CLR_RX_OVER;                                // 0x0048
  __IO uint32_t CLR_TX_OVER;                                // 0x004C

  __IO uint32_t CLR_RD_REQ;                                 // 0x0050
  __IO uint32_t CLR_TX_ABRT;                                // 0x0054
  __IO uint32_t CLR_RX_DONE;                                // 0x0058
  __IO uint32_t CLR_ACTIVITY;                               // 0x005C

  __IO uint32_t CLR_STOP_DET;                               // 0x0060
  __IO uint32_t CLR_START_DET;                              // 0x0064
  __IO uint32_t CLR_GEN_CALL;                               // 0x0068
  __IO uint32_t ENABLE;                                     // 0x006C

  __IO uint32_t STATUS;                                     // 0x0070
  __IO uint32_t TXFLR;                                      // 0x0074
  __IO uint32_t RXFLR;                                      // 0x0078
  __IO uint32_t SDA_HOLD;                                   // 0x007C

  __IO uint32_t TX_ABRT_SOURCE;                             // 0x0080
  __IO uint32_t SLV_DATA_NACK_ONLY;                         // 0x0084
  __IO uint32_t DMA_CR;                                     // 0x0088
  __IO uint32_t DMA_TDLR;                                   // 0x008C

  __IO uint32_t DMA_RDLR;                                   // 0x0090
  __IO uint32_t SDA_SETUP;                                  // 0x0094
  __IO uint32_t ACK_GENERAL_CALL;                           // 0x0098
  __IO uint32_t ENABLE_STATUS;                              // 0x009C

  __IO uint32_t Dummy0[ 20 ];                               // 0x00A0 ****

  __IO uint32_t Dummy1[ 1 ];                                // 0x00F0 ****
  __IO uint32_t COMP_PARAM_1;                               // 0x00F4
  __IO uint32_t COMP_VERSION;                               // 0x00F8
  __IO uint32_t COMP_TYPE;                                  // 0x00FC
} RTL_I2C_TypeDef;

/**
 * @brief I2S Inter Inter-Iintegrated Circuit Sound Interface
 */
typedef struct
{
  __IO uint32_t CTL;                                        // 0x000
  union
  {
    __IO uint32_t PAGE_OWN_OFF;                             // 0x004
    __IO uint32_t TX_PAGE_PTR;                              // 0x004
  };
  __IO uint32_t RX_PAGE_PTR;                                // 0x008
  __IO uint32_t SETTING;                                    // 0x00C

  __IO uint32_t TX_MASK_INT;                                // 0x010
  __IO uint32_t TX_STATUS_INT;                              // 0x014
  __IO uint32_t RX_MASK_INT;                                // 0x018
  __IO uint32_t RX_STATUS_INT;                              // 0x01c

  __IO uint32_t TX_PAGE0_OWN;                               // 0x020
  __IO uint32_t TX_PAGE1_OWN;                               // 0x024
  __IO uint32_t TX_PAGE2_OWN;                               // 0x028
  __IO uint32_t TX_PAGE3_OWN;                               // 0x02C

  __IO uint32_t RX_PAGE0_OWN;                               // 0x030
  __IO uint32_t RX_PAGE1_OWN;                               // 0x034
  __IO uint32_t RX_PAGE2_OWN;                               // 0x038
  __IO uint32_t RX_PAGE3_OWN;                               // 0x03C
} RTL_I2S_TypeDef;

/**
 * @brief NFC Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_NFC_TypeDef;

/**
 * @brief PCM Interface
 */
typedef struct
{
  __IO uint32_t CTL;                                        // 0x000
  union
  {
    __IO uint32_t TRXBSA_OFF;                               // 0x004
    __IO uint32_t CHCNR03;                                  // 0x004
  };
  __IO uint32_t TSR03;                                      // 0x008
  __IO uint32_t BSIZE03;                                    // 0x00C

  __IO uint32_t CH0TXBSA;                                   // 0x010
  __IO uint32_t CH1TXBSA;                                   // 0x014
  __IO uint32_t CH2TXBSA;                                   // 0x018
  __IO uint32_t CH3TXBSA;                                   // 0x01c

  __IO uint32_t CH0RXBSA;                                   // 0x020
  __IO uint32_t CH1RXBSA;                                   // 0x024
  __IO uint32_t CH2RXBSA;                                   // 0x028
  __IO uint32_t CH3RXBSA;                                   // 0x02c

  __IO uint32_t IMR03;                                      // 0x030
  __IO uint32_t ISR03;                                      // 0x034
  __IO uint32_t CHCNR47;                                    // 0x038
  __IO uint32_t TSR47;                                      // 0x03c

  __IO uint32_t BSIZE47;                                    // 0x040
  __IO uint32_t CH4TXBSA;                                   // 0x044
  __IO uint32_t CH5TXBSA;                                   // 0x048
  __IO uint32_t CH6TXBSA;                                   // 0x04c

  __IO uint32_t CH7TXBSA;                                   // 0x050
  __IO uint32_t CH4RXBSA;                                   // 0x054
  __IO uint32_t CH5RXBSA;                                   // 0x058
  __IO uint32_t CH6RXBSA;                                   // 0x05c

  __IO uint32_t CH7RXBSA;                                   // 0x060
  __IO uint32_t IMR47;                                      // 0x064
  __IO uint32_t ISR47;                                      // 0x068
  __IO uint32_t CHCNR811;                                   // 0x06c

  __IO uint32_t TSR811;                                     // 0x070
  __IO uint32_t BSIZE811;                                   // 0x074
  __IO uint32_t CH8TXBSA;                                   // 0x078
  __IO uint32_t CH9TXBSA;                                   // 0x07c

  __IO uint32_t CH10TXBSA;                                  // 0x080
  __IO uint32_t CH11TXBSA;                                  // 0x084
  __IO uint32_t CH8RXBSA;                                   // 0x088
  __IO uint32_t CH9RXBSA;                                   // 0x08c

  __IO uint32_t CH10RXBSA;                                  // 0x090
  __IO uint32_t CH11RXBSA;                                  // 0x094
  __IO uint32_t IMR811;                                     // 0x098
  __IO uint32_t ISR811;                                     // 0x09c

  __IO uint32_t CHCNR1215;                                  // 0x0a0
  __IO uint32_t TSR1215;                                    // 0x0a4
  __IO uint32_t BSIZE1215;                                  // 0x0a8
  __IO uint32_t CH12TXBSA;                                  // 0x0ac

  __IO uint32_t CH13TXBSA;                                  // 0x0b0
  __IO uint32_t CH14TXBSA;                                  // 0x0b4
  __IO uint32_t CH15TXBSA;                                  // 0x0b8
  __IO uint32_t CH12RXBSA;                                  // 0x0bc

  __IO uint32_t CH13RXBSA;                                  // 0x0c0
  __IO uint32_t CH14RXBSA;                                  // 0x0c4
  __IO uint32_t CH15RXBSA;                                  // 0x0c8
  __IO uint32_t IMR1215;                                    // 0x0cc

  __IO uint32_t ISR1215;                                    // 0x0d0
  __IO uint32_t INTMAP;                                     // 0x0d4
  __IO uint32_t WTSR03;                                     // 0x0d8
  __IO uint32_t WTSR47;                                     // 0x0dc

  __IO uint32_t RX_BUFOW;                                   // 0x0e0
} RTL_PCM_TypeDef;

/**
 * @brief PWM Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_PWM_TypeDef;

/**
 * @brief MII Interface
 */
typedef struct
{
  __IO uint32_t IDR0;                                       // 0x0000
  __IO uint32_t IDR4;                                       // 0x0004
  __IO uint32_t Dummy0[ 12 ];                               // 0x0008 ****

  __IO uint32_t COM;                                        // 0x0038
  __IO uint32_t ISRIMR;                                     // 0x003C
  __IO uint32_t TC;                                         // 0x0040
  __IO uint32_t RC;                                         // 0x0044
  __IO uint32_t Dummy1[ 4 ];                                // 0x0048 ****

  __IO uint32_t MS;                                         // 0x0058
  __IO uint32_t MIIA;                                       // 0x005C

  __IO uint32_t Dummy2[ 1192 ];                             // 0x0060 ****

  __IO uint32_t TXFDP1;                                     // 0x1300
  __IO uint32_t Dummy3[ 59 ];                               // 0x1304 ****

  __IO uint32_t RXFDP1;                                     // 0x13F0
  __IO uint32_t Dummy4[ 15 ];                               // 0x13F4 ****

  __IO uint32_t ETNRXCPU1;                                  // 0x1430
  __IO uint32_t IOCMD;                                      // 0x1434
  __IO uint32_t IOCMD1;                                     // 0x1438
} RTL_MII_TypeDef;

typedef struct
{
  __IO uint32_t TXBD_ADDR;                                  // 0xA0  4 Bytes
  __IO uint32_t TXBD_SIZE;                                  // 0xA4  4 Bytes
  __IO uint16_t TXBD_WPTR;                                  // 0xA8  2 Bytes
  __IO uint16_t Dummy0[ 1 ];                                // 0xAA  ****
  __IO uint16_t TXBD_RPTR;                                  // 0xAC  2 Bytes
  __IO uint16_t Dummy1[ 1 ];                                // 0xAE  ****

  __IO uint32_t RXBD_ADDR;                                  // 0xB0  4 Bytes
  __IO uint16_t RXBD_SIZE;                                  // 0xB4  2 Bytes
  __IO uint16_t RXBD_C2H_WPTR;                              // 0xB6  2 Bytes
  __IO uint32_t RXBD_C2H_RPTR;                              // 0xB8  2 Bytes
  __IO uint8_t HCI_RX_REQ;                                  // 0xBA  1 Byte
  __IO uint8_t CPU_RST_DMA;                                 // 0xBB  1 Byte
  __IO uint16_t RX_REQ_ADDR;                                // 0xBC  2 Bytes
  __IO uint16_t Dummy2[ 1 ];                                // 0xBE  ****

  __IO uint16_t CPU_INT_MASK;                               // 0xC0  2 Bytes
  __IO uint16_t CPU_INT_STAS;                               // 0xC2  2 Bytes
  __IO uint8_t CCPWM;                                       // 0xC4  1 Byts
  __IO uint8_t CPU_IND;                                     // 0xC5  1 Byte
  __IO uint16_t CCPWM2;                                     // 0xC6  2 Bytes
  __IO uint32_t CPU_H2C_MSG;                                // 0xC8  4 Bytes
  __IO uint32_t CPU_C2H_MSG;                                // 0xCC  4 Bytes

  __IO uint8_t CRPWM;                                       // 0xD0  1 Bytes
  __IO uint8_t Dummy3[ 1 ];                                 // 0xD1  ****
  __IO uint16_t CRPWM2;                                     // 0xD2  2 Bytes
  __IO uint32_t AHB_DMA_CTRL;                               // 0xD4  4 Bytes
  __IO uint8_t RXBD_CNT;                                    // 0xD8  1 Bytes ???
  __IO uint8_t TX_BUF_UNIT_SZ;                              // 0xD9  1 Bytes
  __IO uint16_t RX_BD_FREE_CNT;                             // 0xDA  2 Bytes
  __IO uint32_t CPU_H2C_MSG_EXT;                            // 0xDC  4 Bytes

  __IO uint32_t CPU_C2H_MSG_EXT;                            // 0xE0  4 Bytes
} RTL_SDIOD_TypeDef;

typedef struct
{
  __IO uint32_t SDMA_SYS_ADDR;                              // 0x00  4byte
  __IO uint16_t BLK_SIZE;                                   // 0x04  2byte
  __IO uint16_t BLK_CNT;                                    // 0x06  2byte
  __IO uint32_t ARG;                                        // 0x08  4byte
  __IO uint16_t XFER_MODE;                                  // 0x0C  2byte
  __IO uint16_t CMD;                                        // 0x0E  2byte

  __IO uint32_t RSP0;                                       // 0x10  4byte
  __IO uint32_t RSP2;                                       // 0x14  4byte
  __IO uint32_t RSP4;                                       // 0x18  4byte
  __IO uint32_t RSP6;                                       // 0x1C  4byte

  __IO uint32_t BUF_DATA_PORT;                              // 0x20  4byte
  __IO uint32_t PRESENT_STATE;                              // 0x24  4byte
  __IO uint8_t HOST_CTRL;                                   // 0x28  1byte
  __IO uint8_t PWR_CTRL;                                    // 0x29  1byte
  __IO uint8_t BLK_GAP_CTRL;                                // 0x2A  1byte
  __IO uint8_t WAKEUP_CTRL;                                 // 0x2B  1byte
  __IO uint16_t CLK_CTRL;                                   // 0x2C  2byte
  __IO uint8_t TIMEOUT_CTRL;                                // 0x2E  1byte
  __IO uint8_t SW_RESET;                                    // 0x2F  1byte

  __IO uint16_t NORMAL_INT_STATUS;                          // 0x30  2byte
  __IO uint16_t ERROR_INT_STATUS;                           // 0x32  2byte
  __IO uint16_t NORMAL_INT_STATUS_EN;                       // 0x34  2byte
  __IO uint16_t ERROR_INT_STATUS_EN;                        // 0x36  2byte
  __IO uint16_t NORMAL_INT_SIG_EN;                          // 0x38  2byte
  __IO uint16_t ERROR_INT_SIG_EN;                           // 0x3A  2byte
  __IO uint32_t Dummy0[ 1 ];                                // 0x3C  ****

  __IO uint32_t CAPABILITIES;                               // 0x40  8byte
  __IO uint32_t Dummy1[ 5 ];                                // 0x44  ****
  __IO uint32_t ADMA_SYS_ADDR;                              // 0x58  8byte
} RTL_SDIOH_TypeDef;

typedef struct
{
  __IO uint32_t CCR;                                        // 0x00
  __IO uint32_t DCR;                                        // 0x04
  __IO uint32_t IOCR;                                       // 0x08
  __IO uint32_t CSR;                                        // 0x0C

  __IO uint32_t DRR;                                        // 0x10
  __IO uint32_t TPR0;                                       // 0x14
  __IO uint32_t TPR1;                                       // 0x18
  __IO uint32_t TPR2;                                       // 0x1C

  __IO uint32_t MR;                                         // 0x20
  __IO uint32_t EMR1;                                       // 0x24
  __IO uint32_t EMR2;                                       // 0x28
  __IO uint32_t EMR3;                                       // 0x2C

  __IO uint32_t CMD_DPIN;                                   // 0x30
  __IO uint32_t TIE_DPIN;                                   // 0x34
  __IO uint32_t Dummy0[ 38 ];                               // 0x38  ****

  __IO uint32_t BCR;                                        // 0xD0
  __IO uint32_t BST;                                        // 0xD4
  __IO uint32_t BSRAM0;                                     // 0xD8
  __IO uint32_t BSRAM1;                                     // 0xDC

  __IO uint32_t Dummy1[ 5 ];                                // 0xE0  ****
  __IO uint32_t PCTL_SVN_ID;                                // 0xF4
  __IO uint32_t PCTL_IDR;                                   // 0xF8
  __IO uint32_t Dummy2[ 1 ];                                // 0xFC  ****

  __IO uint32_t DLY0;                                       // 0x100
  union
  {
    __IO uint32_t DLY1;                                     // 0x104
    __IO uint32_t DCM_RST;                                  // 0x104
  };
  __IO uint32_t DLY_CLK_PHA;                                // 0x108
  __IO uint32_t DLY_ST;                                     // 0x10C
  __IO uint32_t Dummy3[ 69 ];                               // 0x110  ****
  __IO uint32_t MISC;                                       // 0x224
  __IO uint32_t Dummy4[ 30 ];                               // 0x228  ****
  __IO uint32_t OCP_WRAP_IDR;                               // 0x2A0
  __IO uint32_t OCP_WRAP_VERSION;                           // 0x2A4
} RTL_SDRC_TypeDef;

/**
 * @brief SPI Interface
 */
typedef struct
{
  __IO uint32_t CTRLR0;                                     //  0x00   16 bits
  __IO uint32_t CTRLR1;                                     //  0x04   16 bits
  __IO uint32_t SSIENR;                                     //  0x08    1 bit
  __IO uint32_t MWCR;                                       //  0x0C    3 bits

  __IO uint32_t SER;                                        //  0x10
  __IO uint32_t BAUDR;                                      //  0x14   16 bits
  __IO uint32_t TXFTLR;                                     //  0x18    TX_ABW
  __IO uint32_t RXFTLR;                                     //  0x1C    RX_ABW

  __IO uint32_t TXFLR;                                      //  0x20
  __IO uint32_t RXFLR;                                      //  0x24
  __IO uint32_t SR;                                         //  0x28    7 bits
  __IO uint32_t IMR;                                        //  0x2C

  __IO uint32_t ISR;                                        //  0x30    6 bits
  __IO uint32_t RISR;                                       //  0x34    6 bits
  __IO uint32_t TXOICR;                                     //  0x38    1 bits
  __IO uint32_t RXOICR;                                     //  0x3C    1 bits

  __IO uint32_t RXUICR;                                     //  0x40    1 bits
  __IO uint32_t MSTICR;                                     //  0x44    1 bits
  __IO uint32_t ICR;                                        //  0x48    1 bits
  __IO uint32_t DMACR;                                      //  0x4C    2 bits

  __IO uint32_t DMATDLR;                                    //  0x50    TX_ABW
  __IO uint32_t DMARDLR;                                    //  0x54    RX_ABW
  __IO uint32_t IDR;                                        //  0x58   32 bits
  __IO uint32_t COMP_VERSION;                               //  0x5C   32 bits

  __IO uint32_t DR;                                         //  0x60   16 bits 0x60-0xEC
  __IO uint32_t Dummy0[ 35 ];                               //  0x64  ****

  __IO uint32_t RX_SAMPLE_DLY;                              //  0xF0    8 bits
  __IO uint32_t RSVD_0;                                     //  0xF4   32 bits
  __IO uint32_t RSVD_1;                                     //  0xF8   32 bits
  __IO uint32_t RSVD_2;                                     //  0xFC   32 bits
} RTL_SPI_TypeDef;

typedef struct
{
  __IO uint32_t CTRLR0;                                     // 0x0000
  __IO uint32_t CTRLR1;                                     // 0x0004
  __IO uint32_t SSIENR;                                     // 0x0008
  __IO uint32_t MWCR;                                       // 0x000C

  __IO uint32_t SER;                                        // 0x0010
  __IO uint32_t BAUDR;                                      // 0x0014
  __IO uint32_t TXFTLR;                                     // 0x0018
  __IO uint32_t RXFTLR;                                     // 0x001C

  __IO uint32_t TXFLR;                                      // 0x0020
  __IO uint32_t RXFLR;                                      // 0x0024
  __IO uint32_t SR;                                         // 0x0028
  __IO uint32_t IMR;                                        // 0x002C

  __IO uint32_t ISR;                                        // 0x0030
  __IO uint32_t RISR;                                       // 0x0034
  __IO uint32_t TXOICR;                                     // 0x0038
  __IO uint32_t RXOICR;                                     // 0x003C

  __IO uint32_t RXUICR;                                     // 0x0040
  __IO uint32_t MSTICR;                                     // 0x0044
  __IO uint32_t ICR;                                        // 0x0048
  __IO uint32_t DMACR;                                      // 0x004C

  __IO uint32_t DMATDLR0;                                   // 0x0050 DMATDLR
  __IO uint32_t DMATDLR1;                                   // 0x0054 DMARDLR
  __IO uint32_t IDR;                                        // 0x0058
  __IO uint32_t VERSION;                                    // 0x005C COMP_VERSION

  __IO uint32_t DR0;                                        // 0x0060
  __IO uint32_t DR1;                                        // 0x0064
  __IO uint32_t DR2;                                        // 0x0068
  __IO uint32_t DR3;                                        // 0x006C
  __IO uint32_t DR4;                                        // 0x0070
  __IO uint32_t DR5;                                        // 0x0074
  __IO uint32_t DR6;                                        // 0x0078
  __IO uint32_t DR7;                                        // 0x007C
  __IO uint32_t DR8;                                        // 0x0080
  __IO uint32_t DR9;                                        // 0x0084
  __IO uint32_t DR10;                                       // 0x0088
  __IO uint32_t DR11;                                       // 0x008C
  __IO uint32_t DR12;                                       // 0x0090
  __IO uint32_t DR13;                                       // 0x0094
  __IO uint32_t DR14;                                       // 0x0098
  __IO uint32_t DR15;                                       // 0x009C
  __IO uint32_t DR16;                                       // 0x00A0
  __IO uint32_t DR17;                                       // 0x00A4
  __IO uint32_t DR18;                                       // 0x00A8
  __IO uint32_t DR19;                                       // 0x00AC
  __IO uint32_t DR20;                                       // 0x00B0
  __IO uint32_t DR21;                                       // 0x00B4
  __IO uint32_t DR22;                                       // 0x00B8
  __IO uint32_t DR23;                                       // 0x00BC
  __IO uint32_t DR24;                                       // 0x00C0
  __IO uint32_t DR25;                                       // 0x00C4
  __IO uint32_t DR26;                                       // 0x00C8
  __IO uint32_t DR27;                                       // 0x00CC
  __IO uint32_t DR28;                                       // 0x00D0
  __IO uint32_t DR29;                                       // 0x00D4
  __IO uint32_t DR30;                                       // 0x00D8
  __IO uint32_t DR31;                                       // 0x00DC

  __IO uint32_t READ_FAST_SINGLE;                           // 0x00E0
  __IO uint32_t READ_DUAL_DATA;                             // 0x00E4
  __IO uint32_t READ_DUAL_ADDR_DATA;                        // 0x00E8
  __IO uint32_t READ_QUAD_DATA;                             // 0x00EC

  __IO uint32_t READ_QUAD_ADDR_DATA;                        // 0x00F0 RX_SAMPLE_DLY
  __IO uint32_t WRITE_SIGNLE;                               // 0x00F4 RSVD_0
  __IO uint32_t WRITE_DUAL_DATA;                            // 0x00F8 RSVD_1
  __IO uint32_t WRITE_DUAL_ADDR_DATA;                       // 0x00FC RSVD_2

  __IO uint32_t WRITE_QUAD_DATA;                            // 0x0100
  __IO uint32_t WRITE_QUAD_ADDR_DATA;                       // 0x0104
  __IO uint32_t WRITE_ENABLE;                               // 0x0108
  __IO uint32_t READ_STATUS;                                // 0x010C

  __IO uint32_t CTRLR2;                                     // 0x0110
  __IO uint32_t FBAUDR;                                     // 0x0114
  __IO uint32_t ADDR_LENGTH;                                // 0x0118
  __IO uint32_t AUTO_LENGTH;                                // 0x011C

  __IO uint32_t VALID_CMD;                                  // 0x0120
  __IO uint32_t FLASE_SIZE;                                 // 0x0124
  __IO uint32_t FLUSH_FIFO;                                 // 0x0128
} RTL_SPIC_TypeDef;

/**
 * @brief WDG Interface
 */
typedef struct
{
  __IO uint32_t LOAD_COUNT;                                 // 0x00
  __IO uint32_t CURRENT_VAL;                                // 0x04
  __IO uint32_t CTL;                                        // 0x08
  __IO uint32_t EOI;                                        // 0x0C
  __IO uint32_t INT_STATUS;                                 // 0x10
} RTL_ONE_TIMER_TypeDef;

typedef struct
{
  RTL_ONE_TIMER_TypeDef TIMERS[ 8 ];                        // 0x00..0x9F = 20 * 8 = 160 Bytes
  __IO uint32_t INT_STATUS;                                 // 0xA0
  __IO uint32_t EOI;                                        // 0xA4
  __IO uint32_t RAW_INT_STATUS;                             // 0xA8
  __IO uint32_t COMP_VER;                                   // 0xAC
} RTL_TIMER_TypeDef;

typedef struct
{
  union
  {
    __IO uint32_t DLL;                                      // 0x00
    __IO uint32_t REV_BUF;                                  // 0x00
    __IO uint32_t TRAN_HOLD;                                // 0x00
  };
  union
  {
    __IO uint32_t DLH;                                      // 0x04
    __IO uint32_t INTERRUPT_EN;                             // 0x04
  };
  union
  {
    __IO uint32_t INT_ID;                                   // 0x08
    __IO uint32_t FIFO_CTL;                                 // 0x08
  };
  __IO uint32_t LINE_CTL;                                   // 0x0c
  __IO uint32_t MODEM_CTL;                                  // 0x10
  __IO uint32_t LINE_STATUS;                                // 0x14
  __IO uint32_t MODEM_STATUS;                               // 0x18

  __IO uint32_t Dummy0[ 21 ];                               // 0x1C  ****
  __IO uint32_t FIFO_ACCESS;                                // 0x70
  __IO uint32_t Dummy1[ 2 ];                                // 0x74  ****
  __IO uint32_t STATUS;                                     // 0x7c
  __IO uint32_t TFL;                                        // 0x80
  __IO uint32_t RFL;                                        // 0x84
} RTL_LOGU_TypeDef;

/**
 * @brief UART Interface
 */
typedef struct
{
  __IO uint32_t DLL;                                        // 0x00
  union
  {
    __IO uint32_t DLH;                                      // 0x04
    __IO uint32_t INTERRUPT_EN;                             // 0x04
  };
  union
  {
    __IO uint32_t INT_ID;                                   // 0x08
    __IO uint32_t FIFO_CTL;                                 // 0x08
  };
  __IO uint32_t LINE_CTL;                                   // 0x0C
  __IO uint32_t MODEM_CTL;                                  // 0x10
  __IO uint32_t LINE_STATUS;                                // 0x14
  __IO uint32_t MODEM_STATUS;                               // 0x18

  __IO uint32_t SCRATCH_PAD;                                // 0x1C
  __IO uint32_t STS;                                        // 0x20
  __IO uint32_t REV_BUF;                                    // 0x24
  __IO uint32_t TRAN_HOLD;                                  // 0x24
  __IO uint32_t MISC_CTL;                                   // 0x28
  __IO uint32_t Dummy0[ 4 ];                                // 0x2C  ****
  __IO uint32_t DEBUG;                                      // 0x3C
} RTL_UART_TypeDef;

/**
 * @brief USB Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_USB_TypeDef;

/**
 * @brief WDG Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_WDG_TypeDef;


// =================================================================================================
// End of section using anonymous unions
//
#if defined(__ARMCC_VERSION)
#pragma pop
#elif defined(__CWCC__)
#pragma pop
#elif defined(__GNUC__)
/* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
//  #pragma pop
#else
#error Not supported compiler type
#endif

// =================================================================================================
// RTL8195AM Peripheral Registers Bits Definition
//
// FILED_SHIFT  : LSB Position in Register
// FILED_RAWMSK : Mask Before Shift
// FILED_MASK   : Mask After Shift
// FILED(Val)   : ( Val & FILED_RAWMSK ) << FILED_SHIFT
//
// TempVal = ADC->REG;
// TempVal &= ~FILED_MASK; // Clear All Bits of FIELD
// TempVal |=  FILED(Val); // Set Some Bits by Val of FIELD
// REG = TempVal;
//
// =================================================================================================
// SYS : 0x0000
// -------------------------------------------------------------------------------------------------
// SYS_PWR_CTRL
#define SYS_PWR_CTRL_SOC_EN                                            BIT(2)
#define SYS_PWR_CTRL_RET_MEM_EN                                        BIT(1)
#define SYS_PWR_CTRL_PEON_EN                                           BIT(0)

// SYS_ISO_CTRL
#define SYS_ISO_CTRL_SYSPLL                                            BIT(7)
#define SYS_ISO_CTRL_SOC                                               BIT(2)
#define SYS_ISO_CTRL_RET_MEM                                           BIT(1)
#define SYS_ISO_CTRL_PEON                                              BIT(0)

// SYS_FUNC_EN
#define SYS_FUNC_EN_AMACRO_EN                                          BIT(31)
#define SYS_FUNC_EN_PWRON_TRAP_SHTDN_N                                 BIT(30)
#define SYS_FUNC_EN_SIC_MST                                            BIT(25)
#define SYS_FUNC_EN_SIC                                                BIT(24)
#define SYS_FUNC_EN_SYSPEON_EN                                         BIT(4)
#define SYS_FUNC_EN_EELDR                                              BIT(0)

// SYS_CLK_CTRL0
#define SYS_CLK_CTRL0_SOC_OCP_IOBUS_CK_EN                              BIT(2)
#define SYS_CLK_CTRL0_SYSON_CK_EELDR_EN                                BIT(1)
#define SYS_CLK_CTRL0_SYSON_CK_SYSREG_EN                               BIT(0)

// SYS_CLK_CTRL1
#define SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_SHIFT                       (4)
#define SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_RAWMSK                      (0x7)
#define SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_MASK                        \
 (SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_RAWMSK << SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_SHIFT)
#define SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL(x)                          \
 (((x) & SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_RAWMSK) << SYS_CLK_CTRL1_PESOC_OCP_CPU_CK_SEL_SHIFT)
#define SYS_CLK_CTRL1_PESOC_EELDR_CK_SEL                               BIT(0)

// SYS_EFUSE_SYSCFG0
#define SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_SHIFT                    (24)
#define SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_RAWMSK                   (0x3f)
#define SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_MASK                     \
 (SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_RAWMSK << SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00(x)                       \
 (((x) & SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_RAWMSK) << SYS_EFUSE_SYSCFG0_EEROM_SWR_PAR_05_00_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_SHIFT                    (20)
#define SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_RAWMSK                   (0xf)
#define SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_MASK                     \
 (SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_RAWMSK << SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04(x)                       \
 (((x) & SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_RAWMSK) << SYS_EFUSE_SYSCFG0_EEROM_LDO_PAR_07_04_SHIFT)
#define SYS_EFUSE_SYSCFG0_CHIPPDN_EN                                   BIT(17)
#define SYS_EFUSE_SYSCFG0_EEROM_B12V_EN                                BIT(16)
#define SYS_EFUSE_SYSCFG0_EEROM_VID1_SHIFT                             (8)
#define SYS_EFUSE_SYSCFG0_EEROM_VID1_RAWMSK                            (0xff)
#define SYS_EFUSE_SYSCFG0_EEROM_VID1_MASK                              \
 (SYS_EFUSE_SYSCFG0_EEROM_VID1_RAWMSK << SYS_EFUSE_SYSCFG0_EEROM_VID1_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_VID1(x)                                \
 (((x) & SYS_EFUSE_SYSCFG0_EEROM_VID1_RAWMSK) << SYS_EFUSE_SYSCFG0_EEROM_VID1_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_VID0_SHIFT                             (0)
#define SYS_EFUSE_SYSCFG0_EEROM_VID0_RAWMSK                            (0xff)
#define SYS_EFUSE_SYSCFG0_EEROM_VID0_MASK                              \
 (SYS_EFUSE_SYSCFG0_EEROM_VID0_RAWMSK << SYS_EFUSE_SYSCFG0_EEROM_VID0_SHIFT)
#define SYS_EFUSE_SYSCFG0_EEROM_VID0(x)                                \
 (((x) & SYS_EFUSE_SYSCFG0_EEROM_VID0_RAWMSK) << SYS_EFUSE_SYSCFG0_EEROM_VID0_SHIFT)

// SYS_EFUSE_SYSCFG1
#define SYS_EFUSE_SYSCFG1_PDSPL_STL_SHIFT                              (24)
#define SYS_EFUSE_SYSCFG1_PDSPL_STL_RAWMSK                             (0x3)
#define SYS_EFUSE_SYSCFG1_PDSPL_STL_MASK                               \
 (SYS_EFUSE_SYSCFG1_PDSPL_STL_RAWMSK << SYS_EFUSE_SYSCFG1_PDSPL_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_PDSPL_STL(x)                                 \
 (((x) & SYS_EFUSE_SYSCFG1_PDSPL_STL_RAWMSK) << SYS_EFUSE_SYSCFG1_PDSPL_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_PDSOC_STL_SHIFT                              (22)
#define SYS_EFUSE_SYSCFG1_PDSOC_STL_RAWMSK                             (0x3)
#define SYS_EFUSE_SYSCFG1_PDSOC_STL_MASK                               \
 (SYS_EFUSE_SYSCFG1_PDSOC_STL_RAWMSK << SYS_EFUSE_SYSCFG1_PDSOC_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_PDSOC_STL(x)                                 \
 (((x) & SYS_EFUSE_SYSCFG1_PDSOC_STL_RAWMSK) << SYS_EFUSE_SYSCFG1_PDSOC_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_PDPON_STL_SHIFT                              (20)
#define SYS_EFUSE_SYSCFG1_PDPON_STL_RAWMSK                             (0x3)
#define SYS_EFUSE_SYSCFG1_PDPON_STL_MASK                               \
 (SYS_EFUSE_SYSCFG1_PDPON_STL_RAWMSK << SYS_EFUSE_SYSCFG1_PDPON_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_PDPON_STL(x)                                 \
 (((x) & SYS_EFUSE_SYSCFG1_PDPON_STL_RAWMSK) << SYS_EFUSE_SYSCFG1_PDPON_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_SWREG_XRT_SHIFT                              (18)
#define SYS_EFUSE_SYSCFG1_SWREG_XRT_RAWMSK                             (0x3)
#define SYS_EFUSE_SYSCFG1_SWREG_XRT_MASK                               \
 (SYS_EFUSE_SYSCFG1_SWREG_XRT_RAWMSK << SYS_EFUSE_SYSCFG1_SWREG_XRT_SHIFT)
#define SYS_EFUSE_SYSCFG1_SWREG_XRT(x)                                 \
 (((x) & SYS_EFUSE_SYSCFG1_SWREG_XRT_RAWMSK) << SYS_EFUSE_SYSCFG1_SWREG_XRT_SHIFT)
#define SYS_EFUSE_SYSCFG1_SWSLC_STL_SHIFT                              (16)
#define SYS_EFUSE_SYSCFG1_SWSLC_STL_RAWMSK                             (0x3)
#define SYS_EFUSE_SYSCFG1_SWSLC_STL_MASK                               \
 (SYS_EFUSE_SYSCFG1_SWSLC_STL_RAWMSK << SYS_EFUSE_SYSCFG1_SWSLC_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_SWSLC_STL(x)                                 \
 (((x) & SYS_EFUSE_SYSCFG1_SWSLC_STL_RAWMSK) << SYS_EFUSE_SYSCFG1_SWSLC_STL_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_SHIFT                    (14)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_RAWMSK                   (0x3)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_MASK                     \
 (SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_RAWMSK << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45(x)                       \
 (((x) & SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_RAWMSK) << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_46_45_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_SHIFT                    (12)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_RAWMSK                   (0x3)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_MASK                     \
 (SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_RAWMSK << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39(x)                       \
 (((x) & SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_RAWMSK) << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_40_39_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_SHIFT                    (4)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_RAWMSK                   (0xff)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_MASK                     \
 (SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_RAWMSK << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26(x)                       \
 (((x) & SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_RAWMSK) << SYS_EFUSE_SYSCFG1_EEROM_SWR_PAR_33_26_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_SHIFT                        (0)
#define SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_RAWMSK                       (0x7)
#define SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_MASK                         \
 (SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_RAWMSK << SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_SHIFT)
#define SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL(x)                           \
 (((x) & SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_RAWMSK) << SYS_EFUSE_SYSCFG1_EEROM_SWSLD_VOL_SHIFT)

// SYS_EFUSE_SYSCFG2
#define SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_SHIFT               (21)
#define SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_RAWMSK              (0x3ff)
#define SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_MASK                \
 (SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_RAWMSK << SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_SHIFT)
#define SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15(x)                  \
 (((x) & SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_RAWMSK) << SYS_EFUSE_SYSCFG2_EERROM_ANAPAR_SPLL_24_15_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_SHIFT                (16)
#define SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_RAWMSK               (0xf)
#define SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_MASK                 \
 (SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_RAWMSK << SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02(x)                   \
 (((x) & SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_RAWMSK) << SYS_EFUSE_SYSCFG2_EEROM_ANAPAR_SPLL_05_02_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_SHIFT                    (12)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_RAWMSK                   (0x3)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_MASK                     \
 (SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_RAWMSK << SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL(x)                       \
 (((x) & SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_RAWMSK) << SYS_EFUSE_SYSCFG2_EEROM_XTAL_STEL_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_SHIFT                    (8)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_RAWMSK                   (0xf)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_MASK                     \
 (SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_RAWMSK << SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL(x)                       \
 (((x) & SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_RAWMSK) << SYS_EFUSE_SYSCFG2_EEROM_XTAL_FREQ_SEL_SHIFT)

// SYS_EFUSE_SYSCFG3
#define SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_SHIFT                           (28)
#define SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_RAWMSK                          (0xf)
#define SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_MASK                            \
 (SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_RAWMSK << SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBG_PINGP_EN(x)                              \
 (((x) & SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_RAWMSK) << SYS_EFUSE_SYSCFG3_DBG_PINGP_EN_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBG_SEL_SHIFT                                (16)
#define SYS_EFUSE_SYSCFG3_DBG_SEL_RAWMSK                               (0xfff)
#define SYS_EFUSE_SYSCFG3_DBG_SEL_MASK                                 \
 (SYS_EFUSE_SYSCFG3_DBG_SEL_RAWMSK << SYS_EFUSE_SYSCFG3_DBG_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBG_SEL(x)                                   \
 (((x) & SYS_EFUSE_SYSCFG3_DBG_SEL_RAWMSK) << SYS_EFUSE_SYSCFG3_DBG_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_SHIFT                         (14)
#define SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_RAWMSK                        (0x3)
#define SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_MASK                          \
 (SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_RAWMSK << SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL(x)                            \
 (((x) & SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_RAWMSK) << SYS_EFUSE_SYSCFG3_DBGBY3_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_SHIFT                         (12)
#define SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_RAWMSK                        (0x3)
#define SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_MASK                          \
 (SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_RAWMSK << SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL(x)                            \
 (((x) & SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_RAWMSK) << SYS_EFUSE_SYSCFG3_DBGBY2_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_SHIFT                         (10)
#define SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_RAWMSK                        (0x3)
#define SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_MASK                          \
 (SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_RAWMSK << SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL(x)                            \
 (((x) & SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_RAWMSK) << SYS_EFUSE_SYSCFG3_DBGBY1_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_SHIFT                         (8)
#define SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_RAWMSK                        (0x3)
#define SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_MASK                          \
 (SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_RAWMSK << SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL(x)                            \
 (((x) & SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_RAWMSK) << SYS_EFUSE_SYSCFG3_DBGBY0_LOC_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_49                         BIT(3)
#define SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_SHIFT                (0)
#define SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_RAWMSK               (0x7)
#define SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_MASK                 \
 (SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_RAWMSK << SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_SHIFT)
#define SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25(x)                   \
 (((x) & SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_RAWMSK) << SYS_EFUSE_SYSCFG3_EEROM_ANAPAR_SPLL_27_25_SHIFT)

// SYS_EFUSE_SYSCFG4
#define SYS_EFUSE_SYSCFG4_GPIOA_E2_SHIFT                               (1)
#define SYS_EFUSE_SYSCFG4_GPIOA_E2_RAWMSK                              (0x7)
#define SYS_EFUSE_SYSCFG4_GPIOA_E2_MASK                                \
 (SYS_EFUSE_SYSCFG4_GPIOA_E2_RAWMSK << SYS_EFUSE_SYSCFG4_GPIOA_E2_SHIFT)
#define SYS_EFUSE_SYSCFG4_GPIOA_E2(x)                                  \
 (((x) & SYS_EFUSE_SYSCFG4_GPIOA_E2_RAWMSK) << SYS_EFUSE_SYSCFG4_GPIOA_E2_SHIFT)
#define SYS_EFUSE_SYSCFG4_GPIOA_H3L1                                   BIT(0)

// SYS_EFUSE_SYSCFG5
#define SYS_EFUSE_SYSCFG5_NOTHING                                      BIT(0)

// SYS_EFUSE_SYSCFG6
#define SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_SHIFT                (26)
#define SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_RAWMSK               (0x3)
#define SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_MASK                 \
 (SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_RAWMSK << SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL(x)                   \
 (((x) & SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_RAWMSK) << SYS_EFUSE_SYSCFG6_SPIC_INIT_BAUD_RATE_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_SHIFT                            (24)
#define SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_RAWMSK                           (0x3)
#define SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_MASK                             \
 (SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_RAWMSK << SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_SHIFT)
#define SYS_EFUSE_SYSCFG6_CPU_CLK_SEL(x)                               \
 (((x) & SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_RAWMSK) << SYS_EFUSE_SYSCFG6_CPU_CLK_SEL_SHIFT)

// SYS_EFUSE_SYSCFG7
#define SYS_EFUSE_SYSCFG7_MEM_RMV_SIGN                                 BIT(31)
#define SYS_EFUSE_SYSCFG7_MEM_RMV_1PRF1                                BIT(29)
#define SYS_EFUSE_SYSCFG7_MEM_RMV_1PRF0                                BIT(28)
#define SYS_EFUSE_SYSCFG7_MEM_RMV_1PSR                                 BIT(27)
#define SYS_EFUSE_SYSCFG7_MEM_RMV_1PHSR                                BIT(26)
#define SYS_EFUSE_SYSCFG7_MEM_RMV_ROM                                  BIT(25)
#define SYS_EFUSE_SYSCFG7_MEM_RME_CPU_SHIFT                            (22)
#define SYS_EFUSE_SYSCFG7_MEM_RME_CPU_RAWMSK                           (0x7)
#define SYS_EFUSE_SYSCFG7_MEM_RME_CPU_MASK                             \
 (SYS_EFUSE_SYSCFG7_MEM_RME_CPU_RAWMSK << SYS_EFUSE_SYSCFG7_MEM_RME_CPU_SHIFT)
#define SYS_EFUSE_SYSCFG7_MEM_RME_CPU(x)                               \
 (((x) & SYS_EFUSE_SYSCFG7_MEM_RME_CPU_RAWMSK) << SYS_EFUSE_SYSCFG7_MEM_RME_CPU_SHIFT)
#define SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_SHIFT                           (19)
#define SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_RAWMSK                          (0x7)
#define SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_MASK                            \
 (SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_RAWMSK << SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_SHIFT)
#define SYS_EFUSE_SYSCFG7_MEM_RME_WLAN(x)                              \
 (((x) & SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_RAWMSK) << SYS_EFUSE_SYSCFG7_MEM_RME_WLAN_SHIFT)
#define SYS_EFUSE_SYSCFG7_MEM_RME_USB                                  BIT(18)
#define SYS_EFUSE_SYSCFG7_MEM_RME_SDIO                                 BIT(17)

// SYS_REGU_CTRL0
#define SYS_REGU_CTRL0_LDO25M_ADJ_SHIFT                                (20)
#define SYS_REGU_CTRL0_LDO25M_ADJ_RAWMSK                               (0xf)
#define SYS_REGU_CTRL0_LDO25M_ADJ_MASK                                 \
 (SYS_REGU_CTRL0_LDO25M_ADJ_RAWMSK << SYS_REGU_CTRL0_LDO25M_ADJ_SHIFT)
#define SYS_REGU_CTRL0_LDO25M_ADJ(x)                                   \
 (((x) & SYS_REGU_CTRL0_LDO25M_ADJ_RAWMSK) << SYS_REGU_CTRL0_LDO25M_ADJ_SHIFT)
#define SYS_REGU_CTRL0_ANACK_4M_EN                                     BIT(19)
#define SYS_REGU_CTRL0_ANACK_4M_SEL                                    BIT(18)
#define SYS_REGU_CTRL0_PC_EF_EN                                        BIT(17)
#define SYS_REGU_CTRL0_LDOH12_SLP_EN                                   BIT(16)
#define SYS_REGU_CTRL0_LDOH12_ADJ_SHIFT                                (12)
#define SYS_REGU_CTRL0_LDOH12_ADJ_RAWMSK                               (0xf)
#define SYS_REGU_CTRL0_LDOH12_ADJ_MASK                                 \
 (SYS_REGU_CTRL0_LDOH12_ADJ_RAWMSK << SYS_REGU_CTRL0_LDOH12_ADJ_SHIFT)
#define SYS_REGU_CTRL0_LDOH12_ADJ(x)                                   \
 (((x) & SYS_REGU_CTRL0_LDOH12_ADJ_RAWMSK) << SYS_REGU_CTRL0_LDOH12_ADJ_SHIFT)
#define SYS_REGU_CTRL0_LDO25E_ADJ_SHIFT                                (8)
#define SYS_REGU_CTRL0_LDO25E_ADJ_RAWMSK                               (0xf)
#define SYS_REGU_CTRL0_LDO25E_ADJ_MASK                                 \
 (SYS_REGU_CTRL0_LDO25E_ADJ_RAWMSK << SYS_REGU_CTRL0_LDO25E_ADJ_SHIFT)
#define SYS_REGU_CTRL0_LDO25E_ADJ(x)                                   \
 (((x) & SYS_REGU_CTRL0_LDO25E_ADJ_RAWMSK) << SYS_REGU_CTRL0_LDO25E_ADJ_SHIFT)
#define SYS_REGU_CTRL0_DSLEPM_EN                                       BIT(7)
#define SYS_REGU_CTRL0_PC_33V_EN                                       BIT(3)
#define SYS_REGU_CTRL0_PC_EF25_EN                                      BIT(2)
#define SYS_REGU_CTRL0_LDO25M_EN                                       BIT(1)
#define SYS_REGU_CTRL0_LDO25E_EN                                       BIT(0)

// SYS_SWR_CTRL0
#define SYS_SWR_CTRL0_SWR12_COMP_R2_SHIFT                              (30)
#define SYS_SWR_CTRL0_SWR12_COMP_R2_RAWMSK                             (0x3)
#define SYS_SWR_CTRL0_SWR12_COMP_R2_MASK                               \
 (SYS_SWR_CTRL0_SWR12_COMP_R2_RAWMSK << SYS_SWR_CTRL0_SWR12_COMP_R2_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_R2(x)                                 \
 (((x) & SYS_SWR_CTRL0_SWR12_COMP_R2_RAWMSK) << SYS_SWR_CTRL0_SWR12_COMP_R2_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_R1_SHIFT                              (28)
#define SYS_SWR_CTRL0_SWR12_COMP_R1_RAWMSK                             (0x3)
#define SYS_SWR_CTRL0_SWR12_COMP_R1_MASK                               \
 (SYS_SWR_CTRL0_SWR12_COMP_R1_RAWMSK << SYS_SWR_CTRL0_SWR12_COMP_R1_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_R1(x)                                 \
 (((x) & SYS_SWR_CTRL0_SWR12_COMP_R1_RAWMSK) << SYS_SWR_CTRL0_SWR12_COMP_R1_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C3_SHIFT                              (26)
#define SYS_SWR_CTRL0_SWR12_COMP_C3_RAWMSK                             (0x3)
#define SYS_SWR_CTRL0_SWR12_COMP_C3_MASK                               \
 (SYS_SWR_CTRL0_SWR12_COMP_C3_RAWMSK << SYS_SWR_CTRL0_SWR12_COMP_C3_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C3(x)                                 \
 (((x) & SYS_SWR_CTRL0_SWR12_COMP_C3_RAWMSK) << SYS_SWR_CTRL0_SWR12_COMP_C3_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C2_SHIFT                              (24)
#define SYS_SWR_CTRL0_SWR12_COMP_C2_RAWMSK                             (0x3)
#define SYS_SWR_CTRL0_SWR12_COMP_C2_MASK                               \
 (SYS_SWR_CTRL0_SWR12_COMP_C2_RAWMSK << SYS_SWR_CTRL0_SWR12_COMP_C2_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C2(x)                                 \
 (((x) & SYS_SWR_CTRL0_SWR12_COMP_C2_RAWMSK) << SYS_SWR_CTRL0_SWR12_COMP_C2_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C1_SHIFT                              (22)
#define SYS_SWR_CTRL0_SWR12_COMP_C1_RAWMSK                             (0x3)
#define SYS_SWR_CTRL0_SWR12_COMP_C1_MASK                               \
 (SYS_SWR_CTRL0_SWR12_COMP_C1_RAWMSK << SYS_SWR_CTRL0_SWR12_COMP_C1_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_C1(x)                                 \
 (((x) & SYS_SWR_CTRL0_SWR12_COMP_C1_RAWMSK) << SYS_SWR_CTRL0_SWR12_COMP_C1_SHIFT)
#define SYS_SWR_CTRL0_SWR12_COMP_TYPE_L                                BIT(21)
#define SYS_SWR_CTRL0_SWR12_FPWM_MD                                    BIT(20)
#define SYS_SWR_CTRL0_SPSLDO_VOL_SHIFT                                 (17)
#define SYS_SWR_CTRL0_SPSLDO_VOL_RAWMSK                                (0x7)
#define SYS_SWR_CTRL0_SPSLDO_VOL_MASK                                  \
 (SYS_SWR_CTRL0_SPSLDO_VOL_RAWMSK << SYS_SWR_CTRL0_SPSLDO_VOL_SHIFT)
#define SYS_SWR_CTRL0_SPSLDO_VOL(x)                                    \
 (((x) & SYS_SWR_CTRL0_SPSLDO_VOL_RAWMSK) << SYS_SWR_CTRL0_SPSLDO_VOL_SHIFT)
#define SYS_SWR_CTRL0_SWR12_IN_SHIFT                                   (14)
#define SYS_SWR_CTRL0_SWR12_IN_RAWMSK                                  (0x7)
#define SYS_SWR_CTRL0_SWR12_IN_MASK                                    \
 (SYS_SWR_CTRL0_SWR12_IN_RAWMSK << SYS_SWR_CTRL0_SWR12_IN_SHIFT)
#define SYS_SWR_CTRL0_SWR12_IN(x)                                      \
 (((x) & SYS_SWR_CTRL0_SWR12_IN_RAWMSK) << SYS_SWR_CTRL0_SWR12_IN_SHIFT)
#define SYS_SWR_CTRL0_SWR12_STD_SHIFT                                  (12)
#define SYS_SWR_CTRL0_SWR12_STD_RAWMSK                                 (0x3)
#define SYS_SWR_CTRL0_SWR12_STD_MASK                                   \
 (SYS_SWR_CTRL0_SWR12_STD_RAWMSK << SYS_SWR_CTRL0_SWR12_STD_SHIFT)
#define SYS_SWR_CTRL0_SWR12_STD(x)                                     \
 (((x) & SYS_SWR_CTRL0_SWR12_STD_RAWMSK) << SYS_SWR_CTRL0_SWR12_STD_SHIFT)
#define SYS_SWR_CTRL0_SWR12_VOL_SHIFT                                  (8)
#define SYS_SWR_CTRL0_SWR12_VOL_RAWMSK                                 (0xf)
#define SYS_SWR_CTRL0_SWR12_VOL_MASK                                   \
 (SYS_SWR_CTRL0_SWR12_VOL_RAWMSK << SYS_SWR_CTRL0_SWR12_VOL_SHIFT)
#define SYS_SWR_CTRL0_SWR12_VOL(x)                                     \
 (((x) & SYS_SWR_CTRL0_SWR12_VOL_RAWMSK) << SYS_SWR_CTRL0_SWR12_VOL_SHIFT)
#define SYS_SWR_CTRL0_SWR_EN                                           BIT(1)
#define SYS_SWR_CTRL0_SWR_LDO_EN                                       BIT(0)

// SYS_SWR_CTRL1
#define SYS_SWR_CTRL1_SW12_PFM_SEL                                     BIT(25)
#define SYS_SWR_CTRL1_SW12_AUTO_ZCD_L                                  BIT(24)
#define SYS_SWR_CTRL1_SW12_AUTO_MODE                                   BIT(23)
#define SYS_SWR_CTRL1_SW12_LDOF_L                                      BIT(22)
#define SYS_SWR_CTRL1_SW12_OCPS_L                                      BIT(21)
#define SYS_SWR_CTRL1_SW12_TBOX_SHIFT                                  (17)
#define SYS_SWR_CTRL1_SW12_TBOX_RAWMSK                                 (0x3)
#define SYS_SWR_CTRL1_SW12_TBOX_MASK                                   \
 (SYS_SWR_CTRL1_SW12_TBOX_RAWMSK << SYS_SWR_CTRL1_SW12_TBOX_SHIFT)
#define SYS_SWR_CTRL1_SW12_TBOX(x)                                     \
 (((x) & SYS_SWR_CTRL1_SW12_TBOX_RAWMSK) << SYS_SWR_CTRL1_SW12_TBOX_SHIFT)
#define SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_SHIFT                         (15)
#define SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_RAWMSK                        (0x3)
#define SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_MASK                          \
 (SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_RAWMSK << SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_SHIFT)
#define SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY(x)                            \
 (((x) & SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_RAWMSK) << SYS_SWR_CTRL1_SW12_NONOVRLAP_DLY_SHIFT)
#define SYS_SWR_CTRL1_SW12_CLAMP_DUTY                                  BIT(14)
#define SYS_SWR_CTRL1_SWR12_BYPASS_SSR                                 BIT(13)
#define SYS_SWR_CTRL1_SWR12_ZCDOUT_EN                                  BIT(12)
#define SYS_SWR_CTRL1_SWR12_POW_ZCD                                    BIT(11)
#define SYS_SWR_CTRL1_SW12_AREN                                        BIT(10)
#define SYS_SWR_CTRL1_SWR12_OCP_CUR_SHIFT                              (7)
#define SYS_SWR_CTRL1_SWR12_OCP_CUR_RAWMSK                             (0x7)
#define SYS_SWR_CTRL1_SWR12_OCP_CUR_MASK                               \
 (SYS_SWR_CTRL1_SWR12_OCP_CUR_RAWMSK << SYS_SWR_CTRL1_SWR12_OCP_CUR_SHIFT)
#define SYS_SWR_CTRL1_SWR12_OCP_CUR(x)                                 \
 (((x) & SYS_SWR_CTRL1_SWR12_OCP_CUR_RAWMSK) << SYS_SWR_CTRL1_SWR12_OCP_CUR_SHIFT)
#define SYS_SWR_CTRL1_SWR12_OCP_EN                                     BIT(6)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_SHIFT                        (4)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_RAWMSK                       (0x3)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_MASK                         \
 (SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_RAWMSK << SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_SHIFT)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L(x)                           \
 (((x) & SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_RAWMSK) << SYS_SWR_CTRL1_SWR12_SAWTOOTH_CF_L_SHIFT)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_SHIFT                       (2)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_RAWMSK                      (0x3)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_MASK                        \
 (SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_RAWMSK << SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_SHIFT)
#define SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L(x)                          \
 (((x) & SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_RAWMSK) << SYS_SWR_CTRL1_SWR12_SAWTOOTH_CFC_L_SHIFT)
#define SYS_SWR_CTRL1_SWR12_COMP_R3_SHIFT                              (0)
#define SYS_SWR_CTRL1_SWR12_COMP_R3_RAWMSK                             (0x3)
#define SYS_SWR_CTRL1_SWR12_COMP_R3_MASK                               \
 (SYS_SWR_CTRL1_SWR12_COMP_R3_RAWMSK << SYS_SWR_CTRL1_SWR12_COMP_R3_SHIFT)
#define SYS_SWR_CTRL1_SWR12_COMP_R3(x)                                 \
 (((x) & SYS_SWR_CTRL1_SWR12_COMP_R3_RAWMSK) << SYS_SWR_CTRL1_SWR12_COMP_R3_SHIFT)

// SYS_XTAL_CTRL0
#define SYS_XTAL_CTRL0_XQSEL                                           BIT(31)
#define SYS_XTAL_CTRL0_XQSEL_RF                                        BIT(30)
#define SYS_XTAL_CTRL0_SC_XO_SHIFT                                     (24)
#define SYS_XTAL_CTRL0_SC_XO_RAWMSK                                    (0x3f)
#define SYS_XTAL_CTRL0_SC_XO_MASK                                      \
 (SYS_XTAL_CTRL0_SC_XO_RAWMSK << SYS_XTAL_CTRL0_SC_XO_SHIFT)
#define SYS_XTAL_CTRL0_SC_XO(x)                                        \
 (((x) & SYS_XTAL_CTRL0_SC_XO_RAWMSK) << SYS_XTAL_CTRL0_SC_XO_SHIFT)
#define SYS_XTAL_CTRL0_SC_XI_SHIFT                                     (18)
#define SYS_XTAL_CTRL0_SC_XI_RAWMSK                                    (0x3f)
#define SYS_XTAL_CTRL0_SC_XI_MASK                                      \
 (SYS_XTAL_CTRL0_SC_XI_RAWMSK << SYS_XTAL_CTRL0_SC_XI_SHIFT)
#define SYS_XTAL_CTRL0_SC_XI(x)                                        \
 (((x) & SYS_XTAL_CTRL0_SC_XI_RAWMSK) << SYS_XTAL_CTRL0_SC_XI_SHIFT)
#define SYS_XTAL_CTRL0_GMN_SHIFT                                       (13)
#define SYS_XTAL_CTRL0_GMN_RAWMSK                                      (0x1f)
#define SYS_XTAL_CTRL0_GMN_MASK                                        \
 (SYS_XTAL_CTRL0_GMN_RAWMSK << SYS_XTAL_CTRL0_GMN_SHIFT)
#define SYS_XTAL_CTRL0_GMN(x)                                          \
 (((x) & SYS_XTAL_CTRL0_GMN_RAWMSK) << SYS_XTAL_CTRL0_GMN_SHIFT)
#define SYS_XTAL_CTRL0_GMP_SHIFT                                       (8)
#define SYS_XTAL_CTRL0_GMP_RAWMSK                                      (0x1f)
#define SYS_XTAL_CTRL0_GMP_MASK                                        \
 (SYS_XTAL_CTRL0_GMP_RAWMSK << SYS_XTAL_CTRL0_GMP_SHIFT)
#define SYS_XTAL_CTRL0_GMP(x)                                          \
 (((x) & SYS_XTAL_CTRL0_GMP_RAWMSK) << SYS_XTAL_CTRL0_GMP_SHIFT)
#define SYS_XTAL_CTRL0_EN                                              BIT(1)
#define SYS_XTAL_CTRL0_BGMB_EN                                         BIT(0)

// SYS_XTAL_CTRL1
#define SYS_XTAL_CTRL1_COUNTER_MUX_SHIFT                               (25)
#define SYS_XTAL_CTRL1_COUNTER_MUX_RAWMSK                              (0x3)
#define SYS_XTAL_CTRL1_COUNTER_MUX_MASK                                \
 (SYS_XTAL_CTRL1_COUNTER_MUX_RAWMSK << SYS_XTAL_CTRL1_COUNTER_MUX_SHIFT)
#define SYS_XTAL_CTRL1_COUNTER_MUX(x)                                  \
 (((x) & SYS_XTAL_CTRL1_COUNTER_MUX_RAWMSK) << SYS_XTAL_CTRL1_COUNTER_MUX_SHIFT)
#define SYS_XTAL_CTRL1_DELAY_SYSPLL                                    BIT(24)
#define SYS_XTAL_CTRL1_DELAY_USB                                       BIT(23)
#define SYS_XTAL_CTRL1_DELAY_WLAFE                                     BIT(22)
#define SYS_XTAL_CTRL1_AGPIO_SEL                                       BIT(21)
#define SYS_XTAL_CTRL1_DRV_AGPIO_SHIFT                                 (19)
#define SYS_XTAL_CTRL1_DRV_AGPIO_RAWMSK                                (0x3)
#define SYS_XTAL_CTRL1_DRV_AGPIO_MASK                                  \
 (SYS_XTAL_CTRL1_DRV_AGPIO_RAWMSK << SYS_XTAL_CTRL1_DRV_AGPIO_SHIFT)
#define SYS_XTAL_CTRL1_DRV_AGPIO(x)                                    \
 (((x) & SYS_XTAL_CTRL1_DRV_AGPIO_RAWMSK) << SYS_XTAL_CTRL1_DRV_AGPIO_SHIFT)
#define SYS_XTAL_CTRL1_AGPIO_SHIFT                                     (16)
#define SYS_XTAL_CTRL1_AGPIO_RAWMSK                                    (0x7)
#define SYS_XTAL_CTRL1_AGPIO_MASK                                      \
 (SYS_XTAL_CTRL1_AGPIO_RAWMSK << SYS_XTAL_CTRL1_AGPIO_SHIFT)
#define SYS_XTAL_CTRL1_AGPIO(x)                                        \
 (((x) & SYS_XTAL_CTRL1_AGPIO_RAWMSK) << SYS_XTAL_CTRL1_AGPIO_SHIFT)
#define SYS_XTAL_CTRL1_DRV_SYSPLL_SHIFT                                (14)
#define SYS_XTAL_CTRL1_DRV_SYSPLL_RAWMSK                               (0x3)
#define SYS_XTAL_CTRL1_DRV_SYSPLL_MASK                                 \
 (SYS_XTAL_CTRL1_DRV_SYSPLL_RAWMSK << SYS_XTAL_CTRL1_DRV_SYSPLL_SHIFT)
#define SYS_XTAL_CTRL1_DRV_SYSPLL(x)                                   \
 (((x) & SYS_XTAL_CTRL1_DRV_SYSPLL_RAWMSK) << SYS_XTAL_CTRL1_DRV_SYSPLL_SHIFT)
#define SYS_XTAL_CTRL1_GATE_SYSPLL                                     BIT(13)
#define SYS_XTAL_CTRL1_DRV_USB_SHIFT                                   (11)
#define SYS_XTAL_CTRL1_DRV_USB_RAWMSK                                  (0x3)
#define SYS_XTAL_CTRL1_DRV_USB_MASK                                    \
 (SYS_XTAL_CTRL1_DRV_USB_RAWMSK << SYS_XTAL_CTRL1_DRV_USB_SHIFT)
#define SYS_XTAL_CTRL1_DRV_USB(x)                                      \
 (((x) & SYS_XTAL_CTRL1_DRV_USB_RAWMSK) << SYS_XTAL_CTRL1_DRV_USB_SHIFT)
#define SYS_XTAL_CTRL1_GATE_USB                                        BIT(10)
#define SYS_XTAL_CTRL1_DRV_WLAFE_SHIFT                                 (8)
#define SYS_XTAL_CTRL1_DRV_WLAFE_RAWMSK                                (0x3)
#define SYS_XTAL_CTRL1_DRV_WLAFE_MASK                                  \
 (SYS_XTAL_CTRL1_DRV_WLAFE_RAWMSK << SYS_XTAL_CTRL1_DRV_WLAFE_SHIFT)
#define SYS_XTAL_CTRL1_DRV_WLAFE(x)                                    \
 (((x) & SYS_XTAL_CTRL1_DRV_WLAFE_RAWMSK) << SYS_XTAL_CTRL1_DRV_WLAFE_SHIFT)
#define SYS_XTAL_CTRL1_GATE_WLAFE                                      BIT(7)
#define SYS_XTAL_CTRL1_DRV_RF2_SHIFT                                   (5)
#define SYS_XTAL_CTRL1_DRV_RF2_RAWMSK                                  (0x3)
#define SYS_XTAL_CTRL1_DRV_RF2_MASK                                    \
 (SYS_XTAL_CTRL1_DRV_RF2_RAWMSK << SYS_XTAL_CTRL1_DRV_RF2_SHIFT)
#define SYS_XTAL_CTRL1_DRV_RF2(x)                                      \
 (((x) & SYS_XTAL_CTRL1_DRV_RF2_RAWMSK) << SYS_XTAL_CTRL1_DRV_RF2_SHIFT)
#define SYS_XTAL_CTRL1_GATE_RF2                                        BIT(4)
#define SYS_XTAL_CTRL1_DRV_RF1_SHIFT                                   (3)
#define SYS_XTAL_CTRL1_DRV_RF1_RAWMSK                                  (0x3)
#define SYS_XTAL_CTRL1_DRV_RF1_MASK                                    \
 (SYS_XTAL_CTRL1_DRV_RF1_RAWMSK << SYS_XTAL_CTRL1_DRV_RF1_SHIFT)
#define SYS_XTAL_CTRL1_DRV_RF1(x)                                      \
 (((x) & SYS_XTAL_CTRL1_DRV_RF1_RAWMSK) << SYS_XTAL_CTRL1_DRV_RF1_SHIFT)
#define SYS_XTAL_CTRL1_GATE_RF1                                        BIT(1)
#define SYS_XTAL_CTRL1_LDO_SHIFT                                       (0)
#define SYS_XTAL_CTRL1_LDO_RAWMSK                                      (0x3)
#define SYS_XTAL_CTRL1_LDO_MASK                                        \
 (SYS_XTAL_CTRL1_LDO_RAWMSK << SYS_XTAL_CTRL1_LDO_SHIFT)
#define SYS_XTAL_CTRL1_LDO(x)                                          \
 (((x) & SYS_XTAL_CTRL1_LDO_RAWMSK) << SYS_XTAL_CTRL1_LDO_SHIFT)

// SYS_SYSPLL_CTRL0
#define SYS_SYSPLL_CTRL0_LPF_R3_SHIFT                                  (29)
#define SYS_SYSPLL_CTRL0_LPF_R3_RAWMSK                                 (0x7)
#define SYS_SYSPLL_CTRL0_LPF_R3_MASK                                   \
 (SYS_SYSPLL_CTRL0_LPF_R3_RAWMSK << SYS_SYSPLL_CTRL0_LPF_R3_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_R3(x)                                     \
 (((x) & SYS_SYSPLL_CTRL0_LPF_R3_RAWMSK) << SYS_SYSPLL_CTRL0_LPF_R3_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_CS_SHIFT                                  (27)
#define SYS_SYSPLL_CTRL0_LPF_CS_RAWMSK                                 (0x3)
#define SYS_SYSPLL_CTRL0_LPF_CS_MASK                                   \
 (SYS_SYSPLL_CTRL0_LPF_CS_RAWMSK << SYS_SYSPLL_CTRL0_LPF_CS_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_CS(x)                                     \
 (((x) & SYS_SYSPLL_CTRL0_LPF_CS_RAWMSK) << SYS_SYSPLL_CTRL0_LPF_CS_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_CP_SHIFT                                  (25)
#define SYS_SYSPLL_CTRL0_LPF_CP_RAWMSK                                 (0x3)
#define SYS_SYSPLL_CTRL0_LPF_CP_MASK                                   \
 (SYS_SYSPLL_CTRL0_LPF_CP_RAWMSK << SYS_SYSPLL_CTRL0_LPF_CP_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_CP(x)                                     \
 (((x) & SYS_SYSPLL_CTRL0_LPF_CP_RAWMSK) << SYS_SYSPLL_CTRL0_LPF_CP_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_C3_SHIFT                                  (23)
#define SYS_SYSPLL_CTRL0_LPF_C3_RAWMSK                                 (0x3)
#define SYS_SYSPLL_CTRL0_LPF_C3_MASK                                   \
 (SYS_SYSPLL_CTRL0_LPF_C3_RAWMSK << SYS_SYSPLL_CTRL0_LPF_C3_SHIFT)
#define SYS_SYSPLL_CTRL0_LPF_C3(x)                                     \
 (((x) & SYS_SYSPLL_CTRL0_LPF_C3_RAWMSK) << SYS_SYSPLL_CTRL0_LPF_C3_SHIFT)
#define SYS_SYSPLL_CTRL0_WDOG_ENB                                      BIT(22)
#define SYS_SYSPLL_CTRL0_CKTST_EN                                      BIT(21)
#define SYS_SYSPLL_CTRL0_MONCK_SEL_SHIFT                               (18)
#define SYS_SYSPLL_CTRL0_MONCK_SEL_RAWMSK                              (0x7)
#define SYS_SYSPLL_CTRL0_MONCK_SEL_MASK                                \
 (SYS_SYSPLL_CTRL0_MONCK_SEL_RAWMSK << SYS_SYSPLL_CTRL0_MONCK_SEL_SHIFT)
#define SYS_SYSPLL_CTRL0_MONCK_SEL(x)                                  \
 (((x) & SYS_SYSPLL_CTRL0_MONCK_SEL_RAWMSK) << SYS_SYSPLL_CTRL0_MONCK_SEL_SHIFT)
#define SYS_SYSPLL_CTRL0_CP_IOFFSET_SHIFT                              (13)
#define SYS_SYSPLL_CTRL0_CP_IOFFSET_RAWMSK                             (0x1f)
#define SYS_SYSPLL_CTRL0_CP_IOFFSET_MASK                               \
 (SYS_SYSPLL_CTRL0_CP_IOFFSET_RAWMSK << SYS_SYSPLL_CTRL0_CP_IOFFSET_SHIFT)
#define SYS_SYSPLL_CTRL0_CP_IOFFSET(x)                                 \
 (((x) & SYS_SYSPLL_CTRL0_CP_IOFFSET_RAWMSK) << SYS_SYSPLL_CTRL0_CP_IOFFSET_SHIFT)
#define SYS_SYSPLL_CTRL0_CP_IDOUBLE                                    BIT(12)
#define SYS_SYSPLL_CTRL0_CP_BIAS_SHIFT                                 (9)
#define SYS_SYSPLL_CTRL0_CP_BIAS_RAWMSK                                (0x7)
#define SYS_SYSPLL_CTRL0_CP_BIAS_MASK                                  \
 (SYS_SYSPLL_CTRL0_CP_BIAS_RAWMSK << SYS_SYSPLL_CTRL0_CP_BIAS_SHIFT)
#define SYS_SYSPLL_CTRL0_CP_BIAS(x)                                    \
 (((x) & SYS_SYSPLL_CTRL0_CP_BIAS_RAWMSK) << SYS_SYSPLL_CTRL0_CP_BIAS_SHIFT)
#define SYS_SYSPLL_CTRL0_FREF_EDGE                                     BIT(8)
#define SYS_SYSPLL_CTRL0_EN                                            BIT(1)
#define SYS_SYSPLL_CTRL0_LVPC_EN                                       BIT(0)

// SYS_SYSPLL_CTRL1
#define SYS_SYSPLL_CTRL1_CK500K_SEL                                    BIT(15)
#define SYS_SYSPLL_CTRL1_CK200M_EN                                     BIT(14)
#define SYS_SYSPLL_CTRL1_CKSDR_EN                                      BIT(13)
#define SYS_SYSPLL_CTRL1_CKSDR_DIV_SHIFT                               (11)
#define SYS_SYSPLL_CTRL1_CKSDR_DIV_RAWMSK                              (0x3)
#define SYS_SYSPLL_CTRL1_CKSDR_DIV_MASK                                \
 (SYS_SYSPLL_CTRL1_CKSDR_DIV_RAWMSK << SYS_SYSPLL_CTRL1_CKSDR_DIV_SHIFT)
#define SYS_SYSPLL_CTRL1_CKSDR_DIV(x)                                  \
 (((x) & SYS_SYSPLL_CTRL1_CKSDR_DIV_RAWMSK) << SYS_SYSPLL_CTRL1_CKSDR_DIV_SHIFT)
#define SYS_SYSPLL_CTRL1_CK24P576_EN                                   BIT(9)
#define SYS_SYSPLL_CTRL1_CK22P5792_EN                                  BIT(8)
#define SYS_SYSPLL_CTRL1_CK_PS_EN                                      BIT(6)
#define SYS_SYSPLL_CTRL1_CK_PS_SEL_SHIFT                               (3)
#define SYS_SYSPLL_CTRL1_CK_PS_SEL_RAWMSK                              (0x7)
#define SYS_SYSPLL_CTRL1_CK_PS_SEL_MASK                                \
 (SYS_SYSPLL_CTRL1_CK_PS_SEL_RAWMSK << SYS_SYSPLL_CTRL1_CK_PS_SEL_SHIFT)
#define SYS_SYSPLL_CTRL1_CK_PS_SEL(x)                                  \
 (((x) & SYS_SYSPLL_CTRL1_CK_PS_SEL_RAWMSK) << SYS_SYSPLL_CTRL1_CK_PS_SEL_SHIFT)
#define SYS_SYSPLL_CTRL1_LPF_RS_SHIFT                                  (0)
#define SYS_SYSPLL_CTRL1_LPF_RS_RAWMSK                                 (0x7)
#define SYS_SYSPLL_CTRL1_LPF_RS_MASK                                   \
 (SYS_SYSPLL_CTRL1_LPF_RS_RAWMSK << SYS_SYSPLL_CTRL1_LPF_RS_SHIFT)
#define SYS_SYSPLL_CTRL1_LPF_RS(x)                                     \
 (((x) & SYS_SYSPLL_CTRL1_LPF_RS_RAWMSK) << SYS_SYSPLL_CTRL1_LPF_RS_SHIFT)

// SYS_SYSPLL_CTRL2
#define SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_SHIFT                       (0)
#define SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_RAWMSK                      (0xffffffffL)
#define SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_MASK                        \
 (SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_RAWMSK << SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_SHIFT)
#define SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH(x)                          \
 (((x) & SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_RAWMSK) << SYS_SYSPLL_CTRL2_XTAL_DRV_RF_LATCH_SHIFT)
#define SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_SHIFT                    (0)
#define SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_RAWMSK                   (0x7)
#define SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_MASK                     \
 (SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_RAWMSK << SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_SHIFT)
#define SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL(x)                       \
 (((x) & SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_RAWMSK) << SYS_SYSPLL_CTRL2_PESOC_CPU_OCP_CK_SEL_SHIFT)

// SYS_ANA_TIM_CTRL
#define SYS_ANA_TIM_CTRL_ANACK_TU_TIME_SHIFT                           (16)
#define SYS_ANA_TIM_CTRL_ANACK_TU_TIME_RAWMSK                          (0x3f)
#define SYS_ANA_TIM_CTRL_ANACK_TU_TIME_MASK                            \
 (SYS_ANA_TIM_CTRL_ANACK_TU_TIME_RAWMSK << SYS_ANA_TIM_CTRL_ANACK_TU_TIME_SHIFT)
#define SYS_ANA_TIM_CTRL_ANACK_TU_TIME(x)                              \
 (((x) & SYS_ANA_TIM_CTRL_ANACK_TU_TIME_RAWMSK) << SYS_ANA_TIM_CTRL_ANACK_TU_TIME_SHIFT)
#define SYS_ANA_TIM_CTRL_DSBYCNT_EN                                    BIT(15)
#define SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_SHIFT                          (8)
#define SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_RAWMSK                         (0xf)
#define SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_MASK                           \
 (SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_RAWMSK << SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_SHIFT)
#define SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL(x)                             \
 (((x) & SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_RAWMSK) << SYS_ANA_TIM_CTRL_DSTDY_TIM_SCAL_SHIFT)
#define SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_SHIFT                        (0)
#define SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_RAWMSK                       (0xff)
#define SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_MASK                         \
 (SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_RAWMSK << SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_SHIFT)
#define SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD(x)                           \
 (((x) & SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_RAWMSK) << SYS_ANA_TIM_CTRL_DSTBY_TIM_PERIOD_SHIFT)

// SYS_DSLP_TIM_CTRL -- SYS_REGU_CTRL1 ?
#define SYS_REGU_CTRL1_ASIF_EN_SHIFT                                   (24)
#define SYS_REGU_CTRL1_ASIF_EN_RAWMSK                                  (0xff)
#define SYS_REGU_CTRL1_ASIF_EN_MASK                                    \
 (SYS_REGU_CTRL1_ASIF_EN_RAWMSK << SYS_REGU_CTRL1_ASIF_EN_SHIFT)
#define SYS_REGU_CTRL1_ASIF_EN(x)                                      \
 (((x) & SYS_REGU_CTRL1_ASIF_EN_RAWMSK) << SYS_REGU_CTRL1_ASIF_EN_SHIFT)
#define SYS_REGU_CTRL1_ASIF_THP_DA_SHIFT                               (20)
#define SYS_REGU_CTRL1_ASIF_THP_DA_RAWMSK                              (0x3)
#define SYS_REGU_CTRL1_ASIF_THP_DA_MASK                                \
 (SYS_REGU_CTRL1_ASIF_THP_DA_RAWMSK << SYS_REGU_CTRL1_ASIF_THP_DA_SHIFT)
#define SYS_REGU_CTRL1_ASIF_THP_DA(x)                                  \
 (((x) & SYS_REGU_CTRL1_ASIF_THP_DA_RAWMSK) << SYS_REGU_CTRL1_ASIF_THP_DA_SHIFT)
#define SYS_REGU_CTRL1_ASIF_TPD_CK_SHIFT                               (18)
#define SYS_REGU_CTRL1_ASIF_TPD_CK_RAWMSK                              (0x3)
#define SYS_REGU_CTRL1_ASIF_TPD_CK_MASK                                \
 (SYS_REGU_CTRL1_ASIF_TPD_CK_RAWMSK << SYS_REGU_CTRL1_ASIF_TPD_CK_SHIFT)
#define SYS_REGU_CTRL1_ASIF_TPD_CK(x)                                  \
 (((x) & SYS_REGU_CTRL1_ASIF_TPD_CK_RAWMSK) << SYS_REGU_CTRL1_ASIF_TPD_CK_SHIFT)
#define SYS_REGU_CTRL1_ASIF_TSP_DA_SHIFT                               (16)
#define SYS_REGU_CTRL1_ASIF_TSP_DA_RAWMSK                              (0x3)
#define SYS_REGU_CTRL1_ASIF_TSP_DA_MASK                                \
 (SYS_REGU_CTRL1_ASIF_TSP_DA_RAWMSK << SYS_REGU_CTRL1_ASIF_TSP_DA_SHIFT)
#define SYS_REGU_CTRL1_ASIF_TSP_DA(x)                                  \
 (((x) & SYS_REGU_CTRL1_ASIF_TSP_DA_RAWMSK) << SYS_REGU_CTRL1_ASIF_TSP_DA_SHIFT)
#define SYS_REGU_CTRL1_ASIF_POLL                                       BIT(15)
#define SYS_REGU_CTRL1_ASIF_MODE                                       BIT(14)
#define SYS_REGU_CTRL1_ASIF_WE                                         BIT(12)
#define SYS_REGU_CTRL1_ASIF_AD_SHIFT                                   (8)
#define SYS_REGU_CTRL1_ASIF_AD_RAWMSK                                  (0xf)
#define SYS_REGU_CTRL1_ASIF_AD_MASK                                    \
 (SYS_REGU_CTRL1_ASIF_AD_RAWMSK << SYS_REGU_CTRL1_ASIF_AD_SHIFT)
#define SYS_REGU_CTRL1_ASIF_AD(x)                                      \
 (((x) & SYS_REGU_CTRL1_ASIF_AD_RAWMSK) << SYS_REGU_CTRL1_ASIF_AD_SHIFT)
#define SYS_REGU_CTRL1_ASIF_WD_SHIFT                                   (0)
#define SYS_REGU_CTRL1_ASIF_WD_RAWMSK                                  (0xff)
#define SYS_REGU_CTRL1_ASIF_WD_MASK                                    \
 (SYS_REGU_CTRL1_ASIF_WD_RAWMSK << SYS_REGU_CTRL1_ASIF_WD_SHIFT)
#define SYS_REGU_CTRL1_ASIF_WD(x)                                      \
 (((x) & SYS_REGU_CTRL1_ASIF_WD_RAWMSK) << SYS_REGU_CTRL1_ASIF_WD_SHIFT)

// SYS_DSLP_TIM_CAL_CTRL
#define SYS_DSLP_TIM_CAL_CTRL_EN                                       BIT(24)
#define SYS_DSLP_TIM_CAL_CTRL_PERIOD_SHIFT                             (0)
#define SYS_DSLP_TIM_CAL_CTRL_PERIOD_RAWMSK                            (0x7fffff)
#define SYS_DSLP_TIM_CAL_CTRL_PERIOD_MASK                              \
 (SYS_DSLP_TIM_CAL_CTRL_PERIOD_RAWMSK << SYS_DSLP_TIM_CAL_CTRL_PERIOD_SHIFT)
#define SYS_DSLP_TIM_CAL_CTRL_PERIOD(x)                                \
 (((x) & SYS_DSLP_TIM_CAL_CTRL_PERIOD_RAWMSK) << SYS_DSLP_TIM_CAL_CTRL_PERIOD_SHIFT)

// SYS_DEBUG_CTRL
#define SYS_DEBUG_CTRL_PIN_EN                                          BIT(0)

// SYS_PINMUX_CTRL
#define SYS_PINMUX_CTRL_EEPROM_PIN_EN                                  BIT(4)
#define SYS_PINMUX_CTRL_SIC_PIN_EN                                     BIT(0)

// SYS_GPIO_DSTBY_WAKE_CTRL0
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOE3_WEVENT_STS                    BIT(27)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOD5_WEVENT_STS                    BIT(26)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOC7_WEVENT_STS                    BIT(25)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOA5_WEVENT_STS                    BIT(24)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIO_GPE3_PULL_CTRL_EN               BIT(19)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIO_GPD5_PULL_CTRL_EN               BIT(18)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIO_GPC7_PULL_CTRL_EN               BIT(17)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIO_GPA5_PULL_CTRL_EN               BIT(16)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOE3_WINT_MODE                     BIT(11)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOD5_WINT_MODE                     BIT(10)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOC7_WINT_MODE                     BIT(9)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOA5_WINT_MODE                     BIT(8)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOE3_PIN_EN                        BIT(3)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOD5_PIN_EN                        BIT(2)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOC7_PIN_EN                        BIT(1)
#define SYS_GPIO_DSTBY_WAKE_CTRL0_GPIOA5_PIN_EN                        BIT(0)

// SYS_GPIO_DSTBY_WAKE_CTRL1
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOE3_SHTDN_N                       BIT(19)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOD5_SHTDN_N                       BIT(18)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOC7_SHTDN_N                       BIT(17)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOA5_SHTDN_N                       BIT(16)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_SHIFT         (8)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_RAWMSK        (0x3)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_MASK          \
 (SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_RAWMSK << SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_SHIFT)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL(x)            \
 (((x) & SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_RAWMSK) << SYS_GPIO_DSTBY_WAKE_CTRL1_WINT_DEBOUNCE_TIM_SCAL_SHIFT)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOE3_WINT_DEBOUNCE_EN              BIT(3)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOD5_WINT_DEBOUNCE_EN              BIT(2)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOC7_WINT_DEBOUNCE_EN              BIT(1)
#define SYS_GPIO_DSTBY_WAKE_CTRL1_GPIOA5_WINT_DEBOUNCE_EN              BIT(0)

// SYS_DEBUG_REG
#define SYS_DEBUG_REG_VALUE_SHIFT                                      (0)
#define SYS_DEBUG_REG_VALUE_RAWMSK                                     (0xffffffffL)
#define SYS_DEBUG_REG_VALUE_MASK                                       \
 (SYS_DEBUG_REG_VALUE_RAWMSK << SYS_DEBUG_REG_VALUE_SHIFT)
#define SYS_DEBUG_REG_VALUE(x)                                         \
 (((x) & SYS_DEBUG_REG_VALUE_RAWMSK) << SYS_DEBUG_REG_VALUE_SHIFT)

// SYS_EEPROM_CTRL0
#define SYS_EEPROM_CTRL0_EFUSE_UNLOCK_SHIFT                            (24)
#define SYS_EEPROM_CTRL0_EFUSE_UNLOCK_RAWMSK                           (0xff)
#define SYS_EEPROM_CTRL0_EFUSE_UNLOCK_MASK                             \
 (SYS_EEPROM_CTRL0_EFUSE_UNLOCK_RAWMSK << SYS_EEPROM_CTRL0_EFUSE_UNLOCK_SHIFT)
#define SYS_EEPROM_CTRL0_EFUSE_UNLOCK(x)                               \
 (((x) & SYS_EEPROM_CTRL0_EFUSE_UNLOCK_RAWMSK) << SYS_EEPROM_CTRL0_EFUSE_UNLOCK_SHIFT)
#define SYS_EEPROM_CTRL0_SYS_EFUSE_LDALL                               BIT(16)
#define SYS_EEPROM_CTRL0_VPDIDX_SHIFT                                  (8)
#define SYS_EEPROM_CTRL0_VPDIDX_RAWMSK                                 (0xff)
#define SYS_EEPROM_CTRL0_VPDIDX_MASK                                   \
 (SYS_EEPROM_CTRL0_VPDIDX_RAWMSK << SYS_EEPROM_CTRL0_VPDIDX_SHIFT)
#define SYS_EEPROM_CTRL0_VPDIDX(x)                                     \
 (((x) & SYS_EEPROM_CTRL0_VPDIDX_RAWMSK) << SYS_EEPROM_CTRL0_VPDIDX_SHIFT)
#define SYS_EEPROM_CTRL0_MD_SHIFT                                      (6)
#define SYS_EEPROM_CTRL0_MD_RAWMSK                                     (0x3)
#define SYS_EEPROM_CTRL0_MD_MASK                                       \
 (SYS_EEPROM_CTRL0_MD_RAWMSK << SYS_EEPROM_CTRL0_MD_SHIFT)
#define SYS_EEPROM_CTRL0_MD(x)                                         \
 (((x) & SYS_EEPROM_CTRL0_MD_RAWMSK) << SYS_EEPROM_CTRL0_MD_SHIFT)
#define SYS_EEPROM_CTRL0_SYS_AUTOLOAD_SUS                              BIT(5)
#define SYS_EEPROM_CTRL0_SEL                                           BIT(4)
#define SYS_EEPROM_CTRL0_EECS                                          BIT(3)
#define SYS_EEPROM_CTRL0_EESK                                          BIT(2)
#define SYS_EEPROM_CTRL0_EEDI                                          BIT(1)
#define SYS_EEPROM_CTRL0_EEDO                                          BIT(0)

// SYS_EEPROM_CTRL1
#define SYS_EEPROM_CTRL1_VPD_SHIFT                                     (0)
#define SYS_EEPROM_CTRL1_VPD_RAWMSK                                    (0xffffffffL)
#define SYS_EEPROM_CTRL1_VPD_MASK                                      \
 (SYS_EEPROM_CTRL1_VPD_RAWMSK << SYS_EEPROM_CTRL1_VPD_SHIFT)
#define SYS_EEPROM_CTRL1_VPD(x)                                        \
 (((x) & SYS_EEPROM_CTRL1_VPD_RAWMSK) << SYS_EEPROM_CTRL1_VPD_SHIFT)

// SYS_EFUSE_CTRL
#define SYS_EFUSE_CTRL_RWFLAG                                          BIT(31)
#define SYS_EFUSE_CTRL_PGPD_SHIFT                                      (28)
#define SYS_EFUSE_CTRL_PGPD_RAWMSK                                     (0x7)
#define SYS_EFUSE_CTRL_PGPD_MASK                                       \
 (SYS_EFUSE_CTRL_PGPD_RAWMSK << SYS_EFUSE_CTRL_PGPD_SHIFT)
#define SYS_EFUSE_CTRL_PGPD(x)                                         \
 (((x) & SYS_EFUSE_CTRL_PGPD_RAWMSK) << SYS_EFUSE_CTRL_PGPD_SHIFT)
#define SYS_EFUSE_CTRL_RDT_SHIFT                                       (24)
#define SYS_EFUSE_CTRL_RDT_RAWMSK                                      (0xf)
#define SYS_EFUSE_CTRL_RDT_MASK                                        \
 (SYS_EFUSE_CTRL_RDT_RAWMSK << SYS_EFUSE_CTRL_RDT_SHIFT)
#define SYS_EFUSE_CTRL_RDT(x)                                          \
 (((x) & SYS_EFUSE_CTRL_RDT_RAWMSK) << SYS_EFUSE_CTRL_RDT_SHIFT)
#define SYS_EFUSE_CTRL_PGTS_SHIFT                                      (20)
#define SYS_EFUSE_CTRL_PGTS_RAWMSK                                     (0xf)
#define SYS_EFUSE_CTRL_PGTS_MASK                                       \
 (SYS_EFUSE_CTRL_PGTS_RAWMSK << SYS_EFUSE_CTRL_PGTS_SHIFT)
#define SYS_EFUSE_CTRL_PGTS(x)                                         \
 (((x) & SYS_EFUSE_CTRL_PGTS_RAWMSK) << SYS_EFUSE_CTRL_PGTS_SHIFT)
#define SYS_EFUSE_CTRL_PDWN                                            BIT(19)
#define SYS_EFUSE_CTRL_ALDEN                                           BIT(18)
#define SYS_EFUSE_CTRL_ADDR_SHIFT                                      (8)
#define SYS_EFUSE_CTRL_ADDR_RAWMSK                                     (0x3ff)
#define SYS_EFUSE_CTRL_ADDR_MASK                                       \
 (SYS_EFUSE_CTRL_ADDR_RAWMSK << SYS_EFUSE_CTRL_ADDR_SHIFT)
#define SYS_EFUSE_CTRL_ADDR(x)                                         \
 (((x) & SYS_EFUSE_CTRL_ADDR_RAWMSK) << SYS_EFUSE_CTRL_ADDR_SHIFT)
#define SYS_EFUSE_CTRL_DATA_SHIFT                                      (0)
#define SYS_EFUSE_CTRL_DATA_RAWMSK                                     (0xff)
#define SYS_EFUSE_CTRL_DATA_MASK                                       \
 (SYS_EFUSE_CTRL_DATA_RAWMSK << SYS_EFUSE_CTRL_DATA_SHIFT)
#define SYS_EFUSE_CTRL_DATA(x)                                         \
 (((x) & SYS_EFUSE_CTRL_DATA_RAWMSK) << SYS_EFUSE_CTRL_DATA_SHIFT)

// SYS_EFUSE_TEST
#define SYS_EFUSE_TEST_CRES_SEL                                        BIT(26)
#define SYS_EFUSE_TEST_SCAN_START_SHIFT                                (16)
#define SYS_EFUSE_TEST_SCAN_START_RAWMSK                               (0x1ff)
#define SYS_EFUSE_TEST_SCAN_START_MASK                                 \
 (SYS_EFUSE_TEST_SCAN_START_RAWMSK << SYS_EFUSE_TEST_SCAN_START_SHIFT)
#define SYS_EFUSE_TEST_SCAN_START(x)                                   \
 (((x) & SYS_EFUSE_TEST_SCAN_START_RAWMSK) << SYS_EFUSE_TEST_SCAN_START_SHIFT)
#define SYS_EFUSE_TEST_SCAN_END_SHIFT                                  (12)
#define SYS_EFUSE_TEST_SCAN_END_RAWMSK                                 (0xf)
#define SYS_EFUSE_TEST_SCAN_END_MASK                                   \
 (SYS_EFUSE_TEST_SCAN_END_RAWMSK << SYS_EFUSE_TEST_SCAN_END_SHIFT)
#define SYS_EFUSE_TEST_SCAN_END(x)                                     \
 (((x) & SYS_EFUSE_TEST_SCAN_END_RAWMSK) << SYS_EFUSE_TEST_SCAN_END_SHIFT)
#define SYS_EFUSE_TEST_FORCE_PGMEN                                     BIT(11)
#define SYS_EFUSE_TEST_CELL_SEL_SHIFT                                  (8)
#define SYS_EFUSE_TEST_CELL_SEL_RAWMSK                                 (0x3)
#define SYS_EFUSE_TEST_CELL_SEL_MASK                                   \
 (SYS_EFUSE_TEST_CELL_SEL_RAWMSK << SYS_EFUSE_TEST_CELL_SEL_SHIFT)
#define SYS_EFUSE_TEST_CELL_SEL(x)                                     \
 (((x) & SYS_EFUSE_TEST_CELL_SEL_RAWMSK) << SYS_EFUSE_TEST_CELL_SEL_SHIFT)
#define SYS_EFUSE_TEST_TRPT                                            BIT(7)
#define SYS_EFUSE_TEST_SCAN_TTHD_SHIFT                                 (0)
#define SYS_EFUSE_TEST_SCAN_TTHD_RAWMSK                                (0x7f)
#define SYS_EFUSE_TEST_SCAN_TTHD_MASK                                  \
 (SYS_EFUSE_TEST_SCAN_TTHD_RAWMSK << SYS_EFUSE_TEST_SCAN_TTHD_SHIFT)
#define SYS_EFUSE_TEST_SCAN_TTHD(x)                                    \
 (((x) & SYS_EFUSE_TEST_SCAN_TTHD_RAWMSK) << SYS_EFUSE_TEST_SCAN_TTHD_SHIFT)

// SYS_SLP_WAKE_EVENT_MSK0
#define SYS_SLP_WAKE_EVENT_MSK0_GPIO_DSTBY_MSK                         BIT(29)
#define SYS_SLP_WAKE_EVENT_MSK0_A33_MSK                                BIT(28)
#define SYS_SLP_WAKE_EVENT_MSK0_ADC_MSK                                BIT(26)
#define SYS_SLP_WAKE_EVENT_MSK0_I2C_MSK                                BIT(24)
#define SYS_SLP_WAKE_EVENT_MSK0_SPI_MSK                                BIT(22)
#define SYS_SLP_WAKE_EVENT_MSK0_UART_MSK                               BIT(20)
#define SYS_SLP_WAKE_EVENT_MSK0_USB_MSK                                BIT(16)
#define SYS_SLP_WAKE_EVENT_MSK0_SDIO_MSK                               BIT(14)
#define SYS_SLP_WAKE_EVENT_MSK0_NFC_MSK                                BIT(9)
#define SYS_SLP_WAKE_EVENT_MSK0_WLAN_MSK                               BIT(8)
#define SYS_SLP_WAKE_EVENT_MSK0_GPIO_MSK                               BIT(4)
#define SYS_SLP_WAKE_EVENT_MSK0_CHIP_EN_MSK                            BIT(3)
#define SYS_SLP_WAKE_EVENT_MSK0_OVER_CURRENT_MSK                       BIT(2)
#define SYS_SLP_WAKE_EVENT_MSK0_GTIM_MSK                               BIT(1)
#define SYS_SLP_WAKE_EVENT_MSK0_SYSTIM_MSK                             BIT(0)

// SYS_SLP_WAKE_EVENT_MSK1

// SYS_SLP_WAKE_EVENT_STATUS0
#define SYS_SLP_WAKE_EVENT_STATUS0_GPIO_DSTBY_STS                      BIT(29)
#define SYS_SLP_WAKE_EVENT_STATUS0_A33_STS                             BIT(28)
#define SYS_SLP_WAKE_EVENT_STATUS0_ADC_STS                             BIT(26)
#define SYS_SLP_WAKE_EVENT_STATUS0_I2C_STS                             BIT(24)
#define SYS_SLP_WAKE_EVENT_STATUS0_SPI_STS                             BIT(22)
#define SYS_SLP_WAKE_EVENT_STATUS0_UART_STS                            BIT(20)
#define SYS_SLP_WAKE_EVENT_STATUS0_USB_STS                             BIT(16)
#define SYS_SLP_WAKE_EVENT_STATUS0_SDIO_STS                            BIT(14)
#define SYS_SLP_WAKE_EVENT_STATUS0_NFC_STS                             BIT(9)
#define SYS_SLP_WAKE_EVENT_STATUS0_WLAN_STS                            BIT(8)
#define SYS_SLP_WAKE_EVENT_STATUS0_GPIO_STS                            BIT(4)
#define SYS_SLP_WAKE_EVENT_STATUS0_CHIP_EN_STS                         BIT(3)
#define SYS_SLP_WAKE_EVENT_STATUS0_OVER_CURRENT_STS                    BIT(2)
#define SYS_SLP_WAKE_EVENT_STATUS0_GTIM_STS                            BIT(1)
#define SYS_SLP_WAKE_EVENT_STATUS0_SYSTIM_STS                          BIT(0)

// SYS_SLP_WAKE_EVENT_STATUS1

// SYS_SNF_WAKE_EVENT_MSK0
#define SYS_SNF_WAKE_EVENT_MSK0_IMR0_SHIFT                             (1)
#define SYS_SNF_WAKE_EVENT_MSK0_IMR0_RAWMSK                            (0x7fffffffL)
#define SYS_SNF_WAKE_EVENT_MSK0_IMR0_MASK                              \
 (SYS_SNF_WAKE_EVENT_MSK0_IMR0_RAWMSK << SYS_SNF_WAKE_EVENT_MSK0_IMR0_SHIFT)
#define SYS_SNF_WAKE_EVENT_MSK0_IMR0(x)                                \
 (((x) & SYS_SNF_WAKE_EVENT_MSK0_IMR0_RAWMSK) << SYS_SNF_WAKE_EVENT_MSK0_IMR0_SHIFT)
#define SYS_SNF_WAKE_EVENT_MSK0_SYSON_SNFEVT_ADC_MSK                   BIT(0)

// SYS_SNF_WAKE_EVENT_STATUS
#define SYS_SNF_WAKE_EVENT_STATUS_ISR0_SHIFT                           (1)
#define SYS_SNF_WAKE_EVENT_STATUS_ISR0_RAWMSK                          (0x7fffffffL)
#define SYS_SNF_WAKE_EVENT_STATUS_ISR0_MASK                            \
 (SYS_SNF_WAKE_EVENT_STATUS_ISR0_RAWMSK << SYS_SNF_WAKE_EVENT_STATUS_ISR0_SHIFT)
#define SYS_SNF_WAKE_EVENT_STATUS_ISR0(x)                              \
 (((x) & SYS_SNF_WAKE_EVENT_STATUS_ISR0_RAWMSK) << SYS_SNF_WAKE_EVENT_STATUS_ISR0_SHIFT)
#define SYS_SNF_WAKE_EVENT_STATUS_SYSON_SNFEVT_ADC_STS                 BIT(0)

// SYS_PWRMGT_CTRL
#define SYS_PWRMGT_CTRL_REGU_DSLP                                      BIT(7)
#define SYS_PWRMGT_CTRL_CMD_SLP                                        BIT(2)
#define SYS_PWRMGT_CTRL_CMD_DSTBY                                      BIT(1)
#define SYS_PWRMGT_CTRL_CMD_DSLP                                       BIT(0)

// SYS_PWRMGT_OPTION
#define SYS_PWRMGT_OPTION_NORM_SYSCLK_SEL                              BIT(30)
#define SYS_PWRMGT_OPTION_NORM_SYSPLL_EN                               BIT(29)
#define SYS_PWRMGT_OPTION_NORM_XTAL_EN                                 BIT(28)
#define SYS_PWRMGT_OPTION_NORM_EN_SOC                                  BIT(27)
#define SYS_PWRMGT_OPTION_NORM_EN_PWM                                  BIT(26)
#define SYS_PWRMGT_OPTION_NORM_EN_SWR                                  BIT(25)
#define SYS_PWRMGT_OPTION_NORM_LPLDO_SEL                               BIT(24)
#define SYS_PWRMGT_OPTION_SNZ_SYSCLK_SEL                               BIT(22)
#define SYS_PWRMGT_OPTION_SNZ_SYSPLL_EN                                BIT(21)
#define SYS_PWRMGT_OPTION_SNZ_XTAL_EN                                  BIT(20)
#define SYS_PWRMGT_OPTION_SNZ_EN_SOC                                   BIT(19)
#define SYS_PWRMGT_OPTION_SNZ_EN_PWM                                   BIT(18)
#define SYS_PWRMGT_OPTION_SNZ_EN_SWR                                   BIT(17)
#define SYS_PWRMGT_OPTION_SNZ_LPLDO_SEL                                BIT(16)
#define SYS_PWRMGT_OPTION_SLP_SYSCLK_SEL                               BIT(14)
#define SYS_PWRMGT_OPTION_SLP_SYSPLL_EN                                BIT(13)
#define SYS_PWRMGT_OPTION_SLP_XTAL_EN                                  BIT(12)
#define SYS_PWRMGT_OPTION_SLP_EN_SOC                                   BIT(11)
#define SYS_PWRMGT_OPTION_SLP_EN_PWM                                   BIT(10)
#define SYS_PWRMGT_OPTION_SLP_EN_SWR                                   BIT(9)
#define SYS_PWRMGT_OPTION_SLP_LPLDO_SEL                                BIT(8)
#define SYS_PWRMGT_OPTION_DSTBY_SYSCLK_SEL                             BIT(6)
#define SYS_PWRMGT_OPTION_DSTBY_SYSPLL_EN                              BIT(5)
#define SYS_PWRMGT_OPTION_DSTBY_XTAL_EN                                BIT(4)
#define SYS_PWRMGT_OPTION_DSTBY_EN_SOC                                 BIT(3)
#define SYS_PWRMGT_OPTION_DSTBY_EN_PWM                                 BIT(2)
#define SYS_PWRMGT_OPTION_DSTBY_EN_SWR                                 BIT(1)
#define SYS_PWRMGT_OPTION_DSTBY_LPLDO_SEL                              BIT(0)

// SYS_PWRMGT_OPTION_EXT
#define SYS_PWRMGT_OPTION_EXT_SLP_ANACK_SEL                            BIT(2)
#define SYS_PWRMGT_OPTION_EXT_SLP_ANACK_EN                             BIT(1)
#define SYS_PWRMGT_OPTION_EXT_SLP_SWR_ADJ                              BIT(0)

// SYS_DSLP_WEVENT
#define SYS_DSLP_WEVENT_GPIO                                           BIT(2)
#define SYS_DSLP_WEVENT_NFC                                            BIT(1)
#define SYS_DSLP_WEVENT_WTIMER33                                       BIT(0)

// SYS_PERI_MONITOR
#define SYS_PERI_MONITOR_ISO33_NFC                                     BIT(0)

// SYS_SYSTEM_CFG0
#define SYS_SYSTEM_CFG0_BD_PKG_SEL                                     BIT(31)
#define SYS_SYSTEM_CFG0_VENDOR_ID_SHIFT                                (8)
#define SYS_SYSTEM_CFG0_VENDOR_ID_RAWMSK                               (0xf)
#define SYS_SYSTEM_CFG0_VENDOR_ID_MASK                                 \
 (SYS_SYSTEM_CFG0_VENDOR_ID_RAWMSK << SYS_SYSTEM_CFG0_VENDOR_ID_SHIFT)
#define SYS_SYSTEM_CFG0_VENDOR_ID(x)                                   \
 (((x) & SYS_SYSTEM_CFG0_VENDOR_ID_RAWMSK) << SYS_SYSTEM_CFG0_VENDOR_ID_SHIFT)
#define SYS_SYSTEM_CFG0_CHIP_VER_SHIFT                                 (4)
#define SYS_SYSTEM_CFG0_CHIP_VER_RAWMSK                                (0xf)
#define SYS_SYSTEM_CFG0_CHIP_VER_MASK                                  \
 (SYS_SYSTEM_CFG0_CHIP_VER_RAWMSK << SYS_SYSTEM_CFG0_CHIP_VER_SHIFT)
#define SYS_SYSTEM_CFG0_CHIP_VER(x)                                    \
 (((x) & SYS_SYSTEM_CFG0_CHIP_VER_RAWMSK) << SYS_SYSTEM_CFG0_CHIP_VER_SHIFT)
#define SYS_SYSTEM_CFG0_RF_RL_ID_SHIFT                                 (0)
#define SYS_SYSTEM_CFG0_RF_RL_ID_RAWMSK                                (0xf)
#define SYS_SYSTEM_CFG0_RF_RL_ID_MASK                                  \
 (SYS_SYSTEM_CFG0_RF_RL_ID_RAWMSK << SYS_SYSTEM_CFG0_RF_RL_ID_SHIFT)
#define SYS_SYSTEM_CFG0_RF_RL_ID(x)                                    \
 (((x) & SYS_SYSTEM_CFG0_RF_RL_ID_RAWMSK) << SYS_SYSTEM_CFG0_RF_RL_ID_SHIFT)

// SYS_SYSTEM_CFG1
#define SYS_SYSTEM_CFG1_TRP_ICFG_SHIFT                                 (28)
#define SYS_SYSTEM_CFG1_TRP_ICFG_RAWMSK                                (0xf)
#define SYS_SYSTEM_CFG1_TRP_ICFG_MASK                                  \
 (SYS_SYSTEM_CFG1_TRP_ICFG_RAWMSK << SYS_SYSTEM_CFG1_TRP_ICFG_SHIFT)
#define SYS_SYSTEM_CFG1_TRP_ICFG(x)                                    \
 (((x) & SYS_SYSTEM_CFG1_TRP_ICFG_RAWMSK) << SYS_SYSTEM_CFG1_TRP_ICFG_SHIFT)
#define SYS_SYSTEM_CFG1_TRP_BOOT_SEL_                                  BIT(27)
#define SYS_SYSTEM_CFG1_TRP_SPSLDO_SEL                                 BIT(26)
#define SYS_SYSTEM_CFG1_V15_VLD                                        BIT(16)
#define SYS_SYSTEM_CFG1_SYS_SYSPLL_CLK_RDY                             BIT(9)
#define SYS_SYSTEM_CFG1_SYS_XCLK_VLD                                   BIT(8)
#define SYS_SYSTEM_CFG1_ALDN_STS                                       BIT(0)

// =================================================================================================
// SYS_PERI_ON : 0x0200
//
// SYS_PEON_PWR_CTRL
#define SYS_PEON_PWR_CTRL_UAHV_EN                                      BIT(2)
#define SYS_PEON_PWR_CTRL_UALV_EN                                      BIT(1)
#define SYS_PEON_PWR_CTRL_USBD_EN                                      BIT(0)

// SYS_PEON_ISO_CTRL
#define SYS_PEON_ISO_CTRL_OSC32K_EN                                    BIT(4)
#define SYS_PEON_ISO_CTRL_USBA_EN                                      BIT(1)
#define SYS_PEON_ISO_CTRL_USBD_EN                                      BIT(0)

// SYS_SOC_FUNC_EN
#define SYS_SOC_FUNC_EN_SECURITY_ENGINE_EN                             BIT(20)
#define SYS_SOC_FUNC_EN_GTIMER_EN                                      BIT(16)
#define SYS_SOC_FUNC_EN_GDMA1_EN                                       BIT(14)
#define SYS_SOC_FUNC_EN_GDMA0_EN                                       BIT(13)
#define SYS_SOC_FUNC_EN_LOG_UART_EN                                    BIT(12)
#define SYS_SOC_FUNC_EN_CPU_EN                                         BIT(8)
#define SYS_SOC_FUNC_EN_MEM_CTRL_EN                                    BIT(6)
#define SYS_SOC_FUNC_EN_FLASH_EN                                       BIT(4)
#define SYS_SOC_FUNC_EN_LXBUS_EN                                       BIT(2)
#define SYS_SOC_FUNC_EN_OCP_EN                                         BIT(1)
#define SYS_SOC_FUNC_EN_FUN_EN                                         BIT(0)

// SYS_SOC_HCI_COM_FUNC_EN
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_WL_MACON_EN                        BIT(16)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_SM_SEL                             BIT(13)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_MII_EN                             BIT(12)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_OTG_RST_MUX                        BIT(5)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_OTG_EN                             BIT(4)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_SDIOD_ON_RST_MUX                   BIT(3)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_SDIOH_EN                           BIT(2)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_SDIOD_OFF_EN                       BIT(1)
#define SYS_SOC_HCI_COM_FUNC_EN_HCI_SDIOD_ON_EN                        BIT(0)

// SYS_SOC_PERI_FUNC0_EN
#define SYS_SOC_PERI_FUNC0_EN_PCM1_EN                                  BIT(29)
#define SYS_SOC_PERI_FUNC0_EN_PCM0_EN                                  BIT(28)
#define SYS_SOC_PERI_FUNC0_EN_I2S1_EN                                  BIT(25)
#define SYS_SOC_PERI_FUNC0_EN_I2S0_EN                                  BIT(24)
#define SYS_SOC_PERI_FUNC0_EN_I2C3_EN                                  BIT(19)
#define SYS_SOC_PERI_FUNC0_EN_I2C2_EN                                  BIT(18)
#define SYS_SOC_PERI_FUNC0_EN_I2C1_EN                                  BIT(17)
#define SYS_SOC_PERI_FUNC0_EN_I2C0_EN                                  BIT(16)
#define SYS_SOC_PERI_FUNC0_EN_SPI2_EN                                  BIT(10)
#define SYS_SOC_PERI_FUNC0_EN_SPI1_EN                                  BIT(9)
#define SYS_SOC_PERI_FUNC0_EN_SPI0_EN                                  BIT(8)
#define SYS_SOC_PERI_FUNC0_EN_UART2_EN                                 BIT(2)
#define SYS_SOC_PERI_FUNC0_EN_UART1_EN                                 BIT(1)
#define SYS_SOC_PERI_FUNC0_EN_UART0_EN                                 BIT(0)

// SYS_SOC_PERI_FUNC1_EN
#define SYS_SOC_PERI_FUNC1_EN_GPIO_EN                                  BIT(8)
#define SYS_SOC_PERI_FUNC1_EN_DAC1_EN                                  BIT(5)
#define SYS_SOC_PERI_FUNC1_EN_DAC0_EN                                  BIT(4)
#define SYS_SOC_PERI_FUNC1_EN_ADC0_EN                                  BIT(0)

// SYS_SOC_PERI_BD_FUNC0_EN
#define SYS_SOC_PERI_BD_FUNC0_EN_UART2_BD_EN                           BIT(2)
#define SYS_SOC_PERI_BD_FUNC0_EN_UART1_BD_EN                           BIT(1)
#define SYS_SOC_PERI_BD_FUNC0_EN_UART0_BD_EN                           BIT(0)

// SYS_PESOC_CLK_CTRL
#define SYS_PESOC_CLK_CTRL_SLPCK_BTCMD_EN                              BIT(29)
#define SYS_PESOC_CLK_CTRL_ACTCK_BTCMD_EN                              BIT(28)
#define SYS_PESOC_CLK_CTRL_SLPCK_GPIO_EN                               BIT(25)
#define SYS_PESOC_CLK_CTRL_ACTCK_GPIO_EN                               BIT(24)
#define SYS_PESOC_CLK_CTRL_SLPCK_GDMA1_EN                              BIT(19)
#define SYS_PESOC_CLK_CTRL_ACTCK_GDMA1_EN                              BIT(18)
#define SYS_PESOC_CLK_CTRL_SLPCK_GDMA0_EN                              BIT(17)
#define SYS_PESOC_CLK_CTRL_ACTCK_GDMA0_EN                              BIT(16)
#define SYS_PESOC_CLK_CTRL_SLPCK_TIMER_EN                              BIT(15)
#define SYS_PESOC_CLK_CTRL_ACTCK_TIMER_EN                              BIT(14)
#define SYS_PESOC_CLK_CTRL_SLPCK_LOG_UART_EN                           BIT(13)
#define SYS_PESOC_CLK_CTRL_ACTCK_LOG_UART_EN                           BIT(12)
#define SYS_PESOC_CLK_CTRL_SLPCK_SDR_EN                                BIT(11)
#define SYS_PESOC_CLK_CTRL_ACTCK_SDR_EN                                BIT(10)
#define SYS_PESOC_CLK_CTRL_SLPCK_FLASH_EN                              BIT(9)
#define SYS_PESOC_CLK_CTRL_ACTCK_FLASH_EN                              BIT(8)
#define SYS_PESOC_CLK_CTRL_SLPCK_VENDOR_REG_EN                         BIT(7)
#define SYS_PESOC_CLK_CTRL_ACTCK_VENDOR_REG_EN                         BIT(6)
#define SYS_PESOC_CLK_CTRL_SLPCK_TRACE_EN                              BIT(5)
#define SYS_PESOC_CLK_CTRL_ACTCK_TRACE_EN                              BIT(4)
#define SYS_PESOC_CLK_CTRL_CKE_PLFM                                    BIT(2)
#define SYS_PESOC_CLK_CTRL_CKE_OCP                                     BIT(0)

// SYS_PESOC_PERI_CLK_CTRL0
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_SPI2_EN                         BIT(21)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_SPI2_EN                         BIT(20)
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_SPI1_EN                         BIT(19)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_SPI1_EN                         BIT(18)
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_SPI0_EN                         BIT(17)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_SPI0_EN                         BIT(16)
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_UART2_EN                        BIT(5)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_UART2_EN                        BIT(4)
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_UART1_EN                        BIT(3)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_UART1_EN                        BIT(2)
#define SYS_PESOC_PERI_CLK_CTRL0_SLPCK_UART0_EN                        BIT(1)
#define SYS_PESOC_PERI_CLK_CTRL0_ACTCK_UART0_EN                        BIT(0)

// SYS_PESOC_PERI_CLK_CTRL1
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_DAC_EN                          BIT(29)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_DAC_EN                          BIT(28)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_ADC_EN                          BIT(25)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_ADC_EN                          BIT(24)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_PCM_EN                          BIT(21)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_PCM_EN                          BIT(20)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_I2S_EN                          BIT(17)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_I2S_EN                          BIT(16)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_I2C3_EN                         BIT(7)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_I2C3_EN                         BIT(6)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_I2C2_EN                         BIT(5)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_I2C2_EN                         BIT(4)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_I2C1_EN                         BIT(3)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_I2C1_EN                         BIT(2)
#define SYS_PESOC_PERI_CLK_CTRL1_SLPCK_I2C0_EN                         BIT(1)
#define SYS_PESOC_PERI_CLK_CTRL1_ACTCK_I2C0_EN                         BIT(0)

// SYS_PESOC_HCI_CLK_CTRL0
#define SYS_PESOC_HCI_CLK_CTRL0_SLPCK_MII_MPHY_EN                      BIT(25)
#define SYS_PESOC_HCI_CLK_CTRL0_ACTCK_MII_MPHY_EN                      BIT(24)
#define SYS_PESOC_HCI_CLK_CTRL0_SLPCK_OTG_EN                           BIT(5)
#define SYS_PESOC_HCI_CLK_CTRL0_ACTCK_OTG_EN                           BIT(4)
#define SYS_PESOC_HCI_CLK_CTRL0_SLPCK_SDIO_HST_EN                      BIT(3)
#define SYS_PESOC_HCI_CLK_CTRL0_ACTCK_SDIO_HST_EN                      BIT(2)
#define SYS_PESOC_HCI_CLK_CTRL0_SLPCK_SDIO_DEV_EN                      BIT(1)
#define SYS_PESOC_HCI_CLK_CTRL0_ACTCK_SDIO_DEV_EN                      BIT(0)

// SYS_PESOC_COM_CLK_CTRL1
#define SYS_PESOC_COM_CLK_CTRL1_NFC_CAL_EN                             BIT(18)
#define SYS_PESOC_COM_CLK_CTRL1_SLPCK_NFC_EN                           BIT(17)
#define SYS_PESOC_COM_CLK_CTRL1_ACTCK_NFC_EN                           BIT(16)
#define SYS_PESOC_COM_CLK_CTRL1_SLPCK_SECURITY_ENG_EN                  BIT(5)
#define SYS_PESOC_COM_CLK_CTRL1_ACTCK_SECURITY_ENG_EN                  BIT(4)
#define SYS_PESOC_COM_CLK_CTRL1_SLPCK_WL_EN                            BIT(1)
#define SYS_PESOC_COM_CLK_CTRL1_ACTCK_WL_EN                            BIT(0)

// SYS_PESOC_CLK_SEL
#define SYS_PESOC_CLK_SEL_SPI1_SCLK_SEL                                BIT(18)
#define SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_SHIFT                          (16)
#define SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_RAWMSK                         (0x3)
#define SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_MASK                           \
 (SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_RAWMSK << SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_PERI_SCLK_SEL(x)                             \
 (((x) & SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_RAWMSK) << SYS_PESOC_CLK_SEL_PERI_SCLK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_SDR_CK_SEL_SHIFT                             (10)
#define SYS_PESOC_CLK_SEL_SDR_CK_SEL_RAWMSK                            (0x3)
#define SYS_PESOC_CLK_SEL_SDR_CK_SEL_MASK                              \
 (SYS_PESOC_CLK_SEL_SDR_CK_SEL_RAWMSK << SYS_PESOC_CLK_SEL_SDR_CK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_SDR_CK_SEL(x)                                \
 (((x) & SYS_PESOC_CLK_SEL_SDR_CK_SEL_RAWMSK) << SYS_PESOC_CLK_SEL_SDR_CK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_FLASH_CK_SEL_SHIFT                           (8)
#define SYS_PESOC_CLK_SEL_FLASH_CK_SEL_RAWMSK                          (0x3)
#define SYS_PESOC_CLK_SEL_FLASH_CK_SEL_MASK                            \
 (SYS_PESOC_CLK_SEL_FLASH_CK_SEL_RAWMSK << SYS_PESOC_CLK_SEL_FLASH_CK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_FLASH_CK_SEL(x)                              \
 (((x) & SYS_PESOC_CLK_SEL_FLASH_CK_SEL_RAWMSK) << SYS_PESOC_CLK_SEL_FLASH_CK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_TRACE_CK_SEL_SHIFT                           (4)
#define SYS_PESOC_CLK_SEL_TRACE_CK_SEL_RAWMSK                          (0x3)
#define SYS_PESOC_CLK_SEL_TRACE_CK_SEL_MASK                            \
 (SYS_PESOC_CLK_SEL_TRACE_CK_SEL_RAWMSK << SYS_PESOC_CLK_SEL_TRACE_CK_SEL_SHIFT)
#define SYS_PESOC_CLK_SEL_TRACE_CK_SEL(x)                              \
 (((x) & SYS_PESOC_CLK_SEL_TRACE_CK_SEL_RAWMSK) << SYS_PESOC_CLK_SEL_TRACE_CK_SEL_SHIFT)

// SYS_SYS_ANACK_CAL_CTRL
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_CMD                           BIT(15)
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_SEL                           BIT(14)
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_SHIFT                     (0)
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_RAWMSK                    (0x3fff)
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_MASK                      \
 (SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_RAWMSK << SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_SHIFT)
#define SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT(x)                        \
 (((x) & SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_RAWMSK) << SYS_SYS_ANACK_CAL_CTRL_ANACK_CAL_RPT_SHIFT)

// OSC32K_CTRL
#define OSC32K_CTRL_BIAS_CURRENT_SHIFT                                 (16)
#define OSC32K_CTRL_BIAS_CURRENT_RAWMSK                                (0xffff)
#define OSC32K_CTRL_BIAS_CURRENT_MASK                                  \
 (OSC32K_CTRL_BIAS_CURRENT_RAWMSK << OSC32K_CTRL_BIAS_CURRENT_SHIFT)
#define OSC32K_CTRL_BIAS_CURRENT(x)                                    \
 (((x) & OSC32K_CTRL_BIAS_CURRENT_RAWMSK) << OSC32K_CTRL_BIAS_CURRENT_SHIFT)
#define OSC32K_CTRL_RESISTOR_COM_SHIFT                                 (2)
#define OSC32K_CTRL_RESISTOR_COM_RAWMSK                                (0x3)
#define OSC32K_CTRL_RESISTOR_COM_MASK                                  \
 (OSC32K_CTRL_RESISTOR_COM_RAWMSK << OSC32K_CTRL_RESISTOR_COM_SHIFT)
#define OSC32K_CTRL_RESISTOR_COM(x)                                    \
 (((x) & OSC32K_CTRL_RESISTOR_COM_RAWMSK) << OSC32K_CTRL_RESISTOR_COM_SHIFT)
#define OSC32K_CTRL_DBG_SEL                                            BIT(1)
#define OSC32K_CTRL_POW_CKGEN_EN                                       BIT(0)

// OSC32K_REG_CTRL0
#define OSC32K_REG_CTRL0_INDIRT_CMD                                    BIT(23)
#define OSC32K_REG_CTRL0_INDIRT_ADDR_SHIFT                             (16)
#define OSC32K_REG_CTRL0_INDIRT_ADDR_RAWMSK                            (0x3f)
#define OSC32K_REG_CTRL0_INDIRT_ADDR_MASK                              \
 (OSC32K_REG_CTRL0_INDIRT_ADDR_RAWMSK << OSC32K_REG_CTRL0_INDIRT_ADDR_SHIFT)
#define OSC32K_REG_CTRL0_INDIRT_ADDR(x)                                \
 (((x) & OSC32K_REG_CTRL0_INDIRT_ADDR_RAWMSK) << OSC32K_REG_CTRL0_INDIRT_ADDR_SHIFT)
#define OSC32K_REG_CTRL0_INDIRT_WDATA_SHIFT                            (0)
#define OSC32K_REG_CTRL0_INDIRT_WDATA_RAWMSK                           (0xffff)
#define OSC32K_REG_CTRL0_INDIRT_WDATA_MASK                             \
 (OSC32K_REG_CTRL0_INDIRT_WDATA_RAWMSK << OSC32K_REG_CTRL0_INDIRT_WDATA_SHIFT)
#define OSC32K_REG_CTRL0_INDIRT_WDATA(x)                               \
 (((x) & OSC32K_REG_CTRL0_INDIRT_WDATA_RAWMSK) << OSC32K_REG_CTRL0_INDIRT_WDATA_SHIFT)

// OSC32K_REG_CTRL1
#define OSC32K_REG_CTRL1_INDIRT_RDATA_SHIFT                            (0)
#define OSC32K_REG_CTRL1_INDIRT_RDATA_RAWMSK                           (0xffff)
#define OSC32K_REG_CTRL1_INDIRT_RDATA_MASK                             \
 (OSC32K_REG_CTRL1_INDIRT_RDATA_RAWMSK << OSC32K_REG_CTRL1_INDIRT_RDATA_SHIFT)
#define OSC32K_REG_CTRL1_INDIRT_RDATA(x)                               \
 (((x) & OSC32K_REG_CTRL1_INDIRT_RDATA_RAWMSK) << OSC32K_REG_CTRL1_INDIRT_RDATA_SHIFT)

// SYS_THERMAL_METER_CTRL
#define SYS_THERMAL_METER_CTRL_VALUE_SHIFT                             (24)
#define SYS_THERMAL_METER_CTRL_VALUE_RAWMSK                            (0x3f)
#define SYS_THERMAL_METER_CTRL_VALUE_MASK                              \
 (SYS_THERMAL_METER_CTRL_VALUE_RAWMSK << SYS_THERMAL_METER_CTRL_VALUE_SHIFT)
#define SYS_THERMAL_METER_CTRL_VALUE(x)                                \
 (((x) & SYS_THERMAL_METER_CTRL_VALUE_RAWMSK) << SYS_THERMAL_METER_CTRL_VALUE_SHIFT)
#define SYS_THERMAL_METER_CTRL_DELTA_SHIFT                             (16)
#define SYS_THERMAL_METER_CTRL_DELTA_RAWMSK                            (0x3f)
#define SYS_THERMAL_METER_CTRL_DELTA_MASK                              \
 (SYS_THERMAL_METER_CTRL_DELTA_RAWMSK << SYS_THERMAL_METER_CTRL_DELTA_SHIFT)
#define SYS_THERMAL_METER_CTRL_DELTA(x)                                \
 (((x) & SYS_THERMAL_METER_CTRL_DELTA_RAWMSK) << SYS_THERMAL_METER_CTRL_DELTA_SHIFT)

// SYS_UART_MUX_CTRL
#define SYS_UART_MUX_CTRL_UART2_PIN_SEL_SHIFT                          (9)
#define SYS_UART_MUX_CTRL_UART2_PIN_SEL_RAWMSK                         (0x7)
#define SYS_UART_MUX_CTRL_UART2_PIN_SEL_MASK                           \
 (SYS_UART_MUX_CTRL_UART2_PIN_SEL_RAWMSK << SYS_UART_MUX_CTRL_UART2_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART2_PIN_SEL(x)                             \
 (((x) & SYS_UART_MUX_CTRL_UART2_PIN_SEL_RAWMSK) << SYS_UART_MUX_CTRL_UART2_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART2_PIN_EN                                 BIT(8)
#define SYS_UART_MUX_CTRL_UART1_PIN_SEL_SHIFT                          (5)
#define SYS_UART_MUX_CTRL_UART1_PIN_SEL_RAWMSK                         (0x7)
#define SYS_UART_MUX_CTRL_UART1_PIN_SEL_MASK                           \
 (SYS_UART_MUX_CTRL_UART1_PIN_SEL_RAWMSK << SYS_UART_MUX_CTRL_UART1_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART1_PIN_SEL(x)                             \
 (((x) & SYS_UART_MUX_CTRL_UART1_PIN_SEL_RAWMSK) << SYS_UART_MUX_CTRL_UART1_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART1_PIN_EN                                 BIT(4)
#define SYS_UART_MUX_CTRL_UART0_PIN_SEL_SHIFT                          (1)
#define SYS_UART_MUX_CTRL_UART0_PIN_SEL_RAWMSK                         (0x7)
#define SYS_UART_MUX_CTRL_UART0_PIN_SEL_MASK                           \
 (SYS_UART_MUX_CTRL_UART0_PIN_SEL_RAWMSK << SYS_UART_MUX_CTRL_UART0_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART0_PIN_SEL(x)                             \
 (((x) & SYS_UART_MUX_CTRL_UART0_PIN_SEL_RAWMSK) << SYS_UART_MUX_CTRL_UART0_PIN_SEL_SHIFT)
#define SYS_UART_MUX_CTRL_UART0_PIN_EN                                 BIT(0)

// SYS_SPI_MUX_CTRL
#define SYS_SPI_MUX_CTRL_SPI0_MULTI_CS_EN                              BIT(28)
#define SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_SHIFT                            (9)
#define SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_RAWMSK                           (0x7)
#define SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_MASK                             \
 (SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_RAWMSK << SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI2_PIN_SEL(x)                               \
 (((x) & SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_RAWMSK) << SYS_SPI_MUX_CTRL_SPI2_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI2_PIN_EN                                   BIT(8)
#define SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_SHIFT                            (5)
#define SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_RAWMSK                           (0x7)
#define SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_MASK                             \
 (SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_RAWMSK << SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI1_PIN_SEL(x)                               \
 (((x) & SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_RAWMSK) << SYS_SPI_MUX_CTRL_SPI1_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI1_PIN_EN                                   BIT(4)
#define SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_SHIFT                            (1)
#define SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_RAWMSK                           (0x7)
#define SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_MASK                             \
 (SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_RAWMSK << SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI0_PIN_SEL(x)                               \
 (((x) & SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_RAWMSK) << SYS_SPI_MUX_CTRL_SPI0_PIN_SEL_SHIFT)
#define SYS_SPI_MUX_CTRL_SPI0_PIN_EN                                   BIT(0)

// I2C_MUX_CTRL
#define I2C_MUX_CTRL_I2C3_PIN_SEL_SHIFT                                (13)
#define I2C_MUX_CTRL_I2C3_PIN_SEL_RAWMSK                               (0x7)
#define I2C_MUX_CTRL_I2C3_PIN_SEL_MASK                                 \
 (I2C_MUX_CTRL_I2C3_PIN_SEL_RAWMSK << I2C_MUX_CTRL_I2C3_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C3_PIN_SEL(x)                                   \
 (((x) & I2C_MUX_CTRL_I2C3_PIN_SEL_RAWMSK) << I2C_MUX_CTRL_I2C3_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C3_PIN_EN                                       BIT(12)
#define I2C_MUX_CTRL_I2C2_PIN_SEL_SHIFT                                (9)
#define I2C_MUX_CTRL_I2C2_PIN_SEL_RAWMSK                               (0x7)
#define I2C_MUX_CTRL_I2C2_PIN_SEL_MASK                                 \
 (I2C_MUX_CTRL_I2C2_PIN_SEL_RAWMSK << I2C_MUX_CTRL_I2C2_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C2_PIN_SEL(x)                                   \
 (((x) & I2C_MUX_CTRL_I2C2_PIN_SEL_RAWMSK) << I2C_MUX_CTRL_I2C2_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C2_PIN_EN                                       BIT(8)
#define I2C_MUX_CTRL_I2C1_PIN_SEL_SHIFT                                (5)
#define I2C_MUX_CTRL_I2C1_PIN_SEL_RAWMSK                               (0x7)
#define I2C_MUX_CTRL_I2C1_PIN_SEL_MASK                                 \
 (I2C_MUX_CTRL_I2C1_PIN_SEL_RAWMSK << I2C_MUX_CTRL_I2C1_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C1_PIN_SEL(x)                                   \
 (((x) & I2C_MUX_CTRL_I2C1_PIN_SEL_RAWMSK) << I2C_MUX_CTRL_I2C1_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C1_PIN_EN                                       BIT(4)
#define I2C_MUX_CTRL_I2C0_PIN_SEL_SHIFT                                (1)
#define I2C_MUX_CTRL_I2C0_PIN_SEL_RAWMSK                               (0x7)
#define I2C_MUX_CTRL_I2C0_PIN_SEL_MASK                                 \
 (I2C_MUX_CTRL_I2C0_PIN_SEL_RAWMSK << I2C_MUX_CTRL_I2C0_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C0_PIN_SEL(x)                                   \
 (((x) & I2C_MUX_CTRL_I2C0_PIN_SEL_RAWMSK) << I2C_MUX_CTRL_I2C0_PIN_SEL_SHIFT)
#define I2C_MUX_CTRL_I2C0_PIN_EN                                       BIT(0)

// I2S_PCM_MUX_CTRL
#define I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_SHIFT                            (21)
#define I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_RAWMSK                           (0x7)
#define I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_MASK                             \
 (I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_RAWMSK << I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_PCM1_PIN_SEL(x)                               \
 (((x) & I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_RAWMSK) << I2S_PCM_MUX_CTRL_PCM1_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_PCM1_PIN_EN                                   BIT(20)
#define I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_SHIFT                            (17)
#define I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_RAWMSK                           (0x7)
#define I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_MASK                             \
 (I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_RAWMSK << I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_PCM0_PIN_SEL(x)                               \
 (((x) & I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_RAWMSK) << I2S_PCM_MUX_CTRL_PCM0_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_PCM0_PIN_EN                                   BIT(16)
#define I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_SHIFT                            (6)
#define I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_RAWMSK                           (0x3)
#define I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_MASK                             \
 (I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_RAWMSK << I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_I2S1_PIN_SEL(x)                               \
 (((x) & I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_RAWMSK) << I2S_PCM_MUX_CTRL_I2S1_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_I2S1_MCK_EN                                   BIT(5)
#define I2S_PCM_MUX_CTRL_I2S1_PIN_EN                                   BIT(4)
#define I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_SHIFT                            (2)
#define I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_RAWMSK                           (0x3)
#define I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_MASK                             \
 (I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_RAWMSK << I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_I2S0_PIN_SEL(x)                               \
 (((x) & I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_RAWMSK) << I2S_PCM_MUX_CTRL_I2S0_PIN_SEL_SHIFT)
#define I2S_PCM_MUX_CTRL_I2S0_MCK_EN                                   BIT(1)
#define I2S_PCM_MUX_CTRL_I2S0_PIN_EN                                   BIT(0)

// SYS_HCI_PINMUX_CTRL
#define SYS_HCI_PINMUX_CTRL_MII_PIN_EN                                 BIT(24)
#define SYS_HCI_PINMUX_CTRL_SDIOH_PIN_EN                               BIT(1)
#define SYS_HCI_PINMUX_CTRL_SDIOD_PIN_EN                               BIT(0)

// SYS_WLAN_NFC_PINMUX_CTRL
#define SYS_WLAN_NFC_PINMUX_CTRL_NFC_PIN_EN                            BIT(16)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_BTCMD_PIN_EN                     BIT(13)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_BTCOEX_PIN_EN                    BIT(12)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_ANT1_PIN_EN                      BIT(9)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_ANT0_PIN_EN                      BIT(8)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_SHIFT                (1)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_RAWMSK               (0x3)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_MASK                 \
 (SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_RAWMSK << SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_SHIFT)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL(x)                   \
 (((x) & SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_RAWMSK) << SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_SEL_SHIFT)
#define SYS_WLAN_NFC_PINMUX_CTRL_WLAN_LED_PIN_EN                       BIT(0)

// SYS_PWM_ETE_PINMUX_CTRL
#define SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_SHIFT                     (29)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE3_PIN_EN                            BIT(28)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_SHIFT                     (25)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE2_PIN_EN                            BIT(24)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_SHIFT                     (21)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE1_PIN_EN                            BIT(20)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_SHIFT                     (17)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_ETE0_PIN_EN                            BIT(16)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_SHIFT                     (13)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM3_PIN_EN                            BIT(12)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_SHIFT                     (9)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM2_PIN_EN                            BIT(8)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_SHIFT                     (5)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM1_PIN_EN                            BIT(4)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_SHIFT                     (1)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_RAWMSK                    (0x3)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_MASK                      \
 (SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_RAWMSK << SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL(x)                        \
 (((x) & SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_RAWMSK) << SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_SEL_SHIFT)
#define SYS_PWM_ETE_PINMUX_CTRL_PWM0_PIN_EN                            BIT(0)

// SYS_CPU_PERIPHERAL_CTRL
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_SHIFT                 (22)
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_RAWMSK                (0x3)
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_MASK                  \
 (SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_RAWMSK << SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_SHIFT)
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL(x)                    \
 (((x) & SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_RAWMSK) << SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_SEL_SHIFT)
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_IR_EN                         BIT(21)
#define SYS_CPU_PERIPHERAL_CTRL_LOG_UART_PIN_EN                        BIT(20)
#define SYS_CPU_PERIPHERAL_CTRL_TRACE_PIN_EN                           BIT(17)
#define SYS_CPU_PERIPHERAL_CTRL_SDR_PIN_EN                             BIT(4)
#define SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_SHIFT                (1)
#define SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_RAWMSK               (0x3)
#define SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_MASK                 \
 (SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_RAWMSK << SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_SHIFT)
#define SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL(x)                   \
 (((x) & SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_RAWMSK) << SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_SEL_SHIFT)
#define SYS_CPU_PERIPHERAL_CTRL_SPI_FLASH_PIN_EN                       BIT(0)

// SYS_PESOC_MEM_CTRL
#define SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_SHIFT                          (16)
#define SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_RAWMSK                         (0xff)
#define SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_MASK                           \
 (SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_RAWMSK << SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_SHIFT)
#define SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL(x)                             \
 (((x) & SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_RAWMSK) << SYS_PESOC_MEM_CTRL_SDR_DDL_CTRL_SHIFT)
#define SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_SHIFT                        (0)
#define SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_RAWMSK                       (0xff)
#define SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_MASK                         \
 (SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_RAWMSK << SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_SHIFT)
#define SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL(x)                           \
 (((x) & SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_RAWMSK) << SYS_PESOC_MEM_CTRL_FLASH_DDL_CTRL_SHIFT)

// SYS_PESOC_SOC_CTRL
#define SYS_PESOC_SOC_CTRL_GDMA_CFG_SHIFT                              (16)
#define SYS_PESOC_SOC_CTRL_GDMA_CFG_RAWMSK                             (0x1fff)
#define SYS_PESOC_SOC_CTRL_GDMA_CFG_MASK                               \
 (SYS_PESOC_SOC_CTRL_GDMA_CFG_RAWMSK << SYS_PESOC_SOC_CTRL_GDMA_CFG_SHIFT)
#define SYS_PESOC_SOC_CTRL_GDMA_CFG(x)                                 \
 (((x) & SYS_PESOC_SOC_CTRL_GDMA_CFG_RAWMSK) << SYS_PESOC_SOC_CTRL_GDMA_CFG_SHIFT)
#define SYS_PESOC_SOC_CTRL_MII_LX_SLV_SWAP_SEL                         BIT(13)
#define SYS_PESOC_SOC_CTRL_MII_LX_MST_SWAP_SEL                         BIT(12)
#define SYS_PESOC_SOC_CTRL_MII_LX_WRAPPER_EN                           BIT(11)
#define SYS_PESOC_SOC_CTRL_LX_SLV_SWAP_SEL                             BIT(10)
#define SYS_PESOC_SOC_CTRL_LX_MST_SWAP_SEL                             BIT(9)
#define SYS_PESOC_SOC_CTRL_LX_WL_SWAP_SEL                              BIT(8)
#define SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_SHIFT                          (0)
#define SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_RAWMSK                         (0x7)
#define SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_MASK                           \
 (SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_RAWMSK << SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_SHIFT)
#define SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG(x)                             \
 (((x) & SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_RAWMSK) << SYS_PESOC_SOC_CTRL_SRAM_MUX_CFG_SHIFT)

// SYS_PESOC_PERI_CTRL
#define SYS_PESOC_PERI_CTRL_SOC_FUNC_SPI_RN                            BIT(8)
#define SYS_PESOC_PERI_CTRL_FW_CTRL_INT0                               BIT(24)

// SYS_GPIO_SHTDN_CTRL
#define SYS_GPIO_SHTDN_CTRL_GPIOK_SHTDN_N                              BIT(10)
#define SYS_GPIO_SHTDN_CTRL_GPIOJ_SHTDN_N                              BIT(9)
#define SYS_GPIO_SHTDN_CTRL_GPIOI_SHTDN_N                              BIT(8)
#define SYS_GPIO_SHTDN_CTRL_GPIOH_SHTDN_N                              BIT(7)
#define SYS_GPIO_SHTDN_CTRL_GPIOG_SHTDN_N                              BIT(6)
#define SYS_GPIO_SHTDN_CTRL_GPIOF_SHTDN_N                              BIT(5)
#define SYS_GPIO_SHTDN_CTRL_GPIOE_SHTDN_N                              BIT(4)
#define SYS_GPIO_SHTDN_CTRL_GPIOD_SHTDN_N                              BIT(3)
#define SYS_GPIO_SHTDN_CTRL_GPIOC_SHTDN_N                              BIT(2)
#define SYS_GPIO_SHTDN_CTRL_GPIOB_SHTDN_N                              BIT(1)
#define SYS_GPIO_SHTDN_CTRL_GPIOA_SHTDN_N                              BIT(0)

// SYS_GPIO_DRIVING_CTRL
#define SYS_GPIO_DRIVING_CTRL_GPIOK_DRV_SEL                            BIT(20)
#define SYS_GPIO_DRIVING_CTRL_GPIOJ_DRV_SEL                            BIT(18)
#define SYS_GPIO_DRIVING_CTRL_GPIOI_DRV_SEL                            BIT(16)
#define SYS_GPIO_DRIVING_CTRL_GPIOH_DRV_SEL                            BIT(14)
#define SYS_GPIO_DRIVING_CTRL_GPIOG_DRV_SEL                            BIT(12)
#define SYS_GPIO_DRIVING_CTRL_GPIOF_DRV_SEL                            BIT(10)
#define SYS_GPIO_DRIVING_CTRL_GPIOE_DRV_SEL                            BIT(8)
#define SYS_GPIO_DRIVING_CTRL_GPIOD_DRV_SEL                            BIT(6)
#define SYS_GPIO_DRIVING_CTRL_GPIOC_DRV_SEL                            BIT(4)
#define SYS_GPIO_DRIVING_CTRL_GPIOB_DRV_SEL                            BIT(2)
#define SYS_GPIO_DRIVING_CTRL_GPIOA_DRV_SEL                            BIT(0)

// SYS_GPIO_PULL_CTRL0
#define SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_SHIFT                       (30)
#define SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_SHIFT                       (28)
#define SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_SHIFT                       (26)
#define SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_SHIFT                       (24)
#define SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_SHIFT                       (22)
#define SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPB0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_SHIFT                       (14)
#define SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL0_GPA0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL1
#define SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_SHIFT                       (29)
#define SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_RAWMSK                      (0x7)
#define SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_SHIFT                       (28)
#define SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_SHIFT                       (26)
#define SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_SHIFT                       (24)
#define SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_SHIFT                       (22)
#define SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPD0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_SHIFT                       (14)
#define SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL1_GPC0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL2
#define SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_SHIFT                       (26)
#define SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_SHIFT                       (24)
#define SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_SHIFT                       (22)
#define SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPF0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_SHIFT                       (14)
#define SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL2_GPE0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL3
#define SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_SHIFT                       (30)
#define SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_SHIFT                       (28)
#define SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_SHIFT                       (26)
#define SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_SHIFT                       (24)
#define SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_SHIFT                       (22)
#define SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPH0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_SHIFT                       (14)
#define SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL3_GPG0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL4
#define SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_SHIFT                       (28)
#define SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_SHIFT                       (26)
#define SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_SHIFT                       (24)
#define SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_SHIFT                       (22)
#define SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPJ0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_SHIFT                       (14)
#define SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI6_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL4_GPI0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL5
#define SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_SHIFT                       (20)
#define SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPEA_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPE9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPE8_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_SHIFT                       (12)
#define SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK7_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_SHIFT                       (10)
#define SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK5_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_SHIFT                       (8)
#define SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK4_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_SHIFT                       (6)
#define SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK3_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_SHIFT                       (4)
#define SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK2_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK1_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL5_GPK0_PULL_CTRL_SHIFT)

// SYS_GPIO_PULL_CTRL6
#define SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_SHIFT                       (18)
#define SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL6_GPD9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_SHIFT                       (16)
#define SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL6_GPD8_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_SHIFT                       (2)
#define SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL6_GPC9_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_SHIFT                       (0)
#define SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_RAWMSK                      (0x3)
#define SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_MASK                        \
 (SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_RAWMSK << SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_SHIFT)
#define SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL(x)                          \
 (((x) & SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_RAWMSK) << SYS_GPIO_PULL_CTRL6_GPC8_PULL_CTRL_SHIFT)

// SYS_PERI_PWM0_CTRL
#define SYS_PERI_PWM0_CTRL_EN                                          BIT(31)
#define SYS_PERI_PWM0_CTRL_GT_SEL_SHIFT                                (24)
#define SYS_PERI_PWM0_CTRL_GT_SEL_RAWMSK                               (0xf)
#define SYS_PERI_PWM0_CTRL_GT_SEL_MASK                                 \
 (SYS_PERI_PWM0_CTRL_GT_SEL_RAWMSK << SYS_PERI_PWM0_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM0_CTRL_GT_SEL(x)                                   \
 (((x) & SYS_PERI_PWM0_CTRL_GT_SEL_RAWMSK) << SYS_PERI_PWM0_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM0_CTRL_DUTY_SHIFT                                  (12)
#define SYS_PERI_PWM0_CTRL_DUTY_RAWMSK                                 (0x3ff)
#define SYS_PERI_PWM0_CTRL_DUTY_MASK                                   \
 (SYS_PERI_PWM0_CTRL_DUTY_RAWMSK << SYS_PERI_PWM0_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM0_CTRL_DUTY(x)                                     \
 (((x) & SYS_PERI_PWM0_CTRL_DUTY_RAWMSK) << SYS_PERI_PWM0_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM0_CTRL_PERIOD_SHIFT                                (0)
#define SYS_PERI_PWM0_CTRL_PERIOD_RAWMSK                               (0x3ff)
#define SYS_PERI_PWM0_CTRL_PERIOD_MASK                                 \
 (SYS_PERI_PWM0_CTRL_PERIOD_RAWMSK << SYS_PERI_PWM0_CTRL_PERIOD_SHIFT)
#define SYS_PERI_PWM0_CTRL_PERIOD(x)                                   \
 (((x) & SYS_PERI_PWM0_CTRL_PERIOD_RAWMSK) << SYS_PERI_PWM0_CTRL_PERIOD_SHIFT)

// SYS_PERI_PWM1_CTRL
#define SYS_PERI_PWM1_CTRL_EN                                          BIT(31)
#define SYS_PERI_PWM1_CTRL_GT_SEL_SHIFT                                (24)
#define SYS_PERI_PWM1_CTRL_GT_SEL_RAWMSK                               (0xf)
#define SYS_PERI_PWM1_CTRL_GT_SEL_MASK                                 \
 (SYS_PERI_PWM1_CTRL_GT_SEL_RAWMSK << SYS_PERI_PWM1_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM1_CTRL_GT_SEL(x)                                   \
 (((x) & SYS_PERI_PWM1_CTRL_GT_SEL_RAWMSK) << SYS_PERI_PWM1_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM1_CTRL_DUTY_SHIFT                                  (12)
#define SYS_PERI_PWM1_CTRL_DUTY_RAWMSK                                 (0x3ff)
#define SYS_PERI_PWM1_CTRL_DUTY_MASK                                   \
 (SYS_PERI_PWM1_CTRL_DUTY_RAWMSK << SYS_PERI_PWM1_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM1_CTRL_DUTY(x)                                     \
 (((x) & SYS_PERI_PWM1_CTRL_DUTY_RAWMSK) << SYS_PERI_PWM1_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM1_CTRL_PERIOD_SHIFT                                (0)
#define SYS_PERI_PWM1_CTRL_PERIOD_RAWMSK                               (0x3ff)
#define SYS_PERI_PWM1_CTRL_PERIOD_MASK                                 \
 (SYS_PERI_PWM1_CTRL_PERIOD_RAWMSK << SYS_PERI_PWM1_CTRL_PERIOD_SHIFT)
#define SYS_PERI_PWM1_CTRL_PERIOD(x)                                   \
 (((x) & SYS_PERI_PWM1_CTRL_PERIOD_RAWMSK) << SYS_PERI_PWM1_CTRL_PERIOD_SHIFT)

// SYS_PERI_PWM2_CTRL
#define SYS_PERI_PWM2_CTRL_EN                                          BIT(31)
#define SYS_PERI_PWM2_CTRL_GT_SEL_SHIFT                                (24)
#define SYS_PERI_PWM2_CTRL_GT_SEL_RAWMSK                               (0xf)
#define SYS_PERI_PWM2_CTRL_GT_SEL_MASK                                 \
 (SYS_PERI_PWM2_CTRL_GT_SEL_RAWMSK << SYS_PERI_PWM2_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM2_CTRL_GT_SEL(x)                                   \
 (((x) & SYS_PERI_PWM2_CTRL_GT_SEL_RAWMSK) << SYS_PERI_PWM2_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM2_CTRL_DUTY_SHIFT                                  (12)
#define SYS_PERI_PWM2_CTRL_DUTY_RAWMSK                                 (0x3ff)
#define SYS_PERI_PWM2_CTRL_DUTY_MASK                                   \
 (SYS_PERI_PWM2_CTRL_DUTY_RAWMSK << SYS_PERI_PWM2_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM2_CTRL_DUTY(x)                                     \
 (((x) & SYS_PERI_PWM2_CTRL_DUTY_RAWMSK) << SYS_PERI_PWM2_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM2_CTRL_PERIOD_SHIFT                                (0)
#define SYS_PERI_PWM2_CTRL_PERIOD_RAWMSK                               (0x3ff)
#define SYS_PERI_PWM2_CTRL_PERIOD_MASK                                 \
 (SYS_PERI_PWM2_CTRL_PERIOD_RAWMSK << SYS_PERI_PWM2_CTRL_PERIOD_SHIFT)
#define SYS_PERI_PWM2_CTRL_PERIOD(x)                                   \
 (((x) & SYS_PERI_PWM2_CTRL_PERIOD_RAWMSK) << SYS_PERI_PWM2_CTRL_PERIOD_SHIFT)

// SYS_PERI_PWM3_CTRL
#define SYS_PERI_PWM3_CTRL_EN                                          BIT(31)
#define SYS_PERI_PWM3_CTRL_GT_SEL_SHIFT                                (24)
#define SYS_PERI_PWM3_CTRL_GT_SEL_RAWMSK                               (0xf)
#define SYS_PERI_PWM3_CTRL_GT_SEL_MASK                                 \
 (SYS_PERI_PWM3_CTRL_GT_SEL_RAWMSK << SYS_PERI_PWM3_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM3_CTRL_GT_SEL(x)                                   \
 (((x) & SYS_PERI_PWM3_CTRL_GT_SEL_RAWMSK) << SYS_PERI_PWM3_CTRL_GT_SEL_SHIFT)
#define SYS_PERI_PWM3_CTRL_DUTY_SHIFT                                  (12)
#define SYS_PERI_PWM3_CTRL_DUTY_RAWMSK                                 (0x3ff)
#define SYS_PERI_PWM3_CTRL_DUTY_MASK                                   \
 (SYS_PERI_PWM3_CTRL_DUTY_RAWMSK << SYS_PERI_PWM3_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM3_CTRL_DUTY(x)                                     \
 (((x) & SYS_PERI_PWM3_CTRL_DUTY_RAWMSK) << SYS_PERI_PWM3_CTRL_DUTY_SHIFT)
#define SYS_PERI_PWM3_CTRL_PERIOD_SHIFT                                (0)
#define SYS_PERI_PWM3_CTRL_PERIOD_RAWMSK                               (0x3ff)
#define SYS_PERI_PWM3_CTRL_PERIOD_MASK                                 \
 (SYS_PERI_PWM3_CTRL_PERIOD_RAWMSK << SYS_PERI_PWM3_CTRL_PERIOD_SHIFT)
#define SYS_PERI_PWM3_CTRL_PERIOD(x)                                   \
 (((x) & SYS_PERI_PWM3_CTRL_PERIOD_RAWMSK) << SYS_PERI_PWM3_CTRL_PERIOD_SHIFT)

// SYS_PERI_GTIM_EVT_CTRL
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_EN                                 BIT(31)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_SHIFT                      (28)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_RAWMSK                     (0x7)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_MASK                       \
 (SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL(x)                         \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT3_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_SHIFT                    (24)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_RAWMSK                   (0xf)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_MASK                     \
 (SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR(x)                       \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT3_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_EN                                 BIT(23)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_SHIFT                      (20)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_RAWMSK                     (0x7)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_MASK                       \
 (SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL(x)                         \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT2_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_SHIFT                    (16)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_RAWMSK                   (0xf)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_MASK                     \
 (SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR(x)                       \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT2_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_EN                                 BIT(15)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_SHIFT                      (12)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_RAWMSK                     (0x7)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_MASK                       \
 (SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL(x)                         \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT1_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_SHIFT                    (8)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_RAWMSK                   (0xf)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_MASK                     \
 (SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR(x)                       \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT1_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_EN                                 BIT(7)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_SHIFT                      (4)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_RAWMSK                     (0x7)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_MASK                       \
 (SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL(x)                         \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT0_SRC_SEL_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_SHIFT                    (0)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_RAWMSK                   (0xf)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_MASK                     \
 (SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_RAWMSK << SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_SHIFT)
#define SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR(x)                       \
 (((x) & SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_RAWMSK) << SYS_PERI_GTIM_EVT_CTRL_EVT0_PULSE_DUR_SHIFT)

// SYS_PERI_EGTIM_CTRL
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_SHIFT                   (12)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_RAWMSK                  (0x3)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_MASK                    \
 (SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_RAWMSK << SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL(x)                      \
 (((x) & SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_RAWMSK) << SYS_PERI_EGTIM_CTRL_PIN_GROUP2_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_SHIFT                   (10)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_RAWMSK                  (0x3)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_MASK                    \
 (SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_RAWMSK << SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL(x)                      \
 (((x) & SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_RAWMSK) << SYS_PERI_EGTIM_CTRL_PIN_GROUP1_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_SHIFT                   (8)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_RAWMSK                  (0x3)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_MASK                    \
 (SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_RAWMSK << SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL(x)                      \
 (((x) & SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_RAWMSK) << SYS_PERI_EGTIM_CTRL_PIN_GROUP0_OPT_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_SHIFT                          (4)
#define SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_RAWMSK                         (0x3)
#define SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_MASK                           \
 (SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_RAWMSK << SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_REF_SIG_SEL(x)                             \
 (((x) & SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_RAWMSK) << SYS_PERI_EGTIM_CTRL_REF_SIG_SEL_SHIFT)
#define SYS_PERI_EGTIM_CTRL_EN                                         BIT(0)

// SYS_PEON_STATUS
#define SYS_PEON_STATUS_PEON_SDIO_ALDN                                 BIT(0)

// =================================================================================================
// ADC Regitsters Fileds Define
//
#define ADC_FIFO_SHIFT                                                0
#define ADC_FIFO_RAWMSK                                               0xffffffffL
#define ADC_FIFO_MASK                                                 \
  ADC_FIFO_RAWMSK << ADC_FIFO_SHIFT )
#define ADC_FIFO(x)                                                   \
  ((x) & ADC_FIFO_RAWMSK) << ADC_FIFO_SHIFT)
#define ADC_CONTROL_DBG_SEL_SHIFT                                     24
#define ADC_CONTROL_DBG_SEL_RAWMSK                                    0x7
#define ADC_CONTROL_DBG_SEL_MASK                                      \
  ADC_CONTROL_DBG_SEL_RAWMSK << ADC_CONTROL_DBG_SEL_SHIFT )
#define ADC_CONTROL_DBG_SEL(x)                                        \
  ((x) & ADC_CONTROL_DBG_SEL_RAWMSK) << ADC_CONTROL_DBG_SEL_SHIFT)
#define ADC_CONTROL_THRESHOLD_SHIFT                                   16
#define ADC_CONTROL_THRESHOLD_RAWMSK                                  0x3f
#define ADC_CONTROL_THRESHOLD_MASK                                    \
  ADC_CONTROL_THRESHOLD_RAWMSK << ADC_CONTROL_THRESHOLD_SHIFT )
#define ADC_CONTROL_THRESHOLD(x)                                      \
  ((x) & ADC_CONTROL_THRESHOLD_RAWMSK) << ADC_CONTROL_THRESHOLD_SHIFT)
#define ADC_CONTROL_BURST_SIZE_SHIFT                                  8
#define ADC_CONTROL_BURST_SIZE_RAWMSK                                 0x1f
#define ADC_CONTROL_BURST_SIZE_MASK                                   \
  ADC_CONTROL_BURST_SIZE_RAWMSK << ADC_CONTROL_BURST_SIZE_SHIFT )
#define ADC_CONTROL_BURST_SIZE(x)                                     \
  ((x) & ADC_CONTROL_BURST_SIZE_RAWMSK) << ADC_CONTROL_BURST_SIZE_SHIFT)
#define ADC_CONTROL_ENDIAN                                            BIT(3)
#define ADC_CONTROL_ENDIAN_SHIFT                                      3
#define ADC_CONTROL_ENDIAN_RAWMSK                                     0x1
#define ADC_CONTROL_ENDIAN_MASK                                       \
  ADC_CONTROL_ENDIAN_RAWMSK << ADC_CONTROL_ENDIAN_SHIFT )
#define ADC_CONTROL_OVERWRITE                                         BIT(2)
#define ADC_CONTROL_OVERWRITE_SHIFT                                   2
#define ADC_CONTROL_OVERWRITE_RAWMSK                                  0x1
#define ADC_CONTROL_OVERWRITE_MASK                                    \
  ADC_CONTROL_OVERWRITE_RAWMSK << ADC_CONTROL_OVERWRITE_SHIFT )
#define ADC_CONTROL_ONESHOT                                           BIT(1)
#define ADC_CONTROL_ONESHOT_SHIFT                                     1
#define ADC_CONTROL_ONESHOT_RAWMSK                                    0x1
#define ADC_CONTROL_ONESHOT_MASK                                      \
  ADC_CONTROL_ONESHOT_RAWMSK << ADC_CONTROL_ONESHOT_SHIFT )
#define ADC_CONTROL_COMP_ONLY                                         BIT(0)
#define ADC_CONTROL_COMP_ONLY_SHIFT                                   0
#define ADC_CONTROL_COMP_ONLY_RAWMSK                                  0x1
#define ADC_CONTROL_COMP_ONLY_MASK                                    \
  ADC_CONTROL_COMP_ONLY_RAWMSK << ADC_CONTROL_COMP_ONLY_SHIFT )
#define ADC_INTR_EN_AWAKE_CPU_EN                                      BIT(7)
#define ADC_INTR_EN_AWAKE_CPU_EN_SHIFT                                7
#define ADC_INTR_EN_AWAKE_CPU_EN_RAWMSK                               0x1
#define ADC_INTR_EN_AWAKE_CPU_EN_MASK                                 \
  ADC_INTR_EN_AWAKE_CPU_EN_RAWMSK << ADC_INTR_EN_AWAKE_CPU_EN_SHIFT )
#define ADC_INTR_EN_FIFO_RD_ERROR_EN                                  BIT(6)
#define ADC_INTR_EN_FIFO_RD_ERROR_EN_SHIFT                            6
#define ADC_INTR_EN_FIFO_RD_ERROR_EN_RAWMSK                           0x1
#define ADC_INTR_EN_FIFO_RD_ERROR_EN_MASK                             \
  ADC_INTR_EN_FIFO_RD_ERROR_EN_RAWMSK << ADC_INTR_EN_FIFO_RD_ERROR_EN_SHIFT )
#define ADC_INTR_EN_FIFO_RD_REQ_EN                                    BIT(5)
#define ADC_INTR_EN_FIFO_RD_REQ_EN_SHIFT                              5
#define ADC_INTR_EN_FIFO_RD_REQ_EN_RAWMSK                             0x1
#define ADC_INTR_EN_FIFO_RD_REQ_EN_MASK                               \
  ADC_INTR_EN_FIFO_RD_REQ_EN_RAWMSK << ADC_INTR_EN_FIFO_RD_REQ_EN_SHIFT )
#define ADC_INTR_EN_FIFO_FULL_EN                                      BIT(4)
#define ADC_INTR_EN_FIFO_FULL_EN_SHIFT                                4
#define ADC_INTR_EN_FIFO_FULL_EN_RAWMSK                               0x1
#define ADC_INTR_EN_FIFO_FULL_EN_MASK                                 \
  ADC_INTR_EN_FIFO_FULL_EN_RAWMSK << ADC_INTR_EN_FIFO_FULL_EN_SHIFT )
#define ADC_INTR_EN_COMP_3_EN                                         BIT(3)
#define ADC_INTR_EN_COMP_3_EN_SHIFT                                   3
#define ADC_INTR_EN_COMP_3_EN_RAWMSK                                  0x1
#define ADC_INTR_EN_COMP_3_EN_MASK                                    \
  ADC_INTR_EN_COMP_3_EN_RAWMSK << ADC_INTR_EN_COMP_3_EN_SHIFT )
#define ADC_INTR_EN_COMP_2_EN                                         BIT(2)
#define ADC_INTR_EN_COMP_2_EN_SHIFT                                   2
#define ADC_INTR_EN_COMP_2_EN_RAWMSK                                  0x1
#define ADC_INTR_EN_COMP_2_EN_MASK                                    \
  ADC_INTR_EN_COMP_2_EN_RAWMSK << ADC_INTR_EN_COMP_2_EN_SHIFT )
#define ADC_INTR_EN_COMP_1_EN                                         BIT(1)
#define ADC_INTR_EN_COMP_1_EN_SHIFT                                   1
#define ADC_INTR_EN_COMP_1_EN_RAWMSK                                  0x1
#define ADC_INTR_EN_COMP_1_EN_MASK                                    \
  ADC_INTR_EN_COMP_1_EN_RAWMSK << ADC_INTR_EN_COMP_1_EN_SHIFT )
#define ADC_INTR_EN_COMP_0_EN                                         BIT(0)
#define ADC_INTR_EN_COMP_0_EN_SHIFT                                   0
#define ADC_INTR_EN_COMP_0_EN_RAWMSK                                  0x1
#define ADC_INTR_EN_COMP_0_EN_MASK                                    \
  ADC_INTR_EN_COMP_0_EN_RAWMSK << ADC_INTR_EN_COMP_0_EN_SHIFT )
#define ADC_INTR_STS_FIFO_THRESHOLD                                   BIT(7)
#define ADC_INTR_STS_FIFO_THRESHOLD_SHIFT                             7
#define ADC_INTR_STS_FIFO_THRESHOLD_RAWMSK                            0x1
#define ADC_INTR_STS_FIFO_THRESHOLD_MASK                              \
  ADC_INTR_STS_FIFO_THRESHOLD_RAWMSK << ADC_INTR_STS_FIFO_THRESHOLD_SHIFT )
#define ADC_INTR_STS_FIFO_RD_ERROR_ST                                 BIT(6)
#define ADC_INTR_STS_FIFO_RD_ERROR_ST_SHIFT                           6
#define ADC_INTR_STS_FIFO_RD_ERROR_ST_RAWMSK                          0x1
#define ADC_INTR_STS_FIFO_RD_ERROR_ST_MASK                            \
  ADC_INTR_STS_FIFO_RD_ERROR_ST_RAWMSK << ADC_INTR_STS_FIFO_RD_ERROR_ST_SHIFT )
#define ADC_INTR_STS_FIFO_RD_REQ_ST                                   BIT(5)
#define ADC_INTR_STS_FIFO_RD_REQ_ST_SHIFT                             5
#define ADC_INTR_STS_FIFO_RD_REQ_ST_RAWMSK                            0x1
#define ADC_INTR_STS_FIFO_RD_REQ_ST_MASK                              \
  ADC_INTR_STS_FIFO_RD_REQ_ST_RAWMSK << ADC_INTR_STS_FIFO_RD_REQ_ST_SHIFT )
#define ADC_INTR_STS_FIFO_FULL_ST                                     BIT(4)
#define ADC_INTR_STS_FIFO_FULL_ST_SHIFT                               4
#define ADC_INTR_STS_FIFO_FULL_ST_RAWMSK                              0x1
#define ADC_INTR_STS_FIFO_FULL_ST_MASK                                \
  ADC_INTR_STS_FIFO_FULL_ST_RAWMSK << ADC_INTR_STS_FIFO_FULL_ST_SHIFT )
#define ADC_INTR_STS_COMP_3_ST                                        BIT(3)
#define ADC_INTR_STS_COMP_3_ST_SHIFT                                  3
#define ADC_INTR_STS_COMP_3_ST_RAWMSK                                 0x1
#define ADC_INTR_STS_COMP_3_ST_MASK                                   \
  ADC_INTR_STS_COMP_3_ST_RAWMSK << ADC_INTR_STS_COMP_3_ST_SHIFT )
#define ADC_INTR_STS_COMP_2_ST                                        BIT(2)
#define ADC_INTR_STS_COMP_2_ST_SHIFT                                  2
#define ADC_INTR_STS_COMP_2_ST_RAWMSK                                 0x1
#define ADC_INTR_STS_COMP_2_ST_MASK                                   \
  ADC_INTR_STS_COMP_2_ST_RAWMSK << ADC_INTR_STS_COMP_2_ST_SHIFT )
#define ADC_INTR_STS_COMP_1_ST                                        BIT(1)
#define ADC_INTR_STS_COMP_1_ST_SHIFT                                  1
#define ADC_INTR_STS_COMP_1_ST_RAWMSK                                 0x1
#define ADC_INTR_STS_COMP_1_ST_MASK                                   \
  ADC_INTR_STS_COMP_1_ST_RAWMSK << ADC_INTR_STS_COMP_1_ST_SHIFT )
#define ADC_INTR_STS_COMP_0_ST                                        BIT(0)
#define ADC_INTR_STS_COMP_0_ST_SHIFT                                  0
#define ADC_INTR_STS_COMP_0_ST_RAWMSK                                 0x1
#define ADC_INTR_STS_COMP_0_ST_MASK                                   \
  ADC_INTR_STS_COMP_0_ST_RAWMSK << ADC_INTR_STS_COMP_0_ST_SHIFT )
#define ADC_COMP_VALUE_LH_SHIFT                                       16
#define ADC_COMP_VALUE_LH_RAWMSK                                      0xffff
#define ADC_COMP_VALUE_LH_MASK                                        \
  ADC_COMP_VALUE_LH_RAWMSK << ADC_COMP_VALUE_LH_SHIFT )
#define ADC_COMP_VALUE_LH(x)                                          \
  ((x) & ADC_COMP_VALUE_LH_RAWMSK) << ADC_COMP_VALUE_LH_SHIFT)
#define ADC_COMP_VALUE_LL_SHIFT                                       0
#define ADC_COMP_VALUE_LL_RAWMSK                                      0xffff
#define ADC_COMP_VALUE_LL_MASK                                        \
  ADC_COMP_VALUE_LL_RAWMSK << ADC_COMP_VALUE_LL_SHIFT )
#define ADC_COMP_VALUE_LL(x)                                          \
  ((x) & ADC_COMP_VALUE_LL_RAWMSK) << ADC_COMP_VALUE_LL_SHIFT)
#define ADC_COMP_VALUE_HH_SHIFT                                       16
#define ADC_COMP_VALUE_HH_RAWMSK                                      0xffff
#define ADC_COMP_VALUE_HH_MASK                                        \
  ADC_COMP_VALUE_HH_RAWMSK << ADC_COMP_VALUE_HH_SHIFT )
#define ADC_COMP_VALUE_HH(x)                                          \
  ((x) & ADC_COMP_VALUE_HH_RAWMSK) << ADC_COMP_VALUE_HH_SHIFT)
#define ADC_COMP_VALUE_HL_SHIFT                                       0
#define ADC_COMP_VALUE_HL_RAWMSK                                      0xffff
#define ADC_COMP_VALUE_HL_MASK                                        \
  ADC_COMP_VALUE_HL_RAWMSK << ADC_COMP_VALUE_HL_SHIFT )
#define ADC_COMP_VALUE_HL(x)                                          \
  ((x) & ADC_COMP_VALUE_HL_RAWMSK) << ADC_COMP_VALUE_HL_SHIFT)
#define ADC_COMP_SET_SHIFT                                            0
#define ADC_COMP_SET_RAWMSK                                           0xf
#define ADC_COMP_SET_MASK                                             \
  ADC_COMP_SET_RAWMSK << ADC_COMP_SET_SHIFT )
#define ADC_COMP_SET(x)                                               \
  ((x) & ADC_COMP_SET_RAWMSK) << ADC_COMP_SET_SHIFT)
#define ADC_POWER_CUT_CNTR_SHIFT                                      16
#define ADC_POWER_CUT_CNTR_RAWMSK                                     0xff
#define ADC_POWER_CUT_CNTR_MASK                                       \
  ADC_POWER_CUT_CNTR_RAWMSK << ADC_POWER_CUT_CNTR_SHIFT )
#define ADC_POWER_CUT_CNTR(x)                                         \
  ((x) & ADC_POWER_CUT_CNTR_RAWMSK) << ADC_POWER_CUT_CNTR_SHIFT)
#define ADC_POWER_FIFO_ON_ST                                          BIT(11)
#define ADC_POWER_FIFO_ON_ST_SHIFT                                    11
#define ADC_POWER_FIFO_ON_ST_RAWMSK                                   0x1
#define ADC_POWER_FIFO_ON_ST_MASK                                     \
  ADC_POWER_FIFO_ON_ST_RAWMSK << ADC_POWER_FIFO_ON_ST_SHIFT )
#define ADC_POWER_ISO_ON_ST                                           BIT(10)
#define ADC_POWER_ISO_ON_ST_SHIFT                                     10
#define ADC_POWER_ISO_ON_ST_RAWMSK                                    0x1
#define ADC_POWER_ISO_ON_ST_MASK                                      \
  ADC_POWER_ISO_ON_ST_RAWMSK << ADC_POWER_ISO_ON_ST_SHIFT )
#define ADC_POWER_PWR33_ON_ST                                         BIT(9)
#define ADC_POWER_PWR33_ON_ST_SHIFT                                   9
#define ADC_POWER_PWR33_ON_ST_RAWMSK                                  0x1
#define ADC_POWER_PWR33_ON_ST_MASK                                    \
  ADC_POWER_PWR33_ON_ST_RAWMSK << ADC_POWER_PWR33_ON_ST_SHIFT )
#define ADC_POWER_PWR12_ON_ST                                         BIT(8)
#define ADC_POWER_PWR12_ON_ST_SHIFT                                   8
#define ADC_POWER_PWR12_ON_ST_RAWMSK                                  0x1
#define ADC_POWER_PWR12_ON_ST_MASK                                    \
  ADC_POWER_PWR12_ON_ST_RAWMSK << ADC_POWER_PWR12_ON_ST_SHIFT )
#define ADC_POWER_ISO_MANUAL                                          BIT(3)
#define ADC_POWER_ISO_MANUAL_SHIFT                                    3
#define ADC_POWER_ISO_MANUAL_RAWMSK                                   0x1
#define ADC_POWER_ISO_MANUAL_MASK                                     \
  ADC_POWER_ISO_MANUAL_RAWMSK << ADC_POWER_ISO_MANUAL_SHIFT )
#define ADC_POWER_PWR33_MANUAL                                        BIT(2)
#define ADC_POWER_PWR33_MANUAL_SHIFT                                  2
#define ADC_POWER_PWR33_MANUAL_RAWMSK                                 0x1
#define ADC_POWER_PWR33_MANUAL_MASK                                   \
  ADC_POWER_PWR33_MANUAL_RAWMSK << ADC_POWER_PWR33_MANUAL_SHIFT )
#define ADC_POWER_PWR12_MANUAL                                        BIT(1)
#define ADC_POWER_PWR12_MANUAL_SHIFT                                  1
#define ADC_POWER_PWR12_MANUAL_RAWMSK                                 0x1
#define ADC_POWER_PWR12_MANUAL_MASK                                   \
  ADC_POWER_PWR12_MANUAL_RAWMSK << ADC_POWER_PWR12_MANUAL_SHIFT )
#define ADC_POWER_AUTO                                                BIT(0)
#define ADC_POWER_AUTO_SHIFT                                          0
#define ADC_POWER_AUTO_RAWMSK                                         0x1
#define ADC_POWER_AUTO_MASK                                           \
  ADC_POWER_AUTO_RAWMSK << ADC_POWER_AUTO_SHIFT )
#define ADC_ANAPAR_AD0_SHIFT                                          2
#define ADC_ANAPAR_AD0_RAWMSK                                         0x3fffffff
#define ADC_ANAPAR_AD0_MASK                                           \
  ADC_ANAPAR_AD0_RAWMSK << ADC_ANAPAR_AD0_SHIFT )
#define ADC_ANAPAR_AD0(x)                                             \
  ((x) & ADC_ANAPAR_AD0_RAWMSK) << ADC_ANAPAR_AD0_SHIFT)
#define ADC_ANAPAR_AUDIO_EN                                           BIT(1)
#define ADC_ANAPAR_AUDIO_EN_SHIFT                                     1
#define ADC_ANAPAR_AUDIO_EN_RAWMSK                                    0x1
#define ADC_ANAPAR_AUDIO_EN_MASK                                      \
  ADC_ANAPAR_AUDIO_EN_RAWMSK << ADC_ANAPAR_AUDIO_EN_SHIFT )
#define ADC_ANAPAR_EN_MANUAL                                          BIT(0)
#define ADC_ANAPAR_EN_MANUAL_SHIFT                                    0
#define ADC_ANAPAR_EN_MANUAL_RAWMSK                                   0x1
#define ADC_ANAPAR_EN_MANUAL_MASK                                     \
  ADC_ANAPAR_EN_MANUAL_RAWMSK << ADC_ANAPAR_EN_MANUAL_SHIFT )
#define ADC_ANAPAR_AD1_SHIFT                                          0
#define ADC_ANAPAR_AD1_RAWMSK                                         0xffffffffL
#define ADC_ANAPAR_AD1_MASK                                           \
  ADC_ANAPAR_AD1_RAWMSK << ADC_ANAPAR_AD1_SHIFT )
#define ADC_ANAPAR_AD1(x)                                             \
  ((x) & ADC_ANAPAR_AD1_RAWMSK) << ADC_ANAPAR_AD1_SHIFT)
#define ADC_ANAPAR_AD2_SHIFT                                          0
#define ADC_ANAPAR_AD2_RAWMSK                                         0xffffffffL
#define ADC_ANAPAR_AD2_MASK                                           \
  ADC_ANAPAR_AD2_RAWMSK << ADC_ANAPAR_AD2_SHIFT )
#define ADC_ANAPAR_AD2(x)                                             \
  ((x) & ADC_ANAPAR_AD2_RAWMSK) << ADC_ANAPAR_AD2_SHIFT)
#define ADC_ANAPAR_AD3_SHIFT                                          0
#define ADC_ANAPAR_AD3_RAWMSK                                         0xffffffffL
#define ADC_ANAPAR_AD3_MASK                                           \
  ADC_ANAPAR_AD3_RAWMSK << ADC_ANAPAR_AD3_SHIFT )
#define ADC_ANAPAR_AD3(x)                                             \
  ((x) & ADC_ANAPAR_AD3_RAWMSK) << ADC_ANAPAR_AD3_SHIFT)
#define ADC_ANAPAR_AD4_SHIFT                                          0
#define ADC_ANAPAR_AD4_RAWMSK                                         0xffffffffL
#define ADC_ANAPAR_AD4_MASK                                           \
  ADC_ANAPAR_AD4_RAWMSK << ADC_ANAPAR_AD4_SHIFT )
#define ADC_ANAPAR_AD4(x)                                             \
  ((x) & ADC_ANAPAR_AD4_RAWMSK) << ADC_ANAPAR_AD4_SHIFT)
#define ADC_ANAPAR_AD5_SHIFT                                          0
#define ADC_ANAPAR_AD5_RAWMSK                                         0xffffffffL
#define ADC_ANAPAR_AD5_MASK                                           \
  ADC_ANAPAR_AD5_RAWMSK << ADC_ANAPAR_AD5_SHIFT )
#define ADC_ANAPAR_AD5(x)                                             \
  ((x) & ADC_ANAPAR_AD5_RAWMSK) << ADC_ANAPAR_AD5_SHIFT)
#define ADC_CALI_DATA_6_SHIFT                                         16
#define ADC_CALI_DATA_6_RAWMSK                                        0xffff
#define ADC_CALI_DATA_6_MASK                                          \
  ADC_CALI_DATA_6_RAWMSK << ADC_CALI_DATA_6_SHIFT )
#define ADC_CALI_DATA_6(x)                                            \
  ((x) & ADC_CALI_DATA_6_RAWMSK) << ADC_CALI_DATA_6_SHIFT)
#define ADC_CALI_DATA_6(x)                                            \
  ((x) & ADC_CALI_DATA_6_RAWMSK) << ADC_CALI_DATA_6_SHIFT)
#define ADC_CALI_DATA_0_SHIFT                                         0
#define ADC_CALI_DATA_0_RAWMSK                                        0xffff
#define ADC_CALI_DATA_0_MASK                                          \
  ADC_CALI_DATA_0_RAWMSK << ADC_CALI_DATA_0_SHIFT )
#define ADC_CALI_DATA_0(x)                                            \
  ((x) & ADC_CALI_DATA_0_RAWMSK) << ADC_CALI_DATA_0_SHIFT)
#define ADC_CALI_DATA_0(x)                                            \
  ((x) & ADC_CALI_DATA_0_RAWMSK) << ADC_CALI_DATA_0_SHIFT)

// =================================================================================================
// DAC Regitsters Fileds Define
//
#define DAC_FIFO_SHIFT                                                0
#define DAC_FIFO_RAWMSK                                               0xffffffffL
#define DAC_FIFO_MASK                                                 \
  (DAC_FIFO_RAWMSK << DAC_FIFO_SHIFT )
#define DAC_FIFO(x)                                                   \
  (((x) & DAC_FIFO_RAWMSK) << DAC_FIFO_SHIFT)
#define DAC_CTRL_DELTA_SIGMA_SHIFT                                    25
#define DAC_CTRL_DELTA_SIGMA_RAWMSK                                   0x7
#define DAC_CTRL_DELTA_SIGMA_MASK                                     \
  (DAC_CTRL_DELTA_SIGMA_RAWMSK << DAC_CTRL_DELTA_SIGMA_SHIFT )
#define DAC_CTRL_DELTA_SIGMA(x)                                       \
  (((x) & DAC_CTRL_DELTA_SIGMA_RAWMSK) << DAC_CTRL_DELTA_SIGMA_SHIFT)
#define DAC_CTRL_BYPASS_DSC                                           BIT(24)
#define DAC_CTRL_BYPASS_DSC_SHIFT                                     24
#define DAC_CTRL_BYPASS_DSC_RAWMSK                                    0x1
#define DAC_CTRL_BYPASS_DSC_MASK                                      \
  (DAC_CTRL_BYPASS_DSC_RAWMSK << DAC_CTRL_BYPASS_DSC_SHIFT )
#define DAC_CTRL_DSC_DBG_SEL_SHIFT                                    19
#define DAC_CTRL_DSC_DBG_SEL_RAWMSK                                   0x3
#define DAC_CTRL_DSC_DBG_SEL_MASK                                     \
  (DAC_CTRL_DSC_DBG_SEL_RAWMSK << DAC_CTRL_DSC_DBG_SEL_SHIFT )
#define DAC_CTRL_DSC_DBG_SEL(x)                                       \
  (((x) & DAC_CTRL_DSC_DBG_SEL_RAWMSK) << DAC_CTRL_DSC_DBG_SEL_SHIFT)
#define DAC_CTRL_DBG_SEL_SHIFT                                        16
#define DAC_CTRL_DBG_SEL_RAWMSK                                       0x7
#define DAC_CTRL_DBG_SEL_MASK                                         \
  (DAC_CTRL_DBG_SEL_RAWMSK << DAC_CTRL_DBG_SEL_SHIFT )
#define DAC_CTRL_DBG_SEL(x)                                           \
  (((x) & DAC_CTRL_DBG_SEL_RAWMSK) << DAC_CTRL_DBG_SEL_SHIFT)
#define DAC_CTRL_BURST_SIZE_SHIFT                                     8
#define DAC_CTRL_BURST_SIZE_RAWMSK                                    0xf
#define DAC_CTRL_BURST_SIZE_MASK                                      \
  (DAC_CTRL_BURST_SIZE_RAWMSK << DAC_CTRL_BURST_SIZE_SHIFT )
#define DAC_CTRL_BURST_SIZE(x)                                        \
  (((x) & DAC_CTRL_BURST_SIZE_RAWMSK) << DAC_CTRL_BURST_SIZE_SHIFT)
#define DAC_CTRL_FILTER_SETTLE                                        BIT(4)
#define DAC_CTRL_FILTER_SETTLE_SHIFT                                  4
#define DAC_CTRL_FILTER_SETTLE_RAWMSK                                 0x1
#define DAC_CTRL_FILTER_SETTLE_MASK                                   \
  (DAC_CTRL_FILTER_SETTLE_RAWMSK << DAC_CTRL_FILTER_SETTLE_SHIFT )
#define DAC_CTRL_OV_OPTION                                            BIT(3)
#define DAC_CTRL_OV_OPTION_SHIFT                                      3
#define DAC_CTRL_OV_OPTION_RAWMSK                                     0x1
#define DAC_CTRL_OV_OPTION_MASK                                       \
  (DAC_CTRL_OV_OPTION_RAWMSK << DAC_CTRL_OV_OPTION_SHIFT )
#define DAC_CTRL_ENDIAN                                               BIT(2)
#define DAC_CTRL_ENDIAN_SHIFT                                         2
#define DAC_CTRL_ENDIAN_RAWMSK                                        0x1
#define DAC_CTRL_ENDIAN_MASK                                          \
  (DAC_CTRL_ENDIAN_RAWMSK << DAC_CTRL_ENDIAN_SHIFT )
#define DAC_CTRL_SPEED                                                BIT(1)
#define DAC_CTRL_SPEED_SHIFT                                          1
#define DAC_CTRL_SPEED_RAWMSK                                         0x1
#define DAC_CTRL_SPEED_MASK                                           \
  (DAC_CTRL_SPEED_RAWMSK << DAC_CTRL_SPEED_SHIFT )
#define DAC_CTRL_FIFO_EN                                              BIT(0)
#define DAC_CTRL_FIFO_EN_SHIFT                                        0
#define DAC_CTRL_FIFO_EN_RAWMSK                                       0x1
#define DAC_CTRL_FIFO_EN_MASK                                         \
  (DAC_CTRL_FIFO_EN_RAWMSK << DAC_CTRL_FIFO_EN_SHIFT )
#define DAC_INTR_CTRL_DSC_OVERFLOW1_EN                                BIT(6)
#define DAC_INTR_CTRL_DSC_OVERFLOW1_EN_SHIFT                          6
#define DAC_INTR_CTRL_DSC_OVERFLOW1_EN_RAWMSK                         0x1
#define DAC_INTR_CTRL_DSC_OVERFLOW1_EN_MASK                           \
  (DAC_INTR_CTRL_DSC_OVERFLOW1_EN_RAWMSK << DAC_INTR_CTRL_DSC_OVERFLOW1_EN_SHIFT )
#define DAC_INTR_CTRL_DSC_OVERFLOW0_EN                                BIT(5)
#define DAC_INTR_CTRL_DSC_OVERFLOW0_EN_SHIFT                          5
#define DAC_INTR_CTRL_DSC_OVERFLOW0_EN_RAWMSK                         0x1
#define DAC_INTR_CTRL_DSC_OVERFLOW0_EN_MASK                           \
  (DAC_INTR_CTRL_DSC_OVERFLOW0_EN_RAWMSK << DAC_INTR_CTRL_DSC_OVERFLOW0_EN_SHIFT )
#define DAC_INTR_CTRL_WRITE_ERROR_EN                                  BIT(4)
#define DAC_INTR_CTRL_WRITE_ERROR_EN_SHIFT                            4
#define DAC_INTR_CTRL_WRITE_ERROR_EN_RAWMSK                           0x1
#define DAC_INTR_CTRL_WRITE_ERROR_EN_MASK                             \
  (DAC_INTR_CTRL_WRITE_ERROR_EN_RAWMSK << DAC_INTR_CTRL_WRITE_ERROR_EN_SHIFT )
#define DAC_INTR_CTRL_FIFO_STOP_EN                                    BIT(3)
#define DAC_INTR_CTRL_FIFO_STOP_EN_SHIFT                              3
#define DAC_INTR_CTRL_FIFO_STOP_EN_RAWMSK                             0x1
#define DAC_INTR_CTRL_FIFO_STOP_EN_MASK                               \
  (DAC_INTR_CTRL_FIFO_STOP_EN_RAWMSK << DAC_INTR_CTRL_FIFO_STOP_EN_SHIFT )
#define DAC_INTR_CTRL_FIFO_OVERFLOW_EN                                BIT(2)
#define DAC_INTR_CTRL_FIFO_OVERFLOW_EN_SHIFT                          2
#define DAC_INTR_CTRL_FIFO_OVERFLOW_EN_RAWMSK                         0x1
#define DAC_INTR_CTRL_FIFO_OVERFLOW_EN_MASK                           \
  (DAC_INTR_CTRL_FIFO_OVERFLOW_EN_RAWMSK << DAC_INTR_CTRL_FIFO_OVERFLOW_EN_SHIFT )
#define DAC_INTR_CTRL_FIFO_WR_REQ_EN                                  BIT(1)
#define DAC_INTR_CTRL_FIFO_WR_REQ_EN_SHIFT                            1
#define DAC_INTR_CTRL_FIFO_WR_REQ_EN_RAWMSK                           0x1
#define DAC_INTR_CTRL_FIFO_WR_REQ_EN_MASK                             \
  (DAC_INTR_CTRL_FIFO_WR_REQ_EN_RAWMSK << DAC_INTR_CTRL_FIFO_WR_REQ_EN_SHIFT )
#define DAC_INTR_CTRL_FIFO_FULL_EN                                    BIT(0)
#define DAC_INTR_CTRL_FIFO_FULL_EN_SHIFT                              0
#define DAC_INTR_CTRL_FIFO_FULL_EN_RAWMSK                             0x1
#define DAC_INTR_CTRL_FIFO_FULL_EN_MASK                               \
  (DAC_INTR_CTRL_FIFO_FULL_EN_RAWMSK << DAC_INTR_CTRL_FIFO_FULL_EN_SHIFT )
#define DAC_INTR_STS_DSC_OVERFLOW1                                    BIT(6)
#define DAC_INTR_STS_DSC_OVERFLOW1_SHIFT                              6
#define DAC_INTR_STS_DSC_OVERFLOW1_RAWMSK                             0x1
#define DAC_INTR_STS_DSC_OVERFLOW1_MASK                               \
  (DAC_INTR_STS_DSC_OVERFLOW1_RAWMSK << DAC_INTR_STS_DSC_OVERFLOW1_SHIFT )
#define DAC_INTR_STS_DSC_OVERFLOW0                                    BIT(5)
#define DAC_INTR_STS_DSC_OVERFLOW0_SHIFT                              5
#define DAC_INTR_STS_DSC_OVERFLOW0_RAWMSK                             0x1
#define DAC_INTR_STS_DSC_OVERFLOW0_MASK                               \
  (DAC_INTR_STS_DSC_OVERFLOW0_RAWMSK << DAC_INTR_STS_DSC_OVERFLOW0_SHIFT )
#define DAC_INTR_STS_WRITE_ERROR                                      BIT(4)
#define DAC_INTR_STS_WRITE_ERROR_SHIFT                                4
#define DAC_INTR_STS_WRITE_ERROR_RAWMSK                               0x1
#define DAC_INTR_STS_WRITE_ERROR_MASK                                 \
  (DAC_INTR_STS_WRITE_ERROR_RAWMSK << DAC_INTR_STS_WRITE_ERROR_SHIFT )
#define DAC_INTR_STS_FIFOOP                                           BIT(3)
#define DAC_INTR_STS_FIFOOP_SHIFT                                     3
#define DAC_INTR_STS_FIFOOP_RAWMSK                                    0x1
#define DAC_INTR_STS_FIFOOP_MASK                                      \
  (DAC_INTR_STS_FIFOOP_RAWMSK << DAC_INTR_STS_FIFOOP_SHIFT )
#define DAC_INTR_STS_FIFO_OVERFLOW                                    BIT(2)
#define DAC_INTR_STS_FIFO_OVERFLOW_SHIFT                              2
#define DAC_INTR_STS_FIFO_OVERFLOW_RAWMSK                             0x1
#define DAC_INTR_STS_FIFO_OVERFLOW_MASK                               \
  (DAC_INTR_STS_FIFO_OVERFLOW_RAWMSK << DAC_INTR_STS_FIFO_OVERFLOW_SHIFT )
#define DAC_INTR_STS_FIFO_WR_REQ                                      BIT(1)
#define DAC_INTR_STS_FIFO_WR_REQ_SHIFT                                1
#define DAC_INTR_STS_FIFO_WR_REQ_RAWMSK                               0x1
#define DAC_INTR_STS_FIFO_WR_REQ_MASK                                 \
  (DAC_INTR_STS_FIFO_WR_REQ_RAWMSK << DAC_INTR_STS_FIFO_WR_REQ_SHIFT )
#define DAC_INTR_STS_FIFO_FULL                                        BIT(0)
#define DAC_INTR_STS_FIFO_FULL_SHIFT                                  0
#define DAC_INTR_STS_FIFO_FULL_RAWMSK                                 0x1
#define DAC_INTR_STS_FIFO_FULL_MASK                                   \
  (DAC_INTR_STS_FIFO_FULL_RAWMSK << DAC_INTR_STS_FIFO_FULL_SHIFT )
#define DAC_PWR_CTRL_CUT_CNTR_SHIFT                                   16
#define DAC_PWR_CTRL_CUT_CNTR_RAWMSK                                  0xff
#define DAC_PWR_CTRL_CUT_CNTR_MASK                                    \
  (DAC_PWR_CTRL_CUT_CNTR_RAWMSK << DAC_PWR_CTRL_CUT_CNTR_SHIFT )
#define DAC_PWR_CTRL_CUT_CNTR(x)                                      \
  (((x) & DAC_PWR_CTRL_CUT_CNTR_RAWMSK) << DAC_PWR_CTRL_CUT_CNTR_SHIFT)
#define ST_DAC_PWR_CTRL_FIFO_ON                                       BIT(11)
#define ST_DAC_PWR_CTRL_FIFO_ON_SHIFT                                 11
#define ST_DAC_PWR_CTRL_FIFO_ON_RAWMSK                                0x1
#define ST_DAC_PWR_CTRL_FIFO_ON_MASK                                  \
  (ST_DAC_PWR_CTRL_FIFO_ON_RAWMSK << ST_DAC_PWR_CTRL_FIFO_ON_SHIFT )
#define ST_DAC_PWR_CTRL_ISO_ON                                        BIT(10)
#define ST_DAC_PWR_CTRL_ISO_ON_SHIFT                                  10
#define ST_DAC_PWR_CTRL_ISO_ON_RAWMSK                                 0x1
#define ST_DAC_PWR_CTRL_ISO_ON_MASK                                   \
  (ST_DAC_PWR_CTRL_ISO_ON_RAWMSK << ST_DAC_PWR_CTRL_ISO_ON_SHIFT )
#define ST_DAC_PWR_CTRL_PWR33_ON                                      BIT(9)
#define ST_DAC_PWR_CTRL_PWR33_ON_SHIFT                                9
#define ST_DAC_PWR_CTRL_PWR33_ON_RAWMSK                               0x1
#define ST_DAC_PWR_CTRL_PWR33_ON_MASK                                 \
  (ST_DAC_PWR_CTRL_PWR33_ON_RAWMSK << ST_DAC_PWR_CTRL_PWR33_ON_SHIFT )
#define ST_DAC_PWR_CTRL_PWR12_ON                                      BIT(8)
#define ST_DAC_PWR_CTRL_PWR12_ON_SHIFT                                8
#define ST_DAC_PWR_CTRL_PWR12_ON_RAWMSK                               0x1
#define ST_DAC_PWR_CTRL_PWR12_ON_MASK                                 \
  (ST_DAC_PWR_CTRL_PWR12_ON_RAWMSK << ST_DAC_PWR_CTRL_PWR12_ON_SHIFT )
#define DAC_PWR_CTRL_ISO_MANU                                         BIT(3)
#define DAC_PWR_CTRL_ISO_MANU_SHIFT                                   3
#define DAC_PWR_CTRL_ISO_MANU_RAWMSK                                  0x1
#define DAC_PWR_CTRL_ISO_MANU_MASK                                    \
  (DAC_PWR_CTRL_ISO_MANU_RAWMSK << DAC_PWR_CTRL_ISO_MANU_SHIFT )
#define DAC_PWR_CTRL_PWR33_MANU                                       BIT(2)
#define DAC_PWR_CTRL_PWR33_MANU_SHIFT                                 2
#define DAC_PWR_CTRL_PWR33_MANU_RAWMSK                                0x1
#define DAC_PWR_CTRL_PWR33_MANU_MASK                                  \
  (DAC_PWR_CTRL_PWR33_MANU_RAWMSK << DAC_PWR_CTRL_PWR33_MANU_SHIFT )
#define DAC_PWR_CTRL_PWR12_MANU                                       BIT(1)
#define DAC_PWR_CTRL_PWR12_MANU_SHIFT                                 1
#define DAC_PWR_CTRL_PWR12_MANU_RAWMSK                                0x1
#define DAC_PWR_CTRL_PWR12_MANU_MASK                                  \
  (DAC_PWR_CTRL_PWR12_MANU_RAWMSK << DAC_PWR_CTRL_PWR12_MANU_SHIFT )
#define DAC_PWR_CTRL_AUTO                                             BIT(0)
#define DAC_PWR_CTRL_AUTO_SHIFT                                       0
#define DAC_PWR_CTRL_AUTO_RAWMSK                                      0x1
#define DAC_PWR_CTRL_AUTO_MASK                                        \
  (DAC_PWR_CTRL_AUTO_RAWMSK << DAC_PWR_CTRL_AUTO_SHIFT )
#define DAC_ANAPAR_DA0_PWR_ALL_CNTR_SHIFT                             12
#define DAC_ANAPAR_DA0_PWR_ALL_CNTR_RAWMSK                            0xfffff
#define DAC_ANAPAR_DA0_PWR_ALL_CNTR_MASK                              \
  (DAC_ANAPAR_DA0_PWR_ALL_CNTR_RAWMSK << DAC_ANAPAR_DA0_PWR_ALL_CNTR_SHIFT )
#define DAC_ANAPAR_DA0_PWR_ALL_CNTR(x)                                \
  (((x) & DAC_ANAPAR_DA0_PWR_ALL_CNTR_RAWMSK) << DAC_ANAPAR_DA0_PWR_ALL_CNTR_SHIFT)
#define DAC_ANAPAR_DA0_PWR_FUP_CNTR_SHIFT                             0
#define DAC_ANAPAR_DA0_PWR_FUP_CNTR_RAWMSK                            0xfff
#define DAC_ANAPAR_DA0_PWR_FUP_CNTR_MASK                              \
  (DAC_ANAPAR_DA0_PWR_FUP_CNTR_RAWMSK << DAC_ANAPAR_DA0_PWR_FUP_CNTR_SHIFT )
#define DAC_ANAPAR_DA0_PWR_FUP_CNTR(x)                                \
  (((x) & DAC_ANAPAR_DA0_PWR_FUP_CNTR_RAWMSK) << DAC_ANAPAR_DA0_PWR_FUP_CNTR_SHIFT)
#define DAC_ANAPAR_DA1_FUP_EN                                         BIT(31)
#define DAC_ANAPAR_DA1_FUP_EN_SHIFT                                   31
#define DAC_ANAPAR_DA1_FUP_EN_RAWMSK                                  0x1
#define DAC_ANAPAR_DA1_FUP_EN_MASK                                    \
  (DAC_ANAPAR_DA1_FUP_EN_RAWMSK << DAC_ANAPAR_DA1_FUP_EN_SHIFT )
#define DAC_ANAPAR_DA1_ANAPAR_DA_SHIFT                                8
#define DAC_ANAPAR_DA1_ANAPAR_DA_RAWMSK                               0x7fffff
#define DAC_ANAPAR_DA1_ANAPAR_DA_MASK                                 \
  (DAC_ANAPAR_DA1_ANAPAR_DA_RAWMSK << DAC_ANAPAR_DA1_ANAPAR_DA_SHIFT )
#define DAC_ANAPAR_DA1_ANAPAR_DA(x)                                   \
  (((x) & DAC_ANAPAR_DA1_ANAPAR_DA_RAWMSK) << DAC_ANAPAR_DA1_ANAPAR_DA_SHIFT)
#define DAC_ANAPAR_DA1_D_POW_DACVREF                                  BIT(7)
#define DAC_ANAPAR_DA1_D_POW_DACVREF_SHIFT                            7
#define DAC_ANAPAR_DA1_D_POW_DACVREF_RAWMSK                           0x1
#define DAC_ANAPAR_DA1_D_POW_DACVREF_MASK                             \
  (DAC_ANAPAR_DA1_D_POW_DACVREF_RAWMSK << DAC_ANAPAR_DA1_D_POW_DACVREF_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_VREF2                                    BIT(6)
#define DAC_ANAPAR_DA1_D_POW_VREF2_SHIFT                              6
#define DAC_ANAPAR_DA1_D_POW_VREF2_RAWMSK                             0x1
#define DAC_ANAPAR_DA1_D_POW_VREF2_MASK                               \
  (DAC_ANAPAR_DA1_D_POW_VREF2_RAWMSK << DAC_ANAPAR_DA1_D_POW_VREF2_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_MBIAS                                    BIT(5)
#define DAC_ANAPAR_DA1_D_POW_MBIAS_SHIFT                              5
#define DAC_ANAPAR_DA1_D_POW_MBIAS_RAWMSK                             0x1
#define DAC_ANAPAR_DA1_D_POW_MBIAS_MASK                               \
  (DAC_ANAPAR_DA1_D_POW_MBIAS_RAWMSK << DAC_ANAPAR_DA1_D_POW_MBIAS_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_DIV4                                     BIT(4)
#define DAC_ANAPAR_DA1_D_POW_DIV4_SHIFT                               4
#define DAC_ANAPAR_DA1_D_POW_DIV4_RAWMSK                              0x1
#define DAC_ANAPAR_DA1_D_POW_DIV4_MASK                                \
  (DAC_ANAPAR_DA1_D_POW_DIV4_RAWMSK << DAC_ANAPAR_DA1_D_POW_DIV4_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_DF1SE_R                                  BIT(3)
#define DAC_ANAPAR_DA1_D_POW_DF1SE_R_SHIFT                            3
#define DAC_ANAPAR_DA1_D_POW_DF1SE_R_RAWMSK                           0x1
#define DAC_ANAPAR_DA1_D_POW_DF1SE_R_MASK                             \
  (DAC_ANAPAR_DA1_D_POW_DF1SE_R_RAWMSK << DAC_ANAPAR_DA1_D_POW_DF1SE_R_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_DF2SE_L                                  BIT(2)
#define DAC_ANAPAR_DA1_D_POW_DF2SE_L_SHIFT                            2
#define DAC_ANAPAR_DA1_D_POW_DF2SE_L_RAWMSK                           0x1
#define DAC_ANAPAR_DA1_D_POW_DF2SE_L_MASK                             \
  (DAC_ANAPAR_DA1_D_POW_DF2SE_L_RAWMSK << DAC_ANAPAR_DA1_D_POW_DF2SE_L_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_DAC_R                                    BIT(1)
#define DAC_ANAPAR_DA1_D_POW_DAC_R_SHIFT                              1
#define DAC_ANAPAR_DA1_D_POW_DAC_R_RAWMSK                             0x1
#define DAC_ANAPAR_DA1_D_POW_DAC_R_MASK                               \
  (DAC_ANAPAR_DA1_D_POW_DAC_R_RAWMSK << DAC_ANAPAR_DA1_D_POW_DAC_R_SHIFT )
#define DAC_ANAPAR_DA1_D_POW_DAC_L                                    BIT(0)
#define DAC_ANAPAR_DA1_D_POW_DAC_L_SHIFT                              0
#define DAC_ANAPAR_DA1_D_POW_DAC_L_RAWMSK                             0x1
#define DAC_ANAPAR_DA1_D_POW_DAC_L_MASK                               \
  (DAC_ANAPAR_DA1_D_POW_DAC_L_RAWMSK << DAC_ANAPAR_DA1_D_POW_DAC_L_SHIFT )

#define GDMA_CTL_LO_INT_EN_SHIFT                                      0
#define GDMA_CTL_LO_INT_EN_RAWMSK                                     0x1
#define GDMA_CTL_LO_INT_EN_MASK                                       \
  GDMA_CTL_LO_INT_EN_RAWMSK << GDMA_CTL_LO_INT_EN_SHIFT )
#define GDMA_CTL_LO_INT_EN(x)                                         \
  ((x) & GDMA_CTL_LO_INT_EN_RAWMSK) << GDMA_CTL_LO_INT_EN_SHIFT)
#define GDMA_CTL_LO_DST_TR_WIDTH_SHIFT                                1
#define GDMA_CTL_LO_DST_TR_WIDTH_RAWMSK                               0x7
#define GDMA_CTL_LO_DST_TR_WIDTH_MASK                                 \
  GDMA_CTL_LO_DST_TR_WIDTH_RAWMSK << GDMA_CTL_LO_DST_TR_WIDTH_SHIFT )
#define GDMA_CTL_LO_DST_TR_WIDTH(x)                                   \
  ((x) & GDMA_CTL_LO_DST_TR_WIDTH_RAWMSK) << GDMA_CTL_LO_DST_TR_WIDTH_SHIFT)
#define GDMA_CTL_LO_SRC_TR_WIDTH_SHIFT                                4
#define GDMA_CTL_LO_SRC_TR_WIDTH_RAWMSK                               0x7
#define GDMA_CTL_LO_SRC_TR_WIDTH_MASK                                 \
  GDMA_CTL_LO_SRC_TR_WIDTH_RAWMSK << GDMA_CTL_LO_SRC_TR_WIDTH_SHIFT )
#define GDMA_CTL_LO_SRC_TR_WIDTH(x)                                   \
  ((x) & GDMA_CTL_LO_SRC_TR_WIDTH_RAWMSK) << GDMA_CTL_LO_SRC_TR_WIDTH_SHIFT)
#define GDMA_CTL_LO_DINC_SHIFT                                        7
#define GDMA_CTL_LO_DINC_RAWMSK                                       0x3
#define GDMA_CTL_LO_DINC_MASK                                         \
  GDMA_CTL_LO_DINC_RAWMSK << GDMA_CTL_LO_DINC_SHIFT )
#define GDMA_CTL_LO_DINC(x)                                           \
  ((x) & GDMA_CTL_LO_DINC_RAWMSK) << GDMA_CTL_LO_DINC_SHIFT)
#define GDMA_CTL_LO_SINC_SHIFT                                        9
#define GDMA_CTL_LO_SINC_RAWMSK                                       0x3
#define GDMA_CTL_LO_SINC_MASK                                         \
  GDMA_CTL_LO_SINC_RAWMSK << GDMA_CTL_LO_SINC_SHIFT )
#define GDMA_CTL_LO_SINC(x)                                           \
  ((x) & GDMA_CTL_LO_SINC_RAWMSK) << GDMA_CTL_LO_SINC_SHIFT)
#define GDMA_CTL_LO_DEST_MSIZE_SHIFT                                  11
#define GDMA_CTL_LO_DEST_MSIZE_RAWMSK                                 0x7
#define GDMA_CTL_LO_DEST_MSIZE_MASK                                   \
  GDMA_CTL_LO_DEST_MSIZE_RAWMSK << GDMA_CTL_LO_DEST_MSIZE_SHIFT )
#define GDMA_CTL_LO_DEST_MSIZE(x)                                     \
  ((x) & GDMA_CTL_LO_DEST_MSIZE_RAWMSK) << GDMA_CTL_LO_DEST_MSIZE_SHIFT)
#define GDMA_CTL_LO_SRC_MSIZE_SHIFT                                   14
#define GDMA_CTL_LO_SRC_MSIZE_RAWMSK                                  0x7
#define GDMA_CTL_LO_SRC_MSIZE_MASK                                    \
  GDMA_CTL_LO_SRC_MSIZE_RAWMSK << GDMA_CTL_LO_SRC_MSIZE_SHIFT )
#define GDMA_CTL_LO_SRC_MSIZE(x)                                      \
  ((x) & GDMA_CTL_LO_SRC_MSIZE_RAWMSK) << GDMA_CTL_LO_SRC_MSIZE_SHIFT)
#define GDMA_CTL_LO_SRC_GATHER_EN_SHIFT                               17
#define GDMA_CTL_LO_SRC_GATHER_EN_RAWMSK                              0x1
#define GDMA_CTL_LO_SRC_GATHER_EN_MASK                                \
  GDMA_CTL_LO_SRC_GATHER_EN_RAWMSK << GDMA_CTL_LO_SRC_GATHER_EN_SHIFT )
#define GDMA_CTL_LO_SRC_GATHER_EN(x)                                  \
  ((x) & GDMA_CTL_LO_SRC_GATHER_EN_RAWMSK) << GDMA_CTL_LO_SRC_GATHER_EN_SHIFT)
#define GDMA_CTL_LO_DST_SCATTER_EN_SHIFT                              18
#define GDMA_CTL_LO_DST_SCATTER_EN_RAWMSK                             0x1
#define GDMA_CTL_LO_DST_SCATTER_EN_MASK                               \
  GDMA_CTL_LO_DST_SCATTER_EN_RAWMSK << GDMA_CTL_LO_DST_SCATTER_EN_SHIFT )
#define GDMA_CTL_LO_DST_SCATTER_EN(x)                                 \
  ((x) & GDMA_CTL_LO_DST_SCATTER_EN_RAWMSK) << GDMA_CTL_LO_DST_SCATTER_EN_SHIFT)
#define GDMA_CTL_LO_TT_FC_SHIFT                                       20
#define GDMA_CTL_LO_TT_FC_RAWMSK                                      0x7
#define GDMA_CTL_LO_TT_FC_MASK                                        \
  GDMA_CTL_LO_TT_FC_RAWMSK << GDMA_CTL_LO_TT_FC_SHIFT )
#define GDMA_CTL_LO_TT_FC(x)                                          \
  ((x) & GDMA_CTL_LO_TT_FC_RAWMSK) << GDMA_CTL_LO_TT_FC_SHIFT)
#define GDMA_CTL_LO_DMS_SHIFT                                         23
#define GDMA_CTL_LO_DMS_RAWMSK                                        0x3
#define GDMA_CTL_LO_DMS_MASK                                          \
  GDMA_CTL_LO_DMS_RAWMSK << GDMA_CTL_LO_DMS_SHIFT )
#define GDMA_CTL_LO_DMS(x)                                            \
  ((x) & GDMA_CTL_LO_DMS_RAWMSK) << GDMA_CTL_LO_DMS_RAWMSK)
#define GDMA_CTL_LO_SMS_SHIFT                                         25
#define GDMA_CTL_LO_SMS_RAWMSK                                        0x3
#define GDMA_CTL_LO_SMS_MASK                                          \
  GDMA_CTL_LO_SMS_RAWMSK << GDMA_CTL_LO_SMS_SHIFT )
#define GDMA_CTL_LO_SMS(x)                                            \
  ((x) & GDMA_CTL_LO_SMS_RAWMSK) << GDMA_CTL_LO_SMS_SHIFT)
#define GDMA_CTL_LO_LLP_DST_EN_SHIFT                                  27
#define GDMA_CTL_LO_LLP_DST_EN_RAWMSK                                 0x1
#define GDMA_CTL_LO_LLP_DST_EN_MASK                                   \
  GDMA_CTL_LO_LLP_DST_EN_RAWMSK << GDMA_CTL_LO_LLP_DST_EN_SHIFT )
#define GDMA_CTL_LO_LLP_DST_EN(x)                                     \
  ((x) & GDMA_CTL_LO_LLP_DST_EN_RAWMSK) << GDMA_CTL_LO_LLP_DST_EN_SHIFT)
#define GDMA_CTL_LO_LLP_SRC_EN_SHIFT                                  28
#define GDMA_CTL_LO_LLP_SRC_EN_RAWMSK                                 0x1
#define GDMA_CTL_LO_LLP_SRC_EN_MASK                                   \
  GDMA_CTL_LO_LLP_SRC_EN_RAWMSK << GDMA_CTL_LO_LLP_SRC_EN_SHIFT )
#define GDMA_CTL_LO_LLP_SRC_EN(x)                                     \
  ((x) & GDMA_CTL_LO_LLP_SRC_EN_RAWMSK) << GDMA_CTL_LO_LLP_SRC_EN_SHIFT)
#define GDMA_CTL_UP_BLOCK_BS_SHIFT                                    0
#define GDMA_CTL_UP_BLOCK_BS_RAWMSK                                   0xFFF
#define GDMA_CTL_UP_BLOCK_BS_MASK                                     \
  GDMA_CTL_UP_BLOCK_BS_RAWMSK << GDMA_CTL_UP_BLOCK_BS_SHIFT )
#define GDMA_CTL_UP_BLOCK_BS(x)                                       \
  ((x) & GDMA_CTL_UP_BLOCK_BS_RAWMSK) << GDMA_CTL_UP_BLOCK_BS_SHIFT)
#define GDMA_CTL_UP_DONE_SHIFT                                        12
#define GDMA_CTL_UP_DONE_RAWMSK                                       0x1
#define GDMA_CTL_UP_DONE_MASK                                         \
  GDMA_CTL_UP_DONE_RAWMSK << GDMA_CTL_UP_DONE_SHIFT )
#define GDMA_CTL_UP_DONE(x)                                           \
  ((x) & GDMA_CTL_UP_DONE_RAWMSK) << GDMA_CTL_UP_DONE_SHIFT)
#define GDMA_CFG_LO_CH_PRIOR_SHIFT                                    5
#define GDMA_CFG_LO_CH_PRIOR_RAWMSK                                   0x7
#define GDMA_CFG_LO_CH_PRIOR_MASK                                     \
  GDMA_CFG_LO_CH_PRIOR_RAWMSK << GDMA_CFG_LO_CH_PRIOR_SHIFT )
#define GDMA_CFG_LO_CH_PRIOR(x)                                       \
  ((x) & GDMA_CFG_LO_CH_PRIOR_RAWMSK) << GDMA_CFG_LO_CH_PRIOR_SHIFT)
#define GDMA_CFG_LO_CH_SUSP_SHIFT                                     8
#define GDMA_CFG_LO_CH_SUSP_RAWMSK                                    0x1
#define GDMA_CFG_LO_CH_SUSP_MASK                                      \
  GDMA_CFG_LO_CH_SUSP_RAWMSK << GDMA_CFG_LO_CH_SUSP_SHIFT )
#define GDMA_CFG_LO_CH_SUSP(x)                                        \
  ((x) & GDMA_CFG_LO_CH_SUSP_RAWMSK) << GDMA_CFG_LO_CH_SUSP_SHIFT)
#define GDMA_CFG_LO_FIFO_EMPTY_SHIFT                                  9
#define GDMA_CFG_LO_FIFO_EMPTY_RAWMSK                                 0x1
#define GDMA_CFG_LO_FIFO_EMPTY_MASK                                   \
  GDMA_CFG_LO_FIFO_EMPTY_RAWMSK << GDMA_CFG_LO_FIFO_EMPTY_SHIFT )
#define GDMA_CFG_LO_FIFO_EMPTY(x)                                     \
  ((x) & GDMA_CFG_LO_FIFO_EMPTY_RAWMSK) << GDMA_CFG_LO_FIFO_EMPTY_SHIFT)
#define GDMA_CFG_LO_HS_SEL_DST_SHIFT                                  10
#define GDMA_CFG_LO_HS_SEL_DST_RAWMSK                                 0x1
#define GDMA_CFG_LO_HS_SEL_DST_MASK                                   \
  GDMA_CFG_LO_HS_SEL_DST_RAWMSK << GDMA_CFG_LO_HS_SEL_DST_SHIFT )
#define GDMA_CFG_LO_HS_SEL_DST(x)                                     \
  ((x) & GDMA_CFG_LO_HS_SEL_DST_RAWMSK) << GDMA_CFG_LO_HS_SEL_DST_SHIFT)
#define GDMA_CFG_LO_HS_SEL_SRC_SHIFT                                  11
#define GDMA_CFG_LO_HS_SEL_SRC_RAWMSK                                 0x1
#define GDMA_CFG_LO_HS_SEL_SRC_MASK                                   \
  GDMA_CFG_LO_HS_SEL_SRC_RAWMSK << GDMA_CFG_LO_HS_SEL_SRC_SHIFT )
#define GDMA_CFG_LO_HS_SEL_SRC(x)                                     \
  ((x) & GDMA_CFG_LO_HS_SEL_SRC_RAWMSK) << GDMA_CFG_LO_HS_SEL_SRC_SHIFT)
#define GDMA_CFG_LO_LOCK_CH_L_SHIFT                                   12
#define GDMA_CFG_LO_LOCK_CH_L_RAWMSK                                  0x3
#define GDMA_CFG_LO_LOCK_CH_L_MASK                                    \
  GDMA_CFG_LO_LOCK_CH_L_RAWMSK << GDMA_CFG_LO_LOCK_CH_L_SHIFT )
#define GDMA_CFG_LO_LOCK_CH_L(x)                                      \
  ((x) & GDMA_CFG_LO_LOCK_CH_L_RAWMSK) << GDMA_CFG_LO_LOCK_CH_L_SHIFT)
#define GDMA_CFG_LO_LOCK_B_L_SHIFT                                    14
#define GDMA_CFG_LO_LOCK_B_L_RAWMSK                                   0x3
#define GDMA_CFG_LO_LOCK_B_L_MASK                                     \
  GDMA_CFG_LO_LOCK_B_L_RAWMSK << GDMA_CFG_LO_LOCK_B_L_SHIFT )
#define GDMA_CFG_LO_LOCK_B_L(x)                                       \
  ((x) & GDMA_CFG_LO_LOCK_B_L_RAWMSK) << GDMA_CFG_LO_LOCK_B_L_SHIFT)
#define GDMA_CFG_LO_LOCK_CH_SHIFT                                     16
#define GDMA_CFG_LO_LOCK_CH_RAWMSK                                    0x1
#define GDMA_CFG_LO_LOCK_CH_MASK                                      \
  GDMA_CFG_LO_LOCK_CH_RAWMSK << GDMA_CFG_LO_LOCK_CH_SHIFT )
#define GDMA_CFG_LO_LOCK_CH(x)                                        \
  ((x) & GDMA_CFG_LO_LOCK_CH_RAWMSK) << GDMA_CFG_LO_LOCK_CH_SHIFT)
#define GDMA_CFG_LO_LOCK_B_SHIFT                                      17
#define GDMA_CFG_LO_LOCK_B_RAWMSK                                     0x1
#define GDMA_CFG_LO_LOCK_B_MASK                                       \
  GDMA_CFG_LO_LOCK_B_RAWMSK << GDMA_CFG_LO_LOCK_B_SHIFT )
#define GDMA_CFG_LO_LOCK_B(x)                                         \
  ((x) & GDMA_CFG_LO_LOCK_B_RAWMSK) << GDMA_CFG_LO_LOCK_B_SHIFT)
#define GDMA_CFG_LO_DST_HS_POL_SHIFT                                  18
#define GDMA_CFG_LO_DST_HS_POL_RAWMSK                                 0x1
#define GDMA_CFG_LO_DST_HS_POL_MASK                                   \
  GDMA_CFG_LO_DST_HS_POL_RAWMSK << GDMA_CFG_LO_DST_HS_POL_SHIFT )
#define GDMA_CFG_LO_DST_HS_POL(x)                                     \
  ((x) & GDMA_CFG_LO_DST_HS_POL_RAWMSK) << GDMA_CFG_LO_DST_HS_POL_SHIFT)
#define GDMA_CFG_LO_SRC_HS_POL_SHIFT                                  19
#define GDMA_CFG_LO_SRC_HS_POL_RAWMSK                                 0x1
#define GDMA_CFG_LO_SRC_HS_POL_MASK                                   \
  GDMA_CFG_LO_SRC_HS_POL_RAWMSK << GDMA_CFG_LO_SRC_HS_POL_SHIFT )
#define GDMA_CFG_LO_SRC_HS_POL(x)                                     \
  ((x) & GDMA_CFG_LO_SRC_HS_POL_RAWMSK) << GDMA_CFG_LO_SRC_HS_POL_SHIFT)
#define GDMA_CFG_LO_MAX_ABRST_SHIFT                                   20
#define GDMA_CFG_LO_MAX_ABRST_RAWMSK                                  0x3FF
#define GDMA_CFG_LO_MAX_ABRST_MASK                                    \
  GDMA_CFG_LO_MAX_ABRST_RAWMSK << GDMA_CFG_LO_MAX_ABRST_SHIFT )
#define GDMA_CFG_LO_MAX_ABRST(x)                                      \
  ((x) & GDMA_CFG_LO_MAX_ABRST_RAWMSK) << GDMA_CFG_LO_MAX_ABRST_SHIFT)
#define GDMA_CFG_LO_RELOAD_SRC_SHIFT                                  30
#define GDMA_CFG_LO_RELOAD_SRC_RAWMSK                                 0x1
#define GDMA_CFG_LO_RELOAD_SRC_MASK                                   \
  GDMA_CFG_LO_RELOAD_SRC_RAWMSK << GDMA_CFG_LO_RELOAD_SRC_SHIFT )
#define GDMA_CFG_LO_RELOAD_SRC(x)                                     \
  ((x) & GDMA_CFG_LO_RELOAD_SRC_RAWMSK) << GDMA_CFG_LO_RELOAD_SRC_SHIFT)
#define GDMA_CFG_LO_RELOAD_DST_SHIFT                                  31
#define GDMA_CFG_LO_RELOAD_DST_RAWMSK                                 0x1
#define GDMA_CFG_LO_RELOAD_DST_MASK                                   \
  GDMA_CFG_LO_RELOAD_DST_RAWMSK << GDMA_CFG_LO_RELOAD_DST_SHIFT )
#define GDMA_CFG_LO_RELOAD_DST(x)                                     \
  ((x) & GDMA_CFG_LO_RELOAD_DST_RAWMSK) << GDMA_CFG_LO_RELOAD_DST_SHIFT)
#define GDMA_CFG_UP_FCMODE_SHIFT                                      0
#define GDMA_CFG_UP_FCMODE_RAWMSK                                     0x1
#define GDMA_CFG_UP_FCMODE_MASK                                       \
  GDMA_CFG_UP_FCMODE_RAWMSK << GDMA_CFG_UP_FCMODE_SHIFT )
#define GDMA_CFG_UP_FCMODE(x)                                         \
  ((x) & GDMA_CFG_UP_FCMODE_RAWMSK) << GDMA_CFG_UP_FCMODE_SHIFT)
#define GDMA_CFG_UP_FIFO_MODE_SHIFT                                   1
#define GDMA_CFG_UP_FIFO_MODE_RAWMSK                                  0x1
#define GDMA_CFG_UP_FIFO_MODE_MASK                                    \
  GDMA_CFG_UP_FIFO_MODE_RAWMSK << GDMA_CFG_UP_FIFO_MODE_SHIFT )
#define GDMA_CFG_UP_FIFO_MODE(x)                                      \
  ((x) & GDMA_CFG_UP_FIFO_MODE_RAWMSK) << GDMA_CFG_UP_FIFO_MODE_SHIFT)
#define GDMA_CFG_UP_PROTCTL_SHIFT                                     2
#define GDMA_CFG_UP_PROTCTL_RAWMSK                                    0x7
#define GDMA_CFG_UP_PROTCTL_MASK                                      \
  GDMA_CFG_UP_PROTCTL_RAWMSK << GDMA_CFG_UP_PROTCTL_SHIFT )
#define GDMA_CFG_UP_PROTCTL(x)                                        \
  ((x) & GDMA_CFG_UP_PROTCTL_RAWMSK) << GDMA_CFG_UP_PROTCTL_SHIFT)
#define GDMA_CFG_UP_DS_UPD_EN_SHIFT                                   5
#define GDMA_CFG_UP_DS_UPD_EN_RAWMSK                                  0x1
#define GDMA_CFG_UP_DS_UPD_EN_MASK                                    \
  GDMA_CFG_UP_DS_UPD_EN_RAWMSK << GDMA_CFG_UP_DS_UPD_EN_SHIFT )
#define GDMA_CFG_UP_DS_UPD_EN(x)                                      \
  ((x) & GDMA_CFG_UP_DS_UPD_EN_RAWMSK) << GDMA_CFG_UP_DS_UPD_EN_SHIFT)
#define GDMA_CFG_UP_SS_UPD_EN_SHIFT                                   6
#define GDMA_CFG_UP_SS_UPD_EN_RAWMSK                                  0x1
#define GDMA_CFG_UP_SS_UPD_EN_MASK                                    \
  GDMA_CFG_UP_SS_UPD_EN_RAWMSK << GDMA_CFG_UP_SS_UPD_EN_SHIFT )
#define GDMA_CFG_UP_SS_UPD_EN(x)                                      \
  ((x) & GDMA_CFG_UP_SS_UPD_EN_RAWMSK) << GDMA_CFG_UP_SS_UPD_EN_SHIFT)
#define GDMA_CFG_UP_SRC_PER_SHIFT                                     7
#define GDMA_CFG_UP_SRC_PER_RAWMSK                                    0xF
#define GDMA_CFG_UP_SRC_PER_MASK                                      \
  GDMA_CFG_UP_SRC_PER_RAWMSK << GDMA_CFG_UP_SRC_PER_SHIFT )
#define GDMA_CFG_UP_SRC_PER(x)                                        \
  ((x) & GDMA_CFG_UP_SRC_PER_RAWMSK) << GDMA_CFG_UP_SRC_PER_SHIFT)
#define GDMA_CFG_UP_DEST_PER_SHIFT                                    11
#define GDMA_CFG_UP_DEST_PER_RAWMSK                                   0xF
#define GDMA_CFG_UP_DEST_PER_MASK                                     \
  GDMA_CFG_UP_DEST_PER_RAWMSK << GDMA_CFG_UP_DEST_PER_SHIFT )
#define GDMA_CFG_UP_DEST_PER(x)                                       \
  ((x) & GDMA_CFG_UP_DEST_PER_RAWMSK) << GDMA_CFG_UP_DEST_PER_SHIFT)

#define I2C_CON_IC_SLAVE_DISABLE                                      BIT(6)
#define I2C_CON_IC_SLAVE_DISABLE_SHIFT                                6
#define I2C_CON_IC_SLAVE_DISABLE_RAWMSK                               0x1
#define I2C_CON_IC_SLAVE_DISABLE_MASK                                 \
  I2C_CON_IC_SLAVE_DISABLE_RAWMSK << I2C_CON_IC_SLAVE_DISABLE_SHIFT )
#define I2C_CON_IC_RESTART_EN                                         BIT(5)
#define I2C_CON_IC_RESTART_EN_SHIFT                                   5
#define I2C_CON_IC_RESTART_EN_RAWMSK                                  0x1
#define I2C_CON_IC_RESTART_EN_MASK                                    \
  I2C_CON_IC_RESTART_EN_RAWMSK << I2C_CON_IC_RESTART_EN_SHIFT )
#define I2C_CON_IC_10BITADDR_MASTER                                   BIT(4)
#define I2C_CON_IC_10BITADDR_MASTER_SHIFT                             4
#define I2C_CON_IC_10BITADDR_MASTER_RAWMSK                            0x1
#define I2C_CON_IC_10BITADDR_MASTER_MASK                              \
  I2C_CON_IC_10BITADDR_MASTER_RAWMSK << I2C_CON_IC_10BITADDR_MASTER_SHIFT )
#define I2C_CON_IC_10BITADDR_SLAVE                                    BIT(3)
#define I2C_CON_IC_10BITADDR_SLAVE_SHIFT                              3
#define I2C_CON_IC_10BITADDR_SLAVE_RAWMSK                             0x1
#define I2C_CON_IC_10BITADDR_SLAVE_MASK                               \
  I2C_CON_IC_10BITADDR_SLAVE_RAWMSK << I2C_CON_IC_10BITADDR_SLAVE_SHIFT )
#define I2C_CON_SPEED_SHIFT                                           1
#define I2C_CON_SPEED_RAWMSK                                          0x3
#define I2C_CON_SPEED_MASK                                            \
  I2C_CON_SPEED_RAWMSK << I2C_CON_SPEED_SHIFT )
#define I2C_CON_SPEED(x)                                              \
  ((x) & I2C_CON_SPEED_RAWMSK) << I2C_CON_SPEED_SHIFT)
#define I2C_CON_MASTER_MODE                                           BIT(0)
#define I2C_CON_MASTER_MODE_SHIFT                                     0
#define I2C_CON_MASTER_MODE_RAWMSK                                    0x1
#define I2C_CON_MASTER_MODE_MASK                                      \
  I2C_CON_MASTER_MODE_RAWMSK << I2C_CON_MASTER_MODE_SHIFT )
#define I2C_TAR_IC_10BITADDR_MASTER                                   BIT(12)
#define I2C_TAR_IC_10BITADDR_MASTER_SHIFT                             12
#define I2C_TAR_IC_10BITADDR_MASTER_RAWMSK                            0x1
#define I2C_TAR_IC_10BITADDR_MASTER_MASK                              \
  I2C_TAR_IC_10BITADDR_MASTER_RAWMSK << I2C_TAR_IC_10BITADDR_MASTER_SHIFT )
#define I2C_TAR_SPECIAL                                               BIT(11)
#define I2C_TAR_SPECIAL_SHIFT                                         11
#define I2C_TAR_SPECIAL_RAWMSK                                        0x1
#define I2C_TAR_SPECIAL_MASK                                          \
  I2C_TAR_SPECIAL_RAWMSK << I2C_TAR_SPECIAL_SHIFT )
#define I2C_TAR_GC_OR_START                                           BIT(10)
#define I2C_TAR_GC_OR_START_SHIFT                                     10
#define I2C_TAR_GC_OR_START_RAWMSK                                    0x1
#define I2C_TAR_GC_OR_START_MASK                                      \
  I2C_TAR_GC_OR_START_RAWMSK << I2C_TAR_GC_OR_START_SHIFT )
#define I2C_TAR_SHIFT                                                 0
#define I2C_TAR_RAWMSK                                                0x3ff
#define I2C_TAR_MASK                                                  \
  I2C_TAR_RAWMSK << I2C_TAR_SHIFT )
#define I2C_TAR(x)                                                    \
  ((x) & I2C_TAR_RAWMSK) << I2C_TAR_SHIFT)
#define I2C_SAR_SHIFT                                                 0
#define I2C_SAR_RAWMSK                                                0x3ff
#define I2C_SAR_MASK                                                  \
  I2C_SAR_RAWMSK << I2C_SAR_SHIFT )
#define I2C_SAR(x)                                                    \
  ((x) & I2C_SAR_RAWMSK) << I2C_SAR_SHIFT)
#define I2C_HS_MADDR_SHIFT                                            0
#define I2C_HS_MADDR_RAWMSK                                           0x7
#define I2C_HS_MADDR_MASK                                             \
  I2C_HS_MADDR_RAWMSK << I2C_HS_MADDR_SHIFT )
#define I2C_HS_MADDR(x)                                               \
  ((x) & I2C_HS_MADDR_RAWMSK) << I2C_HS_MADDR_SHIFT)
#define I2C_DATA_CMD_RESTART                                          BIT(10)
#define I2C_DATA_CMD_RESTART_SHIFT                                    10
#define I2C_DATA_CMD_RESTART_RAWMSK                                   0x1
#define I2C_DATA_CMD_RESTART_MASK                                     \
  I2C_DATA_CMD_RESTART_RAWMSK << I2C_DATA_CMD_RESTART_SHIFT )
#define I2C_DATA_CMD_STOP                                             BIT(9)
#define I2C_DATA_CMD_STOP_SHIFT                                       9
#define I2C_DATA_CMD_STOP_RAWMSK                                      0x1
#define I2C_DATA_CMD_STOP_MASK                                        \
  I2C_DATA_CMD_STOP_RAWMSK << I2C_DATA_CMD_STOP_SHIFT )
#define I2C_DATA_CMD_CMD                                              BIT(8)
#define I2C_DATA_CMD_CMD_SHIFT                                        8
#define I2C_DATA_CMD_CMD_RAWMSK                                       0x1
#define I2C_DATA_CMD_CMD_MASK                                         \
  I2C_DATA_CMD_CMD_RAWMSK << I2C_DATA_CMD_CMD_SHIFT )
#define I2C_DATA_CMD_DAT_SHIFT                                        0
#define I2C_DATA_CMD_DAT_RAWMSK                                       0xff
#define I2C_DATA_CMD_DAT_MASK                                         \
  I2C_DATA_CMD_DAT_RAWMSK << I2C_DATA_CMD_DAT_SHIFT )
#define I2C_DATA_CMD_DAT(x)                                           \
  ((x) & I2C_DATA_CMD_DAT_RAWMSK) << I2C_DATA_CMD_DAT_SHIFT)
#define I2C_SS_SCL_HCNT_SHIFT                                         0
#define I2C_SS_SCL_HCNT_RAWMSK                                        0xffff
#define I2C_SS_SCL_HCNT_MASK                                          \
  I2C_SS_SCL_HCNT_RAWMSK << I2C_SS_SCL_HCNT_SHIFT )
#define I2C_SS_SCL_HCNT(x)                                            \
  ((x) & I2C_SS_SCL_HCNT_RAWMSK) << I2C_SS_SCL_HCNT_SHIFT)
#define I2C_SS_SCL_LCNT_SHIFT                                         0
#define I2C_SS_SCL_LCNT_RAWMSK                                        0xffff
#define I2C_SS_SCL_LCNT_MASK                                          \
  I2C_SS_SCL_LCNT_RAWMSK << I2C_SS_SCL_LCNT_SHIFT )
#define I2C_SS_SCL_LCNT(x)                                            \
  ((x) & I2C_SS_SCL_LCNT_RAWMSK) << I2C_SS_SCL_LCNT_SHIFT)
#define I2C_FS_SCL_HCNT_SHIFT                                         0
#define I2C_FS_SCL_HCNT_RAWMSK                                        0xffff
#define I2C_FS_SCL_HCNT_MASK                                          \
  I2C_FS_SCL_HCNT_RAWMSK << I2C_FS_SCL_HCNT_SHIFT )
#define I2C_FS_SCL_HCNT(x)                                            \
  ((x) & I2C_FS_SCL_HCNT_RAWMSK) << I2C_FS_SCL_HCNT_SHIFT)
#define I2C_FS_SCL_LCNT_SHIFT                                         0
#define I2C_FS_SCL_LCNT_RAWMSK                                        0xffff
#define I2C_FS_SCL_LCNT_MASK                                          \
  I2C_FS_SCL_LCNT_RAWMSK << I2C_FS_SCL_LCNT_SHIFT )
#define I2C_FS_SCL_LCNT(x)                                            \
  ((x) & I2C_FS_SCL_LCNT_RAWMSK) << I2C_FS_SCL_LCNT_SHIFT)
#define I2C_HS_SCL_HCNT_SHIFT                                         0
#define I2C_HS_SCL_HCNT_RAWMSK                                        0xffff
#define I2C_HS_SCL_HCNT_MASK                                          \
  I2C_HS_SCL_HCNT_RAWMSK << I2C_HS_SCL_HCNT_SHIFT )
#define I2C_HS_SCL_HCNT(x)                                            \
  ((x) & I2C_HS_SCL_HCNT_RAWMSK) << I2C_HS_SCL_HCNT_SHIFT)
#define I2C_HS_SCL_LCNT_SHIFT                                         0
#define I2C_HS_SCL_LCNT_RAWMSK                                        0xffff
#define I2C_HS_SCL_LCNT_MASK                                          \
  I2C_HS_SCL_LCNT_RAWMSK << I2C_HS_SCL_LCNT_SHIFT )
#define I2C_HS_SCL_LCNT(x)                                            \
  ((x) & I2C_HS_SCL_LCNT_RAWMSK) << I2C_HS_SCL_LCNT_SHIFT)
#define I2C_INTR_STAT_R_GEN_CALL                                      BIT(11)
#define I2C_INTR_STAT_R_GEN_CALL_SHIFT                                11
#define I2C_INTR_STAT_R_GEN_CALL_RAWMSK                               0x1
#define I2C_INTR_STAT_R_GEN_CALL_MASK                                 \
  I2C_INTR_STAT_R_GEN_CALL_RAWMSK << I2C_INTR_STAT_R_GEN_CALL_SHIFT )
#define I2C_INTR_STAT_R_START_DET                                     BIT(10)
#define I2C_INTR_STAT_R_START_DET_SHIFT                               10
#define I2C_INTR_STAT_R_START_DET_RAWMSK                              0x1
#define I2C_INTR_STAT_R_START_DET_MASK                                \
  I2C_INTR_STAT_R_START_DET_RAWMSK << I2C_INTR_STAT_R_START_DET_SHIFT )
#define I2C_INTR_STAT_R_STOP_DET                                      BIT(9)
#define I2C_INTR_STAT_R_STOP_DET_SHIFT                                9
#define I2C_INTR_STAT_R_STOP_DET_RAWMSK                               0x1
#define I2C_INTR_STAT_R_STOP_DET_MASK                                 \
  I2C_INTR_STAT_R_STOP_DET_RAWMSK << I2C_INTR_STAT_R_STOP_DET_SHIFT )
#define I2C_INTR_STAT_R_ACTIVITY                                      BIT(8)
#define I2C_INTR_STAT_R_ACTIVITY_SHIFT                                8
#define I2C_INTR_STAT_R_ACTIVITY_RAWMSK                               0x1
#define I2C_INTR_STAT_R_ACTIVITY_MASK                                 \
  I2C_INTR_STAT_R_ACTIVITY_RAWMSK << I2C_INTR_STAT_R_ACTIVITY_SHIFT )
#define I2C_INTR_STAT_R_RX_DONE                                       BIT(7)
#define I2C_INTR_STAT_R_RX_DONE_SHIFT                                 7
#define I2C_INTR_STAT_R_RX_DONE_RAWMSK                                0x1
#define I2C_INTR_STAT_R_RX_DONE_MASK                                  \
  I2C_INTR_STAT_R_RX_DONE_RAWMSK << I2C_INTR_STAT_R_RX_DONE_SHIFT )
#define I2C_INTR_STAT_R_TX_ABRT                                       BIT(6)
#define I2C_INTR_STAT_R_TX_ABRT_SHIFT                                 6
#define I2C_INTR_STAT_R_TX_ABRT_RAWMSK                                0x1
#define I2C_INTR_STAT_R_TX_ABRT_MASK                                  \
  I2C_INTR_STAT_R_TX_ABRT_RAWMSK << I2C_INTR_STAT_R_TX_ABRT_SHIFT )
#define I2C_INTR_STAT_R_RD_REQ                                        BIT(5)
#define I2C_INTR_STAT_R_RD_REQ_SHIFT                                  5
#define I2C_INTR_STAT_R_RD_REQ_RAWMSK                                 0x1
#define I2C_INTR_STAT_R_RD_REQ_MASK                                   \
  I2C_INTR_STAT_R_RD_REQ_RAWMSK << I2C_INTR_STAT_R_RD_REQ_SHIFT )
#define I2C_INTR_STAT_R_TX_EMPTY                                      BIT(4)
#define I2C_INTR_STAT_R_TX_EMPTY_SHIFT                                4
#define I2C_INTR_STAT_R_TX_EMPTY_RAWMSK                               0x1
#define I2C_INTR_STAT_R_TX_EMPTY_MASK                                 \
  I2C_INTR_STAT_R_TX_EMPTY_RAWMSK << I2C_INTR_STAT_R_TX_EMPTY_SHIFT )
#define I2C_INTR_STAT_R_TX_OVER                                       BIT(3)
#define I2C_INTR_STAT_R_TX_OVER_SHIFT                                 3
#define I2C_INTR_STAT_R_TX_OVER_RAWMSK                                0x1
#define I2C_INTR_STAT_R_TX_OVER_MASK                                  \
  I2C_INTR_STAT_R_TX_OVER_RAWMSK << I2C_INTR_STAT_R_TX_OVER_SHIFT )
#define I2C_INTR_STAT_R_RX_FULL                                       BIT(2)
#define I2C_INTR_STAT_R_RX_FULL_SHIFT                                 2
#define I2C_INTR_STAT_R_RX_FULL_RAWMSK                                0x1
#define I2C_INTR_STAT_R_RX_FULL_MASK                                  \
  I2C_INTR_STAT_R_RX_FULL_RAWMSK << I2C_INTR_STAT_R_RX_FULL_SHIFT )
#define I2C_INTR_STAT_R_RX_OVER                                       BIT(1)
#define I2C_INTR_STAT_R_RX_OVER_SHIFT                                 1
#define I2C_INTR_STAT_R_RX_OVER_RAWMSK                                0x1
#define I2C_INTR_STAT_R_RX_OVER_MASK                                  \
  I2C_INTR_STAT_R_RX_OVER_RAWMSK << I2C_INTR_STAT_R_RX_OVER_SHIFT )
#define I2C_INTR_STAT_R_RX_UNDER                                      BIT(0)
#define I2C_INTR_STAT_R_RX_UNDER_SHIFT                                0
#define I2C_INTR_STAT_R_RX_UNDER_RAWMSK                               0x1
#define I2C_INTR_STAT_R_RX_UNDER_MASK                                 \
  I2C_INTR_STAT_R_RX_UNDER_RAWMSK << I2C_INTR_STAT_R_RX_UNDER_SHIFT )
#define I2C_INTR_MASK_M_GEN_CALL                                      BIT(11)
#define I2C_INTR_MASK_M_GEN_CALL_SHIFT                                11
#define I2C_INTR_MASK_M_GEN_CALL_RAWMSK                               0x1
#define I2C_INTR_MASK_M_GEN_CALL_MASK                                 \
  I2C_INTR_MASK_M_GEN_CALL_RAWMSK << I2C_INTR_MASK_M_GEN_CALL_SHIFT )
#define I2C_INTR_MASK_M_START_DET                                     BIT(10)
#define I2C_INTR_MASK_M_START_DET_SHIFT                               10
#define I2C_INTR_MASK_M_START_DET_RAWMSK                              0x1
#define I2C_INTR_MASK_M_START_DET_MASK                                \
  I2C_INTR_MASK_M_START_DET_RAWMSK << I2C_INTR_MASK_M_START_DET_SHIFT )
#define I2C_INTR_MASK_M_STOP_DET                                      BIT(9)
#define I2C_INTR_MASK_M_STOP_DET_SHIFT                                9
#define I2C_INTR_MASK_M_STOP_DET_RAWMSK                               0x1
#define I2C_INTR_MASK_M_STOP_DET_MASK                                 \
  I2C_INTR_MASK_M_STOP_DET_RAWMSK << I2C_INTR_MASK_M_STOP_DET_SHIFT )
#define I2C_INTR_MASK_M_ACTIVITY                                      BIT(8)
#define I2C_INTR_MASK_M_ACTIVITY_SHIFT                                8
#define I2C_INTR_MASK_M_ACTIVITY_RAWMSK                               0x1
#define I2C_INTR_MASK_M_ACTIVITY_MASK                                 \
  I2C_INTR_MASK_M_ACTIVITY_RAWMSK << I2C_INTR_MASK_M_ACTIVITY_SHIFT )
#define I2C_INTR_MASK_M_RX_DONE                                       BIT(7)
#define I2C_INTR_MASK_M_RX_DONE_SHIFT                                 7
#define I2C_INTR_MASK_M_RX_DONE_RAWMSK                                0x1
#define I2C_INTR_MASK_M_RX_DONE_MASK                                  \
  I2C_INTR_MASK_M_RX_DONE_RAWMSK << I2C_INTR_MASK_M_RX_DONE_SHIFT )
#define I2C_INTR_MASK_M_TX_ABRT                                       BIT(6)
#define I2C_INTR_MASK_M_TX_ABRT_SHIFT                                 6
#define I2C_INTR_MASK_M_TX_ABRT_RAWMSK                                0x1
#define I2C_INTR_MASK_M_TX_ABRT_MASK                                  \
  I2C_INTR_MASK_M_TX_ABRT_RAWMSK << I2C_INTR_MASK_M_TX_ABRT_SHIFT )
#define I2C_INTR_MASK_M_RD_REQ                                        BIT(5)
#define I2C_INTR_MASK_M_RD_REQ_SHIFT                                  5
#define I2C_INTR_MASK_M_RD_REQ_RAWMSK                                 0x1
#define I2C_INTR_MASK_M_RD_REQ_MASK                                   \
  I2C_INTR_MASK_M_RD_REQ_RAWMSK << I2C_INTR_MASK_M_RD_REQ_SHIFT )
#define I2C_INTR_MASK_M_TX_EMPTY                                      BIT(4)
#define I2C_INTR_MASK_M_TX_EMPTY_SHIFT                                4
#define I2C_INTR_MASK_M_TX_EMPTY_RAWMSK                               0x1
#define I2C_INTR_MASK_M_TX_EMPTY_MASK                                 \
  I2C_INTR_MASK_M_TX_EMPTY_RAWMSK << I2C_INTR_MASK_M_TX_EMPTY_SHIFT )
#define I2C_INTR_MASK_M_TX_OVER                                       BIT(3)
#define I2C_INTR_MASK_M_TX_OVER_SHIFT                                 3
#define I2C_INTR_MASK_M_TX_OVER_RAWMSK                                0x1
#define I2C_INTR_MASK_M_TX_OVER_MASK                                  \
  I2C_INTR_MASK_M_TX_OVER_RAWMSK << I2C_INTR_MASK_M_TX_OVER_SHIFT )
#define I2C_INTR_MASK_M_RX_FULL                                       BIT(2)
#define I2C_INTR_MASK_M_RX_FULL_SHIFT                                 2
#define I2C_INTR_MASK_M_RX_FULL_RAWMSK                                0x1
#define I2C_INTR_MASK_M_RX_FULL_MASK                                  \
  I2C_INTR_MASK_M_RX_FULL_RAWMSK << I2C_INTR_MASK_M_RX_FULL_SHIFT )
#define I2C_INTR_MASK_M_RX_OVER                                       BIT(1)
#define I2C_INTR_MASK_M_RX_OVER_SHIFT                                 1
#define I2C_INTR_MASK_M_RX_OVER_RAWMSK                                0x1
#define I2C_INTR_MASK_M_RX_OVER_MASK                                  \
  I2C_INTR_MASK_M_RX_OVER_RAWMSK << I2C_INTR_MASK_M_RX_OVER_SHIFT )
#define I2C_INTR_MASK_M_RX_UNDER                                      BIT(0)
#define I2C_INTR_MASK_M_RX_UNDER_SHIFT                                0
#define I2C_INTR_MASK_M_RX_UNDER_RAWMSK                               0x1
#define I2C_INTR_MASK_M_RX_UNDER_MASK                                 \
  I2C_INTR_MASK_M_RX_UNDER_RAWMSK << I2C_INTR_MASK_M_RX_UNDER_SHIFT )
#define I2C_RAW_INTR_STAT_GEN_CALL                                    BIT(11)
#define I2C_RAW_INTR_STAT_GEN_CALL_SHIFT                              11
#define I2C_RAW_INTR_STAT_GEN_CALL_RAWMSK                             0x1
#define I2C_RAW_INTR_STAT_GEN_CALL_MASK                               \
  I2C_RAW_INTR_STAT_GEN_CALL_RAWMSK << I2C_RAW_INTR_STAT_GEN_CALL_SHIFT )
#define I2C_RAW_INTR_STAT_START_DET                                   BIT(10)
#define I2C_RAW_INTR_STAT_START_DET_SHIFT                             10
#define I2C_RAW_INTR_STAT_START_DET_RAWMSK                            0x1
#define I2C_RAW_INTR_STAT_START_DET_MASK                              \
  I2C_RAW_INTR_STAT_START_DET_RAWMSK << I2C_RAW_INTR_STAT_START_DET_SHIFT )
#define I2C_RAW_INTR_STAT_STOP_DET                                    BIT(9)
#define I2C_RAW_INTR_STAT_STOP_DET_SHIFT                              9
#define I2C_RAW_INTR_STAT_STOP_DET_RAWMSK                             0x1
#define I2C_RAW_INTR_STAT_STOP_DET_MASK                               \
  I2C_RAW_INTR_STAT_STOP_DET_RAWMSK << I2C_RAW_INTR_STAT_STOP_DET_SHIFT )
#define I2C_RAW_INTR_STAT_ACTIVITY                                    BIT(8)
#define I2C_RAW_INTR_STAT_ACTIVITY_SHIFT                              8
#define I2C_RAW_INTR_STAT_ACTIVITY_RAWMSK                             0x1
#define I2C_RAW_INTR_STAT_ACTIVITY_MASK                               \
  I2C_RAW_INTR_STAT_ACTIVITY_RAWMSK << I2C_RAW_INTR_STAT_ACTIVITY_SHIFT )
#define I2C_RAW_INTR_STAT_RX_DONE                                     BIT(7)
#define I2C_RAW_INTR_STAT_RX_DONE_SHIFT                               7
#define I2C_RAW_INTR_STAT_RX_DONE_RAWMSK                              0x1
#define I2C_RAW_INTR_STAT_RX_DONE_MASK                                \
  I2C_RAW_INTR_STAT_RX_DONE_RAWMSK << I2C_RAW_INTR_STAT_RX_DONE_SHIFT )
#define I2C_RAW_INTR_STAT_TX_ABRT                                     BIT(6)
#define I2C_RAW_INTR_STAT_TX_ABRT_SHIFT                               6
#define I2C_RAW_INTR_STAT_TX_ABRT_RAWMSK                              0x1
#define I2C_RAW_INTR_STAT_TX_ABRT_MASK                                \
  I2C_RAW_INTR_STAT_TX_ABRT_RAWMSK << I2C_RAW_INTR_STAT_TX_ABRT_SHIFT )
#define I2C_RAW_INTR_STAT_RD_REQ                                      BIT(5)
#define I2C_RAW_INTR_STAT_RD_REQ_SHIFT                                5
#define I2C_RAW_INTR_STAT_RD_REQ_RAWMSK                               0x1
#define I2C_RAW_INTR_STAT_RD_REQ_MASK                                 \
  I2C_RAW_INTR_STAT_RD_REQ_RAWMSK << I2C_RAW_INTR_STAT_RD_REQ_SHIFT )
#define I2C_RAW_INTR_STAT_TX_EMPTY                                    BIT(4)
#define I2C_RAW_INTR_STAT_TX_EMPTY_SHIFT                              4
#define I2C_RAW_INTR_STAT_TX_EMPTY_RAWMSK                             0x1
#define I2C_RAW_INTR_STAT_TX_EMPTY_MASK                               \
  I2C_RAW_INTR_STAT_TX_EMPTY_RAWMSK << I2C_RAW_INTR_STAT_TX_EMPTY_SHIFT )
#define I2C_RAW_INTR_STAT_TX_OVER                                     BIT(3)
#define I2C_RAW_INTR_STAT_TX_OVER_SHIFT                               3
#define I2C_RAW_INTR_STAT_TX_OVER_RAWMSK                              0x1
#define I2C_RAW_INTR_STAT_TX_OVER_MASK                                \
  I2C_RAW_INTR_STAT_TX_OVER_RAWMSK << I2C_RAW_INTR_STAT_TX_OVER_SHIFT )
#define I2C_RAW_INTR_STAT_RX_FULL                                     BIT(2)
#define I2C_RAW_INTR_STAT_RX_FULL_SHIFT                               2
#define I2C_RAW_INTR_STAT_RX_FULL_RAWMSK                              0x1
#define I2C_RAW_INTR_STAT_RX_FULL_MASK                                \
  I2C_RAW_INTR_STAT_RX_FULL_RAWMSK << I2C_RAW_INTR_STAT_RX_FULL_SHIFT )
#define I2C_RAW_INTR_STAT_RX_OVER                                     BIT(1)
#define I2C_RAW_INTR_STAT_RX_OVER_SHIFT                               1
#define I2C_RAW_INTR_STAT_RX_OVER_RAWMSK                              0x1
#define I2C_RAW_INTR_STAT_RX_OVER_MASK                                \
  I2C_RAW_INTR_STAT_RX_OVER_RAWMSK << I2C_RAW_INTR_STAT_RX_OVER_SHIFT )
#define I2C_RAW_INTR_STAT_RX_UNDER                                    BIT(0)
#define I2C_RAW_INTR_STAT_RX_UNDER_SHIFT                              0
#define I2C_RAW_INTR_STAT_RX_UNDER_RAWMSK                             0x1
#define I2C_RAW_INTR_STAT_RX_UNDER_MASK                               \
  I2C_RAW_INTR_STAT_RX_UNDER_RAWMSK << I2C_RAW_INTR_STAT_RX_UNDER_SHIFT )
#define I2C_RX_TL_SHIFT                                               0
#define I2C_RX_TL_RAWMSK                                              0xff
#define I2C_RX_TL_MASK                                                \
  I2C_RX_TL_RAWMSK << I2C_RX_TL_SHIFT )
#define I2C_RX_TL(x)                                                  \
  ((x) & I2C_RX_TL_RAWMSK) << I2C_RX_TL_SHIFT)
#define I2C_TX_TL_SHIFT                                               0
#define I2C_TX_TL_RAWMSK                                              0xff
#define I2C_TX_TL_MASK                                                \
  I2C_TX_TL_RAWMSK << I2C_TX_TL_SHIFT )
#define I2C_TX_TL(x)                                                  \
  ((x) & I2C_TX_TL_RAWMSK) << I2C_TX_TL_SHIFT)
#define I2C_CLR_INTR                                                  BIT(0)
#define I2C_CLR_INTR_SHIFT                                            0
#define I2C_CLR_INTR_RAWMSK                                           0x1
#define I2C_CLR_INTR_MASK                                             \
  I2C_CLR_INTR_RAWMSK << I2C_CLR_INTR_SHIFT )
#define I2C_CLR_RX_UNDER                                              BIT(0)
#define I2C_CLR_RX_UNDER_SHIFT                                        0
#define I2C_CLR_RX_UNDER_RAWMSK                                       0x1
#define I2C_CLR_RX_UNDER_MASK                                         \
  I2C_CLR_RX_UNDER_RAWMSK << I2C_CLR_RX_UNDER_SHIFT )
#define I2C_CLR_RX_OVER                                               BIT(0)
#define I2C_CLR_RX_OVER_SHIFT                                         0
#define I2C_CLR_RX_OVER_RAWMSK                                        0x1
#define I2C_CLR_RX_OVER_MASK                                          \
  I2C_CLR_RX_OVER_RAWMSK << I2C_CLR_RX_OVER_SHIFT )
#define I2C_CLR_TX_OVER                                               BIT(0)
#define I2C_CLR_TX_OVER_SHIFT                                         0
#define I2C_CLR_TX_OVER_RAWMSK                                        0x1
#define I2C_CLR_TX_OVER_MASK                                          \
  I2C_CLR_TX_OVER_RAWMSK << I2C_CLR_TX_OVER_SHIFT )
#define I2C_CLR_RD_REQ                                                BIT(0)
#define I2C_CLR_RD_REQ_SHIFT                                          0
#define I2C_CLR_RD_REQ_RAWMSK                                         0x1
#define I2C_CLR_RD_REQ_MASK                                           \
  I2C_CLR_RD_REQ_RAWMSK << I2C_CLR_RD_REQ_SHIFT )
#define CLR_RD_REQ                                                    BIT(0)
#define CLR_RD_REQ_SHIFT                                              0
#define CLR_RD_REQ_RAWMSK                                             0x1
#define CLR_RD_REQ_MASK                                               \
  CLR_RD_REQ_RAWMSK << CLR_RD_REQ_SHIFT )
#define I2C_CLR_RX_DONE                                               BIT(0)
#define I2C_CLR_RX_DONE_SHIFT                                         0
#define I2C_CLR_RX_DONE_RAWMSK                                        0x1
#define I2C_CLR_RX_DONE_MASK                                          \
  I2C_CLR_RX_DONE_RAWMSK << I2C_CLR_RX_DONE_SHIFT )
#define I2C_CLR_ACTIVITY                                              BIT(0)
#define I2C_CLR_ACTIVITY_SHIFT                                        0
#define I2C_CLR_ACTIVITY_RAWMSK                                       0x1
#define I2C_CLR_ACTIVITY_MASK                                         \
  I2C_CLR_ACTIVITY_RAWMSK << I2C_CLR_ACTIVITY_SHIFT )
#define I2C_CLR_STOP_DET                                              BIT(0)
#define I2C_CLR_STOP_DET_SHIFT                                        0
#define I2C_CLR_STOP_DET_RAWMSK                                       0x1
#define I2C_CLR_STOP_DET_MASK                                         \
  I2C_CLR_STOP_DET_RAWMSK << I2C_CLR_STOP_DET_SHIFT )
#define I2C_CLR_START_DET                                             BIT(0)
#define I2C_CLR_START_DET_SHIFT                                       0
#define I2C_CLR_START_DET_RAWMSK                                      0x1
#define I2C_CLR_START_DET_MASK                                        \
  I2C_CLR_START_DET_RAWMSK << I2C_CLR_START_DET_SHIFT )
#define I2C_CLR_GEN_CALL                                              BIT(0)
#define I2C_CLR_GEN_CALL_SHIFT                                        0
#define I2C_CLR_GEN_CALL_RAWMSK                                       0x1
#define I2C_CLR_GEN_CALL_MASK                                         \
  I2C_CLR_GEN_CALL_RAWMSK << I2C_CLR_GEN_CALL_SHIFT )
#define I2C_ENABLE                                                    BIT(0)
#define I2C_ENABLE_SHIFT                                              0
#define I2C_ENABLE_RAWMSK                                             0x1
#define I2C_ENABLE_MASK                                               \
  I2C_ENABLE_RAWMSK << I2C_ENABLE_SHIFT )
#define I2C_STATUS_SLV_ACTIVITY                                       BIT(6)
#define I2C_STATUS_SLV_ACTIVITY_SHIFT                                 6
#define I2C_STATUS_SLV_ACTIVITY_RAWMSK                                0x1
#define I2C_STATUS_SLV_ACTIVITY_MASK                                  \
  I2C_STATUS_SLV_ACTIVITY_RAWMSK << I2C_STATUS_SLV_ACTIVITY_SHIFT )
#define I2C_STATUS_MST_ACTIVITY                                       BIT(5)
#define I2C_STATUS_MST_ACTIVITY_SHIFT                                 5
#define I2C_STATUS_MST_ACTIVITY_RAWMSK                                0x1
#define I2C_STATUS_MST_ACTIVITY_MASK                                  \
  I2C_STATUS_MST_ACTIVITY_RAWMSK << I2C_STATUS_MST_ACTIVITY_SHIFT )
#define I2C_STATUS_RFF                                                BIT(4)
#define I2C_STATUS_RFF_SHIFT                                          4
#define I2C_STATUS_RFF_RAWMSK                                         0x1
#define I2C_STATUS_RFF_MASK                                           \
  I2C_STATUS_RFF_RAWMSK << I2C_STATUS_RFF_SHIFT )
#define I2C_STATUS_RFNE                                               BIT(3)
#define I2C_STATUS_RFNE_SHIFT                                         3
#define I2C_STATUS_RFNE_RAWMSK                                        0x1
#define I2C_STATUS_RFNE_MASK                                          \
  I2C_STATUS_RFNE_RAWMSK << I2C_STATUS_RFNE_SHIFT )
#define I2C_STATUS_TFE                                                BIT(2)
#define I2C_STATUS_TFE_SHIFT                                          2
#define I2C_STATUS_TFE_RAWMSK                                         0x1
#define I2C_STATUS_TFE_MASK                                           \
  I2C_STATUS_TFE_RAWMSK << I2C_STATUS_TFE_SHIFT )
#define I2C_STATUS_TFNF                                               BIT(1)
#define I2C_STATUS_TFNF_SHIFT                                         1
#define I2C_STATUS_TFNF_RAWMSK                                        0x1
#define I2C_STATUS_TFNF_MASK                                          \
  I2C_STATUS_TFNF_RAWMSK << I2C_STATUS_TFNF_SHIFT )
#define I2C_STATUS_ACTIVITY                                           BIT(0)
#define I2C_STATUS_ACTIVITY_SHIFT                                     0
#define I2C_STATUS_ACTIVITY_RAWMSK                                    0x1
#define I2C_STATUS_ACTIVITY_MASK                                      \
  I2C_STATUS_ACTIVITY_RAWMSK << I2C_STATUS_ACTIVITY_SHIFT )
#define I2C_TXFLR_SHIFT                                               0
#define I2C_TXFLR_RAWMSK                                              0x3f
#define I2C_TXFLR_MASK                                                \
  I2C_TXFLR_RAWMSK << I2C_TXFLR_SHIFT )
#define I2C_TXFLR(x)                                                  \
  ((x) & I2C_TXFLR_RAWMSK) << I2C_TXFLR_SHIFT)
#define I2C_RXFLR_SHIFT                                               0
#define I2C_RXFLR_RAWMSK                                              0x1f
#define I2C_RXFLR_MASK                                                \
  I2C_RXFLR_RAWMSK << I2C_RXFLR_SHIFT )
#define I2C_RXFLR(x)                                                  \
  ((x) & I2C_RXFLR_RAWMSK) << I2C_RXFLR_SHIFT)
#define I2C_SDA_HOLD_SHIFT                                            0
#define I2C_SDA_HOLD_RAWMSK                                           0xffff
#define I2C_SDA_HOLD_MASK                                             \
  I2C_SDA_HOLD_RAWMSK << I2C_SDA_HOLD_SHIFT )
#define I2C_SDA_HOLD(x)                                               \
  ((x) & I2C_SDA_HOLD_RAWMSK) << I2C_SDA_HOLD_SHIFT)
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX                            BIT(15)
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_SHIFT                      15
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_RAWMSK                     0x1
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_MASK                       \
  I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST                           BIT(14)
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_SHIFT                     14
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_RAWMSK                    0x1
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_MASK                      \
  I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO                       BIT(13)
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_SHIFT                 13
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_RAWMSK                0x1
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_MASK                  \
  I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_SHIFT )
#define I2C_TX_ABRT_SOURCE_ARB_LOST                                   BIT(12)
#define I2C_TX_ABRT_SOURCE_ARB_LOST_SHIFT                             12
#define I2C_TX_ABRT_SOURCE_ARB_LOST_RAWMSK                            0x1
#define I2C_TX_ABRT_SOURCE_ARB_LOST_MASK                              \
  I2C_TX_ABRT_SOURCE_ARB_LOST_RAWMSK << I2C_TX_ABRT_SOURCE_ARB_LOST_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS                            BIT(11)
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_SHIFT                      11
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_RAWMSK                     0x1
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_MASK                       \
  I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT                        BIT(10)
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_SHIFT                  10
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_RAWMSK                 0x1
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_MASK                   \
  I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT                         BIT(9)
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_SHIFT                   9
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_RAWMSK                  0x1
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_MASK                    \
  I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT                            BIT(8)
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_SHIFT                      8
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_RAWMSK                     0x1
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_MASK                       \
  I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET                          BIT(7)
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_SHIFT                    7
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_RAWMSK                   0x1
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_MASK                     \
  I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET                             BIT(6)
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_SHIFT                       6
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_RAWMSK                      0x1
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_MASK                        \
  I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ                            BIT(5)
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_SHIFT                      5
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_RAWMSK                     0x1
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_MASK                       \
  I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK                           BIT(4)
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_SHIFT                     4
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_RAWMSK                    0x1
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_MASK                      \
  I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK                          BIT(3)
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_SHIFT                    3
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_RAWMSK                   0x1
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_MASK                     \
  I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK                         BIT(2)
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_SHIFT                   2
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_RAWMSK                  0x1
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_MASK                    \
  I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK                         BIT(1)
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_SHIFT                   1
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_RAWMSK                  0x1
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_MASK                    \
  I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_SHIFT )
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK                         BIT(0)
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_SHIFT                   0
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_RAWMSK                  0x1
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_MASK                    \
  I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_RAWMSK << I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_SHIFT )
#define I2C_SLV_DATA_NACK_ONLY                                        BIT(0)
#define I2C_SLV_DATA_NACK_ONLY_SHIFT                                  0
#define I2C_SLV_DATA_NACK_ONLY_RAWMSK                                 0x1
#define I2C_SLV_DATA_NACK_ONLY_MASK                                   \
  I2C_SLV_DATA_NACK_ONLY_RAWMSK << I2C_SLV_DATA_NACK_ONLY_SHIFT )
#define I2C_DMA_CR_TDMAE                                              BIT(1)
#define I2C_DMA_CR_TDMAE_SHIFT                                        1
#define I2C_DMA_CR_TDMAE_RAWMSK                                       0x1
#define I2C_DMA_CR_TDMAE_MASK                                         \
  I2C_DMA_CR_TDMAE_RAWMSK << I2C_DMA_CR_TDMAE_SHIFT )
#define I2C_DMA_CR_RDMAE                                              BIT(0)
#define I2C_DMA_CR_RDMAE_SHIFT                                        0
#define I2C_DMA_CR_RDMAE_RAWMSK                                       0x1
#define I2C_DMA_CR_RDMAE_MASK                                         \
  I2C_DMA_CR_RDMAE_RAWMSK << I2C_DMA_CR_RDMAE_SHIFT )
#define I2C_DMA_TDLR_DMATDL_SHIFT                                     0
#define I2C_DMA_TDLR_DMATDL_RAWMSK                                    0x1f
#define I2C_DMA_TDLR_DMATDL_MASK                                      \
  I2C_DMA_TDLR_DMATDL_RAWMSK << I2C_DMA_TDLR_DMATDL_SHIFT )
#define I2C_DMA_TDLR_DMATDL(x)                                        \
  ((x) & I2C_DMA_TDLR_DMATDL_RAWMSK) << I2C_DMA_TDLR_DMATDL_SHIFT)
#define I2C_DMA_RDLR_DMARDL_SHIFT                                     0
#define I2C_DMA_RDLR_DMARDL_RAWMSK                                    0xf
#define I2C_DMA_RDLR_DMARDL_MASK                                      \
  I2C_DMA_RDLR_DMARDL_RAWMSK << I2C_DMA_RDLR_DMARDL_SHIFT )
#define I2C_DMA_RDLR_DMARDL(x)                                        \
  ((x) & I2C_DMA_RDLR_DMARDL_RAWMSK) << I2C_DMA_RDLR_DMARDL_SHIFT)
#define I2C_SDA_SETUP_SHIFT                                           0
#define I2C_SDA_SETUP_RAWMSK                                          0xff
#define I2C_SDA_SETUP_MASK                                            \
  I2C_SDA_SETUP_RAWMSK << I2C_SDA_SETUP_SHIFT )
#define I2C_SDA_SETUP(x)                                              \
  ((x) & I2C_SDA_SETUP_RAWMSK) << I2C_SDA_SETUP_SHIFT)
#define I2C_ACK_GENERAL_CALL                                          BIT(0)
#define I2C_ACK_GENERAL_CALL_SHIFT                                    0
#define I2C_ACK_GENERAL_CALL_RAWMSK                                   0x1
#define I2C_ACK_GENERAL_CALL_MASK                                     \
  I2C_ACK_GENERAL_CALL_RAWMSK << I2C_ACK_GENERAL_CALL_SHIFT )
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST                            BIT(2)
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_SHIFT                      2
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_RAWMSK                     0x1
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_MASK                       \
  I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_RAWMSK << I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_SHIFT )
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY                     BIT(1)
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_SHIFT               1
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_RAWMSK              0x1
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_MASK                \
  I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_RAWMSK << I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_SHIFT )
#define I2C_ENABLE_STATUS_IC_EN                                       BIT(0)
#define I2C_ENABLE_STATUS_IC_EN_SHIFT                                 0
#define I2C_ENABLE_STATUS_IC_EN_RAWMSK                                0x1
#define I2C_ENABLE_STATUS_IC_EN_MASK                                  \
  I2C_ENABLE_STATUS_IC_EN_RAWMSK << I2C_ENABLE_STATUS_IC_EN_SHIFT )
#define I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_SHIFT                        16
#define I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_RAWMSK                       0xff
#define I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_MASK                         \
  I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_RAWMSK << I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_SHIFT )
#define I2C_COMP_PARAM_1_TX_BUFFER_DEPTH(x)                           \
  ((x) & I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_RAWMSK) << I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_SHIFT)
#define I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_SHIFT                        8
#define I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_RAWMSK                       0xff
#define I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_MASK                         \
  I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_RAWMSK << I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_SHIFT )
#define I2C_COMP_PARAM_1_RX_BUFFER_DEPTH(x)                           \
  ((x) & I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_RAWMSK) << I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_SHIFT)
#define I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS                           BIT(7)
#define I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_SHIFT                     7
#define I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_RAWMSK                    0x1
#define I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_MASK                      \
  I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_RAWMSK << I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_SHIFT )
#define I2C_COMP_PARAM_1_HAS_DMA                                      BIT(6)
#define I2C_COMP_PARAM_1_HAS_DMA_SHIFT                                6
#define I2C_COMP_PARAM_1_HAS_DMA_RAWMSK                               0x1
#define I2C_COMP_PARAM_1_HAS_DMA_MASK                                 \
  I2C_COMP_PARAM_1_HAS_DMA_RAWMSK << I2C_COMP_PARAM_1_HAS_DMA_SHIFT )
#define I2C_COMP_PARAM_1_INTR_IO                                      BIT(5)
#define I2C_COMP_PARAM_1_INTR_IO_SHIFT                                5
#define I2C_COMP_PARAM_1_INTR_IO_RAWMSK                               0x1
#define I2C_COMP_PARAM_1_INTR_IO_MASK                                 \
  I2C_COMP_PARAM_1_INTR_IO_RAWMSK << I2C_COMP_PARAM_1_INTR_IO_SHIFT )
#define I2C_COMP_PARAM_1_HC_COUNT_VALUES                              BIT(4)
#define I2C_COMP_PARAM_1_HC_COUNT_VALUES_SHIFT                        4
#define I2C_COMP_PARAM_1_HC_COUNT_VALUES_RAWMSK                       0x1
#define I2C_COMP_PARAM_1_HC_COUNT_VALUES_MASK                         \
  I2C_COMP_PARAM_1_HC_COUNT_VALUES_RAWMSK << I2C_COMP_PARAM_1_HC_COUNT_VALUES_SHIFT )
#define I2C_COMP_PARAM_1_MAX_SPEED_MODE_SHIFT                         2
#define I2C_COMP_PARAM_1_MAX_SPEED_MODE_RAWMSK                        0x3
#define I2C_COMP_PARAM_1_MAX_SPEED_MODE_MASK                          \
  I2C_COMP_PARAM_1_MAX_SPEED_MODE_RAWMSK << I2C_COMP_PARAM_1_MAX_SPEED_MODE_SHIFT )
#define I2C_COMP_PARAM_1_MAX_SPEED_MODE(x)                            \
  ((x) & I2C_COMP_PARAM_1_MAX_SPEED_MODE_RAWMSK) << I2C_COMP_PARAM_1_MAX_SPEED_MODE_SHIFT)
#define I2C_COMP_PARAM_1_APB_DATA_WIDTH_SHIFT                         0
#define I2C_COMP_PARAM_1_APB_DATA_WIDTH_RAWMSK                        0x3
#define I2C_COMP_PARAM_1_APB_DATA_WIDTH_MASK                          \
  I2C_COMP_PARAM_1_APB_DATA_WIDTH_RAWMSK << I2C_COMP_PARAM_1_APB_DATA_WIDTH_SHIFT )
#define I2C_COMP_PARAM_1_APB_DATA_WIDTH(x)                            \
  ((x) & I2C_COMP_PARAM_1_APB_DATA_WIDTH_RAWMSK) << I2C_COMP_PARAM_1_APB_DATA_WIDTH_SHIFT)
#define I2C_COMP_VERSION_SHIFT                                        0
#define I2C_COMP_VERSION_RAWMSK                                       0xffffffffL
#define I2C_COMP_VERSION_MASK                                         \
  I2C_COMP_VERSION_RAWMSK << I2C_COMP_VERSION_SHIFT )
#define I2C_COMP_VERSION(x)                                           \
  ((x) & I2C_COMP_VERSION_RAWMSK) << I2C_COMP_VERSION_SHIFT)
#define I2C_COMP_TYPE_SHIFT                                           0
#define I2C_COMP_TYPE_RAWMSK                                          0xffffffffL
#define I2C_COMP_TYPE_MASK                                            \
  I2C_COMP_TYPE_RAWMSK << I2C_COMP_TYPE_SHIFT )
#define I2C_COMP_TYPE(x)                                              \
  ((x) & I2C_COMP_TYPE_RAWMSK) << I2C_COMP_TYPE_SHIFT)

#define I2S_CTL_EN                                                    BIT(0)
#define I2S_CTL_EN_SHIFT                                              0
#define I2S_CTL_EN_RAWMSK                                             0x1
#define I2S_CTL_EN_MASK                                               \
  I2S_CTL_EN_RAWMSK << I2S_CTL_EN_SHIFT )
#define I2S_CTL_TRX_ACT_SHIFT                                         1
#define I2S_CTL_TRX_ACT_RAWMSK                                        0x3
#define I2S_CTL_TRX_ACT_MASK                                          \
  I2S_CTL_TRX_ACT_RAWMSK << I2S_CTL_TRX_ACT_SHIFT )
#define I2S_CTL_TRX_ACT(x)                                            \
  ((x) & I2S_CTL_TRX_ACT_RAWMSK) << I2S_CTL_TRX_ACT_SHIFT)
#define I2S_CTL_CH_NUM_SHIFT                                          3
#define I2S_CTL_CH_NUM_RAWMSK                                         0x3
#define I2S_CTL_CH_NUM_MASK                                           \
  I2S_CTL_CH_NUM_RAWMSK << I2S_CTL_CH_NUM_SHIFT )
#define I2S_CTL_CH_NUM(x)                                             \
  ((x) & I2S_CTL_CH_NUM_RAWMSK) << I2S_CTL_CH_NUM_SHIFT)
#define I2S_CTL_WL                                                    BIT(6)
#define I2S_CTL_WL_SHIFT                                              6
#define I2S_CTL_WL_RAWMSK                                             0x1
#define I2S_CTL_WL_MASK                                               \
  I2S_CTL_WL_RAWMSK << I2S_CTL_WL_SHIFT )
#define I2S_CTL_LRSWAP                                                BIT(10)
#define I2S_CTL_LRSWAP_SHIFT                                          10
#define I2S_CTL_LRSWAP_RAWMSK                                         0x1
#define I2S_CTL_LRSWAP_MASK                                           \
  I2S_CTL_LRSWAP_RAWMSK << I2S_CTL_LRSWAP_SHIFT )
#define I2S_CTL_SCK_INV                                               BIT(11)
#define I2S_CTL_SCK_INV_SHIFT                                         11
#define I2S_CTL_SCK_INV_RAWMSK                                        0x1
#define I2S_CTL_SCK_INV_MASK                                          \
  I2S_CTL_SCK_INV_RAWMSK << I2S_CTL_SCK_INV_SHIFT )
#define I2S_CTL_ENDIAN_SWAP                                           BIT(12)
#define I2S_CTL_ENDIAN_SWAP_SHIFT                                     12
#define I2S_CTL_ENDIAN_SWAP_RAWMSK                                    0x1
#define I2S_CTL_ENDIAN_SWAP_MASK                                      \
  I2S_CTL_ENDIAN_SWAP_RAWMSK << I2S_CTL_ENDIAN_SWAP_SHIFT )
#define I2S_CTL_SLAVE_MODE                                            BIT(29)
#define I2S_CTL_SLAVE_MODE_SHIFT                                      29
#define I2S_CTL_SLAVE_MODE_RAWMSK                                     0x1
#define I2S_CTL_SLAVE_MODE_MASK                                       \
  I2S_CTL_SLAVE_MODE_RAWMSK << I2S_CTL_SLAVE_MODE_SHIFT )
#define I2S_CTL_CLK_SRC                                               BIT(30)
#define I2S_CTL_CLK_SRC_SHIFT                                         30
#define I2S_CTL_CLK_SRC_RAWMSK                                        0x1
#define I2S_CTL_CLK_SRC_MASK                                          \
  I2S_CTL_CLK_SRC_RAWMSK << I2S_CTL_CLK_SRC_SHIFT )
#define I2S_CTL_SW_RSTN                                               BIT(31)
#define I2S_CTL_SW_RSTN_SHIFT                                         31
#define I2S_CTL_SW_RSTN_RAWMSK                                        0x1
#define I2S_CTL_SW_RSTN_MASK                                          \
  I2S_CTL_SW_RSTN_RAWMSK << I2S_CTL_SW_RSTN_SHIFT )
#define I2S_SETTING_PAGE_SZ_SHIFT                                     0
#define I2S_SETTING_PAGE_SZ_RAWMSK                                    0xFFF
#define I2S_SETTING_PAGE_SZ_MASK                                      \
  I2S_SETTING_PAGE_SZ_RAWMSK << I2S_SETTING_PAGE_SZ_SHIFT )
#define I2S_SETTING_PAGE_SZ(x)                                        \
  ((x) & I2S_SETTING_PAGE_SZ_RAWMSK) << I2S_SETTING_PAGE_SZ_SHIFT)
#define I2S_SETTING_PAGE_NUM_SHIFT                                    12
#define I2S_SETTING_PAGE_NUM_RAWMSK                                   0x3
#define I2S_SETTING_PAGE_NUM_MASK                                     \
  I2S_SETTING_PAGE_NUM_RAWMSK << I2S_SETTING_PAGE_NUM_SHIFT )
#define I2S_SETTING_PAGE_NUM(x)                                       \
  ((x) & I2S_SETTING_PAGE_NUM_RAWMSK) << I2S_SETTING_PAGE_NUM_SHIFT)
#define I2S_SETTING_SAMPLE_RATE_SHIFT                                 14
#define I2S_SETTING_SAMPLE_RATE_RAWMSK                                0x7
#define I2S_SETTING_SAMPLE_RATE_MASK                                  \
  I2S_SETTING_SAMPLE_RATE_RAWMSK << I2S_SETTING_SAMPLE_RATE_SHIFT )
#define I2S_SETTING_SAMPLE_RATE(x)                                    \
  ((x) & I2S_SETTING_SAMPLE_RATE_RAWMSK) << I2S_SETTING_SAMPLE_RATE_SHIFT)
#define I2S_PAGE_OWN                                                  BIT(31)
#define I2S_PAGE_OWN_SHIFT                                            31
#define I2S_PAGE_OWN_RAWMSK                                           0x1
#define I2S_PAGE_OWN_MASK                                             \
  I2S_PAGE_OWN_RAWMSK << I2S_PAGE_OWN_SHIFT )

#define MII_COM_RST                                                   BIT0
#define MII_COM_RXCHKSUM                                              BIT1
#define MII_COM_RXJUMBO                                               BIT3

#define MII_ISMR_STS_RXOK                                             BIT0
#define MII_ISMR_STS_RER_RUNT                                         BIT2
#define MII_ISMR_STS_RER_OVF                                          BIT4
#define MII_ISMR_STS_RDU                                              BIT5
#define MII_ISMR_STS_TXOK                                             BIT6
#define MII_ISMR_STS_TER                                              BIT7
#define MII_ISMR_STS_LINKCHG                                          BIT8
#define MII_ISMR_STS_TDU                                              BIT9
#define MII_ISMR_MSK_RXOK                                             BIT16
#define MII_ISMR_MSK_RER_RUNT                                         BIT18
#define MII_ISMR_MSK_RER_OVF                                          BIT20
#define MII_ISMR_MSK_RDU                                              BIT21
#define MII_ISMR_MSK_TXOK                                             BIT22
#define MII_ISMR_MSK_TER                                              BIT23
#define MII_ISMR_MSK_LINKCHG                                          BIT24
#define MII_ISMR_MSK_TDU                                              BIT25

#define MII_ISMR_STS_CLR_ALL                                          0x0000FFFF

#define MII_TC_TX_NOPADDING                                           BIT0
#define MII_TC_NORMAL_MODE                                            0
#define MII_TC_LBK_R2T                                                1
#define MII_TC_LBK_T2R                                                3
#define MII_TC_LBK_MASK                                               0x00000300
#define MII_TC_IFG_TIME                                               3
#define MII_TC_IFG_MASK                                               0x00001C00

#define MII_RC_AAP                                                    BIT0
#define MII_RC_APM                                                    BIT1
#define MII_RC_AM                                                     BIT2
#define MII_RC_AB                                                     BIT3
#define MII_RC_AR                                                     BIT4
#define MII_RC_AER                                                    BIT5

#define MII_MS_LINKB                                                  BIT26

#define MII_MIIA_FLAG                                                 BIT31
#define MII_MIIA_PHY_ADDR_MASK                                        0x7C000000
#define MII_MIIA_PHY_REG_ADDR_MASK                                    0x001F0000

#define MII_IOCMD_TXFN1ST                                             BIT0
#define MII_IOCMD_TE                                                  BIT4
#define MII_IOCMD_RE                                                  BIT5
#define MII_IOCMD_RXFTH_1024                                          0
#define MII_IOCMD_RXFTH_128                                           1
#define MII_IOCMD_RXFTH_256                                           2
#define MII_IOCMD_RXFTH_512                                           3
#define MII_IOCMD_RXFTH_MASK                                          0x00001800
#define MII_IOCMD_TXFTH_128                                           0
#define MII_IOCMD_TXFTH_256                                           1
#define MII_IOCMD_TXFTH_512                                           2
#define MII_IOCMD_TXFTH_1024                                          3
#define MII_IOCMD_TXFTH_MASK                                          0x00180000
#define MII_IOCMD_SHORT_DES_FMT                                       BIT30

#define MII_IOCMD1_RXRING1                                            BIT16
#define MII_IOCMD1_EN_1GB                                             BIT24
#define MII_IOCMD1_DSC_FMT_EXTRA                                      0x3
#define MII_IOCMD1_DSCFMTEXTRA_MASK                                   0x70000000

#define PCM_CTL_SLAVE_SEL_SHIFT                                       8
#define PCM_CTL_SLAVE_SEL_RAWMSK                                      0x1
#define PCM_CTL_SLAVE_SEL_MASK                                        \
  PCM_CTL_SLAVE_SEL_RAWMSK << PCM_CTL_SLAVE_SEL_SHIFT )
#define PCM_CTL_SLAVE_SEL(x)                                          \
  ((x) & PCM_CTL_SLAVE_SEL_RAWMSK) << PCM_CTL_SLAVE_SEL_SHIFT)
#define PCM_CTL_FSINV_SHIFT                                           9
#define PCM_CTL_FSINV_RAWMSK                                          0x1
#define PCM_CTL_FSINV_MASK                                            \
  PCM_CTL_FSINV_RAWMSK << PCM_CTL_FSINV_SHIFT )
#define PCM_CTL_FSINV(x)                                              \
  ((x) & PCM_CTL_FSINV_RAWMSK) << PCM_CTL_FSINV_SHIFT)
#define PCM_CTL_PCM_EN_SHIFT                                          12
#define PCM_CTL_PCM_EN_RAWMSK                                         0x1
#define PCM_CTL_PCM_EN_MASK                                           \
  PCM_CTL_PCM_EN_RAWMSK << PCM_CTL_PCM_EN_SHIFT )
#define PCM_CTL_PCM_EN(x)                                             \
  ((x) & PCM_CTL_PCM_EN_RAWMSK) << PCM_CTL_PCM_EN_SHIFT)
#define PCM_CTL_LINEARMODE_SHIFT                                      13
#define PCM_CTL_LINEARMODE_RAWMSK                                     0x1
#define PCM_CTL_LINEARMODE_MASK                                       \
  PCM_CTL_LINEARMODE_RAWMSK << PCM_CTL_LINEARMODE_SHIFT )
#define PCM_CTL_LINEARMODE(x)                                         \
  ((x) & PCM_CTL_LINEARMODE_RAWMSK) << PCM_CTL_LINEARMODE_SHIFT)
#define PCM_CTL_LOOP_BACK_SHIFT                                       14
#define PCM_CTL_LOOP_BACK_RAWMSK                                      0x1
#define PCM_CTL_LOOP_BACK_MASK                                        \
  PCM_CTL_LOOP_BACK_RAWMSK << PCM_CTL_LOOP_BACK_SHIFT )
#define PCM_CTL_LOOP_BACK(x)                                          \
  ((x) & PCM_CTL_LOOP_BACK_RAWMSK) << PCM_CTL_LOOP_BACK_SHIFT)
#define PCM_CTL_ENDIAN_SWAP_SHIFT                                     17
#define PCM_CTL_ENDIAN_SWAP_RAWMSK                                    0x1
#define PCM_CTL_ENDIAN_SWAP_MASK                                      \
  PCM_CTL_ENDIAN_SWAP_RAWMSK << PCM_CTL_ENDIAN_SWAP_SHIFT )
#define PCM_CTL_ENDIAN_SWAP(x)                                        \
  ((x) & PCM_CTL_ENDIAN_SWAP_RAWMSK) << PCM_CTL_ENDIAN_SWAP_SHIFT)
#define PCM_CHCNR03_CH0RE_SHIFT                                       24
#define PCM_CHCNR03_CH0RE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH0RE_MASK                                        \
  PCM_CHCNR03_CH0RE_RAWMSK << PCM_CHCNR03_CH0RE_SHIFT )
#define PCM_CHCNR03_CH0RE(x)                                          \
  ((x) & PCM_CHCNR03_CH0RE_RAWMSK) << PCM_CHCNR03_CH0RE_SHIFT)
#define PCM_CHCNR03_CH0TE_SHIFT                                       25
#define PCM_CHCNR03_CH0TE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH0TE_MASK                                        \
  PCM_CHCNR03_CH0TE_RAWMSK << PCM_CHCNR03_CH0TE_SHIFT )
#define PCM_CHCNR03_CH0TE(x)                                          \
  ((x) & PCM_CHCNR03_CH0TE_RAWMSK) << PCM_CHCNR03_CH0TE_SHIFT)
#define PCM_CHCNR03_CH1RE_SHIFT                                       16
#define PCM_CHCNR03_CH1RE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH1RE_MASK                                        \
  PCM_CHCNR03_CH1RE_RAWMSK << PCM_CHCNR03_CH1RE_SHIFT )
#define PCM_CHCNR03_CH1RE(x)                                          \
  ((x) & PCM_CHCNR03_CH1RE_RAWMSK) << PCM_CHCNR03_CH1RE_SHIFT)
#define PCM_CHCNR03_CH1TE_SHIFT                                       17
#define PCM_CHCNR03_CH1TE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH1TE_MASK                                        \
  PCM_CHCNR03_CH1TE_RAWMSK << PCM_CHCNR03_CH1TE_SHIFT )
#define PCM_CHCNR03_CH1TE(x)                                          \
  ((x) & PCM_CHCNR03_CH1TE_RAWMSK) << PCM_CHCNR03_CH1TE_SHIFT)
#define PCM_CHCNR03_CH2RE_SHIFT                                       8
#define PCM_CHCNR03_CH2RE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH2RE_MASK                                        \
  PCM_CHCNR03_CH2RE_RAWMSK << PCM_CHCNR03_CH2RE_SHIFT )
#define PCM_CHCNR03_CH2RE(x)                                          \
  ((x) & PCM_CHCNR03_CH2RE_RAWMSK) << PCM_CHCNR03_CH2RE_SHIFT)
#define PCM_CHCNR03_CH2TE_SHIFT                                       9
#define PCM_CHCNR03_CH2TE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH2TE_MASK                                        \
  PCM_CHCNR03_CH2TE_RAWMSK << PCM_CHCNR03_CH2TE_SHIFT )
#define PCM_CHCNR03_CH2TE(x)                                          \
  ((x) & PCM_CHCNR03_CH2TE_RAWMSK) << PCM_CHCNR03_CH2TE_SHIFT)
#define PCM_CHCNR03_CH3RE_SHIFT                                       0
#define PCM_CHCNR03_CH3RE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH3RE_MASK                                        \
  PCM_CHCNR03_CH3RE_RAWMSK << PCM_CHCNR03_CH3RE_SHIFT )
#define PCM_CHCNR03_CH3RE(x)                                          \
  ((x) & PCM_CHCNR03_CH3RE_RAWMSK) << PCM_CHCNR03_CH3RE_SHIFT)
#define PCM_CHCNR03_CH3TE_SHIFT                                       1
#define PCM_CHCNR03_CH3TE_RAWMSK                                      0x1
#define PCM_CHCNR03_CH3TE_MASK                                        \
  PCM_CHCNR03_CH3TE_RAWMSK << PCM_CHCNR03_CH3TE_SHIFT )
#define PCM_CHCNR03_CH3TE(x)                                          \
  ((x) & PCM_CHCNR03_CH3TE_RAWMSK) << PCM_CHCNR03_CH3TE_SHIFT)
#define PCM_CHCNR03_CH0MUA_SHIFT                                      26
#define PCM_CHCNR03_CH0MUA_RAWMSK                                     0x1
#define PCM_CHCNR03_CH0MUA_MASK                                       \
  PCM_CHCNR03_CH0MUA_RAWMSK << PCM_CHCNR03_CH0MUA_SHIFT )
#define PCM_CHCNR03_CH0MUA(x)                                         \
  ((x) & PCM_CHCNR03_CH0MUA_RAWMSK) << PCM_CHCNR03_CH0MUA_SHIFT)
#define PCM_CHCNR03_CH0BAND_SHIFT                                     27
#define PCM_CHCNR03_CH0BAND_RAWMSK                                    0x1
#define PCM_CHCNR03_CH0BAND_MASK                                      \
  PCM_CHCNR03_CH0BAND_RAWMSK << PCM_CHCNR03_CH0BAND_SHIFT )
#define PCM_CHCNR03_CH0BAND(x)                                        \
  ((x) & PCM_CHCNR03_CH0BAND_RAWMSK) << PCM_CHCNR03_CH0BAND_SHIFT)
#define PCM_TSR03_CH0TSA_SHIFT                                        24
#define PCM_TSR03_CH0TSA_RAWMSK                                       0x1F
#define PCM_TSR03_CH0TSA_MASK                                         \
  PCM_TSR03_CH0TSA_RAWMSK << PCM_TSR03_CH0TSA_SHIFT )
#define PCM_TSR03_CH0TSA(x)                                           \
  ((x) & PCM_TSR03_CH0TSA_RAWMSK) << PCM_TSR03_CH0TSA_SHIFT)
#define PCM_BSIZE03_CH0BSIZE_SHIFT                                    24
#define PCM_BSIZE03_CH0BSIZE_RAWMSK                                   0xFF
#define PCM_BSIZE03_CH0BSIZE_MASK                                     \
  PCM_BSIZE03_CH0BSIZE_RAWMSK << PCM_BSIZE03_CH0BSIZE_SHIFT )
#define PCM_BSIZE03_CH0BSIZE(x)                                       \
  ((x) & PCM_BSIZE03_CH0BSIZE_RAWMSK) << PCM_BSIZE03_CH0BSIZE_SHIFT)

// =================================================================================================
// RTL8195AM Memory and Peripheral Map
//
#define RTL_ROM_BASE                  ((uint32_t)0x00000000)  // ROM base address in the alias region
#define RTL_SRAM_BASE                 ((uint32_t)0x10000000)  // SRAM base address in the alias region
#define RTL_TCM_BASE                  ((uint32_t)0x1FFF0000)  // TCM base address in the alias region
#define RTL_SDRAM_BASE                ((uint32_t)0x30000000)  // SDRAM base address in the alias region
#define RTL_PERIPH_BASE               ((uint32_t)0x40000000)  // Peripheral base address in the alias region
#define RTL_FLASH_BASE                ((uint32_t)0x98000000)  // FLASH base address in the alias region

#define RTL_SRAM_BB_BASE              ((uint32_t)0x00000000)  // SRAM base address in the bit-band region
#define RTL_PERIPH_BB_BASE            ((uint32_t)0x42000000)  // Peripheral base address in the bit-band region

// =================================================================================================
// RTL8195AM Peripheral Offset * Index = BaseAddress
//
#define GDMA_REG_OFF                  0x1000                  // GDMA0  GDMA1
#define I2S_REG_OFF                   0x1000                  // I2S0   I2S1
#define PCM_REG_OFF                   0x1000                  // PCM0   PCM1
#define SPI_REG_OFF                   0x400                   // SPI0   SPI1  SPI2
#define UART_REG_OFF                  0x400                   // UART0  UART1 UART2

// =================================================================================================
// RTL8195AM Peripheral memory map
//
#define RTL_ADC_BASE                  ( RTL_PERIPH_BASE + 0x00010000 )
#define RTL_CRYPTO_BASE               ( RTL_PERIPH_BASE + 0x00070000 )
#define RTL_DAC_BASE                  ( RTL_PERIPH_BASE + 0x00011000 )
#define RTL_GDMA0_BASE                ( RTL_PERIPH_BASE + 0x00060000 )
#define RTL_GDMA1_BASE                ( RTL_PERIPH_BASE + 0x00061000 )
#define RTL_GPIO_BASE                 ( RTL_PERIPH_BASE + 0x00001000 )
#define RTL_I2C0_BASE                 ( RTL_PERIPH_BASE + 0x00044000 )
#define RTL_I2C1_BASE                 ( RTL_PERIPH_BASE + 0x00044400 )
#define RTL_I2C2_BASE                 ( RTL_PERIPH_BASE + 0x00003400 )
#define RTL_I2C3_BASE                 ( RTL_PERIPH_BASE + 0x00003800 )
#define RTL_I2S0_BASE                 ( RTL_PERIPH_BASE + 0x00062000 )
#define RTL_I2S1_BASE                 ( RTL_PERIPH_BASE + 0x00063000 )
#define RTL_LOGU_BASE                 ( RTL_PERIPH_BASE + 0x00003000 )
#define RTL_MII_BASE                  ( RTL_PERIPH_BASE + 0x00050000 )
#define RTL_SDIOD_BASE                ( RTL_PERIPH_BASE + 0x00050000 )
#define RTL_NFC_BASE                  ( RTL_PERIPH_BASE + 0x00002400 )
#define RTL_PCM0_BASE                 ( RTL_PERIPH_BASE + 0x00064000 )
#define RTL_PCM1_BASE                 ( RTL_PERIPH_BASE + 0x00065000 )
#define RTL_SDIOH_BASE                ( RTL_PERIPH_BASE + 0x00058000 )
#define RTL_SDRC_BASE                 ( RTL_PERIPH_BASE + 0x00005000 )
#define RTL_SPI0_BASE                 ( RTL_PERIPH_BASE + 0x00042000 )
#define RTL_SPI1_BASE                 ( RTL_PERIPH_BASE + 0x00042400 )
#define RTL_SPI2_BASE                 ( RTL_PERIPH_BASE + 0x00042800 )
#define RTL_SPIC_BASE                 ( RTL_PERIPH_BASE + 0x00006000 )
#define RTL_SYS_BASE                  ( RTL_PERIPH_BASE + 0x00000000 )
#define RTL_TIMER_BASE                ( RTL_PERIPH_BASE + 0x00002000 )
#define RTL_UART0_BASE                ( RTL_PERIPH_BASE + 0x00040000 )
#define RTL_UART1_BASE                ( RTL_PERIPH_BASE + 0x00040400 )
#define RTL_UART2_BASE                ( RTL_PERIPH_BASE + 0x00040800 )
#define RTL_USBOTG_BASE               ( RTL_PERIPH_BASE + 0x000C0000 )
#define RTL_VENDOR_BASE               ( RTL_PERIPH_BASE + 0x00002800 )
#define RTL_WDG_BASE                  ( RTL_PERIPH_BASE + 0x00080000 )

// =================================================================================================
// RTL8195AM Peripheral Declaration
//
#define RTL_ADC                       ( (RTL_ADC_TypeDef    *) RTL_ADC_BASE    )
#define RTL_CRYPTO                    ( (RTL_CRYPTO_TypeDef *) RTL_CRYPTO_BASE )
#define RTL_DAC                       ( (RTL_DAC_TypeDef    *) RTL_DAC_BASE    )
#define RTL_GDMA0                     ( (RTL_GDMA_TypeDef   *) RTL_GDMA0_BASE  )
#define RTL_GDMA1                     ( (RTL_GDMA_TypeDef   *) RTL_GDMA1_BASE  )
#define RTL_GPIO                      ( (RTL_GPIO_TypeDef   *) RTL_GPIO_BASE   )
#define RTL_I2C0                      ( (RTL_I2C_TypeDef    *) RTL_I2C0_BASE   )
#define RTL_I2C1                      ( (RTL_I2C_TypeDef    *) RTL_I2C1_BASE   )
#define RTL_I2C2                      ( (RTL_I2C_TypeDef    *) RTL_I2C2_BASE   )
#define RTL_I2C3                      ( (RTL_I2C_TypeDef    *) RTL_I2C3_BASE   )
#define RTL_I2S0                      ( (RTL_I2S_TypeDef    *) RTL_I2S0_BASE   )
#define RTL_I2S1                      ( (RTL_I2S_TypeDef    *) RTL_I2S1_BASE   )
#define RTL_LOGU                      ( (RTL_LOGU_TypeDef   *) RTL_LOGU_BASE   )
#define RTL_MII                       ( (RTL_MII_TypeDef    *) RTL_MII_BASE    )
#define RTL_PCM0                      ( (RTL_PCM_TypeDef    *) RTL_PCM0_BASE   )
#define RTL_PCM1                      ( (RTL_PCM_TypeDef    *) RTL_PCM1_BASE   )
#define RTL_SDIOD                     ( (RTL_SDIOD_TypeDef  *) RTL_SDIOD_BASE  )
#define RTL_SDIOH                     ( (RTL_SDIOH_TypeDef  *) RTL_SDIOH_BASE  )
#define RTL_SDRC                      ( (RTL_SDRC_TypeDef   *) RTL_SDRC_BASE   )
#define RTL_SPI0                      ( (RTL_SPI_TypeDef    *) RTL_SPI0_BASE   )
#define RTL_SPI1                      ( (RTL_SPI_TypeDef    *) RTL_SPI1_BASE   )
#define RTL_SPI2                      ( (RTL_SPI_TypeDef    *) RTL_SPI2_BASE   )
#define RTL_SPIC                      ( (RTL_SPIC_TypeDef   *) RTL_SPIC_BASE   )
#define RTL_SYS                       ( (RTL_SYS_TypeDef    *) RTL_SYS_BASE    )
#define RTL_TIMER                     ( (RTL_TIMER_TypeDef  *) RTL_TIMER_BASE  )
#define RTL_UART0                     ( (RTL_UART_TypeDef   *) RTL_UART0_BASE  )
#define RTL_UART1                     ( (RTL_UART_TypeDef   *) RTL_UART1_BASE  )
#define RTL_UART2                     ( (RTL_UART_TypeDef   *) RTL_UART2_BASE  )
#define RTL_USB                       ( (RTL_USB_TypeDef    *) RTL_USB_BASE    )
#define RTL_WDG                       ( (RTL_WDG_TypeDef    *) RTL_WDG_BASE    )

#define RTL_PWM0                      ( (RTL_PWM_TypeDef    *) RTL_PWM0_BASE   )
#define RTL_PWM1                      ( (RTL_PWM_TypeDef    *) RTL_PWM1_BASE   )
#define RTL_PWM2                      ( (RTL_PWM_TypeDef    *) RTL_PWM2_BASE   )
#define RTL_PWM3                      ( (RTL_PWM_TypeDef    *) RTL_PWM3_BASE   )

#if ( 0 )
#include "rtl8195am_adc.h"
#include "rtl8195am_crypto.h"
#include "rtl8195am_dac.h"
#include "rtl8195am_efuse.h"
#include "rtl8195am_gdma.h"
#include "rtl8195am_gpio.h"
#include "rtl8195am_gspi.h"
#include "rtl8195am_i2c.h"
#include "rtl8195am_i2s.h"
#include "rtl8195am_irq.h"
#include "rtl8195am_logu.h"
#include "rtl8195am_mii.h"
#include "rtl8195am_nfc.h"
#include "rtl8195am_pcm.h"
#include "rtl8195am_pwm.h"
#include "rtl8195am_sdiod.h"
#include "rtl8195am_sdioh.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_spi.h"
#include "rtl8195am_spic.h"
#include "rtl8195am_system.h"
#include "rtl8195am_timer.h"
#include "rtl8195am_uart.h"
#include "rtl8195am_usb.h"
#include "rtl8195am_wdg.h"
#include "rtl8195am_wifi.h"

#include "rtl8195am_consol.h"
#include "rtl8195am_diag.h"
#include "rtl8195am_misc.h"
#include "rtl8195am_rtos.h"

#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RTL8195AM_H__

