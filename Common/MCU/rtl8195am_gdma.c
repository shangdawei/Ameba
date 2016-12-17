#include "rtl8195am_gdma.h"

#ifndef CONFIG_CHIP_E_CUT
BOOL
HalGdmaChBlockSetingRtl8195a_Patch(
    IN VOID *Data
)
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) Data;
  PGDMA_CH_LLI_ELE pLliEle;
  struct GDMA_CH_LLI *pGdmaChLli;
  struct BLOCK_SIZE_LIST *pGdmaChBkLi;
  u32 MultiBlockCount = pHalGdmaAdapter->MaxMuliBlock;
  u32 CtlxLow, CtlxUp, CfgxLow, CfgxUp;
  u8 GdmaIndex = pHalGdmaAdapter->GdmaIndex;
  u8 ChNum = pHalGdmaAdapter->ChNum;
  u32 ChEn = pHalGdmaAdapter->ChEn;
  u8 GdmaChIsrBitmap = (ChEn & 0xFF);
  u8 PendingIsrIndex;

  pLliEle = pHalGdmaAdapter->pLlix->pLliEle;
  pGdmaChLli = pHalGdmaAdapter->pLlix->pNextLli;
  pGdmaChBkLi = pHalGdmaAdapter->pBlockSizeList;

  //4 1) Check chanel is avaliable
  if (HAL_GDMAX_READ32(GdmaIndex, REG_GDMA_CH_EN) & ChEn)
  {
    //4 Disable Channel
    DBG_GDMA_WARN("Channel had used; Disable Channel!!!!\n");

    HalGdmaChDisRtl8195a(Data);

  }

  //4 2) Check if there are the pending isr; TFR, Block, Src Tran, Dst Tran,  Error
  for (PendingIsrIndex=0; PendingIsrIndex<5;PendingIsrIndex++)
  {

    u32 PendRaw, PendStstus;
    PendRaw = HAL_GDMAX_READ32(GdmaIndex,
        (REG_GDMA_RAW_INT_BASE + PendingIsrIndex*8));
    PendStstus = HAL_GDMAX_READ32(GdmaIndex,
        (REG_GDMA_STATUS_INT_BASE + PendingIsrIndex*8));

    if ((PendRaw & GdmaChIsrBitmap) || (PendStstus & GdmaChIsrBitmap))
    {
      //4 Clear Pending Isr
      HAL_GDMAX_WRITE32(GdmaIndex,
          (REG_GDMA_CLEAR_INT_BASE + PendingIsrIndex*8),
          (PendStstus & (GdmaChIsrBitmap))
      );

    }
  }

  //4 Fill in SARx register
  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_SAR + ChNum*REG_GDMA_CH_OFF),
      (pHalGdmaAdapter->ChSar)
  );

  //4 Fill in DARx register
  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_DAR + ChNum*REG_GDMA_CH_OFF),
      (pHalGdmaAdapter->ChDar)
  );

  //4 3) Process CTLx
  CtlxLow = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_CTL + ChNum*REG_GDMA_CH_OFF));

  //4 Clear Config low register bits
  CtlxLow &= (BIT_INVC_CTLX_LO_INT_EN &
      BIT_INVC_CTLX_LO_DST_TR_WIDTH &
      BIT_INVC_CTLX_LO_SRC_TR_WIDTH &
      BIT_INVC_CTLX_LO_DINC &
      BIT_INVC_CTLX_LO_SINC &
      BIT_INVC_CTLX_LO_DEST_MSIZE &
      BIT_INVC_CTLX_LO_SRC_MSIZE &
      BIT_INVC_CTLX_LO_TT_FC &
      BIT_INVC_CTLX_LO_LLP_DST_EN &
      BIT_INVC_CTLX_LO_LLP_SRC_EN);

  CtlxUp = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_CTL + ChNum*REG_GDMA_CH_OFF + 4));

  //4 Clear Config upper register bits
  CtlxUp &= (BIT_INVC_CTLX_UP_BLOCK_BS &
      BIT_INVC_CTLX_UP_DONE);

  CtlxLow = BIT_CTLX_LO_INT_EN(pHalGdmaAdapter->GdmaCtl.IntEn) |
  BIT_CTLX_LO_DST_TR_WIDTH(pHalGdmaAdapter->GdmaCtl.DstTrWidth) |
  BIT_CTLX_LO_SRC_TR_WIDTH(pHalGdmaAdapter->GdmaCtl.SrcTrWidth) |
  BIT_CTLX_LO_DINC(pHalGdmaAdapter->GdmaCtl.Dinc) |
  BIT_CTLX_LO_SINC(pHalGdmaAdapter->GdmaCtl.Sinc) |
  BIT_CTLX_LO_DEST_MSIZE(pHalGdmaAdapter->GdmaCtl.DestMsize) |
  BIT_CTLX_LO_SRC_MSIZE(pHalGdmaAdapter->GdmaCtl.SrcMsize) |
  BIT_CTLX_LO_TT_FC(pHalGdmaAdapter->GdmaCtl.TtFc) |
  BIT_CTLX_LO_LLP_DST_EN(pHalGdmaAdapter->GdmaCtl.LlpDstEn) |
  BIT_CTLX_LO_LLP_SRC_EN(pHalGdmaAdapter->GdmaCtl.LlpSrcEn) |
  CtlxLow;

  CtlxUp = BIT_CTLX_UP_BLOCK_BS(pGdmaChBkLi->BlockSize) |
  BIT_CTLX_UP_DONE(pHalGdmaAdapter->GdmaCtl.Done) |
  CtlxUp;

  //4 Fill in CTLx register
  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_CTL + ChNum*REG_GDMA_CH_OFF),
      CtlxLow
  );

  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_CTL + ChNum*REG_GDMA_CH_OFF +4),
      CtlxUp
  );

  //4 4) Program CFGx

  CfgxLow = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_CFG + ChNum*REG_GDMA_CH_OFF));

  CfgxLow &= (BIT_INVC_CFGX_LO_CH_PRIOR &
      BIT_INVC_CFGX_LO_CH_SUSP &
      BIT_INVC_CFGX_LO_HS_SEL_DST &
      BIT_INVC_CFGX_LO_HS_SEL_SRC &
      BIT_INVC_CFGX_LO_LOCK_CH_L &
      BIT_INVC_CFGX_LO_LOCK_B_L &
      BIT_INVC_CFGX_LO_LOCK_CH &
      BIT_INVC_CFGX_LO_LOCK_B &
      BIT_INVC_CFGX_LO_RELOAD_SRC &
      BIT_INVC_CFGX_LO_RELOAD_DST);

  CfgxUp = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_CFG + ChNum*REG_GDMA_CH_OFF + 4));

  CfgxUp &= (BIT_INVC_CFGX_UP_FIFO_MODE &
      BIT_INVC_CFGX_UP_DS_UPD_EN &
      BIT_INVC_CFGX_UP_SS_UPD_EN &
      BIT_INVC_CFGX_UP_SRC_PER &
      BIT_INVC_CFGX_UP_DEST_PER);

  CfgxLow = BIT_CFGX_LO_CH_PRIOR(pHalGdmaAdapter->GdmaCfg.ChPrior) |
  BIT_CFGX_LO_CH_SUSP(pHalGdmaAdapter->GdmaCfg.ChSusp) |
  BIT_CFGX_LO_HS_SEL_DST(pHalGdmaAdapter->GdmaCfg.HsSelDst) |
  BIT_CFGX_LO_HS_SEL_SRC(pHalGdmaAdapter->GdmaCfg.HsSelSrc) |
  BIT_CFGX_LO_LOCK_CH_L(pHalGdmaAdapter->GdmaCfg.LockChL) |
  BIT_CFGX_LO_LOCK_B_L(pHalGdmaAdapter->GdmaCfg.LockBL) |
  BIT_CFGX_LO_LOCK_CH(pHalGdmaAdapter->GdmaCfg.LockCh) |
  BIT_CFGX_LO_LOCK_B(pHalGdmaAdapter->GdmaCfg.LockB) |
  BIT_CFGX_LO_RELOAD_SRC(pHalGdmaAdapter->GdmaCfg.ReloadSrc) |
  BIT_CFGX_LO_RELOAD_DST(pHalGdmaAdapter->GdmaCfg.ReloadDst) |
  CfgxLow;

  CfgxUp = BIT_CFGX_UP_FIFO_MODE(pHalGdmaAdapter->GdmaCfg.FifoMode) |
  BIT_CFGX_UP_DS_UPD_EN(pHalGdmaAdapter->GdmaCfg.DsUpdEn) |
  BIT_CFGX_UP_SS_UPD_EN(pHalGdmaAdapter->GdmaCfg.SsUpdEn) |
  BIT_CFGX_UP_SRC_PER(pHalGdmaAdapter->GdmaCfg.SrcPer) |
  BIT_CFGX_UP_DEST_PER(pHalGdmaAdapter->GdmaCfg.DestPer) |
  CfgxUp;

  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_CFG + ChNum*REG_GDMA_CH_OFF),
      CfgxLow
  );

  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_CFG + ChNum*REG_GDMA_CH_OFF +4),
      CfgxUp
  );

  //4 Check 4 Bytes Alignment
  if ((u32)(pLliEle) & 0x3)
  {
    DBG_GDMA_WARN("LLi Addr: 0x%x not 4 bytes alignment!!!!\n",
        pHalGdmaAdapter->pLli);
    return _FALSE;
  }

  HAL_GDMAX_WRITE32(GdmaIndex,
      (REG_GDMA_CH_LLP + ChNum*REG_GDMA_CH_OFF),
      pLliEle
  );

  //4 Update the first llp0
  pLliEle->CtlxLow = CtlxLow;
  pLliEle->CtlxUp = CtlxUp;
  pLliEle->Llpx = (u32)pGdmaChLli->pLliEle;
  DBG_GDMA_INFO("Block Count %d\n", MultiBlockCount);

  pGdmaChBkLi = pGdmaChBkLi->pNextBlockSiz;

  while (MultiBlockCount > 1)
  {
    MultiBlockCount--;
    DBG_GDMA_INFO("Block Count %d\n", MultiBlockCount);
    pLliEle = pGdmaChLli->pLliEle;

    if (NULL == pLliEle)
    {
      DBG_GDMA_ERR("pLliEle Null Point!!!!!\n");
      return _FALSE;
    }

    //4 Clear the last element llp enable bit
    if (1 == MultiBlockCount)
    {
      if (((pHalGdmaAdapter->Rsvd4to7) & 0x01) == 1)
      {
        CtlxLow &= (BIT_INVC_CTLX_LO_LLP_DST_EN &
            BIT_INVC_CTLX_LO_LLP_SRC_EN);
      }
    }
    //4 Update block size for transfer
    CtlxUp &= (BIT_INVC_CTLX_UP_BLOCK_BS);
    CtlxUp |= BIT_CTLX_UP_BLOCK_BS(pGdmaChBkLi->BlockSize);

    //4 Update tje Lli and Block size list point to next llp
    pGdmaChLli = pGdmaChLli->pNextLli;
    pGdmaChBkLi = pGdmaChBkLi->pNextBlockSiz;

    //4 Updatethe Llpx context
    pLliEle->CtlxLow = CtlxLow;
    pLliEle->CtlxUp = CtlxUp;
    pLliEle->Llpx = (u32)(pGdmaChLli->pLliEle);

  }

  return _TRUE;
}

