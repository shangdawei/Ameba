#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_macro.h"

//#define __SYSTEM_CLOCK            ( 5*__XTAL )
#define __SYSTEM_CLOCK              ( 200000000UL/6*5)    /* System Core frequency : 166,666,667 */
#define __HSI                       ( 8000000UL)
#define __XTAL                      ( 5000000UL)          /* Oscillator frequency */

#define SYSCLK_FREQ                 SYSTEM_CLK

uint32_t SystemCoreClock = __SYSTEM_CLOCK;

extern uint32_t __vector_table;

extern u32 HalGetCpuClk( VOID );

#if ( CONFIG_CHIP_X_CUT == CONFIG_CHIP_A_CUT )
#endif
const u32 SysCpkClkTbl[ ] = {
  200000000, 100000000, 50000000, 25000000, 12500000, 4000000 };

void SystemCoreClockSetup( uint32_t NewSystemCoreClock )
{
  // ToDo
  SystemCoreClock = NewSystemCoreClock;
}

uint32_t SystemCoreClockGet( void )
{
#if ( CONFIG_CHIP_X_CUT == CONFIG_CHIP_A_CUT )

  u32 CpuType = 0, CpuClk = 0, FreqDown = 0;

  CpuType = ( ( HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_CLK_CTRL1) & ( 0x70 ) ) >> 4 );
  FreqDown = HAL_READ32(SYSTEM_CTRL_BASE, REG_SYS_SYSPLL_CTRL1) & BIT17;

  CpuClk = SysCpkClkTbl[ CpuType ];

  if ( !FreqDown )
  {
    if ( CpuClk > 4000000 )
    {
      CpuClk = ( CpuClk * 5 / 6 );
    }
  }

  return CpuClk;
#else
  return HalGetCpuClk( );
#endif
}

void SystemInit( void )
{
  if ( !( CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk ) )
  {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }

#ifdef __DEBUG__
  SCB->VTOR = (uint32_t)&__vector_table;
#else
  SCB->VTOR = (uint32_t) &__vector_table;
#endif
}

void SystemCoreClockUpdate( void )
{
  SystemCoreClock = SystemCoreClockGet( );
}

void SystemDelayUs( uint32_t Us )
{
  int32_t Done = DWT->CYCCNT + Us * ( SystemCoreClock / 1000000 );
  while ( ( (int32_t) DWT->CYCCNT - Done ) < 0 )
    ;
}

// Used for Debug In RAM to Simulate ROMLoader/Bootloader
// ToDo Exract everyting from ROMLoader
void SystemPrepare( void )
{

}








#if defined (CONFIG_USB_EN) && defined(CONFIG_USB_HOST_ONLY)
  extern void _usb_init( void );
#endif

#if defined(CONFIG_SDIO_DEVICE_EN) && defined(CONFIG_SDIO_DEVICE_NORMAL)
  extern VOID HalSdioInit( VOID );
#endif

#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
  extern void init_rom_wlan_ram_map( void );
  extern VOID wlan_network( VOID );
#endif

//3 Monitor App Function
extern VOID RtlConsolInitRam( u32 Boot, u32 TBLSz, VOID * pTBL );
#ifndef CONFIG_KERNEL
  extern VOID RtlConsolTaskRom( VOID * Data );
#endif

#ifndef CONFIG_WITHOUT_MONITOR
  extern COMMAND_TABLE    UartLogRamCmdTable[];
  extern u32 GetRamCmdNum( VOID );
  extern VOID UartLogIrqHandleRam( VOID * Data );
#endif

#ifdef CONFIG_APP_DEMO
  #define MAIN_APP_DEFAULT_STACK_SIZE         2048
  #define MAIN_APP_DEFAULT_PRIORITY           (tskIDLE_PRIORITY + 1)
#endif

#ifdef CONFIG_MBED_ENABLED
  extern void __libc_fini_array ( void );
  extern void __libc_init_array ( void );
  extern  void SVC_Handler ( void );
  extern  void PendSV_Handler ( void );
  extern  void SysTick_Handler ( void );
#endif

#ifndef CONFIG_WITHOUT_MONITOR
static
VOID
ReRegisterPlatformLogUart(
  VOID
)
{
  IRQ_HANDLE          UartIrqHandle;
  //4 Register Log Uart Callback function
  UartIrqHandle.Data = ( u32 )NULL; //(u32)&UartAdapter;
  UartIrqHandle.IrqNum = UART_LOG_IRQ;
  UartIrqHandle.IrqFun = ( IRQ_FUN ) UartLogIrqHandleRam;
  UartIrqHandle.Priority = 5;
  //4 Register Isr handle
  InterruptUnRegister( &UartIrqHandle );
  InterruptRegister( &UartIrqHandle );
#if !TASK_SCHEDULER_DISABLED
  RtlConsolInitRam( ( u32 )RAM_STAGE, ( u32 )GetRamCmdNum(), ( VOID * )&UartLogRamCmdTable );
#else
  RtlConsolInitRam( ( u32 )ROM_STAGE, ( u32 )GetRamCmdNum(), ( VOID * )&UartLogRamCmdTable );
#endif
}
#endif  // end of "#ifndef CONFIG_WITHOUT_MONITOR"


