#include "rtl8195am_uart.h"

u8 HalRuartGetChipVerRtl8195a( VOID )
{
  u8 chip_ver;

  chip_ver = ( HAL_READ32(SYSTEM_CTRL_BASE, 0x01F0) >> 4 ) & 0x0f;
  return chip_ver;
}

/**
 * Reset RUART Tx FIFO.
 *
 * Reset RUART Receiver and Rx FIFO wrapper function.
 * It will check LINE_STATUS_REG until reset action completion.
 *
 * @return BOOL
 */
HAL_STATUS HalRuartResetTxFifoRtl8195a(
IN VOID *Data  ///< RUART Adapter
  )
{
  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
  u8 UartIndex = pHalRuartAdapter->UartIndex;
  u32 rx_trigger_lv;
  volatile u32 RegValue;
  u32 timeout;

  // Backup the RX FIFO trigger Level setting
  rx_trigger_lv = HAL_RUART_READ32( UartIndex, RUART_FIFO_CTL_REG_OFF );
  rx_trigger_lv &= 0xC0;   // only keep the bit[7:6]

  /* Step 2: Enable clear_txfifo */
  RegValue = ( FIFO_CTL_DEFAULT_WITH_FIFO_DMA | RUART_FIFO_CTL_REG_CLEAR_TXFIFO ) & ( ~0xC0 );
  RegValue |= rx_trigger_lv;
  HAL_RUART_WRITE32( UartIndex, RUART_FIFO_CTL_REG_OFF, RegValue );

  // Wait TSR empty
  RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_STATUS_REG_OFF );
  timeout = 100;  // wait 10 ms
  while ( ( ( RegValue & RUART_LINE_STATUS_REG_TEMT ) == 0 ) && ( timeout > 0 ) )
  {
    HalDelayUs( 100 );
    RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_STATUS_REG_OFF );
    timeout--;
  }

  return HAL_OK;
}

// Reset RX FIFO
HAL_STATUS HalRuartResetRxFifoRtl8195a_Patch(
IN VOID *Data  ///< RUART Adapter
  )
{
  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
  u8 UartIndex;
  volatile u32 RegValue;
  u32 rx_trigger_lv;

  UartIndex = pHalRuartAdapter->UartIndex;

  /* Step 1: Enable Reset_rcv */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_STS_REG_OFF );
  RegValue |= RUART_STS_REG_RESET_RCV;
  HAL_RUART_WRITE32( UartIndex, RUART_STS_REG_OFF, RegValue );

  // Backup the RX FIFO trigger Level setting
  rx_trigger_lv = HAL_RUART_READ32( UartIndex, RUART_FIFO_CTL_REG_OFF );
  rx_trigger_lv &= 0xC0;   // only keep the bit[7:6]

  /* Step 2: Enable clear_rxfifo */
  RegValue = ( FIFO_CTL_DEFAULT_WITH_FIFO_DMA | RUART_FIFO_CTL_REG_CLEAR_RXFIFO ) & ( ~0xC0 );
  RegValue |= rx_trigger_lv;
  HAL_RUART_WRITE32( UartIndex, RUART_FIFO_CTL_REG_OFF, RegValue );

  /* Step 3: Disable Reset_rcv */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_STS_REG_OFF );
  RegValue &= ~( RUART_STS_REG_RESET_RCV );
  HAL_RUART_WRITE32( UartIndex, RUART_STS_REG_OFF, RegValue );

  return HAL_OK;
}

// Reset both TX and RX FIFO
HAL_STATUS HalRuartResetTRxFifoRtl8195a(
IN VOID *Data  ///< RUART Adapter
  )
{
  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
  u8 UartIndex;
  volatile u32 RegValue;
  u32 timeout;
  u32 rx_trigger_lv;

  UartIndex = pHalRuartAdapter->UartIndex;

  /* Step 1: Enable Reset_rcv */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_STS_REG_OFF );
  RegValue |= RUART_STS_REG_RESET_RCV;
  HAL_RUART_WRITE32( UartIndex, RUART_STS_REG_OFF, RegValue );

  // Backup the RX FIFO trigger Level setting
  rx_trigger_lv = HAL_RUART_READ32( UartIndex, RUART_FIFO_CTL_REG_OFF );
  rx_trigger_lv &= 0xC0;   // only keep the bit[7:6]

  /* Step 2: Enable clear_txfifo & clear_rxfifo */
  RegValue = ( FIFO_CTL_DEFAULT_WITH_FIFO_DMA | RUART_FIFO_CTL_REG_CLEAR_TXFIFO
    | RUART_FIFO_CTL_REG_CLEAR_RXFIFO ) & ( ~0xC0 );
  RegValue |= rx_trigger_lv;
  HAL_RUART_WRITE32( UartIndex, RUART_FIFO_CTL_REG_OFF, RegValue );

  // Wait THR & TSR empty
  RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_STATUS_REG_OFF );
  timeout = 100;  // wait 10 ms
  while ( ( ( RegValue & RUART_LINE_STATUS_REG_TEMT ) == 0 ) && ( timeout > 0 ) )
  {
    HalDelayUs( 100 );
    RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_STATUS_REG_OFF );
    timeout--;
  }

  /* Step 3: Disable Reset_rcv */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_STS_REG_OFF );
  RegValue &= ~( RUART_STS_REG_RESET_RCV );
  HAL_RUART_WRITE32( UartIndex, RUART_STS_REG_OFF, RegValue );

  return HAL_OK;
}

HAL_STATUS HalRuartGenBaudRateRtl8195a( IN RUART_SPEED_SETTING *pBaudSetting )
{
  u32 baud_rate;
  u32 min_divisor = 0;
  u32 min_err = 0xffffffff;
  u32 uart_ovsr;
  u32 uart_ovsr_mod;
  u32 min_uart_ovsr;  // ovsr with mini err
  u32 min_uart_ovsr_mod;
  u32 uart_clock;
  u32 divisor_temp;
  u32 max_jitter_temp;
  u32 err_temp;
  u32 uart_ovsr_target;
  u32 uart_ovsrs_actual;
  u32 ovsr_adj;
  u32 adj_bits;
  u32 div_res;
  u32 uart_ovsrs_actual_mod;

  baud_rate = pBaudSetting->BaudRate;
  if ( baud_rate >= 1000000 )
  {
    baud_rate /= 100;
    uart_clock = pBaudSetting->sclk;
  }
  else
  {
    baud_rate /= 2;
    uart_clock = pBaudSetting->sclk * 50;   // UART clock is 1/2 CPU clock
  }

  div_res = pBaudSetting->divisor_resolution;
  while ( ( min_err > pBaudSetting->max_err ) && ( div_res > 0 ) )
  {
    uart_ovsr = pBaudSetting->Ovsr_max;
    while ( uart_ovsr >= pBaudSetting->Ovsr_min )
    {
      divisor_temp = ( ( uart_clock / baud_rate ) / uart_ovsr );
      max_jitter_temp = 0;
      if ( divisor_temp > 0 )
      {
        max_jitter_temp = 100000 / uart_ovsr;
        if ( max_jitter_temp >= pBaudSetting->jitter_lim )
        {
          err_temp = 100;
        }
        else
        {
          err_temp = ( uart_clock / divisor_temp ) / ( ( uart_ovsr / 100 ) * 100 );
          if ( err_temp > baud_rate )
          {
            err_temp = ( err_temp - baud_rate ) * 1000 / baud_rate;
          }
          else
          {
            err_temp = ( baud_rate - err_temp ) * 1000 / baud_rate;
          }

          if ( err_temp < min_err )
          {
            min_err = err_temp;
            min_divisor = divisor_temp;
            min_uart_ovsr = uart_ovsr / 100;
            min_uart_ovsr_mod = uart_ovsr % 100;
          }
          else if ( err_temp == min_err )
          {
            uart_ovsr_mod = uart_ovsr % 100;
            // we perfer OVSR bigger and adj bits smaller
            if ( ( ( uart_ovsr / 100 ) >= min_uart_ovsr ) && ( uart_ovsr_mod < min_uart_ovsr_mod ) )
            {
              min_err = err_temp;
              min_divisor = divisor_temp;
              min_uart_ovsr = uart_ovsr / 100;
              min_uart_ovsr_mod = uart_ovsr_mod;
            }
          }
        }
      }
      uart_ovsr -= div_res;
    }
    div_res = div_res >> 1;
  }

  if ( min_divisor == 0 )
  {
    min_divisor = 1;
  }
  uart_ovsr_target = ( uart_clock / baud_rate ) / min_divisor;

  ovsr_adj = 0;
  adj_bits = 0;
  uart_ovsrs_actual = uart_ovsr_target / 100;
  uart_ovsrs_actual_mod = uart_ovsr_target % 100;
  if ( uart_ovsrs_actual_mod > 0 )
  {
    adj_bits = ( uart_ovsrs_actual_mod * pBaudSetting->Ovsr_adj_max_bits ) / 100;
    if ( ( uart_ovsrs_actual_mod - ( ( adj_bits * 100 ) / pBaudSetting->Ovsr_adj_max_bits ) ) > 4 )
    {
      adj_bits++;
    }

    if ( adj_bits > ( pBaudSetting->Ovsr_adj_max_bits - 1 ) )
    {
      DBG_UART_WARN( "HalRuartGenBaudRateRtl8195a: adj_bits=%d\r\n", adj_bits );
      adj_bits = pBaudSetting->Ovsr_adj_max_bits - 1;
    }
  }
  ovsr_adj = pBaudSetting->Ovsr_adj_map[ adj_bits ];
//    DBG_8195A("baud_rate=%d uart_clock=%d uart_ovsr_target=%d min_divisor=%d adj_bits=%d\r\n", baud_rate, uart_clock, uart_ovsr_target, min_divisor, adj_bits);

  pBaudSetting->Ovsr = uart_ovsrs_actual;
  pBaudSetting->Div = min_divisor;
  pBaudSetting->Ovsr_adj = ovsr_adj;
  pBaudSetting->Ovsr_adj_bits = adj_bits;

  DBG_UART_INFO( "HalRuartGenBaudRateRtl8195a: BaudRate=%d ovsr=%d divisor=%d ovsr_adj=0x%x\r\n",
    pBaudSetting->BaudRate, uart_ovsrs_actual, min_divisor, ovsr_adj );

  return HAL_OK;
}

