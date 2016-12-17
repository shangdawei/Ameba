#if (1)

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>


#define MAX_ARGV 10

#define UART_LOG_CMD_BUFCNT           ( 5 )
#define UART_LOG_CMD_BUFLEN           ( 127 )

// platform_autoconf.h
#define CONFIG_UART_LOG_HISTORY       ( 1 )

typedef struct _COMMAND_TABLE_ {
 const uint8_t* cmd;
 uint16_t ArgvCnt;
 uint32_t (*func)(uint16_t argc, uint8_t* argv[]);
 const uint8_t* msg;
}COMMAND_TABLE, *PCOMMAND_TABLE;

typedef struct _UART_LOG_BUF_
{
   uint8_t BufCount;
   uint8_t UARTLogBuf[ UART_LOG_CMD_BUFLEN ];
} UART_LOG_BUF, * PUART_LOG_BUF;


typedef struct _UART_LOG_CTL_ {
  uint8_t NewIdx;
  uint8_t SeeIdx;
  uint8_t RevdNo;
  uint8_t EscSTS;
  uint8_t ExecuteCmd;
  uint8_t ExecuteEsc;
  uint8_t BootRdy;
  uint8_t Resvd;
  PUART_LOG_BUF pTmpLogBuf;
  void *pfINPUT;
  PCOMMAND_TABLE pCmdTbl;
  uint32_t CmdTblSz;

  #ifdef CONFIG_UART_LOG_HISTORY
  uint32_t CRSTS;
  #endif

  #ifdef CONFIG_UART_LOG_HISTORY
  uint8_t (*pHistoryBuf)[UART_LOG_CMD_BUFLEN];
  #endif

  #ifdef CONFIG_KERNEL
  uint32_t		TaskRdy;
  _Sema	Sema;
  #else
  uint32_t TaskRdy;
  void *Sema;
  #endif

} UART_LOG_CTL, *PUART_LOG_CTL;

// #pragma location=0x10000384
// #pragma section=".mon.ram.bss"
_Pragma( "location=\".mon.ram.bss\"")
__root volatile UART_LOG_CTL UartLogCtl ;

// #pragma section=".mon.ram.bss"
// #pragma location=0x100003ac
_Pragma( "location=\".mon.ram.bss\"")
__root volatile UART_LOG_BUF UartLogBuf ;

// #pragma section=".mon.ram.bss"
// #pragma location=0x1000042c
_Pragma( "location=\".mon.ram.bss\"")
__root volatile uint8_t UartLogHistoryBuf[UART_LOG_CMD_BUFCNT][UART_LOG_CMD_BUFLEN] ;

// #pragma section=".mon.ram.bss"
// #pragma location=0x100006a8
_Pragma( "location=\".mon.ram.bss\"")
__root volatile UART_LOG_CTL *pUartLogCtl;

// #pragma section=".mon.ram.bss"
// #pragma location=0x100006ac
_Pragma( "location=\".mon.ram.bss\"")
__root volatile uint8_t *ArgvArray[MAX_ARGV] ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

int __dummy_entry__()
{
  return 0;
}
