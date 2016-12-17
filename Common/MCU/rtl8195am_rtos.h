#ifndef __RTL8195AM_RTOS_H__
#define __RTL8195AM_RTOS_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

/* NOTE: struct size must be a 2's power! */
typedef struct _MemChunk
{
  struct _MemChunk *next;
  int size;
} MemChunk;

typedef MemChunk heap_buf_t;

/// A heap
typedef struct Heap
{
  struct _MemChunk *FreeList;     ///< Head of the free list
} Heap;

/**
 * Utility macro to allocate a heap of size \a size.
 *
 * \param name Variable name for the heap.
 * \param size Heap size in bytes.
 */
#define HEAP_DEFINE_BUF(name, size) \
	heap_buf_t name[((size) + sizeof(heap_buf_t) - 1) / sizeof(heap_buf_t)]

/// Initialize \a heap within the buffer pointed by \a memory which is of \a size bytes
void tcm_heap_init( void );

/// Allocate a chunk of memory of \a size bytes from the heap
void *tcm_heap_allocmem( int size );

/// Free a chunk of memory of \a size bytes from the heap
void tcm_heap_freemem( void *mem, int size );

int tcm_heap_freeSpace( void );

#define HNEW(heap, type) \
	(type*)tcm_heap_allocmem(heap, sizeof(type))

#define HNEWVEC(heap, type, nelem) \
	(type*)tcm_heap_allocmem(heap, sizeof(type) * (nelem))

#define HDELETE(heap, type, mem) \
	tcm_heap_freemem(heap, mem, sizeof(type))

#define HDELETEVEC(heap, type, nelem, mem) \
	tcm_heap_freemem(heap, mem, sizeof(type) * (nelem))

/**
 * \name Compatibility interface with C standard library
 * \{
 */
void *tcm_heap_malloc( int size );
void *tcm_heap_calloc( int size );
void tcm_heap_free( void * mem );
/** \} */

#define CONFIG_LITTLE_ENDIAN

#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8711B)
#define CONFIG_PLATFORM_AMEBA_X
#endif

#if defined(CONFIG_PLATFORM_8195A)
#define CONFIG_USE_TCM_HEAP 1					/* USE TCM HEAP */
#define USE_MUTEX_FOR_SPINLOCK	1
#endif

#if defined(CONFIG_PLATFORM_AMEBA_X)
#define CONFIG_MEM_MONITOR	MEM_MONITOR_SIMPLE
#else
#define CONFIG_MEM_MONITOR	MEM_MONITOR_LEAK
#endif

/* Define compilor specific symbol */
//
// inline function
//
#if defined ( __ICCARM__ )
#define __inline__                      inline
#define __inline                        inline
#define __inline_definition			//In dialect C99, inline means that a function's definition is provided
//only for inlining, and that there is another definition
//(without inline) somewhere else in the program.
//That means that this program is incomplete, because if
//add isn't inlined (for example, when compiling without optimization),
//then main will have an unresolved reference to that other definition.

// Do not inline function is the function body is defined .c file and this
// function will be called somewhere else, otherwise there is compile error
#elif defined ( __CC_ARM   )
#define __inline__			__inline	//__linine__ is not supported in keil compilor, use __inline instead
#define inline				__inline
#define __inline_definition			// for dialect C99
#elif defined   (  __GNUC__  )
#define __inline__                      inline
#define __inline                        inline
#define __inline_definition	inline
#endif

#include <stdio.h>
#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8711B)
#include "platform_autoconf.h"
#else
#ifndef SUCCESS
#define SUCCESS	0
#endif
#ifndef FAIL
#define FAIL	(-1)
#endif
#ifndef _SUCCESS
#define _SUCCESS	1
#endif
#ifndef _FAIL
#define _FAIL	0
#endif
#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    (!FALSE)
#endif

#define _TRUE        TRUE
#define _FALSE	     FALSE

#endif

#if defined( PLATFORM_FREERTOS)
#include "freertos_service.h"
#elif defined( PLATFORM_ECOS)
#include "ecos/ecos_service.h"
#endif

#define RTW_MAX_DELAY			0xFFFFFFFF
#define RTW_WAIT_FOREVER		0xFFFFFFFF

/* Definitions returned by xTaskGetSchedulerState(). */
#define OS_SCHEDULER_NOT_STARTED	0
#define OS_SCHEDULER_RUNNING		1
#define OS_SCHEDULER_SUSPENDED		2

struct timer_list
{
  _timerHandle timer_hdl;
  unsigned long data;
  void (*function)( void * );
};

typedef thread_return (*thread_func_t)( thread_context context );
typedef void (*TIMER_FUN)( void *context );
typedef int (*event_handler_t)( char *buf, int buf_len, int flags, void *user_data );

#define CONFIG_THREAD_COMM_SEMA
struct task_struct
{
  const char *task_name;
  _thread_hdl_ task; /* I: workqueue thread */

#ifdef CONFIG_THREAD_COMM_SIGNAL
  const char *name; /* I: workqueue thread name */
  u32 queue_num; /* total signal num */
  u32 cur_queue_num; /* cur signal num should < queue_num */
#elif defined(CONFIG_THREAD_COMM_SEMA)
  _sema wakeup_sema;
  _sema terminate_sema;
//	_queue work_queue;  //TODO
#endif
  u32 blocked;
  u32 callback_running;
};

typedef struct
{
  _xqueue event_queue;
  struct task_struct thread;
} rtw_worker_thread_t;

typedef struct
{
  event_handler_t function;
  char *buf;
  int buf_len;
  int flags;
  void *user_data;
} rtw_event_message_t;

struct worker_timer_entry
{
  struct list_head list;
  _timerHandle timer_hdl;
  rtw_event_message_t message;
  rtw_worker_thread_t *worker_thread;
  u32 timeout;
};
#ifdef CONFIG_THREAD_COMM_SIGNAL
struct work_struct;
typedef void (*work_func_t)(void *context);
struct work_struct
{
  _list list;
  u32 data;
  work_func_t func;
  void *context;
  struct task_struct *used_wq;
};

struct delayed_work
{
  struct work_struct work;
  struct timer_list timer;
};
#endif

#ifdef CONFIG_MEM_MONITOR
//----- ------------------------------------------------------------------
// Memory Monitor
//----- ------------------------------------------------------------------
#define MEM_MONITOR_SIMPLE		0x1
#define MEM_MONITOR_LEAK		0x2

#define MEM_MONITOR_FLAG_WIFI_DRV	0x1
#define MEM_MONITOR_FLAG_WPAS		0x2
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
struct mem_entry
{
  struct list_head list;
  int size;
  void *ptr;
};
#endif

void init_mem_monitor( _list *pmem_table, int *used_num );
void deinit_mem_monitor( _list *pmem_table, int *used_num );
void add_mem_usage( _list *pmem_table, void *ptr, int size, int *used_num, int flag );
void del_mem_usage( _list *pmem_table, void *ptr, int *used_num, int flag );
int get_mem_usage( _list *pmem_table );
#endif

