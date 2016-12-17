#include "rtl8195am_consol.h"
#include "rtl8195am_section.h"

// =================================================================================================
//
extern volatile UART_LOG_CTL UartLogCtl;                                           // 0x10000384
extern volatile UART_LOG_BUF UartLogBuf;                                           // 0x100003ac
extern uint8_t UartLogHistoryBuf[ UART_LOG_HISTORY_LEN ][ UART_LOG_CMD_BUFLEN ];   // 0x1000042c
extern volatile UART_LOG_CTL *pUartLogCtl;                                         // 0x100006a8
extern uint8_t *ArgvArray[ MAX_ARGV ];                                             // 0x100006ac

// =================================================================================================
//
_LONG_CALL_ extern uint8_t UartLogCmdChk( IN uint8_t RevData, IN UART_LOG_CTL *prvUartLogCtl,
  IN uint8_t EchoFlag );
_LONG_CALL_ extern void UartLogCmdExecute( IN PUART_LOG_CTL pUartLogCtlExe );
_LONG_CALL_ extern void ArrayInitialize( IN uint8_t *pArrayToInit, IN uint8_t ArrayLen,
  IN uint8_t InitValue );
_LONG_CALL_ extern void UartLogHistoryCmd( IN uint8_t RevData, IN UART_LOG_CTL *prvUartLogCtl,
  IN uint8_t EchoFlag );

//======================================================
//<Function>:  UartLogIrqHandleRam
//<Usage   >:  To deal with Uart-Log RX IRQ
//<Argus    >:  void
//<Return   >:  void
//<Notes    >:  NA
//======================================================
MON_RAM_TEXT_SECTION
void UartLogIrqHandleRam( void * Data )
{
  uint8_t UartReceiveData = 0;
  //For Test
  BOOL PullMode = _FALSE;

  u32 IrqEn = DiagGetIsrEnReg( );

  DiagSetIsrEnReg( 0 );

  UartReceiveData = DiagGetChar( PullMode );
  if ( UartReceiveData == 0 )
  {
    goto exit;
  }

  //KB_ESC chk is for cmd history, it's a special case here.
  if ( UartReceiveData == KB_ASCII_ESC )
  {
    //4 Esc detection is only valid in the first stage of boot sequence (few seconds)
    if ( pUartLogCtl->ExecuteEsc != _TRUE )
    {
      pUartLogCtl->ExecuteEsc = _TRUE;
      ( *pUartLogCtl ).EscSTS = 0;
    }
    else
    {
      //4 the input commands are valid only when the task is ready to execute commands
      if ( ( pUartLogCtl->BootRdy == 1 )
#ifdef CONFIG_KERNEL
        || ( pUartLogCtl->TaskRdy == 1 )
#endif
        )
      {
        if ( ( *pUartLogCtl ).EscSTS == 0 )
        {
          ( *pUartLogCtl ).EscSTS = 1;
        }
      }
      else
      {
        ( *pUartLogCtl ).EscSTS = 0;
      }
    }
  }
  else if ( ( *pUartLogCtl ).EscSTS == 1 )
  {
    if ( UartReceiveData != KB_ASCII_LBRKT )
    {
      ( *pUartLogCtl ).EscSTS = 0;
    }
    else
    {
      ( *pUartLogCtl ).EscSTS = 2;
    }
  }

  else
  {
    if ( ( *pUartLogCtl ).EscSTS == 2 )
    {
      ( *pUartLogCtl ).EscSTS = 0;
#ifdef CONFIG_UART_LOG_HISTORY
      if ( ( UartReceiveData == 'A' ) || UartReceiveData == 'B' )
      {
        UartLogHistoryCmd( UartReceiveData, (UART_LOG_CTL *) pUartLogCtl, 1 );
      }
#endif
    }
    else
    {
      if ( UartLogCmdChk( UartReceiveData, (UART_LOG_CTL *) pUartLogCtl, 1 ) == 2 )
      {
        //4 check UartLog buffer to prevent from incorrect access
        if ( pUartLogCtl->pTmpLogBuf != NULL )
        {
          pUartLogCtl->ExecuteCmd = _TRUE;
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
          if ( pUartLogCtl->TaskRdy )
            RtlUpSemaFromISR( (_Sema *) &pUartLogCtl->Sema );
#endif
        }
        else
        {
          ArrayInitialize( (uint8_t *) pUartLogCtl->pTmpLogBuf->UARTLogBuf, UART_LOG_CMD_BUFLEN,
            '\0' );
        }
      }
    }
  }
  exit: DiagSetIsrEnReg( IrqEn );

}

