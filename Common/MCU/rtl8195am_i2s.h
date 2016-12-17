#ifndef __RTL8195AM_I2S_H__
#define __RTL8195AM_I2S_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

//=============== Register Bit Field Definition ====================
// REG_I2S_CONTROL
#define BIT_CTLX_I2S_EN                         BIT(0)
#define BIT_SHIFT_CTLX_I2S_EN                   0
#define BIT_MASK_CTLX_I2S_EN                    0x1
#define BIT_CTRL_CTLX_I2S_EN(x)                 (((x) & BIT_MASK_CTLX_I2S_EN) << BIT_SHIFT_CTLX_I2S_EN)

#define BIT_SHIFT_CTLX_I2S_TRX_ACT              1
#define BIT_MASK_CTLX_I2S_TRX_ACT               0x3
#define BIT_CTRL_CTLX_I2S_TRX_ACT(x)            (((x) & BIT_MASK_CTLX_I2S_TRX_ACT) << BIT_SHIFT_CTLX_I2S_TRX_ACT)
#define BIT_GET_CTLX_I2S_TRX_ACT(x)             (((x) >> BIT_SHIFT_CTLX_I2S_TRX_ACT) & BIT_MASK_CTLX_I2S_TRX_ACT)

#define BIT_SHIFT_CTLX_I2S_CH_NUM               3
#define BIT_MASK_CTLX_I2S_CH_NUM                0x3
#define BIT_CTRL_CTLX_I2S_CH_NUM(x)             (((x) & BIT_MASK_CTLX_I2S_CH_NUM) << BIT_SHIFT_CTLX_I2S_CH_NUM)
#define BIT_GET_CTLX_I2S_CH_NUM(x)              (((x) >> BIT_SHIFT_CTLX_I2S_CH_NUM) & BIT_MASK_CTLX_I2S_CH_NUM)

#define BIT_CTLX_I2S_WL                         BIT(6)
#define BIT_SHIFT_CTLX_I2S_WL                   6
#define BIT_MASK_CTLX_I2S_WL                    0x1
#define BIT_CTRL_CTLX_I2S_WL(x)                 (((x) & BIT_MASK_CTLX_I2S_WL) << BIT_SHIFT_CTLX_I2S_WL)

#define BIT_CTLX_I2S_LRSWAP                     BIT(10)
#define BIT_SHIFT_CTLX_I2S_LRSWAP               10
#define BIT_MASK_CTLX_I2S_LRSWAP                0x1
#define BIT_CTRL_CTLX_I2S_LRSWAP(x)             (((x) & BIT_MASK_CTLX_I2S_LRSWAP) << BIT_SHIFT_CTLX_I2S_LRSWAP)

#define BIT_CTLX_I2S_SCK_INV                    BIT(11)
#define BIT_SHIFT_CTLX_I2S_SCK_INV              11
#define BIT_MASK_CTLX_I2S_SCK_INV               0x1
#define BIT_CTRL_CTLX_I2S_SCK_INV(x)            (((x) & BIT_MASK_CTLX_I2S_SCK_INV) << BIT_SHIFT_CTLX_I2S_SCK_INV)

#define BIT_CTLX_I2S_ENDIAN_SWAP                BIT(12)
#define BIT_SHIFT_CTLX_I2S_ENDIAN_SWAP          12
#define BIT_MASK_CTLX_I2S_ENDIAN_SWAP           0x1
#define BIT_CTRL_CTLX_I2S_ENDIAN_SWAP(x)        (((x) & BIT_MASK_CTLX_I2S_ENDIAN_SWAP) << BIT_SHIFT_CTLX_I2S_ENDIAN_SWAP)

#define BIT_CTLX_I2S_SLAVE_MODE                 BIT(29)
#define BIT_SHIFT_CTLX_I2S_SLAVE_MODE           29
#define BIT_MASK_CTLX_I2S_SLAVE_MODE            0x1
#define BIT_CTRL_CTLX_I2S_SLAVE_MODE(x)         (((x) & BIT_MASK_CTLX_I2S_SLAVE_MODE) << BIT_SHIFT_CTLX_I2S_SLAVE_MODE)

#define BIT_CTLX_I2S_CLK_SRC                    BIT(30)
#define BIT_SHIFT_CTLX_I2S_CLK_SRC              30
#define BIT_MASK_CTLX_I2S_CLK_SRC               0x1
#define BIT_CTRL_CTLX_I2S_CLK_SRC(x)            (((x) & BIT_MASK_CTLX_I2S_CLK_SRC) << BIT_SHIFT_CTLX_I2S_CLK_SRC)

#define BIT_CTLX_I2S_SW_RSTN                    BIT(31)
#define BIT_SHIFT_CTLX_I2S_SW_RSTN              31
#define BIT_MASK_CTLX_I2S_SW_RSTN               0x1
#define BIT_CTRL_CTLX_I2S_SW_RSTN(x)            (((x) & BIT_MASK_CTLX_I2S_SW_RSTN) << BIT_SHIFT_CTLX_I2S_SW_RSTN)

