#ifndef __RTL8195AM_TYPES_H__
#define __RTL8195AM_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic_types.h"

typedef uint32_t uint;
typedef int32_t sint;

typedef uint8_t BOOLEAN, *PBOOLEAN;

typedef uint32_t dma_addr_t;

typedef void (*proc_t)( void* );

typedef uint32_t __kernel_size_t;
typedef int32_t __kernel_ssize_t;

typedef __kernel_size_t SIZE_T;
typedef __kernel_ssize_t SSIZE_T;

typedef struct
{
  volatile int32_t counter;
} atomic_t;

typedef enum _RTK_STATUS_
{
  _EXIT_SUCCESS = 0,
  _EXIT_FAILURE = 1
} RTK_STATUS, *PRTK_STATUS;

//this part is adapted from linux (Linux/include/acpi/platform/acenv.h)
#ifndef va_arg

//this definition is in (Linux/include/acpi/actypes.h)
typedef int32_t acpi_native_int;

#ifndef _VALIST
#define _VALIST
typedef char *va_list;
#endif

// Storage alignment properties
#define  _AUPBND                (sizeof (acpi_native_int) - 1)
#define  _ADNBND                (sizeof (acpi_native_int) - 1)

// Variable argument list macro definitions
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)              (ap = (va_list) NULL)
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

#endif

typedef struct _RAM_START_FUNCTION_
{
  void (*RamStartFun)( void );
} RAM_START_FUNCTION, *PRAM_START_FUNCTION;

typedef struct _RAM_FUNCTION_START_TABLE_
{
  void (*RamStartFun)( void );
  void (*RamWakeupFun)( void );
  void (*RamPatchFun0)( void );
  void (*RamPatchFun1)( void );
  void (*RamPatchFun2)( void );
} RAM_FUNCTION_START_TABLE, *PRAM_FUNCTION_START_TABLE;

typedef enum _HAL_STATUS
{
  HAL_OK = 0x00,
  HAL_BUSY = 0x01,
  HAL_TIMEOUT = 0x02,
  HAL_ERR_PARA = 0x03,              // error with invaild parameters
  HAL_ERR_MEM = 0x04,               // error with memory allocation failed
  HAL_ERR_HW = 0x05,                // error with hardware error
  HAL_ERR_UNKNOWN = 0xee            // unknown error
} HAL_STATUS;

typedef enum _EFUSE_CPU_CLK_
{
  CLK_200M = 0,
  CLK_100M = 1,
  CLK_50M = 2,
  CLK_25M = 3,
  CLK_12_5M = 4,
  CLK_4M = 5,
  CPU_CLK_TYPE_NO = 6
} EFUSE_CPU_CLK;

typedef enum _BOOT_TYPE_
{
  BOOT_FROM_FLASH = 0,
  BOOT_FROM_SDIO = 1,
  BOOT_FROM_USB = 2,
  BOOT_FROM_RSVD = 3,
} BOOT_TYPE;

typedef enum _HAL_RESET_REASON
{
  REASON_DEFAULT_RST = 0,           // normal startup by power on
  REASON_WDT_RST,                   // hardware watch dog reset
  REASON_EXCEPTION_RST,             // exception reset, GPIO status won't change
  REASON_SOFT_WDT_RST,              // software watch dog reset, GPIO status won't change
  REASON_SOFT_RESTART,              // software restart ,system_restart , GPIO status won't change
  REASON_DEEP_SLEEP_AWAKE,          // wake up from deep-sleep
  REASON_EXT_SYS_RST                // external system reset
} HAL_RESET_REASON;

typedef enum _CONSOLE_OP_STAGE_
{
  ROM_STAGE = 0,
  RAM_STAGE = 1
} CONSOLE_OP_STAGE;

//UART LOG echo-function type.
typedef uint32_t (*ECHOFUNC)( uint8_t *, ... );

// Only 126 bytes could be used for keeping input cmd, the last byte is for string end ('\0').
// Must be not changed!
//
#define UART_LOG_CMD_BUFLEN         127
#define UART_LOG_HISTORY_LEN        5
#define MAX_ARGV                    10

typedef struct _UART_LOG_BUF_
{
  uint8_t BufCount;                             //record the input cmd char number.
  uint8_t UARTLogBuf[ UART_LOG_CMD_BUFLEN ];    //record the input command.
} UART_LOG_BUF, *PUART_LOG_BUF;

typedef struct _COMMAND_TABLE_
{
  const uint8_t* cmd;
  uint8_t ArgvCnt;
  uint32_t (*func)( uint8_t argc, uint8_t* argv[ ] );
  const uint8_t* msg;
} COMMAND_TABLE, *PCOMMAND_TABLE;

// Since ROM code will reference this typedef, so keep the typedef same size
// Must be not changed!
//
typedef struct _UART_LOG_CTL_
{
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

  uint32_t CRSTS;                                     // CONFIG_UART_LOG_HISTORY
  uint8_t (*pHistoryBuf)[ UART_LOG_CMD_BUFLEN ];      // CONFIG_UART_LOG_HISTORY
  uint32_t TaskRdy;                                   // CONFIG_KERNEL
  void * Sema;                                        // CONFIG_KERNEL : _Sema(FreeRTOS)
} UART_LOG_CTL, *PUART_LOG_CTL;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RTL8195AM_TYPES_H__
