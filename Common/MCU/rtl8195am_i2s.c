#include "rtl8195am_i2s.h"

extern void *
_memset( void *s, int c, SIZE_T n );

RTK_STATUS
HalI2SInitRtl8195a_Patch(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;

  u8 I2SIdx;
  //u8  I2SEn;
  u8 I2SMaster;
  u8 I2SWordLen;
  u8 I2SChNum;
  u8 I2SPageNum;
  u16 I2SPageSize;
  u16 I2SRate;
  u32 I2STxIntrMSK;
  u32 I2SRxIntrMSK;
  u8 I2STRxAct;
  u8 *I2STxData;
  u8 *I2SRxData;

  u32 Tmp;

  I2SIdx = pHalI2SInitData->I2SIdx;
  //I2SEn          = pHalI2SInitData->I2SEn;
  I2SMaster = pHalI2SInitData->I2SMaster;
  I2SWordLen = pHalI2SInitData->I2SWordLen;
  I2SChNum = pHalI2SInitData->I2SChNum;
  I2SPageNum = pHalI2SInitData->I2SPageNum;
  I2SPageSize = pHalI2SInitData->I2SPageSize;
  I2SRate = pHalI2SInitData->I2SRate;
  I2STRxAct = pHalI2SInitData->I2STRxAct;
  I2STxData = pHalI2SInitData->I2STxData;
  I2SRxData = pHalI2SInitData->I2SRxData;

  /* Disable the I2S first, and reset to default */
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, BIT_CTRL_CTLX_I2S_EN(0) |
      BIT_CTRL_CTLX_I2S_SW_RSTN(1));
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, BIT_CTRL_CTLX_I2S_EN(0) |
      BIT_CTRL_CTLX_I2S_SW_RSTN(0));
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, BIT_CTRL_CTLX_I2S_EN(0) |
      BIT_CTRL_CTLX_I2S_SW_RSTN(1));

  Tmp = HAL_I2S_READ32(I2SIdx, REG_I2S_CTL);
  Tmp |= BIT_CTRL_CTLX_I2S_ENDIAN_SWAP(1);

  if (I2SRate&0x10)
  {
    Tmp |= BIT_CTRL_CTLX_I2S_CLK_SRC(1);
  }

  Tmp |= (BIT_CTRL_CTLX_I2S_WL(I2SWordLen) | BIT_CTRL_CTLX_I2S_CH_NUM(I2SChNum) |
      BIT_CTRL_CTLX_I2S_SLAVE_MODE(I2SMaster) | BIT_CTRL_CTLX_I2S_TRX_ACT(I2STRxAct));
  /* set 44.1khz clock source, word length, channel number, master or slave, trx act */
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, Tmp);

  Tmp = BIT_CTRL_SETTING_I2S_PAGE_SZ(I2SPageSize) | BIT_CTRL_SETTING_I2S_PAGE_NUM(I2SPageNum) |
  BIT_CTRL_SETTING_I2S_SAMPLE_RATE(I2SRate);
  /* set page size, page number, sample rate */
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_SETTING, Tmp);

  /* need tx rx buffer? need rx page own bit */
  if (I2STxData != NULL)
  {
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_TX_PAGE_PTR, (u32)I2STxData);
  }

  if (I2SRxData != NULL)
  {
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_RX_PAGE_PTR, (u32)I2SRxData);
  }

  pHalI2SInitData->I2STxIdx = 0;
  pHalI2SInitData->I2SRxIdx = 0;
  pHalI2SInitData->I2SHWTxIdx = 0;
  pHalI2SInitData->I2SHWRxIdx = 0;
  /* I2S Clear all interrupts first */
  HalI2SClrAllIntrRtl8195a(pHalI2SInitData);

  /* I2S Disable all interrupts first */
  I2STxIntrMSK = pHalI2SInitData->I2STxIntrMSK;
  I2SRxIntrMSK = pHalI2SInitData->I2SRxIntrMSK;
  pHalI2SInitData->I2STxIntrMSK = 0;
  pHalI2SInitData->I2SRxIntrMSK = 0;
  HalI2SIntrCtrlRtl8195a(pHalI2SInitData);
  pHalI2SInitData->I2STxIntrMSK = I2STxIntrMSK;
  pHalI2SInitData->I2SRxIntrMSK = I2SRxIntrMSK;

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetRateRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_CTL);
  reg_value &= ~(BIT_MASK_CTLX_I2S_CLK_SRC << BIT_SHIFT_CTLX_I2S_CLK_SRC);
  if (pHalI2SInitData->I2SRate&0x10)
  {
    reg_value |= BIT_CTRL_CTLX_I2S_CLK_SRC(1);
  }
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, reg_value);

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_SETTING);
  reg_value &= ~(BIT_MASK_SETTING_I2S_SAMPLE_RATE << BIT_SHIFT_SETTING_I2S_SAMPLE_RATE);
  reg_value |= BIT_CTRL_SETTING_I2S_SAMPLE_RATE(pHalI2SInitData->I2SRate);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_SETTING, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetWordLenRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;
  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_CTL);
  reg_value &= ~(BIT_MASK_CTLX_I2S_WL << BIT_SHIFT_CTLX_I2S_WL);
  reg_value |= BIT_CTRL_CTLX_I2S_WL(pHalI2SInitData->I2SWordLen);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetChNumRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;
  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_CTL);
  reg_value &= ~(BIT_MASK_CTLX_I2S_CH_NUM << BIT_SHIFT_CTLX_I2S_CH_NUM);
  reg_value |= BIT_CTRL_CTLX_I2S_CH_NUM(pHalI2SInitData->I2SChNum);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetPageNumRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_SETTING);
  reg_value &= ~(BIT_MASK_SETTING_I2S_PAGE_NUM << BIT_SHIFT_SETTING_I2S_PAGE_NUM);
  reg_value |= BIT_CTRL_SETTING_I2S_PAGE_NUM(pHalI2SInitData->I2SPageNum);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_SETTING, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetPageSizeRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_SETTING);
  reg_value &= ~(BIT_MASK_SETTING_I2S_PAGE_SZ << BIT_SHIFT_SETTING_I2S_PAGE_SZ);
  reg_value |= BIT_CTRL_SETTING_I2S_PAGE_SZ(pHalI2SInitData->I2SPageSize);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_SETTING, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetDirectionRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_CTL);
  reg_value &= ~(BIT_MASK_CTLX_I2S_TRX_ACT << BIT_SHIFT_CTLX_I2S_TRX_ACT);
  reg_value |= BIT_CTRL_CTLX_I2S_TRX_ACT(pHalI2SInitData->I2STRxAct);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_CTL, reg_value);

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SSetDMABufRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 reg_value;
  u32 page_num;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg_value = HAL_I2S_READ32(I2SIdx, REG_I2S_SETTING);
  reg_value &= ~(BIT_MASK_SETTING_I2S_PAGE_SZ << BIT_SHIFT_SETTING_I2S_PAGE_SZ);
  reg_value &= ~(BIT_MASK_SETTING_I2S_PAGE_NUM << BIT_SHIFT_SETTING_I2S_PAGE_NUM);
  reg_value |= BIT_CTRL_SETTING_I2S_PAGE_SZ(pHalI2SInitData->I2SPageSize);
  reg_value |= BIT_CTRL_SETTING_I2S_PAGE_NUM(pHalI2SInitData->I2SPageNum);
  HAL_I2S_WRITE32(I2SIdx, REG_I2S_SETTING, reg_value);

  page_num = pHalI2SInitData->I2SPageNum + 1;
  if (pHalI2SInitData->I2STxData)
  {
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_TX_PAGE_PTR, (uint32_t)pHalI2SInitData->I2STxData);
    pHalI2SInitData->I2STxIntrMSK = (1<<page_num) - 1;
  }
  else
  {
    pHalI2SInitData->I2STxIntrMSK = 0;
  }

  if (pHalI2SInitData->I2SRxData)
  {
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_RX_PAGE_PTR, (uint32_t)pHalI2SInitData->I2SRxData);
    pHalI2SInitData->I2SRxIntrMSK = (1<<page_num) - 1;
  }
  else
  {
    pHalI2SInitData->I2SRxIntrMSK = 0;

  }

  // According to the page number to modify the ISR mask
  HalI2SIntrCtrlRtl8195a(pHalI2SInitData);

  return _EXIT_SUCCESS;
}

