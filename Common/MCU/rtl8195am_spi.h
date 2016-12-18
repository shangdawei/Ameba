#ifndef __RTL8195AM_SPI_H__
#define __RTL8195AM_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

#define SSI_DUMMY_DATA      0x00        // for master mode, we need to push a Dummy data to TX FIFO for read

#define SSI_CLK_SPI1        (PLATFORM_CLOCK/2)
#define SSI_CLK_SPI0_2      (PLATFORM_CLOCK/4)

/* Parameters of DW_apb_ssi for RTL8195A */
#define SSI_TX_FIFO_DEPTH  64
#define TX_ABW              6  // 1-8, log2(SSI_TX_FIFO_DEPTH)
#define SSI_RX_FIFO_DEPTH  64
#define RX_ABW              6  // 1-8, log2(SSI_RX_FIFO_DEPTH)

#define SSI0_REG_BASE  0x40042000
#define SSI1_REG_BASE  0x40042400
#define SSI2_REG_BASE  0x40042800

/* Memory Map of DW_apb_ssi */
#define REG_DW_SSI_CTRLR0          0x00  // 16 bits
#define REG_DW_SSI_CTRLR1          0x04  // 16 bits
#define REG_DW_SSI_SSIENR          0x08  //  1 bit
#define REG_DW_SSI_MWCR            0x0C  //  3 bits
#define REG_DW_SSI_SER             0x10  //
#define REG_DW_SSI_BAUDR           0x14  // 16 bits
#define REG_DW_SSI_TXFTLR          0x18  //  TX_ABW
#define REG_DW_SSI_RXFTLR          0x1C  //  RX_ABW
#define REG_DW_SSI_TXFLR           0x20  //
#define REG_DW_SSI_RXFLR           0x24  //
#define REG_DW_SSI_SR              0x28  //  7 bits
#define REG_DW_SSI_IMR             0x2C  //
#define REG_DW_SSI_ISR             0x30  //  6 bits
#define REG_DW_SSI_RISR            0x34  //  6 bits
#define REG_DW_SSI_TXOICR          0x38  //  1 bits
#define REG_DW_SSI_RXOICR          0x3C  //  1 bits
#define REG_DW_SSI_RXUICR          0x40  //  1 bits
#define REG_DW_SSI_MSTICR          0x44  //  1 bits
#define REG_DW_SSI_ICR             0x48  //  1 bits
#define REG_DW_SSI_DMACR           0x4C  //  2 bits
#define REG_DW_SSI_DMATDLR         0x50  //  TX_ABW
#define REG_DW_SSI_DMARDLR         0x54  //  RX_ABW
#define REG_DW_SSI_IDR             0x58  // 32 bits
#define REG_DW_SSI_COMP_VERSION    0x5C  // 32 bits
#define REG_DW_SSI_DR              0x60  // 16 bits 0x60-0xEC
#define REG_DW_SSI_RX_SAMPLE_DLY   0xF0  //  8 bits
#define REG_DW_SSI_RSVD_0          0xF4  // 32 bits
#define REG_DW_SSI_RSVD_1          0xF8  // 32 bits
#define REG_DW_SSI_RSVD_2          0xFC  // 32 bits

// CTRLR0          0x00  // 16 bits, 6.2.1
// DFS Reset Value: 0x7
#define BIT_SHIFT_CTRLR0_DFS       0
#define BIT_MASK_CTRLR0_DFS        0xF
#define BIT_CTRLR0_DFS(x)(((x) & BIT_MASK_CTRLR0_DFS) << BIT_SHIFT_CTRLR0_DFS)
#define BIT_INVC_CTRLR0_DFS (~(BIT_MASK_CTRLR0_DFS << BIT_SHIFT_CTRLR0_DFS))

#define BIT_SHIFT_CTRLR0_FRF       4
#define BIT_MASK_CTRLR0_FRF        0x3
#define BIT_CTRLR0_FRF(x)(((x) & BIT_MASK_CTRLR0_FRF) << BIT_SHIFT_CTRLR0_FRF)
#define BIT_INVC_CTRLR0_FRF (~(BIT_MASK_CTRLR0_FRF << BIT_SHIFT_CTRLR0_FRF))

#define BIT_SHIFT_CTRLR0_SCPH      6
#define BIT_MASK_CTRLR0_SCPH       0x1
#define BIT_CTRLR0_SCPH(x)(((x) & BIT_MASK_CTRLR0_SCPH) << BIT_SHIFT_CTRLR0_SCPH)
#define BIT_INVC_CTRLR0_SCPH (~(BIT_MASK_CTRLR0_SCPH << BIT_SHIFT_CTRLR0_SCPH))

#define BIT_SHIFT_CTRLR0_SCPOL     7
#define BIT_MASK_CTRLR0_SCPOL      0x1
#define BIT_CTRLR0_SCPOL(x)(((x) & BIT_MASK_CTRLR0_SCPOL) << BIT_SHIFT_CTRLR0_SCPOL)
#define BIT_INVC_CTRLR0_SCPOL (~(BIT_MASK_CTRLR0_SCPOL << BIT_SHIFT_CTRLR0_SCPOL))

#define BIT_SHIFT_CTRLR0_TMOD      8
#define BIT_MASK_CTRLR0_TMOD       0x3
#define BIT_CTRLR0_TMOD(x)(((x) & BIT_MASK_CTRLR0_TMOD) << BIT_SHIFT_CTRLR0_TMOD)
#define BIT_INVC_CTRLR0_TMOD (~(BIT_MASK_CTRLR0_TMOD << BIT_SHIFT_CTRLR0_TMOD))

#define BIT_SHIFT_CTRLR0_SLV_OE    10
#define BIT_MASK_CTRLR0_SLV_OE     0x1
#define BIT_CTRLR0_SLV_OE(x)(((x) & BIT_MASK_CTRLR0_SLV_OE) << BIT_SHIFT_CTRLR0_SLV_OE)
#define BIT_INVC_CTRLR0_SLV_OE (~(BIT_MASK_CTRLR0_SLV_OE << BIT_SHIFT_CTRLR0_SLV_OE))

