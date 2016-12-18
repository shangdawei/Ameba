#ifndef __RTL8195AM_LOG_UART_H__
#define __RTL8195AM_LOG_UART_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

#define LOG_UART_WAIT_FOREVER               0xffffffff

// Define Line Control Register Bits
typedef enum
{
  LCR_DLS_5B = 0,                           // Data Length: 5 bits
  LCR_DLS_6B = BIT( 0 ),                    // Data Length: 6 bits
  LCR_DLS_7B = BIT( 1 ),                    // Data Length: 7 bits
  LCR_DLS_8B = ( BIT(1) | BIT( 0 ) ),       // Data Length: 7 bits
  LCR_STOP_1B = 0,                          // Number of stop bits: 1
  LCR_STOP_2B = BIT( 2 ),                   // Number of stop bits: 1.5(data len=5) or 2
  LCR_PARITY_NONE = 0,                      // Parity Enable: 0
  LCR_PARITY_ODD = BIT( 3 ),                // Parity Enable: 1, Even Parity: 0
  LCR_PARITY_EVEN = ( BIT(4) | BIT( 3 ) ),  // Parity Enable: 1, Even Parity: 1
  LCR_BC = BIT( 6 ),                        // Break Control Bit
  LCR_DLAB = BIT( 7 )                       // Divisor Latch Access Bit
} LOG_UART_LINE_CTRL;

/*
 IIR[3:0]:
 0000 = modem status
 0001 = no interrupt pending
 0010 = THR empty
 0100 = received data available
 0110 = receiver line status
 0111 = busy detect
 1100 = character timeout
 */
// define Log UART Interrupt Indication ID
typedef enum
{
  IIR_MODEM_STATUS = 0,  //Clear to send or data set ready or ring indicator or data carrier detect.
  IIR_NO_PENDING = 1,
  IIR_THR_EMPTY = 2,                        // TX FIFO level lower than threshold or FIFO empty
  IIR_RX_RDY = 4,                           // RX data ready
  IIR_RX_LINE_STATUS = 6,                   // Overrun/parity/framing errors or break interrupt
  IIR_BUSY = 7,
  IIR_CHAR_TIMEOUT = 12                     // timeout: Rx dara ready but no read
} LOG_UART_INT_ID;

// Define Interrupt Enable Bit
typedef enum
{
  IER_ERBFI = BIT( 0 ),                     // Enable Received Data Available Interrupt
  IER_ETBEI = BIT( 1 ),                     // Enable Transmit Holding Register Empty Interrupt
  IER_ELSI = BIT( 2 ),                      // Enable Receiver Line Status Interrupt
  IER_EDSSI = BIT( 3 ),                     // Enable Modem Status Interrupt
  IER_PTIME = BIT( 7 )                      // Programmable THRE Interrupt Mode Enable
} LOG_UART_INT_EN;

// Define Line Status Bit
typedef enum
{
  LSR_DR = BIT( 0 ),                        // Data Ready bit
  LSR_OE = BIT( 1 ),                        // Overrun error bit
  LSR_PE = BIT( 2 ),                        // Parity Error bit
  LSR_FE = BIT( 3 ),                        // Framing Error bit
  LSR_BI = BIT( 4 ),                        // Break Interrupt bit
  LSR_THRE = BIT( 5 ),                      // Transmit Holding Register Empty bit(IER_PTIME=0)
  LSR_FIFOF = BIT( 5 ),                     // Transmit FIFO Full bit(IER_PTIME=1)
  LSR_TEMT = BIT( 6 ),                      // Transmitter Empty bit
  LSR_RFE = BIT( 7 )                        // Receiver FIFO Error bit
} LOG_UART_LINE_STATUS;

enum
{
  LOG_UART_RST_TX_FIFO = 0x01,
  LOG_UART_RST_RX_FIFO = 0x02
};

#define LOG_UART_TX_FIFO_DEPTH      16
#define LOG_UART_RX_FIFO_DEPTH      16