u32
HalGdmaQueryDArRtl8195a(
    IN VOID *Data
)
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) Data;
  u8 GdmaIndex = pHalGdmaAdapter->GdmaIndex;
  u8 ChNum = pHalGdmaAdapter->ChNum;
  u32 dar;

  dar = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_DAR + ChNum*REG_GDMA_CH_OFF));

  return dar;
}

u32
HalGdmaQuerySArRtl8195a(
    IN VOID *Data
)
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) Data;
  u8 GdmaIndex = pHalGdmaAdapter->GdmaIndex;
  u8 ChNum = pHalGdmaAdapter->ChNum;
  u32 dar;

  dar = HAL_GDMAX_READ32(GdmaIndex,
      (REG_GDMA_CH_SAR + ChNum*REG_GDMA_CH_OFF));

  return dar;
}

BOOL
HalGdmaQueryChEnRtl8195a (
    IN VOID *Data
)
{

  PHAL_GDMA_ADAPTER pHalGdmaAdapter = Data;

  if (HAL_GDMAX_READ32(pHalGdmaAdapter->GdmaIndex, REG_GDMA_CH_EN) & (pHalGdmaAdapter->ChEn))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

#endif

#define MAX_GDMA_INDX       1
#define MAX_GDMA_CHNL       6

static u8 HalGdmaReg[ MAX_GDMA_INDX + 1 ];

const HAL_GDMA_CHNL GDMA_Chnl_Option[ ] = {
  {
    0, 0, GDMA0_CHANNEL0_IRQ, 0 }, {
    1, 0, GDMA1_CHANNEL0_IRQ, 0 }, {
    0, 1, GDMA0_CHANNEL1_IRQ, 0 }, {
    1, 1, GDMA1_CHANNEL1_IRQ, 0 }, {
    0, 2, GDMA0_CHANNEL2_IRQ, 0 }, {
    1, 2, GDMA1_CHANNEL2_IRQ, 0 }, {
    0, 3, GDMA0_CHANNEL3_IRQ, 0 }, {
    1, 3, GDMA1_CHANNEL3_IRQ, 0 }, {
    0, 4, GDMA0_CHANNEL4_IRQ, 0 }, {
    1, 4, GDMA1_CHANNEL4_IRQ, 0 }, {
    0, 5, GDMA0_CHANNEL5_IRQ, 0 }, {
    1, 5, GDMA1_CHANNEL5_IRQ, 0 },

  {
    0xff, 0, 0, 0 }    // end
};

const HAL_GDMA_CHNL GDMA_Multi_Block_Chnl_Option[ ] = {
  {
    0, 4, GDMA0_CHANNEL4_IRQ, 0 }, {
    1, 4, GDMA1_CHANNEL4_IRQ, 0 }, {
    0, 5, GDMA0_CHANNEL5_IRQ, 0 }, {
    1, 5, GDMA1_CHANNEL5_IRQ, 0 },

  {
    0xff, 0, 0, 0 }    // end
};

const u16 HalGdmaChnlEn[ 6 ] = {
  GdmaCh0, GdmaCh1, GdmaCh2, GdmaCh3, GdmaCh4, GdmaCh5 };

VOID HalGdmaOpInit(
    IN VOID *Data
)
{
  PHAL_GDMA_OP pHalGdmaOp = (PHAL_GDMA_OP) Data;

  pHalGdmaOp->HalGdmaOnOff = HalGdmaOnOffRtl8195a;
  pHalGdmaOp->HalGdamChInit = HalGdamChInitRtl8195a;
  pHalGdmaOp->HalGdmaChDis = HalGdmaChDisRtl8195a;
  pHalGdmaOp->HalGdmaChEn = HalGdmaChEnRtl8195a;
  pHalGdmaOp->HalGdmaChSeting = HalGdmaChSetingRtl8195a;
#ifndef CONFIG_CHIP_E_CUT
  pHalGdmaOp->HalGdmaChBlockSeting = HalGdmaChBlockSetingRtl8195a_Patch;
#else
  pHalGdmaOp->HalGdmaChBlockSeting = HalGdmaChBlockSetingRtl8195a_V04;
#endif
  pHalGdmaOp->HalGdmaChIsrEnAndDis = HalGdmaChIsrEnAndDisRtl8195a;
  pHalGdmaOp->HalGdmaChIsrClean = HalGdmaChIsrCleanRtl8195a;
  pHalGdmaOp->HalGdmaChCleanAutoSrc = HalGdmaChCleanAutoSrcRtl8195a;
  pHalGdmaOp->HalGdmaChCleanAutoDst = HalGdmaChCleanAutoDstRtl8195a;
}

VOID HalGdmaOn( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  pHalGdmaAdapter->GdmaOnOff = ON;
  HalGdmaOnOffRtl8195a( (VOID*) pHalGdmaAdapter );
}

VOID HalGdmaOff( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  pHalGdmaAdapter->GdmaOnOff = OFF;
  HalGdmaOnOffRtl8195a( (VOID*) pHalGdmaAdapter );
}

BOOL HalGdmaChInit( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  return ( HalGdamChInitRtl8195a( (VOID*) pHalGdmaAdapter ) );
}

VOID HalGdmaChDis( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  HalGdmaChDisRtl8195a( (VOID*) pHalGdmaAdapter );
}

VOID HalGdmaChEn( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  HalGdmaChEnRtl8195a( (VOID*) pHalGdmaAdapter );
}

BOOL HalGdmaChSeting( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  return ( HalGdmaChSetingRtl8195a( (VOID*) pHalGdmaAdapter ) );
}

BOOL HalGdmaChBlockSeting( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
#ifndef CONFIG_CHIP_E_CUT
  return ( HalGdmaChBlockSetingRtl8195a_Patch( (VOID*) pHalGdmaAdapter ) );
#else
  return (HalGdmaChBlockSetingRtl8195a_V04((VOID*)pHalGdmaAdapter));
#endif
}

VOID HalGdmaChIsrEn( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  pHalGdmaAdapter->IsrCtrl = ENABLE;
  HalGdmaChIsrEnAndDisRtl8195a( (VOID*) pHalGdmaAdapter );
}

VOID HalGdmaChIsrDis( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  pHalGdmaAdapter->IsrCtrl = DISABLE;
  HalGdmaChIsrEnAndDisRtl8195a( (VOID*) pHalGdmaAdapter );
}

u8 HalGdmaChIsrClean( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  return ( HalGdmaChIsrCleanRtl8195a( (VOID*) pHalGdmaAdapter ) );
}

VOID HalGdmaChCleanAutoSrc( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  HalGdmaChCleanAutoSrcRtl8195a( (VOID*) pHalGdmaAdapter );
}

VOID HalGdmaChCleanAutoDst( PHAL_GDMA_ADAPTER pHalGdmaAdapter )
{
  HalGdmaChCleanAutoDstRtl8195a( (VOID*) pHalGdmaAdapter );
}

HAL_STATUS HalGdmaChnlRegister( u8 GdmaIdx, u8 ChnlNum )
{
  u32 mask;

  if ( ( GdmaIdx > MAX_GDMA_INDX ) || ( ChnlNum > MAX_GDMA_CHNL ) )
  {
    // Invalid GDMA Index or Channel Number
    return HAL_ERR_PARA;
  }

  mask = 1 << ChnlNum;

  if ( ( HalGdmaReg[ GdmaIdx ] & mask ) != 0 )
  {
    return HAL_BUSY;
  }
  else
  {
#if 1
    if ( HalGdmaReg[ GdmaIdx ] == 0 )
    {
      if ( GdmaIdx == 0 )
      {
        ACTCK_GDMA0_CCTRL( ON );
        GDMA0_FCTRL( ON );
      }
      else
      {
        ACTCK_GDMA1_CCTRL( ON );
        GDMA1_FCTRL( ON );
      }
    }
#endif
    HalGdmaReg[ GdmaIdx ] |= mask;
    return HAL_OK;
  }
}

VOID HalGdmaChnlUnRegister( u8 GdmaIdx, u8 ChnlNum )
{
  u32 mask;

  if ( ( GdmaIdx > MAX_GDMA_INDX ) || ( ChnlNum > MAX_GDMA_CHNL ) )
  {
    // Invalid GDMA Index or Channel Number
    return;
  }

  mask = 1 << ChnlNum;

  HalGdmaReg[ GdmaIdx ] &= ~mask;
#if 1
  if ( HalGdmaReg[ GdmaIdx ] == 0 )
  {
    if ( GdmaIdx == 0 )
    {
      ACTCK_GDMA0_CCTRL( OFF );
      GDMA0_FCTRL( OFF );
    }
    else
    {
      ACTCK_GDMA1_CCTRL( OFF );
      GDMA1_FCTRL( OFF );
    }
  }
#endif
}

PHAL_GDMA_CHNL HalGdmaChnlAlloc( HAL_GDMA_CHNL *pChnlOption )
{
  HAL_GDMA_CHNL *pgdma_chnl;

  pgdma_chnl = pChnlOption;
  if ( pChnlOption == NULL )
  {
    // Use default GDMA Channel Option table
    pgdma_chnl = (HAL_GDMA_CHNL*) &GDMA_Chnl_Option[ 0 ];
  }
  else
  {
    pgdma_chnl = (HAL_GDMA_CHNL*) pgdma_chnl;
  }

  while ( pgdma_chnl->GdmaIndx <= MAX_GDMA_INDX )
  {
    if ( HalGdmaChnlRegister( pgdma_chnl->GdmaIndx, pgdma_chnl->GdmaChnl ) == HAL_OK )
    {
      // This GDMA Channel is available
      break;
    }
    pgdma_chnl += 1;
  }

  if ( pgdma_chnl->GdmaIndx > MAX_GDMA_INDX )
  {
    pgdma_chnl = NULL;
  }

  return pgdma_chnl;
}

VOID HalGdmaChnlFree( HAL_GDMA_CHNL *pChnl )
{
  IRQ_HANDLE IrqHandle;

  IrqHandle.IrqNum = pChnl->IrqNum;
  InterruptDis( &IrqHandle );
  InterruptUnRegister( &IrqHandle );
  HalGdmaChnlUnRegister( pChnl->GdmaIndx, pChnl->GdmaChnl );
}

VOID HalGdmaMemIrqHandler( VOID *pData )
{
  PHAL_GDMA_OBJ pHalGdmaObj = (PHAL_GDMA_OBJ) pData;
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PIRQ_HANDLE pGdmaIrqHandle;

  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );
  pGdmaIrqHandle = &( pHalGdmaObj->GdmaIrqHandle );
  // Clean Auto Reload Bit
  HalGdmaChCleanAutoDst( (VOID*) pHalGdmaAdapter );

  // Clear Pending ISR
  HalGdmaChIsrClean( (VOID*) pHalGdmaAdapter );

  HalGdmaChDis( (VOID*) ( pHalGdmaAdapter ) );
  pHalGdmaObj->Busy = 0;

  if ( pGdmaIrqHandle->IrqFun != NULL )
  {
    pGdmaIrqHandle->IrqFun( (VOID*) pGdmaIrqHandle->Data );
  }
}