HAL_STATUS HalRuartDumpBaudRateTableRtl8195a(
IN VOID *Data )
{
  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
  RUART_SPEED_SETTING RuartSpeedSetting;
  u32 Divisor;
  u32 Ovsr;
  u32 Ovsr_adj;
  u32 i;
  u32 j;
  u32 adj;

  RuartSpeedSetting.max_err = 3;
  RuartSpeedSetting.Ovsr_min = UART_OVSR_POOL_MIN;
  RuartSpeedSetting.Ovsr_max = UART_OVSR_POOL_MAX;
  RuartSpeedSetting.divisor_resolution = DIVISOR_RESOLUTION;
  RuartSpeedSetting.jitter_lim = JITTER_LIMIT;
  RuartSpeedSetting.sclk = UART_SCLK;

  if ( pHalRuartAdapter->pDefaultBaudRateTbl != NULL )
  {
    // for debugging
    DBG_8195A( "==== 10 Bit ====\r\n" );
    i = 0;
    RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_10;
    RuartSpeedSetting.Ovsr_adj_max_bits = 10;
    while ( pHalRuartAdapter->pDefaultBaudRateTbl[ i ] < 0xffffffff )
    {
      RuartSpeedSetting.BaudRate = pHalRuartAdapter->pDefaultBaudRateTbl[ i ];
      if ( HalRuartGenBaudRateRtl8195a( &RuartSpeedSetting ) == HAL_OK )
      {
        Divisor = RuartSpeedSetting.Div;
        Ovsr = RuartSpeedSetting.Ovsr;
        Ovsr_adj = RuartSpeedSetting.Ovsr_adj;
        adj = 0;
        for ( j = 0; j < 10; j++ )
        {
          if ( Ovsr_adj & ( 1 << j ) )
          {
            adj++;
          }
        }

        DBG_8195A( "BAUD: %d\t\tOVSR: %d\t\tDIV: %d\t\tADJ: 0x%04x\t%d\r\n",
          pHalRuartAdapter->pDefaultBaudRateTbl[ i ], Ovsr, Divisor, Ovsr_adj, adj );
      }
      i++;
    }

    DBG_8195A( "==== 9 Bit ====\r\n" );
    i = 0;
    RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_9;
    RuartSpeedSetting.Ovsr_adj_max_bits = 9;
    while ( pHalRuartAdapter->pDefaultBaudRateTbl[ i ] < 0xffffffff )
    {
      RuartSpeedSetting.BaudRate = pHalRuartAdapter->pDefaultBaudRateTbl[ i ];
      if ( HalRuartGenBaudRateRtl8195a( &RuartSpeedSetting ) == HAL_OK )
      {
        Divisor = RuartSpeedSetting.Div;
        Ovsr = RuartSpeedSetting.Ovsr;
        Ovsr_adj = RuartSpeedSetting.Ovsr_adj;
        adj = 0;
        for ( j = 0; j < 10; j++ )
        {
          if ( Ovsr_adj & ( 1 << j ) )
          {
            adj++;
          }
        }

        DBG_8195A( "BAUD: %d\t\tOVSR: %d\t\tDIV: %d\t\tADJ: 0x%04x\t%d\r\n",
          pHalRuartAdapter->pDefaultBaudRateTbl[ i ], Ovsr, Divisor, Ovsr_adj, adj );
      }
      i++;
    }

    DBG_8195A( "==== 8 Bit ====\r\n" );
    i = 0;
    RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_8;
    RuartSpeedSetting.Ovsr_adj_max_bits = 8;
    while ( pHalRuartAdapter->pDefaultBaudRateTbl[ i ] < 0xffffffff )
    {
      RuartSpeedSetting.BaudRate = pHalRuartAdapter->pDefaultBaudRateTbl[ i ];
      if ( HalRuartGenBaudRateRtl8195a( &RuartSpeedSetting ) == HAL_OK )
      {
        Divisor = RuartSpeedSetting.Div;
        Ovsr = RuartSpeedSetting.Ovsr;
        Ovsr_adj = RuartSpeedSetting.Ovsr_adj;
        adj = 0;
        for ( j = 0; j < 10; j++ )
        {
          if ( Ovsr_adj & ( 1 << j ) )
          {
            adj++;
          }
        }

        DBG_8195A( "BAUD: %d\t\tOVSR: %d\t\tDIV: %d\t\tADJ: 0x%04x\t%d\r\n",
          pHalRuartAdapter->pDefaultBaudRateTbl[ i ], Ovsr, Divisor, Ovsr_adj, adj );
      }
      i++;
    }
  }
  return HAL_OK;
}

HAL_STATUS HalRuartSetBaudRateRtl8195a(
IN VOID *Data )
{
  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
  RUART_SPEED_SETTING RuartSpeedSetting;
  u32 RegValue;
  u32 Dll, Dlm;
  u8 UartIndex;
  u32 Divisor;
  u32 Ovsr;
  u32 Ovsr_adj;
  u32 i;
  u32 cpu_clk;
  u32 baud_rate_temp;
  u32 err;
  u8 is_defined_baud;
  u8 word_bits;
  u8 adj_bits;

#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)
  u8 chip_ver;

  // get chip version
  chip_ver = HalRuartGetChipVerRtl8195a();
#endif

  if ( pHalRuartAdapter->WordLen == RUART_WLS_8BITS )
  {
    word_bits = 8 + 1;    // 1 start bit + 8 data bit
  }
  else
  {
    word_bits = 7 + 1;
  }

  if ( pHalRuartAdapter->Parity == RUART_PARITY_ENABLE )
  {
    word_bits++;        // 1 parity bit
  }

  is_defined_baud = 0;

  if ( pHalRuartAdapter->pDefaultBaudRateTbl != NULL )
  {
    i = 0;
    while ( pHalRuartAdapter->pDefaultBaudRateTbl[ i ] < 0xffffffff )
    {
      if ( pHalRuartAdapter->pDefaultBaudRateTbl[ i ] == pHalRuartAdapter->BaudRate )
      {
        Divisor = pHalRuartAdapter->pDefaultDivTbl[ i ];
        Ovsr = pHalRuartAdapter->pDefaultOvsrRTbl[ i ];
        switch ( word_bits )
        {
          case 9:
            adj_bits = pHalRuartAdapter->pDefOvsrAdjBitTbl_9[ i ];
            Ovsr_adj = pHalRuartAdapter->pDefOvsrAdjTbl_9[ adj_bits ];
            break;
          case 10:
            adj_bits = pHalRuartAdapter->pDefOvsrAdjBitTbl_10[ i ];
            Ovsr_adj = pHalRuartAdapter->pDefOvsrAdjTbl_10[ adj_bits ];
            break;
          case 8:
            adj_bits = pHalRuartAdapter->pDefOvsrAdjBitTbl_8[ i ];
            Ovsr_adj = pHalRuartAdapter->pDefOvsrAdjTbl_8[ adj_bits ];
            break;

          default:
            adj_bits = pHalRuartAdapter->pDefOvsrAdjBitTbl_9[ i ];
            Ovsr_adj = pHalRuartAdapter->pDefOvsrAdjTbl_9[ adj_bits ];
            break;
        }
        // Verify again
        cpu_clk = UART_SCLK;
        baud_rate_temp = cpu_clk / Ovsr / Divisor;
        if ( baud_rate_temp > pHalRuartAdapter->BaudRate )
        {
          err = baud_rate_temp - pHalRuartAdapter->BaudRate;
        }
        else
        {
          err = pHalRuartAdapter->BaudRate - baud_rate_temp;
        }

        // Tolerance is 10%
        // If the err is too big, it may caused by "the baud rate table is not for this CPU clock"
        if ( err < ( pHalRuartAdapter->BaudRate / 10 ) )
        {
          is_defined_baud = 1;
        }
        break;  // break the while loop
      }
      else
      {
        i++;
      }
    }
  }

  if ( is_defined_baud == 0 )
  {

    switch ( word_bits )
    {
      case 9:
        RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_9;
        break;

      case 10:
        RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_10;
        break;

      case 8:
        RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_8;
        break;

      default:
        word_bits = 9;
        RuartSpeedSetting.Ovsr_adj_map = pHalRuartAdapter->pDefOvsrAdjTbl_9;
        break;
    }
    DBG_UART_INFO( "BaudRate(%d) not in the Lookup table \n", pHalRuartAdapter->BaudRate );
    RuartSpeedSetting.Ovsr_adj_max_bits = word_bits;
    RuartSpeedSetting.max_err = 3;
    RuartSpeedSetting.Ovsr_min = UART_OVSR_POOL_MIN;
    RuartSpeedSetting.Ovsr_max = UART_OVSR_POOL_MAX;
    RuartSpeedSetting.divisor_resolution = DIVISOR_RESOLUTION;
    RuartSpeedSetting.jitter_lim = JITTER_LIMIT;
    RuartSpeedSetting.sclk = UART_SCLK;
    RuartSpeedSetting.BaudRate = pHalRuartAdapter->BaudRate;
#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)
    if (chip_ver < 2)
    {
      // A or B Cut
      // workround: +2% bias
      RuartSpeedSetting.BaudRate = (pHalRuartAdapter->BaudRate * 102)/100;
    }
#endif
    if ( HalRuartGenBaudRateRtl8195a( &RuartSpeedSetting ) == HAL_OK )
    {
      Divisor = RuartSpeedSetting.Div;
      Ovsr = RuartSpeedSetting.Ovsr;
      Ovsr_adj = RuartSpeedSetting.Ovsr_adj;
    }
    else
    {
      DBG_UART_ERR( "Invalid BaudRate(%d), Force Baud Rateit as 9600\n",
        pHalRuartAdapter->BaudRate );
      Divisor = 434;
      Ovsr = 20;
      Ovsr_adj = 0;
    }
  }

  UartIndex = pHalRuartAdapter->UartIndex;

  DBG_UART_INFO( "HalRuartSetBaudRateRtl8195a: BaudRate:%d Divisor:%d Ovsr:%d Ovsr_ADj:0x%x\n",
    pHalRuartAdapter->BaudRate, Divisor, Ovsr, Ovsr_adj );

  Dll = Divisor & 0xFF;
  Dlm = ( Divisor & 0xFF00 ) >> 8;

  /* Set DLAB bit to 1 to access DLL/DLM */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF );
  RegValue |= RUART_LINE_CTL_REG_DLAB_ENABLE;
  HAL_RUART_WRITE32( UartIndex, RUART_LINE_CTL_REG_OFF, RegValue );

  HAL_RUART_WRITE32( UartIndex, RUART_DLL_OFF, Dll );
  HAL_RUART_WRITE32( UartIndex, RUART_DLM_OFF, Dlm );

  /**
   * Clean Rx break signal interrupt status at initial stage.
   */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_SCRATCH_PAD_REG_OFF );
  RegValue |= RUART_SP_REG_RXBREAK_INT_STATUS;
  HAL_RUART_WRITE32( UartIndex, RUART_SCRATCH_PAD_REG_OFF, RegValue );

  /* Set OVSR(xfactor) */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_STS_REG_OFF );
  RegValue &= ~( RUART_STS_REG_XFACTOR );
  RegValue |= ( ( ( Ovsr - 5 ) << 4 ) & RUART_STS_REG_XFACTOR );
  HAL_RUART_WRITE32( UartIndex, RUART_STS_REG_OFF, RegValue );

  /* Set OVSR_ADJ[10:0] (xfactor_adj[26:16]) */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_SCRATCH_PAD_REG_OFF );
  RegValue &= ~( RUART_SP_REG_XFACTOR_ADJ );
  RegValue |= ( ( Ovsr_adj << 16 ) & RUART_SP_REG_XFACTOR_ADJ );
  HAL_RUART_WRITE32( UartIndex, RUART_SCRATCH_PAD_REG_OFF, RegValue );

  /* clear DLAB bit */
  RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF );
  RegValue &= ~( RUART_LINE_CTL_REG_DLAB_ENABLE );
  HAL_RUART_WRITE32( UartIndex, RUART_LINE_CTL_REG_OFF, RegValue );
  pHalRuartAdapter->BaudRateUsing = pHalRuartAdapter->BaudRate;
  pHalRuartAdapter->WordLenUsing = pHalRuartAdapter->WordLen;
  pHalRuartAdapter->ParityUsing = pHalRuartAdapter->Parity;

  return HAL_OK;
}