#define BIT_SHIFT_CTRLR0_SRL       11
#define BIT_MASK_CTRLR0_SRL        0x1
#define BIT_CTRLR0_SRL(x)(((x) & BIT_MASK_CTRLR0_SRL) << BIT_SHIFT_CTRLR0_SRL)
#define BIT_INVC_CTRLR0_SRL (~(BIT_MASK_CTRLR0_SRL << BIT_SHIFT_CTRLR0_SRL))

#define BIT_SHIFT_CTRLR0_CFS       12
#define BIT_MASK_CTRLR0_CFS        0xF
#define BIT_CTRLR0_CFS(x)(((x) & BIT_MASK_CTRLR0_CFS) << BIT_SHIFT_CTRLR0_CFS)
#define BIT_INVC_CTRLR0_CFS (~(BIT_MASK_CTRLR0_CFS << BIT_SHIFT_CTRLR0_CFS))

// CTRLR1          0x04  // 16 bits
#define BIT_SHIFT_CTRLR1_NDF    0
#define BIT_MASK_CTRLR1_NDF     0xFFFF
#define BIT_CTRLR1_NDF(x)(((x) & BIT_MASK_CTRLR1_NDF) << BIT_SHIFT_CTRLR1_NDF)
#define BIT_INVC_CTRLR1_NDF (~(BIT_MASK_CTRLR1_NDF << BIT_SHIFT_CTRLR1_NDF))

// SSIENR          0x08  //  1 bit
#define BIT_SHIFT_SSIENR_SSI_EN    0
#define BIT_MASK_SSIENR_SSI_EN     0x1
#define BIT_SSIENR_SSI_EN(x)(((x) & BIT_MASK_SSIENR_SSI_EN) << BIT_SHIFT_SSIENR_SSI_EN)
#define BIT_INVC_SSIENR_SSI_EN (~(BIT_MASK_SSIENR_SSI_EN << BIT_SHIFT_SSIENR_SSI_EN))

// MWCR            0x0c  //  3 bits
#define BIT_SHIFT_MWCR_MWMOD    0
#define BIT_MASK_MWCR_MWMOD     0x1
#define BIT_MWCR_MWMOD(x)(((x) & BIT_MASK_MWCR_MWMOD) << BIT_SHIFT_MWCR_MWMOD)
#define BIT_INVC_MWCR_MWMOD (~(BIT_MASK_MWCR_MWMOD << BIT_SHIFT_MWCR_MWMOD))

#define BIT_SHIFT_MWCR_MDD      1
#define BIT_MASK_MWCR_MDD       0x1
#define BIT_MWCR_MDD(x)(((x) & BIT_MASK_MWCR_MDD) << BIT_SHIFT_MWCR_MDD)
#define BIT_INVC_MWCR_MDD (~(BIT_MASK_MWCR_MDD << BIT_SHIFT_MWCR_MDD))

#define BIT_SHIFT_MWCR_MHS      2
#define BIT_MASK_MWCR_MHS       0x1
#define BIT_MWCR_MHS(x)(((x) & BIT_MASK_MWCR_MHS) << BIT_SHIFT_MWCR_MHS)
#define BIT_INVC_MWCR_MHS (~(BIT_MASK_MWCR_MHS << BIT_SHIFT_MWCR_MHS))

// SER             0x10   // Variable Length
#define BIT_SHIFT_SER_SER    0
#define BIT_MASK_SER_SER     0xFF
#define BIT_SER_SER(x)(((x) & BIT_MASK_SER_SER) << BIT_SHIFT_SER_SER)
#define BIT_INVC_SER_SER (~(BIT_MASK_SER_SER << BIT_SHIFT_SER_SER))

// BAUDR           0x14  // 16 bits
#define BIT_SHIFT_BAUDR_SCKDV    0
#define BIT_MASK_BAUDR_SCKDV     0xFFFF
#define BIT_BAUDR_SCKDV(x)(((x) & BIT_MASK_BAUDR_SCKDV) << BIT_SHIFT_BAUDR_SCKDV)
#define BIT_INVC_BAUDR_SCKDV (~(BIT_MASK_BAUDR_SCKDV << BIT_SHIFT_BAUDR_SCKDV))

// TXFLTR          0x18        // Variable Length
#define BIT_SHIFT_TXFTLR_TFT    0
#define BIT_MASK_TXFTLR_TFT     0x3F  // (TX_ABW-1):0
#define BIT_TXFTLR_TFT(x)(((x) & BIT_MASK_TXFTLR_TFT) << BIT_SHIFT_TXFTLR_TFT)
#define BIT_INVC_TXFTLR_TFT (~(BIT_MASK_TXFTLR_TFT << BIT_SHIFT_TXFTLR_TFT))

// RXFLTR          0x1c        // Variable Length
#define BIT_SHIFT_RXFTLR_RFT    0
#define BIT_MASK_RXFTLR_RFT     0x3F  // (RX_ABW-1):0
#define BIT_RXFTLR_RFT(x)(((x) & BIT_MASK_RXFTLR_RFT) << BIT_SHIFT_RXFTLR_RFT)
#define BIT_INVC_RXFTLR_RFT (~(BIT_MASK_RXFTLR_RFT << BIT_SHIFT_RXFTLR_RFT))

// TXFLR           0x20  // see     [READ ONLY]
#define BIT_MASK_TXFLR_TXTFL    0x7F  // (TX_ABW):0

// RXFLR           0x24  // see     [READ ONLY]
#define BIT_MASK_RXFLR_RXTFL    0x7F  // (RX_ABW):0

// SR              0x28  //  7 bits [READ ONLY]
#define BIT_SR_BUSY  BIT0
#define BIT_SR_TFNF  BIT1
#define BIT_SR_TFE   BIT2
#define BIT_SR_RFNE  BIT3
#define BIT_SR_RFF   BIT4
#define BIT_SR_TXE   BIT5
#define BIT_SR_DCOL  BIT6

