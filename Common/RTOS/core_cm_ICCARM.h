/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       Cortex-M Core definitions
 *
 * -----------------------------------------------------------------------------
 */

#ifndef __CORE_CM_ICCARM_H__
#define __CORE_CM_ICCARM_H__

#include "rtl8195am.h"

// -----------------------------------------------------------------------------
#define __TEST_ONLY__           0U
// -----------------------------------------------------------------------------

#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

#ifndef __INLINE_FORCED
#define __INLINE_FORCED         _Pragma( STRINGIFY(inline=forced) )
#endif

#ifdef    __STATIC_INLINE
#undef  __STATIC_INLINE
#define __STATIC_INLINE         static
#endif

// #pragma diag_suppress=Pe550

/*
 __ARM4TM__, __ARM5__, __ARM5E__     : ARM7 ARM9
 __ARM6__, __ARM6M__, __ARM6SM__     : Cortex-M0
 __ARM7M__, __ARM7EM__               : Cortex-M3 Cortex-M4
 __ARM7A__, or __ARM7R___            : Cortex-A  Cortex-R
 */

#if (__CORE__ == __ARM6M__  )
#define __ARM_ARCH_6M__         1U
#elif (__CORE__ == __ARM7M__  )
#define __ARM_ARCH_7M__         1U
#elif (__CORE__ == __ARM7EM__  )
#define __ARM_ARCH_7EM__        1U
#endif

#if ( __TEST_ONLY__ > 0  )

#undef __ARM_ARCH_6M__
#undef __ARM_ARCH_7M__
#undef __ARM_ARCH_7EM__
#undef __FPU_USED
#undef __CORTEX_M

#define __ARM_ARCH_7M__         1U
#define __CORTEX_M              3U
#define __FPU_USED              1U

#endif

#ifndef __ARM_ARCH_6M__
#define __ARM_ARCH_6M__         0U
#endif
#ifndef __ARM_ARCH_7M__
#define __ARM_ARCH_7M__         0U
#endif
#ifndef __ARM_ARCH_7EM__
#define __ARM_ARCH_7EM__        0U
#endif
#ifndef __ARM_ARCH_8M_BASE__
#define __ARM_ARCH_8M_BASE__    0U
#endif
#ifndef __ARM_ARCH_8M_MAIN__
#define __ARM_ARCH_8M_MAIN__    0U
#endif

// -----------------------------------------------------------------------------

#if ((__ARM_ARCH_6M__ + __ARM_ARCH_7M__ + __ARM_ARCH_7EM__ + __ARM_ARCH_8M_BASE__ + __ARM_ARCH_8M_MAIN__) != 1U)
#error "Unknown ARM Architecture!"
#endif

#ifdef RTE_CMSIS_RTOS2_RTX5_ARMV8M_NS
#define __DOMAIN_NS             1U
#endif

#ifndef __DOMAIN_NS
#define __DOMAIN_NS             0U
#elif ((__DOMAIN_NS == 1U) && ((__ARM_ARCH_6M__ == 1U) || (__ARM_ARCH_7M__ == 1U) || (__ARM_ARCH_7EM__ == 1U)))
#error "Non-secure domain requires ARMv8-M Architecture!"
#endif

#ifndef __EXCLUSIVE_ACCESS
#if ((__ARM_ARCH_7M__ == 1U) || (__ARM_ARCH_7EM__ == 1U) || (__ARM_ARCH_8M_BASE__ == 1U) || (__ARM_ARCH_8M_MAIN__ == 1U))
#define __EXCLUSIVE_ACCESS      1U
#else
#define __EXCLUSIVE_ACCESS      0U
#endif
#endif

#define IS_PRIVILEGED()         ((__get_CONTROL() & 1U) == 0U)

#define IS_IRQ_MODE()           (__get_IPSR() != 0U)

#if ((__ARM_ARCH_7M__ == 1U) || (__ARM_ARCH_7EM__ == 1U) || (__ARM_ARCH_8M_MAIN__ == 1U))
#define IS_IRQ_MASKED()         ((__get_PRIMASK() != 0U) || (__get_BASEPRI() != 0U))
#else
#define IS_IRQ_MASKED()         (__get_PRIMASK() != 0U)
#endif