BOOL HalGdmaMemCpyAggrInit( PHAL_GDMA_OBJ pHalGdmaObj )
{
  HAL_GDMA_CHNL *pgdma_chnl;
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PIRQ_HANDLE pGdmaIrqHandle;
  IRQ_HANDLE IrqHandle;

  pgdma_chnl = HalGdmaChnlAlloc( ( PHAL_GDMA_CHNL ) & GDMA_Multi_Block_Chnl_Option[ 0 ] );// get a whatever GDMA channel
  if ( NULL == pgdma_chnl )
  {
    DBG_GDMA_ERR( "%s: Cannot allocate a GDMA Channel\n", __FUNCTION__ );
    return _FALSE;
  }

  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );
  pGdmaIrqHandle = &( pHalGdmaObj->GdmaIrqHandle );

  DBG_GDMA_INFO( "%s: Use GDMA%d CH%d\n", __FUNCTION__, pgdma_chnl->GdmaIndx,
    pgdma_chnl->GdmaChnl );

  _memset( (void *) pHalGdmaAdapter, 0, sizeof(HAL_GDMA_ADAPTER) );

  pHalGdmaAdapter->GdmaCtl.TtFc = TTFCMemToMem;
  pHalGdmaAdapter->GdmaCtl.Done = 1;
  pHalGdmaAdapter->MuliBlockCunt = 0;
  pHalGdmaAdapter->MaxMuliBlock = 1;
  pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
  pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->GdmaIsrType = ( TransferType | ErrType );
  pHalGdmaAdapter->IsrCtrl = ENABLE;
  pHalGdmaAdapter->GdmaOnOff = ON;
  pHalGdmaAdapter->GdmaCtl.IntEn = 1;
  pHalGdmaAdapter->Rsvd4to7 = 1;
  pHalGdmaAdapter->Llpctrl = 1;
  pGdmaIrqHandle->IrqNum = pgdma_chnl->IrqNum;
  pGdmaIrqHandle->Priority = 10;

  IrqHandle.IrqFun = (IRQ_FUN) HalGdmaMemIrqHandler;
  IrqHandle.Data = (u32) pHalGdmaObj;
  IrqHandle.IrqNum = pGdmaIrqHandle->IrqNum;
  IrqHandle.Priority = pGdmaIrqHandle->Priority;

  InterruptRegister( &IrqHandle );
  InterruptEn( &IrqHandle );
  pHalGdmaObj->Busy = 0;

  return _TRUE;
}

