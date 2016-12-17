#ifndef __RTL8195AM_UART_H__
#define __RTL8195AM_UART_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

//Register offset
#define UART_REV_BUF_OFF            0x00
#define UART_TRAN_HOLD_OFF          0x00
#define UART_DLH_OFF                0x04
#define UART_DLL_OFF                0x00
#define UART_INTERRUPT_EN_REG_OFF   0x04
#define UART_INTERRUPT_IDEN_REG_OFF 0x08
#define UART_FIFO_CTL_REG_OFF       0x08
#define UART_LINE_CTL_REG_OFF       0x0c
#define UART_MODEM_CTL_REG_OFF      0x10
#define UART_LINE_STATUS_REG_OFF    0x14
#define UART_MODEM_STATUS_REG_OFF   0x18
#define UART_FIFO_ACCESS_REG_OFF    0x70
#define UART_STATUS_REG_OFF         0x7c
#define UART_TFL_OFF                0x80
#define UART_RFL_OFF                0x84

//Buad rate
#define UART_BAUD_RATE_2400         2400
#define UART_BAUD_RATE_4800         4800
#define UART_BAUD_RATE_9600         9600
#define UART_BAUD_RATE_19200        19200
#define UART_BAUD_RATE_38400        38400
#define UART_BAUD_RATE_57600        57600
#define UART_BAUD_RATE_115200       115200
#define UART_BAUD_RATE_921600       921600
#define UART_BAUD_RATE_1152000      1152000

#define UART_PARITY_ENABLE          0x08
#define UART_PARITY_DISABLE         0

#define UART_DATA_LEN_5BIT          0x0
#define UART_DATA_LEN_6BIT          0x1
#define UART_DATA_LEN_7BIT          0x2
#define UART_DATA_LEN_8BIT          0x3

#define UART_STOP_1BIT              0x0
#define UART_STOP_2BIT              0x4

#define HAL_UART_READ32(addr)            HAL_READ32(LOG_UART_REG_BASE, addr)
#define HAL_UART_WRITE32(addr, value)    HAL_WRITE32(LOG_UART_REG_BASE, addr, value)
#define HAL_UART_READ16(addr)            HAL_READ16(LOG_UART_REG_BASE, addr)
#define HAL_UART_WRITE16(addr, value)    HAL_WRITE16(LOG_UART_REG_BASE, addr, value)
#define HAL_UART_READ8(addr)             HAL_READ8(LOG_UART_REG_BASE, addr)
#define HAL_UART_WRITE8(addr, value)     HAL_WRITE8(LOG_UART_REG_BASE, addr, value)

extern _LONG_CALL_ VOID HalSerialPutcRtl8195a( IN u8 c );
extern _LONG_CALL_ u8 HalSerialGetcRtl8195a( IN BOOL PullMode );
extern _LONG_CALL_ u32 HalSerialGetIsrEnRegRtl8195a( VOID );
extern _LONG_CALL_ VOID HalSerialSetIrqEnRegRtl8195a( IN u32 SetValue );

#define MAX_UART_INDEX      2

#define RUART_DLL_OFF                   0x00
#define RUART_DLM_OFF                   0x04    //RW, DLAB = 1
#define RUART_INTERRUPT_EN_REG_OFF      0x04
#define RUART_IER_ERBI                  0x01    //BIT0, Enable Received Data Available Interrupt (rx trigger)
#define RUART_IER_ETBEI                 (1<<1)  //BIT1, Enable Transmitter FIFO Empty Interrupt (tx fifo empty)
#define RUART_IER_ELSI                  (1<<2)  //BIT2, Enable Receiver Line Status Interrupt (receiver line status)
#define RUART_IER_EDSSI                 (1<<3)  //BIT3, Enable Modem Status Interrupt (modem status transition)

#define RUART_INT_ID_REG_OFF            0x08    //[R]
#define RUART_IIR_INT_PEND              0x01
#define RUART_IIR_INT_ID                (0x07<<1) //011(3), 010(2), 110(6), 001(1), 000(0)
#define RUART_FIFO_CTL_REG_OFF          0x08    //[W]
#define RUART_FIFO_CTL_REG_FIFO_ENABLE  0x01    //BIT0
#define RUART_FIFO_CTL_REG_CLEAR_RXFIFO (1<<1)  //BIT1, 0x02, Write 1 clear
#define RUART_FIFO_CTL_REG_CLEAR_TXFIFO (1<<2)  //BIT2, 0x04, Write 1 clear
#define RUART_FIFO_CTL_REG_DMA_ENABLE   0x08    //BIT3

#define FIFO_CTL_DEFAULT_WITH_FIFO_DMA  0xC9
#define FIFO_CTL_DEFAULT_WITH_FIFO      0xC1