#define XPSR_INITIAL_VALUE      0x01000000U

#if    (__DOMAIN_NS == 1U)
#define STACK_FRAME_INIT        0xBCU
#else
#define STACK_FRAME_INIT        0xFDU
#endif

#define IS_EXTENDED_STACK_FRAME(n) (((n) & 0x10U) == 0U)

//  ==== Service Calls definitions ====

#if ((__ARM_ARCH_7M__ == 1U) || (__ARM_ARCH_7EM__ == 1U) || (__ARM_ARCH_8M_MAIN__ == 1U))

// #define SVC_RegF "r12"
#define SVC_ArgF(f)               \
register uint32_t __rf;           \
__ASM("MOV %0, %0"                \
      : "=r"(__rf) );             \
__ASM("MOV r12, %0"               \
      : : "r" (f) )

// #define SVC_RegF "r7"
#elif ((__ARM_ARCH_6M__ == 1U) || (__ARM_ARCH_8M_BASE__ == 1U))

#define SVC_ArgF(f)               \
register uint32_t __rf;           \
__ASM("MOV %0, %0"                \
      : "=r"(__rf) );             \
__ASM("MOV r7, %0"                \
      : : "r" (f) )

#endif

#define SVC_ArgN(n)               \
register uint32_t __r##n

#define SVC_ArgR(n,a)             \
register uint32_t __r##n;         \
__ASM("MOV %0, %1"                \
      : "=r"(__r##n)              \
      : "r" (a) )

#define SVC_In0 "r"(__rf)
#define SVC_In1 "r"(__rf),"r"(__r0)
#define SVC_In2 "r"(__rf),"r"(__r0),"r"(__r1)
#define SVC_In3 "r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2)
#define SVC_In4 "r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)

#define SVC_Out0
#define SVC_Out1 "=r"(__r0)
#define SVC_Out2 "=r"(__r0),"=r"(__r1)

#define SVC_CL0
#define SVC_CL1 "r1"
#define SVC_CL2 "r0","r1"

#define SVC_Call0(in, out, cl)                                                  \
  __ASM volatile ("svc 0" : out : in : cl)

#if ((__ARM_ARCH_7M__ == 1U) || (__ARM_ARCH_7EM__ == 1U) || (__ARM_ARCH_8M_MAIN__ == 1U))

#if    (__FPU_USED == 1U)

// "bic   %[val],#7\n" ====> "bic   %[val],%[val],#7\n"
#define SVC_Call0M(in, out, cl)                                                 \
  register uint32_t val;                                                        \
  __ASM volatile (                                                              \
    "mrs   %[val],control\n"                                                    \
    "tst   %[val],#2\n"                                                         \
    "bne   Label0\n"                                                            \
    "tst   %[val],#4\n"                                                         \
    "mrs   %[val],msp\n"                                                        \
    "ite   eq\n"                                                                \
    "subeq %[val],#32\n"                                                        \
    "subne %[val],#104\n"                                                       \
    "bic   %[val],%[val],#7\n"                                                  \
    "msr   psp,%[val]\n"                                                        \
  "Label0:\n"                                                                   \
    "svc 0"                                                                     \
  : out, [val] "=&l" (val) : in : cl)
#else

#define SVC_Call0M(in, out, cl)                                                \
  register uint32_t val;                                                       \
  __ASM volatile (                                                             \
    "mrs   %[val],control\n"                                                   \
    "tst   %[val],#2\n"                                                        \
    "bne   Label0\n"                                                           \
    "mrs   %[val],msp\n"                                                       \
    "subs  %[val],#32\n"                                                       \
    "bic   %[val],%[val],#7\n"                                                 \
    "msr   psp,%[val]\n"                                                       \
  "Label0:\n"                                                                  \
    "svc 0"                                                                    \
  : out, [val] "=&l" (val) : in : cl)
#endif

#elif ((__ARM_ARCH_6M__ == 1U) || (__ARM_ARCH_8M_BASE__ == 1U))

#define SVC_Call0M(in, out, cl)                                                \
  register uint32_t val;                                                       \
  __ASM volatile (                                                             \
    "mrs   %[val],control\n"                                                   \
    "lsls  %[val],#30\n"                                                       \
    "bmi   Label0\n"                                                           \
    "mrs   %[val],msp\n"                                                       \
    "subs  %[val],#32\n"                                                       \
    "lsrs  %[val],#3\n"                                                        \
    "lsls  %[val],#3\n"                                                        \
    "msr   psp,%[val]\n"                                                       \
  "Label0:\n"                                                                  \
    "svc 0"                                                                    \
  : out, [val] "=&l" (val) : in : cl)
#endif

#define SVC0_0N(f,t)                                                           \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (void) {                                            \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In0, SVC_Out0, SVC_CL2);                                       \
}