VOID HalGdmaMultiBlockSetting( PHAL_GDMA_OBJ pHalGdmaObj, PHAL_GDMA_BLOCK pHalGdmaBlock )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  u8 BlockNumber;
  u8 BlockIndex;
  u8 FourBytesAlign;

  BlockNumber = pHalGdmaObj->BlockNum;
  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );

  pHalGdmaAdapter->GdmaCtl.LlpSrcEn = 1;
  pHalGdmaAdapter->GdmaCtl.LlpDstEn = 1;

  if ( ( ( pHalGdmaBlock[ 0 ].SrcAddr & 0x03 ) == 0 )
    && ( ( pHalGdmaBlock[ 0 ].DstAddr & 0x03 ) == 0 )
    && ( ( pHalGdmaBlock[ 0 ].BlockLength & 0X03 ) == 0 ) )
  {
    pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
    pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
    FourBytesAlign = 1;
  }
  else
  {
    pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
    pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
    FourBytesAlign = 0;
  }

  for ( BlockIndex = 0; BlockIndex < BlockNumber; BlockIndex++ )
  {

    pHalGdmaObj->GdmaChLli[ BlockIndex ].Sarx = pHalGdmaBlock[ BlockIndex ].SrcAddr;
    pHalGdmaObj->GdmaChLli[ BlockIndex ].Darx = pHalGdmaBlock[ BlockIndex ].DstAddr;
    pHalGdmaObj->BlockSizeList[ BlockIndex ].pNextBlockSiz = &pHalGdmaObj->BlockSizeList[ BlockIndex
      + 1 ];

    if ( FourBytesAlign )
    {
      pHalGdmaObj->BlockSizeList[ BlockIndex ].BlockSize = pHalGdmaBlock[ BlockIndex ].BlockLength
        >> 2;
    }
    else
    {
      pHalGdmaObj->BlockSizeList[ BlockIndex ].BlockSize = pHalGdmaBlock[ BlockIndex ].BlockLength;
    }

    pHalGdmaObj->Lli[ BlockIndex ].pLliEle =
      (GDMA_CH_LLI_ELE*) &pHalGdmaObj->GdmaChLli[ BlockIndex ];
    pHalGdmaObj->Lli[ BlockIndex ].pNextLli = &pHalGdmaObj->Lli[ BlockIndex + 1 ];

    if ( BlockIndex == BlockNumber - 1 )
    {
      pHalGdmaObj->BlockSizeList[ BlockIndex ].pNextBlockSiz = NULL;
      pHalGdmaObj->Lli[ BlockIndex ].pNextLli = NULL;
    }
    //DBG_GDMA_INFO("Lli[%d].pLiEle = %x\r\n", BlockIndex,Lli[BlockIndex].pLliEle);
    //DBG_GDMA_INFO("Lli[%d].pNextLli = %x\r\n", BlockIndex,Lli[BlockIndex].pNextLli);
  }

  pHalGdmaAdapter->pBlockSizeList = (struct BLOCK_SIZE_LIST*) &pHalGdmaObj->BlockSizeList;
  pHalGdmaAdapter->pLlix = (struct GDMA_CH_LLI*) &pHalGdmaObj->Lli;
  //DBG_GDMA_INFO("pHalGdmaAdapter->pBlockSizeList = %x\r\n", pHalGdmaAdapter->pBlockSizeList);
  //DBG_GDMA_INFO("pHalGdmaAdapter->pLlix  = %x\r\n", pHalGdmaAdapter->pLlix );
}

