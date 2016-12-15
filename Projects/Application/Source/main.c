#include "IAR_ICCARM_Define.h"

#include "cmsis_os2.h"
#include "rtl8195am.h"
#include <string.h>
#include <stdlib.h>

extern uint32_t UserIrqFunTable[32];
extern uint32_t __vectors_table;

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
  UserIrqFunTable[0] = __vectors_table;

  SystemCoreClockUpdate();

  osKernelInitialize();

  osThreadNew( LPTask, NULL, NULL );
  osThreadNew( HPTask, NULL, NULL );

  if ( osKernelGetState() == osKernelReady )
    osKernelStart();

  while ( 1 )
  {
  }
}