HAL_STATUS HalRuartInitRtl8195a_Patch(
IN VOID *Data  ///< RUART Adapter
  )
{
  /* DBG_ENTRANCE; */
  u32 RegValue;
  u8 UartIndex;
  u8 PinmuxSelect;

  PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;

  UartIndex = pHalRuartAdapter->UartIndex;
  PinmuxSelect = pHalRuartAdapter->PinmuxSelect;

  if ( UartIndex > 2 )
  {
    DBG_UART_ERR(ANSI_COLOR_MAGENTA"HalRuartInitRtl8195a: Invalid UART Index\n"ANSI_COLOR_RESET);
    return HAL_ERR_PARA;
  }

  DBG_UART_INFO( "HalRuartInitRtl8195a: [UART %d] PinSel=%d\n", UartIndex, PinmuxSelect );
  if ( ( PinmuxSelect == RUART0_MUX_TO_GPIOE ) && ( ( UartIndex == 0 ) || ( UartIndex == 1 ) ) )
  {
  DBG_UART_WARN(ANSI_COLOR_MAGENTA"UART Pin may conflict with JTAG\r\n"ANSI_COLOR_RESET);
}

// switch Pin from EEPROM to UART0
if ( ( PinmuxSelect == RUART0_MUX_TO_GPIOC ) && ( UartIndex == 0 ) )
{
  RegValue = HAL_READ32( SYSTEM_CTRL_BASE, 0xa4 );
  if ( RegValue & 0x10 )
  {
    DBG_UART_WARN( "UART Pin may conflict with EEPROM\n" );
//          HAL_WRITE32(SYSTEM_CTRL_BASE, 0xa4, (RegValue & (~0x10)));
  }
}

switch ( UartIndex )
{
  case 0:
    /* UART 0 */
    ACTCK_UART0_CCTRL( ON );
    SLPCK_UART0_CCTRL( ON );
    PinCtrl( UART0, PinmuxSelect, ON );
    UART0_FCTRL( ON );
    UART0_BD_FCTRL( ON );
    break;

  case 1:
    /* UART 1 */
    ACTCK_UART1_CCTRL( ON );
    SLPCK_UART1_CCTRL( ON );
    PinCtrl( UART1, PinmuxSelect, ON );
    UART1_FCTRL( ON );
    UART1_BD_FCTRL( ON );
    break;

  case 2:
    /* UART 1 */
    ACTCK_UART2_CCTRL( ON );
    SLPCK_UART2_CCTRL( ON );
    PinCtrl( UART2, PinmuxSelect, ON );
    UART2_FCTRL( ON );
    UART2_BD_FCTRL( ON );
    break;

  default:
    DBG_UART_ERR( "Invalid UART Index(%d)\n", UartIndex );
    return HAL_ERR_PARA;
}

/* Reset RX FIFO */
HalRuartResetRxFifoRtl8195a( Data );
DBG_UART_INFO(ANSI_COLOR_CYAN"HAL UART Init[UART %d]\n"ANSI_COLOR_RESET, UartIndex);

/* Disable all interrupts */
HAL_RUART_WRITE32( UartIndex, RUART_INTERRUPT_EN_REG_OFF, 0x00 );

/* Set Baudrate Division */
if ( ( pHalRuartAdapter->BaudRateUsing != pHalRuartAdapter->BaudRate )
  || ( pHalRuartAdapter->WordLenUsing != pHalRuartAdapter->WordLen )
  || ( pHalRuartAdapter->ParityUsing != pHalRuartAdapter->Parity ) )
{
  HalRuartSetBaudRateRtl8195a( pHalRuartAdapter );
}

/**
 * Clean Rx break signal interrupt status at initial stage.
 */
RegValue = HAL_RUART_READ32( UartIndex, RUART_SCRATCH_PAD_REG_OFF );
RegValue |= RUART_SP_REG_RXBREAK_INT_STATUS;
HAL_RUART_WRITE32( UartIndex, RUART_SCRATCH_PAD_REG_OFF, RegValue );

//    DBG_UART_INFO("[R] UART%d INT_EN(0x04) = %x\n", UartIndex, pHalRuartAdapter->Interrupts);
RegValue = ( ( pHalRuartAdapter->Interrupts ) & 0xFF );
HAL_RUART_WRITE32( UartIndex, RUART_INTERRUPT_EN_REG_OFF, RegValue );
//    DBG_UART_INFO("[W] UART%d INT_EN(0x04) = %x\n", UartIndex, RegValue);

/* Configure FlowControl */
if ( pHalRuartAdapter->FlowControl == AUTOFLOW_ENABLE )
{
  RegValue = HAL_RUART_READ32( UartIndex, RUART_MODEM_CTL_REG_OFF );
  RegValue |= RUART_MCL_AUTOFLOW_ENABLE;
  HAL_RUART_WRITE32( UartIndex, RUART_MODEM_CTL_REG_OFF, RegValue );
}

/* RUART DMA Initialization */
//    HalRuartDmaInitRtl8195a(pHalRuartAdapter);
DBG_UART_INFO( "[R] UART%d LCR(0x%02X): %X\n", UartIndex, RUART_LINE_CTL_REG_OFF,
  HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF ) );
RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF );

/* PARITY CONTROL */
RegValue &= BIT_CLR_LCR_WLS;
RegValue |= BIT_LCR_WLS( pHalRuartAdapter->WordLen );

RegValue &= BIT_INVC_LCR_STB_EN;
RegValue |= BIT_LCR_STB_EN( pHalRuartAdapter->StopBit );

RegValue &= BIT_INVC_LCR_PARITY_EN;
RegValue |= BIT_LCR_PARITY_EN( pHalRuartAdapter->Parity );

/* PARITY TYPE SELECT */
RegValue &= BIT_INVC_LCR_PARITY_TYPE;
RegValue |= BIT_LCR_PARITY_TYPE( pHalRuartAdapter->ParityType );

/* STICK PARITY CONTROL */
RegValue &= BIT_INVC_LCR_STICK_PARITY_EN;
RegValue |= BIT_LCR_STICK_PARITY_EN( pHalRuartAdapter->StickParity );

HAL_RUART_WRITE32( UartIndex, RUART_LINE_CTL_REG_OFF, RegValue );
DBG_UART_INFO( "[W] UART%d LCR(0x%02X): %X\n", UartIndex, RUART_LINE_CTL_REG_OFF,
  HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF ) );

/* Need to assert RTS during initial stage. */
if ( pHalRuartAdapter->FlowControl == AUTOFLOW_ENABLE )
{
  HalRuartRTSCtrlRtl8195a( Data, 1 );
}
pHalRuartAdapter->State = HAL_UART_STATE_READY;

return HAL_OK;
}

HAL_STATUS HalRuartEnableRtl8195a(
IN VOID *Data )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
u8 UartIndex;

// Enable IP Clock
UartIndex = pHalRuartAdapter->UartIndex;
switch ( UartIndex )
{
  case 0:
    /* UART 0 */
    ACTCK_UART0_CCTRL( ON );
    SLPCK_UART0_CCTRL( ON );
    break;

  case 1:
    /* UART 1 */
    ACTCK_UART1_CCTRL( ON );
    SLPCK_UART1_CCTRL( ON );
    break;

  case 2:
    /* UART 1 */
    ACTCK_UART2_CCTRL( ON );
    SLPCK_UART2_CCTRL( ON );
    break;

  default:
    DBG_UART_ERR( "Invalid UART Index(%d)\n", UartIndex );
    return HAL_ERR_PARA;
}

return HAL_OK;
}

HAL_STATUS HalRuartDisableRtl8195a(
IN VOID *Data )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
u8 UartIndex;

// Gate IP Clock
UartIndex = pHalRuartAdapter->UartIndex;
switch ( UartIndex )
{
  case 0:
    /* UART 0 */
    ACTCK_UART0_CCTRL( OFF );
    SLPCK_UART0_CCTRL( OFF );
    break;

  case 1:
    /* UART 1 */
    ACTCK_UART1_CCTRL( OFF );
    SLPCK_UART1_CCTRL( OFF );
    break;

  case 2:
    /* UART 1 */
    ACTCK_UART2_CCTRL( OFF );
    SLPCK_UART2_CCTRL( OFF );
    break;

  default:
    DBG_UART_ERR( "Invalid UART Index(%d)\n", UartIndex );
    return HAL_ERR_PARA;
}

return HAL_OK;
}

HAL_STATUS HalRuartFlowCtrlRtl8195a(
IN VOID *Data )
{
u32 UartIndex;
u32 RegValue;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;

UartIndex = pHalRuartAdapter->UartIndex;

RegValue = HAL_RUART_READ32( UartIndex, RUART_MODEM_CTL_REG_OFF );
if ( !pHalRuartAdapter->FlowControl )
{
  // No Auto Flow Control: no flow control or flow controled by software
  RegValue &= ~( RUART_MCL_AUTOFLOW_ENABLE );
}
else
{
  RegValue |= RUART_MCL_AUTOFLOW_ENABLE;
}
HAL_RUART_WRITE32( UartIndex, RUART_MODEM_CTL_REG_OFF, RegValue );

return HAL_OK;
}

u32 _UartTxDmaIrqHandle_Patch(
IN VOID *Data )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;
u8 IsrTypeMap;

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

// Clear Pending ISR
IsrTypeMap = pHalGdmaOp->HalGdmaChIsrClean( (VOID*) pHalGdmaAdapter );

if ( IsrTypeMap & BlockType )
{
  pHalGdmaAdapter->MuliBlockCunt++;
}

if ( pHalGdmaAdapter->MuliBlockCunt == pHalGdmaAdapter->MaxMuliBlock )
{
  // Clean Auto Reload Bit
  pHalGdmaOp->HalGdmaChCleanAutoDst( (VOID*) pHalGdmaAdapter );
  pHalGdmaOp->HalGdmaChDis( (VOID*) ( pHalGdmaAdapter ) );

  if ( ( HAL_UART_STATE_BUSY_TX == pHalRuartAdapter->State )
    || ( HAL_UART_STATE_BUSY_TX_RX == pHalRuartAdapter->State ) )
  {
    if ( pHalRuartAdapter->State == HAL_UART_STATE_BUSY_TX )
    {
      pHalRuartAdapter->State = HAL_UART_STATE_READY;
    }
    else
    {
      pHalRuartAdapter->State = HAL_UART_STATE_BUSY_RX;
    }

    // Call user TX complete callback
    if ( NULL != pHalRuartAdapter->TxCompCallback )
    {
      pHalRuartAdapter->TxCompCallback( pHalRuartAdapter->TxCompCbPara );
    }
  }
}
return 0;
}

u32 _UartRxDmaIrqHandle_Patch(
IN VOID *Data )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;
u8 IsrTypeMap;
u8 LineStatus;
u8 UartIndex;

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

// Clear Pending ISR
IsrTypeMap = pHalGdmaOp->HalGdmaChIsrClean( (VOID*) pHalGdmaAdapter );

if ( IsrTypeMap & BlockType )
{
  pHalGdmaAdapter->MuliBlockCunt++;
}

if ( ( pHalGdmaAdapter->MuliBlockCunt == pHalGdmaAdapter->MaxMuliBlock ) )
{
  // Clean Auto Reload Bit
  pHalGdmaOp->HalGdmaChCleanAutoSrc( (VOID*) pHalGdmaAdapter );
  pHalGdmaOp->HalGdmaChDis( (VOID*) ( pHalGdmaAdapter ) );

  // Check the Line Status
  UartIndex = pHalRuartAdapter->UartIndex;
  LineStatus = (u8) HAL_RUART_READ32( UartIndex, RUART_LINE_STATUS_REG_OFF );
  pHalRuartAdapter->Status |= LineStatus & RUART_LINE_STATUS_ERR;

  if ( pHalRuartAdapter->State == HAL_UART_STATE_BUSY_RX )
  {
    pHalRuartAdapter->State = HAL_UART_STATE_READY;
  }
  else
  {
    pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX;
  }

  // Call User Rx complete callback
  if ( pHalRuartAdapter->RxCompCallback != NULL )
  {
    pHalRuartAdapter->RxCompCallback( pHalRuartAdapter->RxCompCbPara );
  }
}
return 0;
}

/**
 * RUART send a data buffer by DMA(non-block) mode.
 *
 * RUART send data.
 *
 * @return VOID
 */
HAL_STATUS HalRuartDmaSendRtl8195a_Patch(
IN VOID *Data,      // PHAL_RUART_ADAPTER
IN u8 *pTxData,     // the Buffer to be send
IN u32 Length      // the length of data to be send
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
//    u8 UartIndex = pHalRuartAdapter->UartIndex;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;
HAL_UART_State State;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_READY ) && ( State != HAL_UART_STATE_BUSY_RX ) )
{
  DBG_UART_WARN( "HalRuartDmaSendRtl8195a: on Busy, State=%d\n", State );
  return HAL_BUSY;
}

if ( ( pTxData == NULL ) || ( Length == 0 ) )
{
  pHalRuartAdapter->Status = HAL_UART_STATUS_ERR_PARA;
  DBG_UART_ERR( "HalRuartDmaSendRtl8195a: Err: pTxData=0x%x,  Length=%d\n", pTxData, Length );
  return HAL_ERR_PARA;
}

if ( State == HAL_UART_STATE_READY )
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX_RX;
}

pHalRuartAdapter->Status = HAL_UART_STATUS_OK;
pHalRuartAdapter->pTxBuf = pTxData;
pHalRuartAdapter->TxCount = Length;

// Enable GDMA for TX
pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

if ( ( ( pHalRuartAdapter->TxCount & 0x03 ) == 0 )
  && ( ( ( u32 )( pHalRuartAdapter->pTxBuf ) & 0x03 ) == 0 ) )
{
  // 4-bytes aligned, move 4 bytes each transfer
  pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeOne;
  pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
  pHalGdmaAdapter->GdmaCtl.BlockSize = pHalRuartAdapter->TxCount >> 2;
}
else
{
  // move 1 byte each transfer
  pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeFour;
  pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
  pHalGdmaAdapter->GdmaCtl.BlockSize = pHalRuartAdapter->TxCount;
}