/*********************************** OSDEP API *****************************************/
u8* _rtw_vmalloc( u32 sz );
u8* _rtw_zvmalloc( u32 sz );
void _rtw_vmfree( u8 *pbuf, u32 sz );
u8* _rtw_zmalloc( u32 sz );
u8* _rtw_malloc( u32 sz );
void _rtw_mfree( u8 *pbuf, u32 sz );
#ifdef CONFIG_MEM_MONITOR
u8* rtw_vmalloc( u32 sz );
u8* rtw_zvmalloc( u32 sz );
void rtw_vmfree( u8 *pbuf, u32 sz );
u8* rtw_zmalloc( u32 sz );
u8* rtw_malloc( u32 sz );
void rtw_mfree( u8 *pbuf, u32 sz );
#else
#define	rtw_vmalloc		_rtw_vmalloc
#define	rtw_zvmalloc		_rtw_zvmalloc
#define	rtw_vmfree  		_rtw_vmfree
#define	rtw_zmalloc 		_rtw_zmalloc
#define	rtw_malloc  		_rtw_malloc
#define	rtw_mfree   		_rtw_mfree
#endif
#define rtw_free(buf)		rtw_mfree((u8 *)buf, 0)
void* rtw_malloc2d( int h, int w, int size );
void rtw_mfree2d( void *pbuf, int h, int w, int size );
void rtw_memcpy( void* dst, void* src, u32 sz );
int rtw_memcmp( void *dst, void *src, u32 sz );
void rtw_memset( void *pbuf, int c, u32 sz );

void rtw_init_listhead( _list *list );
u32 rtw_is_list_empty( _list *phead );
void rtw_list_insert_head( _list *plist, _list *phead );
void rtw_list_insert_tail( _list *plist, _list *phead );
void rtw_list_delete( _list *plist );

void rtw_init_sema( _sema *sema, int init_val );
void rtw_free_sema( _sema *sema );
void rtw_up_sema( _sema *sema );
void rtw_up_sema_from_isr( _sema *sema );
u32 rtw_down_sema( _sema *sema );
u32 rtw_down_timeout_sema( _sema *sema, u32 timeout );
void rtw_mutex_init( _mutex *pmutex );
void rtw_mutex_free( _mutex *pmutex );
void rtw_mutex_put( _mutex *pmutex );
void rtw_mutex_get( _mutex *pmutex );
int rtw_mutex_get_timeout( _mutex *pmutex, u32 timeout_ms );
void rtw_enter_critical( _lock *plock, _irqL *pirqL );
void rtw_exit_critical( _lock *plock, _irqL *pirqL );
void rtw_enter_critical_from_isr( _lock *plock, _irqL *pirqL );
void rtw_exit_critical_from_isr( _lock *plock, _irqL *pirqL );
void rtw_enter_critical_bh( _lock *plock, _irqL *pirqL );
void rtw_exit_critical_bh( _lock *plock, _irqL *pirqL );
int rtw_enter_critical_mutex( _mutex *pmutex, _irqL *pirqL );
void rtw_exit_critical_mutex( _mutex *pmutex, _irqL *pirqL );
void rtw_spinlock_init( _lock *plock );
void rtw_spinlock_free( _lock *plock );
void rtw_spinlock_init( _lock *plock );
void rtw_spinlock_free( _lock *plock );
void rtw_spin_lock( _lock *plock );
void rtw_spin_unlock( _lock *plock );
void rtw_spinlock_irqsave( _lock *plock, _irqL *irqL );
void rtw_spinunlock_irqsave( _lock *plock, _irqL *irqL );

int rtw_init_xqueue( _xqueue* queue, const char* name, u32 message_size, u32 number_of_messages );
int rtw_push_to_xqueue( _xqueue* queue, void* message, u32 timeout_ms );
int rtw_pop_from_xqueue( _xqueue* queue, void* message, u32 timeout_ms );
int rtw_deinit_xqueue( _xqueue* queue );

void rtw_init_queue( _queue *pqueue );
void rtw_deinit_queue( _queue *pqueue );
u32 rtw_is_queue_empty( _queue *pqueue );
u32 rtw_queue_empty( _queue *pqueue );
u32 rtw_end_of_queue_search( _list *queue, _list *pelement );
_list* rtw_get_queue_head( _queue *queue );

u32 rtw_get_current_time( void );
u32 rtw_systime_to_ms( u32 systime );
u32 rtw_systime_to_sec( u32 systime );
u32 rtw_ms_to_systime( u32 ms );
u32 rtw_sec_to_systime( u32 sec );
s32 rtw_get_passing_time_ms( u32 start );
s32 rtw_get_time_interval_ms( u32 start, u32 end );

void rtw_msleep_os( int ms );
void rtw_usleep_os( int us );
u32 rtw_atoi( u8* s );
void rtw_mdelay_os( int ms );
void rtw_udelay_os( int us );
void rtw_yield_os( void );

//Atomic integer operations
void ATOMIC_SET( ATOMIC_T *v, int i );
int ATOMIC_READ( ATOMIC_T *v );
void ATOMIC_ADD( ATOMIC_T *v, int i );
void ATOMIC_SUB( ATOMIC_T *v, int i );
void ATOMIC_INC( ATOMIC_T *v );
void ATOMIC_DEC( ATOMIC_T *v );
int ATOMIC_ADD_RETURN( ATOMIC_T *v, int i );
int ATOMIC_SUB_RETURN( ATOMIC_T *v, int i );
int ATOMIC_INC_RETURN( ATOMIC_T *v );
int ATOMIC_DEC_RETURN( ATOMIC_T *v );
int ATOMIC_DEC_AND_TEST( ATOMIC_T *v );

u64 rtw_modular64( u64 x, u64 y );
int rtw_get_random_bytes( void* dst, u32 size );
u32 rtw_getFreeHeapSize( void );
void flush_signals_thread( void );

void rtw_acquire_wakelock( void );
void rtw_release_wakelock( void );

/*********************************** Thread related *****************************************/
int rtw_create_task( struct task_struct *task, const char *name, u32 stack_size, u32 priority,
  thread_func_t func, void *thctx );
void rtw_delete_task( struct task_struct * task );
void rtw_wakeup_task( struct task_struct *task );
int rtw_create_worker_thread( rtw_worker_thread_t* worker_thread, u8 priority, u32 stack_size,
  u32 event_queue_size );
int rtw_delete_worker_thread( rtw_worker_thread_t* worker_thread );

#if 0 //TODO
void rtw_init_delayed_work(struct delayed_work *dwork, work_func_t func, const char *name);
void rtw_deinit_delayed_work(struct delayed_work *dwork);
int rtw_queue_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, u32 delay, void* context);
BOOLEAN rtw_cancel_delayed_work(struct delayed_work *dwork);
#endif

void rtw_thread_enter( char *name );
void rtw_thread_exit( void );
u8 rtw_get_scheduler_state( void );

#ifdef PLATFORM_LINUX
#define rtw_warn_on(condition) WARN_ON(condition)
#else
#define rtw_warn_on(condition) do {} while (0)
#endif

