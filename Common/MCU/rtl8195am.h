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
// RTL8195AM Analog to Digital Converter SAR (ADC)
//
typedef struct
{
  __IO uint32_t FIFO_READ;                                 //0x0000
  __IO uint32_t CONTROL;                                   //0x0004
  __IO uint32_t INTR_EN;                                   //0x0008
  __IO uint32_t INTR_STS;                                  //0x000C
  __IO uint32_t COMP_VALUE_L;                              //0x0010
  __IO uint32_t COMP_VALUE_H;                              //0x0014
  __IO uint32_t COMP_SET;                                  //0x0018
  __IO uint32_t POWER;                                     //0x001C
  __IO uint32_t ANAPAR_AD0;                                //0x0020
  __IO uint32_t ANAPAR_AD1;                                //0x0024
  __IO uint32_t ANAPAR_AD2;                                //0x0028
  __IO uint32_t ANAPAR_AD3;                                //0x002C
  __IO uint32_t ANAPAR_AD4;                                //0x0030
  __IO uint32_t ANAPAR_AD5;                                //0x0034
  __IO uint32_t CALI_DATA;                                 //0x0038
} RTL_ADC_TypeDef;

// =================================================================================================
// RTL8195AM System and Peripheral Controller
//
typedef struct
{
  // -----------------------------------------------------------------------------------------------
  // SYSTEM
  // -----------------------------------------------------------------------------------------------
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

  __IO uint32_t DummyC[ 8 ];                                // 0x00C0 ****

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

  // -----------------------------------------------------------------------------------------------
  // PERI_ON
  // -----------------------------------------------------------------------------------------------
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

/**
 * @brief Digital to Analog Converter
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_DAC_TypeDef;

/**
 * @brief GDMA Controller
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_GDMA_TypeDef;

/**
 * @brief GPIO General Purpose I/O
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_GPIO_TypeDef;

/**
 * @brief I2C Inter-integrated Circuit Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_I2C_TypeDef;

/**
 * @brief I2S Inter Inter-Iintegrated Circuit Sound Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_I2S_TypeDef;

/**
 * @brief MII Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_MII_TypeDef;

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
  __IO uint32_t CR;
} RTL_PCM_TypeDef;

/**
 * @brief PWM Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_PWM_TypeDef;

/**
 * @brief SSI Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_SSI_TypeDef;

/**
 * @brief UART Interface
 */
typedef struct
{
  __IO uint32_t CR;
} RTL_UART_TypeDef;

/**
 * @brief USB Interface
 */

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
// RTL8195AM Memory and Peripheral Map
//
#define RTL_ROM_BASE                  ((uint32_t)0x00000000) //  ROM base address in the alias region
#define RTL_SRAM_BASE                 ((uint32_t)0x10000000) //  SRAM base address in the alias region
#define RTL_TCM_BASE                  ((uint32_t)0x1FFF0000) //  TCM base address in the alias region
#define RTL_SDRAM_BASE                ((uint32_t)0x30000000) //  SDRAM base address in the alias region
#define RTL_PERIPH_BASE               ((uint32_t)0x40000000) //  Peripheral base address in the alias region
#define RTL_FLASH_BASE                ((uint32_t)0x98000000) //  FLASH base address in the alias region

#define RTL_SRAM_BB_BASE              ((uint32_t)0x00000000) //  SRAM base address in the bit-band region
#define RTL_PERIPH_BB_BASE            ((uint32_t)0x42000000) //  Peripheral base address in the bit-band region

//  Peripheral memory map
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
#define RTL_LOG_UART_BASE             ( RTL_PERIPH_BASE + 0x00003000 )
#define RTL_MII_BASE                  ( RTL_PERIPH_BASE + 0x00050000 )
#define RTL_NFC_INTERFACE_BASE        ( RTL_PERIPH_BASE + 0x00002400 )
#define RTL_PCM0_BASE                 ( RTL_PERIPH_BASE + 0x00064000 )
#define RTL_PCM1_BASE                 ( RTL_PERIPH_BASE + 0x00065000 )
#define RTL_SDIO_HOST_BASE            ( RTL_PERIPH_BASE + 0x00058000 )
#define RTL_SDR_CTRL_BASE             ( RTL_PERIPH_BASE + 0x00005000 )
#define RTL_SPI0_BASE                 ( RTL_PERIPH_BASE + 0x00042000 )
#define RTL_SPI1_BASE                 ( RTL_PERIPH_BASE + 0x00042400 )
#define RTL_SPI2_BASE                 ( RTL_PERIPH_BASE + 0x00042800 )
#define RTL_SPI_FLASH_CTRL_BASE       ( RTL_PERIPH_BASE + 0x00006000 )
#define RTL_SYS_BASE                  ( RTL_PERIPH_BASE + 0x00000000 )
#define RTL_TIMER_BASE                ( RTL_PERIPH_BASE + 0x00002000 )
#define RTL_UART0_BASE                ( RTL_PERIPH_BASE + 0x00040000 )
#define RTL_UART1_BASE                ( RTL_PERIPH_BASE + 0x00040400 )
#define RTL_UART2_BASE                ( RTL_PERIPH_BASE + 0x00040800 )
#define RTL_USB_OTG_BASE              ( RTL_PERIPH_BASE + 0x000C0000 )
#define RTL_VENDOR_BASE               ( RTL_PERIPH_BASE + 0x00002800 )
#define RTL_WDG_BASE                  ( RTL_PERIPH_BASE + 0x00080000 )
#define RTL_WIFI_BASE                 ( RTL_PERIPH_BASE + 0x00080000 )

#if (0 )

#define RTL_SYS_BASE                  ( RTL_PERIPH_BASE + 0x00000000 )
#define RTL_GPIO_BASE                 ( RTL_PERIPH_BASE + 0x00001000 )
#define RTL_TIMER_BASE                ( RTL_PERIPH_BASE + 0x00002000 )
#define RTL_NFC_INTERFACE_BASE        ( RTL_PERIPH_BASE + 0x00002400 )
#define RTL_VENDOR_BASE               ( RTL_PERIPH_BASE + 0x00002800 )
#define RTL_LOG_UART_BASE             ( RTL_PERIPH_BASE + 0x00003000 )
#define RTL_I2C2_BASE                 ( RTL_PERIPH_BASE + 0x00003400 )
#define RTL_I2C3_BASE                 ( RTL_PERIPH_BASE + 0x00003800 )
#define RTL_SDR_CTRL_BASE             ( RTL_PERIPH_BASE + 0x00005000 )
#define RTL_SPI_FLASH_CTRL_BASE       ( RTL_PERIPH_BASE + 0x00006000 )
#define RTL_ADC_BASE                  ( RTL_PERIPH_BASE + 0x00010000 )
#define RTL_DAC_BASE                  ( RTL_PERIPH_BASE + 0x00011000 )
#define RTL_UART0_BASE                ( RTL_PERIPH_BASE + 0x00040000 )
#define RTL_UART1_BASE                ( RTL_PERIPH_BASE + 0x00040400 )
#define RTL_UART2_BASE                ( RTL_PERIPH_BASE + 0x00040800 )
#define RTL_SPI0_BASE                 ( RTL_PERIPH_BASE + 0x00042000 )
#define RTL_SPI1_BASE                 ( RTL_PERIPH_BASE + 0x00042400 )
#define RTL_SPI2_BASE                 ( RTL_PERIPH_BASE + 0x00042800 )
#define RTL_I2C0_BASE                 ( RTL_PERIPH_BASE + 0x00044000 )
#define RTL_I2C1_BASE                 ( RTL_PERIPH_BASE + 0x00044400 )
#define RTL_MII_BASE                  ( RTL_PERIPH_BASE + 0x00050000 )
#define RTL_SDIO_HOST_BASE            ( RTL_PERIPH_BASE + 0x00058000 )
#define RTL_GDMA0_BASE                ( RTL_PERIPH_BASE + 0x00060000 )
#define RTL_GDMA1_BASE                ( RTL_PERIPH_BASE + 0x00061000 )
#define RTL_I2S0_BASE                 ( RTL_PERIPH_BASE + 0x00062000 )
#define RTL_I2S1_BASE                 ( RTL_PERIPH_BASE + 0x00063000 )
#define RTL_PCM0_BASE                 ( RTL_PERIPH_BASE + 0x00064000 )
#define RTL_PCM1_BASE                 ( RTL_PERIPH_BASE + 0x00065000 )
#define RTL_CRYPTO_BASE               ( RTL_PERIPH_BASE + 0x00070000 )
#define RTL_WIFI_BASE                 ( RTL_PERIPH_BASE + 0x00080000 )
#define RTL_USB_OTG_BASE              ( RTL_PERIPH_BASE + 0x000C0000 )
#define RTL_WDG_BASE                  ( RTL_PERIPH_BASE + 0x00080000 )

#endif

#define GDMA1_REG_OFF                 0x1000
#define I2S1_REG_OFF                  0x1000
#define PCM1_REG_OFF                  0x1000
#define SSI_REG_OFF                   0x400
#define RUART_REG_OFF                 0x400

// =================================================================================================
// RTL8195AM Peripheral Declaration
//
#define RTL_SYS                       ( (RTL_SYS_TypeDef *) RTL_SYS_BASE )
#define RTL_ADC                       ( (RTL_ADC_TypeDef *) RTL_ADC_BASE )

#include "rtl8195am_adc.h"
#include "rtl8195am_consol.h"
#include "rtl8195am_crypto.h"
#include "rtl8195am_dac.h"
#include "rtl8195am_diag.h"
#include "rtl8195am_efuse.h"
#include "rtl8195am_gdma.h"
#include "rtl8195am_gpio.h"
#include "rtl8195am_gspi.h"
#include "rtl8195am_i2c.h"
#include "rtl8195am_i2s.h"
#include "rtl8195am_irq.h"
#include "rtl8195am_log_uart.h"
#include "rtl8195am_mii.h"
#include "rtl8195am_misc.h"
#include "rtl8195am_nfc.h"
#include "rtl8195am_pcm.h"
#include "rtl8195am_pwm.h"
#include "rtl8195am_rtos.h"
#include "rtl8195am_sdio_device.h"
#include "rtl8195am_sdio_host.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_spic.h"
#include "rtl8195am_ssi.h"
#include "rtl8195am_system.h"
#include "rtl8195am_timer.h"
#include "rtl8195am_uart.h"
#include "rtl8195am_usb.h"
#include "rtl8195am_wdg.h"
#include "rtl8195am_wifi.h"

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RTL8195AM_H__