VOID HalGdmaLLPMemAlign( PHAL_GDMA_OBJ pHalGdmaObj, PHAL_GDMA_BLOCK pHalGdmaBlock )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PGDMA_CH_LLI_ELE pLliEle;
  struct GDMA_CH_LLI *pGdmaChLli;
  struct BLOCK_SIZE_LIST *pGdmaChBkLi;
  u32 CtlxLow;
  u32 CtlxUp;
  u8 BlockNumber;
  u8 BlockIndex;

  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );
  BlockNumber = pHalGdmaObj->BlockNum;

  pLliEle = pHalGdmaAdapter->pLlix->pLliEle;
  pGdmaChLli = pHalGdmaAdapter->pLlix->pNextLli;
  pGdmaChBkLi = pHalGdmaAdapter->pBlockSizeList;

  //4 Move to the second block to configure Memory Alginment setting
  pLliEle->Llpx = (u32) pGdmaChLli->pLliEle;
  pGdmaChBkLi = pGdmaChBkLi->pNextBlockSiz;

  for ( BlockIndex = 1; BlockIndex < BlockNumber; BlockIndex++ )
  {
    pLliEle = pGdmaChLli->pLliEle;
    CtlxLow = pLliEle->CtlxLow;
    CtlxLow &= ( BIT_INVC_CTLX_LO_DST_TR_WIDTH & BIT_INVC_CTLX_LO_SRC_TR_WIDTH );
    CtlxUp = pLliEle->CtlxUp;
    CtlxUp &= ( BIT_INVC_CTLX_UP_BLOCK_BS );

    if ( ( ( pHalGdmaBlock[ BlockIndex ].SrcAddr & 0x03 ) == 0 )
      && ( ( pHalGdmaBlock[ BlockIndex ].DstAddr & 0x03 ) == 0 )
      && ( ( pHalGdmaBlock[ BlockIndex ].BlockLength & 0X03 ) == 0 ) )
    {
      pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
      pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
      pGdmaChBkLi->BlockSize = pHalGdmaBlock[ BlockIndex ].BlockLength >> 2;

    }
    else
    {
      pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
      pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
      pGdmaChBkLi->BlockSize = pHalGdmaBlock[ BlockIndex ].BlockLength;
    }

    CtlxLow |= ( BIT_CTLX_LO_DST_TR_WIDTH( pHalGdmaAdapter->GdmaCtl.DstTrWidth )
      | BIT_CTLX_LO_SRC_TR_WIDTH( pHalGdmaAdapter->GdmaCtl.SrcTrWidth ) );
    CtlxUp |= BIT_CTLX_UP_BLOCK_BS( pGdmaChBkLi->BlockSize );

    pGdmaChLli = pGdmaChLli->pNextLli;
    pGdmaChBkLi = pGdmaChBkLi->pNextBlockSiz;
    pLliEle->CtlxLow = CtlxLow;
    pLliEle->CtlxUp = CtlxUp;
    pLliEle->Llpx = ( u32 )( pGdmaChLli->pLliEle );

  }
}