// REG_I2S_SETTING
#define BIT_SHIFT_SETTING_I2S_PAGE_SZ           0
#define BIT_MASK_SETTING_I2S_PAGE_SZ            0xFFF
#define BIT_CTRL_SETTING_I2S_PAGE_SZ(x)         (((x) & BIT_MASK_SETTING_I2S_PAGE_SZ) << BIT_SHIFT_SETTING_I2S_PAGE_SZ)
#define BIT_GET_SETTING_I2S_PAGE_SZ(x)          (((x) >> BIT_SHIFT_SETTING_I2S_PAGE_SZ) & BIT_MASK_SETTING_I2S_PAGE_SZ)

#define BIT_SHIFT_SETTING_I2S_PAGE_NUM          12
#define BIT_MASK_SETTING_I2S_PAGE_NUM           0x3
#define BIT_CTRL_SETTING_I2S_PAGE_NUM(x)        (((x) & BIT_MASK_SETTING_I2S_PAGE_NUM) << BIT_SHIFT_SETTING_I2S_PAGE_NUM)
#define BIT_GET_SETTING_I2S_PAGE_NUM(x)         (((x) >> BIT_SHIFT_SETTING_I2S_PAGE_NUM) & BIT_MASK_SETTING_I2S_PAGE_NUM)

#define BIT_SHIFT_SETTING_I2S_SAMPLE_RATE       14
#define BIT_MASK_SETTING_I2S_SAMPLE_RATE        0x7
#define BIT_CTRL_SETTING_I2S_SAMPLE_RATE(x)     (((x) & BIT_MASK_SETTING_I2S_SAMPLE_RATE) << BIT_SHIFT_SETTING_I2S_SAMPLE_RATE)
#define BIT_GET_SETTING_I2S_SAMPLE_RATE(x)      (((x) >> BIT_SHIFT_SETTING_I2S_SAMPLE_RATE) & BIT_MASK_SETTING_I2S_SAMPLE_RATE)

// i2s trx page own bit
#define BIT_PAGE_I2S_OWN_BIT                    BIT(31)
#define BIT_SHIFT_PAGE_I2S_OWN_BIT              31
#define BIT_MASK_PAGE_I2S_OWN_BIT               0x1
#define BIT_CTRL_PAGE_I2S_OWN_BIT(x)            (((x) & BIT_MASK_PAGE_I2S_OWN_BIT) << BIT_SHIFT_PAGE_I2S_OWN_BIT)

//=============== Register Address Definition ====================
#define REG_I2S_PAGE_OWN_OFF   0x004

#define REG_I2S_CTL            0x000
#define REG_I2S_TX_PAGE_PTR    0x004
#define REG_I2S_RX_PAGE_PTR    0x008
#define REG_I2S_SETTING        0x00C

#define REG_I2S_TX_MASK_INT    0x010
#define REG_I2S_TX_STATUS_INT  0x014
#define REG_I2S_RX_MASK_INT    0x018
#define REG_I2S_RX_STATUS_INT  0x01c

#define REG_I2S_TX_PAGE0_OWN   0x020
#define REG_I2S_TX_PAGE1_OWN   0x024
#define REG_I2S_TX_PAGE2_OWN   0x028
#define REG_I2S_TX_PAGE3_OWN   0x02C
#define REG_I2S_RX_PAGE0_OWN   0x030
#define REG_I2S_RX_PAGE1_OWN   0x034
#define REG_I2S_RX_PAGE2_OWN   0x038
#define REG_I2S_RX_PAGE3_OWN   0x03C

/*I2S Essential Functions and Macros*/
VOID
HalI2SWrite32(
    IN u8 I2SIdx,
    IN u8 I2SReg,
    IN u32 I2SVal
);

u32
HalI2SRead32(
    IN u8 I2SIdx,
    IN u8 I2SReg
);

/*
 #define HAL_I2SX_READ32(I2sIndex, addr)     \
                HAL_READ32(I2S0_REG_BASE+ (I2sIndex*I2S1_REG_OFF), addr)
 #define HAL_I2SX_WRITE32(I2sIndex, addr, value)     \
                HAL_WRITE32((I2S0_REG_BASE+ (I2sIndex*I2S1_REG_OFF)), addr, value)
 */

#define HAL_I2S_WRITE32(I2SIdx, addr, value)    HalI2SWrite32(I2SIdx,addr,value)
#define HAL_I2S_READ32(I2SIdx, addr)            HalI2SRead32(I2SIdx,addr)

/* I2S debug output*/
#define I2S_PREFIX      "RTL8195A[i2s]: "
#define I2S_PREFIX_LVL  "    [i2s_DBG]: "

typedef enum _I2S_DBG_LVL_
{
  HAL_I2S_LVL = 0x01,
  SAL_I2S_LVL = 0x02,
  VERI_I2S_LVL = 0x03,
} I2S_DBG_LVL, *PI2S_DBG_LVL;

#ifdef CONFIG_DEBUG_LOG
#ifdef CONFIG_DEBUG_LOG_I2S_HAL

#define DBG_8195A_I2S(...)  do{ \
        _DbgDump("\r"I2S_PREFIX __VA_ARGS__);\
    }while(0)

#define I2SDBGLVL   0xFF
#define DBG_8195A_I2S_LVL(LVL,...)  do{\
            if (LVL&I2SDBGLVL){\
                _DbgDump("\r"I2S_PREFIX_LVL __VA_ARGS__);\
            }\
    }while(0)