#define RUART_MODEM_CTL_REG_OFF         0x10
#define RUART_MCR_RTS                   BIT1
#define RUART_MCL_AUTOFLOW_ENABLE       (1<<5)  //BIT5, 0x20

#define RUART_LINE_CTL_REG_OFF          0x0C
#define RUART_LINE_CTL_REG_DLAB_ENABLE  (1<<7)  //BIT7, 0x80

#define RUART_LINE_STATUS_REG_OFF       0x14
#define RUART_LINE_STATUS_REG_DR        0x01    //BIT0, Data Ready indicator
#define RUART_LINE_STATUS_ERR_OVERRUN   (1<<1)  //BIT1, Over Run
#define RUART_LINE_STATUS_ERR_PARITY    (1<<2)  //BIT2, Parity error
#define RUART_LINE_STATUS_ERR_FRAMING   (1<<3)  //BIT3, Framing error
#define RUART_LINE_STATUS_ERR_BREAK     (1<<4)  //BIT4, Break interrupt error
#define RUART_LINE_STATUS_REG_THRE      (1<<5)  //BIT5, 0x20, Transmit Holding Register Empty Interrupt enable
#define RUART_LINE_STATUS_REG_TEMT      (1<<6)  //BIT6, 0x40, Transmitter Empty indicator(bit)
#define RUART_LINE_STATUS_ERR_RXFIFO    (1<<7)  //BIT7, RX FIFO error
#define RUART_LINE_STATUS_ERR           (RUART_LINE_STATUS_ERR_OVERRUN|RUART_LINE_STATUS_ERR_PARITY| \
                                        RUART_LINE_STATUS_ERR_FRAMING|RUART_LINE_STATUS_ERR_BREAK| \
                                        RUART_LINE_STATUS_ERR_RXFIFO)      //Line status error

#define RUART_MODEM_STATUS_REG_OFF      0x18    //Modem Status Register
#define RUART_SCRATCH_PAD_REG_OFF       0x1C    //Scratch Pad Register
#define RUART_SP_REG_RXBREAK_INT_STATUS (1<<7)  //BIT7, 0x80, Write 1 clear
#define RUART_SP_REG_DBG_SEL            (0x0F<<8) //[11:8], Debug port selection
#define RUART_SP_REG_XFACTOR_ADJ        (0x7FF<<16)  //[26:16]

#define RUART_STS_REG_OFF               0x20
#define RUART_STS_REG_RESET_RCV         (1<<3)  //BIT3, 0x08, Reset Uart Receiver
#define RUART_STS_REG_XFACTOR           0xF<<4

#define RUART_REV_BUF_REG_OFF           0x24  //Receiver Buffer Register
#define RUART_TRAN_HOLD_REG_OFF         0x24  //Transmitter Holding Register

#define RUART_MISC_CTL_REG_OFF          0x28
#define RUART_TXDMA_BURSTSIZE_MASK      0xF8    //7:3
#define RUART_RXDMA_BURSTSIZE_MASK      0x1F00  //12:8

#define RUART_DEBUG_REG_OFF             0x3C

// RUART_LINE_CTL_REG_OFF (0x0C)
#define BIT_SHIFT_LCR_WLS             0     // word length select: 0: 7 bits, 1: 8bits
#define BIT_MASK_LCR_WLS_8BITS        0x1
#define BIT_LCR_WLS(x)(((x) & BIT_MASK_LCR_WLS_8BITS) << BIT_SHIFT_LCR_WLS)
#define BIT_CLR_LCR_WLS (~(BIT_MASK_LCR_WLS_8BITS << BIT_SHIFT_LCR_WLS))

#define BIT_SHIFT_LCR_STB             2     // Stop bit select: 0: no stop bit, 1: 1 stop bit
#define BIT_MASK_LCR_STB_EN           0x1
#define BIT_LCR_STB_EN(x)(((x) & BIT_MASK_LCR_STB_EN) << BIT_SHIFT_LCR_STB)
#define BIT_INVC_LCR_STB_EN (~(BIT_MASK_LCR_STB_EN << BIT_SHIFT_LCR_STB))

#define BIT_SHIFT_LCR_PARITY_EN       3
#define BIT_MASK_LCR_PARITY_EN        0x1
#define BIT_LCR_PARITY_EN(x)(((x) & BIT_MASK_LCR_PARITY_EN) << BIT_SHIFT_LCR_PARITY_EN)
#define BIT_INVC_LCR_PARITY_EN (~(BIT_MASK_LCR_PARITY_EN << BIT_SHIFT_LCR_PARITY_EN))