VOID ShowRamBuildInfo( VOID )
{
  /*
  DBG_8195A("=========================================================\n\n");
  //DBG_8195A("Build Time: "UTS_VERSION"\n");
  DBG_8195A("Build Time: "RTL8195AFW_COMPILE_TIME"\n");
  DBG_8195A("Build Author: "RTL8195AFW_COMPILE_BY"\n");
  DBG_8195A("Build Host: "RTL8195AFW_COMPILE_HOST"\n");
  DBG_8195A("Build ToolChain Version: "RTL195AFW_COMPILER"\n\n");
  DBG_8195A("=========================================================\n");
  */
}

#ifdef CONFIG_APP_DEMO
#include "device.h"
#include "gpio_api.h"   // mbed

_WEAK int main( void )
{
  gpio_t gpio_led;
#ifndef CONFIG_WITHOUT_MONITOR
  ReRegisterPlatformLogUart();
#endif
  // Init LED control pin
  gpio_init( &gpio_led, PC_5 );
  gpio_dir( &gpio_led, PIN_OUTPUT );  // Direction: Output
  gpio_mode( &gpio_led, PullNone );   // No pull

  while( 1 )
  {
    gpio_write( &gpio_led, !gpio_read( &gpio_led ) );
    RtlMsleepOS( 1000 );
  }

  return 0;
}
#else
//default main
_WEAK int main( void )
{
  // Init SDIO
#if defined(CONFIG_SDIO_DEVICE_EN) && defined(CONFIG_SDIO_DEVICE_NORMAL)
  HalSdioInit();
#endif
#ifndef CONFIG_WITHOUT_MONITOR
  ReRegisterPlatformLogUart();
#endif
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
  wlan_network();
#else
#if defined (CONFIG_USB_EN) && defined(CONFIG_USB_HOST_ONLY)
  _usb_init();
#endif
#endif  // end of else of "#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)"
  //3 4)Enable Schedule
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
#ifdef PLATFORM_FREERTOS
  vTaskStartScheduler();
#endif
#else
  RtlConsolTaskRom( NULL );
#endif
  return 0;
}
#endif // end of #if CONFIG_APP_DEMO

__weak void __low_level_init( void )
{
  // weak function
}

#if defined ( __ICCARM__ )
  #pragma section="SDRAM.bss"
  #pragma section="SDRAM.bss"
#endif
// The Main App entry point
void _AppStart( void )
{
#ifdef CONFIG_MBED_ENABLED
  InterruptForOSInit( ( VOID * )SVC_Handler,
                      ( VOID * )PendSV_Handler,
                      ( VOID * )SysTick_Handler );
  __asm (
    "ldr   r0, =SystemInit\n"
    "blx   r0\n"
    "ldr   r0, =_start\n"
    "bx    r0\n"
  );

  for( ;; );

#else
  // It's Not Mbed BSP
#ifdef CONFIG_KERNEL
#endif
  // Disable debug info log of spiflash
  DBG_INFO_MSG_OFF( _DBG_SPI_FLASH_ );
#ifdef CONFIG_APP_DEMO
#ifdef PLATFORM_FREERTOS
  xTaskCreate( ( TaskFunction_t )main, "MAIN_APP__TASK", ( MAIN_APP_DEFAULT_STACK_SIZE / 4 ),
               ( void * )NULL, MAIN_APP_DEFAULT_PRIORITY, NULL );
  vTaskStartScheduler();
#endif
#else
  __low_level_init();
#if defined ( __ICCARM__ )
  // __iar_data_init3 replaced by __iar_cstart_call_ctors, just do c++ constructor,
  __iar_cstart_call_ctors( NULL );
  // clear SDRAM bss
  u8 * __sdram_bss_start__   = ( u8 * )__section_begin( "SDRAM.bss" );
  u8 * __sdram_bss_end__     = ( u8 * )__section_end( "SDRAM.bss" );

  //DiagPrintf("clean sdram bss %8x to %8x\n\r", __sdram_bss_start__, __sdram_bss_end__);
  if( ( int )__sdram_bss_end__ - ( int )__sdram_bss_start__ > 0 )
    memset( __sdram_bss_start__, 0, ( int )__sdram_bss_end__ - ( int )__sdram_bss_start__ );

#elif defined ( __GNUC__ )
  // clear SDRAM bss
  extern u8 __sdram_bss_start__[];
  extern u8 __sdram_bss_end__[];

  //DiagPrintf("clean sdram bss %8x to %8x\n\r", __sdram_bss_start__, __sdram_bss_end__);
  if( ( int )__sdram_bss_end__ - ( int )__sdram_bss_start__ > 0 )
    memset( __sdram_bss_start__, 0, ( int )__sdram_bss_end__ - ( int )__sdram_bss_start__ );

#else
#error !!!!!!NOT Support this compiler!!!!!!
#endif
  // force SP align to 8 byte not 4 byte (initial SP is 4 byte align)
  __asm(
    "mov r0, sp\n"
    "bic r0, r0, #7\n"
    "mov sp, r0\n"
  );
  main();
#if defined ( __ICCARM__ )
  // for compile issue, If user never call this function, Liking fail
  __iar_data_init3();
#endif
#endif // end of #if CONFIG_APP_DEMO
#endif  // end of else of "#ifdef CONFIG_MBED_ENABLED"
}