VOID HalGdmaMemAggr( PHAL_GDMA_OBJ pHalGdmaObj, PHAL_GDMA_BLOCK pHalGdmaBlock )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;

  u8 BlockNumber;

  BlockNumber = pHalGdmaObj->BlockNum;
  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );

  if ( pHalGdmaObj->Busy )
  {
    DBG_GDMA_ERR( "%s: ==> GDMA is Busy\r\n", __FUNCTION__ );
    return;
  }
  pHalGdmaObj->Busy = 1;

  pHalGdmaAdapter->MaxMuliBlock = BlockNumber;
  pHalGdmaAdapter->ChSar = pHalGdmaBlock[ 0 ].SrcAddr;
  pHalGdmaAdapter->ChDar = pHalGdmaBlock[ 0 ].DstAddr;

  HalGdmaMultiBlockSetting( pHalGdmaObj, pHalGdmaBlock );
  HalGdmaOn( ( pHalGdmaAdapter ) );
  HalGdmaChIsrEn( ( pHalGdmaAdapter ) );
  HalGdmaChBlockSeting( ( pHalGdmaAdapter ) );
  HalGdmaLLPMemAlign( pHalGdmaObj, pHalGdmaBlock );
  HalGdmaChEn( ( pHalGdmaAdapter ) );

}

BOOL HalGdmaMemCpyInit( PHAL_GDMA_OBJ pHalGdmaObj )
{
  HAL_GDMA_CHNL *pgdma_chnl;
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PIRQ_HANDLE pGdmaIrqHandle;
  IRQ_HANDLE IrqHandle;

  pgdma_chnl = HalGdmaChnlAlloc( NULL );    // get a whatever GDMA channel
  if ( NULL == pgdma_chnl )
  {
    DBG_GDMA_ERR( "%s: Cannot allocate a GDMA Channel\n", __FUNCTION__ );
    return _FALSE;
  }

  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );
  pGdmaIrqHandle = &( pHalGdmaObj->GdmaIrqHandle );

  DBG_GDMA_INFO( "%s: Use GDMA%d CH%d\n", __FUNCTION__, pgdma_chnl->GdmaIndx,
    pgdma_chnl->GdmaChnl );
