#include "rtl8195am.h"


#define SYSCLK_FREQ  166666666

uint32_t SystemCoreClock;

extern uint32_t __vector_table;

void SystemCoreClockSetup( void )
{

}

uint32_t SystemCoreClockGet( void )
{
  return SystemCoreClock;
}

void SystemInit( void )
{
  if ( !( CoreDebug->DEMCR &CoreDebug_DEMCR_TRCENA_Msk ))
  {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }

  SystemCoreClockSetup();

  SystemCoreClockUpdate();
#ifdef __DEBUG__
  SCB->VTOR = (uint32_t)&__vector_table;
#else
  SCB->VTOR = (uint32_t)&__vector_table;
#endif
}

void SystemCoreClockUpdate( void )
{
  SystemCoreClock = SYSCLK_FREQ;
}

void SystemDelayUs( uint32_t Us )
{
  int32_t Done = DWT->CYCCNT + Us * ( SystemCoreClock / 1000000 );
  while ( ( ( int32_t )DWT->CYCCNT - Done ) < 0 )
    ;
}