#else
#define DBG_I2S_LOG_PERD    100
#define DBG_8195A_I2S(...)
#define DBG_8195A_I2S_LVL(...)
#endif
#else
#define DBG_I2S_LOG_PERD    100
#define DBG_8195A_I2S(...)
#define DBG_8195A_I2S_LVL(...)
#endif

/*
 #define REG_I2S_PAGE_OWN_OFF   0x004
 #define REG_I2S_CTL            0x000
 #define REG_I2S_TX_PAGE_PTR    0x004
 #define REG_I2S_RX_PAGE_PTR    0x008
 #define REG_I2S_SETTING        0x00C

 #define REG_I2S_TX_MASK_INT    0x010
 #define REG_I2S_TX_STATUS_INT  0x014
 #define REG_I2S_RX_MASK_INT    0x018
 #define REG_I2S_RX_STATUS_INT  0x01c



 #define REG_I2S_TX_PAGE0_OWN   0x020
 #define REG_I2S_TX_PAGE1_OWN   0x024
 #define REG_I2S_TX_PAGE2_OWN   0x028
 #define REG_I2S_TX_PAGE3_OWN   0x02C
 #define REG_I2S_RX_PAGE0_OWN   0x030
 #define REG_I2S_RX_PAGE1_OWN   0x034
 #define REG_I2S_RX_PAGE2_OWN   0x038
 #define REG_I2S_RX_PAGE3_OWN   0x03C
 */