// IMR             0x2c  // see
#define BIT_SHIFT_IMR_TXEIM    0
#define BIT_MASK_IMR_TXEIM     0x1
// #define BIT_IMR_TXEIM(x)(((x) & BIT_MASK_IMR_TXEIM) << BIT_SHIFT_IMR_TXEIM)
#define BIT_INVC_IMR_TXEIM (~(BIT_MASK_IMR_TXEIM << BIT_SHIFT_IMR_TXEIM))

#define BIT_SHIFT_IMR_TXOIM    1
#define BIT_MASK_IMR_TXOIM     0x1
// #define BIT_IMR_TXOIM(x)(((x) & BIT_MASK_IMR_TXOIM) << BIT_SHIFT_IMR_TXOIM)
#define BIT_INVC_IMR_TXOIM (~(BIT_MASK_IMR_TXOIM << BIT_SHIFT_IMR_TXOIM))

#define BIT_SHIFT_IMR_RXUIM    2
#define BIT_MASK_IMR_RXUIM     0x1
// #define BIT_IMR_RXUIM(x)(((x) & BIT_MASK_IMR_RXUIM) << BIT_SHIFT_IMR_RXUIM)
#define BIT_INVC_IMR_RXUIM (~(BIT_MASK_IMR_RXUIM << BIT_SHIFT_IMR_RXUIM))

#define BIT_SHIFT_IMR_RXOIM    3
#define BIT_MASK_IMR_RXOIM     0x1
// #define BIT_IMR_RXOIM(x)(((x) & BIT_MASK_IMR_RXOIM) << BIT_SHIFT_IMR_RXOIM)
#define BIT_INVC_IMR_RXOIM (~(BIT_MASK_IMR_RXOIM << BIT_SHIFT_IMR_RXOIM))

#define BIT_SHIFT_IMR_RXFIM    4
#define BIT_MASK_IMR_RXFIM     0x1
// #define BIT_IMR_RXFIM(x)(((x) & BIT_MASK_IMR_RXFIM) << BIT_SHIFT_IMR_RXFIM)
#define BIT_INVC_IMR_RXFIM (~(BIT_MASK_IMR_RXFIM << BIT_SHIFT_IMR_RXFIM))

#define BIT_SHIFT_IMR_MSTIM    5
#define BIT_MASK_IMR_MSTIM     0x1
// #define BIT_IMR_MSTIM(x)(((x) & BIT_MASK_IMR_MSTIM) << BIT_SHIFT_IMR_MSTIM)
#define BIT_INVC_IMR_MSTIM (~(BIT_MASK_IMR_MSTIM << BIT_SHIFT_IMR_MSTIM))

#define BIT_IMR_TXEIM  BIT0
#define BIT_IMR_TXOIM  BIT1
#define BIT_IMR_RXUIM  BIT2
#define BIT_IMR_RXOIM  BIT3
#define BIT_IMR_RXFIM  BIT4
#define BIT_IMR_MSTIM  BIT5

// ISR             0x30  //  6 bits [READ ONLY]
#define BIT_ISR_TXEIS  BIT0
#define BIT_ISR_TXOIS  BIT1
#define BIT_ISR_RXUIS  BIT2
#define BIT_ISR_RXOIS  BIT3
#define BIT_ISR_RXFIS  BIT4
#define BIT_ISR_MSTIS  BIT5

// RISR            0x34  //  6 bits [READ ONLY]
#define BIT_RISR_TXEIR  BIT0
#define BIT_RISR_TXOIR  BIT1
#define BIT_RISR_RXUIR  BIT2
#define BIT_RISR_RXOIR  BIT3
#define BIT_RISR_RXFIR  BIT4
#define BIT_RISR_MSTIR  BIT5

// TXOICR          0x38  //  1 bits [READ ONLY]
// RXOICR          0x3c  //  1 bits [READ ONLY]
// RXUICR          0x40  //  1 bits [READ ONLY]
// MSTICR          0x44  //  1 bits [READ ONLY]
// ICR             0x48  //  1 bits [READ ONLY]

// DMACR           0x4c  //  2 bits
#define BIT_SHIFT_DMACR_RDMAE    0
#define BIT_MASK_DMACR_RDMAE     0x1
#define BIT_DMACR_RDMAE(x)(((x) & BIT_MASK_DMACR_RDMAE) << BIT_SHIFT_DMACR_RDMAE)
#define BIT_INVC_DMACR_RDMAE (~(BIT_MASK_DMACR_RDMAE << BIT_SHIFT_DMACR_RDMAE))

#define BIT_SHIFT_DMACR_TDMAE    1
#define BIT_MASK_DMACR_TDMAE     0x1
#define BIT_DMACR_TDMAE(x)(((x) & BIT_MASK_DMACR_TDMAE) << BIT_SHIFT_DMACR_TDMAE)
#define BIT_INVC_DMACR_TDMAE (~(BIT_MASK_DMACR_TDMAE << BIT_SHIFT_DMACR_TDMAE))

// DMATDLR         0x50
#define BIT_SHIFT_DMATDLR_DMATDL    0
#define BIT_MASK_DMATDLR_DMATDL     0x3F  // (TX_ABW-1):0
#define BIT_DMATDLR_DMATDL(x)(((x) & BIT_MASK_DMATDLR_DMATDL) << BIT_SHIFT_DMATDLR_DMATDL)
#define BIT_INVC_DMATDLR_DMATDL (~(BIT_MASK_DMATDLR_DMATDL << BIT_SHIFT_DMATDLR_DMATDL))

// DMARDLR         0x54
#define BIT_SHIFT_DMARDLR_DMARDL    0
#define BIT_MASK_DMARDLR_DMARDL     0x3F  // (RX_ABW-1):0
#define BIT_DMARDLR_DMARDL(x)(((x) & BIT_MASK_DMARDLR_DMARDL) << BIT_SHIFT_DMARDLR_DMARDL)
#define BIT_INVC_DMARDLR_DMARDL (~(BIT_MASK_DMARDLR_DMARDL << BIT_SHIFT_DMARDLR_DMARDL))

// IDR             0x58  // 32 bits [READ ONLY]
// COMP_VERSION    0x5c  // 32 bits [READ ONLY]