u8
HalI2SGetTxPageRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;

  u8 I2SIdx;
  u16 I2STxIdx = pHalI2SInitData->I2STxIdx;
  u32 reg;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg = HAL_I2S_READ32(I2SIdx, REG_I2S_TX_PAGE0_OWN+(I2STxIdx<<2));
  if ((reg & (1<<31)) == 0)
  {
    return I2STxIdx;
  }
  else
  {
    return 0xFF;
  }
}

u8
HalI2SGetRxPageRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;

  u8 I2SIdx;
  u16 I2SRxIdx = pHalI2SInitData->I2SRxIdx;
  u32 reg;

  I2SIdx = pHalI2SInitData->I2SIdx;

  reg = HAL_I2S_READ32(I2SIdx, REG_I2S_RX_PAGE0_OWN+(I2SRxIdx << 2));
  if ((reg & (1<<31)) == 0)
  {
    return I2SRxIdx;
  }
  else
  {
    return 0xFF;
  }
}

RTK_STATUS
HalI2SPageSendRtl8195a(
    IN VOID *Data,
    IN u8 PageIdx
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u16 I2STxIdx = pHalI2SInitData->I2STxIdx;
  u8 I2SPageNum = pHalI2SInitData->I2SPageNum;
  u8 I2SIdx;

  if (I2STxIdx != PageIdx)
  {
    DBG_I2S_ERR("HalI2SPageSendRtl8195a: UnExpected Page Index. TxPage=%d, Expected:%d\r\n",
        PageIdx, I2STxIdx);
  }

  I2SIdx = pHalI2SInitData->I2SIdx;

  HAL_I2S_WRITE32(I2SIdx, REG_I2S_TX_PAGE0_OWN+4*PageIdx, 1<<31);
  I2STxIdx = PageIdx+1;
  if (I2STxIdx > I2SPageNum)
  {
    I2STxIdx = 0;
  }
  pHalI2SInitData->I2STxIdx = I2STxIdx;

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SPageRecvRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u16 I2SRxIdx = pHalI2SInitData->I2SRxIdx;
  u8 I2SPageNum = pHalI2SInitData->I2SPageNum;
  u32 reg;
  u8 I2SIdx;

  I2SIdx = pHalI2SInitData->I2SIdx;
  reg = HAL_I2S_READ32(I2SIdx, REG_I2S_RX_PAGE0_OWN+(I2SRxIdx << 2));
  if ((reg & (1<<31)) != 0)
  {
    DBG_I2S_ERR("HalI2SPageRecvRtl8195a: No Idle Rx Page\r\n");
    return _EXIT_FAILURE;
  }

  HAL_I2S_WRITE32(I2SIdx, REG_I2S_RX_PAGE0_OWN+(I2SRxIdx<<2), 1<<31);
  I2SRxIdx += 1;
  if (I2SRxIdx > I2SPageNum)
  {
    I2SRxIdx = 0;
  }
  pHalI2SInitData->I2SRxIdx = I2SRxIdx;

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SClearAllOwnBitRtl8195a(
    IN VOID *Data
)
{
  PHAL_I2S_INIT_DAT pHalI2SInitData = (PHAL_I2S_INIT_DAT)Data;
  u8 I2SIdx;
  u32 i;

  I2SIdx = pHalI2SInitData->I2SIdx;

  for (i=0;i<4;i++)
  {
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_TX_PAGE0_OWN+(i<<2), 0);
    HAL_I2S_WRITE32(I2SIdx, REG_I2S_RX_PAGE0_OWN+(i<<2), 0);
  }

  return _EXIT_SUCCESS;
}