#define BIT_SHIFT_LCR_PARITY_TYPE       4
#define BIT_MASK_LCR_PARITY_TYPE        0x1
#define BIT_LCR_PARITY_TYPE(x)(((x) & BIT_MASK_LCR_PARITY_TYPE) << BIT_SHIFT_LCR_PARITY_TYPE)
#define BIT_INVC_LCR_PARITY_TYPE (~(BIT_MASK_LCR_PARITY_TYPE << BIT_SHIFT_LCR_PARITY_TYPE))

#define BIT_SHIFT_LCR_STICK_PARITY_EN       5
#define BIT_MASK_LCR_STICK_PARITY_EN        0x1
#define BIT_LCR_STICK_PARITY_EN(x)(((x) & BIT_MASK_LCR_STICK_PARITY_EN) << BIT_SHIFT_LCR_STICK_PARITY_EN)
#define BIT_INVC_LCR_STICK_PARITY_EN (~(BIT_MASK_LCR_STICK_PARITY_EN << BIT_SHIFT_LCR_STICK_PARITY_EN))

#define BIT_SHIFT_LCR_BREAK_CTRL       6
#define BIT_MASK_LCR_BREAK_CTRL        0x1
#define BIT_UART_LCR_BREAK_CTRL        ((BIT_MASK_LCR_BREAK_CTRL) << BIT_SHIFT_LCR_BREAK_CTRL)

#define RUART_BAUD_RATE_2400     2400
#define RUART_BAUD_RATE_4800     4800
#define RUART_BAUD_RATE_9600     9600
#define RUART_BAUD_RATE_19200    19200
#define RUART_BAUD_RATE_38400    38400
#define RUART_BAUD_RATE_57600    57600
#define RUART_BAUD_RATE_115200   115200
#define RUART_BAUD_RATE_921600   921600
#define RUART_BAUD_RATE_1152000  1152000

#define HAL_RUART_READ32(UartIndex, addr)    \
    HAL_READ32(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr)
#define HAL_RUART_WRITE32(UartIndex, addr, value)    \
    HAL_WRITE32(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr, value)
#define HAL_RUART_READ16(UartIndex, addr)    \
    HAL_READ16(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr)
#define HAL_RUART_WRITE16(UartIndex, addr, value)    \
    HAL_WRITE16(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr, value)
#define HAL_RUART_READ8(UartIndex, addr)    \
    HAL_READ8(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr)
#define HAL_RUART_WRITE8(UartIndex, addr, value)    \
    HAL_WRITE8(UART0_REG_BASE+ (UartIndex*RUART_REG_OFF), addr, value)

#define UART_OVSR_POOL_MIN      1000
#define UART_OVSR_POOL_MAX      2090
#define DIVISOR_RESOLUTION      10
#define JITTER_LIMIT            100
#define UART_SCLK               (200000000*5/12)

typedef struct _RUART_SPEED_SETTING_
{
  u32 BaudRate;
  u32 Ovsr;
  u32 Div;
  u32 Ovsr_adj;
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
  u8 Ovsr_adj_max_bits;  // 9: No parity, 10: with Parity
  u8 Ovsr_adj_bits;
  u16 *Ovsr_adj_map;
  u32 max_err;        // 10 ~ 100: 30
  u32 Ovsr_min;       // 10 ~ 20: 1000
  u32 Ovsr_max;       // 10 ~ 20: 2000
  u32 divisor_resolution; // 1 ~ 20: 10
  u32 jitter_lim;     // 50 ~ 100: 100
  u32 sclk;           // 83.33333 MHz
#endif
} RUART_SPEED_SETTING, *PRUART_SPEED_SETTING;

typedef enum _UART_RXFIFO_TRIGGER_LEVEL_
{
  OneByte = 0x00,
  FourBytes = 0x01,
  EightBytes = 0x10,
  FourteenBytes = 0x11
} UART_RXFIFO_TRIGGER_LEVEL, *PUART_RXFIFO_TRIGGER_LEVEL;

typedef enum _RUART0_PINMUX_SELECT_
{
  RUART0_MUX_TO_GPIOC = S0,
  RUART0_MUX_TO_GPIOE = S1,
  RUART0_MUX_TO_GPIOA = S2
} RUART0_PINMUX_SELECT, *PRUART0_PINMUX_SELECT;

typedef enum _RUART1_PINMUX_SELECT_
{
  RUART1_MUX_TO_GPIOD = S0,
  RUART1_MUX_TO_GPIOE = S1,
  RUART1_MUX_TO_GPIOB = S2
} RUART1_PINMUX_SELECT, *PRUART1_PINMUX_SELECT;