if ( pHalGdmaAdapter->GdmaCtl.BlockSize > 4095 )
{
  // over Maximum block size 4096
  return HAL_ERR_PARA;
}

pHalGdmaAdapter->MuliBlockCunt = 0;
pHalGdmaAdapter->MaxMuliBlock = 1;
pHalGdmaAdapter->ChSar = ( u32 )( pHalRuartAdapter->pTxBuf );

pHalGdmaAdapter->Rsvd4to7 = 0;
pHalGdmaAdapter->Llpctrl = 0;
pHalGdmaAdapter->GdmaCtl.LlpSrcEn = 0;

pHalGdmaOp->HalGdmaOnOff( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChIsrEnAndDis( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChSeting( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChEn( (VOID*) ( pHalGdmaAdapter ) );

return HAL_OK;
}

/**
 * RUART Receive data by Interrupt (non-block) mode.
 *
 * RUART Receive data.
 * Receive one byte each time.
 *
 * @return u8
 */
HAL_STATUS HalRuartDmaRecvRtl8195a_Patch(
IN VOID *Data,  ///< RUART Adapter
IN u8 *pRxData,  ///< Rx buffer
IN u32 Length      // buffer length
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
HAL_UART_State State;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_READY ) && ( State != HAL_UART_STATE_BUSY_TX ) )
{
  DBG_UART_WARN( "%s: on Busy, State=%d\n", State );
  return HAL_BUSY;
}

if ( ( pRxData == NULL ) || ( Length == 0 ) )
{
  pHalRuartAdapter->Status = HAL_UART_STATUS_ERR_PARA;
  DBG_UART_ERR( "HalRuartDmaRecvRtl8195a: Err: pTxData=0x%x,  Length=%d\n", pRxData, Length );
  return HAL_ERR_PARA;
}

if ( State == HAL_UART_STATE_READY )
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_RX;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX_RX;
}

pHalRuartAdapter->Status = HAL_UART_STATUS_OK;
pHalRuartAdapter->pRxBuf = pRxData;
pHalRuartAdapter->RxCount = Length;

// Enable GDMA for RX
pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

if ( ( ( u32 )( pHalRuartAdapter->pRxBuf ) & 0x03 ) == 0 )
{
  // 4-bytes aligned, move 4 bytes each DMA transaction
  pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeOne;
  pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
}
else
{
  // move 1 byte each DMA transaction
  pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeFour;
  pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
}
pHalGdmaAdapter->GdmaCtl.BlockSize = pHalRuartAdapter->RxCount;
if ( pHalGdmaAdapter->GdmaCtl.BlockSize > 4095 )
{
  // over Maximum block size 4096
  DBG_UART_ERR( "HalRuartDmaRecvRtl8195a: BlockSize too big(%d)\n",
    pHalGdmaAdapter->GdmaCtl.BlockSize );
  return HAL_ERR_PARA;
}

pHalGdmaAdapter->MuliBlockCunt = 0;
pHalGdmaAdapter->MaxMuliBlock = 1;
pHalGdmaAdapter->ChDar = ( u32 )( pHalRuartAdapter->pRxBuf );

pHalGdmaAdapter->Rsvd4to7 = 0;
pHalGdmaAdapter->Llpctrl = 0;
pHalGdmaAdapter->GdmaCtl.LlpSrcEn = 0;

pHalGdmaOp->HalGdmaOnOff( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChIsrEnAndDis( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChSeting( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChEn( (VOID*) ( pHalGdmaAdapter ) );

return HAL_OK;
}

/**
 * RUART send a data buffer by Multi-Block DMA(non-block) mode.
 *
 * RUART send data.
 *
 * @return VOID
 */
HAL_STATUS HalRuartMultiBlkDmaSendRtl8195a(
IN VOID *Data,      // PHAL_RUART_ADAPTER
IN u8 *pTxData,     // the Buffer to be send
IN u32 Length      // the length of data to be send
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;
HAL_UART_State State;
UART_DMA_MULTIBLK *pDmaBlkList;
u32 BlockBytes;
u32 TotalTr;
u32 SrcAddr;
u8 i;
u8 BlkNum;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_READY ) && ( State != HAL_UART_STATE_BUSY_RX ) )
{
  DBG_UART_WARN( "HalRuartDmaSendRtl8195a: on Busy, State=%d\n", State );
  return HAL_BUSY;
}

if ( ( pTxData == NULL ) || ( Length == 0 ) )
{
  pHalRuartAdapter->Status = HAL_UART_STATUS_ERR_PARA;
  DBG_UART_ERR( "HalRuartMultiBlkDmaSendRtl8195a: Err: pTxData=0x%x,  Length=%d\n", pTxData,
    Length );
  return HAL_ERR_PARA;
}

if ( State == HAL_UART_STATE_READY )
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX_RX;
}

pHalRuartAdapter->Status = HAL_UART_STATUS_OK;
pHalRuartAdapter->pTxBuf = pTxData;
pHalRuartAdapter->TxCount = Length;

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
pDmaBlkList = pUartGdmaConfig->pTxDmaBlkList;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

if ( ( ( pHalRuartAdapter->TxCount & 0x03 ) == 0 )
  && ( ( ( u32 )( pHalRuartAdapter->pTxBuf ) & 0x03 ) == 0 ) )
{
  // 4-bytes aligned, move 4 bytes each transfer
  pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeOne;
  pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthFourBytes;
  TotalTr = Length >> 2;     // 4-bytes each write
  BlockBytes = UART_DMA_BLOCK_SIZE << 2; // a block can transfer BlockSize*4 bytes
}
else
{
  // move 1 byte each transfer
  pHalGdmaAdapter->GdmaCtl.SrcMsize = MsizeFour;
  pHalGdmaAdapter->GdmaCtl.SrcTrWidth = TrWidthOneByte;
  TotalTr = Length;     // 1-byte each write
  BlockBytes = UART_DMA_BLOCK_SIZE;
}

BlkNum = 0;
SrcAddr = (u32) pTxData;
for ( i = 0; i < UART_DMA_MBLK_NUM; i++ )
{
  pDmaBlkList->GdmaChLli[ i ].Sarx = SrcAddr;
  pDmaBlkList->GdmaChLli[ i ].Darx = ( u32 )( pHalGdmaAdapter->ChDar );
  pDmaBlkList->Lli[ i ].pLliEle = (GDMA_CH_LLI_ELE*) &( pDmaBlkList->GdmaChLli[ i ] );
  SrcAddr += BlockBytes;
  BlkNum++;
  if ( TotalTr >= UART_DMA_BLOCK_SIZE )
  {
    pDmaBlkList->Lli[ i ].pNextLli = &( pDmaBlkList->Lli[ i + 1 ] );
    pDmaBlkList->BlockSizeList[ i ].pNextBlockSiz = &( pDmaBlkList->BlockSizeList[ i + 1 ] );
    pDmaBlkList->BlockSizeList[ i ].BlockSize = UART_DMA_BLOCK_SIZE;
    TotalTr -= UART_DMA_BLOCK_SIZE;
  }
  else
  {
    pDmaBlkList->Lli[ i ].pNextLli = (struct GDMA_CH_LLI*) NULL;
    pDmaBlkList->BlockSizeList[ i ].pNextBlockSiz = (struct BLOCK_SIZE_LIST*) NULL;
    pDmaBlkList->BlockSizeList[ i ].BlockSize = TotalTr;
    TotalTr = 0;
    break;
  }
}

if ( TotalTr > 0 )
{
  // Cannot transfer all data in multiple-block DMA
  // Try to increase block number, but maximum block number is 16
  pDmaBlkList->Lli[ UART_DMA_MBLK_NUM - 1 ].pNextLli = (struct GDMA_CH_LLI*) NULL;
  pDmaBlkList->BlockSizeList[ UART_DMA_MBLK_NUM - 1 ].pNextBlockSiz =
    (struct BLOCK_SIZE_LIST*) NULL;
  DBG_UART_ERR( "HalRuartMultiBlkDmaSendRtl8195a: Cannot Transfer all data\n" );
}

pHalGdmaAdapter->MuliBlockCunt = 0;
pHalGdmaAdapter->MaxMuliBlock = BlkNum;
pHalGdmaAdapter->Rsvd4to7 = 1;
pHalGdmaAdapter->Llpctrl = 1;
pHalGdmaAdapter->GdmaCtl.LlpSrcEn = 1;

pHalGdmaOp->HalGdmaOnOff( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChIsrEnAndDis( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChBlockSeting( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChEn( (VOID*) ( pHalGdmaAdapter ) );

return HAL_OK;

}

/**
 * RUART Receive data by Multi-Block DMA (non-block) mode.
 *
 * RUART Receive data.
 *
 * @return u8
 */
HAL_STATUS HalRuartMultiBlkDmaRecvRtl8195a(
IN VOID *Data,  ///< RUART Adapter
IN u8 *pRxData,  ///< Rx buffer
IN u32 Length      // buffer length
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
HAL_UART_State State;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
PHAL_GDMA_OP pHalGdmaOp;
UART_DMA_MULTIBLK *pDmaBlkList;
u32 TotalTr;
u32 DstAddr;
u8 i;
u8 BlkNum;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_READY ) && ( State != HAL_UART_STATE_BUSY_TX ) )
{
  DBG_UART_WARN( "HalRuartMultiBlkDmaRecvRtl8195a: on Busy, State=%d\n", State );
  return HAL_BUSY;
}

if ( ( pRxData == NULL ) || ( Length == 0 ) )
{
  pHalRuartAdapter->Status = HAL_UART_STATUS_ERR_PARA;
  DBG_UART_ERR( "HalRuartDmaRecvRtl8195a: Err: pTxData=0x%x,  Length=%d\n", pRxData, Length );
  return HAL_ERR_PARA;
}

if ( State == HAL_UART_STATE_READY )
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_RX;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX_RX;
}

pHalRuartAdapter->Status = HAL_UART_STATUS_OK;
pHalRuartAdapter->pRxBuf = pRxData;
pHalRuartAdapter->RxCount = Length;

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
pDmaBlkList = pUartGdmaConfig->pRxDmaBlkList;
pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

if ( ( ( u32 )( pHalRuartAdapter->pRxBuf ) & 0x03 ) == 0 )
{
  // 4-bytes aligned, move 4 bytes each DMA transaction
  pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeOne;
  pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthFourBytes;
}
else
{
  // move 1 byte each DMA transaction
  pHalGdmaAdapter->GdmaCtl.DestMsize = MsizeFour;
  pHalGdmaAdapter->GdmaCtl.DstTrWidth = TrWidthOneByte;
}

TotalTr = Length;     // 1-byte each write, total transaction = data lenth
BlkNum = 0;
DstAddr = (u32) pRxData;
for ( i = 0; i < UART_DMA_MBLK_NUM; i++ )
{
  pDmaBlkList->GdmaChLli[ i ].Sarx = ( u32 )( pHalGdmaAdapter->ChSar );
  pDmaBlkList->GdmaChLli[ i ].Darx = DstAddr;
  pDmaBlkList->Lli[ i ].pLliEle = (GDMA_CH_LLI_ELE*) &( pDmaBlkList->GdmaChLli[ i ] );
  DstAddr += UART_DMA_BLOCK_SIZE;
  BlkNum++;
  if ( TotalTr >= UART_DMA_BLOCK_SIZE )
  {
    pDmaBlkList->Lli[ i ].pNextLli = &( pDmaBlkList->Lli[ i + 1 ] );
    pDmaBlkList->BlockSizeList[ i ].pNextBlockSiz = &( pDmaBlkList->BlockSizeList[ i + 1 ] );
    pDmaBlkList->BlockSizeList[ i ].BlockSize = UART_DMA_BLOCK_SIZE;
    TotalTr -= UART_DMA_BLOCK_SIZE;
  }
  else
  {
    pDmaBlkList->Lli[ i ].pNextLli = (struct GDMA_CH_LLI*) NULL;
    pDmaBlkList->BlockSizeList[ i ].pNextBlockSiz = (struct BLOCK_SIZE_LIST*) NULL;
    pDmaBlkList->BlockSizeList[ i ].BlockSize = TotalTr;
    TotalTr = 0;
    break;
  }
}