#if 0
  if (pgdma_chnl->GdmaIndx == 0)
  {
    ACTCK_GDMA0_CCTRL(ON);
    GDMA0_FCTRL(ON);
  }
  else if (pgdma_chnl->GdmaIndx == 1)
  {
    ACTCK_GDMA1_CCTRL(ON);
    GDMA1_FCTRL(ON);
  }
#endif
  _memset( (void *) pHalGdmaAdapter, 0, sizeof(HAL_GDMA_ADAPTER) );

//    pHalGdmaAdapter->GdmaCtl.TtFc = TTFCMemToMem;
  pHalGdmaAdapter->GdmaCtl.Done = 1;
//    pHalGdmaAdapter->MuliBlockCunt = 0;
//    pHalGdmaAdapter->MaxMuliBlock = 1;
  pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
  pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->GdmaIsrType = ( TransferType | ErrType );
  pHalGdmaAdapter->IsrCtrl = ENABLE;
  pHalGdmaAdapter->GdmaOnOff = ON;

  pHalGdmaAdapter->GdmaCtl.IntEn = 1;
//    pHalGdmaAdapter->GdmaCtl.SrcMsize   = MsizeEight;
//    pHalGdmaAdapter->GdmaCtl.DestMsize  = MsizeEight;
//    pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
//    pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
//    pHalGdmaAdapter->GdmaCtl.Dinc = IncType;
//    pHalGdmaAdapter->GdmaCtl.Sinc = IncType;

  pGdmaIrqHandle->IrqNum = pgdma_chnl->IrqNum;
  pGdmaIrqHandle->Priority = 10;

  IrqHandle.IrqFun = (IRQ_FUN) HalGdmaMemIrqHandler;
  IrqHandle.Data = (u32) pHalGdmaObj;
  IrqHandle.IrqNum = pGdmaIrqHandle->IrqNum;
  IrqHandle.Priority = pGdmaIrqHandle->Priority;

  InterruptRegister( &IrqHandle );
  InterruptEn( &IrqHandle );
  pHalGdmaObj->Busy = 0;

  return _TRUE;
}

VOID HalGdmaMemCpyDeInit( PHAL_GDMA_OBJ pHalGdmaObj )
{
  HAL_GDMA_CHNL GdmaChnl;
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PIRQ_HANDLE pGdmaIrqHandle;

  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );
  pGdmaIrqHandle = &( pHalGdmaObj->GdmaIrqHandle );

  GdmaChnl.GdmaIndx = pHalGdmaAdapter->GdmaIndex;
  GdmaChnl.GdmaChnl = pHalGdmaAdapter->ChNum;
  GdmaChnl.IrqNum = pGdmaIrqHandle->IrqNum;
  HalGdmaChnlFree( &GdmaChnl );
}

// If multi-task using the same GDMA Object, then it needs a mutex to protect this procedure
VOID* HalGdmaMemCpy( PHAL_GDMA_OBJ pHalGdmaObj, void* pDest, void* pSrc, u32 len )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;

  if ( pHalGdmaObj->Busy )
  {
    DBG_GDMA_ERR( "%s: ==> GDMA is Busy\r\n", __FUNCTION__ );
    return 0;
  }
  pHalGdmaObj->Busy = 1;
  pHalGdmaAdapter = &( pHalGdmaObj->HalGdmaAdapter );

  DBG_GDMA_INFO( "%s: ==> Src=0x%x Dst=0x%x Len=%d\r\n", __FUNCTION__, pSrc, pDest, len );
  if ( ( ( (u32) pSrc & 0x03 ) == 0 ) && ( ( (u32) pDest & 0x03 ) == 0 )
    && ( ( len & 0x03 ) == 0 ) )
  {
    // 4-bytes aligned, move 4 bytes each transfer
    pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
    pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
    pHalGdmaAdapter->GdmaCtl.BlockSize = len >> 2;
  }
  else
  {
    pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
    pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeEight;
    pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
    pHalGdmaAdapter->GdmaCtl.BlockSize = len;
  }

  pHalGdmaAdapter->ChSar = (u32) pSrc;
  pHalGdmaAdapter->ChDar = (u32) pDest;
  pHalGdmaAdapter->PacketLen = len;

  HalGdmaOn( ( pHalGdmaAdapter ) );
  HalGdmaChIsrEn( ( pHalGdmaAdapter ) );
  HalGdmaChSeting( ( pHalGdmaAdapter ) );
  HalGdmaChEn( ( pHalGdmaAdapter ) );

  return ( pDest );
}

#ifdef CONFIG_GPIO_EN

HAL_GPIO_ADAPTER gHAL_Gpio_Adapter;
extern PHAL_GPIO_ADAPTER _pHAL_Gpio_Adapter;

extern VOID GPIO_PullCtrl_8195a(u32 chip_pin, u8 pull_type);

/**
 * @brief  To get the GPIO IP Pin name for the given chip pin name
 *
 * @param  chip_pin: The chip pin name.
 *
 * @retval The gotten GPIO IP pin name
 */
u32
HAL_GPIO_GetPinName(
    u32 chip_pin
)
{
  return HAL_GPIO_GetIPPinName_8195a((u32)chip_pin);
}

/**
 * @brief  Set the GPIO pad Pull type
 *
 *  @param    pin: The pin for pull type control.
 *  @param    mode: the pull type for the pin.
 *  @return   None
 */