/*********************************** Timer related *****************************************/
_timerHandle rtw_timerCreate( const signed char *pcTimerName, osdepTickType xTimerPeriodInTicks,
  u32 uxAutoReload, void * pvTimerID, TIMER_FUN pxCallbackFunction );
u32 rtw_timerDelete( _timerHandle xTimer, osdepTickType xBlockTime );
u32 rtw_timerIsTimerActive( _timerHandle xTimer );
u32 rtw_timerStop( _timerHandle xTimer, osdepTickType xBlockTime );
u32 rtw_timerChangePeriod( _timerHandle xTimer, osdepTickType xNewPeriod, osdepTickType xBlockTime );

/*********************************** OSDEP API end *****************************************/
#define LIST_CONTAINOR(ptr, type, member) \
	((type *)((char *)(ptr)-(SIZE_T)((char *)&((type *)ptr)->member - (char *)ptr)))

#define time_after(a,b)	((long)(b) - (long)(a) < 0)
#define time_before(a,b)	time_after(b,a)
#define time_after_eq(a,b)	((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b)	time_after_eq(b,a)

#define _RND(sz, r) ((((sz)+((r)-1))/(r))*(r))
#define RND4(x)	(((x >> 2) + (((x & 3) == 0) ?  0: 1)) << 2)

__inline static u32 _RND4( u32 sz )
{
  u32 val;

  val = ( ( sz >> 2 ) + ( ( sz & 3 ) ? 1 : 0 ) ) << 2;

  return val;
}

__inline static u32 _RND8( u32 sz )
{
  u32 val;

  val = ( ( sz >> 3 ) + ( ( sz & 7 ) ? 1 : 0 ) ) << 3;

  return val;
}

__inline static u32 _RND128( u32 sz )
{
  u32 val;

  val = ( ( sz >> 7 ) + ( ( sz & 127 ) ? 1 : 0 ) ) << 7;

  return val;
}

__inline static u32 _RND256( u32 sz )
{
  u32 val;

  val = ( ( sz >> 8 ) + ( ( sz & 255 ) ? 1 : 0 ) ) << 8;

  return val;
}

__inline static u32 _RND512( u32 sz )
{
  u32 val;

  val = ( ( sz >> 9 ) + ( ( sz & 511 ) ? 1 : 0 ) ) << 9;

  return val;
}

__inline static u32 bitshift( u32 bitmask )
{
  u32 i;

  for ( i = 0; i <= 31; i++ )
    if ( ( ( bitmask >> i ) & 0x1 ) == 1 )
      break;

  return i;
}

/* Macros for handling unaligned memory accesses */

#define RTW_GET_BE16(a) ((u16) (((a)[0] << 8) | (a)[1]))
#define RTW_PUT_BE16(a, val)			\
	do {					\
		(a)[0] = ((u16) (val)) >> 8;	\
		(a)[1] = ((u16) (val)) & 0xff;	\
	} while (0)

#define RTW_GET_LE16(a) ((u16) (((a)[1] << 8) | (a)[0]))
#define RTW_PUT_LE16(a, val)			\
	do {					\
		(a)[1] = ((u16) (val)) >> 8;	\
		(a)[0] = ((u16) (val)) & 0xff;	\
	} while (0)

#define RTW_GET_BE24(a) ((((u32) (a)[0]) << 16) | (((u32) (a)[1]) << 8) | \
			 ((u32) (a)[2]))