if ( TotalTr > 0 )
{
  // Cannot transfer all data in multiple-block DMA
  // Try to increase block number, but maximum block number is 16
  pDmaBlkList->Lli[ UART_DMA_MBLK_NUM - 1 ].pNextLli = (struct GDMA_CH_LLI*) NULL;
  pDmaBlkList->BlockSizeList[ UART_DMA_MBLK_NUM - 1 ].pNextBlockSiz =
    (struct BLOCK_SIZE_LIST*) NULL;
  DBG_UART_ERR( "HalRuartMultiBlkDmaRecvRtl8195a: Cannot Transfer all data\n" );
}

pHalGdmaAdapter->MuliBlockCunt = 0;
pHalGdmaAdapter->MaxMuliBlock = BlkNum;
pHalGdmaAdapter->Rsvd4to7 = 1;
pHalGdmaAdapter->Llpctrl = 1;
pHalGdmaAdapter->GdmaCtl.LlpDstEn = 1;

pHalGdmaOp->HalGdmaOnOff( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChIsrEnAndDis( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChBlockSeting( (VOID*) ( pHalGdmaAdapter ) );
pHalGdmaOp->HalGdmaChEn( (VOID*) ( pHalGdmaAdapter ) );

return HAL_OK;
}

/**
 * Stop non-blocking UART TX
 *
 *
 * @return VOID
 */
HAL_STATUS HalRuartStopRecvRtl8195a_Patch(
IN VOID *Data      // PHAL_RUART_ADAPTER
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
PUART_DMA_CONFIG pUartGdmaConfig;
HAL_UART_State State;
u32 DMA_Dar;
u32 RecvdCnt;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_BUSY_RX ) && ( State != HAL_UART_STATE_BUSY_TX_RX ) )
{
  DBG_UART_WARN( "HalRuartStopRecvRtl8195a: Not in TX state, State=%d\n", State );
  return HAL_OK;
}

if ( HAL_OK != RuartLock( pHalRuartAdapter ) )
{
  DBG_UART_WARN( "HalRuartStopRecvRtl8195a:Unable to Lock, Statu=%d\n", State );
  return HAL_BUSY;
}

// Disable Rx interrupt
pHalRuartAdapter->Interrupts &= ~( RUART_IER_ERBI | RUART_IER_ELSI );
HalRuartSetIMRRtl8195a( pHalRuartAdapter );

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
if ( NULL != pUartGdmaConfig )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PHAL_GDMA_OP pHalGdmaOp;
  u8 IsrTypeMap;

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
  pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

  if ( ( NULL != pHalGdmaAdapter ) && ( NULL != pHalGdmaOp )
    && ( HalGdmaQueryChEnRtl8195a( (VOID*) pHalGdmaAdapter ) ) )
  {
    // Clean Auto Reload Bit
    pHalGdmaOp->HalGdmaChCleanAutoDst( (VOID*) pHalGdmaAdapter );
    // Clear Pending ISR
    IsrTypeMap = pHalGdmaOp->HalGdmaChIsrClean( (VOID*) pHalGdmaAdapter );
    pHalGdmaOp->HalGdmaChDis( (VOID*) ( pHalGdmaAdapter ) );

    DMA_Dar = HalGdmaQueryDArRtl8195a( (VOID*) pHalGdmaAdapter );
    RecvdCnt = DMA_Dar - ( u32 )( pHalRuartAdapter->pRxBuf );
//            DBG_8195A("%s: got %d bytes\r\n", __FUNCTION__, RecvdCnt);
    pHalRuartAdapter->RxCount -= RecvdCnt;
    pHalRuartAdapter->pRxBuf += RecvdCnt;
  }
}

while ( HalRuartGetCRtl8195a( pHalRuartAdapter, pHalRuartAdapter->pRxBuf ) == HAL_OK )
{
  pHalRuartAdapter->RxCount--;
  pHalRuartAdapter->pRxBuf++;
}

if ( pHalRuartAdapter->State == HAL_UART_STATE_BUSY_RX )
{
  pHalRuartAdapter->State = HAL_UART_STATE_READY;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_TX;
}

RuartUnLock( pHalRuartAdapter );

return HAL_OK;

}

/**
 * Stop non-blocking UART TX
 *
 *
 * @return VOID
 */
HAL_STATUS HalRuartStopSendRtl8195a_Patch(
IN VOID *Data      // PHAL_RUART_ADAPTER
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
PUART_DMA_CONFIG pUartGdmaConfig;
HAL_UART_State State;
u32 DMA_Sar;
u32 TxedCnt;

State = pHalRuartAdapter->State;
if ( ( State != HAL_UART_STATE_BUSY_TX ) && ( State != HAL_UART_STATE_BUSY_TX_RX ) )
{
  DBG_UART_WARN( "HalRuartDmaSendRtl8195a: Not in TX state, State=%d\n", State );
  return HAL_OK;
}

if ( HAL_OK != RuartLock( pHalRuartAdapter ) )
{
  DBG_UART_WARN( "HalRuartDmaSendRtl8195a:Unable to Lock, Statu=%d\n", State );
  return HAL_BUSY;
}

// Disable Tx FIFO empty interrupt
pHalRuartAdapter->Interrupts &= ~RUART_IER_ETBEI;
HalRuartSetIMRRtl8195a( pHalRuartAdapter );

pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
if ( NULL != pUartGdmaConfig )
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;
  PHAL_GDMA_OP pHalGdmaOp;
  u8 IsrTypeMap;

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
  pHalGdmaOp = (PHAL_GDMA_OP) pUartGdmaConfig->pHalGdmaOp;

  if ( ( NULL != pHalGdmaAdapter ) && ( NULL != pHalGdmaOp )
    && ( HalGdmaQueryChEnRtl8195a( (VOID*) pHalGdmaAdapter ) ) )
  {
    // Clean Auto Reload Bit
    pHalGdmaOp->HalGdmaChCleanAutoDst( (VOID*) pHalGdmaAdapter );
    // Clear Pending ISR
    IsrTypeMap = pHalGdmaOp->HalGdmaChIsrClean( (VOID*) pHalGdmaAdapter );
    pHalGdmaOp->HalGdmaChDis( (VOID*) ( pHalGdmaAdapter ) );

    DMA_Sar = HalGdmaQuerySArRtl8195a( (VOID*) pHalGdmaAdapter );
    TxedCnt = DMA_Sar - ( u32 )( pHalRuartAdapter->pTxBuf );
//            DBG_8195A("%s: got %d bytes\r\n", __FUNCTION__, RecvdCnt);
    pHalRuartAdapter->TxCount -= TxedCnt;
    pHalRuartAdapter->pTxBuf += TxedCnt;
  }
}

if ( State == HAL_UART_STATE_BUSY_TX )
{
  pHalRuartAdapter->State = HAL_UART_STATE_READY;
}
else
{
  pHalRuartAdapter->State = HAL_UART_STATE_BUSY_RX;
}

RuartUnLock( pHalRuartAdapter );

return HAL_OK;

}

VOID HalRuartEnterCriticalRtl8195a(
IN VOID *Data  ///< RUART Adapter
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
#ifdef CONFIG_GDMA_EN
PUART_DMA_CONFIG pUartGdmaConfig;
#endif

InterruptDis( &pHalRuartAdapter->IrqHandle );

#ifdef CONFIG_GDMA_EN
pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
if (NULL != pUartGdmaConfig)
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER)pUartGdmaConfig->pRxHalGdmaAdapter;
  if (pHalGdmaAdapter->ChEn != 0)
  {
    InterruptDis(&pUartGdmaConfig->RxGdmaIrqHandle);
  }

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER)pUartGdmaConfig->pTxHalGdmaAdapter;
  if (pHalGdmaAdapter->ChEn != 0)
  {
    InterruptDis(&pUartGdmaConfig->TxGdmaIrqHandle);
  }
}
#endif
}

VOID HalRuartExitCriticalRtl8195a(
IN VOID *Data  ///< RUART Adapter
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
#ifdef CONFIG_GDMA_EN
PUART_DMA_CONFIG pUartGdmaConfig;
#endif

InterruptEn( &pHalRuartAdapter->IrqHandle );

#ifdef CONFIG_GDMA_EN
pUartGdmaConfig = pHalRuartAdapter->DmaConfig;
if (NULL != pUartGdmaConfig)
{
  PHAL_GDMA_ADAPTER pHalGdmaAdapter;

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER)pUartGdmaConfig->pRxHalGdmaAdapter;
  if (pHalGdmaAdapter->ChEn != 0)
  {
    InterruptEn(&pUartGdmaConfig->RxGdmaIrqHandle);
  }

  pHalGdmaAdapter = (PHAL_GDMA_ADAPTER)pUartGdmaConfig->pTxHalGdmaAdapter;
  if (pHalGdmaAdapter->ChEn != 0)
  {
    InterruptEn(&pUartGdmaConfig->TxGdmaIrqHandle);
  }
}
#endif
}

VOID HalRuartDumpRegRtl8195a(
IN VOID *Data )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
u8 UartIndex;
u32 i;
u32 RegValue;

UartIndex = pHalRuartAdapter->UartIndex;

/* Set DLAB bit to 1 to access DLL/DLM */
RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF );
RegValue |= RUART_LINE_CTL_REG_DLAB_ENABLE;
HAL_RUART_WRITE32( UartIndex, RUART_LINE_CTL_REG_OFF, RegValue );

for ( i = 0; i < 0x40; i++ )
{
  DBG_8195A( "UART Reg[0x%x] = 0x%x\r\n", i, HAL_RUART_READ8( UartIndex, i ) );
}

/* clear DLAB bit */
RegValue = HAL_RUART_READ32( UartIndex, RUART_LINE_CTL_REG_OFF );
RegValue &= ~( RUART_LINE_CTL_REG_DLAB_ENABLE );
HAL_RUART_WRITE32( UartIndex, RUART_LINE_CTL_REG_OFF, RegValue );
}

#ifndef CONFIG_CHIP_E_CUT
// Pre-Defined Supported Baud Rate Table for CPU 166 MHz
const u32 DEF_BAUDRATE_TABLE[ ] = {
110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76800, 115200, 128000,
153600, 230400, 380400, 460800, 500000, 921600, 1000000, 1382400, 1444400, 1500000, 1843200,
2000000, 2100000, 2764800, 3000000, 3250000, 3692300, 3750000, 4000000, 6000000,

56000, 256000,

  // For UART to IR Carrier
66000, 72000, 73400, 76000, 80000, 112000,

  // End of the table
0xffffffff };

const u16 ovsr_adj_table_10bit[ 10 ] = {
0x000, 0x020, 0x044, 0x124, 0x294, 0x2AA, 0x16B, 0x2DB, 0x3BB, 0x3EF };

const u16 ovsr_adj_table_9bit[ 9 ] = {
0x000, 0x010, 0x044, 0x92, 0xAA, 0x155, 0x1B6, 0x1BB, 0x1EF };

const u16 ovsr_adj_table_8bit[ 8 ] = {
0x000, 0x010, 0x044, 0x92, 0xAA, 0xB5, 0xBB, 0xEF };

#if 0   // Old format
#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)

const u8 DEF_OVSR_166[] =
{
10, 10, 12, 14,
10, 10, 10, 11,
14, 11, 14, 11,
14, 10, 11, 14,
18, 17, 17, 18,
17, 13, 19, 18,
10, 11, 13, 19,
14, 13, 12, 11,
10, 10, 13,

20, 18,

// For UART to IR Carrier
13, 13, 18, 15,
20, 12,
};

const u16 DEF_DIV_166[] =
{
74272, 27233, 11347, 4863,
3404, 1702, 851, 516,
304, 258, 152, 129,
76, 71, 58, 38,
19, 12, 10, 9,
5, 6, 3, 3,
5, 4, 3, 2,
2, 2, 2, 2,
2, 2, 1,

73, 17,

// For UART to IR Carrier
97, 89, 63, 73,
52, 62,
};

const u16 DEF_OVSR_ADJ_166[] =
{
0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x000,
0x2AA, 0x3BB, 0x1B6, 0x010,
0x1B6, 0x2AA, 0x1B6, 0x2DB,
0x3BB, 0x000, 0x2AA, 0x294,
0x2DB, 0x2AA, 0x2AA, 0x000 ,
0x3BB, 0x088, 0x2AA,

0x000, 0x2DB,

// For UART to IR Carrier
0x000, 0x000, 0x000, 0x000,
0x000, 0x000
};
#endif  //#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)