RTK_STATUS
HalI2SDMACtrlRtl8195a(
    IN VOID *Data
)
{

  return _EXIT_SUCCESS;
}

//1 need to be modified

/*======================================================
 Local used variables
 */
SRAM_BF_DATA_SECTION
HAL_I2S_OP HalI2SOpSAL = {
  0 };

VOID
I2SISRHandle(
    IN VOID *Data
)
{
  PHAL_I2S_ADAPTER pI2SAdp = (PHAL_I2S_ADAPTER) Data;
  PHAL_I2S_OP pHalI2SOP = &HalI2SOpSAL;
  PHAL_I2S_INIT_DAT pI2SCfg = pI2SAdp->pInitDat;
  u32 I2STxIsr, I2SRxIsr;
  u8 I2SPageNum = pI2SCfg->I2SPageNum+1;
//    u32 I2SPageSize = (pI2SAdp->I2SPageSize+1)<<2;
  u32 i;
  u32 pbuf;

  I2STxIsr = pHalI2SOP->HalI2SReadReg(pI2SCfg, REG_I2S_TX_STATUS_INT);
  I2SRxIsr = pHalI2SOP->HalI2SReadReg(pI2SCfg, REG_I2S_RX_STATUS_INT);

  pI2SCfg->I2STxIntrClr = I2STxIsr;
  pI2SCfg->I2SRxIntrClr = I2SRxIsr;
  pHalI2SOP->HalI2SClrIntr(pI2SCfg);

  for (i=0; i<I2SPageNum; i++)
  { // page 0, 1, 2, 3
    if (I2STxIsr & (1<<pI2SCfg->I2SHWTxIdx))
    {
//            pbuf = ((u32)(pI2SCfg->I2STxData)) + (I2SPageSize*pI2SCfg->I2SHWTxIdx);
      pbuf = (u32)pI2SAdp->TxPageList[pI2SCfg->I2SHWTxIdx];
      pI2SAdp->UserCB.TxCCB(pI2SAdp->UserCB.TxCBId, (char*)pbuf);
      I2STxIsr &= ~(1<<pI2SCfg->I2SHWTxIdx);
      pI2SCfg->I2SHWTxIdx += 1;
      if (pI2SCfg->I2SHWTxIdx == I2SPageNum)
      {
        pI2SCfg->I2SHWTxIdx = 0;
      }
    }

    if (I2SRxIsr & (1<<pI2SCfg->I2SHWRxIdx))
    {
//            pbuf = ((u32)(pI2SCfg->I2SRxData)) + (I2SPageSize*pI2SCfg->I2SHWRxIdx);
      pbuf = (u32)pI2SAdp->RxPageList[pI2SCfg->I2SHWRxIdx];
      pI2SAdp->UserCB.RxCCB(pI2SAdp->UserCB.RxCBId, (char*)pbuf);
      I2SRxIsr &= ~(1<<pI2SCfg->I2SHWRxIdx);
      pI2SCfg->I2SHWRxIdx += 1;
      if (pI2SCfg->I2SHWRxIdx == I2SPageNum)
      {
        pI2SCfg->I2SHWRxIdx = 0;
      }
    }
  }
}