/* template
 #define BIT_SHIFT_CTLX_ 7
 #define BIT_MASK_CTLX_  0x1
 #define BIT_CTLX_(x) (((x) & BIT_MASK_CTLX_) << BIT_SHIFT_CTLX_)
 #define BIT_INV_CTLX_ (~(BIT_MASK_CTLX_ << BIT_SHIFT_CTLX_))
 *//*
 #define BIT_SHIFT_CTLX_IIS_EN 0
 #define BIT_MASK_CTLX_IIS_EN  0x1
 #define BIT_CTLX_IIS_EN(x) (((x) & BIT_MASK_CTLX_IIS_EN) << BIT_SHIFT_CTLX_IIS_EN)
 #define BIT_INV_CTLX_IIS_EN (~(BIT_MASK_CTLX_IIS_EN << BIT_SHIFT_CTLX_IIS_EN))

 #define BIT_SHIFT_CTLX_TRX 1
 #define BIT_MASK_CTLX_TRX 0x3
 #define BIT_CTLX_TRX(x) (((x) & BIT_MASK_CTLX_TRX) << BIT_SHIFT_CTLX_TRX)
 #define BIT_INV_CTLX_TRX (~(BIT_MASK_CTLX_TRX << BIT_SHIFT_CTLX_TRX))

 #define BIT_SHIFT_CTLX_CH_NUM 3
 #define BIT_MASK_CTLX_CH_NUM  0x3
 #define BIT_CTLX_CH_NUM(x) (((x) & BIT_MASK_CTLX_CH_NUM) << BIT_SHIFT_CTLX_CH_NUM)
 #define BIT_INV_CTLX_CH_NUM (~(BIT_MASK_CTLX_CH_NUM << BIT_SHIFT_CTLX_CH_NUM))

 #define BIT_SHIFT_CTLX_EDGE_SW 5
 #define BIT_MASK_CTLX_EDGE_SW  0x1
 #define BIT_CTLX_EDGE_SW(x) (((x) & BIT_MASK_CTLX_EDGE_SW) << BIT_SHIFT_CTLX_EDGE_SW)
 #define BIT_INV_CTLX_EDGE_SW (~(BIT_MASK_CTLX_EDGE_SW << BIT_SHIFT_CTLX_EDGE_SW))

 #define BIT_SHIFT_CTLX_WL 6
 #define BIT_MASK_CTLX_WL  0x1
 #define BIT_CTLX_WL(x) (((x) & BIT_MASK_CTLX_WL) << BIT_SHIFT_CTLX_WL)
 #define BIT_INV_CTLX_WL (~(BIT_MASK_CTLX_WL << BIT_SHIFT_CTLX_WL))

 #define BIT_SHIFT_CTLX_LOOP_BACK 7
 #define BIT_MASK_CTLX_LOOP_BACK  0x1
 #define BIT_CTLX_LOOP_BACK(x) (((x) & BIT_MASK_CTLX_LOOP_BACK) << BIT_SHIFT_CTLX_LOOP_BACK)
 #define BIT_INV_CTLX_LOOP_BACK (~(BIT_MASK_CTLX_LOOP_BACK << BIT_SHIFT_CTLX_LOOP_BACK))


 #define BIT_SHIFT_CTLX_FORMAT 8
 #define BIT_MASK_CTLX_FORMAT  0x3
 #define BIT_CTLX_FORMAT(x) (((x) & BIT_MASK_CTLX_FORMAT) << BIT_SHIFT_CTLX_FORMAT)
 #define BIT_INV_CTLX_FORMAT (~(BIT_MASK_CTLX_FORMAT << BIT_SHIFT_CTLX_FORMAT))

 #define BIT_SHIFT_CTLX_LRSWAP 10
 #define BIT_MASK_CTLX_LRSWAP  0x1
 #define BIT_CTLX_LRSWAP(x) (((x) & BIT_MASK_CTLX_LRSWAP) << BIT_SHIFT_CTLX_LRSWAP)
 #define BIT_INV_CTLX_LRSWAP (~(BIT_MASK_CTLX_LRSWAP << BIT_SHIFT_CTLX_LRSWAP))

 #define BIT_SHIFT_CTLX_SCK_INV 11
 #define BIT_MASK_CTLX_SCK_INV  0x1
 #define BIT_CTLX_SCK_INV(x) (((x) & BIT_MASK_CTLX_SCK_INV) << BIT_SHIFT_CTLX_SCK_INV)
 #define BIT_INV_CTLX_SCK_INV (~(BIT_MASK_CTLX_SCK_INV << BIT_SHIFT_CTLX_SCK_INV))

 #define BIT_SHIFT_CTLX_ENDIAN_SWAP 12
 #define BIT_MASK_CTLX_ENDIAN_SWAP  0x1
 #define BIT_CTLX_ENDIAN_SWAP(x) (((x) & BIT_MASK_CTLX_ENDIAN_SWAP) << BIT_SHIFT_CTLX_ENDIAN_SWAP)
 #define BIT_INV_CTLX_ENDIAN_SWAP (~(BIT_MASK_CTLX_ENDIAN_SWAP << BIT_SHIFT_CTLX_ENDIAN_SWAP))


 #define BIT_SHIFT_CTLX_DEBUG_SWITCH 15
 #define BIT_MASK_CTLX_DEBUG_SWITCH  0x3
 #define BIT_CTLX_DEBUG_SWITCH(x) (((x) & BIT_MASK_CTLX_DEBUG_SWITCH) << BIT_SHIFT_CTLX_DEBUG_SWITCH)
 #define BIT_INV_CTLX_DEBUG_SWITCH (~(BIT_MASK_CTLX_DEBUG_SWITCH << BIT_SHIFT_CTLX_DEBUG_SWITCH))

 #define BIT_SHIFT_CTLX_SLAVE_SEL 29
 #define BIT_MASK_CTLX_SLAVE_SEL  0x1
 #define BIT_CTLX_SLAVE_SEL(x) (((x) & BIT_MASK_CTLX_SLAVE_SEL) << BIT_SHIFT_CTLX_SLAVE_SEL)
 #define BIT_INV_CTLX_SLAVE_SEL (~(BIT_MASK_CTLX_SLAVE_SEL << BIT_SHIFT_CTLX_SLAVE_SEL))


 #define BIT_SHIFT_CTLX_CLK_SRC 30
 #define BIT_MASK_CTLX_CLK_SRC  0x1
 #define BIT_CTLX_CLK_SRC(x) (((x) & BIT_MASK_CTLX_CLK_SRC) << BIT_SHIFT_CTLX_CLK_SRC)
 #define BIT_INV_CTLX_CLK_SRC (~(BIT_MASK_CTLX_CLK_SRC << BIT_SHIFT_CTLX_CLK_SRC))



 #define BIT_SHIFT_CTLX_SW_RSTN 31
 #define BIT_MASK_CTLX_SW_RSTN  0x1
 #define BIT_CTLX_SW_RSTN(x) (((x) & BIT_MASK_CTLX_SW_RSTN) << BIT_SHIFT_CTLX_SW_RSTN)
 #define BIT_INV_CTLX_SW_RSTN (~(BIT_MASK_CTLX_SW_RSTN << BIT_SHIFT_CTLX_SW_RSTN))


 #define BIT_SHIFT_SETTING_PAGE_SZ 0
 #define BIT_MASK_SETTING_PAGE_SZ  0xFFF
 #define BIT_SETTING_PAGE_SZ(x) (((x) & BIT_MASK_SETTING_PAGE_SZ) << BIT_SHIFT_SETTING_PAGE_SZ)
 #define BIT_INV_SETTING_PAGE_SZ (~(BIT_MASK_SETTING_PAGE_SZ << BIT_SHIFT_SETTING_PAGE_SZ))

 #define BIT_SHIFT_SETTING_PAGE_NUM 12
 #define BIT_MASK_SETTING_PAGE_NUM  0x3
 #define BIT_SETTING_PAGE_NUM(x) (((x) & BIT_MASK_SETTING_PAGE_NUM) << BIT_SHIFT_SETTING_PAGE_NUM)
 #define BIT_INV_SETTING_PAGE_NUM (~(BIT_MASK_SETTING_PAGE_NUM << BIT_SHIFT_SETTING_PAGE_NUM))

 #define BIT_SHIFT_SETTING_SAMPLE_RATE 14
 #define BIT_MASK_SETTING_SAMPLE_RATE  0x7
 #define BIT_SETTING_SAMPLE_RATE(x) (((x) & BIT_MASK_SETTING_SAMPLE_RATE) << BIT_SHIFT_SETTING_SAMPLE_RATE)
 #define BIT_INV_SETTING_SAMPLE_RATE (~(BIT_MASK_SETTING_SAMPLE_RATE << BIT_SHIFT_SETTING_SAMPLE_RATE))
 */

typedef enum _I2S_CTL_FORMAT
{
  FormatI2s = 0x00,
  FormatLeftJustified = 0x01,
  FormatRightJustified = 0x02
} I2S_CTL_FORMAT, *PI2S_CTL_FORMAT;

typedef enum _I2S_CTL_CHNUM
{
  ChannelStereo = 0x00,
  Channel5p1 = 0x01,
  ChannelMono = 0x02
} I2S_CTL_CHNUM, *PI2S_CTL_CHNUM;