// DR              0x60  // 16 bits 0x60-0xEC
#define BIT_SHIFT_DR_DR    0
#define BIT_MASK_DR_DR     0xFFFF
#define BIT_DR_DR(x)(((x) & BIT_MASK_DR_DR) << BIT_SHIFT_DR_DR)
#define BIT_INVC_DR_DR (~(BIT_MASK_DR_DR << BIT_SHIFT_DR_DR))

// RX_SAMPLE_DLY   0xF0  //  8 bits
#define BIT_SHIFT_RX_SAMPLE_DLY_RSD    0
#define BIT_MASK_RX_SAMPLE_DLY_RSD     0xFFFF
#define BIT_RX_SAMPLE_DLY_RSD(x)(((x) & BIT_MASK_RX_SAMPLE_DLY_RSD) << BIT_SHIFT_RX_SAMPLE_DLY_RSD)
#define BIT_INVC_RX_SAMPLE_DLY_RSD (~(BIT_MASK_RX_SAMPLE_DLY_RSD << BIT_SHIFT_RX_SAMPLE_DLY_RSD))

// RSVD_0          0xF4  // 32 bits
// RSVD_1          0xF8  // 32 bits
// RSVD_2          0xFC  // 32 bits

// SSI0 Pinmux
#define BIT_SHIFT_SSI0_PIN_EN    0
#define BIT_MASK_SSI0_PIN_EN     0x1
#define BIT_SSI0_PIN_EN(x)(((x) & BIT_MASK_SSI0_PIN_EN) << BIT_SHIFT_SSI0_PIN_EN)
#define BIT_INVC_SSI0_PIN_EN (~(BIT_MASK_SSI0_PIN_EN << BIT_SHIFT_SSI0_PIN_EN))

#define BIT_SHIFT_SSI0_PIN_SEL    1
#define BIT_MASK_SSI0_PIN_SEL     0x7
#define BIT_SSI0_PIN_SEL(x)(((x) & BIT_MASK_SSI0_PIN_SEL) << BIT_SHIFT_SSI0_PIN_SEL)
#define BIT_INVC_SSI0_PIN_SEL (~(BIT_MASK_SSI0_PIN_SEL << BIT_SHIFT_SSI0_PIN_SEL))

// SSI1 Pinmux
#define BIT_SHIFT_SSI1_PIN_EN    4
#define BIT_MASK_SSI1_PIN_EN     0x1
#define BIT_SSI1_PIN_EN(x)(((x) & BIT_MASK_SSI1_PIN_EN) << BIT_SHIFT_SSI1_PIN_EN)
#define BIT_INVC_SSI1_PIN_EN (~(BIT_MASK_SSI1_PIN_EN << BIT_SHIFT_SSI1_PIN_EN))

#define BIT_SHIFT_SSI1_PIN_SEL    5
#define BIT_MASK_SSI1_PIN_SEL     0x7
#define BIT_SSI1_PIN_SEL(x)(((x) & BIT_MASK_SSI1_PIN_SEL) << BIT_SHIFT_SSI1_PIN_SEL)
#define BIT_INVC_SSI1_PIN_SEL (~(BIT_MASK_SSI1_PIN_SEL << BIT_SHIFT_SSI1_PIN_SEL))

// SSI2 Pinmux
#define BIT_SHIFT_SSI2_PIN_EN    8
#define BIT_MASK_SSI2_PIN_EN     0x1
#define BIT_SSI2_PIN_EN(x)(((x) & BIT_MASK_SSI2_PIN_EN) << BIT_SHIFT_SSI2_PIN_EN)
#define BIT_INVC_SSI2_PIN_EN (~(BIT_MASK_SSI2_PIN_EN << BIT_SHIFT_SSI2_PIN_EN))

#define BIT_SHIFT_SSI2_PIN_SEL    9
#define BIT_MASK_SSI2_PIN_SEL     0x7
#define BIT_SSI2_PIN_SEL(x)(((x) & BIT_MASK_SSI2_PIN_SEL) << BIT_SHIFT_SSI2_PIN_SEL)
#define BIT_INVC_SSI2_PIN_SEL (~(BIT_MASK_SSI2_PIN_SEL << BIT_SHIFT_SSI2_PIN_SEL))

// SSI0 Multiple Chip Selection (Pinmux Select is controlled by BIT_SSI0_PIN_SEL)
#define BIT_SHIFT_SSI0_MULTI_CS_EN    28
#define BIT_MASK_SSI0_MULTI_CS_EN     0x1
#define BIT_SSI0_MULTI_CS_EN(x)(((x) & BIT_MASK_SSI0_MULTI_CS_EN) << BIT_SHIFT_SSI0_MULTI_CS_EN)
#define BIT_INVC_SSI0_MULTI_CS_EN (~(BIT_MASK_SSI0_MULTI_CS_EN << BIT_SHIFT_SSI0_MULTI_CS_EN))

#define HAL_SSI_READ32(SsiIndex, addr)         \
    HAL_READ32(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr)
#define HAL_SSI_WRITE32(SsiIndex, addr, value) \
    HAL_WRITE32(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr, value)
#define HAL_SSI_READ16(SsiIndex, addr)         \
    HAL_READ16(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr)
#define HAL_SSI_WRITE16(SsiIndex, addr, value) \
    HAL_WRITE16(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr, value)
#define HAL_SSI_READ8(SsiIndex, addr)          \
    HAL_READ8(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr)
#define HAL_SSI_WRITE8(SsiIndex, addr, value)  \
    HAL_WRITE8(SPI0_REG_BASE+ (SsiIndex*SSI_REG_OFF), addr, value)

// SSI Pinmux Select
typedef enum _SSI0_PINMUX_SELECT_
{
  SSI0_MUX_TO_GPIOE = S0,
  SSI0_MUX_TO_GPIOC = S1
} SSI0_PINMUX_SELECT, *PSSI0_PINMUX_SELECT;