#ifdef CONFIG_CHIP_C_CUT

const u8 DEF_OVSR_166[] =
{
13, 12, 12, 12,
18, 10, 10, 11,
10, 11, 10, 20,
20, 20, 20, 20,
20, 18, 20, 12,
15, 16, 20, 19,
18, 15, 10, 13,
15, 13, 12, 11,
11, 10, 13,

16, 18,

// For UART to IR Carrier
13, 13, 18, 15,
20, 12,
};

const u16 DEF_DIV_166[] =
{
58275, 23148, 11574, 5787,
1929, 1736, 868, 526,
434, 263, 217, 72,
54, 36, 32, 27,
18, 12, 9, 13,
6, 5, 3, 3,
3, 3, 4, 3,
2, 2, 2, 2,
2, 2, 1,

93, 18,

// For UART to IR Carrier
97, 89, 63, 73,
52, 62,
};

const u16 DEF_OVSR_ADJ_166[] =
{
0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x010,
0x010, 0x010, 0x124, 0x010,
0x010, 0x088, 0x010, 0x2DB,
0x000, 0x16B, 0x010, 0x088,
0x2AA, 0x000, 0x294, 0x088,
0x000, 0x3BB, 0x3BB, 0x088,
0x010, 0x294, 0x3BB,

0x000, 0x010,

// For UART to IR Carrier
0x000, 0x000, 0x000, 0x000,
0x000, 0x000
};

#endif  // #ifdef CONFIG_CHIP_C_CUT
#endif  // end of #if 0   // Old format

#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)
const u8 DEF_OVSR_B_CUT[] =
{
20, 20, 20, 20,
20, 20, 15, 18,
13, 15, 18, 13,
18, 12, 11, 10,
16, 15, 16, 18,
11, 20, 19, 14,
18, 11, 20, 19,
14, 13, 12, 11,
21, 20, 13,

18, 11,

// For UART to IR Carrier
13, 13, 18, 15,
20, 12

};

const u16 DEF_DIV_B_CUT[] =
{
37202, 13616, 6808, 3404,
1702, 851, 567, 315,
327, 189, 118, 109,
59, 59, 58, 53,
22, 14, 11, 9,
8, 4, 3, 4,
3, 4, 2, 2,
2, 2, 2, 2,
1, 1, 1,

81, 29,

// For UART to IR Carrier
97, 89, 63, 73,
52, 62
};

const u8 DEF_OVSR_ADJ_BITS_B_CUT_10B[] =
{
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
1, 3, 1, 2,
1, 4, 7, 1,
2, 1, 4, 5,
8, 6, 6, 1,
8, 4, 6,

0, 0,

// For UART to IR Carrier
0, 0, 0, 0,
0, 0

};

const u8 DEF_OVSR_ADJ_BITS_B_CUT_9B[] =
{
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
1, 3, 1, 1,
1, 4, 6, 1,
1, 1, 4, 4,
7, 6, 5, 1,
7, 4, 6,

0, 0,

// For UART to IR Carrier
0, 0, 0, 0,
0, 0

};

const u8 DEF_OVSR_ADJ_BITS_B_CUT_8B[] =
{
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
1, 3, 1, 1,
1, 4, 6, 1,
1, 1, 4, 4,
6, 5, 5, 1,
6, 4, 5,

0, 0,

// For UART to IR Carrier
0, 0, 0, 0,
0, 0
};

#endif  // #if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)

const u8 DEF_OVSR_C_CUT[ ] = {
20, 20, 20, 20, 20, 20, 20, 14, 20, 12, 14, 19, 19, 19, 13, 20, 19, 18, 20, 15, 18, 20, 20, 19, 11,
15, 20, 13, 15, 13, 12, 11, 11, 20, 13,

16, 13,

  // For UART to IR Carrier
13, 13, 18, 15, 20, 12 };

const u16 DEF_DIV_C_CUT[ ] = {
37878, 13888, 6944, 3472, 1736, 868, 434, 413, 217, 241, 155, 76, 57, 38, 50, 27, 19, 12, 9, 11, 5,
4, 3, 3, 5, 3, 2, 3, 2, 2, 2, 2, 2, 1, 1,

93, 25,

  // For UART to IR Carrier
97, 89, 63, 73, 52, 62 };

const u8 DEF_OVSR_ADJ_BITS_C_CUT_10B[ ] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 1, 2, 1, 8, 1, 2, 1, 1, 8, 2, 1, 9, 8, 3, 1,
8, 9,

0, 0,

  // For UART to IR Carrier
0, 0, 0, 0, 0, 0

};

const u8 DEF_OVSR_ADJ_BITS_C_CUT_9B[ ] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 1, 8, 1, 2, 1, 1, 8, 2, 1, 8, 8, 3, 1,
8, 8,

0, 0,

  // For UART to IR Carrier
0, 0, 0, 0, 0, 0

};

const u8 DEF_OVSR_ADJ_BITS_C_CUT_8B[ ] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 1, 7, 1, 2, 1, 1, 7, 2, 1, 7, 7, 2, 1,
7, 7,

0, 0,

  // For UART to IR Carrier
0, 0, 0, 0, 0, 0 };
#else
extern const u32 DEF_BAUDRATE_TABLE_ROM[];
extern const u16 ovsr_adj_table_10bit_rom[10];
extern const u16 ovsr_adj_table_9bit_rom[9];
extern const u16 ovsr_adj_table_8bit_rom[8];
extern const u8 DEF_OVSR_ROM[];
extern const u16 DEF_DIV_ROM[];
extern const u8 DEF_OVSR_ADJ_10BITS_ROM[];
extern const u8 DEF_OVSR_ADJ_9BITS_ROM[];
extern const u8 DEF_OVSR_ADJ_8BITS_ROM[];

#endif  // #if !(CONFIG_CHIP_E_CUT)

extern u32 _UartIrqHandle( VOID *Data );

extern HAL_STATUS
HalRuartInitRtl8195a_Patch(
IN VOID *Data  ///< RUART Adapter
);

#if (CONFIG_CHIP_C_CUT)
extern _LONG_CALL_ HAL_STATUS
HalRuartInitRtl8195aV02(
  IN VOID *Data  ///< RUART Adapter
);
#endif

extern u8 HalRuartGetChipVerRtl8195a( VOID );

const HAL_GDMA_CHNL Uart2_TX_GDMA_Chnl_Option[ ] = {
{
0, 0, GDMA0_CHANNEL0_IRQ, 0 }, {
0, 1, GDMA0_CHANNEL1_IRQ, 0 }, {
0, 2, GDMA0_CHANNEL2_IRQ, 0 }, {
0, 3, GDMA0_CHANNEL3_IRQ, 0 }, {
0, 4, GDMA0_CHANNEL4_IRQ, 0 }, {
0, 5, GDMA0_CHANNEL5_IRQ, 0 },

{
0xff, 0, 0, 0 }    // end
};

const HAL_GDMA_CHNL Uart2_RX_GDMA_Chnl_Option[ ] = {
{
1, 0, GDMA1_CHANNEL0_IRQ, 0 }, {
1, 1, GDMA1_CHANNEL1_IRQ, 0 }, {
1, 2, GDMA1_CHANNEL2_IRQ, 0 }, {
1, 3, GDMA1_CHANNEL3_IRQ, 0 }, {
1, 4, GDMA1_CHANNEL4_IRQ, 0 }, {
1, 5, GDMA1_CHANNEL5_IRQ, 0 },

{
0xff, 0, 0, 0 }    // end
};

const HAL_GDMA_CHNL Uart_GDMA_MB_Chnl_Option[ ] = {
{
0, 4, GDMA0_CHANNEL4_IRQ, 0 }, {
1, 4, GDMA1_CHANNEL4_IRQ, 0 }, {
0, 5, GDMA0_CHANNEL5_IRQ, 0 }, {
1, 5, GDMA1_CHANNEL5_IRQ, 0 },

{
0xff, 0, 0, 0 }    // end
};

const HAL_GDMA_CHNL Uart2_TX_GDMA_MB_Chnl_Option[ ] = {
{
0, 4, GDMA0_CHANNEL4_IRQ, 0 }, {
0, 5, GDMA0_CHANNEL5_IRQ, 0 },

{
0xff, 0, 0, 0 }    // end
};

const HAL_GDMA_CHNL Uart2_RX_GDMA_MB_Chnl_Option[ ] = {
{
1, 4, GDMA1_CHANNEL4_IRQ, 0 }, {
1, 5, GDMA1_CHANNEL5_IRQ, 0 },

{
0xff, 0, 0, 0 }    // end
};

VOID HalRuartOpInit(
IN VOID *Data )
{
PHAL_RUART_OP pHalRuartOp = (PHAL_RUART_OP) Data;

pHalRuartOp->HalRuartAdapterLoadDef = HalRuartAdapterLoadDefRtl8195a;
pHalRuartOp->HalRuartTxGdmaLoadDef = HalRuartTxGdmaLoadDefRtl8195a;
pHalRuartOp->HalRuartRxGdmaLoadDef = HalRuartRxGdmaLoadDefRtl8195a;
pHalRuartOp->HalRuartResetRxFifo = HalRuartResetRxFifoRtl8195a_Patch;
#if CONFIG_CHIP_E_CUT
pHalRuartOp->HalRuartInit = HalRuartInitRtl8195a_V04;
#else
pHalRuartOp->HalRuartInit = HalRuartInitRtl8195a_Patch;         // Hardware Init ROM code patch
#endif
pHalRuartOp->HalRuartDeInit = HalRuartDeInitRtl8195a;         // Hardware Init
pHalRuartOp->HalRuartPutC = HalRuartPutCRtl8195a;         // Send a byte
pHalRuartOp->HalRuartSend = HalRuartSendRtl8195a;         // Polling mode Tx
pHalRuartOp->HalRuartIntSend = HalRuartIntSendRtl8195a;      // Interrupt mode Tx
#if CONFIG_CHIP_E_CUT
  pHalRuartOp->HalRuartDmaSend = HalRuartDmaSendRtl8195a_V04;      // DMA mode Tx
  pHalRuartOp->HalRuartStopSend = HalRuartStopSendRtl8195a_V04;// Stop non-blocking TX
#else
pHalRuartOp->HalRuartDmaSend = HalRuartDmaSendRtl8195a_Patch;      // DMA mode Tx
pHalRuartOp->HalRuartStopSend = HalRuartStopSendRtl8195a_Patch;     // Stop non-blocking TX
#endif
pHalRuartOp->HalRuartGetC = HalRuartGetCRtl8195a;           // get a byte
pHalRuartOp->HalRuartRecv = HalRuartRecvRtl8195a;         // Polling mode Rx
pHalRuartOp->HalRuartIntRecv = HalRuartIntRecvRtl8195a;      // Interrupt mode Rx
pHalRuartOp->HalRuartDmaRecv = HalRuartDmaRecvRtl8195a;      // DMA mode Rx
#if CONFIG_CHIP_E_CUT
  pHalRuartOp->HalRuartStopRecv = HalRuartStopRecvRtl8195a_V04;     // Stop non-blocking Rx
#else
pHalRuartOp->HalRuartStopRecv = HalRuartStopRecvRtl8195a_Patch; // Stop non-blocking Rx
#endif
pHalRuartOp->HalRuartGetIMR = HalRuartGetIMRRtl8195a;
pHalRuartOp->HalRuartSetIMR = HalRuartSetIMRRtl8195a;
pHalRuartOp->HalRuartGetDebugValue = HalRuartGetDebugValueRtl8195a;
pHalRuartOp->HalRuartDmaInit = HalRuartDmaInitRtl8195a;
pHalRuartOp->HalRuartRTSCtrl = HalRuartRTSCtrlRtl8195a;
pHalRuartOp->HalRuartRegIrq = HalRuartRegIrqRtl8195a;
pHalRuartOp->HalRuartIntEnable = HalRuartIntEnableRtl8195a;
pHalRuartOp->HalRuartIntDisable = HalRuartIntDisableRtl8195a;
}