typedef enum _RUART2_PINMUX_SELECT_
{
  RUART2_MUX_TO_GPIOA = S0,
  RUART2_MUX_TO_GPIOC = S1,
  RUART2_MUX_TO_GPIOD = S2
} RUART2_PINMUX_SELECT, *PRUART2_PINMUX_SELECT;

typedef enum _RUART_FLOW_CONTROL_
{
  AUTOFLOW_DISABLE = 0,
  AUTOFLOW_ENABLE = 1
} RUART_FLOW_CONTROL, *PRUART_FLOW_CONTROL;

typedef enum _RUART_WORD_LEN_SEL_
{
  RUART_WLS_7BITS = 0,
  RUART_WLS_8BITS = 1
} RUART_WORD_LEN_SEL, *PRUART_WORD_LEN_SEL;

typedef enum _RUART_STOP_BITS_
{
  RUART_STOP_BIT_1 = 0,
  RUART_STOP_BIT_2 = 1
} RUART_STOP_BITS, *PRUART_STOP_BITS;

typedef enum _RUART_PARITY_CONTROL_
{
  RUART_PARITY_DISABLE = 0,
  RUART_PARITY_ENABLE = 1
} RUART_PARITY_CONTROL, *PRUART_PARITY_CONTROL;

typedef enum _RUART_PARITY_TYPE_
{
  RUART_ODD_PARITY = 0,
  RUART_EVEN_PARITY = 1
} RUART_PARITY_TYPE, *PRUART_PARITY_TYPE;

typedef enum _RUART_STICK_PARITY_CONTROL_
{
  RUART_STICK_PARITY_DISABLE = 0,
  RUART_STICK_PARITY_ENABLE = 1
} RUART_STICK_PARITY_CONTROL, *PRUART_STICK_PARITY_CONTROL;

typedef enum _UART_INT_ID_
{
  ModemStatus = 0,
  TxFifoEmpty = 1,
  ReceiverDataAvailable = 2,
  ReceivLineStatus = 3,
  TimeoutIndication = 6
} UART_INT_ID, *PUART_INT_ID;

typedef enum _HAL_UART_State_
{
  HAL_UART_STATE_NULL = 0x00,    // UART hardware not been initial yet
  HAL_UART_STATE_READY = 0x10,    // UART is initialed, ready to use
  HAL_UART_STATE_BUSY = 0x20,    // UART hardware is busy on configuration
  HAL_UART_STATE_BUSY_TX = 0x21,    // UART is buzy on TX
  HAL_UART_STATE_BUSY_RX = 0x22,    // UART is busy on RX
  HAL_UART_STATE_BUSY_TX_RX = 0x23,    // UART is busy on TX an RX
  HAL_UART_STATE_TIMEOUT = 0x30,    // Transfer timeout
  HAL_UART_STATE_ERROR = 0x40     // UART Error
} HAL_UART_State, *PHAL_UART_State;

typedef enum _HAL_UART_Status_
{
  HAL_UART_STATUS_OK = 0x00,    // Transfer OK
  HAL_UART_STATUS_TIMEOUT = 0x01,    // Transfer Timeout
  HAL_UART_STATUS_ERR_OVERRUN = 0x02,    // RX Over run
  HAL_UART_STATUS_ERR_PARITY = 0x04,    // Parity error
  HAL_UART_STATUS_ERR_FRAM = 0x08,    // Framing Error
  HAL_UART_STATUS_ERR_BREAK = 0x10,    // Break Interrupt
  HAL_UART_STATUS_ERR_PARA = 0x20,    // Parameter error
  HAL_UART_STATUS_ERR_RXFIFO = 0x80,    // RX FIFO error
} HAL_UART_Status, *PHAL_UART_Status;

u32
HalRuartGetDebugValueRtl8195a(
IN VOID* Data, IN u32 DbgSel );

#if 0
u32
FindElementIndex(
    u32 Element,
    u32* Array
);
#endif

VOID
RuartResetRxFifoRtl8195a( IN u8 UartIndex );
#if 0
VOID
RuartBusDomainEnableRtl8195a(
    IN u8 UartIndex
);
#endif

HAL_STATUS
HalRuartResetRxFifoRtl8195a(
IN VOID *Data );

HAL_STATUS
HalRuartInitRtl8195a(
IN VOID *Data );

VOID
HalRuartDeInitRtl8195a(
IN VOID *Data  ///< RUART Adapter
  );

HAL_STATUS
HalRuartPutCRtl8195a(
IN VOID *Data, IN u8 TxData );

u32
HalRuartSendRtl8195a(
IN VOID *Data, IN u8 *pTxData, IN u32 Length, IN u32 Timeout );

