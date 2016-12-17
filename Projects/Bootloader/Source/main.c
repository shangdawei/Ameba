#include "IAR_ICCARM_Define.h"

#include "cmsis_os2.h"
#include "rtl8195am.h"
#include <string.h>
#include <stdlib.h>

#include "rtl8195am_diag.h"
#include "rtl8195am_peri_on.h"

void HPTask( void * Arg )
{
  while ( 1 )
  {
    osDelay( 50 );
  }
}

void LPTask( void * Arg )
{
  while ( 1 )
  {
    osDelay( 200 );
  }
}

int main( void )
{
  DBG_SPIF_INFO( "%x", 0, 0 );

  UART2_BD_FCTRL(0);

  SystemCoreClockUpdate( );

  osKernelInitialize( );

  osThreadNew( LPTask, NULL, NULL );
  osThreadNew( HPTask, NULL, NULL );

  if ( osKernelGetState( ) == osKernelReady )
    osKernelStart( );

  while ( 1 )
  {
  }
}