#define SVC0_0(f,t)                                                            \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (void) {                                            \
  SVC_ArgN(0);                                                                 \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In0, SVC_Out1, SVC_CL1);                                       \
  return (t) __r0;                                                             \
}

#define SVC0_0M(f,t)                                                           \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (void) {                                            \
  SVC_ArgN(0);                                                                 \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0M(SVC_In0, SVC_Out1, SVC_CL1);                                      \
  return (t) __r0;                                                             \
}

#define SVC0_0D(f,t)                                                           \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (void) {                                            \
  SVC_ArgN(0);                                                                 \
  SVC_ArgN(1);                                                                 \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In0, SVC_Out2, SVC_CL0);                                       \
  return (((t) __r0) | (((t) __r1) << 32));                                    \
}

#define SVC0_1N(f,t,t1)                                                        \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1) {                                           \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In1, SVC_Out0, SVC_CL1);                                       \
}

#define SVC0_1(f,t,t1)                                                         \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1) {                                           \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In1, SVC_Out1, SVC_CL1);                                       \
  return (t) __r0;                                                             \
}

#define SVC0_1M(f,t,t1)                                                        \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1) {                                           \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0M(SVC_In1, SVC_Out1, SVC_CL1);                                      \
  return (t) __r0;                                                             \
}

#define SVC0_2(f,t,t1,t2)                                                      \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2) {                                    \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In2, SVC_Out1, SVC_CL0);                                       \
  return (t) __r0;                                                             \
}

#define SVC0_2M(f,t,t1,t2)                                                     \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2) {                                    \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0M(SVC_In2, SVC_Out1, SVC_CL0);                                      \
  return (t) __r0;                                                             \
}

#define SVC0_3(f,t,t1,t2,t3)                                                   \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2, t3 a3) {                             \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgR(2,a3);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In3, SVC_Out1, SVC_CL0);                                       \
  return (t) __r0;                                                             \
}

#define SVC0_3M(f,t,t1,t2,t3)                                                  \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2, t3 a3) {                             \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgR(2,a3);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0M(SVC_In3, SVC_Out1, SVC_CL0);                                      \
  return (t) __r0;                                                             \
}

#define SVC0_4(f,t,t1,t2,t3,t4)                                                \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2, t3 a3, t4 a4) {                      \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgR(2,a3);                                                              \
  SVC_ArgR(3,a4);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0(SVC_In4, SVC_Out1, SVC_CL0);                                       \
  return (t) __r0;                                                             \
}

#define SVC0_4M(f,t,t1,t2,t3,t4)                                               \
__INLINE_FORCED                                                                \
__STATIC_INLINE t __svc##f (t1 a1, t2 a2, t3 a3, t4 a4) {                      \
  SVC_ArgR(0,a1);                                                              \
  SVC_ArgR(1,a2);                                                              \
  SVC_ArgR(2,a3);                                                              \
  SVC_ArgR(3,a4);                                                              \
  SVC_ArgF(svcRtx##f);                                                         \
  SVC_Call0M(SVC_In4, SVC_Out1, SVC_CL0);                                      \
  return (t) __r0;                                                             \
}

//  ==== Core Peripherals functions ====

extern uint32_t SystemCoreClock;        // System Clock Frequency (Core Clock)