VOID
HAL_GPIO_PullCtrl(
    u32 pin,
    u32 mode
)
{
  u8 pull_type;

  switch (mode)
  {
    case hal_PullNone:
    pull_type = DIN_PULL_NONE;
    break;

    case hal_PullDown:
    pull_type = DIN_PULL_LOW;
    break;

    case hal_PullUp:
    pull_type = DIN_PULL_HIGH;
    break;

    case hal_OpenDrain:
    default:
    pull_type = DIN_PULL_NONE;
    break;
  }

//    HAL_GPIO_PullCtrl_8195a (pin, pull_type);
  GPIO_PullCtrl_8195a (pin, pull_type);
}

/**
 * @brief  Initializes a GPIO Pin by the GPIO_Pin parameters.
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin initialization.
 *
 * @retval HAL_STATUS
 */
VOID
HAL_GPIO_Init(
    HAL_GPIO_PIN *GPIO_Pin
)
{
  u8 port_num;
  u8 pin_num;
  u32 chip_pin;
  HAL_STATUS ret;

  if (_pHAL_Gpio_Adapter == NULL)
  {
    _pHAL_Gpio_Adapter = &gHAL_Gpio_Adapter;
//        DBG_GPIO_INFO("HAL_GPIO_Init: Initial GPIO Adapter\n ");
  }

  port_num = HAL_GPIO_GET_PORT_BY_NAME(GPIO_Pin->pin_name);
  pin_num = HAL_GPIO_GET_PIN_BY_NAME(GPIO_Pin->pin_name);
  chip_pin = GPIO_GetChipPinName_8195a(port_num, pin_num);
  if (GpioFunctionChk(chip_pin, ENABLE) == _FALSE)
  {
    DBG_GPIO_ERR("HAL_GPIO_Init: GPIO Pin(%x) Unavailable\n ", chip_pin);
    return;
  }

  // Make the pin pull control default as High-Z
  GPIO_PullCtrl_8195a(chip_pin, HAL_GPIO_HIGHZ);

  ret = HAL_GPIO_Init_8195a(GPIO_Pin);

  if (ret != HAL_OK)
  {
    GpioFunctionChk(chip_pin, DISABLE);
  }
}

/**
 * @brief  Initializes a GPIO Pin as a interrupt signal
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin initialization.
 *
 * @retval HAL_STATUS
 */
VOID
HAL_GPIO_Irq_Init(
    HAL_GPIO_PIN *GPIO_Pin
)
{
  u8 port_num;
  u8 pin_num;
  u32 chip_pin;
  HAL_STATUS ret;

  if (_pHAL_Gpio_Adapter == NULL)
  {
    _pHAL_Gpio_Adapter = &gHAL_Gpio_Adapter;
//        DBG_GPIO_INFO("%s: Initial GPIO Adapter\n ", __FUNCTION__);
  }

  if (_pHAL_Gpio_Adapter->IrqHandle.IrqFun == NULL)
  {
    _pHAL_Gpio_Adapter->IrqHandle.IrqFun = (IRQ_FUN)HAL_GPIO_MbedIrqHandler_8195a;
    _pHAL_Gpio_Adapter->IrqHandle.Priority = 6;
    HAL_GPIO_RegIrq_8195a(&_pHAL_Gpio_Adapter->IrqHandle);
    InterruptEn(&_pHAL_Gpio_Adapter->IrqHandle);
//        DBG_GPIO_INFO("%s: Initial GPIO IRQ Adapter\n ", __FUNCTION__);
  }

  port_num = HAL_GPIO_GET_PORT_BY_NAME(GPIO_Pin->pin_name);
  pin_num = HAL_GPIO_GET_PIN_BY_NAME(GPIO_Pin->pin_name);
  chip_pin = GPIO_GetChipPinName_8195a(port_num, pin_num);
  if (GpioFunctionChk(chip_pin, ENABLE) == _FALSE)
  {
    DBG_GPIO_ERR("HAL_GPIO_Irq_Init: GPIO Pin(%x) Unavailable\n ", chip_pin);
    return;
  }

  DBG_GPIO_INFO("HAL_GPIO_Irq_Init: GPIO(name=0x%x)(mode=%d)\n ", GPIO_Pin->pin_name,
      GPIO_Pin->pin_mode);
  HAL_GPIO_MaskIrq_8195a(GPIO_Pin);
  ret = HAL_GPIO_Init_8195a(GPIO_Pin);
  if (ret != HAL_OK)
  {
    GpioFunctionChk(chip_pin, DISABLE);
  }
}

/**
 * @brief  UnInitial GPIO Adapter
 *
 *
 * @retval HAL_STATUS
 */
VOID
HAL_GPIO_IP_DeInit(
    VOID
)
{
  if (_pHAL_Gpio_Adapter != NULL)
  {
    InterruptDis(&_pHAL_Gpio_Adapter->IrqHandle);
    HAL_GPIO_UnRegIrq_8195a(&_pHAL_Gpio_Adapter->IrqHandle);
    _pHAL_Gpio_Adapter = NULL;
  }

}

/**
 * @brief  De-Initializes a GPIO Pin, reset it as default setting.
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @retval HAL_STATUS
 */
VOID
HAL_GPIO_DeInit(
    HAL_GPIO_PIN *GPIO_Pin
)
{
  u8 port_num;
  u8 pin_num;
  u32 chip_pin;

  port_num = HAL_GPIO_GET_PORT_BY_NAME(GPIO_Pin->pin_name);
  pin_num = HAL_GPIO_GET_PIN_BY_NAME(GPIO_Pin->pin_name);
  chip_pin = GPIO_GetChipPinName_8195a(port_num, pin_num);
  HAL_GPIO_DeInit_8195a(GPIO_Pin);

  GpioFunctionChk(chip_pin, DISABLE);
}

#endif // CONFIG_GPIO_EN
