/*------------------------------------------------------------------------------
 * MDK - Component ::Event Recorder
 * Copyright (c) 2016 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    EventRecorderConf.h
 * Purpose: Event Recorder Configuration
 * Rev.:    V1.0.0
 *----------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h>Event Recorder

//   <o>Number of Records
//     <8=>8 <16=>16 <32=>32 <64=>64 <128=>128 <256=>256 <512=>512 <1024=>1024
//     <2048=>2048 <4096=>4096 <8192=>8192 <16384=>16384 <32768=>32768
//     <65536=>65536 <131072=>131072 <262144=>262144 <524288=>524288
//     <1048576=>1048576
//   <i>Configure size of Event Record Buffer (each record is 16 bytes)
//   <i>Must be 2^n (min=8, max=1048576)
#define EVENT_RECORD_COUNT      64U

//   <o>Time Stamp Source
//      <0=> DWT Cycle Counter  <1=> SysTick  <2=> CMSIS RTOS
//      <3=> User Timer (Normal Reset)  <4=> User Timer (Power-On Reset)
//   <i>Selects source for 32-bit time stamp
#define EVENT_TIMESTAMP_SOURCE  0

//   <h>SysTick Configuration
//   <i>Configure values when Time Stamp Source is set to SysTick

//     <o>SysTick Input Clock Frequency [Hz] <1-1000000000>
//     <i>Defines SysTick input clock (typical identical with processor clock)
#define SYSTICK_CLOCK           100000000U

//     <o>SysTick Interrupt Frequency [us] <1-1000000000>
//     <i>Defines time period of the SysTick timer interrupt
#define SYSTICK_PERIOD_US       1000U

//   </h>

// </h>

//------------- <<< end of configuration section >>> ---------------------------

// MDKARM :: Options : C/C++ (AC6) : Preprocessor Symbols : Define
#define EVR_RTX_DISABLE

//
// Defined in RTX_Config.h
//
#if (0)

#define OS_EVR_EVFLAGS          ( 0 )
#define OS_EVR_KERNEL           ( 0 )
#define OS_EVR_MEMORY           ( 0 )
#define OS_EVR_MEMPOOL          ( 0 )
#define OS_EVR_MSGQUEUE         ( 0 )
#define OS_EVR_MUTEX            ( 0 )
#define OS_EVR_SEMAPHORE        ( 0 )
#define OS_EVR_THREAD           ( 0 )
#define OS_EVR_TIMER            ( 0 )

#endif

#define EVR_RTX_EVENT_FLAGS_CLEAR_DISABLE
#define EVR_RTX_EVENT_FLAGS_CLEAR_DONE_DISABLE
#define EVR_RTX_EVENT_FLAGS_CREATED_DISABLE
#define EVR_RTX_EVENT_FLAGS_DELETE_DISABLE
#define EVR_RTX_EVENT_FLAGS_DESTROYED_DISABLE
#define EVR_RTX_EVENT_FLAGS_ERROR_DISABLE
#define EVR_RTX_EVENT_FLAGS_GET_DISABLE
#define EVR_RTX_EVENT_FLAGS_GET_NAME_DISABLE
#define EVR_RTX_EVENT_FLAGS_NEW_DISABLE
#define EVR_RTX_EVENT_FLAGS_SET_DISABLE
#define EVR_RTX_EVENT_FLAGS_SET_DONE_DISABLE
#define EVR_RTX_EVENT_FLAGS_WAIT_COMPLETED_DISABLE
#define EVR_RTX_EVENT_FLAGS_WAIT_DISABLE
#define EVR_RTX_EVENT_FLAGS_WAIT_NOT_COMPLETED_DISABLE
#define EVR_RTX_EVENT_FLAGS_WAIT_PENDING_DISABLE
#define EVR_RTX_EVENT_FLAGS_WAIT_TIMEOUT_DISABLE

#define EVR_RTX_KERNEL_ERROR_DISABLE
#define EVR_RTX_KERNEL_GET_INFO_DISABLE
#define EVR_RTX_KERNEL_GET_STATE_DISABLE
#define EVR_RTX_KERNEL_GET_SYS_TIMER_COUNT_DISABLE
#define EVR_RTX_KERNEL_GET_SYS_TIMER_FREQ_DISABLE
#define EVR_RTX_KERNEL_GET_TICK_COUNT_DISABLE
#define EVR_RTX_KERNEL_GET_TICK_FREQ_DISABLE
#define EVR_RTX_KERNEL_INFO_RETRIEVED_DISABLE
#define EVR_RTX_KERNEL_INITIALIZE_COMPLETED_DISABLE
#define EVR_RTX_KERNEL_INITIALIZE_DISABLE
#define EVR_RTX_KERNEL_LOCK_DISABLE
#define EVR_RTX_KERNEL_LOCK_RESTORED_DISABLE
#define EVR_RTX_KERNEL_LOCKED_DISABLE
#define EVR_RTX_KERNEL_RESTORE_LOCK_DISABLE
#define EVR_RTX_KERNEL_RESUME_DISABLE
#define EVR_RTX_KERNEL_RESUMED_DISABLE
#define EVR_RTX_KERNEL_START_DISABLE
#define EVR_RTX_KERNEL_STARTED_DISABLE
#define EVR_RTX_KERNEL_SUSPEND_DISABLE
#define EVR_RTX_KERNEL_SUSPENDED_DISABLE
#define EVR_RTX_KERNEL_UNLOCK_DISABLE
#define EVR_RTX_KERNEL_UNLOCKED_DISABLE

#define EVR_RTX_MEMORY_ALLOC_DISABLE
#define EVR_RTX_MEMORY_BLOCK_ALLOC_DISABLE
#define EVR_RTX_MEMORY_BLOCK_FREE_DISABLE
#define EVR_RTX_MEMORY_BLOCK_INIT_DISABLE
#define EVR_RTX_MEMORY_FREE_DISABLE
#define EVR_RTX_MEMORY_INIT_DISABLE
#define EVR_RTX_MEMORY_POOL_ALLOC_DISABLE
#define EVR_RTX_MEMORY_POOL_ALLOC_FAILED_DISABLE
#define EVR_RTX_MEMORY_POOL_ALLOC_PENDING_DISABLE
#define EVR_RTX_MEMORY_POOL_ALLOC_TIMEOUT_DISABLE
#define EVR_RTX_MEMORY_POOL_ALLOCATED_DISABLE
#define EVR_RTX_MEMORY_POOL_CREATED_DISABLE
#define EVR_RTX_MEMORY_POOL_DEALLOCATED_DISABLE
#define EVR_RTX_MEMORY_POOL_DELETE_DISABLE
#define EVR_RTX_MEMORY_POOL_DESTROYED_DISABLE
#define EVR_RTX_MEMORY_POOL_ERROR_DISABLE
#define EVR_RTX_MEMORY_POOL_FREE_DISABLE
#define EVR_RTX_MEMORY_POOL_FREE_FAILED_DISABLE
#define EVR_RTX_MEMORY_POOL_GET_BLOCK_SZIE_DISABLE
#define EVR_RTX_MEMORY_POOL_GET_CAPACITY_DISABLE
#define EVR_RTX_MEMORY_POOL_GET_COUNT_DISABLE
#define EVR_RTX_MEMORY_POOL_GET_NAME_DISABLE
#define EVR_RTX_MEMORY_POOL_GET_SPACE_DISABLE
#define EVR_RTX_MEMORY_POOL_NEW_DISABLE

#define EVR_RTX_MESSAGE_QUEUE_CREATED_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_DELETE_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_DESTROYED_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_ERROR_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_CAPACITY_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_COUNT_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_MSG_SIZE_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_NAME_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_PENDING_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_SPACE_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_GET_TIMEOUT_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_INSERT_PENDING_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_INSERTED_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_NEW_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_NOT_INSERTED_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_NOT_RETRIEVED_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_PUT_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_PUT_PENDING_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_PUT_TIMEOUT_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_RESET_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_RESET_DONE_DISABLE
#define EVR_RTX_MESSAGE_QUEUE_RETRIEVED_DISABLE

#define EVR_RTX_MUTEX_ACQUIRE_DISABLE
#define EVR_RTX_MUTEX_ACQUIRE_PENDING_DISABLE
#define EVR_RTX_MUTEX_ACQUIRE_TIMEOUT_DISABLE
#define EVR_RTX_MUTEX_ACQUIRED_DISABLE
#define EVR_RTX_MUTEX_CREATED_DISABLE
#define EVR_RTX_MUTEX_DELETE_DISABLE
#define EVR_RTX_MUTEX_DESTROYED_DISABLE
#define EVR_RTX_MUTEX_ERROR_DISABLE
#define EVR_RTX_MUTEX_GET_NAME_DISABLE
#define EVR_RTX_MUTEX_GET_OWNER_DISABLE
#define EVR_RTX_MUTEX_NEW_DISABLE
#define EVR_RTX_MUTEX_NOT_ACQUIRED_DISABLE
#define EVR_RTX_MUTEX_RELEASE_DISABLE
#define EVR_RTX_MUTEX_RELEASED_DISABLE

#define EVR_RTX_SEMAPHORE_ACQUIRE_DISABLE
#define EVR_RTX_SEMAPHORE_ACQUIRE_PENDING_DISABLE
#define EVR_RTX_SEMAPHORE_ACQUIRE_TIMEOUT_DISABLE
#define EVR_RTX_SEMAPHORE_ACQUIRED_DISABLE
#define EVR_RTX_SEMAPHORE_CREATED_DISABLE
#define EVR_RTX_SEMAPHORE_DELETE_DISABLE
#define EVR_RTX_SEMAPHORE_DESTROYED_DISABLE
#define EVR_RTX_SEMAPHORE_ERROR_DISABLE
#define EVR_RTX_SEMAPHORE_GET_COUNT_DISABLE
#define EVR_RTX_SEMAPHORE_GET_NAME_DISABLE
#define EVR_RTX_SEMAPHORE_NEW_DISABLE
#define EVR_RTX_SEMAPHORE_NOT_ACQUIRED_DISABLE
#define EVR_RTX_SEMAPHORE_RELEASE_DISABLE
#define EVR_RTX_SEMAPHORE_RELEASED_DISABLE

#define EVR_RTX_THREAD_BLOCKED_DISABLE
#define EVR_RTX_THREAD_CREATED_DISABLE
#define EVR_RTX_THREAD_DELAY_COMPLETED_DISABLE
#define EVR_RTX_THREAD_DELAY_DISABLE
#define EVR_RTX_THREAD_DELAY_UNTIL_DISABLE
#define EVR_RTX_THREAD_DESTROYED_DISABLE
#define EVR_RTX_THREAD_DETACH_DISABLE
#define EVR_RTX_THREAD_DETACHED_DISABLE
#define EVR_RTX_THREAD_ENUMERATE_DISABLE
#define EVR_RTX_THREAD_ERROR_DISABLE
#define EVR_RTX_THREAD_EXIT_DISABLE
#define EVR_RTX_THREAD_FLAGS_CLEAR_DISABLE
#define EVR_RTX_THREAD_FLAGS_CLEAR_DONE_DISABLE
#define EVR_RTX_THREAD_FLAGS_GET_DISABLE
#define EVR_RTX_THREAD_FLAGS_SET_DISABLE
#define EVR_RTX_THREAD_FLAGS_SET_DONE_DISABLE
#define EVR_RTX_THREAD_FLAGS_WAIT_COMPLETED_DISABLE
#define EVR_RTX_THREAD_FLAGS_WAIT_DISABLE
#define EVR_RTX_THREAD_FLAGS_WAIT_NOT_COMPLETED_DISABLE
#define EVR_RTX_THREAD_FLAGS_WAIT_PENDING_DISABLE
#define EVR_RTX_THREAD_FLAGS_WAIT_TIMEOUT_DISABLE
#define EVR_RTX_THREAD_GET_COUNT_DISABLE
#define EVR_RTX_THREAD_GET_ID_DISABLE
#define EVR_RTX_THREAD_GET_NAME_DISABLE
#define EVR_RTX_THREAD_GET_PRIORITY_DISABLE
#define EVR_RTX_THREAD_GET_STACK_SIZE_DISABLE
#define EVR_RTX_THREAD_GET_STACK_SPACE_DISABLE
#define EVR_RTX_THREAD_GET_STATE_DISABLE
#define EVR_RTX_THREAD_JOIN_DISABLE
#define EVR_RTX_THREAD_JOIN_PENDING_DISABLE
#define EVR_RTX_THREAD_JOINED_DISABLE
#define EVR_RTX_THREAD_NEW_DISABLE
#define EVR_RTX_THREAD_RESUME_DISABLE
#define EVR_RTX_THREAD_RESUMED_DISABLE
#define EVR_RTX_THREAD_SET_PRIORITY_DISABLE
#define EVR_RTX_THREAD_SUSPEND_DISABLE
#define EVR_RTX_THREAD_SUSPENDED_DISABLE
#define EVR_RTX_THREAD_SWITCH_DISABLE
#define EVR_RTX_THREAD_TERMINATE_DISABLE
#define EVR_RTX_THREAD_UNBLOCKED_DISABLE
#define EVR_RTX_THREAD_YIELD_DISABLE

#define EVR_RTX_TIMER_CALLBACK_DISABLE
#define EVR_RTX_TIMER_CREATED_DISABLE
#define EVR_RTX_TIMER_DELETE_DISABLE
#define EVR_RTX_TIMER_DESTROYED_DISABLE
#define EVR_RTX_TIMER_ERROR_DISABLE
#define EVR_RTX_TIMER_GET_NAME_DISABLE
#define EVR_RTX_TIMER_IS_RUNNING_DISABLE
#define EVR_RTX_TIMER_NEW_DISABLE
#define EVR_RTX_TIMER_START_DISABLE
#define EVR_RTX_TIMER_STARTED_DISABLE
#define EVR_RTX_TIMER_STOP_DISABLE
#define EVR_RTX_TIMER_STOPPED_DISABLE