/// Initialize SVC and PendSV System Service Calls
__STATIC_INLINE void SVC_Initialize( void )
{
#if ((__ARM_ARCH_8M_MAIN__ == 1U) || (defined(__CORTEX_M) && (__CORTEX_M == 7U)))
  uint32_t p, n;

  SCB->SHPR[10] = 0xFFU;
  n = 32U - (uint32_t)__CLZ(~(SCB->SHPR[10] | 0xFFFFFF00U));
  p = NVIC_GetPriorityGrouping();
  if (p >= n)
  {
    n = p + 1U;
  }
  SCB->SHPR[7] = (uint8_t)(0xFEU << n);
#elif  (__ARM_ARCH_8M_BASE__ == 1U)
  SCB->SHPR[1] |= 0x00FF0000U;
  SCB->SHPR[0] |= (SCB->SHPR[1] << (8+1)) & 0xFC000000U;
#elif ((__ARM_ARCH_7M__ == 1U) || \
       (__ARM_ARCH_7EM__ == 1U))
  uint32_t p, n;

  SCB->SHP[ 10 ] = 0xFFU;
  n = 32U - (uint32_t) __CLZ( ~( SCB->SHP[ 10 ] | 0xFFFFFF00U ) );
  p = NVIC_GetPriorityGrouping( );
  if ( p >= n )
  {
    n = p + 1U;
  }
  SCB->SHP[ 7 ] = (uint8_t) ( 0xFEU << n );
#elif  (__ARM_ARCH_6M__ == 1U)
  SCB->SHP[1] |= 0x00FF0000U;
  SCB->SHP[0] |= (SCB->SHP[1] << (8+1)) & 0xFC000000U;
#endif
}

/// Setup SysTick Timer
/// \param[in] period  Timer Load value
__STATIC_INLINE void SysTick_Setup( uint32_t period )
{
  SysTick->LOAD = period - 1U;
  SysTick->VAL = 0U;
#if ((__ARM_ARCH_8M_MAIN__ == 1U) || (defined(__CORTEX_M) && (__CORTEX_M == 7U)))
  SCB->SHPR[11] = 0xFFU;
#elif  (__ARM_ARCH_8M_BASE__ == 1U)
  SCB->SHPR[1] |= 0xFF000000U;
#elif ((__ARM_ARCH_7M__ == 1U) || \
       (__ARM_ARCH_7EM__ == 1U))
  SCB->SHP[ 11 ] = 0xFFU;
#elif  (__ARM_ARCH_6M__ == 1U)
  SCB->SHP[1] |= 0xFF000000U;
#endif
}

/// Get SysTick Period
/// \return    SysTick Period
__STATIC_INLINE uint32_t SysTick_GetPeriod( void )
{
  return ( SysTick->LOAD + 1U );
}

/// Get SysTick Value
/// \return    SysTick Value
__STATIC_INLINE uint32_t SysTick_GetVal( void )
{
  uint32_t Val = SysTick->VAL;
  return ( SysTick->LOAD - Val );
}

/// Get SysTick Overflow (Auto Clear)
/// \return    SysTick Overflow flag
__STATIC_INLINE uint32_t SysTick_GetOvf( void )
{
  return ( ( SysTick->CTRL >> 16 ) & 1U );
}

/// Enable SysTick Timer
__STATIC_INLINE void SysTick_Enable( void )
{
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk |
  SysTick_CTRL_TICKINT_Msk |
  SysTick_CTRL_CLKSOURCE_Msk;
}

/// Disable SysTick Timer
__STATIC_INLINE void SysTick_Disable( void )
{
  SysTick->CTRL = 0U;
}

/// Setup External Tick Timer Interrupt
/// \param[in] irqn  Interrupt number
__STATIC_INLINE void ExtTick_SetupIRQ( int32_t irqn )
{
#if    (__ARM_ARCH_8M_MAIN__ == 1U)
  NVIC->IPR[irqn] = 0xFFU;
#elif  (__ARM_ARCH_8M_BASE__ == 1U)
  NVIC->IPR[irqn >> 2] = (NVIC->IPR[irqn >> 2] & ~(0xFFU << ((irqn & 3) << 3))) |
  (0xFFU << ((irqn & 3) << 3));
#elif ((__ARM_ARCH_7M__ == 1U) || \
       (__ARM_ARCH_7EM__ == 1U))
  NVIC->IP[ irqn ] = 0xFFU;