typedef enum _SSI1_PINMUX_SELECT_
{
  SSI1_MUX_TO_GPIOA = S0,
  SSI1_MUX_TO_GPIOB = S1,
  SSI1_MUX_TO_GPIOD = S2
} SSI1_PINMUX_SELECT, *PSSI1_PINMUX_SELECT;

typedef enum _SSI2_PINMUX_SELECT_
{
  SSI2_MUX_TO_GPIOG = S0,
  SSI2_MUX_TO_GPIOE = S1,
  SSI2_MUX_TO_GPIOD = S2
} SSI2_PINMUX_SELECT, *PSSI2_PINMUX_SELECT;

typedef enum _SSI0_MULTI_CS_PINMUX_SELECT_
{
  SSI0_CS_MUX_TO_GPIOE = S0,
  SSI0_CS_MUX_TO_GPIOC = S1
} SSI0_MULTI_CS_PINMUX_SELECT, *PSSI0_MULTI_CS_PINMUX_SELECT;

typedef enum _SSI_CTRLR0_TMOD_
{
  TMOD_TR = 0,
  TMOD_TO = 1,
  TMOD_RO = 2,
  TMOD_EEPROM_R = 3
} SSI_CTRLR0_TMOD, *PSSI_CTRLR0_TMOD;

typedef enum _SSI_CTRLR0_SCPOL_
{
  SCPOL_INACTIVE_IS_LOW = 0,
  SCPOL_INACTIVE_IS_HIGH = 1
} SSI_CTRLR0_SCPOL, *PSSI_CTRLR0_SCPOL;

typedef enum _SSI_CTRLR0_SCPH_
{
  SCPH_TOGGLES_IN_MIDDLE = 0,
  SCPH_TOGGLES_AT_START = 1
} SSI_CTRLR0_SCPH, *PSSI_CTRLR0_SCPH;

typedef enum _SSI_CTRLR0_DFS_
{
  DFS_4_BITS = 3,
  DFS_5_BITS = 4,
  DFS_6_BITS = 5,
  DFS_7_BITS = 6,
  DFS_8_BITS = 7,
  DFS_9_BITS = 8,
  DFS_10_BITS = 9,
  DFS_11_BITS = 10,
  DFS_12_BITS = 11,
  DFS_13_BITS = 12,
  DFS_14_BITS = 13,
  DFS_15_BITS = 14,
  DFS_16_BITS = 15,
} SSI_CTRLR0_DFS, *PSSI_CTRLR0_DFS;

typedef enum _SSI_CTRLR0_CFS_
{
  CFS_1_BIT = 0,
  CFS_2_BITS = 1,
  CFS_3_BITS = 2,
  CFS_4_BITS = 3,
  CFS_5_BITS = 4,
  CFS_6_BITS = 5,
  CFS_7_BITS = 6,
  CFS_8_BITS = 7,
  CFS_9_BITS = 8,
  CFS_10_BITS = 9,
  CFS_11_BITS = 10,
  CFS_12_BITS = 11,
  CFS_13_BITS = 12,
  CFS_14_BITS = 13,
  CFS_15_BITS = 14,
  CFS_16_BITS = 15
} SSI_CTRLR0_CFS, *PSSI_CTRLR0_CFS;

typedef enum _SSI_CTRLR0_SLV_OE_
{
  SLV_TXD_ENABLE = 0,
  SLV_TXD_DISABLE = 1
} SSI_CTRLR0_SLV_OE, *PSSI_CTRLR0_SLV_OE;

typedef enum _SSI_ROLE_SELECT_
{
  SSI_SLAVE = 0,
  SSI_MASTER = 1
} SSI_ROLE_SELECT, *PSSI_ROLE_SELECT;

typedef enum _SSI_FRAME_FORMAT_
{
  FRF_MOTOROLA_SPI = 0,
  FRF_TI_SSP = 1,
  FRF_NS_MICROWIRE = 2,
  FRF_RSVD = 3
} SSI_FRAME_FORMAT, *PSSI_FRAME_FORMAT;

typedef enum _SSI_DMACR_ENABLE_
{
  SSI_NODMA = 0,
  SSI_RXDMA_ENABLE = 1,
  SSI_TXDMA_ENABLE = 2,
  SSI_TRDMA_ENABLE = 3
} SSI_DMACR_ENABLE, *PSSI_DMACR_ENABLE;

typedef enum _SSI_MWCR_HANDSHAKE_
{
  MW_HANDSHAKE_DISABLE = 0,
  MW_HANDSHAKE_ENABLE = 1
} SSI_MWCR_HANDSHAKE, *PSSI_MWCR_HANDSHAKE;

typedef enum _SSI_MWCR_DIRECTION_
{
  MW_DIRECTION_SLAVE_TO_MASTER = 0,
  MW_DIRECTION_MASTER_TO_SLAVE = 1
} SSI_MWCR_DIRECTION, *PSSI_MWCR_DIRECTION;

typedef enum _SSI_MWCR_TMOD_
{
  MW_TMOD_NONSEQUENTIAL = 0,
  MW_TMOD_SEQUENTIAL = 1
} SSI_MWCR_TMOD, *PSSI_MWCR_TMOD;

typedef enum _SSI_DATA_TRANSFER_MECHANISM_
{
  SSI_DTM_BASIC,
  SSI_DTM_INTERRUPT,
  SSI_DTM_DMA
} SSI_DATA_TRANSFER_MECHANISM, *PSSI_DATA_TRANSFER_MECHANISM;