typedef enum _I2S_CTL_TRX_ACT
{
  RxOnly = 0x00,
  TxOnly = 0x01,
  TXRX = 0x02
} I2S_CTL_TRX_ACT, *PI2S_CTL_TRX_ACT;
/*
 typedef struct _I2S_CTL_REG_ {
 I2S_CTL_FORMAT         Format;
 I2S_CTL_CHNUM          ChNum;
 I2S_CTL_TRX_ACT        TrxAct;

 u32                    I2s_En         :1; // Bit 0
 u32                    Rsvd1to4       :4; // Bit 1-4 is TrxAct, ChNum
 u32                    EdgeSw         :1; // Bit 5 Edge switch
 u32                    WordLength     :1; // Bit 6
 u32                    LoopBack       :1; // Bit 7
 u32                    Rsvd8to9       :2; // Bit 8-9 is Format
 u32                    DacLrSwap      :1; // Bit 10
 u32                    SckInv         :1; // Bit 11
 u32                    EndianSwap     :1; // Bit 12
 u32                    Rsvd13to14     :2; // Bit 11-14
 u32                    DebugSwitch    :2; // Bit 15-16
 u32                    Rsvd17to28    :12; // Bit 17-28
 u32                    SlaveMode      :1; // Bit 29
 u32                    SR44p1KHz      :1; // Bit 30
 u32                    SwRstn         :1; // Bit 31
 } I2S_CTL_REG, *PI2S_CTL_REG;
 */
typedef enum _I2S_SETTING_PAGE_NUM
{
  I2s1Page = 0x00,
  I2s2Page = 0x01,
  I2s3Page = 0x02,
  I2s4Page = 0x03
} I2S_SETTING_PAGE_NUM, *PI2S_SETTING_PAGE_NUM;

//sampling rate
typedef enum _I2S_SETTING_SR
{
  I2sSR8K = 0x00,
  I2sSR16K = 0x01,
  I2sSR24K = 0x02,
  I2sSR32K = 0x03,
  I2sSR48K = 0x05,
  I2sSR44p1K = 0x15,
  I2sSR96K = 0x06,
  I2sSR88p2K = 0x16
} I2S_SETTING_SR, *PI2S_SETTING_SR;
/*
 typedef struct _I2S_SETTING_REG_ {
 I2S_SETTING_PAGE_NUM     PageNum;
 I2S_SETTING_SR           SampleRate;

 u32                      PageSize:12; // Bit 0-11
 }I2S_SETTING_REG, *PI2S_SETTING_REG;

 typedef enum _I2S_TX_ISR {
 I2sTxP0OK          = 0x01,
 I2sTxP1OK          = 0x02,
 I2sTxP2OK          = 0x04,
 I2sTxP3OK          = 0x08,
 I2sTxPageUn        = 0x10,
 I2sTxFifoEmpty     = 0x20
 }I2S_TX_ISR, *PI2S_TX_ISR;

 typedef enum _I2S_RX_ISR {
 I2sRxP0OK          = 0x01,
 I2sRxP1OK          = 0x02,
 I2sRxP2OK          = 0x04,
 I2sRxP3OK          = 0x08,
 I2sRxPageUn        = 0x10,
 I2sRxFifoFull      = 0x20
 }I2S_RX_ISR, *PI2S_RX_ISR;
 */

/* Hal I2S function prototype*/
RTK_STATUS
HalI2SInitRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SInitRtl8195a_Patch(
    IN VOID *Data
);

RTK_STATUS
HalI2SDeInitRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2STxRtl8195a(
    IN VOID *Data,
    IN u8 *pBuff
);

RTK_STATUS
HalI2SRxRtl8195a(
    IN VOID *Data,
    OUT u8 *pBuff
);

RTK_STATUS
HalI2SEnableRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SIntrCtrlRtl8195a(
    IN VOID *Data
);

u32
HalI2SReadRegRtl8195a(
    IN VOID *Data,
    IN u8 I2SReg
);

RTK_STATUS
HalI2SSetRateRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetWordLenRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetChNumRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetPageNumRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetPageSizeRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetDirectionRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SSetDMABufRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SClrIntrRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SClrAllIntrRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SDMACtrlRtl8195a(
    IN VOID *Data
);

u8
HalI2SGetTxPageRtl8195a(
    IN VOID *Data
);

u8
HalI2SGetRxPageRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SPageSendRtl8195a(
    IN VOID *Data,
    IN u8 PageIdx
);

RTK_STATUS
HalI2SPageRecvRtl8195a(
    IN VOID *Data
);

RTK_STATUS
HalI2SClearAllOwnBitRtl8195a(
    IN VOID *Data
);

#ifdef CONFIG_CHIP_E_CUT
_LONG_CALL_ RTK_STATUS
HalI2SInitRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetRateRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetWordLenRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetChNumRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetPageNumRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetPageSizeRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetDirectionRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SSetDMABufRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ u8
HalI2SGetTxPageRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ u8
HalI2SGetRxPageRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SPageSendRtl8195a_V04(
    IN VOID *Data,
    IN u8 PageIdx
);

_LONG_CALL_ RTK_STATUS
HalI2SPageRecvRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ RTK_STATUS
HalI2SClearAllOwnBitRtl8195a_V04(
    IN VOID *Data
);

#endif  // #ifdef CONFIG_CHIP_E_CUT