#elif  (__ARM_ARCH_6M__ == 1U)
  NVIC->IP[irqn >> 2] = (NVIC->IP[irqn >> 2] & ~(0xFFU << ((irqn & 3) << 3))) |
  (0xFFU << ((irqn & 3) << 3));
#endif
}

/// Enable External Tick Timer Interrupt
/// \param[in] irqn  Interrupt number
__STATIC_INLINE void ExtTick_EnableIRQ( int32_t irqn )
{
  NVIC->ISER[ irqn >> 5 ] = 1U << ( irqn & 0x1F );
}

/// Disable External Tick Timer Interrupt
/// \param[in] irqn  Interrupt number
__STATIC_INLINE void ExtTick_DisableIRQ( int32_t irqn )
{
  NVIC->ICER[ irqn >> 5 ] = 1U << ( irqn & 0x1F );
}

/// Get Pending SV (Service Call) and ST (SysTick) Flags
/// \return    Pending SV&ST Flags
__STATIC_INLINE uint8_t GetPendSV_ST( void )
{
  return ( (uint8_t) ( ( SCB->ICSR & ( SCB_ICSR_PENDSVSET_Msk | SCB_ICSR_PENDSTSET_Msk ) ) >> 24 ) );
}

/// Get Pending SV (Service Call) Flag
/// \return    Pending SV Flag
__STATIC_INLINE uint8_t GetPendSV( void )
{
  return ( (uint8_t) ( ( SCB->ICSR & ( SCB_ICSR_PENDSVSET_Msk ) ) >> 24 ) );
}

/// Clear Pending SV (Service Call) and ST (SysTick) Flags
__STATIC_INLINE void ClrPendSV_ST( void )
{
  SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk | SCB_ICSR_PENDSTCLR_Msk;
}

/// Clear Pending SV (Service Call) Flag
__STATIC_INLINE void ClrPendSV( void )
{
  SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;
}

/// Set Pending SV (Service Call) Flag
__STATIC_INLINE void SetPendSV( void )
{
  SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

/// Set Pending Flags
/// \param[in] flags  Flags to set
__STATIC_INLINE void SetPendFlags( uint8_t flags )
{
  SCB->ICSR = ( (uint32_t) flags << 24 );
}

//  ==== Exclusive Access Operation ====

#if (__EXCLUSIVE_ACCESS == 1U)

/// Atomic Access Operation: Write (8-bit)
/// \param[in]  mem             Memory address
/// \param[in]  val             Value to write
/// \return                     Previous value
__STATIC_INLINE uint8_t atomic_wr8( uint8_t *mem, uint8_t val )
{
  register uint32_t res;
  register uint8_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrexb %[ret],[%[mem]]\n"
      "strexb %[res],%[val],[%[mem]]\n"
      "cbz    %[res],Label2\n"
      "b       Label1\n"
      "Label2:"
      : [ret] "=&l" (ret),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [val] "l" (val)
      : "memory"
  );

  return ret;
}

/// Atomic Access Operation: Set bits (32-bit)
/// \param[in]  mem             Memory address
/// \param[in]  bits            Bit mask
/// \return                     New value
__STATIC_INLINE uint32_t atomic_set32( uint32_t *mem, uint32_t bits )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[val],[%[mem]]\n"
#if (__ARM_ARCH_8M_BASE__ == 1U)
      "mov   %[ret],%[val]\n"
      "orrs  %[ret],%[bits]\n"
#else
      "orr   %[ret],%[val],%[bits]\n"
#endif
      "strex %[res],%[ret],[%[mem]]\n"
      "cbz   %[res],Label2\n"
      "b     Label1\n"
      "Label2:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [bits] "l" (bits)
#if (__ARM_ARCH_8M_BASE__ == 1U)
      : "memory", "cc"