_LONG_CALL_ HAL_STATUS HalSsiPinmuxEnableRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ HAL_STATUS HalSsiEnableRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ HAL_STATUS HalSsiDisableRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiInitRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiSetSclkPolarityRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiSetSclkPhaseRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiWriteRtl8195a( VOID *Adaptor, u32 value );
_LONG_CALL_ HAL_STATUS HalSsiLoadSettingRtl8195a( VOID *Adaptor, VOID *Setting );
_LONG_CALL_ROM_ HAL_STATUS HalSsiSetInterruptMaskRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiSetDeviceRoleRtl8195a( VOID *Adaptor, u32 Role );
_LONG_CALL_ HAL_STATUS HalSsiInterruptEnableRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiInterruptDisableRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiReadInterruptRtl8195a( VOID *Adaptor, VOID *RxData, u32 Length );
_LONG_CALL_ROM_ HAL_STATUS HalSsiSetRxFifoThresholdLevelRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiSetTxFifoThresholdLevelRtl8195a( VOID *Adaptor );
_LONG_CALL_ HAL_STATUS HalSsiWriteInterruptRtl8195a( VOID *Adaptor, VOID *TxData, u32 Length );
_LONG_CALL_ROM_ HAL_STATUS HalSsiSetSlaveEnableRegisterRtl8195a( VOID *Adaptor, u32 SlaveIndex );
_LONG_CALL_ROM_ u32 HalSsiBusyRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiWriteableRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiReadableRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiGetInterruptMaskRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiGetRxFifoLevelRtl8195a( VOID *Adaptor );
_LONG_CALL_ u32 HalSsiGetTxFifoLevelRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiGetStatusRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiGetInterruptStatusRtl8195a( VOID *Adaptor );
_LONG_CALL_ u32 HalSsiReadRtl8195a( VOID *Adaptor );
_LONG_CALL_ u32 HalSsiGetRawInterruptStatusRtl8195a( VOID *Adaptor );
_LONG_CALL_ROM_ u32 HalSsiGetSlaveEnableRegisterRtl8195a( VOID *Adaptor );

_LONG_CALL_ROM_ VOID _SsiReadInterrupt( VOID *Adaptor );
_LONG_CALL_ROM_ VOID _SsiWriteInterrupt( VOID *Adaptor );
_LONG_CALL_ u32 _SsiIrqHandle( VOID *Adaptor );

// ROM code patch
VOID _SsiReadInterruptRtl8195a( VOID *Adapter );
VOID _SsiWriteInterruptRtl8195a( VOID *Adapter );
HAL_STATUS HalSsiInitRtl8195a_Patch( VOID *Adaptor );
HAL_STATUS HalSsiPinmuxEnableRtl8195a_Patch( VOID *Adaptor );
HAL_STATUS HalSsiPinmuxDisableRtl8195a( VOID *Adaptor );
HAL_STATUS HalSsiDeInitRtl8195a( VOID * Adapter );
HAL_STATUS HalSsiClockOffRtl8195a( VOID * Adapter );
HAL_STATUS HalSsiClockOnRtl8195a( VOID * Adapter );
VOID HalSsiSetSclkRtl8195a( VOID *Adapter, u32 ClkRate );
HAL_STATUS HalSsiIntReadRtl8195a( VOID *Adapter, VOID *RxData, u32 Length );
HAL_STATUS HalSsiIntWriteRtl8195a( VOID *Adapter, u8 *pTxData, u32 Length );
VOID HalSsiTxFIFOThresholdRtl8195a( VOID *Adaptor, u32 txftl );
HAL_STATUS HalSsiEnterCriticalRtl8195a( VOID * Data );
HAL_STATUS HalSsiExitCriticalRtl8195a( VOID * Data );
HAL_STATUS HalSsiIsTimeoutRtl8195a( u32 StartCount, u32 TimeoutCnt );
HAL_STATUS HalSsiStopRecvRtl8195a( VOID * Data );

#if CONFIG_CHIP_E_CUT
HAL_STATUS HalSsiPinmuxEnableRtl8195a_V04(VOID *Adaptor);
HAL_STATUS HalSsiPinmuxDisableRtl8195a_V04(VOID * Adaptor);
VOID _SsiReadInterruptRtl8195a_V04(VOID *Adapter);
VOID _SsiWriteInterruptRtl8195a_V04(VOID *Adapter);
HAL_STATUS HalSsiInitRtl8195a_V04(VOID *Adaptor);
HAL_STATUS HalSsiSetFormatRtl8195a_V04(VOID * Adaptor);
HAL_STATUS HalSsiDeInitRtl8195a_V04(VOID *Adapter);
HAL_STATUS HalSsiIntReadRtl8195a_V04(VOID *Adapter, VOID *RxData, u32 Length);
HAL_STATUS HalSsiIntWriteRtl8195a_V04(VOID *Adapter, u8 *pTxData, u32 Length);
HAL_STATUS HalSsiClockOffRtl8195a_V04(VOID * Adapter);
HAL_STATUS HalSsiClockOnRtl8195a_V04(VOID * Adapter);
VOID HalSsiSetSclkRtl8195a_V04(VOID *Adapter, u32 ClkRate);
VOID HalSsiTxGdmaLoadDefRtl8195a_V04(IN VOID * Adapter);
VOID HalSsiRxGdmaLoadDefRtl8195a_V04(IN VOID * Adapter);
VOID HalSsiDmaInitRtl8195a_V04(VOID *Adapter);
HAL_STATUS HalSsiDmaSendRtl8195a_V04(IN VOID * Adapter, IN u8 * pTxData, IN u32 Length);
HAL_STATUS HalSsiDmaRecvRtl8195a_V04(IN VOID * Adapter, IN u8 * pRxData, IN u32 Length);
HAL_STATUS HalSsiDmaSendMultiBlockRtl8195a_V04(VOID * Adapter, u8 * pTxData, u32 Length);
HAL_STATUS HalSsiDmaRecvMultiBlockRtl8195a_V04(VOID * Adapter, u8 * pRxData, u32 Length);

#endif

#ifdef CONFIG_GDMA_EN
VOID HalSsiTxGdmaLoadDefRtl8195a(VOID *Adapter);
VOID HalSsiRxGdmaLoadDefRtl8195a(VOID *Adapter);
VOID HalSsiDmaInitRtl8195a(VOID *Adapter);
HAL_STATUS HalSsiDmaSendRtl8195a(VOID *Adapter, u8 *pTxData, u32 Length);
HAL_STATUS HalSsiDmaRecvRtl8195a(VOID *Adapter, u8 *pRxData, u32 Length);
HAL_STATUS HalSsiDmaSendMultiBlockRtl8195a(VOID * Adapter, u8 * pRxData, u32 Length);
HAL_STATUS HalSsiDmaRecvMultiBlockRtl8195a(VOID * Adapter, u8 * pRxData, u32 Length);