static HAL_STATUS
RtkI2SIrqInit(
    IN PHAL_I2S_ADAPTER pI2SAdapter
)
{
  PIRQ_HANDLE pIrqHandle;

  if (pI2SAdapter->DevNum > I2S_MAX_ID)
  {
    DBG_I2S_ERR("RtkI2SIrqInit: Invalid I2S Index(&d)\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  pIrqHandle = &pI2SAdapter->IrqHandle;

  switch (pI2SAdapter->DevNum)
  {
    case I2S0_SEL:
    pIrqHandle->IrqNum = I2S0_PCM0_IRQ;
    break;

    case I2S1_SEL:
    pIrqHandle->IrqNum = I2S1_PCM1_IRQ;
    break;

    default:
    return HAL_ERR_PARA;
  }

  pIrqHandle->Data = (u32) (pI2SAdapter);
  pIrqHandle->IrqFun = (IRQ_FUN) I2SISRHandle;
  pIrqHandle->Priority = 6;
  InterruptRegister(pIrqHandle);
  InterruptEn(pIrqHandle);

  return HAL_OK;
}

static HAL_STATUS
RtkI2SIrqDeInit(
    IN PHAL_I2S_ADAPTER pI2SAdapter
)
{
  if (pI2SAdapter->DevNum > I2S_MAX_ID)
  {
    DBG_I2S_ERR("RtkI2SIrqDeInit: Invalid I2S Index(&d)\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  InterruptDis(&pI2SAdapter->IrqHandle);
  InterruptUnRegister(&pI2SAdapter->IrqHandle);

  return HAL_OK;
}

static HAL_STATUS
RtkI2SPinMuxInit(
    IN PHAL_I2S_ADAPTER pI2SAdapter
)
{
  u32 I2Stemp;

  if (pI2SAdapter->DevNum > I2S_MAX_ID)
  {
    DBG_I2S_ERR("RtkI2SPinMuxInit: Invalid I2S Index(&d)\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  // enable system pll
  I2Stemp = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) | (1<<9) | (1<<10);
  HAL_WRITE32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1, I2Stemp);

  switch (pI2SAdapter->DevNum)
  {
    case I2S0_SEL:
    ACTCK_I2S_CCTRL(ON);
    SLPCK_I2S_CCTRL(ON);
    LXBUS_FCTRL(ON); // enable lx bus for i2s

    /*I2S0 Pin Mux Setting*/
    PinCtrl(I2S0, pI2SAdapter->PinMux, ON);
    if (pI2SAdapter->PinMux == I2S_S0)
    {
      DBG_I2S_WARN(ANSI_COLOR_MAGENTA"I2S0 Pin may conflict with JTAG\r\n"ANSI_COLOR_RESET);
    }
    I2S0_MCK_CTRL(ON);
    I2S0_PIN_CTRL(ON);
    I2S0_FCTRL(ON);

    break;
    case I2S1_SEL:
    ACTCK_I2S_CCTRL(ON);
    SLPCK_I2S_CCTRL(ON);
    LXBUS_FCTRL(ON); // enable lx bus for i2s

    /*I2S1 Pin Mux Setting*/
    PinCtrl(I2S1, pI2SAdapter->PinMux, ON);
    if (pI2SAdapter->PinMux == I2S_S2)
    {
      DBG_I2S_WARN(ANSI_COLOR_MAGENTA"I2S1 Pin may conflict with JTAG\r\n"ANSI_COLOR_RESET);
    }
    I2S1_MCK_CTRL(ON);
    I2S1_PIN_CTRL(ON);
    I2S0_FCTRL(ON); //i2s 1 is control by bit 24 BIT_PERI_I2S0_EN
    I2S1_FCTRL(ON);
    break;
    default:
    return HAL_ERR_PARA;
  }

  return HAL_OK;
}

static HAL_STATUS
RtkI2SPinMuxDeInit(
    IN PHAL_I2S_ADAPTER pI2SAdapter
)
{
  if (pI2SAdapter->DevNum > I2S_MAX_ID)
  {
    DBG_I2S_ERR("RtkI2SPinMuxDeInit: Invalid I2S Index(&d)\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  switch (pI2SAdapter->DevNum)
  {
    case I2S0_SEL:
    /*I2S0 Pin Mux Setting*/
    //ACTCK_I2C0_CCTRL(OFF);
    PinCtrl(I2S0, pI2SAdapter->PinMux, OFF);
    I2S0_MCK_CTRL(OFF);
    I2S0_PIN_CTRL(OFF);
    //I2S0_FCTRL(OFF);

    break;
    case I2S1_SEL:
    /*I2S1 Pin Mux Setting*/
    //ACTCK_I2C1_CCTRL(OFF);
    PinCtrl(I2S1, pI2SAdapter->PinMux, OFF);
    I2S1_MCK_CTRL(OFF);
    I2S1_PIN_CTRL(OFF);
    //I2S1_FCTRL(OFF);
    break;
    default:
    return HAL_ERR_PARA;
  }

  return HAL_OK;
}

HAL_STATUS
RtkI2SInit(
    IN VOID *Data
)
{
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  PHAL_I2S_OP pHalI2SOP = &HalI2SOpSAL;
  PHAL_I2S_INIT_DAT pI2SCfg;

  if (pI2SAdapter == 0)
  {
    DBG_I2S_ERR("RtkI2SInit: Null Pointer\r\n");
    return HAL_ERR_PARA;
  }

  if (pI2SAdapter->DevNum > I2S_MAX_ID)
  {
    DBG_I2S_ERR("RtkI2SInit: Invalid I2S Index(&d)\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  pI2SCfg = pI2SAdapter->pInitDat;

  /*I2S Initialize HAL Operations*/
  HalI2SOpInit(pHalI2SOP);

  /*I2S Interrupt Initialization*/
  RtkI2SIrqInit(pI2SAdapter);

  /*I2S Pin Mux Initialization*/
  RtkI2SPinMuxInit(pI2SAdapter);

  /*I2S Load User Setting*/
  pI2SCfg->I2SIdx = pI2SAdapter->DevNum;

  /*I2S HAL Initialization*/
  pHalI2SOP->HalI2SInit(pI2SCfg);

  /*I2S Device Status Update*/
  pI2SAdapter->DevSts = I2S_STS_INITIALIZED;

  /*I2S Enable Module*/
  pI2SCfg->I2SEn = I2S_ENABLE;
  pHalI2SOP->HalI2SEnable(pI2SCfg);

  /*I2S Device Status Update*/
  pI2SAdapter->DevSts = I2S_STS_IDLE;

  return HAL_OK;
}

HAL_STATUS
RtkI2SDeInit(
    IN VOID *Data
)
{
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  PHAL_I2S_OP pHalI2SOP = &HalI2SOpSAL;
  PHAL_I2S_INIT_DAT pI2SCfg;
  u32 I2Stemp;

  if (pI2SAdapter == 0)
  {
    DBG_I2S_ERR("RtkI2SDeInit: Null Pointer\r\n");
    return HAL_ERR_PARA;
  }

  pI2SCfg = pI2SAdapter->pInitDat;

  /*I2S Disable Module*/
  pI2SCfg->I2SEn = I2S_DISABLE;
  pHalI2SOP->HalI2SEnable(pI2SCfg);
  HalI2SClearAllOwnBit((VOID*)pI2SCfg);

  /*I2C HAL DeInitialization*/
  //pHalI2SOP->HalI2SDeInit(pI2SCfg);
  /*I2S Interrupt DeInitialization*/
  RtkI2SIrqDeInit(pI2SAdapter);

  /*I2S Pin Mux DeInitialization*/
  RtkI2SPinMuxDeInit(pI2SAdapter);

  /*I2S HAL DeInitialization*/
  pHalI2SOP->HalI2SDeInit(pI2SCfg);

  /*I2S CLK Source Close*/
  I2Stemp = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) & (~((1<<9) | (1<<10)));
  HAL_WRITE32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1, I2Stemp);

  /*I2S Device Status Update*/
  pI2SAdapter->DevSts = I2S_STS_UNINITIAL;

  return HAL_OK;
}

HAL_STATUS
RtkI2SEnable(
    IN VOID *Data
)
{
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  PHAL_I2S_OP pHalI2SOP = &HalI2SOpSAL;
  PHAL_I2S_INIT_DAT pI2SCfg;
  u32 I2Stemp;

  // Enable IP Clock
  I2Stemp = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) | (1<<9) | (1<<10);
  HAL_WRITE32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1, I2Stemp);
  ACTCK_I2S_CCTRL(ON);
  SLPCK_I2S_CCTRL(ON);

  pI2SCfg = pI2SAdapter->pInitDat;
  pI2SCfg->I2SEn = I2S_ENABLE;
  pHalI2SOP->HalI2SEnable(pI2SCfg);

  return HAL_OK;
}

HAL_STATUS
RtkI2SDisable(
    IN VOID *Data
)
{
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  PHAL_I2S_OP pHalI2SOP = &HalI2SOpSAL;
  PHAL_I2S_INIT_DAT pI2SCfg;
  u32 I2Stemp;

  pI2SCfg = pI2SAdapter->pInitDat;
  pI2SCfg->I2SEn = I2S_DISABLE;
  pHalI2SOP->HalI2SEnable(pI2SCfg);

  // Gate IP Clock
  ACTCK_I2S_CCTRL(OFF);
  SLPCK_I2S_CCTRL(OFF);

  // Close I2S bus clock(WS,SCLK,MCLK). If needs that clock, mark this.
  I2Stemp = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) & (~((1<<9) | (1<<10)));
  HAL_WRITE32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1, I2Stemp);

  return HAL_OK;
}

RTK_STATUS
RtkI2SIoCtrl(
    IN VOID *Data
)
{
  return _EXIT_SUCCESS;
}

RTK_STATUS
RtkI2SPowerCtrl(
    IN VOID *Data
)
{
  return _EXIT_SUCCESS;
}

HAL_STATUS
RtkI2SLoadDefault(
    IN VOID *Adapter,
    IN VOID *Setting
)
{
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Adapter;
  PHAL_I2S_INIT_DAT pI2SCfg = pI2SAdapter->pInitDat;
  PHAL_I2S_DEF_SETTING pLoadSetting = (PHAL_I2S_DEF_SETTING)Setting;

  if (pI2SAdapter == 0)
  {
    DBG_I2S_ERR("RtkI2SLoadDefault: Null Pointer\r\n");
    return HAL_ERR_PARA;
  }

  if (pI2SAdapter->pInitDat == NULL)
  {
    DBG_I2S_ERR("RtkI2SLoadDefault: pInitDat is NULL!\r\n", pI2SAdapter->DevNum);
    return HAL_ERR_PARA;
  }

  pI2SAdapter->DevSts = pLoadSetting->DevSts;
  pI2SAdapter->ErrType = 0;
  pI2SAdapter->TimeOut = 0;

  pI2SCfg->I2SIdx = pI2SAdapter->DevNum;
  pI2SCfg->I2SEn = I2S_DISABLE;
  pI2SCfg->I2SMaster = pLoadSetting->I2SMaster;
  pI2SCfg->I2SWordLen = pLoadSetting->I2SWordLen;
  pI2SCfg->I2SChNum = pLoadSetting->I2SChNum;
  pI2SCfg->I2SPageNum = pLoadSetting->I2SPageNum;
  pI2SCfg->I2SPageSize = pLoadSetting->I2SPageSize;
  pI2SCfg->I2SRate = pLoadSetting->I2SRate;
  pI2SCfg->I2STRxAct = pLoadSetting->I2STRxAct;
  pI2SCfg->I2STxIntrMSK = pLoadSetting->I2STxIntrMSK;
  pI2SCfg->I2SRxIntrMSK = pLoadSetting->I2SRxIntrMSK;

  return HAL_OK;
}

VOID HalI2SOpInit(
    IN VOID *Data
)
{
  PHAL_I2S_OP pHalI2SOp = (PHAL_I2S_OP) Data;

  pHalI2SOp->HalI2SDeInit = HalI2SDeInitRtl8195a;
  pHalI2SOp->HalI2STx = HalI2STxRtl8195a;
  pHalI2SOp->HalI2SRx = HalI2SRxRtl8195a;
  pHalI2SOp->HalI2SEnable = HalI2SEnableRtl8195a;
  pHalI2SOp->HalI2SIntrCtrl = HalI2SIntrCtrlRtl8195a;
  pHalI2SOp->HalI2SReadReg = HalI2SReadRegRtl8195a;
  pHalI2SOp->HalI2SClrIntr = HalI2SClrIntrRtl8195a;
  pHalI2SOp->HalI2SClrAllIntr = HalI2SClrAllIntrRtl8195a;
  pHalI2SOp->HalI2SDMACtrl = HalI2SDMACtrlRtl8195a;

#ifndef CONFIG_CHIP_E_CUT
  pHalI2SOp->HalI2SInit = HalI2SInitRtl8195a_Patch;
  pHalI2SOp->HalI2SSetRate = HalI2SSetRateRtl8195a;
  pHalI2SOp->HalI2SSetWordLen = HalI2SSetWordLenRtl8195a;
  pHalI2SOp->HalI2SSetChNum = HalI2SSetChNumRtl8195a;
  pHalI2SOp->HalI2SSetPageNum = HalI2SSetPageNumRtl8195a;
  pHalI2SOp->HalI2SSetPageSize = HalI2SSetPageSizeRtl8195a;
#else
  pHalI2SOp->HalI2SInit = HalI2SInitRtl8195a_V04;
  pHalI2SOp->HalI2SSetRate = HalI2SSetRateRtl8195a_V04;
  pHalI2SOp->HalI2SSetWordLen = HalI2SSetWordLenRtl8195a_V04;
  pHalI2SOp->HalI2SSetChNum = HalI2SSetChNumRtl8195a_V04;
  pHalI2SOp->HalI2SSetPageNum = HalI2SSetPageNumRtl8195a_V04;
  pHalI2SOp->HalI2SSetPageSize = HalI2SSetPageSizeRtl8195a_V04;
#endif  // #ifndef CONFIG_CHIP_E_CUT
}

HAL_STATUS
HalI2SInit(
    IN VOID *Data
)
{
  HAL_STATUS ret;
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  u32 Function;
  u8 funret;

#ifdef CONFIG_SOC_PS_MODULE
  REG_POWER_STATE I2sPwrState;
#endif

  if(pI2SAdapter->DevNum == 0)
  {
    Function = I2S0;
  }
  else
  {
    Function = I2S1;
  }

  funret = FunctionChk(Function, (u32)pI2SAdapter->PinMux);

  if (funret == _FALSE)
  {
    return HAL_ERR_HW;
  }

  ret = RtkI2SInit(Data);
#ifdef CONFIG_SOC_PS_MODULE
  if(ret == HAL_OK)
  {
    // To register a new peripheral device power state
    I2sPwrState.FuncIdx = I2S0 + pI2SAdapter->DevNum;
    I2sPwrState.PwrState = ACT;
    RegPowerState(I2sPwrState);
  }
#endif

  return ret;

}

VOID
HalI2SDeInit(
    IN VOID *Data
)
{
#ifdef CONFIG_SOC_PS_MODULE
  REG_POWER_STATE I2sPwrState;
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
  u8 HwState;

  I2sPwrState.FuncIdx = I2S0 + pI2SAdapter->DevNum;
  QueryRegPwrState(I2sPwrState.FuncIdx, &(I2sPwrState.PwrState), &HwState);

  // if the power state isn't ACT, then switch the power state back to ACT first
  if ((I2sPwrState.PwrState != ACT) && (I2sPwrState.PwrState != INACT))
  {
    HalI2SEnable(Data);
    QueryRegPwrState(I2sPwrState.FuncIdx, &(I2sPwrState.PwrState), &HwState);
  }

  if (I2sPwrState.PwrState == ACT)
  {
    I2sPwrState.PwrState = INACT;
    RegPowerState(I2sPwrState);
  }
#endif

  RtkI2SDeInit(Data);

}

HAL_STATUS
HalI2SDisable(
    IN VOID *Data
)
{
  HAL_STATUS ret;
#ifdef CONFIG_SOC_PS_MODULE
  REG_POWER_STATE I2sPwrState;
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
#endif

  ret = RtkI2SDisable(Data);
#ifdef CONFIG_SOC_PS_MODULE
  if (ret == HAL_OK)
  {
    I2sPwrState.FuncIdx = I2S0 + pI2SAdapter->DevNum;
    I2sPwrState.PwrState = SLPCG;
    RegPowerState(I2sPwrState);
  }
#endif
  return ret;
}

HAL_STATUS
HalI2SEnable(
    IN VOID *Data
)
{
  HAL_STATUS ret;
#ifdef CONFIG_SOC_PS_MODULE
  REG_POWER_STATE I2sPwrState;
  PHAL_I2S_ADAPTER pI2SAdapter = (PHAL_I2S_ADAPTER) Data;
#endif

  ret = RtkI2SEnable(Data);
#ifdef CONFIG_SOC_PS_MODULE
  if (ret == HAL_OK)
  {
    I2sPwrState.FuncIdx = I2S0 + pI2SAdapter->DevNum;
    I2sPwrState.PwrState = ACT;
    RegPowerState(I2sPwrState);
  }
#endif
  return ret;
}