#else
      : "memory"
#endif
  );

  return ret;
}

/// Atomic Access Operation: Clear bits (32-bit)
/// \param[in]  mem             Memory address
/// \param[in]  bits            Bit mask
/// \return                     Previous value
__STATIC_INLINE uint32_t atomic_clr32( uint32_t *mem, uint32_t bits )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
#if (__ARM_ARCH_8M_BASE__ == 1U)
      "mov   %[val],%[ret]\n"
      "bics  %[val],%[bits]\n"
#else
      "bic   %[val],%[ret],%[bits]\n"
#endif
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label2\n"
      "b     Label1\n"
      "Label2:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [bits] "l" (bits)
#if (__ARM_ARCH_8M_BASE__ == 1U)
      : "memory", "cc"
#else
      : "memory"
#endif
  );

  return ret;
}

/// Atomic Access Operation: Check if all specified bits (32-bit) are active and clear them
/// \param[in]  mem             Memory address
/// \param[in]  bits            Bit mask
/// \return                     Active bits before clearing or 0 if not active
__STATIC_INLINE uint32_t atomic_chk32_all( uint32_t *mem, uint32_t bits )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
#if (__ARM_ARCH_8M_BASE__ == 1U)
      "mov   %[val],%[ret]\n"
      "ands  %[val],%[bits]\n"
#else
      "and   %[val],%[ret],%[bits]\n"
#endif
      "cmp   %[val],%[bits]\n"
      "beq   Label2\n"
      "clrex\n"
      "movs  %[ret],#0\n"
      "b     Label3\n"
      "Label2:\n"
#if (__ARM_ARCH_8M_BASE__ == 1U)
      "mov   %[val],%[ret]\n"
      "bics  %[val],%[bits]\n"
#else
      "bic   %[val],%[ret],%[bits]\n"
#endif
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label3\n"
      "b     Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [bits] "l" (bits)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Check if any specified bits (32-bit) are active and clear them
/// \param[in]  mem             Memory address
/// \param[in]  bits            Bit mask
/// \return                     Active bits before clearing or 0 if not active
__STATIC_INLINE uint32_t atomic_chk32_any( uint32_t *mem, uint32_t bits )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
      "tst   %[ret],%[bits]\n"
      "bne   Label2\n"
      "clrex\n"
      "movs  %[ret],#0\n"
      "b     Label3\n"
      "Label2:\n"
#if (__ARM_ARCH_8M_BASE__ == 1U)
      "mov   %[val],%[ret]\n"
      "bics  %[val],%[bits]\n"
#else
      "bic   %[val],%[ret],%[bits]\n"
#endif
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label3\n"
      "b     Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [bits] "l" (bits)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Increment (32-bit)
/// \param[in]  mem             Memory address
/// \return                     Previous value
__STATIC_INLINE uint32_t atomic_inc32( uint32_t *mem )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
      "adds  %[val],%[ret],#1\n"
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label2\n"
      "b     Label1\n"
      "Label2:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem)
      : "cc", "memory"
  );

  return ret;
}

/// atomic Access Operation: Increment (32-bit) if Less Than
/// \param[in]  mem             Memory address
/// \param[in]  max             Maximum value
/// \return                     Previous value
__STATIC_INLINE uint32_t atomic_inc32_lt( uint32_t *mem, uint32_t max )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
      "cmp   %[max],%[ret]\n"
      "bhi    Label2\n"
      "clrex\n"
      "b      Label3\n"
      "Label2:\n"
      "adds  %[val],%[ret],#1\n"
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label3\n"
      "b     Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [max] "l" (max)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Increment (16-bit) if Less Than