#endif  // end of "#ifdef CONFIG_GDMA_EN"

/**
 * LOG Configurations
 */

extern u32 SSI_DBG_CONFIG;
extern uint8_t SPI0_IS_AS_SLAVE;

#define SSI_DBG_ENTRANCE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENTRANCE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE ANSI_COLOR_GREEN __VA_ARGS__ ANSI_COLOR_RESET); \
}while(0)

#define SSI_DBG_INIT(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INIT_V(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_V)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INIT_VV(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INIT_VV)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_PINMUX(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_PINMUX)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_ENDIS(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_ENDIS)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_V(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_V)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_HNDLR(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_HNDLR)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_READ(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_READ)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_INT_WRITE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_INT_WRITE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_STATUS(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_STATUS)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_FIFO(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_FIFO)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_READ(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_READ)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_WRITE(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_WRITE)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

#define SSI_DBG_SLV_CTRL(...)  do {\
    if (unlikely(SSI_DBG_CONFIG & DBG_TYPE_SLV_CTRL)) \
        DBG_SSI_INFO(IDENT_FOUR_SPACE __VA_ARGS__); \
}while(0)

typedef enum _SSI_DBG_TYPE_LIST_
{
  DBG_TYPE_ENTRANCE = 1 << 0,
  DBG_TYPE_INIT = 1 << 1,
  DBG_TYPE_INIT_V = 1 << 2,
  DBG_TYPE_INIT_VV = 1 << 3,
  DBG_TYPE_PINMUX = 1 << 4,
  DBG_TYPE_ENDIS = 1 << 5,
  DBG_TYPE_INT = 1 << 6,
  DBG_TYPE_INT_V = 1 << 7,
  DBG_TYPE_INT_HNDLR = 1 << 8,
  DBG_TYPE_INT_READ = 1 << 9,
  DBG_TYPE_INT_WRITE = 1 << 10,
  DBG_TYPE_STATUS = 1 << 11,
  DBG_TYPE_FIFO = 1 << 12,
  DBG_TYPE_READ = 1 << 13,
  DBG_TYPE_WRITE = 1 << 14,
  DBG_TYPE_SLV_CTRL = 1 << 15
} SSI_DBG_TYPE_LIST, *PSSI_DBG_TYPE_LIST;

typedef struct _SSI_DMA_CONFIG_
{
  VOID *pHalGdmaOp;
  VOID *pTxHalGdmaAdapter;
  VOID *pRxHalGdmaAdapter;
  u8 RxDmaBurstSize;
  u8 TxDmaBurstSize;
  u8 RxDmaEnable;
  u8 TxDmaEnable;
  IRQ_HANDLE RxGdmaIrqHandle;
  IRQ_HANDLE TxGdmaIrqHandle;
} SSI_DMA_CONFIG, *PSSI_DMA_CONFIG;

#ifdef CONFIG_GDMA_EN
typedef struct _HAL_SSI_DMA_MULTIBLK_
{
  volatile GDMA_CH_LLI_ELE GdmaChLli[16];
  struct GDMA_CH_LLI Lli[16];
  struct BLOCK_SIZE_LIST BlockSizeList[16];
}SSI_DMA_MULTIBLK, *PSSI_DMA_MULTIBLK;
#endif
/**
 * DesignWare SSI Configurations
 */
typedef struct _HAL_SSI_ADAPTOR_
{
  SSI_DMA_CONFIG DmaConfig;
  IRQ_HANDLE IrqHandle;
  //
  VOID (*RxCompCallback)( VOID *Para );
  VOID *RxCompCbPara;
  VOID *RxData;
  VOID (*TxCompCallback)( VOID *Para );
  VOID *TxCompCbPara;
  VOID *TxData;
  u32 DmaRxDataLevel;
  u32 DmaTxDataLevel;
  u32 InterruptPriority;
  u32 RxLength;
  u32 RxLengthRemainder;
  u32 RxThresholdLevel;
  u32 TxLength;
  u32 TxThresholdLevel;
  u32 SlaveSelectEnable;
  //
  u16 ClockDivider;
  u16 DataFrameNumber;
  //
  u8 ControlFrameSize;
  u8 DataFrameFormat;
  u8 DataFrameSize;
  u8 DmaControl;
  u8 Index;
  u8 InterruptMask;
  u8 MicrowireDirection;
  u8 MicrowireHandshaking;
  u8 MicrowireTransferMode;
  u8 PinmuxSelect;
  u8 Role;
  u8 SclkPhase;
  u8 SclkPolarity;
  u8 SlaveOutputEnable;
  u8 TransferMode;
  u8 TransferMechanism;

  // Extend
  u8 Reserve;
  u8 HaveTxChannel;
  u8 HaveRxChannel;
  u8 DefaultRxThresholdLevel;
#ifdef CONFIG_GDMA_EN
  SSI_DMA_MULTIBLK DmaTxMultiBlk, DmaRxMultiBlk;
#endif
  u32 ReservedDummy;
  VOID (*TxIdleCallback)( VOID *Para );
  VOID *TxIdleCbPara;
} HAL_SSI_ADAPTOR, *PHAL_SSI_ADAPTOR;