#define RTW_PUT_BE24(a, val)					\
	do {							\
		(a)[0] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[2] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_BE32(a) ((((u32) (a)[0]) << 24) | (((u32) (a)[1]) << 16) | \
			 (((u32) (a)[2]) << 8) | ((u32) (a)[3]))
#define RTW_PUT_BE32(a, val)					\
	do {							\
		(a)[0] = (u8) ((((u32) (val)) >> 24) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[2] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[3] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_LE32(a) ((((u32) (a)[3]) << 24) | (((u32) (a)[2]) << 16) | \
			 (((u32) (a)[1]) << 8) | ((u32) (a)[0]))
#define RTW_PUT_LE32(a, val)					\
	do {							\
		(a)[3] = (u8) ((((u32) (val)) >> 24) & 0xff);	\
		(a)[2] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[0] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_BE64(a) ((((u64) (a)[0]) << 56) | (((u64) (a)[1]) << 48) | \
			 (((u64) (a)[2]) << 40) | (((u64) (a)[3]) << 32) | \
			 (((u64) (a)[4]) << 24) | (((u64) (a)[5]) << 16) | \
			 (((u64) (a)[6]) << 8) | ((u64) (a)[7]))
#define RTW_PUT_BE64(a, val)				\
	do {						\
		(a)[0] = (u8) (((u64) (val)) >> 56);	\
		(a)[1] = (u8) (((u64) (val)) >> 48);	\
		(a)[2] = (u8) (((u64) (val)) >> 40);	\
		(a)[3] = (u8) (((u64) (val)) >> 32);	\
		(a)[4] = (u8) (((u64) (val)) >> 24);	\
		(a)[5] = (u8) (((u64) (val)) >> 16);	\
		(a)[6] = (u8) (((u64) (val)) >> 8);	\
		(a)[7] = (u8) (((u64) (val)) & 0xff);	\
	} while (0)

#define RTW_GET_LE64(a) ((((u64) (a)[7]) << 56) | (((u64) (a)[6]) << 48) | \
			 (((u64) (a)[5]) << 40) | (((u64) (a)[4]) << 32) | \
			 (((u64) (a)[3]) << 24) | (((u64) (a)[2]) << 16) | \
			 (((u64) (a)[1]) << 8) | ((u64) (a)[0]))

struct osdep_service_ops
{
  u8* (*rtw_vmalloc)( u32 sz );
  u8* (*rtw_zvmalloc)( u32 sz );
  void (*rtw_vmfree)( u8 *pbuf, u32 sz );
  u8* (*rtw_malloc)( u32 sz );
  u8* (*rtw_zmalloc)( u32 sz );
  void (*rtw_mfree)( u8 *pbuf, u32 sz );
  void (*rtw_memcpy)( void* dst, void* src, u32 sz );
  int (*rtw_memcmp)( void *dst, void *src, u32 sz );
  void (*rtw_memset)( void *pbuf, int c, u32 sz );
  void (*rtw_init_sema)( _sema *sema, int init_val );
  void (*rtw_free_sema)( _sema *sema );
  void (*rtw_up_sema)( _sema *sema );
  void (*rtw_up_sema_from_isr)( _sema *sema );
  u32 (*rtw_down_timeout_sema)( _sema *sema, u32 timeout );
  void (*rtw_mutex_init)( _mutex *pmutex );
  void (*rtw_mutex_free)( _mutex *pmutex );
  void (*rtw_mutex_get)( _mutex *pmutex );
  int (*rtw_mutex_get_timeout)( _mutex *pmutex, u32 timeout_ms );
  void (*rtw_mutex_put)( _mutex *pmutex );
  void (*rtw_enter_critical)( _lock *plock, _irqL *pirqL );
  void (*rtw_exit_critical)( _lock *plock, _irqL *pirqL );
  void (*rtw_enter_critical_from_isr)( _lock *plock, _irqL *pirqL );
  void (*rtw_exit_critical_from_isr)( _lock *plock, _irqL *pirqL );
  void (*rtw_enter_critical_bh)( _lock *plock, _irqL *pirqL );
  void (*rtw_exit_critical_bh)( _lock *plock, _irqL *pirqL );
  int (*rtw_enter_critical_mutex)( _mutex *pmutex, _irqL *pirqL );
  void (*rtw_exit_critical_mutex)( _mutex *pmutex, _irqL *pirqL );
  void (*rtw_spinlock_init)( _lock *plock );
  void (*rtw_spinlock_free)( _lock *plock );
  void (*rtw_spin_lock)( _lock *plock );
  void (*rtw_spin_unlock)( _lock *plock );
  void (*rtw_spinlock_irqsave)( _lock *plock, _irqL *irqL );
  void (*rtw_spinunlock_irqsave)( _lock *plock, _irqL *irqL );
  int (*rtw_init_xqueue)( _xqueue* queue, const char* name, u32 message_size,
    u32 number_of_messages );
  int (*rtw_push_to_xqueue)( _xqueue* queue, void* message, u32 timeout_ms );
  int (*rtw_pop_from_xqueue)( _xqueue* queue, void* message, u32 timeout_ms );
  int (*rtw_deinit_xqueue)( _xqueue* queue );
  u32 (*rtw_get_current_time)( void );
  u32 (*rtw_systime_to_ms)( u32 systime );
  u32 (*rtw_systime_to_sec)( u32 systime );
  u32 (*rtw_ms_to_systime)( u32 ms );
  u32 (*rtw_sec_to_systime)( u32 sec );
  void (*rtw_msleep_os)( int ms );
  void (*rtw_usleep_os)( int us );
  void (*rtw_mdelay_os)( int ms );
  void (*rtw_udelay_os)( int us );
  void (*rtw_yield_os)( void );
  void (*ATOMIC_SET)( ATOMIC_T *v, int i );
  int (*ATOMIC_READ)( ATOMIC_T *v );
  void (*ATOMIC_ADD)( ATOMIC_T *v, int i );
  void (*ATOMIC_SUB)( ATOMIC_T *v, int i );
  void (*ATOMIC_INC)( ATOMIC_T *v );
  void (*ATOMIC_DEC)( ATOMIC_T *v );
  int (*ATOMIC_ADD_RETURN)( ATOMIC_T *v, int i );
  int (*ATOMIC_SUB_RETURN)( ATOMIC_T *v, int i );
  int (*ATOMIC_INC_RETURN)( ATOMIC_T *v );
  int (*ATOMIC_DEC_RETURN)( ATOMIC_T *v );
  u64 (*rtw_modular64)( u64 x, u64 y );
  int (*rtw_get_random_bytes)( void* dst, u32 size );
  u32 (*rtw_getFreeHeapSize)( void );
  int (*rtw_create_task)( struct task_struct *task, const char *name, u32 stack_size, u32 priority,
    thread_func_t func, void *thctx );
  void (*rtw_delete_task)( struct task_struct *task );
  void (*rtw_wakeup_task)( struct task_struct *task );

#if 0	//TODO
  void (*rtw_init_delayed_work)(struct delayed_work *dwork, work_func_t func, const char *name);
  void (*rtw_deinit_delayed_work)(struct delayed_work *dwork);
  int (*rtw_queue_delayed_work)(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay, void* context);
  BOOLEAN (*rtw_cancel_delayed_work)(struct delayed_work *dwork);
#endif
  void (*rtw_thread_enter)( char *name );
  void (*rtw_thread_exit)( void );
  _timerHandle (*rtw_timerCreate)( const signed char *pcTimerName,
    osdepTickType xTimerPeriodInTicks, u32 uxAutoReload, void * pvTimerID,
    TIMER_FUN pxCallbackFunction );
  u32 (*rtw_timerDelete)( _timerHandle xTimer, osdepTickType xBlockTime );
  u32 (*rtw_timerIsTimerActive)( _timerHandle xTimer );
  u32 (*rtw_timerStop)( _timerHandle xTimer, osdepTickType xBlockTime );
  u32 (*rtw_timerChangePeriod)( _timerHandle xTimer, osdepTickType xNewPeriod,
    osdepTickType xBlockTime );

  void (*rtw_acquire_wakelock)( void );
  void (*rtw_release_wakelock)( void );

  u8 (*rtw_get_scheduler_state)( void );
};
/*********************************** OSDEP API end *****************************************/

#if 0
/* Structure used to pass parameters to each task. */
typedef struct SEMAPHORE_PARAMETERS
{
  xSemaphoreHandle xSemaphore;
//	volatile unsigned long *pulSharedVariable;
  portTickType xBlockTime;
}xSemaphoreParameters;
#endif

//#define RTW_STATUS_TIMEDOUT -110

#define MAX_SEMA_COUNT                      32	/* the maximum count of a semaphore */

typedef xSemaphoreHandle _Sema;
typedef xSemaphoreHandle _Mutex;
typedef u32 _Lock;
typedef struct TIMER_LIST _Timer;

//typedef unsigned char	                _buffer;

typedef unsigned long _IRQL;
//typedef	struct net_device *     _nic_hdl;
typedef xTaskHandle _THREAD_HDL_;
typedef VOID THREAD_RETURN;
typedef VOID* THREAD_CONTEXT;

#ifndef mdelay
#define mdelay(t)					((t/portTICK_RATE_MS)>0)?(vTaskDelay(t/portTICK_RATE_MS)):(vTaskDelay(1))
#endif

#ifndef udelay
#define udelay(t)					((t/(portTICK_RATE_MS*1000))>0)?vTaskDelay(t/(portTICK_RATE_MS*1000)):(vTaskDelay(1))
#endif

/* to delete/start/stop a timer it will send a message to the timer task through a message queue,
 so we define the max wait time for message sending */
#define RTL_TIMER_API_MAX_BLOCK_TIME    1000    // unit is ms
#define RTL_TIMER_API_MAX_BLOCK_TICKS   (RTL_TIMER_API_MAX_BLOCK_TIME/portTICK_RATE_MS)

typedef VOID
(*RTL_TIMER_CALL_BACK)( void *pContext );

typedef struct _RTL_TIMER
{
#ifdef PLATFORM_FREERTOS
  xTimerHandle TimerHandle; // the timer handle of created FreeRTOS soft-timer
#endif
  RTL_TIMER_CALL_BACK CallBackFunc; // Callback function of this timer
  u32 msPeriod; // The period of this timer
  void *Context; // Timer specific context.
  u8 isPeriodical;   // is a periodical timer
  u8 TimerName[ 35 ];  // the Name of timer
} RTL_TIMER, *PRTL_TIMER;

__inline static VOID RtlEnterCritical( VOID )
{
  portENTER_CRITICAL( );
}

__inline static VOID RtlExitCritical( VOID )
{
  portEXIT_CRITICAL( );
}

__inline static VOID
RtlEnterCriticalBh(
    IN _Lock *plock,
    IN _IRQL *pirqL
)
{
  SpinLockBh(plock);
}

__inline static VOID
RtlExitCriticalBh(
    IN _Lock *plock,
    IN _IRQL *pirqL
)
{
  SpinUnlockBh(plock);
}
__inline static u32
RtlEnterCriticalMutex(
    IN _Mutex *pmutex,
    IN _IRQL *pirqL
)
{
  u32 ret = 0;
  xSemaphoreTake(*pmutex, portMAX_DELAY);
  return ret;
}

__inline static VOID
RtlExitCriticalMutex(
    IN _Mutex *pmutex,
    IN _IRQL *pirqL
)
{
  xSemaphoreGive(*pmutex);
}

__inline static VOID
RtlInitTimer(
    IN _Timer *ptimer,
    IN VOID *Data,
    IN VOID (*pfunc)(VOID *),
    IN VOID* cntx
)
{
  ptimer->Function = pfunc;
  ptimer->Data = (unsigned long)cntx;
  InitTimer(ptimer);
}

__inline static VOID
RtlSetTimer(
    IN _Timer *ptimer,
    IN u32 delay_time
)
{
  ModTimer(ptimer , (JIFFIES+(delay_time*RTL_HZ/1000)));
}

__inline static VOID
RtlCancelTimer(
    IN _Timer *ptimer,
    IN u8 *bcancelled
)
{
  DelTimerSync(ptimer);
  *bcancelled= _TRUE;  //TRUE ==1; FALSE==0
}

__inline static u32
RtlSystime2Ms(
    IN u32 systime
)
{
  return systime * 1000 / RTL_HZ;
}

__inline static u32
RtlMs2Systime(
    IN u32 ms
)
{
  return ms * RTL_HZ / 1000;
}

extern u8* RtlZmalloc( u32 sz );
extern u8* RtlMalloc( u32 sz );
extern VOID RtlMfree( u8 *pbuf, u32 sz );

extern VOID* RtlMalloc2d( u32 h, u32 w, u32 size );
extern VOID RtlMfree2d( VOID *pbuf, u32 h, u32 w, u32 size );

extern VOID RtlInitSema( _Sema *sema, u32 init_val );
extern VOID RtlFreeSema( _Sema *sema );
extern VOID RtlUpSema( _Sema *sema );
extern VOID RtlUpSemaFromISR( _Sema *sema );
extern u32 RtlDownSema( _Sema *sema );
extern u32 RtlDownSemaWithTimeout( _Sema *sema, u32 ms );

extern VOID RtlMutexInit( _Mutex *pmutex );
extern VOID RtlMutexFree( _Mutex *pmutex );

extern VOID RtlSpinlockInit( _Lock *plock );
extern VOID RtlSpinlockFree( _Lock *plock );
extern VOID RtlSpinlock( _Lock *plock );
extern VOID RtlSpinunlock( _Lock *plock );
extern VOID RtlSpinlockEx( _Lock *plock );
extern VOID RtlSpinunlockEx( _Lock *plock );

extern VOID RtlSleepSchedulable( u32 ms );

extern VOID RtlMsleepOS( u32 ms );
extern VOID RtlUsleepOS( u32 us );
extern VOID RtlMdelayOS( u32 ms );
extern VOID RtlUdelayOS( u32 us );

//extern VOID	rtw_mdelay_os(u32 ms);
//extern VOID	rtw_udelay_os(u32 us);

//1TODO: Need Check if we need add this api
extern VOID RtlYieldOS( VOID );

#define RtlUpMutex(mutex)		RtlUpSema(mutex)
#define RtlDownMutex(mutex)		RtlDownSema(mutex)

__inline static u8
RtlCancelTimerEx(
    IN _Timer *ptimer
)
{
  DelTimerSync(ptimer);
  return 0;
}

static __inline VOID
ThreadEnter(
    IN char *name
)
{
  DBG_8195A("\rRTKTHREAD_enter %s\n", name);
}

#define ThreadExit() do{DBG_8195A("\rRTKTHREAD_exit %s\n", __FUNCTION__);}while(0)

__inline static VOID FlushSignalsThread( VOID )
{
#ifdef PLATFORM_LINUX
  if (signal_pending (current))
  {
    flush_signals(current);
  }
#endif
}

#define RTL_RND(sz, r) ((((sz)+((r)-1))/(r))*(r))
#define RTL_RND4(x)	(((x >> 2) + (((x & 3) == 0) ?  0: 1)) << 2)

__inline static u32
RtlRnd4(
    IN u32 sz
)
{

  u32 val;

  val = ((sz >> 2) + ((sz & 3) ? 1: 0)) << 2;

  return val;

}

__inline static u32
RtlRnd8(
    IN u32 sz
)
{

  u32 val;

  val = ((sz >> 3) + ((sz & 7) ? 1: 0)) << 3;

  return val;

}

__inline static u32
RtlRnd128(
    IN u32 sz
)
{

  u32 val;

  val = ((sz >> 7) + ((sz & 127) ? 1: 0)) << 7;

  return val;

}

__inline
static u32 RtlRnd256(
    IN u32 sz
)
{

  u32 val;

  val = ((sz >> 8) + ((sz & 255) ? 1: 0)) << 8;

  return val;

}

__inline static u32
RtlRnd512(
    IN u32 sz
)
{

  u32 val;

  val = ((sz >> 9) + ((sz & 511) ? 1: 0)) << 9;

  return val;

}

__inline static u32
BitShift(
    IN u32 BitMask
)
{
  u32 i;

  for (i = 0; i <= 31; i++)
  if (((BitMask>>i) & 0x1) == 1) break;

  return i;
}

//#ifdef __GNUC__
#ifdef PLATFORM_LINUX
#define STRUCT_PACKED __attribute__ ((packed))
#else
#define STRUCT_PACKED
#endif

//Atomic integer operations
#define RTL_ATOMIC_T atomic_t

static inline VOID RTL_ATOMIC_SET(
    IN RTL_ATOMIC_T *v,
    IN u32 i
)
{
  AtomicSet(i,v);
}

static inline uint32_t RTL_ATOMIC_READ(
    IN RTL_ATOMIC_T *v
)
{
  return AtomicRead(v);
}

static inline VOID RTL_ATOMIC_ADD(
    IN RTL_ATOMIC_T *v,
    IN u32 i
)
{
  AtomicAdd(i,v);
}
static inline VOID
RTL_ATOMIC_SUB(
    IN RTL_ATOMIC_T *v,
    IN u32 i
)
{
  AtomicSub(i,v);
}

static inline VOID
RTL_ATOMIC_INC(
    IN RTL_ATOMIC_T *v
)
{
  AtomicInc(v);
}

static inline VOID
RTL_ATOMIC_DEC(
    IN RTL_ATOMIC_T *v
)
{
  AtomicDec(v);
}

static inline u32
RTL_ATOMIC_ADD_RETURN(
    IN RTL_ATOMIC_T *v,
    IN u32 i
)
{
  return AtomicAddReturn(i,v);
}

static inline u32
RTL_ATOMIC_SUB_RETURN(
    IN RTL_ATOMIC_T *v,
    IN u32 i
)
{
  return AtomicSubReturn(i,v);
}

static inline u32
RTL_ATOMIC_INC_RETURN(
    IN RTL_ATOMIC_T *v
)
{
  return AtomicIncReturn(v);
}

static inline u32
RTL_ATOMIC_DEC_RETURN(
    IN RTL_ATOMIC_T *v
)
{
  return AtomicDecReturn(v);
}

extern u64 RtlModular64( u64 x, u64 y );

/* Macros for handling unaligned memory accesses */
#if 0
#define RTW_GET_BE16(a) ((u16) (((a)[0] << 8) | (a)[1]))
#define RTW_PUT_BE16(a, val)			\
	do {					\
		(a)[0] = ((u16) (val)) >> 8;	\
		(a)[1] = ((u16) (val)) & 0xff;	\
	} while (0)

#define RTW_GET_LE16(a) ((u16) (((a)[1] << 8) | (a)[0]))
#define RTW_PUT_LE16(a, val)			\
	do {					\
		(a)[1] = ((u16) (val)) >> 8;	\
		(a)[0] = ((u16) (val)) & 0xff;	\
	} while (0)

#define RTW_GET_BE24(a) ((((u32) (a)[0]) << 16) | (((u32) (a)[1]) << 8) | \
			 ((u32) (a)[2]))
#define RTW_PUT_BE24(a, val)					\
	do {							\
		(a)[0] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[2] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_BE32(a) ((((u32) (a)[0]) << 24) | (((u32) (a)[1]) << 16) | \
			 (((u32) (a)[2]) << 8) | ((u32) (a)[3]))
#define RTW_PUT_BE32(a, val)					\
	do {							\
		(a)[0] = (u8) ((((u32) (val)) >> 24) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[2] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[3] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_LE32(a) ((((u32) (a)[3]) << 24) | (((u32) (a)[2]) << 16) | \
			 (((u32) (a)[1]) << 8) | ((u32) (a)[0]))
#define RTW_PUT_LE32(a, val)					\
	do {							\
		(a)[3] = (u8) ((((u32) (val)) >> 24) & 0xff);	\
		(a)[2] = (u8) ((((u32) (val)) >> 16) & 0xff);	\
		(a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);	\
		(a)[0] = (u8) (((u32) (val)) & 0xff);		\
	} while (0)

#define RTW_GET_BE64(a) ((((u64) (a)[0]) << 56) | (((u64) (a)[1]) << 48) | \
			 (((u64) (a)[2]) << 40) | (((u64) (a)[3]) << 32) | \
			 (((u64) (a)[4]) << 24) | (((u64) (a)[5]) << 16) | \
			 (((u64) (a)[6]) << 8) | ((u64) (a)[7]))
#define RTW_PUT_BE64(a, val)				\
	do {						\
		(a)[0] = (u8) (((u64) (val)) >> 56);	\
		(a)[1] = (u8) (((u64) (val)) >> 48);	\
		(a)[2] = (u8) (((u64) (val)) >> 40);	\
		(a)[3] = (u8) (((u64) (val)) >> 32);	\
		(a)[4] = (u8) (((u64) (val)) >> 24);	\
		(a)[5] = (u8) (((u64) (val)) >> 16);	\
		(a)[6] = (u8) (((u64) (val)) >> 8);	\
		(a)[7] = (u8) (((u64) (val)) & 0xff);	\
	} while (0)

#define RTW_GET_LE64(a) ((((u64) (a)[7]) << 56) | (((u64) (a)[6]) << 48) | \
			 (((u64) (a)[5]) << 40) | (((u64) (a)[4]) << 32) | \
			 (((u64) (a)[3]) << 24) | (((u64) (a)[2]) << 16) | \
			 (((u64) (a)[1]) << 8) | ((u64) (a)[0]))
#endif

extern PRTL_TIMER
RtlTimerCreate(
    IN char *pTimerName,
    IN u32 TimerPeriodMS,
    IN RTL_TIMER_CALL_BACK CallbckFunc,
    IN void *pContext,
    IN u8 isPeriodical
);

extern VOID
RtlTimerDelete(
    IN PRTL_TIMER pTimerHdl
);

extern u8
RtlTimerStart(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
);

extern u8
RtlTimerStop(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
);

extern u8
RtlTimerReset(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
);

extern u8
RtlTimerChangePeriod(
    IN PRTL_TIMER pTimerHdl,
    IN u32 NewPeriodMS,
    IN u8 isFromISR
);

#define JIFFIES	        xTaskGetTickCount()

enum
{
  TIMER_NO_INIT = 0,
  TIMER_INIT = 1,
  TIMER_START = 2,
  TIMER_DISABLE = 3
};

struct TIMER_LIST
{
  xTimerHandle TimeHdl;
  u32 Flag;
  unsigned long Data;
  VOID (*Function)( void * );
  u32 TimerID;
};

static inline VOID
InitTimer(
    IN struct TIMER_LIST *Timer
)
{
#ifdef RTK_MODE_TIMER
  u32 data = Timer->Data;
#endif
#ifndef PLATFORM_FREERTOS
  u32 Flags;
#endif
  u32 TimerID = Timer->TimerID;
  VOID (*Function)(VOID *) = Timer->Function;
//    xTimerHandle timer_handle;

#ifdef PLATFORM_FREERTOS
  SaveAndCli();
#else
  SaveAndCli(Flags);
#endif

  if (Timer->Flag != TIMER_DISABLE)
  {
    if (Timer->Flag == TIMER_NO_INIT)
    {
      Timer->TimeHdl = xTimerCreate( (const char *)"Timer",// Just a test name, not used by the kernel.
          ( 100 ),// The timer period in ticks.
          pdFALSE,// The timers will auto-reload themselves when they expire.
          ( void * ) TimerID,// Assign each timer a unique id equal to its array index.
          Function
#ifdef RTK_MODE_TIMER
          ,data				// Each timer calls the same callback when it expires.
#endif
      );
      if (NULL == Timer->TimeHdl)
      {
        DBG_ERROR_LOG("\rInitial Timer fail !!!!!!!!!\n");
      }
      else
      {
        TimerID++;
      }

      Timer->Flag = TIMER_INIT;
    }
    else if (Timer->Flag == TIMER_START)
    {
      xTimerStop(Timer->TimeHdl,0);
      Timer->Flag = TIMER_DISABLE;
    }
  }

#ifdef PLATFORM_FREERTOS
  RestoreFlags();
#else
  RestoreFlags(Flags);
#endif
}

static inline void
ModTimer(
    IN struct TIMER_LIST *Timer,
    IN u32 TimeoutTicks
)
{
#ifndef PLATFORM_FREERTOS
  u32 Flags;
#endif

  void (*Function)(void *) = Timer->Function;

#ifdef PLATFORM_FREERTOS
  SaveAndCli();
#else
  SaveAndCli(Flags);
#endif

  if (Timer->Flag == TIMER_NO_INIT)
  {
    if (Timer->Function)
    {
      Timer->TimeHdl = xTimerCreate((const char *)"Timer",// Just a text name, not used by the kernel.
          ( 100 ),// The timer period in ticks.
          pdFALSE,// The timers will auto-reload themselves when they expire.
          ( void * ) Timer->TimerID,// Assign each timer a unique id equal to its array index.
          Function
#ifdef RTK_MODE_TIMER
          ,Timer->Data	// Each timer calls the same callback when it expires.
#endif
      );
      if (NULL == Timer->TimeHdl)
      {
        DBG_ERROR_LOG("\rInitial Timer fail !!!!!!!!!\n");
      }
      else
      {
        Timer->TimerID++;
      }

      Timer->Flag = TIMER_INIT;
    }
    else
    {
      //printf("###mod_timer() not initilized, timer->flag=%d timer->function=%p timeout_ticks=%llu###\n", timer->flag, timer->function, timeout_ticks);
#ifdef PLATFORM_FREERTOS
      RestoreFlags();
#else
      RestoreFlags(Flags);
#endif
      return;
    }
  }
  else if (Timer->Flag == TIMER_START)
  {
    xTimerStop(Timer->TimeHdl,0);
    Timer->Flag = TIMER_DISABLE;
  }

  TimeoutTicks -= xTaskGetTickCount();
  if (TimeoutTicks <= 0)
  TimeoutTicks = 2;

  if (xTimerStart(Timer->TimeHdl, TimeoutTicks ))
  Timer->Flag = TIMER_START;
  else
  DBG_ERROR_LOG("\r###mod_timer() - no slots available###\n");
#ifdef PLATFORM_FREERTOS
  RestoreFlags();
#else
  RestoreFlags(Flags);
#endif
}

static inline int
TimerPending (
    IN const struct TIMER_LIST *Timer
)
{
  if (Timer->TimeHdl && Timer->Flag != TIMER_NO_INIT)
  return 1;
  else
  return 0;
}

static inline void
DelTimerSync(
    IN struct TIMER_LIST *Timer
)
{
#ifdef PLATFORM_FREERTOS
  SaveAndCli();
#else
  u32 Flags;
  SaveAndCli(Flags);
#endif
  if (Timer->TimeHdl && Timer->Flag != TIMER_INIT)
  {
    if (Timer->Flag == TIMER_START)
    xTimerStop(Timer->TimeHdl, 0);

    xTimerDelete(Timer->TimeHdl, 0);
    Timer->Flag = TIMER_NO_INIT;
  }

#ifdef PLATFORM_FREERTOS
  RestoreFlags();
#else
  RestoreFlags(Flags);
#endif
}

/*
 *      These inlines deal with timer wrapping correctly. You are
 *      strongly encouraged to use them
 *      1. Because people otherwise forget
 *      2. Because if the timer wrap changes in future you wont have to
 *         alter your driver code.
 *
 * time_after(a,b) returns true if the time a is after time b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#define TIME_AFTER(a,b)		((long)(b) - (long)(a) < 0)
#define TIMER_BEFORE(a,b)		TIME_AFTER(b,a)

#define TIME_AFTER_EQ(a,b)		((long)(a) - (long)(b) >= 0)
#define TIMER_BEFORE_EQ(a,b)		TIME_AFTER_EQ(b,a)

#if 0
#define __init
#define __exit
#define __devinit
#define __devexit
#endif
#define RTL_HZ                          100

#define SemaInit(sem, value)            vSemaphoreCreateBinary(sem)
#define SemaPost(sem)                   xSemaphoreGive(sem)
#define SemaWait(sem, block_time)       xSemaphoreTake(sem, block_time)
//#define printk                          DiagPrintf

#define SpinLockInit(lock)              do { } while (0)
#define SpinLock(x)                     do { } while (0)
#define SpinUnlock(x)                   do { } while (0)
#define SpinLockBh(x)                   do { } while (0)
#define SpinUnlockBh(x)                 do { } while (0)
#ifdef PLATFORM_FREERTOS
#define RestoreFlags()                  portEXIT_CRITICAL()
#define SaveAndCli()			        portENTER_CRITICAL()
#define SpinLockIrqSave(lock, flags)	SaveAndCli()
#define SpinUnlockIrqRestore(l, f)	    RestoreFlags()
#else
#define RestoreFlags(x)                 portENABLE_INTERRUPTS()
#define SaveAndCli(x)			        portDISABLE_INTERRUPTS()
#define SpinLockIrqSave(lock, flags)	SaveAndCli(flags)
#define SpinUnlockIrqRestore(l, f)	    RestoreFlags(f)
#endif

//#define RtlKmalloc(size, flag)          pvPortMallocAligned(size, 0)
#define RtlKmalloc(size, flag)          pvPortMalloc(size)
#define RtlKfree(pv)                    vPortFreeAligned(pv)

#ifdef CONFIG_TIMER_MODULE
#define __Delay(t)                  HalDelayUs(t)
#else
static __inline__ u32 __Delay( u32 us )
{
  DBG_8195A( "No Delay: please enable hardware Timer\n" );
}
#endif

#define Mdelay(t)					__Delay(t*1000)
#define Udelay(t)					__Delay(t)

#define ASSERT(_bool_)					do { } while (0)

//#define panic_printk				DiagPrintf
//#define sprintf						DiagPrintf
//#define diag_sprintf                DiagPrintf

//1TODO: Need check again; the below just for compile ok ; chris

/*
 * ATOMIC_READ - read atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically reads the value of @v.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
//#define AtomicRead(v)  ((*v))
static __inline__ u32
AtomicRead(
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    u32 Temp;

    SaveAndCli();
    Temp = v->counter;
    RestoreFlags();

    return Temp;

#else
   u32 Temp, Flags;

   SaveAndCli( Flags );Temp = v->counter;
   RestoreFlags( Flags );

return Temp;
#endif
}

/*
 * ATOMIC_SET - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
//#define AtomicSet(v,i) ((v)->counter = (i))
static __inline__ VOID
AtomicSet(
    IN  u32 i,
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    SaveAndCli();
    v->counter = i;
    RestoreFlags();
#else
    u32 Flags;

    SaveAndCli( Flags );v->counter = i;
    RestoreFlags( Flags );
#endif
}

/*
 * The MIPS I implementation is only atomic with respect to
 * interrupts.  R3000 based multiprocessor machines are rare anyway ...
 *
 * AtomicAdd - add integer to atomic variable
 * @i: integer value to add
 * @v: pointer of type atomic_t
 *
 * Atomically adds @i to @v.  Note that the guaranteed useful range
 * of an atomic_t is only 24 bits.
 */
static __inline__ VOID
AtomicAdd(
    IN  u32 i,
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    SaveAndCli();
    v->counter += i;
    RestoreFlags();
#else
    u32 Flags;

    SaveAndCli( Flags );v->counter += i;
    RestoreFlags( Flags );
#endif
}

/*
 * AtomicSub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 *
 * Atomically subtracts @i from @v.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
static __inline__ void
AtomicSub(
    IN  u32 i,
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    SaveAndCli();
    v->counter -= i;
    RestoreFlags();
#else
    u32 Flags;

    SaveAndCli( Flags );v->counter -= i;
    RestoreFlags( Flags );
#endif
}

static __inline__ u32
AtomicAddReturn(
    IN  u32 i,
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    u32 Temp;

    SaveAndCli();
    Temp = v->counter;
    Temp += i;
    v->counter = Temp;
    RestoreFlags();

    return Temp;

#else
       u32 Temp, Flags;

       SaveAndCli( Flags );Temp = v->counter;
       Temp += i;
       v->counter = Temp;
       RestoreFlags( Flags );

return Temp;
#endif
}

static __inline__ u32
AtomicSubReturn(
    IN  u32 i,
    IN  atomic_t * v
)
{
#ifdef PLATFORM_FREERTOS
    u32 Temp;

    SaveAndCli();
    Temp = v->counter;
    Temp -= i;
    v->counter = Temp;
    RestoreFlags();

    return Temp;

#else

       u32 Temp, Flags;

       SaveAndCli( Flags );Temp = v->counter;
       Temp -= i;
       v->counter = Temp;
       RestoreFlags( Flags );

return Temp;
#endif
}

/*
 * ATOMIC_INC - increment atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically increments @v by 1.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
#define AtomicInc(v) AtomicAdd(1,(v))

#define AtomicIncReturn(v) AtomicAddReturn(1,(v))

/*
 * ATOMIC_DEC - decrement and test
 * @v: pointer of type atomic_t
 *
 * Atomically decrements @v by 1.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
#define AtomicDec(v) AtomicSub(1,(v))

#define AtomicDecReturn(v) AtomicSubReturn(1,(v))

/*
 * ATOMIC_DEC_AND_TEST - decrement by 1 and test
 * @v: pointer of type atomic_t
 *
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
#define AtomicDecAndTest(v) (AtomicSubReturn(1, (v)) == 0)

/* Not needed on 64bit architectures */
static __inline__ u32
__Div64_32(
IN __uint64_t *n,
IN u32 base
)
{
__uint64_t rem = *n;
__uint64_t b = base;
__uint64_t res, d = 1;
u32 high = rem >> 32;

/* Reduce the thing a bit first */
res = 0;
if (high >= base)
{
high /= base;
res = (__uint64_t) high << 32;
rem -= (__uint64_t) (high*base) << 32;
}

while ((__int64_t)b > 0 && b < rem)
{
b = b+b;
d = d+d;
}

do
{
if (rem >= b)
{
rem -= b;
res += d;
}
b >>= 1;
d >>= 1;
}while (d);

*n = res;
return rem;
}

#define DO_DIV(n,base) ({				\
	unsigned int __base = (base);			\
	unsigned int __rem;				\
	(void)(((typeof((n)) *)0) == ((__uint64_t *)0));	\
	if (((n) >> 32) == 0) {			\
		__rem = (unsigned int)(n) % __base;		\
		(n) = (unsigned int)(n) / __base;		\
	} else 						\
		__rem = __Div64_32(&(n), __base);	\
	__rem;						\
 })

#define MBOX_WAIT_NO_TIMEOUT        0xffffffff  // waiting for send/receive message with no timeout
#define MBOX_WAIT_NONE              0           // No wait for send/receive message

typedef enum _MAILBOX_ID_
{
MBOX_ID_WLAN = 0,
MBOX_ID_UART = 1,
MBOX_ID_I2C = 2,
MBOX_ID_I2S = 3,
MBOX_ID_SPI = 4,
MBOX_ID_SDIO = 5,
MBOX_ID_SDIO_MP = 6,

MBOX_ID_MAX = 0xff
} MAILBOX_ID;

#if defined(CONFIG_SDIO_DEVICE_EN) && defined(CONFIG_SDIO_DEVICE_NORMAL)
typedef enum _MSG_TYPE_SDIO
{
MSG_SDIO_RX_PKT=1,		// request to send a SDIO RX packet to the host side
MSG_SDIO_C2H=2,// request to send a C2H message
MSG_SDIO_RPWM=3,// request to set the RPWM
MSG_SDIO_MP_LOOP_TXPKT=4,// request to loopback this TX packet

MSG_SDIO_MAX=0xff
}MSG_TYPE_SDIO;
#endif  // end  of "#ifdef CONFIG_SDIO_DEVICE_EN"

/* the data structure of a MailBox to deliver message blocks */
typedef struct _RTL_MAILBOX_
{
void *mbox_hdl;      // the mailbox handle which return from OS create queue API
_Sema *pWakeSema;     // the semaphore to wakeup the message receiving task
_LIST mbox_list;      // the link list to chain all created mailbox
u8 mbox_id; /* the ID of this Mailbox, this ID is
 used to locate the MBox for send/get message */
} RTL_MAILBOX, *PRTL_MAILBOX;

/* the data structure of a message block */
typedef struct _RTL_MSG_BLK
{
u8 MsgType;		// the message type
u8 Reserved;       // reserved
u16 DateLen;        // the vaild data length of the pBuf
u32 Para;           // the optional parameters associated with this message type
u8 *pBuf;          // point to a data buffer associated with this message type
} MSG_BLK, *PMSG_BLK;

/* the data structure for system level message block management */
typedef struct _RTL_MBOX_ROOT_
{
_LIST mbox_list;			// the link list of all created mailbox
_Mutex Mutex;				// the Mutex to protect the mailbox create/delete procedure
u8 isInitialed;        // is this Mailbox link-list initialed
} RTL_MBOX_ROOT, *PRTL_MBOX_ROOT;

// Export Funcction API
extern PRTL_MAILBOX RtlMailboxCreate(
IN u8 MboxID,
IN u32 MboxSize,
IN _Sema *pWakeSema
);

extern VOID RtlMailboxDel(
IN PRTL_MAILBOX MboxHdl
);

extern u8 RtlMailboxSendToBack(
IN u8 MboxID,
IN MSG_BLK *pMsg,
IN u32 MSToWait,
IN u8 IsFromISR
);

extern u8 RtlMailboxSendToFront(
IN u8 MboxID,
IN MSG_BLK *pMsg,
IN u32 MSToWait,
IN u8 IsFromISR
);

extern u8 RtlMailboxReceive(
IN u8 MboxID,
OUT MSG_BLK *pMsg,
IN u32 MSToWait,
IN u8 IsFromISR
);

extern u8 RtlMailboxPeek(
IN u8 MboxID,
OUT MSG_BLK *pMsg,
IN u32 MSToWait,
IN u8 IsFromISR
);

extern u32 RtlMailboxMsgWaiting(
IN u8 MboxID,
IN u8 IsFromISR
);

typedef enum _RT_DEV_LOCK_E
{
RT_DEV_LOCK_EFUSE = 0,
RT_DEV_LOCK_FLASH = 1,
RT_DEV_LOCK_MAX = 2
} RT_DEV_LOCK_E;

void device_mutex_lock( RT_DEV_LOCK_E device );
void device_mutex_unlock( RT_DEV_LOCK_E device );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_RTOS_H__ */