// Define FIFO Control Register Bits
typedef enum
{
  FCR_FIFO_EN = BIT( 0 ),                     // FIFO Enable.
  FCR_RST_RX = BIT( 1 ),                      // RCVR FIFO Reset, self clear
  FCR_RST_TX = BIT( 2 ),                      // XMIT FIFO Reset, self clear
  FCR_TX_TRIG_EMP = 0,                        // TX Empty Trigger: FIFO empty
  FCR_TX_TRIG_2CH = BIT( 4 ),                 // TX Empty Trigger: 2 characters in the FIFO
  FCR_TX_TRIG_QF = BIT( 5 ),                  // TX Empty Trigger: FIFO 1/4 full
  FCR_TX_TRIG_HF = ( BIT(5) | BIT( 4 ) ),     // TX Empty Trigger: FIFO 1/2 full
  FCR_TX_TRIG_MASK = ( BIT(5) | BIT( 4 ) ),   // TX Empty Trigger Bit Mask
  FCR_RX_TRIG_1CH = 0,                        // RCVR Trigger: 1 character in the FIFO
  FCR_RX_TRIG_QF = BIT( 6 ),                  // RCVR Trigger: FIFO 1/4 full
  FCR_RX_TRIG_HF = BIT( 7 ),                  // RCVR Trigger: FIFO 1/2 full
  FCR_RX_TRIG_AF = ( BIT(7) | BIT( 6 ) ),     // RCVR Trigger: FIFO 2 less than full
  FCR_RX_TRIG_MASK = ( BIT(7) | BIT( 6 ) )    // RCVR Trigger bits Mask
} LOG_UART_FIFO_CTRL;

typedef struct _HAL_LOG_UART_ADAPTER_
{
  u32 BaudRate;
  u32 FIFOControl;
  u32 IntEnReg;
  u8 Parity;
  u8 Stop;
  u8 DataLength;

  u8 LineStatus;
  volatile u32 TxCount;                     // how many byte to TX
  volatile u32 RxCount;                     // how many bytes to RX
  volatile u8 *pTxBuf;
  volatile u8 *pRxBuf;
  u8 *pTxStartAddr;
  u8 *pRxStartAddr;

  IRQ_HANDLE IrqHandle;
  void (*LineStatusCallback)( void *para, u8 status );    // User Line Status interrupt callback
  void (*TxCompCallback)( void *para );                   // User Tx complete callback
  void (*RxCompCallback)( void *para );                   // User Rx complete callback
  void *LineStatusCbPara;                                 // the argument for LineStatusCallback
  void *TxCompCbPara;                                     // the argument for TxCompCallback
  void *RxCompCbPara;                                     // the argument for RxCompCallback

  void (*api_irq_handler)( u32 id, LOG_UART_INT_ID event );
  u32 api_irq_id;
} HAL_LOG_UART_ADAPTER, *PHAL_LOG_UART_ADAPTER;

void HalLogUartIrqHandle( void * Data );
void HalLogUartSetBaudRate( HAL_LOG_UART_ADAPTER *pUartAdapter );
void HalLogUartSetLineCtrl( HAL_LOG_UART_ADAPTER *pUartAdapter );
void HalLogUartSetIntEn( HAL_LOG_UART_ADAPTER *pUartAdapter );
u32 HalLogUartInitSetting( HAL_LOG_UART_ADAPTER *pUartAdapter );
u32 HalLogUartRecv( HAL_LOG_UART_ADAPTER *pUartAdapter, u8 *pRxData, u32 Length, u32 TimeoutMS );
u32 HalLogUartSend( HAL_LOG_UART_ADAPTER *pUartAdapter, u8 *pTxData, u32 Length, u32 TimeoutMS );
HAL_STATUS HalLogUartIntSend( HAL_LOG_UART_ADAPTER *pUartAdapter, u8 *pTxData, u32 Length );
HAL_STATUS HalLogUartIntRecv( HAL_LOG_UART_ADAPTER *pUartAdapter, u8 *pRxData, u32 Length );
void HalLogUartAbortIntSend( HAL_LOG_UART_ADAPTER *pUartAdapter );
void HalLogUartAbortIntRecv( HAL_LOG_UART_ADAPTER *pUartAdapter );
HAL_STATUS HalLogUartRstFIFO( HAL_LOG_UART_ADAPTER *pUartAdapter, u8 RstCtrl );
void HalLogUartEnable( HAL_LOG_UART_ADAPTER *pUartAdapter );
void HalLogUartDisable( HAL_LOG_UART_ADAPTER *pUartAdapter );

typedef struct _LOG_UART_ADAPTER_
{
  u32 BaudRate;
  u32 FIFOControl;
  u32 IntEnReg;
  u8 Parity;
  u8 Stop;
  u8 DataLength;
} LOG_UART_ADAPTER, *PLOG_UART_ADAPTER;

extern _LONG_CALL_ROM_ u32 HalLogUartInit( IN LOG_UART_ADAPTER UartAdapter );

void HalLogUartHandle( void );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_LOG_UART_H__ */
