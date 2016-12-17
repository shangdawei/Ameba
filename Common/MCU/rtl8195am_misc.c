#include "rtl8195am_misc.h"
#include "rtl8195am_timer.h"
#include "rtl8195am_diag.h"

#if !defined (__ICCARM__)
extern u8 RAM_IMG1_VALID_PATTEN[];
void *tmp = RAM_IMG1_VALID_PATTEN;
#endif

#if defined ( __ICCARM__ )
size_t __write(int Handle, const unsigned char * Buf, size_t Bufsize)
{
 	int nChars = 0;
 	/* Check for stdout and stderr
 	(only necessary if file descriptors are enabled.) */
 	if (Handle != 1 && Handle != 2)
 	{
 		return -1;
 	}
 	for (/*Empty */; Bufsize > 0; --Bufsize)
 	{
 		DiagPutChar(*Buf++);
 		++nChars;
 	}
 	return nChars;
}

size_t __read(int Handle, unsigned char * Buf, size_t Bufsize)
{
	int nChars = 0;
	/* Check for stdin
	(only necessary if FILE descriptors are enabled) */
	if (Handle != 0)
	{
		return -1;
	}
	for (/*Empty*/; Bufsize > 0; --Bufsize)
	{
		int c = DiagGetChar(_FALSE);
		if (c < 0)
			break;
		*(Buf++) = c;
		++nChars;
	}
	return nChars;
}

unsigned int rand_x = 123456789;

u32 Rand2( void )
{
  static unsigned int y = 362436;
  static unsigned int z = 521288629;
  static unsigned int c = 7654321;

  unsigned long long t, a = 698769069;

  rand_x = 69069 * rand_x + 12345;
  y ^= ( y << 13 );
  y ^= ( y >> 17 );
  y ^= ( y << 5 );
  t = a * z + c;
  c = ( t >> 32 );
  z = t;

  return rand_x + y + z;
}







extern BOOL
HalTimerInitRtl8195a(
    IN  VOID    *Data
);

VOID
PatchHalInitPlatformTimer(
VOID
)
{
    TIMER_ADAPTER       TimerAdapter;

    OSC32K_CKGEN_CTRL(ON);
    GTIMER_FCTRL(ON);
    ACTCK_TIMER_CCTRL(ON);
    SLPCK_TIMER_CCTRL(ON);

    TimerAdapter.IrqDis = ON;
//    TimerAdapter.IrqHandle = (IRQ_FUN)NULL;
    TimerAdapter.TimerId = 1;
    TimerAdapter.TimerIrqPriority = 0;
    TimerAdapter.TimerLoadValueUs = 0;
    TimerAdapter.TimerMode = FREE_RUN_MODE;

    HalTimerInitRtl8195a((VOID*) &TimerAdapter);

}

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


extern u32
HalLogUartInit(
    IN  LOG_UART_ADAPTER    UartAdapter
);

extern u32
HalGetCpuClk(
    VOID
);

const u32 StartupCpkClkTbl[]= {
    200000000,
    100000000,
    50000000,
    25000000,
    12500000,
    4000000
};


u32
StartupHalGetCpuClk(
    VOID
)
{
    u32  CpuType = 0, CpuClk = 0, FreqDown = 0;

    CpuType = ((HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_CLK_CTRL1) & (0x70)) >> 4);
    FreqDown = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) & BIT17;

    CpuClk = StartupCpkClkTbl[CpuType];

    if ( !FreqDown ) {
        if ( CpuClk > 4000000 ){
            CpuClk = (CpuClk*5/6);
        }
    }

    return CpuClk;
}

u32
PatchHalLogUartInit(
    IN  LOG_UART_ADAPTER    UartAdapter
)
{
    u32 SetData;
    u32 Divisor;
    u32 Dlh;
    u32 Dll;
    u32 SysClock;

    /*
        Interrupt enable Register
        7: THRE Interrupt Mode Enable
        2: Enable Receiver Line Status Interrupt
        1: Enable Transmit Holding Register Empty Interrupt
        0: Enable Received Data Available Interrupt
        */
    // disable all interrupts
    HAL_UART_WRITE32(UART_INTERRUPT_EN_REG_OFF, 0);

    /*
        Line Control Register
        7:   DLAB, enable reading and writing DLL and DLH register, and must be cleared after
        initial baud rate setup
        3:   PEN, parity enable/disable
        2:   STOP, stop bit
        1:0  DLS, data length
        */

    // set DLAB bit to 1
    HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF, 0x80);

    // set up buad rate division