/**
 * Load UART HAL default setting
 *
 * Call this function to load the default setting for UART HAL adapter
 *
 *
 */
VOID HalRuartAdapterInit( PRUART_ADAPTER pRuartAdapter, u8 UartIdx )
{
PHAL_RUART_OP pHalRuartOp;
PHAL_RUART_ADAPTER pHalRuartAdapter;

if ( NULL == pRuartAdapter )
{
  return;
}

pHalRuartOp = pRuartAdapter->pHalRuartOp;
pHalRuartAdapter = pRuartAdapter->pHalRuartAdapter;

if ( ( NULL == pHalRuartOp ) || ( NULL == pHalRuartAdapter ) )
{
  return;
}

// Load default setting
if ( pHalRuartOp->HalRuartAdapterLoadDef != NULL )
{
  pHalRuartOp->HalRuartAdapterLoadDef( pHalRuartAdapter, UartIdx );
  pHalRuartAdapter->IrqHandle.Priority = 10;
}
else
{
  // Initial your UART HAL adapter here
}

// Start to modify the defualt setting
pHalRuartAdapter->PinmuxSelect = RUART0_MUX_TO_GPIOC;
pHalRuartAdapter->BaudRate = 38400;

//    pHalRuartAdapter->IrqHandle.IrqFun = (IRQ_FUN)_UartIrqHandle;
//    pHalRuartAdapter->IrqHandle.Data = (void *)pHalRuartAdapter;

// Register IRQ
InterruptRegister( &pHalRuartAdapter->IrqHandle );

}

/**
 * Load UART HAL GDMA default setting
 *
 * Call this function to load the default setting for UART GDMA
 *
 *
 */
HAL_STATUS HalRuartTxGdmaInit( PHAL_RUART_ADAPTER pHalRuartAdapter,
PUART_DMA_CONFIG pUartGdmaConfig, u8 IsMultiBlk )
{
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
HAL_GDMA_CHNL *pgdma_chnl;
HAL_GDMA_CHNL *pgdma_chnl_tbl = NULL;
UART_DMA_MULTIBLK *pDmaBlkList;

if ( ( NULL == pHalRuartAdapter ) || ( NULL == pUartGdmaConfig ) )
{
  return HAL_ERR_PARA;
}

// Load default setting
HalRuartTxGdmaLoadDefRtl8195a( pHalRuartAdapter, pUartGdmaConfig );

pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
if ( IsMultiBlk )
{
  // need to allocate a multiple block channel
  if ( pHalRuartAdapter->UartIndex != 2 )
  {
    pgdma_chnl_tbl = (HAL_GDMA_CHNL*) Uart_GDMA_MB_Chnl_Option;
  }
  else
  {
    // UART2 TX Only can use GDMA 0
    pgdma_chnl_tbl = (HAL_GDMA_CHNL*) Uart2_TX_GDMA_MB_Chnl_Option;
  }
  // Default use the 1st channel of the table
  pgdma_chnl = pgdma_chnl_tbl;
  pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
  pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
  pUartGdmaConfig->TxGdmaIrqHandle.IrqNum = pgdma_chnl->IrqNum;
}
else
{
  if ( pHalRuartAdapter->UartIndex == 2 )
  {
    // UART2 TX Only can use GDMA 0
    pgdma_chnl_tbl = (HAL_GDMA_CHNL *) Uart2_TX_GDMA_Chnl_Option;
  }
}

// Start to patch the default setting
if ( HalGdmaChnlRegister( pHalGdmaAdapter->GdmaIndex, pHalGdmaAdapter->ChNum ) != HAL_OK )
{
  // The default GDMA Channel is not available, try others
  pgdma_chnl = HalGdmaChnlAlloc( pgdma_chnl_tbl );

  if ( pgdma_chnl == NULL )
  {
    // No Available DMA channel
    DBG_UART_WARN( "HalRuartTxGdmaInit: Allocate DMA Channel Failed\n" );
    return HAL_BUSY;
  }
  else
  {
    pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
    pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
    pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
    pUartGdmaConfig->TxGdmaIrqHandle.IrqNum = pgdma_chnl->IrqNum;
  }
}

// User can assign a Interrupt Handler here
//    pUartGdmaConfig->TxGdmaIrqHandle.Data = pHalRuartAdapter;
//    pUartGdmaConfig->TxGdmaIrqHandle.IrqFun = (IRQ_FUN)_UartTxDmaIrqHandle
//    pUartGdmaConfig->TxGdmaIrqHandle.Priority = 12;
pUartGdmaConfig->TxGdmaIrqHandle.Priority = 12;
#if CONFIG_CHIP_E_CUT
pUartGdmaConfig->TxGdmaIrqHandle.IrqFun = (IRQ_FUN)_UartTxDmaIrqHandle_V04;
#else
pUartGdmaConfig->TxGdmaIrqHandle.IrqFun = (IRQ_FUN) _UartTxDmaIrqHandle_Patch;
#endif
HalRuartDmaInitRtl8195a( pHalRuartAdapter );
InterruptRegister( &pUartGdmaConfig->TxGdmaIrqHandle );
InterruptEn( &pUartGdmaConfig->TxGdmaIrqHandle );
pUartGdmaConfig->TxDmaMBChnl = IsMultiBlk;

if ( IsMultiBlk )
{
  pDmaBlkList = pUartGdmaConfig->pTxDmaBlkList;
  if ( NULL != pDmaBlkList )
  {
    pHalGdmaAdapter->pBlockSizeList = (struct BLOCK_SIZE_LIST*) &( pDmaBlkList->BlockSizeList );
    pHalGdmaAdapter->pLlix = (struct GDMA_CH_LLI*) &( pDmaBlkList->Lli );
  }
  else
  {
    DBG_UART_WARN( "HalRuartTxGdmaInit: no Block List for DMA\n" );
  }
}

return HAL_OK;
}

VOID HalRuartTxGdmaDeInit( PUART_DMA_CONFIG pUartGdmaConfig )
{
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
HAL_GDMA_CHNL GdmaChnl;

pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pTxHalGdmaAdapter;
GdmaChnl.GdmaIndx = pHalGdmaAdapter->GdmaIndex;
GdmaChnl.GdmaChnl = pHalGdmaAdapter->ChNum;
GdmaChnl.IrqNum = pUartGdmaConfig->TxGdmaIrqHandle.IrqNum;
HalGdmaChnlFree( &GdmaChnl );
pUartGdmaConfig->TxDmaMBChnl = 0;
}

/**
 * Load UART HAL GDMA default setting
 *
 * Call this function to load the default setting for UART GDMA
 *
 *
 */
HAL_STATUS HalRuartRxGdmaInit( PHAL_RUART_ADAPTER pHalRuartAdapter,
PUART_DMA_CONFIG pUartGdmaConfig, u8 IsMultiBlk )
{
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
HAL_GDMA_CHNL *pgdma_chnl;
HAL_GDMA_CHNL *pgdma_chnl_tbl = NULL;
UART_DMA_MULTIBLK *pDmaBlkList;

if ( ( NULL == pHalRuartAdapter ) || ( NULL == pUartGdmaConfig ) )
{
  return HAL_ERR_PARA;
}

// Load default setting
HalRuartRxGdmaLoadDefRtl8195a( pHalRuartAdapter, pUartGdmaConfig );

pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
if ( IsMultiBlk )
{
  // need to allocate a multiple block channel
  if ( pHalRuartAdapter->UartIndex != 2 )
  {
    pgdma_chnl_tbl = (HAL_GDMA_CHNL *) Uart_GDMA_MB_Chnl_Option;
  }
  else
  {
    // UART2 RX Only can use GDMA 1
    pgdma_chnl_tbl = (HAL_GDMA_CHNL *) Uart2_RX_GDMA_MB_Chnl_Option;
  }
  // Default use the 1st channel of the table
  pgdma_chnl = pgdma_chnl_tbl;
  pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
  pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
  pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
  pUartGdmaConfig->RxGdmaIrqHandle.IrqNum = pgdma_chnl->IrqNum;
}
else
{
  if ( pHalRuartAdapter->UartIndex == 2 )
  {
    // UART2 RX Only can use GDMA 1
    pgdma_chnl_tbl = (HAL_GDMA_CHNL *) Uart2_RX_GDMA_Chnl_Option;
  }
}

// Start to patch the default setting
if ( HalGdmaChnlRegister( pHalGdmaAdapter->GdmaIndex, pHalGdmaAdapter->ChNum ) != HAL_OK )
{
  // The default GDMA Channel is not available, try others
  pgdma_chnl = HalGdmaChnlAlloc( (HAL_GDMA_CHNL*) pgdma_chnl_tbl );
  if ( pgdma_chnl == NULL )
  {
    // No Available DMA channel
    DBG_UART_WARN( "HalRuartRxGdmaInit: Allocate DMA Channel Failed\n" );
    return HAL_BUSY;
  }
  else
  {
    pHalGdmaAdapter->GdmaIndex = pgdma_chnl->GdmaIndx;
    pHalGdmaAdapter->ChNum = pgdma_chnl->GdmaChnl;
    pHalGdmaAdapter->ChEn = 0x0101 << pgdma_chnl->GdmaChnl;
    pUartGdmaConfig->RxGdmaIrqHandle.IrqNum = pgdma_chnl->IrqNum;
  }
}

//    pUartGdmaConfig->RxGdmaIrqHandle.Data = pHalRuartAdapter;
#if CONFIG_CHIP_E_CUT
pUartGdmaConfig->RxGdmaIrqHandle.IrqFun = (IRQ_FUN)_UartRxDmaIrqHandle_V04;
#else
pUartGdmaConfig->RxGdmaIrqHandle.IrqFun = (IRQ_FUN) _UartRxDmaIrqHandle_Patch;
#endif
pUartGdmaConfig->RxGdmaIrqHandle.Priority = 11;

HalRuartDmaInitRtl8195a( pHalRuartAdapter );
InterruptRegister( &pUartGdmaConfig->RxGdmaIrqHandle );
InterruptEn( &pUartGdmaConfig->RxGdmaIrqHandle );
pUartGdmaConfig->RxDmaMBChnl = IsMultiBlk;
if ( IsMultiBlk )
{
  pDmaBlkList = pUartGdmaConfig->pRxDmaBlkList;
  if ( NULL != pDmaBlkList )
  {
    pHalGdmaAdapter->pBlockSizeList = (struct BLOCK_SIZE_LIST*) &( pDmaBlkList->BlockSizeList );
    pHalGdmaAdapter->pLlix = (struct GDMA_CH_LLI*) &( pDmaBlkList->Lli );
  }
  else
  {
    DBG_UART_WARN( "HalRuartRxGdma: no Block List for DMA\n" );
  }
}

return HAL_OK;
}

VOID HalRuartRxGdmaDeInit( PUART_DMA_CONFIG pUartGdmaConfig )
{
PHAL_GDMA_ADAPTER pHalGdmaAdapter;
HAL_GDMA_CHNL GdmaChnl;

pHalGdmaAdapter = (PHAL_GDMA_ADAPTER) pUartGdmaConfig->pRxHalGdmaAdapter;
GdmaChnl.GdmaIndx = pHalGdmaAdapter->GdmaIndex;
GdmaChnl.GdmaChnl = pHalGdmaAdapter->ChNum;
GdmaChnl.IrqNum = pUartGdmaConfig->RxGdmaIrqHandle.IrqNum;
HalGdmaChnlFree( &GdmaChnl );
pUartGdmaConfig->RxDmaMBChnl = 0;
}

/**
 * Hook a RX indication callback
 *
 * To hook a callback function which will be called when a got a RX byte
 *
 *
 */
VOID HalRuartRxIndHook( PRUART_ADAPTER pRuartAdapter,
VOID *pCallback,
VOID *pPara )
{
PHAL_RUART_ADAPTER pHalRuartAdapter = pRuartAdapter->pHalRuartAdapter;

pHalRuartAdapter->RxDRCallback = (void (*)( void* )) pCallback;
pHalRuartAdapter->RxDRCbPara = pPara;

// enable RX data ready interrupt
pHalRuartAdapter->Interrupts |= RUART_IER_ERBI | RUART_IER_ELSI;
pRuartAdapter->pHalRuartOp->HalRuartSetIMR( pHalRuartAdapter );
}