HAL_STATUS
HalRuartIntSendRtl8195a(
IN VOID *Data,      // PHAL_RUART_ADAPTER
  IN u8 *pTxData,     // the Buffer to be send
  IN u32 Length       // the length of data to be send
  );

HAL_STATUS
HalRuartDmaSendRtl8195a(
IN VOID *Data,      // PHAL_RUART_ADAPTER
  IN u8 *pTxData,     // the Buffer to be send
  IN u32 Length      // the length of data to be send
  );

HAL_STATUS
HalRuartStopSendRtl8195a(
IN VOID *Data      // PHAL_RUART_ADAPTER
  );

HAL_STATUS
HalRuartGetCRtl8195a(
IN VOID *Data, OUT u8 *pRxByte );

u32
HalRuartRecvRtl8195a(
IN VOID *Data, IN u8 *pRxData, IN u32 Length, IN u32 Timeout );

HAL_STATUS
HalRuartIntRecvRtl8195a(
IN VOID *Data,  ///< RUART Adapter
  IN u8 *pRxData,  ///< Rx buffer
  IN u32 Length      // buffer length
  );

HAL_STATUS
HalRuartDmaRecvRtl8195a(
IN VOID *Data,  ///< RUART Adapter
  IN u8 *pRxData,  ///< Rx buffer
  IN u32 Length      // buffer length
  );

HAL_STATUS
HalRuartStopRecvRtl8195a(
IN VOID *Data      // PHAL_RUART_ADAPTER
  );

u8
HalRuartGetIMRRtl8195a(
IN VOID *Data );

_LONG_CALL_ROM_ VOID
HalRuartSetIMRRtl8195a(
IN VOID *Data );

VOID
HalRuartDmaInitRtl8195a(
IN VOID *Data );

VOID
HalRuartRTSCtrlRtl8195a(
IN VOID *Data, IN BOOLEAN RtsCtrl );

VOID
HalRuartRegIrqRtl8195a(
IN VOID *Data );

VOID
HalRuartIntEnableRtl8195a(
IN VOID *Data );

VOID
HalRuartIntDisableRtl8195a(
IN VOID *Data );

VOID
HalRuartAdapterLoadDefRtl8195a(
IN VOID *pAdp, IN u8 UartIdx );

VOID
HalRuartTxGdmaLoadDefRtl8195a(
IN VOID *pAdp,
IN VOID *pCfg );

VOID
HalRuartRxGdmaLoadDefRtl8195a(
IN VOID *pAdp,
IN VOID *pCfg );

_LONG_CALL_ HAL_STATUS HalRuartIntSendRtl8195aV02(
IN VOID *Data,      // PHAL_RUART_ADAPTER
  IN u8 *pTxData,     // the Buffer to be send
  IN u32 Length      // the length of data to be send
  );

_LONG_CALL_ HAL_STATUS
HalRuartIntRecvRtl8195aV02(
IN VOID *Data,  ///< RUART Adapter
  IN u8 *pRxData,  ///< Rx buffer
  IN u32 Length      // buffer length
  );

_LONG_CALL_ s32
FindElementIndex_v02( u32 Element,  ///< RUART Baudrate
  u32* Array,    ///< Pre-defined Baudrate Array
  u32 ElementNo );

_LONG_CALL_ HAL_STATUS HalRuartInitRtl8195a_v02( IN VOID *Data );

// New added function 2015/04/20
HAL_STATUS
HalRuartResetTxFifoRtl8195a(
IN VOID *Data  ///< RUART Adapter
  );

HAL_STATUS
HalRuartResetRxFifoRtl8195a_Patch(
IN VOID *Data  ///< RUART Adapter
  );

HAL_STATUS
HalRuartResetTRxFifoRtl8195a(
IN VOID *Data  ///< RUART Adapter
  );

HAL_STATUS
HalRuartSetBaudRateRtl8195a(
IN VOID *Data );

HAL_STATUS
HalRuartEnableRtl8195a(
IN VOID *Data );

HAL_STATUS
HalRuartDisableRtl8195a(
IN VOID *Data );

HAL_STATUS
HalRuartFlowCtrlRtl8195a(
IN VOID *Data );

u32
_UartTxDmaIrqHandle_Patch(
IN VOID *Data );

u32
_UartRxDmaIrqHandle_Patch(
IN VOID *Data );

HAL_STATUS
HalRuartDmaSendRtl8195a_Patch(
IN VOID *Data, IN u8 *pTxData, IN u32 Length );

HAL_STATUS
HalRuartDmaRecvRtl8195a_Patch(
IN VOID *Data, IN u8 *pRxData, IN u32 Length );