#ifdef CONFIG_FPGA
    SysClock = SYSTEM_CLK;
    Divisor = (SysClock / (16 * (UartAdapter.BaudRate)));
#else
    {
        u32 SampleRate,Remaind;

        //SysClock = (HalGetCpuClk()>>2);
    SysClock = (StartupHalGetCpuClk()>>2);

        SampleRate = (16 * (UartAdapter.BaudRate));

        Divisor= SysClock/SampleRate;

        Remaind = ((SysClock*10)/SampleRate) - (Divisor*10);

        if (Remaind>4) {
            Divisor++;
        }
    }
#endif


    Dll = Divisor & 0xff;
    Dlh = (Divisor & 0xff00)>>8;
    HAL_UART_WRITE32(UART_DLL_OFF, Dll);
    HAL_UART_WRITE32(UART_DLH_OFF, Dlh);

    // clear DLAB bit
    HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF, 0);

    // set data format
    SetData = UartAdapter.Parity | UartAdapter.Stop | UartAdapter.DataLength;
    HAL_UART_WRITE32(UART_LINE_CTL_REG_OFF, SetData);

    /* FIFO Control Register
        7:6  level of receive data available interrupt
        5:4  level of TX empty trigger
        2    XMIT FIFO reset
        1    RCVR FIFO reset
        0    FIFO enable/disable
        */
    // FIFO setting, enable FIFO and set trigger level (2 less than full when receive
    // and empty when transfer
    HAL_UART_WRITE32(UART_FIFO_CTL_REG_OFF, UartAdapter.FIFOControl);

    /*
        Interrupt Enable Register
        7: THRE Interrupt Mode enable
        2: Enable Receiver Line status Interrupt
        1: Enable Transmit Holding register empty INT32
        0: Enable received data available interrupt
        */
    HAL_UART_WRITE32(UART_INTERRUPT_EN_REG_OFF, UartAdapter.IntEnReg);

    if (UartAdapter.IntEnReg) {
        // Enable Peripheral_IRQ Setting for Log_Uart
        HAL_WRITE32(VENDOR_REG_BASE, PERIPHERAL_IRQ_EN, 0x1000000);

        // Enable ARM Cortex-M3 IRQ
        NVIC_SetPriorityGrouping(0x3);
        NVIC_SetPriority(PERIPHERAL_IRQ, 14);
        NVIC_EnableIRQ(PERIPHERAL_IRQ);
    }


    return 0;
}

u32 log_uart_irq(VOID *Data)
{
  return 0;
}

VOID
PatchHalInitPlatformLogUart(
    VOID
)
{
    IRQ_HANDLE          UartIrqHandle;
    LOG_UART_ADAPTER    UartAdapter;

    //4 Release log uart reset and clock
    LOC_UART_FCTRL(OFF);
    LOC_UART_FCTRL(ON);
    ACTCK_LOG_UART_CCTRL(ON);

    PinCtrl(LOG_UART,S0,ON);

    //4 Register Log Uart Callback function
    UartIrqHandle.Data = (u32)NULL;//(u32)&UartAdapter;
    UartIrqHandle.IrqNum = UART_LOG_IRQ;
    UartIrqHandle.IrqFun = (IRQ_FUN) log_uart_irq;//UartLogIrqHandleRam;
    UartIrqHandle.Priority = 0;

    //4 Inital Log uart
    UartAdapter.BaudRate = UART_BAUD_RATE_38400;
    UartAdapter.DataLength = UART_DATA_LEN_8BIT;
    UartAdapter.FIFOControl = 0xC1;
    UartAdapter.IntEnReg = 0x00;
    UartAdapter.Parity = UART_PARITY_DISABLE;
    UartAdapter.Stop = UART_STOP_1BIT;

    //4 Initial Log Uart
    PatchHalLogUartInit(UartAdapter);

    //4 Register Isr handle
    InterruptRegister(&UartIrqHandle);

    UartAdapter.IntEnReg = 0x05;

    //4 Initial Log Uart for Interrupt
    PatchHalLogUartInit(UartAdapter);

    //4 initial uart log parameters before any uartlog operation
    //RtlConsolInit(ROM_STAGE,GetRomCmdNum(),(VOID*)&UartLogRomCmdTable);// executing boot seq.,
}