HAL_STATUS HalRuartResetTxFifo(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
return (HalRuartResetTxFifoRtl8195a_V04(Data));
#else
return ( HalRuartResetTxFifoRtl8195a( Data ) );
#endif
}

HAL_STATUS HalRuartResetRxFifo(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
return (HalRuartResetRxFifoRtl8195a_V04(Data));
#else
return ( HalRuartResetRxFifoRtl8195a_Patch( Data ) );
#endif
}

HAL_STATUS HalRuartResetTRxFifo(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
return (HalRuartResetTRxFifoRtl8195a_V04(Data));
#else
return ( HalRuartResetTRxFifoRtl8195a( Data ) );
#endif
}

HAL_STATUS HalRuartSetBaudRate(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
return HalRuartSetBaudRateRtl8195a_V04(Data);
#else
return HalRuartSetBaudRateRtl8195a( Data );
#endif
}

HAL_STATUS HalRuartInit(
IN VOID *Data )
{
HAL_STATUS ret;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
#ifdef CONFIG_SOC_PS_MODULE
REG_POWER_STATE UartPwrState;
#endif
#if CONFIG_CHIP_E_CUT
pHalRuartAdapter->pDefaultBaudRateTbl = (uint32_t*)DEF_BAUDRATE_TABLE_ROM;

pHalRuartAdapter->pDefaultOvsrRTbl = (uint8_t*)DEF_OVSR_ROM;
pHalRuartAdapter->pDefaultDivTbl = (uint16_t*)DEF_DIV_ROM;
pHalRuartAdapter->pDefOvsrAdjBitTbl_10 = (uint8_t*)DEF_OVSR_ADJ_10BITS_ROM;
pHalRuartAdapter->pDefOvsrAdjBitTbl_9 = (uint8_t*)DEF_OVSR_ADJ_9BITS_ROM;
pHalRuartAdapter->pDefOvsrAdjBitTbl_8 = (uint8_t*)DEF_OVSR_ADJ_8BITS_ROM;

pHalRuartAdapter->pDefOvsrAdjTbl_10 = (uint16_t*)ovsr_adj_table_10bit_rom;
pHalRuartAdapter->pDefOvsrAdjTbl_9 = (uint16_t*)ovsr_adj_table_9bit_rom;
pHalRuartAdapter->pDefOvsrAdjTbl_8 = (uint16_t*)ovsr_adj_table_8bit_rom;

ret = HalRuartInitRtl8195a_V04(Data);
#else
pHalRuartAdapter->pDefaultBaudRateTbl = (uint32_t*) DEF_BAUDRATE_TABLE;
#if defined(CONFIG_CHIP_A_CUT) || defined(CONFIG_CHIP_B_CUT)
u8 chip_ver;

chip_ver = HalRuartGetChipVerRtl8195a();
if (chip_ver < 2)
{
  pHalRuartAdapter->pDefaultOvsrRTbl = (uint8_t*)DEF_OVSR_B_CUT;
  pHalRuartAdapter->pDefaultDivTbl = (uint16_t*)DEF_DIV_B_CUT;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_10 = (uint8_t*)DEF_OVSR_ADJ_BITS_B_CUT_10B;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_9 = (uint8_t*)DEF_OVSR_ADJ_BITS_B_CUT_9B;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_8 = (uint8_t*)DEF_OVSR_ADJ_BITS_B_CUT_8B;
}
else
#endif
{
  pHalRuartAdapter->pDefaultOvsrRTbl = (uint8_t*) DEF_OVSR_C_CUT;
  pHalRuartAdapter->pDefaultDivTbl = (uint16_t*) DEF_DIV_C_CUT;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_10 = (uint8_t*) DEF_OVSR_ADJ_BITS_C_CUT_10B;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_9 = (uint8_t*) DEF_OVSR_ADJ_BITS_C_CUT_9B;
  pHalRuartAdapter->pDefOvsrAdjBitTbl_8 = (uint8_t*) DEF_OVSR_ADJ_BITS_C_CUT_8B;
}
pHalRuartAdapter->pDefOvsrAdjTbl_10 = (uint16_t*) ovsr_adj_table_10bit;
pHalRuartAdapter->pDefOvsrAdjTbl_9 = (uint16_t*) ovsr_adj_table_9bit;
pHalRuartAdapter->pDefOvsrAdjTbl_8 = (uint16_t*) ovsr_adj_table_8bit;

if ( _FALSE
  == FunctionChk( ( pHalRuartAdapter->UartIndex + UART0 ), pHalRuartAdapter->PinmuxSelect ) )
{
  return HAL_ERR_HW;
}
ret = HalRuartInitRtl8195a_Patch( Data );
#endif

#ifdef CONFIG_SOC_PS_MODULE
if(ret == HAL_OK)
{
  // To register a new peripheral device power state
  UartPwrState.FuncIdx = UART0 + pHalRuartAdapter->UartIndex;
  UartPwrState.PwrState = ACT;
  RegPowerState(UartPwrState);
}
#endif
return ret;
}

VOID HalRuartDeInit(
IN VOID *Data )
{
#ifdef CONFIG_SOC_PS_MODULE
REG_POWER_STATE UartPwrState;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
u8 HwState;

UartPwrState.FuncIdx = UART0 + pHalRuartAdapter->UartIndex;
QueryRegPwrState(UartPwrState.FuncIdx, &(UartPwrState.PwrState), &HwState);

// if the power state isn't ACT, then switch the power state back to ACT first
if ((UartPwrState.PwrState != ACT) && (UartPwrState.PwrState != INACT))
{
  HalRuartEnable(Data);
  QueryRegPwrState(UartPwrState.FuncIdx, &(UartPwrState.PwrState), &HwState);
}

if (UartPwrState.PwrState == ACT)
{
  UartPwrState.PwrState = INACT;
  RegPowerState(UartPwrState);
}
#endif

HalRuartDeInitRtl8195a( Data );
}

HAL_STATUS HalRuartDisable(
IN VOID *Data )
{
HAL_STATUS ret;
#ifdef CONFIG_SOC_PS_MODULE
REG_POWER_STATE UartPwrState;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
#endif

#if CONFIG_CHIP_E_CUT
ret = HalRuartDisableRtl8195a_V04(Data);
#else
ret = HalRuartDisableRtl8195a( Data );
#endif
#ifdef CONFIG_SOC_PS_MODULE
if (ret == HAL_OK)
{
  UartPwrState.FuncIdx = UART0 + pHalRuartAdapter->UartIndex;
  UartPwrState.PwrState = SLPCG;
  RegPowerState(UartPwrState);
}
#endif
return ret;
}

HAL_STATUS HalRuartEnable(
IN VOID *Data )
{
HAL_STATUS ret;
#ifdef CONFIG_SOC_PS_MODULE
REG_POWER_STATE UartPwrState;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
#endif

#if CONFIG_CHIP_E_CUT
ret = HalRuartEnableRtl8195a_V04(Data);
#else
ret = HalRuartEnableRtl8195a( Data );
#endif
#ifdef CONFIG_SOC_PS_MODULE
if (ret == HAL_OK)
{
  UartPwrState.FuncIdx = UART0 + pHalRuartAdapter->UartIndex;
  UartPwrState.PwrState = ACT;
  RegPowerState(UartPwrState);
}
#endif
return ret;
}

HAL_STATUS HalRuartFlowCtrl(
IN VOID *Data )
{
HAL_STATUS ret;
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;

#if CONFIG_CHIP_E_CUT
ret = HalRuartFlowCtrlRtl8195a_V04((VOID *)Data);
#else
ret = HalRuartFlowCtrlRtl8195a( (VOID *) Data );
#endif
// RTS_Pin = AFE ? (~rts | RX_FIFO_Level_Over) : ~rts;
HalRuartRTSCtrlRtl8195a( Data, pHalRuartAdapter->RTSCtrl );

return ret;
}

VOID HalRuartEnterCritical(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
HalRuartEnterCriticalRtl8195a_V04(Data);
#else
HalRuartEnterCriticalRtl8195a( Data );
#endif
}

VOID HalRuartExitCritical(
IN VOID *Data )
{
#if CONFIG_CHIP_E_CUT
HalRuartExitCriticalRtl8195a_V04(Data);
#else
HalRuartExitCriticalRtl8195a( Data );
#endif
}

/**
 * RUART send a data buffer by DMA(non-block) mode.
 *
 * RUART send data.
 *
 * @return VOID
 */
HAL_STATUS HalRuartDmaSend(
IN VOID *Data,      // PHAL_RUART_ADAPTER
IN u8 *pTxBuf,     // the Buffer to be send
IN u32 Length      // the length of data to be send
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
u32 BlockSize;
HAL_STATUS ret;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;

if ( ( ( Length & 0x03 ) == 0 ) && ( ( ( u32 )( pTxBuf ) & 0x03 ) == 0 ) )
{
  // 4-bytes aligned, move 4 bytes each transfer
  BlockSize = Length >> 2;
}
else
{
  BlockSize = Length;
}

if ( BlockSize < 4096 )
{
#if CONFIG_CHIP_E_CUT
  ret = HalRuartDmaSendRtl8195a_V04(Data, pTxBuf, Length);
#else
  ret = HalRuartDmaSendRtl8195a_Patch( Data, pTxBuf, Length );
#endif
}
else
{
  // over Maximum block size 4095, use multiple block DMA
  pUartGdmaConfig = pHalRuartAdapter->DmaConfig;

  if ( 0 == pUartGdmaConfig->TxDmaMBChnl )
  {
    // Current DMA channel doesn't support multiple block, so re-allocate DMA channel
    HalRuartTxGdmaDeInit( pHalRuartAdapter->DmaConfig );
    ret = HalRuartTxGdmaInit( pHalRuartAdapter, pUartGdmaConfig, 1 );
    if ( HAL_OK != ret )
    {
      DBG_UART_WARN( "HalRuartDmaSend: Reallocate DMA Multi-Block Chnl failed(%d)\n", ret );
      return ret;
    }
  }
#if CONFIG_CHIP_E_CUT
  ret = HalRuartMultiBlkDmaSendRtl8195a_V04(Data, pTxBuf, Length);
#else
  ret = HalRuartMultiBlkDmaSendRtl8195a( Data, pTxBuf, Length );
#endif
}

return ret;
}

/**
 * RUART receive a data buffer by DMA(non-block) mode.
 *
 * RUART send data.
 *
 * @return VOID
 */
HAL_STATUS HalRuartDmaRecv(
IN VOID *Data,      // PHAL_RUART_ADAPTER
IN u8 *pRxBuf,     // the Buffer for store RX data
IN u32 Length      // the length of data to receive
)
{
PHAL_RUART_ADAPTER pHalRuartAdapter = (PHAL_RUART_ADAPTER) Data;
//    u32 BlockSize;
HAL_STATUS ret;
PUART_DMA_CONFIG pUartGdmaConfig;
PHAL_GDMA_ADAPTER pHalGdmaAdapter;

if ( Length < 4096 )
{
#if CONFIG_CHIP_E_CUT
  ret = HalRuartDmaRecvRtl8195a_V04(Data, pRxBuf, Length);
#else
  ret = HalRuartDmaRecvRtl8195a_Patch( Data, pRxBuf, Length );
#endif
}
else
{
  // over Maximum block size 4095, use multiple block DMA
  pUartGdmaConfig = pHalRuartAdapter->DmaConfig;

  if ( !pUartGdmaConfig->RxDmaMBChnl )
  {
    // Current DMA channel doesn't support multiple block, so re-allocate DMA channel
    HalRuartRxGdmaDeInit( pHalRuartAdapter->DmaConfig );
    ret = HalRuartRxGdmaInit( pHalRuartAdapter, pUartGdmaConfig, 1 );
    if ( HAL_OK != ret )
    {
      DBG_UART_WARN( "HalRuartDmaRecv: Reallocate DMA Multi-Block Chnl failed(%d)\n", ret );
      return ret;
    }
  }
#if CONFIG_CHIP_E_CUT
  ret = HalRuartMultiBlkDmaRecvRtl8195a_V04(Data, pRxBuf, Length);
#else
  ret = HalRuartMultiBlkDmaRecvRtl8195a( Data, pRxBuf, Length );
#endif
}

return ret;
}