HAL_STATUS
HalRuartMultiBlkDmaSendRtl8195a(
IN VOID *Data, IN u8 *pTxData, IN u32 Length );

HAL_STATUS
HalRuartMultiBlkDmaRecvRtl8195a(
IN VOID *Data, IN u8 *pRxData, IN u32 Length );

HAL_STATUS
RuartIsTimeout( u32 StartCount, u32 TimeoutCnt );

HAL_STATUS
HalRuartStopRecvRtl8195a_Patch(
IN VOID *Data );

HAL_STATUS
HalRuartStopSendRtl8195a_Patch(
IN VOID *Data );

VOID
HalRuartEnterCriticalRtl8195a(
IN VOID *Data );

VOID
HalRuartExitCriticalRtl8195a(
IN VOID *Data );

#if CONFIG_CHIP_E_CUT
_LONG_CALL_ HAL_STATUS
HalRuartResetTxFifoRtl8195a_V04(
    IN VOID *Data  ///< RUART Adapter
);

_LONG_CALL_ HAL_STATUS
HalRuartResetRxFifoRtl8195a_V04(
    IN VOID *Data///< RUART Adapter
);

_LONG_CALL_ HAL_STATUS
HalRuartResetTRxFifoRtl8195a_V04(
    IN VOID *Data///< RUART Adapter
);

_LONG_CALL_ HAL_STATUS
HalRuartSetBaudRateRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ HAL_STATUS
HalRuartInitRtl8195a_V04(
    IN VOID *Data///< RUART Adapter
);

_LONG_CALL_ HAL_STATUS
HalRuartEnableRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ HAL_STATUS
HalRuartDisableRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ HAL_STATUS
HalRuartFlowCtrlRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ u32
_UartTxDmaIrqHandle_V04(
    IN VOID *Data
);

_LONG_CALL_ u32
_UartRxDmaIrqHandle_V04(
    IN VOID *Data
);

_LONG_CALL_ HAL_STATUS
HalRuartDmaSendRtl8195a_V04(
    IN VOID *Data,
    IN u8 *pTxData,
    IN u32 Length
);

_LONG_CALL_ HAL_STATUS
HalRuartDmaRecvRtl8195a_V04(
    IN VOID *Data,
    IN u8 *pRxData,
    IN u32 Length
);

_LONG_CALL_ HAL_STATUS
HalRuartMultiBlkDmaSendRtl8195a_V04(
    IN VOID *Data,
    IN u8 *pTxData,
    IN u32 Length
);

_LONG_CALL_ HAL_STATUS
HalRuartMultiBlkDmaRecvRtl8195a_V04(
    IN VOID *Data,
    IN u8 *pRxData,
    IN u32 Length
);

_LONG_CALL_ HAL_STATUS
HalRuartStopRecvRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ HAL_STATUS
HalRuartStopSendRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ VOID
HalRuartEnterCriticalRtl8195a_V04(
    IN VOID *Data
);

_LONG_CALL_ VOID
HalRuartExitCriticalRtl8195a_V04(
    IN VOID *Data
);

#endif  // #if CONFIG_CHIP_E_CUT

/**
 * RUART Configurations
 */
#define UART_WAIT_FOREVER       0xffffffff

#define UART_DMA_MBLK_NUM       16      // maximum block number for each DMA transfer, it must <= 16
#define UART_DMA_BLOCK_SIZE     4092    // the block size of multiple block DMA, it cann0t over 4095

typedef struct _HAL_UART_DMA_MULTIBLK_
{
  volatile GDMA_CH_LLI_ELE GdmaChLli[ UART_DMA_MBLK_NUM ];
  struct GDMA_CH_LLI Lli[ UART_DMA_MBLK_NUM ];
  struct BLOCK_SIZE_LIST BlockSizeList[ UART_DMA_MBLK_NUM ];
} UART_DMA_MULTIBLK, *PUART_DMA_MULTIBLK;

typedef struct _UART_DMA_CONFIG_
{
  u8 TxDmaEnable;
  u8 RxDmaEnable;
  u8 TxDmaBurstSize;
  u8 RxDmaBurstSize;
  VOID *pHalGdmaOp;
  VOID *pTxHalGdmaAdapter;
  VOID *pRxHalGdmaAdapter;
  IRQ_HANDLE TxGdmaIrqHandle;
  IRQ_HANDLE RxGdmaIrqHandle;
#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
  UART_DMA_MULTIBLK *pTxDmaBlkList;       // point to multi-block list
  UART_DMA_MULTIBLK *pRxDmaBlkList;       // point to multi-block list
  u8 TxDmaMBChnl;     // is using DMA multiple block channel
  u8 RxDmaMBChnl;     // is using DMA multiple block channel
#endif
} UART_DMA_CONFIG, *PUART_DMA_CONFIG;