/// \param[in]  mem             Memory address
/// \param[in]  max             Maximum value
/// \return                     Previous value
__STATIC_INLINE uint16_t atomic_inc16_lt( uint16_t *mem, uint16_t max )
{
  register uint32_t val, res;
  register uint16_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrexh %[ret],[%[mem]]\n"
      "cmp    %[max],%[ret]\n"
      "bhi    Label2\n"
      "clrex\n"
      "b      Label3\n"
      "Label2:\n"
      "adds   %[val],%[ret],#1\n"
      "strexh %[res],%[val],[%[mem]]\n"
      "cbz    %[res],Label3\n"
      "b      Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [max] "l" (max)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Increment (16-bit) and clear on Limit
/// \param[in]  mem             Memory address
/// \param[in]  max             Maximum value
/// \return                     Previous value
__STATIC_INLINE uint16_t atomic_inc16_lim( uint16_t *mem, uint16_t lim )
{
  register uint32_t val, res;
  register uint16_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrexh %[ret],[%[mem]]\n"
      "adds   %[val],%[ret],#1\n"
      "cmp    %[lim],%[val]\n"
      "bhi    Label2\n"
      "movs   %[val],#0\n"
      "Label2:\n"
      "strexh %[res],%[val],[%[mem]]\n"
      "cbz    %[res],Label3\n"
      "b      Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem),
      [lim] "l" (lim)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Decrement (32-bit) if Not Zero
/// \param[in]  mem             Memory address
/// \return                     Previous value
__STATIC_INLINE uint32_t atomic_dec32_nz( uint32_t *mem )
{
  register uint32_t val, res;
  register uint32_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[mem]]\n"
      "cbnz  %[ret],Label2\n"
      "clrex\n"
      "b     Label3\n"
      "Label2:\n"
      "subs  %[val],%[ret],#1\n"
      "strex %[res],%[val],[%[mem]]\n"
      "cbz   %[res],Label3\n"
      "b     Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Decrement (16-bit) if Not Zero
/// \param[in]  mem             Memory address
/// \return                     Previous value
__STATIC_INLINE uint16_t atomic_dec16_nz( uint16_t *mem )
{
  register uint32_t val, res;
  register uint16_t ret;

  __ASM volatile (
      "Label1:\n"
      "ldrexh %[ret],[%[mem]]\n"
      "cbnz   %[ret],Label2\n"
      "clrex\n"
      "b      Label3\n"
      "Label2:\n"
      "subs   %[val],%[ret],#1\n"
      "strexh %[res],%[val],[%[mem]]\n"
      "cbz    %[res],Label3\n"
      "b      Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [mem] "l" (mem)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Link Get
/// \param[in]  root            Root address
/// \return                     Link
__STATIC_INLINE void *atomic_link_get( void **root )
{
  register uint32_t val, res;
  register void *ret;

  __ASM volatile (
      "Label1:\n"
      "ldrex %[ret],[%[root]]\n"
      "cbnz  %[ret],Label2\n"
      "clrex\n"
      "b     Label3\n"
      "Label2:\n"
      "ldr   %[val],[%[ret]]\n"
      "strex %[res],%[val],[%[root]]\n"
      "cbz   %[res],Label3\n"
      "b     Label1\n"
      "Label3:"
      : [ret] "=&l" (ret),
      [val] "=&l" (val),
      [res] "=&l" (res)
      : [root] "l" (root)
      : "cc", "memory"
  );

  return ret;
}

/// Atomic Access Operation: Link Put
/// \param[in]  root            Root address
/// \param[in]  lnk             Link
__STATIC_INLINE void atomic_link_put( void **root, void *link )
{
  register uint32_t val1, val2, res;

__ASM volatile (
    "Label1:\n"
    "ldr   %[val1],[%[root]]\n"
    "str   %[val1],[%[link]]\n"
    "dmb\n"
    "ldrex %[val1],[%[root]]\n"
    "ldr   %[val2],[%[link]]\n"
    "cmp   %[val2],%[val2]\n"
    "bne   Label1\n"
    "strex %[res],%[link],[%[root]]\n"
    "cbz   %[res],Label2\n"
    "b     Label1\n"
    "Label2:"
    : [val1] "=&l" (val1),
    [val2] "=&l" (val2),
    [res] "=&l" (res)
    : [root] "l" (root),
    [link] "l" (link)
    : "cc", "memory"
);
}

#endif  // (__EXCLUSIVE_ACCESS == 1U)

// #pragma diag_default=Pe550

#endif  // __CORE_CM_ICCARM_H__