// HAL functions Wrapper
static __inline VOID
HalI2SSetRate(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetRateRtl8195a(Data);
#else
  HalI2SSetRateRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetWordLen(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetWordLenRtl8195a(Data);
#else
  HalI2SSetWordLenRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetChNum(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetChNumRtl8195a(Data);
#else
  HalI2SSetChNumRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetPageNum(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetPageNumRtl8195a(Data);
#else
  HalI2SSetPageNumRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetPageSize(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetPageSizeRtl8195a(Data);
#else
  HalI2SSetPageSizeRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetDirection(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetDirectionRtl8195a(Data);
#else
  HalI2SSetDirectionRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SSetDMABuf(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SSetDMABufRtl8195a(Data);
#else
  HalI2SSetDMABufRtl8195a_V04(Data);
#endif
}

static __inline u8
HalI2SGetTxPage(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  return HalI2SGetTxPageRtl8195a(Data);
#else
  return HalI2SGetTxPageRtl8195a_V04(Data);
#endif
}

static __inline u8
HalI2SGetRxPage(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  return HalI2SGetRxPageRtl8195a(Data);
#else
  return HalI2SGetRxPageRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SPageSend(
    IN VOID *Data,
    IN u8 PageIdx
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SPageSendRtl8195a(Data, PageIdx);
#else
  HalI2SPageSendRtl8195a_V04(Data, PageIdx);
#endif
}

static __inline VOID
HalI2SPageRecv(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SPageRecvRtl8195a(Data);
#else
  HalI2SPageRecvRtl8195a_V04(Data);
#endif
}

static __inline VOID
HalI2SClearAllOwnBit(
    IN VOID *Data
)
{
#ifndef CONFIG_CHIP_E_CUT
  HalI2SClearAllOwnBitRtl8195a(Data);
#else
  HalI2SClearAllOwnBitRtl8195a_V04(Data);
#endif
}

/* User Define Flags */

#define I2S_MAX_ID                  1   // valid I2S index 0 ~ I2S_MAX_ID

/**********************************************************************/
/* I2S HAL initial data structure */
typedef struct _HAL_I2S_INIT_DAT_
{
  u8 I2SIdx; /*I2S index used*/
  u8 I2SEn; /*I2S module enable tx/rx/tx+rx*/
  u8 I2SMaster; /*I2S Master or Slave mode*/
  u8 I2SWordLen; /*I2S Word length 16 or 24bits*/

  u8 I2SChNum; /*I2S Channel number mono or stereo*/
  u8 I2SPageNum; /*I2S Page Number 2~4*/
  u16 I2SPageSize; /*I2S page Size 1~4096 word*/

  u8 *I2STxData; /*I2S Tx data pointer*/

  u8 *I2SRxData; /*I2S Rx data pointer*/

  u32 I2STxIntrMSK; /*I2S Tx Interrupt Mask*/
  u32 I2STxIntrClr; /*I2S Tx Interrupt register to clear */

  u32 I2SRxIntrMSK; /*I2S Rx Interrupt Mask*/
  u32 I2SRxIntrClr; /*I2S Rx Interrupt register to clear*/

  u16 I2STxIdx; /*I2S TX page index */
  u16 I2SRxIdx; /*I2S RX page index */

  u16 I2SHWTxIdx; /*I2S HW TX page index */
  u16 I2SHWRxIdx; /*I2S HW RX page index */

  u16 I2SRate; /*I2S sample rate*/
  u8 I2STRxAct; /*I2S tx rx act*/
} HAL_I2S_INIT_DAT, *PHAL_I2S_INIT_DAT;

/**********************************************************************/
/* I2S Data Structures */
/* I2S Module Selection */
typedef enum _I2S_MODULE_SEL_
{
  I2S0_SEL = 0x0,
  I2S1_SEL = 0x1,
} I2S_MODULE_SEL, *PI2S_MODULE_SEL;
/*
 typedef struct _HAL_I2S_ADAPTER_ {
 u32                       Enable:1;
 I2S_CTL_REG               I2sCtl;
 I2S_SETTING_REG           I2sSetting;
 u32                       abc;
 u8                        I2sIndex;
 }HAL_I2S_ADAPTER, *PHAL_I2S_ADAPTER;
 */
/* I2S HAL Operations */
typedef struct _HAL_I2S_OP_
{
  RTK_STATUS (*HalI2SInit)( VOID *Data );
  RTK_STATUS (*HalI2SDeInit)( VOID *Data );
  RTK_STATUS (*HalI2STx)( VOID *Data, u8 *pBuff );
  RTK_STATUS (*HalI2SRx)( VOID *Data, u8 *pBuff );
  RTK_STATUS (*HalI2SEnable)( VOID *Data );
  RTK_STATUS (*HalI2SIntrCtrl)( VOID *Data );
  u32 (*HalI2SReadReg)( VOID *Data, u8 I2SReg );
  RTK_STATUS (*HalI2SSetRate)( VOID *Data );
  RTK_STATUS (*HalI2SSetWordLen)( VOID *Data );
  RTK_STATUS (*HalI2SSetChNum)( VOID *Data );
  RTK_STATUS (*HalI2SSetPageNum)( VOID *Data );
  RTK_STATUS (*HalI2SSetPageSize)( VOID *Data );

  RTK_STATUS (*HalI2SClrIntr)( VOID *Data );
  RTK_STATUS (*HalI2SClrAllIntr)( VOID *Data );
  RTK_STATUS (*HalI2SDMACtrl)( VOID *Data );
/*
 VOID (*HalI2sOnOff)(VOID *Data);
 BOOL (*HalI2sInit)(VOID *Data);
 BOOL (*HalI2sSetting)(VOID *Data);
 BOOL (*HalI2sEn)(VOID *Data);
 BOOL (*HalI2sIsrEnAndDis) (VOID *Data);
 BOOL (*HalI2sDumpReg)(VOID *Data);
 BOOL (*HalI2s)(VOID *Data);
 */
} HAL_I2S_OP, *PHAL_I2S_OP;

/**********************************************************************/

/* I2S Pinmux Selection */
#if 0
typedef enum _I2S0_PINMUX_
{
  I2S0_TO_S0 = 0x0,
  I2S0_TO_S1 = 0x1,
  I2S0_TO_S2 = 0x2,
}I2S0_PINMUX, *PI2S0_PINMUX;

typedef enum _I2S1_PINMUX_
{
  I2S1_TO_S0 = 0x0,
  I2S1_TO_S1 = 0x1,
}I2S1_PINMUX, *PI2S1_PINMUX;
#endif

typedef enum _I2S_PINMUX_
{
  I2S_S0 = 0,
  I2S_S1 = 1,
  I2S_S2 = 2,
  I2S_S3 = 3
} I2S_PINMUX, *PI2S_PINMUX;

/* I2S Module Status */
typedef enum _I2S_MODULE_STATUS_
{
  I2S_DISABLE = 0x0,
  I2S_ENABLE = 0x1,
} I2S_MODULE_STATUS, *PI2S_MODULE_STATUS;

/* I2S Device Status */
typedef enum _I2S_Device_STATUS_
{
  I2S_STS_UNINITIAL = 0x00,
  I2S_STS_INITIALIZED = 0x01,
  I2S_STS_IDLE = 0x02,

  I2S_STS_TX_READY = 0x03,
  I2S_STS_TX_ING = 0x04,

  I2S_STS_RX_READY = 0x05,
  I2S_STS_RX_ING = 0x06,

  I2S_STS_TRX_READY = 0x07,
  I2S_STS_TRX_ING = 0x08,

  I2S_STS_ERROR = 0x09,
} I2S_Device_STATUS, *PI2S_Device_STATUS;

/* I2S Feature Status */
typedef enum _I2S_FEATURE_STATUS_
{
  I2S_FEATURE_DISABLED = 0,
  I2S_FEATURE_ENABLED = 1,
} I2S_FEATURE_STATUS, *PI2S_FEATURE_STATUS;

/* I2S Device Mode */
typedef enum _I2S_DEV_MODE_
{
  I2S_MASTER_MODE = 0x0,
  I2S_SLAVE_MODE = 0x1
} I2S_DEV_MODE, *PI2S_DEV_MODE;

/* I2S Word Length */
typedef enum _I2S_WORD_LEN_
{
  I2S_WL_16 = 0x0,
  I2S_WL_24 = 0x1,
} I2S_WORD_LEN, *PI2S_WORD_LEN;

/* I2S Bus Transmit/Receive */
typedef enum _I2S_DIRECTION_
{
  I2S_ONLY_RX = 0x0,
  I2S_ONLY_TX = 0x1,
  I2S_TXRX = 0x2
} I2S_DIRECTION, *PI2S_DIRECTION;

/* I2S Channel number */
typedef enum _I2S_CH_NUM_
{
  I2S_CH_STEREO = 0x0,
  I2S_CH_RSVD = 0x1,
  I2S_CH_MONO = 0x2
} I2S_CH_NUM, *PI2S_CH_NUM;

/* I2S Page number */
typedef enum _I2S_PAGE_NUM_
{
  I2S_1PAGE = 0x0,
  I2S_2PAGE = 0x1,
  I2S_3PAGE = 0x2,
  I2S_4PAGE = 0x3
} I2S_PAGE_NUM, *PI2S_PAGE_NUM;

/* I2S Sample rate*/
typedef enum _I2S_SAMPLE_RATE_
{
  I2S_SR_8KHZ = 0x00,	// /12
  I2S_SR_16KHZ = 0x01,	// /6
  I2S_SR_24KHZ = 0x02,	// /4
  I2S_SR_32KHZ = 0x03,	// /3
  I2S_SR_48KHZ = 0x05,	// /2
  I2S_SR_96KHZ = 0x06,	// x1, base 96kHz
  I2S_SR_7p35KHZ = 0x10,
  I2S_SR_11p02KHZ = 0x11,
  I2S_SR_22p05KHZ = 0x12,
  I2S_SR_29p4KHZ = 0x13,
  I2S_SR_44p1KHZ = 0x15,
  I2S_SR_88p2KHZ = 0x16	// x1, base 88200Hz
} I2S_SAMPLE_RATE, *PI2S_SAMPLE_RATE;

/* I2S TX interrupt mask/status */
typedef enum _I2S_TX_IMR_
{
  I2S_TX_INT_PAGE0_OK = ( 1 << 0 ),
  I2S_TX_INT_PAGE1_OK = ( 1 << 1 ),
  I2S_TX_INT_PAGE2_OK = ( 1 << 2 ),
  I2S_TX_INT_PAGE3_OK = ( 1 << 3 ),
  I2S_TX_INT_FULL = ( 1 << 4 ),
  I2S_TX_INT_EMPTY = ( 1 << 5 )
} I2S_TX_IMR, *PI2S_TX_IMR;

/* I2S RX interrupt mask/status */
typedef enum _I2S_RX_IMR_
{
  I2S_RX_INT_PAGE0_OK = ( 1 << 0 ),
  I2S_RX_INT_PAGE1_OK = ( 1 << 1 ),
  I2S_RX_INT_PAGE2_OK = ( 1 << 2 ),
  I2S_RX_INT_PAGE3_OK = ( 1 << 3 ),
  I2S_RX_INT_EMPTY = ( 1 << 4 ),
  I2S_RX_INT_FULL = ( 1 << 5 )
} I2S_RX_IMR, *PI2S_RX_IMR;

/* I2S User Callbacks */
typedef struct _SAL_I2S_USER_CB_
{
  VOID (*TXCB)( VOID *Data );
  VOID (*TXCCB)( VOID *Data );
  VOID (*RXCB)( VOID *Data );
  VOID (*RXCCB)( VOID *Data );
  VOID (*RDREQCB)( VOID *Data );
  VOID (*ERRCB)( VOID *Data );
  VOID (*GENCALLCB)( VOID *Data );
} SAL_I2S_USER_CB, *PSAL_I2S_USER_CB;

typedef struct _I2S_USER_CB_
{
  VOID (*TxCCB)( uint32_t id, char *pbuf );
  u32 TxCBId;
  VOID (*RxCCB)( uint32_t id, char *pbuf );
  u32 RxCBId;
} I2S_USER_CB, *PI2S_USER_CB;

/* Software API Level I2S Handler */
typedef struct _HAL_I2S_ADAPTER_
{
  u8 DevNum;             //I2S device number
  u8 PinMux;             //I2S pin mux seletion
  u8 RSVD0;              //Reserved
  volatile u8 DevSts;             //I2S device status

  u32 RSVD2;              //Reserved
  u32 I2SExd;             //I2S extended options:
                          //bit 0: I2C RESTART supported,
                          //          0 for NOT supported,
                          //          1 for supported
                          //bit 1: I2C General Call supported
                          //          0 for NOT supported,
                          //          1 for supported
                          //bit 2: I2C START Byte supported
                          //          0 for NOT supported,
                          //          1 for supported
                          //bit 3: I2C Slave-No-Ack
                          //         supported
                          //          0 for NOT supported,
                          //          1 for supported
                          //bit 4: I2C bus loading,
                          //          0 for 100pf,
                          //          1  for 400pf
                          //bit 5: I2C slave ack to General
                          //         Call
                          //bit 6: I2C User register address
                          //bit 7: I2C 2-Byte User register
                          //         address
                          //bit 31~bit 8: Reserved
  u32 ErrType;         //
  u32 TimeOut;            //I2S IO Timeout count

  PHAL_I2S_INIT_DAT pInitDat;           //Pointer to I2S initial data struct
  I2S_USER_CB UserCB;            //Pointer to I2S User Callback
  IRQ_HANDLE IrqHandle;          // Irq Handler

  u32* TxPageList[ 4 ];       // The Tx DAM buffer: pointer of each page
  u32* RxPageList[ 4 ];       // The Tx DAM buffer: pointer of each page
} HAL_I2S_ADAPTER, *PHAL_I2S_ADAPTER;

typedef struct _HAL_I2S_DEF_SETTING_
{
  u8 I2SMaster;           // Master or Slave mode
  u8 DevSts;             //I2S device status
  u8 I2SChNum;           //I2S Channel number mono or stereo
  u8 I2SPageNum;         //I2S Page number 2~4
  u8 I2STRxAct;          //I2S tx rx act, tx only or rx only or tx+rx
  u8 I2SWordLen;         //I2S Word length 16bit or 24bit
  u16 I2SPageSize;        //I2S Page size 1~4096 word

  u16 I2SRate;            //I2S sample rate 8k ~ 96khz

  u32 I2STxIntrMSK; /*I2S Tx Interrupt Mask*/
  u32 I2SRxIntrMSK; /*I2S Rx Interrupt Mask*/
} HAL_I2S_DEF_SETTING, *PHAL_I2S_DEF_SETTING;

/**********************************************************************/
HAL_STATUS
RtkI2SLoadDefault(IN VOID *Adapter, IN VOID *Setting);

HAL_STATUS
RtkI2SInit(IN VOID *Data);

HAL_STATUS
RtkI2SDeInit(IN VOID *Data);

HAL_STATUS
RtkI2SEnable(IN VOID *Data);

HAL_STATUS
RtkI2SDisable(IN VOID *Data);

extern HAL_STATUS
HalI2SInit( IN VOID *Data);

extern VOID
HalI2SDeInit( IN VOID *Data);

extern HAL_STATUS
HalI2SDisable( IN VOID *Data);

extern HAL_STATUS
HalI2SEnable( IN VOID *Data);

/**********************************************************************/

VOID I2S0ISRHandle( VOID *Data );
VOID I2S1ISRHandle( VOID *Data );

/**********************************************************************/

VOID HalI2SOpInit(
    IN VOID *Data
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_I2S_H__ */