typedef struct _HAL_RUART_ADAPTER_
{
  u32 BaudRate;
  u32 FlowControl;
  u32 FifoControl;
  u32 Interrupts;
  u32 TxCount;     // how many byte to TX
  u32 RxCount;     // how many bytes to RX
  u8 *pTxBuf;
  u8 *pRxBuf;
  HAL_UART_State State;       // UART state
  u8 Status;      // Transfer Status
  u8 Locked;      // is UART locked for operation
  u8 UartIndex;
  u8 WordLen;     // word length select: 0 -> 7 bits, 1 -> 8 bits
  u8 StopBit;     // word length select: 0 -> 1 stop bit, 1 -> 2 stop bit
  u8 Parity;      // parity check enable
  u8 ParityType;  // parity check type
  u8 StickParity;
  u8 ModemStatus; // the modem status
  u8 DmaEnable;
  u8 TestCaseNumber;
  u8 PinmuxSelect;
  BOOL PullMode;
  IRQ_HANDLE IrqHandle;
  PUART_DMA_CONFIG DmaConfig;
  VOID (*ModemStatusInd)( VOID *pAdapter );    // modem status indication interrupt handler
  VOID (*TxTDCallback)( VOID *pAdapter );      // User Tx Done callback function
  VOID (*RxDRCallback)( VOID *pAdapter );      // User Rx Data ready callback function
  VOID (*TxCompCallback)( VOID *para );    // User Tx complete callback function
  VOID (*RxCompCallback)( VOID *para );    // User Rx complete callback function
  VOID *TxTDCbPara;   // the pointer agrument for TxTDCallback
  VOID *RxDRCbPara;   // the pointer agrument for RxDRCallback
  VOID *TxCompCbPara; // the pointer argument for TxCompCbPara
  VOID *RxCompCbPara; // the pointer argument for RxCompCallback
  VOID (*EnterCritical)( void );
  VOID (*ExitCritical)( void );

#if defined(E_CUT_ROM_DOMAIN) || (!defined(CONFIG_RELEASE_BUILD_LIBRARIES))
  //1 New member only can be added below: members above must be fixed for ROM code
  u32 *pDefaultBaudRateTbl;      // point to the table of pre-defined baud rate
  u8 *pDefaultOvsrRTbl;         // point to the table of OVSR for pre-defined baud rate
  u16 *pDefaultDivTbl;           // point to the table of DIV for pre-defined baud rate
  u8 *pDefOvsrAdjBitTbl_10;     // point to the table of OVSR-Adj bits for 10 bits
  u8 *pDefOvsrAdjBitTbl_9;     // point to the table of OVSR-Adj bits for 9 bits
  u8 *pDefOvsrAdjBitTbl_8;     // point to the table of OVSR-Adj bits for 8 bits
  u16 *pDefOvsrAdjTbl_10;       // point to the table of OVSR-Adj for pre-defined baud rate
  u16 *pDefOvsrAdjTbl_9;       // point to the table of OVSR-Adj for pre-defined baud rate
  u16 *pDefOvsrAdjTbl_8;       // point to the table of OVSR-Adj for pre-defined baud rate
  PUART_DMA_MULTIBLK pTxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
  PUART_DMA_MULTIBLK pRxDMAMBlk;  // point to the Link List Table of the DMA Multiple Block
  u32 BaudRateUsing;             // Current using Baud-Rate
  u8 WordLenUsing;             // Current using Word Length
  u8 ParityUsing;             // Current using Parity check
  u8 RTSCtrl;               // Software RTS Control

#if 0//CONFIG_CHIP_E_CUT
u8 TxState;
u8 RxState;
u32 TxInitSize;     // how many byte to TX at atart
u32 RxInitSize;// how many bytes to RX at start

VOID (*RuartEnterCritical)(VOID *para);// enter critical: disable UART interrupt
VOID (*RuartExitCritical)(VOID *para);// exit critical: re-enable UART interrupt
VOID (*TaskYield)(VOID *para);// User Task Yield: do a context switch while waitting
VOID *TaskYieldPara;// the agrument (pointer) for TaskYield
#endif    // #if CONFIG_CHIP_E_CUT
#endif
} HAL_RUART_ADAPTER, *PHAL_RUART_ADAPTER;

