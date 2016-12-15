#include "rtl8195am_irq.h"

typedef enum IRQx
{
  /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQx = -14,
  SysTick_IRQx = -1,
  /******  RTL8195A Specific Interrupt Numbers ************/
  SYSTEM_ON_IRQx = 0,
  PERIPHERAL_IRQx = 19,           // Handle IRQ[32..63] : HalPeripheralIntrHandle() in ROM
  GDMA1_CHANNEL5_IRQx = 31,
  /******  RTL8195A PERIPHERAL_IRQx Numbers : Status and Mask ************/
  I2C0_IRQx = 64,                 //
  LP_EXTENSION_IRQx = 93,         // Handle IRQ[96..127]
  PTA_TRX_IRQx = 95,              //
  /******  RTL8195A LP_EXTENSION_IRQx Numbers : Status and Mask ************/
  RXI300_IRQx = 96,
  NFC_IRQx = 97,
  LAST_IRQx = 127
} IRQx_Type;

// ---------------------------------------------------------------------------------------------------------------------
#define Reset_Handler             ( 0x00000100 )  // SP=0x1FFFFFFC, goto HalResetVsr()
#define NMI_Handler               ( 0x00000108 )  // Halt()
#define HardFault_Handler         ( 0x0000010C )  // call HalHardFaultHandler() : DebugPrint( ... )
#define MemManage_Handler         ( 0x00000120 )  // Halt()
#define BusFault_Handler          ( 0x00000124 )  // Halt()
#define UsageFault_Handler        ( 0x00000128 )  // Halt()

// ---------------------------------------------------------------------------------------------------------------------

#define NVIC_ROM_VECTOR_ADDRESS   ( 0x00000000 )  // Initial vector position at start of ROM : Copy to RAM
#define NVIC_ROM_VECTOR_SIZE      ( 0x00000100 )

#define NVIC_RAM_VECTOR_ADDRESS   ( 0x10000000 )  // Vectors positioned at start of RAM : Copy from ROM
#define NVIC_RAM_VECTOR_SIZE      ( 0x00000100 )

#define NVIC_USR_VECTOR_ADDRESS   ( 0x10000100 )  // PERIPHERAL_IRQ Handler Entry
#define NVIC_USR_VECTOR_SIZE      ( 0x00000100 )

#define NVIC_DAT_VECTOR_ADDRESS   ( 0x10000200 )  // PERIPHERAL_IRQ Handler Argment
#define NVIC_DAT_VECTOR_SIZE      ( 0x00000100 )

const uint32_t ROM_VectorTable[ 32 ] = {
  0x1FFFFFFC,               //
  Reset_Handler + 1,        //
  NMI_Handler + 1,          //
  HardFault_Handler + 1,    // call HalHardFaultHandler() : DebugPrint( ... )
  MemManage_Handler + 1,    //
  BusFault_Handler + 1,     //
  UsageFault_Handler + 1,   //
  0x00000000 };             // Other are 0x00000000

void NVIC_SetVector( IRQn_Type IRQn, uint32_t vector )
{
  uint32_t *vectors = (uint32_t *) SCB->VTOR;
  uint32_t i;

  // Copy and switch to dynamic vectors if the first time called
  if ( SCB->VTOR != NVIC_RAM_VECTOR_ADDRESS )
  {
    uint32_t *old_vectors = vectors;
    vectors = (uint32_t*) NVIC_RAM_VECTOR_ADDRESS;    // 0x1000-0000

    for ( i = 0; i < NVIC_NUM_VECTORS; i++ )
    {
      vectors[ i ] = old_vectors[ i ];
    }

    SCB->VTOR = (uint32_t) NVIC_RAM_VECTOR_ADDRESS;   // 0x1000-0000
  }

  vectors[ IRQn + NVIC_USER_IRQ_OFFSET ] = vector;
}

uint32_t NVIC_GetVector( IRQn_Type IRQn )
{
  uint32_t *vectors = (uint32_t*) SCB->VTOR;
  return vectors[ IRQn + NVIC_USER_IRQ_OFFSET ];
}