MON_RAM_TEXT_SECTION
void RtlConsolInitRam( IN u32 Boot, IN u32 TBLSz, IN void *pTBL )
{
  UartLogBuf.BufCount = 0;
  ArrayInitialize( &UartLogBuf.UARTLogBuf[ 0 ], UART_LOG_CMD_BUFLEN, '\0' );
  pUartLogCtl = &UartLogCtl;

  pUartLogCtl->NewIdx = 0;
  pUartLogCtl->SeeIdx = 0;
  pUartLogCtl->RevdNo = 0;
  pUartLogCtl->EscSTS = 0;
  pUartLogCtl->BootRdy = 0;
  pUartLogCtl->pTmpLogBuf = &UartLogBuf;
#ifdef CONFIG_UART_LOG_HISTORY
  pUartLogCtl->CRSTS = 0;
  pUartLogCtl->pHistoryBuf = &UartLogHistoryBuf[ 0 ];
#endif
  pUartLogCtl->pfINPUT = (void*) &DiagPrintf;
  pUartLogCtl->pCmdTbl = (PCOMMAND_TABLE) pTBL;
  pUartLogCtl->CmdTblSz = TBLSz;
#ifdef CONFIG_KERNEL
  pUartLogCtl->TaskRdy = 0;
#endif
  //executing boot sequence
  if ( Boot == ROM_STAGE )
  {
    pUartLogCtl->ExecuteCmd = _FALSE;
    pUartLogCtl->ExecuteEsc = _FALSE;
  }
  else
  {
    pUartLogCtl->ExecuteCmd = _FALSE;
    pUartLogCtl->ExecuteEsc = _TRUE;                                       //don't check Esc anymore
#if defined(CONFIG_KERNEL)
    /* Create a Semaphone */
    RtlInitSema( (_Sema*) &( pUartLogCtl->Sema ), 0 );
    pUartLogCtl->TaskRdy = 0;
#ifdef PLATFORM_FREERTOS
#define	LOGUART_STACK_SIZE	128 //USE_MIN_STACK_SIZE modify from 512 to 128
#if CONFIG_USE_TCM_HEAP
    {
      int ret = 0;
      void *stack_addr = tcm_heap_malloc(LOGUART_STACK_SIZE*sizeof(int));
      //void *stack_addr = rtw_malloc(stack_size*sizeof(int));
      if(stack_addr == NULL)
      {
        DiagPrintf("Out of TCM heap in \"LOGUART_TASK\" ");
      }
      ret = xTaskGenericCreate(
          RtlConsolTaskRam,
          (const char *)"LOGUART_TASK",
          LOGUART_STACK_SIZE,
          NULL,
          tskIDLE_PRIORITY + 5 + PRIORITIE_OFFSET,
          NULL,
          stack_addr,
          NULL);
      if (pdTRUE != ret)
      {
        DiagPrintf("Create Log UART Task Err!!\n");
      }
    }
#else
    if ( pdTRUE != xTaskCreate( RtlConsolTaskRam, (const signed char * const ) "LOGUART_TASK",
    LOGUART_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5 + PRIORITIE_OFFSET, NULL ) )
    {
      DiagPrintf( "Create Log UART Task Err!!\n" );
    }
#endif

#endif

#endif
  }

  CONSOLE_8195A( );
}

extern uint8_t** GetArgv( const uint8_t *string );
#if SUPPORT_LOG_SERVICE
extern char log_buf[LOG_SERVICE_BUFLEN];
extern xSemaphoreHandle log_rx_interrupt_sema;
#endif
//======================================================
void console_cmd_exec( PUART_LOG_CTL pUartLogCtlExe )
{
  uint8_t CmdCnt = 0;
  uint8_t argc = 0;
  uint8_t **argv;
  //u32  CmdNum;
  PUART_LOG_BUF pUartLogBuf = pUartLogCtlExe->pTmpLogBuf;
#if SUPPORT_LOG_SERVICE
  strncpy(log_buf, (const uint8_t*)&(*pUartLogBuf).UARTLogBuf[0], LOG_SERVICE_BUFLEN-1);
#endif
  argc = GetArgc( (const uint8_t*) &( ( *pUartLogBuf ).UARTLogBuf[ 0 ] ) );
  argv = GetArgv( (const uint8_t*) &( ( *pUartLogBuf ).UARTLogBuf[ 0 ] ) );

  if ( argc > 0 )
  {
#if SUPPORT_LOG_SERVICE
//		if(log_handler(argv[0]) == NULL)
//			legency_interactive_handler(argc, argv);
    RtlUpSema((_Sema *)&log_rx_interrupt_sema);
#endif
    ArrayInitialize( argv[ 0 ], sizeof( argv[ 0 ] ), 0 );
  }
  else
  {
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
    acquire_wakelock(WAKELOCK_LOGUART);
#endif
    CONSOLE_8195A( ); // for null command
  }

  ( *pUartLogBuf ).BufCount = 0;
  ArrayInitialize( &( *pUartLogBuf ).UARTLogBuf[ 0 ], UART_LOG_CMD_BUFLEN, '\0' );
}
//======================================================
// overload original RtlConsolTaskRam
MON_RAM_TEXT_SECTION
void RtlConsolTaskRam( void *Data )
{
#if SUPPORT_LOG_SERVICE
  log_service_init();
#endif
  //4 Set this for UartLog check cmd history
#ifdef CONFIG_KERNEL
  pUartLogCtl->TaskRdy = 1;
#endif
#ifndef CONFIG_KERNEL
  pUartLogCtl->BootRdy = 1;
#endif
  do
  {
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
    RtlDownSema( (_Sema *) &pUartLogCtl->Sema );
#endif
    if ( pUartLogCtl->ExecuteCmd )
    {
      // Add command handler here
      console_cmd_exec( (PUART_LOG_CTL) pUartLogCtl );
      //UartLogCmdExecute((PUART_LOG_CTL)pUartLogCtl);
      pUartLogCtl->ExecuteCmd = _FALSE;
    }
  }
  while ( 1 );
}

//======================================================
void console_init( void )
{
  IRQ_HANDLE UartIrqHandle;

  //4 Register Log Uart Callback function
  UartIrqHandle.Data = NULL; //(u32)&UartAdapter;
  UartIrqHandle.IrqNum = UART_LOG_IRQ;
  UartIrqHandle.IrqFun = (IRQ_FUN) UartLogIrqHandleRam;
  UartIrqHandle.Priority = 0;

  //4 Register Isr handle
  InterruptUnRegister( &UartIrqHandle );
  InterruptRegister( &UartIrqHandle );
#if !TASK_SCHEDULER_DISABLED
  RtlConsolInitRam( (u32) RAM_STAGE, (u32) 0, (void*) NULL );
#else
  RtlConsolInitRam((u32)ROM_STAGE,(u32)0,(void*)NULL);
#endif
}