typedef struct _HAL_RUART_OP_
{
VOID (*HalRuartAdapterLoadDef)( VOID *pAdp, u8 UartIdx );    // Load UART adapter default setting
VOID (*HalRuartTxGdmaLoadDef)( VOID *pAdp, VOID *pCfg );     // Load TX GDMA default setting
VOID (*HalRuartRxGdmaLoadDef)( VOID *pAdp, VOID *pCfg );     // Load RX GDMA default setting
HAL_STATUS (*HalRuartResetRxFifo)( VOID *Data );
HAL_STATUS (*HalRuartInit)( VOID *Data );
VOID (*HalRuartDeInit)( VOID *Data );
HAL_STATUS (*HalRuartPutC)( VOID *Data, u8 TxData );
u32 (*HalRuartSend)( VOID *Data, u8 *pTxData, u32 Length, u32 Timeout );
HAL_STATUS (*HalRuartIntSend)( VOID *Data, u8 *pTxData, u32 Length );
HAL_STATUS (*HalRuartDmaSend)( VOID *Data, u8 *pTxData, u32 Length );
HAL_STATUS (*HalRuartStopSend)( VOID *Data );
HAL_STATUS (*HalRuartGetC)( VOID *Data, u8 *pRxByte );
u32 (*HalRuartRecv)( VOID *Data, u8 *pRxData, u32 Length, u32 Timeout );
HAL_STATUS (*HalRuartIntRecv)( VOID *Data, u8 *pRxData, u32 Length );
HAL_STATUS (*HalRuartDmaRecv)( VOID *Data, u8 *pRxData, u32 Length );
HAL_STATUS (*HalRuartStopRecv)( VOID *Data );
u8 (*HalRuartGetIMR)( VOID *Data );
VOID (*HalRuartSetIMR)( VOID *Data );
u32 (*HalRuartGetDebugValue)( VOID *Data, u32 DbgSel );
VOID (*HalRuartDmaInit)( VOID *Data );
VOID (*HalRuartRTSCtrl)( VOID *Data, BOOLEAN RtsCtrl );
VOID (*HalRuartRegIrq)( VOID *Data );
VOID (*HalRuartIntEnable)( VOID *Data );
VOID (*HalRuartIntDisable)( VOID *Data );
} HAL_RUART_OP, *PHAL_RUART_OP;

typedef struct _RUART_DATA_
{
PHAL_RUART_ADAPTER pHalRuartAdapter;
BOOL PullMode;
u8 BinaryData;
u8 SendBuffer;
u8 RecvBuffer;
} RUART_DATA, *PRUART_DATA;

typedef struct _RUART_ADAPTER_
{
PHAL_RUART_OP pHalRuartOp;
PHAL_RUART_ADAPTER pHalRuartAdapter;
PUART_DMA_CONFIG pHalRuartDmaCfg;
} RUART_ADAPTER, *PRUART_ADAPTER;

extern VOID
HalRuartOpInit(
IN VOID *Data );

extern HAL_STATUS
HalRuartTxGdmaInit( PHAL_RUART_ADAPTER pHalRuartAdapter, PUART_DMA_CONFIG pUartGdmaConfig,
u8 IsMultiBlk );

extern VOID
HalRuartTxGdmaDeInit( PUART_DMA_CONFIG pUartGdmaConfig );

extern HAL_STATUS
HalRuartRxGdmaInit( PHAL_RUART_ADAPTER pHalRuartAdapter, PUART_DMA_CONFIG pUartGdmaConfig,
u8 IsMultiBlk );

extern VOID
HalRuartRxGdmaDeInit( PUART_DMA_CONFIG pUartGdmaConfig );

extern HAL_STATUS
HalRuartResetTxFifo(
VOID *Data );

extern HAL_STATUS
HalRuartResetRxFifo(
IN VOID *Data );

extern HAL_STATUS
HalRuartSetBaudRate(
IN VOID *Data );

extern HAL_STATUS
HalRuartInit(
IN VOID *Data );

extern VOID
HalRuartDeInit(
IN VOID *Data );

extern HAL_STATUS
HalRuartDisable(
IN VOID *Data );

extern HAL_STATUS
HalRuartEnable(
IN VOID *Data );

HAL_STATUS
HalRuartFlowCtrl(
IN VOID *Data );

VOID
HalRuartEnterCritical(
IN VOID *Data );

VOID
HalRuartExitCritical(
IN VOID *Data );

HAL_STATUS
HalRuartDmaSend(
IN VOID *Data, IN u8 *pTxBuf, IN u32 Length );

HAL_STATUS
HalRuartDmaRecv(
IN VOID *Data, IN u8 *pRxBuf, IN u32 Length );

extern const HAL_RUART_OP _HalRuartOp;
extern HAL_STATUS RuartLock( PHAL_RUART_ADAPTER pHalRuartAdapter );
extern VOID RuartUnLock( PHAL_RUART_ADAPTER pHalRuartAdapter );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_UART_H__ */