// ---------------------------------------------------------------------------------------------------------------------
// void VectorTableInitRTL8195A( void )
// {
//   RAM_VectorTable[0x00] = (StackPointer);
//   RAM_VectorTable[0x01] = (Reset_Handler + 1);
//   RAM_VectorTable[0x02] = (NMI_Handler + 1);
//   RAM_VectorTable[0x03] = (HardFault_Handler + 1);
//
//   RAM_VectorTable[0x10] = (HalSysOnIntrHandle + 1);
//   RAM_VectorTable[0x11] = (HalWdgIntrHandle + 1);
//   RAM_VectorTable[0x12] = (HalTimer0IntrHandle + 1);
//   RAM_VectorTable[0x13] = (HalTimer1IntrHandle + 1);
//   RAM_VectorTable[0x14] = (HalI2C3IntrHandle + 1);
//   RAM_VectorTable[0x15] = (HalTimer2To7IntrHandle + 1);
//   RAM_VectorTable[0x16] = (HalSpi0IntrHandle + 1);
//   RAM_VectorTable[0x17] = (HalGpioIntrHandle + 1);
//   RAM_VectorTable[0x18] = (HalUart0IntrHandle + 1);
//   RAM_VectorTable[0x19] = (HalSpiFlashIntrHandle + 1);
//   RAM_VectorTable[0x1A] = (HalUsbOtgIntrHandle + 1);
//   RAM_VectorTable[0x1B] = (HalSdioHostIntrHandle + 1);
//   RAM_VectorTable[0x1C] = (HalSdioDeviceIntrHandle + 1);
//   RAM_VectorTable[0x1D] = (HalI2s0OrPcm0IntrHandle + 1);
//   RAM_VectorTable[0x1E] = (HalI2s1OrPcm1IntrHandle + 1);
//   RAM_VectorTable[0x1F] = (HalWlDmaIntrHandle + 1);
//   RAM_VectorTable[0x20] = (HalWlProtocolIntrHandle + 1);
//   RAM_VectorTable[0x21] = (HalCryptoIntrHandle + 1);
//   RAM_VectorTable[0x22] = (HalGmacIntrHandle + 1);
//
//   RAM_VectorTable[0x23] = (HalPeripheralIntrHandle + 1);
//
//   RAM_VectorTable[0x24] = (HalGdma0Ch0IntrHandle + 1);
//   RAM_VectorTable[0x25] = (HalGdma0Ch1IntrHandle + 1);
//   RAM_VectorTable[0x26] = (HalGdma0Ch2IntrHandle + 1);
//   RAM_VectorTable[0x27] = (HalGdma0Ch3IntrHandle + 1);
//   RAM_VectorTable[0x28] = (HalGdma0Ch4IntrHandle + 1);
//   RAM_VectorTable[0x29] = (HalGdma0Ch5IntrHandle + 1);
//   RAM_VectorTable[0x2A] = (HalGdma1Ch0IntrHandle + 1);
//   RAM_VectorTable[0x2B] = (HalGdma1Ch1IntrHandle + 1);
//   RAM_VectorTable[0x2C] = (HalGdma1Ch2IntrHandle + 1);
//   RAM_VectorTable[0x2D] = (HalGdma1Ch3IntrHandle + 1);
//   RAM_VectorTable[0x2E] = (HalGdma1Ch4IntrHandle + 1);
//   RAM_VectorTable[0x2F] = (HalGdma1Ch5IntrHandle + 1);
// }
//
// void VectorTableOverrideRtl8195A()
// {
//   RAM_VectorTable[0x02] = HalNMIHandler_Patch;
//   RAM_VectorTable[0x03] = HalHardFaultHandler_Patch_asm;
// }
//
//void VectorTableInitForOSRtl8195A()
//{
//  RAM_VectorTable[0x0B] = vPortSVCHandler;
//  RAM_VectorTable[0x0E] = xPortPendSVHandler;
//  RAM_VectorTable[0x0F] = xPortSysTickHandler;
//}
//
// void InfraStart( void ) @ 0x1000-6000 : Image2 Entry
// {
//   VectorTableOverrideRtl8195A()
//   VectorTableInitForOSRtl8195A()
// }
// ---------------------------------------------------------------------------------------------------------------------