typedef struct _HAL_SSI_OP_
{
  HAL_STATUS (*HalSsiPinmuxEnable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiPinmuxDisable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiEnable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiDisable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiInit)( VOID *Adaptor );
  HAL_STATUS (*HalSsiSetSclkPolarity)( VOID *Adaptor );
  HAL_STATUS (*HalSsiSetSclkPhase)( VOID *Adaptor );
  HAL_STATUS (*HalSsiWrite)( VOID *Adaptor, u32 value );
  HAL_STATUS (*HalSsiLoadSetting)( VOID *Adaptor, VOID *Setting );
  HAL_STATUS (*HalSsiSetInterruptMask)( VOID *Adaptor );
  HAL_STATUS (*HalSsiSetDeviceRole)( VOID *Adaptor, u32 Role );
  HAL_STATUS (*HalSsiInterruptEnable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiInterruptDisable)( VOID *Adaptor );
  HAL_STATUS (*HalSsiReadInterrupt)( VOID *Adaptor, VOID *RxData, u32 Length );
  HAL_STATUS (*HalSsiSetRxFifoThresholdLevel)( VOID *Adaptor );
  HAL_STATUS (*HalSsiSetTxFifoThresholdLevel)( VOID *Adaptor );
  HAL_STATUS (*HalSsiWriteInterrupt)( VOID *Adaptor, u8 *TxData, u32 Length );
  HAL_STATUS (*HalSsiSetSlaveEnableRegister)( VOID *Adaptor, u32 SlaveIndex );
  u32 (*HalSsiBusy)( VOID *Adaptor );
  u32 (*HalSsiReadable)( VOID *Adaptor );
  u32 (*HalSsiWriteable)( VOID *Adaptor );
  u32 (*HalSsiGetInterruptMask)( VOID *Adaptor );
  u32 (*HalSsiGetRxFifoLevel)( VOID *Adaptor );
  u32 (*HalSsiGetTxFifoLevel)( VOID *Adaptor );
  u32 (*HalSsiGetStatus)( VOID *Adaptor );
  u32 (*HalSsiGetInterruptStatus)( VOID *Adaptor );
  u32 (*HalSsiRead)( VOID *Adaptor );
  u32 (*HalSsiGetRawInterruptStatus)( VOID *Adaptor );
  u32 (*HalSsiGetSlaveEnableRegister)( VOID *Adaptor );
} HAL_SSI_OP, *PHAL_SSI_OP;

typedef struct _DW_SSI_DEFAULT_SETTING_
{
  VOID (*RxCompCallback)( VOID *Para );
  VOID *RxCompCbPara;
  VOID *RxData;
  VOID (*TxCompCallback)( VOID *Para );
  VOID *TxCompCbPara;
  VOID *TxData;
  u32 DmaRxDataLevel;
  u32 DmaTxDataLevel;
  u32 InterruptPriority;
  u32 RxLength;
  u32 RxLengthRemainder;
  u32 RxThresholdLevel;
  u32 TxLength;
  u32 TxThresholdLevel;
  u32 SlaveSelectEnable;
  //
  u16 ClockDivider;
  u16 DataFrameNumber;
  //
  u8 ControlFrameSize;
  u8 DataFrameFormat;
  u8 DataFrameSize;
  u8 DmaControl;
  //u8   Index;
  u8 InterruptMask;
  u8 MicrowireDirection;
  u8 MicrowireHandshaking;
  u8 MicrowireTransferMode;
  //u8   PinmuxSelect;
  //u8   Role;
  u8 SclkPhase;
  u8 SclkPolarity;
  u8 SlaveOutputEnable;
  u8 TransferMode;
  u8 TransferMechanism;
} DW_SSI_DEFAULT_SETTING, *PDW_SSI_DEFAULT_SETTING;

struct spi_s
{
  HAL_SSI_ADAPTOR spi_adp;
  HAL_SSI_OP spi_op;
  u32 irq_handler;
  u32 irq_id;
  u32 dma_en;
  u32 state;
  u8 sclk;
#ifdef CONFIG_GDMA_EN
  HAL_GDMA_ADAPTER spi_gdma_adp_tx;
  HAL_GDMA_ADAPTER spi_gdma_adp_rx;
#endif
  u32 bus_tx_done_handler;
  u32 bus_tx_done_irq_id;
};

VOID HalSsiOpInit( VOID *Adaptor );
static __inline__ VOID HalSsiSetSclk(
    IN PHAL_SSI_ADAPTOR pHalSsiAdapter,
    IN u32 ClkRate)
{
  HalSsiSetSclkRtl8195a((VOID*)pHalSsiAdapter, ClkRate);
}

HAL_STATUS HalSsiInit( VOID * Data );
HAL_STATUS HalSsiDeInit( VOID * Data );
HAL_STATUS HalSsiEnable( VOID * Data );
HAL_STATUS HalSsiDisable( VOID * Data );
HAL_STATUS HalSsiEnterCritical( VOID * Data );
HAL_STATUS HalSsiExitCritical( VOID * Data );
HAL_STATUS HalSsiTimeout( u32 StartCount, u32 TimeoutCnt );
HAL_STATUS HalSsiStopRecv( VOID * Data );
HAL_STATUS HalSsiSetFormat( VOID * Data );
#ifdef CONFIG_GDMA_EN
HAL_STATUS HalSsiTxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
VOID HalSsiTxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_STATUS HalSsiRxGdmaInit(PHAL_SSI_OP pHalSsiOp, PHAL_SSI_ADAPTOR pHalSsiAdapter);
VOID HalSsiRxGdmaDeInit(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_STATUS HalSsiRxMultiBlkChnl(PHAL_SSI_ADAPTOR pHalSsiAdapter);
HAL_STATUS HalSsiDmaRecv(VOID * Adapter, u8 * pRxData, u32 Length);
HAL_STATUS HalSsiDmaSend(VOID *Adapter, u8 *pTxData, u32 Length);

static __inline__ VOID
HalSsiDmaInit(
    IN PHAL_SSI_ADAPTOR pHalSsiAdapter
)
{
#if CONFIG_CHIP_E_CUT
  HalSsiDmaInitRtl8195a_V04((void *)pHalSsiAdapter);
#else
  HalSsiDmaInitRtl8195a((void *)pHalSsiAdapter);
#endif
}
/*
 static __inline__ HAL_STATUS HalSsiDmaSend(VOID *Adapter, u8 *pTxData, u32 Length)
 {
 return (HalSsiDmaSendRtl8195a(Adapter, pTxData, Length));
 }

 static __inline__ HAL_STATUS HalSsiDmaRecv(VOID *Adapter, u8  *pRxData, u32 Length)
 {
 return (HalSsiDmaRecvRtl8195a(Adapter, pRxData, Length));
 }
 */

#endif  // end of "#ifdef CONFIG_GDMA_EN"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_SPI_H__ */