#include "rtl8195am_rtos.h"

//#define _DEBUG

#if CONFIG_USE_TCM_HEAP
#define FREE_FILL_CODE     0xDEAD
#define ALLOC_FILL_CODE    0xBEEF

#define ROUND_UP2(x, pad) (((x) + ((pad) - 1)) & ~((pad) - 1))

#define TCM_HEAP_SIZE	(40*1024)

static struct Heap g_tcm_heap;

#if defined (__ICCARM__)
#pragma location=".tcm.heap"
#else
__attribute__((section(".tcm.heap")))
#endif
HEAP_DEFINE_BUF(tcm_heap, TCM_HEAP_SIZE);
//unsigned char tcm_heap[TCM_HEAP_SIZE];

static int g_heap_inited=0;
static _lock tcm_lock;

extern void vPortSetExtFree( void (*free)( void *p ), uint32_t upper, uint32_t lower );

void tcm_heap_init(void)
{
  //#ifdef _DEBUG
  //memset(memory, FREE_FILL_CODE, size);
  //#endif

  //ASSERT2(((int)memory % alignof(heap_buf_t)) == 0,
  //"memory buffer is unaligned, please use the HEAP_DEFINE_BUF() macro to declare heap buffers!\n");

  /* Initialize heap with a single big chunk */
  g_tcm_heap.FreeList = (MemChunk *)&tcm_heap;
  g_tcm_heap.FreeList->next = NULL;
  g_tcm_heap.FreeList->size = sizeof(tcm_heap);

  g_heap_inited = 1;
  rtw_spinlock_init(&tcm_lock);

#if PLATFORM_FREERTOS
  // let RTOS know how to free memory if using as task stack
  vPortSetExtFree(tcm_heap_free, 0x20000000, 0x1fff0000);
#endif
}

void tcm_heap_dump(void)
{
  MemChunk *chunk, *prev;
  struct Heap* h = &g_tcm_heap;

  printf("---Free List--\n\r");
  for (prev = (MemChunk *)&h->FreeList, chunk = h->FreeList;
      chunk;
      prev = chunk, chunk = chunk->next)
  {
    printf(" prev %x, chunk %x, size %d \n\r", prev, chunk, chunk->size);
  }
  printf("--------------\n\r");
}

void *tcm_heap_allocmem(int size)
{
  MemChunk *chunk, *prev;
  struct Heap* h = &g_tcm_heap;
  _irqL irqL;

  rtw_enter_critical(&tcm_lock, &irqL);

  if(!g_heap_inited) tcm_heap_init();

  /* Round size up to the allocation granularity */
  size = ROUND_UP2(size, sizeof(MemChunk));

  /* Handle allocations of 0 bytes */
  if (!size)
  size = sizeof(MemChunk);

  /* Walk on the free list looking for any chunk big enough to
   * fit the requested block size.
   */
  for (prev = (MemChunk *)&h->FreeList, chunk = h->FreeList;
      chunk;
      prev = chunk, chunk = chunk->next)
  {
    if (chunk->size >= size)
    {
      if (chunk->size == size)
      {
        /* Just remove this chunk from the free list */
        prev->next = chunk->next;
#ifdef _DEBUG
        memset(chunk, ALLOC_FILL_CODE, size);
#endif

        rtw_exit_critical(&tcm_lock, &irqL);
        //printf("----ALLOC1-----\n\r");
        //tcm_heap_dump();
        //printf("--------------\n\r");
        return (void *)chunk;
      }
      else
      {
        /* Allocate from the END of an existing chunk */
        chunk->size -= size;
#ifdef _DEBUG
        memset((uint8_t *)chunk + chunk->size, ALLOC_FILL_CODE, size);
#endif
        rtw_exit_critical(&tcm_lock, &irqL);
        //printf("----ALLOC2-----\n\r");
        //tcm_heap_dump();
        //printf("--------------\n\r");

        return (void *)((uint8_t *)chunk + chunk->size);
      }
    }
  }

  rtw_exit_critical(&tcm_lock, &irqL);
  //printf("----ALLOC3-----\n\r");
  //tcm_heap_dump();
  //printf("--------------\n\r");
  return NULL; /* fail */
}

void tcm_heap_freemem(void *mem, int size)
{
  MemChunk *prev;
  //ASSERT(mem);
  struct Heap* h = &g_tcm_heap;
  _irqL irqL;

  rtw_enter_critical(&tcm_lock, &irqL);

  if(!g_heap_inited) tcm_heap_init();

#ifdef _DEBUG
  memset(mem, FREE_FILL_CODE, size);
#endif

  /* Round size up to the allocation granularity */
  size = ROUND_UP2(size, sizeof(MemChunk));

  /* Handle allocations of 0 bytes */
  if (!size)
  size = sizeof(MemChunk);

  /* Special cases: first chunk in the free list or memory completely full */
  //ASSERT((uint8_t*)mem != (uint8_t*)h->FreeList);
  if (((uint8_t *)mem) < ((uint8_t *)h->FreeList) || !h->FreeList)
  {
    /* Insert memory block before the current free list head */
    prev = (MemChunk *)mem;
    prev->next = h->FreeList;
    prev->size = size;
    h->FreeList = prev;
  }
  else /* Normal case: not the first chunk in the free list */
  {
    /*
     * Walk on the free list. Stop at the insertion point (when mem
     * is between prev and prev->next)
     */
    prev = h->FreeList;
    while (prev->next < (MemChunk *)mem && prev->next)
    prev = prev->next;

    /* Make sure mem is not *within* prev */
    //ASSERT((uint8_t*)mem >= (uint8_t*)prev + prev->size);
    /* Should it be merged with previous block? */
    if (((uint8_t *)prev) + prev->size == ((uint8_t *)mem))
    {
      /* Yes */
      prev->size += size;
    }
    else /* not merged with previous chunk */
    {
      MemChunk *curr = (MemChunk*)mem;

      /* insert it after the previous node
       * and move the 'prev' pointer forward
       * for the following operations
       */
      curr->next = prev->next;
      curr->size = size;
      prev->next = curr;

      /* Adjust for the following test */
      prev = curr;
    }
  }

  /* Also merge with next chunk? */
  if (((uint8_t *)prev) + prev->size == ((uint8_t *)prev->next))
  {
    prev->size += prev->next->size;
    prev->next = prev->next->next;

    /* There should be only one merge opportunity, becuase we always merge on free */
    //ASSERT((uint8_t*)prev + prev->size != (uint8_t*)prev->next);
  }

  rtw_exit_critical(&tcm_lock, &irqL);
  //printf("---FREE %x--\n\r", mem);
  //tcm_heap_dump();
  //printf("--------------\n\r");

}

int tcm_heap_freeSpace(void)
{
  int free_mem = 0;
  struct Heap* h = &g_tcm_heap;
  _irqL irqL;
  MemChunk *chunk;

  rtw_enter_critical(&tcm_lock, &irqL);

  if(!g_heap_inited) tcm_heap_init();

  for (chunk = h->FreeList; chunk; chunk = chunk->next)
  free_mem += chunk->size;

  rtw_exit_critical(&tcm_lock, &irqL);
  return free_mem;
}

/**
 * Standard malloc interface
 */
void *tcm_heap_malloc(int size)
{
  int *mem;

  size += sizeof(int);
  if ((mem = (int*)tcm_heap_allocmem(size)))
  {
    *mem++ = size;
  }

  return mem;
}

/**
 * Standard calloc interface
 */
void *tcm_heap_calloc(int size)
{
  void *mem;

  if ((mem = tcm_heap_malloc(size)))
  memset(mem, 0, size);

  return mem;
}

/**
 * Free a block of memory, determining its size automatically.
 *
 * \param h    Heap from which the block was allocated.
 * \param mem  Pointer to a block of memory previously allocated with
 *             either heap_malloc() or heap_calloc().
 *
 * \note If \a mem is a NULL pointer, no operation is performed.
 *
 * \note Freeing the same memory block twice has undefined behavior.
 *
 * \note This function works like the ANSI C free().
 */
void tcm_heap_free(void *mem)
{
  int *_mem = (int *)mem;

  if (_mem)
  {
    --_mem;
    tcm_heap_freemem(_mem, *_mem);
  }
}

static void alloc_test(int size, int test_len)
{
  //Simple test
  uint8_t *a[100];
  int i, j;

  for (i = 0; i < test_len; i++)
  {
    a[i] = tcm_heap_allocmem(size);
    //ASSERT(a[i]);
    for (j = 0; j < size; j++)
    a[i][j] = i;
  }

  //ASSERT(heap_freeSpace(&h) == HEAP_SIZE - test_len * ROUND_UP2(size, sizeof(MemChunk)));

  for (i = 0; i < test_len; i++)
  {
    for (j = 0; j < size; j++)
    {
      printf("a[%d][%d] = %d\n", i, j, a[i][j]);
      //ASSERT(a[i][j] == i);
    }
    tcm_heap_freemem(a[i], size);
  }
  //ASSERT(heap_freeSpace(&h) == HEAP_SIZE);
}

#define ALLOC_SIZE 256
#define ALLOC_SIZE2 1024
#define TEST_LEN 20
#define TEST_LEN2 10
#define HEAP_SIZE 59*1024
int tcm_heap_testRun(void)
{
  alloc_test(ALLOC_SIZE, TEST_LEN);
  alloc_test(ALLOC_SIZE2, TEST_LEN2);
  /* Try to allocate the whole heap */
  uint8_t *b = tcm_heap_allocmem(HEAP_SIZE);
  int i, j;
  //ASSERT(b);
  //ASSERT(heap_freeSpace(&h) == 0);

  //ASSERT(!heap_allocmem(&h, HEAP_SIZE));

  for (j = 0; j < HEAP_SIZE; j++)
  b[j] = j;

  for (j = 0; j < HEAP_SIZE; j++)
  {
    printf("b[%d] = %d\n", j, j);
    //ASSERT(b[j] == (j & 0xff));
  }
  tcm_heap_freemem(b, HEAP_SIZE);
  //ASSERT(heap_freeSpace(&h) == HEAP_SIZE);

  return 0;
}

#endif

#define OSDEP_DBG(x, ...) do {} while(0)

extern struct osdep_service_ops osdep_service;

#ifdef CONFIG_LITTLE_ENDIAN
u16
_htons(u16 n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

u16
_ntohs(u16 n)
{
  return _htons(n);
}

u32
_htonl(u32 n)
{
  return ((n & 0xff) << 24) |
  ((n & 0xff00) << 8) |
  ((n & 0xff0000UL) >> 8) |
  ((n & 0xff000000UL) >> 24);
}

u32
_ntohl(u32 n)
{
  return _htonl(n);
}

#endif /* CONFIG_LITTLE_ENDIAN */
/*
 * Translate the OS dependent @param error_code to OS independent RTW_STATUS_CODE
 * @return: one of RTW_STATUS_CODE
 */
int RTW_STATUS_CODE( int error_code )
{
  if ( error_code >= 0 )
    return _SUCCESS;

  return _FAIL;
}

u32 rtw_atoi( u8* s )
{
  int num = 0, flag = 0;
  int i;

  for ( i = 0; i <= strlen( (char *) s ); i++ )
  {
    if ( s[ i ] >= '0' && s[ i ] <= '9' )
      num = num * 10 + s[ i ] - '0';
    else if ( s[ 0 ] == '-' && i == 0 )
      flag = 1;
    else
      break;
  }

  if ( flag == 1 )
    num = num * -1;

  return ( num );
}
void *tcm_heap_malloc( int size );
void *tcm_heap_calloc( int size );
u8* _rtw_vmalloc( u32 sz )
{
  u8 *pbuf = NULL;
#if CONFIG_USE_TCM_HEAP
  pbuf = tcm_heap_malloc(sz);
#endif
  if ( pbuf == NULL )
  {
    if ( osdep_service.rtw_vmalloc )
    {
      pbuf = osdep_service.rtw_vmalloc( sz );
    }
    else
      OSDEP_DBG( "Not implement osdep service: rtw_vmalloc" );
  }
  return pbuf;
}

u8* _rtw_zvmalloc( u32 sz )
{
  u8 *pbuf = NULL;
#if CONFIG_USE_TCM_HEAP
  pbuf = tcm_heap_calloc(sz);
#endif
  if ( pbuf == NULL )
  {
    if ( osdep_service.rtw_zvmalloc )
    {
      pbuf = osdep_service.rtw_zvmalloc( sz );
    }
    else
      OSDEP_DBG( "Not implement osdep service: rtw_zvmalloc" );
  }
  return pbuf;
}

void _rtw_vmfree( u8 *pbuf, u32 sz )
{

#if CONFIG_USE_TCM_HEAP
  if( (u32)pbuf > 0x1FFF0000 && (u32)pbuf < 0x20000000 )
  tcm_heap_free(pbuf);
  else
#endif
  {
    if ( osdep_service.rtw_vmfree )
    {
      osdep_service.rtw_vmfree( pbuf, sz );
    }
    else
      OSDEP_DBG( "Not implement osdep service: rtw_vmfree" );
  }
}

u8* _rtw_malloc( u32 sz )
{
  if ( osdep_service.rtw_malloc )
  {
    u8 *pbuf = osdep_service.rtw_malloc( sz );
    return pbuf;
  }
  else
    OSDEP_DBG( "Not implement osdep service: rtw_malloc" );

  return NULL;
}

u8* _rtw_zmalloc( u32 sz )
{
  if ( osdep_service.rtw_zmalloc )
  {
    u8 *pbuf = osdep_service.rtw_zmalloc( sz );
    return pbuf;
  }
  else
    OSDEP_DBG( "Not implement osdep service: rtw_zmalloc" );

  return NULL;
}

void _rtw_mfree( u8 *pbuf, u32 sz )
{
  if ( osdep_service.rtw_mfree )
  {
    osdep_service.rtw_mfree( pbuf, sz );
  }
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mfree" );
}

#ifdef CONFIG_MEM_MONITOR
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
_list mem_table;
int mem_used_num;
#endif
int min_free_heap_size;

void init_mem_monitor(_list *pmem_table, int *used_num)
{
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  rtw_init_listhead(pmem_table);
  *used_num = 0;
#endif
  min_free_heap_size = rtw_getFreeHeapSize();
}

void deinit_mem_monitor(_list *pmem_table, int *used_num)
{
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  _list *plist;
  struct mem_entry *mem_entry;

  if(*used_num > 0)
  DBG_ERR("Have %d mem_entry kept in monitor", *used_num);
  else
  DBG_INFO("No mem_entry kept in monitor");

  save_and_cli();

  while (rtw_end_of_queue_search(pmem_table, get_next(pmem_table)) == _FALSE)
  {
    plist = get_next(pmem_table);
    mem_entry = LIST_CONTAINOR(plist, struct mem_entry, list);

    DBG_ERR("Not release memory at %p with size of %d", mem_entry->ptr, mem_entry->size);

    rtw_list_delete(plist);
    _rtw_mfree((u8 *) mem_entry, sizeof(struct mem_entry));
  }

  restore_flags();
#endif
}

void add_mem_usage(_list *pmem_table, void *ptr, int size, int *used_num, int flag)
{
  int free_heap_size = rtw_getFreeHeapSize();
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  struct mem_entry *mem_entry;
#endif
  if(ptr == NULL)
  {
    DBG_ERR("Catch a mem alloc fail with size of %d, current heap free size = %d", size, free_heap_size);
    return;
  }
  else
  {
    if(flag == MEM_MONITOR_FLAG_WPAS)
    DBG_INFO("Alloc memory at %p with size of %d", ptr, size);
    else
    DBG_INFO("Alloc memory at %p with size of %d", ptr, size);
  }
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  mem_entry = (struct mem_entry *) _rtw_malloc(sizeof(struct mem_entry));

  if(mem_entry == NULL)
  {
    DBG_ERR("Fail to alloc mem_entry");
    return;
  }

  memset(mem_entry, 0, sizeof(struct mem_entry));
  mem_entry->ptr = ptr;
  mem_entry->size = size;

  save_and_cli();
  rtw_list_insert_head(&mem_entry->list, pmem_table);
  restore_flags();

  *used_num ++;
#endif
  if(min_free_heap_size > free_heap_size)
  min_free_heap_size = free_heap_size;
}

void del_mem_usage(_list *pmem_table, void *ptr, int *used_num, int flag)
{
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  _list *plist;
  struct mem_entry *mem_entry = NULL;

  if(ptr == NULL)
  return;

  if(flag == MEM_MONITOR_FLAG_WPAS)
  DBG_INFO("Free memory at %p", ptr);
  else
  DBG_INFO("Free memory at %p", ptr);

  save_and_cli();

  plist = get_next(pmem_table);
  while ((rtw_end_of_queue_search(pmem_table, plist)) == _FALSE)
  {
    mem_entry = LIST_CONTAINOR(plist, struct mem_entry, list);
    if(mem_entry->ptr == ptr)
    {
      rtw_list_delete(plist);
      break;
    }
    plist = get_next(plist);
  }

  restore_flags();

  if(plist == pmem_table)
  DBG_ERR("Fail to find the mem_entry in mem table");
  else
  {
    *used_num --;
    _rtw_mfree((u8 *) mem_entry, sizeof(struct mem_entry));
  }
#endif
}

#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
int get_mem_usage(_list *pmem_table)
{
  _list *plist;
  struct mem_entry *mem_entry;
  int mem_usage = 0;
  int entry_num = 0;

  save_and_cli();

  if((plist = get_next(pmem_table)) == NULL)
  {
    DBG_ERR("No mem table available\n");
    restore_flags();
    return 0;
  }

  while (rtw_end_of_queue_search(pmem_table, plist) == _FALSE)
  {
    entry_num ++;
    mem_entry = LIST_CONTAINOR(plist, struct mem_entry, list);
    mem_usage += mem_entry->size;

    DBG_INFO("size of mem_entry(%d)=%d\n", entry_num, mem_entry->size);
    plist = get_next(plist);
  }

  restore_flags();

  DBG_INFO("Get %d mem_entry\n", entry_num);

  return mem_usage;
}
#endif

u8* rtw_vmalloc(u32 sz)
{
  u8 *pbuf = _rtw_vmalloc(sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  add_mem_usage(&mem_table, pbuf, sz, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  add_mem_usage(NULL, pbuf, sz, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
  return pbuf;
}

u8* rtw_zvmalloc(u32 sz)
{
  u8 *pbuf = _rtw_zvmalloc(sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  add_mem_usage(&mem_table, pbuf, sz, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  add_mem_usage(NULL, pbuf, sz, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
  return pbuf;
}

void rtw_vmfree(u8 *pbuf, u32 sz)
{
  _rtw_vmfree(pbuf, sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  del_mem_usage(&mem_table, pbuf, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  del_mem_usage(NULL, pbuf, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
}

u8* rtw_malloc(u32 sz)
{
  u8 *pbuf = _rtw_malloc(sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  add_mem_usage(&mem_table, pbuf, sz, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  add_mem_usage(NULL, pbuf, sz, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
  return pbuf;
}

u8* rtw_zmalloc(u32 sz)
{
  u8 *pbuf = _rtw_zmalloc(sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  add_mem_usage(&mem_table, pbuf, sz, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  add_mem_usage(NULL, pbuf, sz, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
  return pbuf;
}

void rtw_mfree(u8 *pbuf, u32 sz)
{
  _rtw_mfree(pbuf, sz);
#if CONFIG_MEM_MONITOR & MEM_MONITOR_LEAK
  del_mem_usage(&mem_table, pbuf, &mem_used_num, MEM_MONITOR_FLAG_WIFI_DRV);
#else
  del_mem_usage(NULL, pbuf, NULL, MEM_MONITOR_FLAG_WIFI_DRV);
#endif
}
#endif

void* rtw_malloc2d( int h, int w, int size )
{
  int j;

  void **a = (void **) rtw_zmalloc( h * sizeof(void *) + h * w * size );
  if ( a == NULL )
  {
    OSDEP_DBG( "%s: alloc memory fail!\n", __FUNCTION__ );
    return NULL;
  }

  for ( j = 0; j < h; j++ )
    a[ j ] = ( (char *) ( a + h ) ) + j * w * size;

  return a;
}

void rtw_mfree2d( void *pbuf, int h, int w, int size )
{
  rtw_mfree( (u8 *) pbuf, h * sizeof(void*) + w * h * size );
}

void rtw_memcpy( void* dst, void* src, u32 sz )
{
  if ( osdep_service.rtw_memcpy )
    osdep_service.rtw_memcpy( dst, src, sz );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_memcpy" );
}

int rtw_memcmp( void *dst, void *src, u32 sz )
{
  if ( osdep_service.rtw_memcmp )
    return osdep_service.rtw_memcmp( dst, src, sz );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_memcmp" );

  return _FALSE;
}

void rtw_memset( void *pbuf, int c, u32 sz )
{
  if ( osdep_service.rtw_memset )
    osdep_service.rtw_memset( pbuf, c, sz );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_memset" );
}

void rtw_init_listhead( _list *list )
{
  INIT_LIST_HEAD( list );
}

/*
 For the following list_xxx operations,
 caller must guarantee the atomic context.
 Otherwise, there will be racing condition.
 */
u32 rtw_is_list_empty( _list *phead )
{
  if ( list_empty( phead ) )
    return _TRUE;

  return _FALSE;
}

void rtw_list_insert_head( _list *plist, _list *phead )
{
  list_add( plist, phead );
}

void rtw_list_insert_tail( _list *plist, _list *phead )
{
  list_add_tail( plist, phead );
}

/*

 Caller must check if the list is empty before calling rtw_list_delete

 */
void rtw_list_delete( _list *plist )
{
  list_del_init( plist );
}

void rtw_init_sema( _sema *sema, int init_val )
{
  if ( osdep_service.rtw_init_sema )
    osdep_service.rtw_init_sema( sema, init_val );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_init_sema" );
}

void rtw_free_sema( _sema *sema )
{
  if ( osdep_service.rtw_free_sema )
    osdep_service.rtw_free_sema( sema );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_free_sema" );
}

void rtw_up_sema( _sema *sema )
{
  if ( osdep_service.rtw_up_sema )
    osdep_service.rtw_up_sema( sema );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_up_sema" );
}

void rtw_up_sema_from_isr( _sema *sema )
{
  if ( osdep_service.rtw_up_sema_from_isr )
    osdep_service.rtw_up_sema_from_isr( sema );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_up_sema_from_isr" );
}

u32 rtw_down_timeout_sema( _sema *sema, u32 timeout )
{
  if ( osdep_service.rtw_down_timeout_sema )
    return osdep_service.rtw_down_timeout_sema( sema, timeout );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_down_timeout_sema" );

  return _FAIL;
}

u32 rtw_down_sema( _sema *sema )
{
  while ( rtw_down_timeout_sema( sema, RTW_MAX_DELAY ) != _TRUE )
//		rom_e_rtw_msg_871X_LEVEL(DOWN_SEMA_1, _drv_always_, "%s(%p) failed, retry\n",  __FUNCTION__, sema);
    //OSDEP_DBG_LEVEL(_drv_always_, "%s(%p) failed, retry\n",  __FUNCTION__, sema);
    OSDEP_DBG( "%s(%p) failed, retry\n", __FUNCTION__, sema );
  return _TRUE;
}

void rtw_mutex_init( _mutex *pmutex )
{
  if ( osdep_service.rtw_mutex_init )
    osdep_service.rtw_mutex_init( pmutex );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mutex_init" );
}

void rtw_mutex_free( _mutex *pmutex )
{
  if ( osdep_service.rtw_mutex_free )
    osdep_service.rtw_mutex_free( pmutex );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mutex_free" );
}

void rtw_mutex_put( _mutex *pmutex )
{
  if ( osdep_service.rtw_mutex_put )
    osdep_service.rtw_mutex_put( pmutex );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mutex_put" );
}

void rtw_mutex_get( _mutex *pmutex )
{
  if ( osdep_service.rtw_mutex_get )
    osdep_service.rtw_mutex_get( pmutex );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mutex_get" );
}

int rtw_mutex_get_timeout( _mutex *pmutex, u32 timeout_ms )
{
  if ( osdep_service.rtw_mutex_get_timeout )
    return osdep_service.rtw_mutex_get_timeout( pmutex, timeout_ms );
  else
  {
    OSDEP_DBG( "Not implement osdep service: rtw_mutex_get_timeout" );
    return -1;
  }
}

void rtw_enter_critical( _lock *plock, _irqL *pirqL )
{
  if ( osdep_service.rtw_enter_critical )
    osdep_service.rtw_enter_critical( plock, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_enter_critical" );
}

void rtw_exit_critical( _lock *plock, _irqL *pirqL )
{
  if ( osdep_service.rtw_exit_critical )
    osdep_service.rtw_exit_critical( plock, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_exit_critical" );
}

void rtw_enter_critical_from_isr( _lock *plock, _irqL *pirqL )
{
  if ( osdep_service.rtw_enter_critical )
    osdep_service.rtw_enter_critical( plock, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_enter_critical_from_isr" );
}

void rtw_exit_critical_from_isr( _lock *plock, _irqL *pirqL )
{
  if ( osdep_service.rtw_exit_critical )
    osdep_service.rtw_exit_critical( plock, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_exit_critical_from_isr" );
}

void rtw_enter_critical_bh( _lock *plock, _irqL *pirqL )
{
  rtw_spin_lock( plock );
}

void rtw_exit_critical_bh( _lock *plock, _irqL *pirqL )
{
  rtw_spin_unlock( plock );
}

int rtw_enter_critical_mutex( _mutex *pmutex, _irqL *pirqL )
{
  if ( osdep_service.rtw_enter_critical_mutex )
    return osdep_service.rtw_enter_critical_mutex( pmutex, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_enter_critical_mutex" );

  return 0;
}

void rtw_exit_critical_mutex( _mutex *pmutex, _irqL *pirqL )
{
  if ( osdep_service.rtw_exit_critical_mutex )
    osdep_service.rtw_exit_critical_mutex( pmutex, pirqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_exit_critical_mutex" );
}

void rtw_init_queue( _queue *pqueue )
{
  rtw_init_listhead( &( pqueue->queue ) );
  rtw_spinlock_init( &( pqueue->lock ) );
}

u32 rtw_queue_empty( _queue *pqueue )
{
  return ( rtw_is_list_empty( &( pqueue->queue ) ) );
}

u32 rtw_end_of_queue_search( _list *head, _list *plist )
{
  if ( head == plist )
    return _TRUE;
  else
    return _FALSE;
}

#if 1
void rtw_spinlock_init( _lock *plock )
{
  if ( osdep_service.rtw_spinlock_init )
    osdep_service.rtw_spinlock_init( plock );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spinlock_init" );
}

void rtw_spinlock_free( _lock *plock )
{
  if ( osdep_service.rtw_spinlock_free )
    osdep_service.rtw_spinlock_free( plock );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spinlock_free" );
}

void rtw_spin_lock( _lock *plock )
{
  if ( osdep_service.rtw_spin_lock )
    osdep_service.rtw_spin_lock( plock );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spin_lock" );
}

void rtw_spin_unlock( _lock *plock )
{
  if ( osdep_service.rtw_spin_unlock )
    osdep_service.rtw_spin_unlock( plock );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spin_unlock" );
}

void rtw_spinlock_irqsave( _lock *plock, _irqL *irqL )
{
  if ( osdep_service.rtw_spinlock_irqsave )
    osdep_service.rtw_spinlock_irqsave( plock, irqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spinlock_irqsave" );
}

void rtw_spinunlock_irqsave( _lock *plock, _irqL *irqL )
{
  if ( osdep_service.rtw_spinunlock_irqsave )
    osdep_service.rtw_spinunlock_irqsave( plock, irqL );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_spinunlock_irqsave" );
}
#endif

int rtw_init_xqueue( _xqueue* queue, const char* name, u32 message_size, u32 number_of_messages )
{
  if ( osdep_service.rtw_init_xqueue )
    return (int) osdep_service.rtw_init_xqueue( queue, name, message_size, number_of_messages );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_init_xqueue" );

  return FAIL;
}

int rtw_push_to_xqueue( _xqueue* queue, void* message, u32 timeout_ms )
{
  if ( osdep_service.rtw_push_to_xqueue )
    return (int) osdep_service.rtw_push_to_xqueue( queue, message, timeout_ms );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_push_to_xqueue" );

  return FAIL;
}

int rtw_pop_from_xqueue( _xqueue* queue, void* message, u32 timeout_ms )
{
  if ( osdep_service.rtw_pop_from_xqueue )
    return (int) osdep_service.rtw_pop_from_xqueue( queue, message, timeout_ms );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_pop_from_xqueue" );

  return FAIL;
}

int rtw_deinit_xqueue( _xqueue* queue )
{
  if ( osdep_service.rtw_deinit_xqueue )
    return (int) osdep_service.rtw_deinit_xqueue( queue );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_deinit_xqueue" );

  return FAIL;
}

#if 0
void rtw_init_queue(_queue *pqueue)
{
  rtw_init_listhead(&(pqueue->queue));
  rtw_mutex_init(&(pqueue->lock));
}

void rtw_deinit_queue(_queue *pqueue)
{
  rtw_mutex_free(&(pqueue->lock));
}

u32 rtw_is_queue_empty(_queue *pqueue)
{
  return (rtw_is_list_empty(&(pqueue->queue)));
}

u32 rtw_end_of_queue_search(_list *head, _list *plist)
{
  if (head == plist)
  return _TRUE;

  return _FALSE;
}

_list *rtw_get_queue_head(_queue *queue)
{
  return (&(queue->queue));
}
#endif

u32 rtw_get_current_time( void )
{
  if ( osdep_service.rtw_get_current_time )
    return osdep_service.rtw_get_current_time( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_get_current_time" );

  return 0;
}

u32 rtw_systime_to_ms( u32 systime )
{
  if ( osdep_service.rtw_systime_to_ms )
    return osdep_service.rtw_systime_to_ms( systime );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_systime_to_ms" );

  return 0;
}

u32 rtw_systime_to_sec( u32 systime )
{
  if ( osdep_service.rtw_systime_to_sec )
    return osdep_service.rtw_systime_to_sec( systime );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_systime_to_sec" );

  return 0;
}

u32 rtw_ms_to_systime( u32 ms )
{
  if ( osdep_service.rtw_ms_to_systime )
    return osdep_service.rtw_ms_to_systime( ms );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_ms_to_systime" );

  return 0;
}

u32 rtw_sec_to_systime( u32 sec )
{
  if ( osdep_service.rtw_sec_to_systime )
    return osdep_service.rtw_sec_to_systime( sec );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_sec_to_systime" );

  return 0;
}

// the input parameter start use the same unit as returned by rtw_get_current_time
s32 rtw_get_passing_time_ms( u32 start )
{
  return rtw_systime_to_ms( rtw_get_current_time( ) - start );
}

s32 rtw_get_time_interval_ms( u32 start, u32 end )
{
  return rtw_systime_to_ms( end - start );
}

void rtw_msleep_os( int ms )
{
  if ( osdep_service.rtw_msleep_os )
    osdep_service.rtw_msleep_os( ms );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_msleep_os" );
}

void rtw_usleep_os( int us )
{
  if ( osdep_service.rtw_usleep_os )
    osdep_service.rtw_usleep_os( us );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_usleep_os" );
}

void rtw_mdelay_os( int ms )
{
  if ( osdep_service.rtw_mdelay_os )
    osdep_service.rtw_mdelay_os( ms );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_mdelay_os" );
}

void rtw_udelay_os( int us )
{
  if ( osdep_service.rtw_udelay_os )
    osdep_service.rtw_udelay_os( us );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_udelay_os" );
}

void rtw_yield_os( void )
{
  if ( osdep_service.rtw_yield_os )
    osdep_service.rtw_yield_os( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_yield_os" );
}

void ATOMIC_SET( ATOMIC_T *v, int i )
{
  if ( osdep_service.ATOMIC_SET )
    osdep_service.ATOMIC_SET( v, i );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_SET" );
}

int ATOMIC_READ( ATOMIC_T *v )
{
  if ( osdep_service.ATOMIC_READ )
    return osdep_service.ATOMIC_READ( v );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_READ" );

  return 0;
}

void ATOMIC_ADD( ATOMIC_T *v, int i )
{
  if ( osdep_service.ATOMIC_ADD )
    osdep_service.ATOMIC_ADD( v, i );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_ADD" );
}

void ATOMIC_SUB( ATOMIC_T *v, int i )
{
  if ( osdep_service.ATOMIC_SUB )
    osdep_service.ATOMIC_SUB( v, i );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_SUB" );
}

void ATOMIC_INC( ATOMIC_T *v )
{
  if ( osdep_service.ATOMIC_INC )
    osdep_service.ATOMIC_INC( v );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_INC" );
}

void ATOMIC_DEC( ATOMIC_T *v )
{
  if ( osdep_service.ATOMIC_DEC )
    osdep_service.ATOMIC_DEC( v );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_DEC" );
}

int ATOMIC_ADD_RETURN( ATOMIC_T *v, int i )
{
  if ( osdep_service.ATOMIC_ADD_RETURN )
    return osdep_service.ATOMIC_ADD_RETURN( v, i );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_ADD_RETURN" );

  return 0;
}

int ATOMIC_SUB_RETURN( ATOMIC_T *v, int i )
{
  if ( osdep_service.ATOMIC_SUB_RETURN )
    return osdep_service.ATOMIC_SUB_RETURN( v, i );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_SUB_RETURN" );

  return 0;
}

int ATOMIC_INC_RETURN( ATOMIC_T *v )
{
  if ( osdep_service.ATOMIC_INC_RETURN )
    return osdep_service.ATOMIC_INC_RETURN( v );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_INC_RETURN" );

  return 0;
}

int ATOMIC_DEC_RETURN( ATOMIC_T *v )
{
  if ( osdep_service.ATOMIC_DEC_RETURN )
    return osdep_service.ATOMIC_DEC_RETURN( v );
  else
    OSDEP_DBG( "Not implement osdep service: ATOMIC_DEC_RETURN" );

  return 0;
}

int ATOMIC_DEC_AND_TEST( ATOMIC_T *v )
{
  return ATOMIC_DEC_RETURN( v ) == 0;
}

u64 rtw_modular64( u64 x, u64 y )
{
  if ( osdep_service.rtw_modular64 )
    return osdep_service.rtw_modular64( x, y );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_modular64" );

  return 0;
}

int rtw_get_random_bytes( void* dst, u32 size )
{
  if ( osdep_service.rtw_get_random_bytes )
    return osdep_service.rtw_get_random_bytes( dst, size );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_get_random_bytes" );

  return 0;
}

u32 rtw_getFreeHeapSize( void )
{
  if ( osdep_service.rtw_getFreeHeapSize )
    return osdep_service.rtw_getFreeHeapSize( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_getFreeHeapSize" );

  return 0;
}

int rtw_netif_queue_stopped( void *pnetdev )
{
  return 0;
}

void rtw_netif_wake_queue( void *pnetdev )
{
}

void rtw_netif_start_queue( void *pnetdev )
{
}

void rtw_netif_stop_queue( void *pnetdev )
{
}

void flush_signals_thread( void )
{
}

void rtw_acquire_wakelock( void )
{
  if ( osdep_service.rtw_acquire_wakelock )
    osdep_service.rtw_acquire_wakelock( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_acquire_wakelock" );
}

void rtw_release_wakelock( void )
{
  if ( osdep_service.rtw_release_wakelock )
    osdep_service.rtw_release_wakelock( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_release_wakelock" );
}

int rtw_create_task( struct task_struct *task, const char *name, u32 stack_size, u32 priority,
  thread_func_t func, void *thctx )
{
  if ( osdep_service.rtw_create_task )
    return osdep_service.rtw_create_task( task, name, stack_size, priority, func, thctx );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_create_task" );
  return 1;
}
void rtw_delete_task( struct task_struct *task )
{
  if ( osdep_service.rtw_delete_task )
    osdep_service.rtw_delete_task( task );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_delete_task" );

  return;
}
void rtw_wakeup_task( struct task_struct *task )
{
  if ( osdep_service.rtw_wakeup_task )
    osdep_service.rtw_wakeup_task( task );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_wakeup_task" );

  return;
}

static void worker_thread_main( void *arg )
{
  rtw_worker_thread_t* worker_thread = (rtw_worker_thread_t*) arg;

  while ( 1 )
  {
    rtw_event_message_t message;

    if ( rtw_pop_from_xqueue( &worker_thread->event_queue, &message, RTW_WAIT_FOREVER ) == SUCCESS )
    {
      message.function( message.buf, message.buf_len, message.flags, message.user_data );
      if ( message.buf )
      {
        //printf("\n!!!!!Free %p(%d)\n", message.buf, message.buf_len);
        _rtw_mfree( message.buf, message.buf_len );
      }
    }
  }
}

int rtw_create_worker_thread( rtw_worker_thread_t* worker_thread, u8 priority, u32 stack_size,
  u32 event_queue_size )
{
  if ( NULL == worker_thread )
    return FAIL;

  memset( worker_thread, 0, sizeof( *worker_thread ) );

  if ( rtw_init_xqueue( &worker_thread->event_queue, "worker queue", sizeof(rtw_event_message_t),
    event_queue_size ) != SUCCESS )
  {
    return FAIL;
  }

  if ( !rtw_create_task( &worker_thread->thread, "worker thread", stack_size, priority,
    worker_thread_main, (void*) worker_thread ) )
  {
    rtw_deinit_xqueue( &worker_thread->event_queue );
    return FAIL;
  }

  return SUCCESS;
}

int rtw_delete_worker_thread( rtw_worker_thread_t* worker_thread )
{
  if ( NULL == worker_thread )
    return FAIL;

  rtw_deinit_xqueue( &worker_thread->event_queue );

  rtw_delete_task( &worker_thread->thread );

  return SUCCESS;
}

_timerHandle rtw_timerCreate( const signed char *pcTimerName, osdepTickType xTimerPeriodInTicks,
  u32 uxAutoReload, void * pvTimerID, TIMER_FUN pxCallbackFunction )
{
  if ( osdep_service.rtw_timerCreate )
    return osdep_service.rtw_timerCreate( pcTimerName, xTimerPeriodInTicks, uxAutoReload, pvTimerID,
      pxCallbackFunction );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_timerCreate" );

  return 0;
}

u32 rtw_timerDelete( _timerHandle xTimer, osdepTickType xBlockTime )
{
  if ( osdep_service.rtw_timerDelete )
    return osdep_service.rtw_timerDelete( xTimer, xBlockTime );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_timerDelete" );

  return 0;
}

u32 rtw_timerIsTimerActive( _timerHandle xTimer )
{
  if ( osdep_service.rtw_timerIsTimerActive )
    return osdep_service.rtw_timerIsTimerActive( xTimer );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_timerIsTimerActive" );

  return 0;
}

u32 rtw_timerStop( _timerHandle xTimer, osdepTickType xBlockTime )
{
  if ( osdep_service.rtw_timerStop )
    return osdep_service.rtw_timerStop( xTimer, xBlockTime );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_timerStop" );

  return 0;
}

u32 rtw_timerChangePeriod( _timerHandle xTimer, osdepTickType xNewPeriod, osdepTickType xBlockTime )
{
  if ( osdep_service.rtw_timerChangePeriod )
    return osdep_service.rtw_timerChangePeriod( xTimer, xNewPeriod, xBlockTime );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_timerChangePeriod" );

  return 0;
}

#if 0 //TODO
void rtw_init_delayed_work(struct delayed_work *dwork, work_func_t func, const char *name)
{
  if(osdep_service.rtw_init_delayed_work)
  osdep_service.rtw_init_delayed_work(dwork, func, name);
  else
  OSDEP_DBG("Not implement osdep service: rtw_init_delayed_work");

  return;
}

void rtw_deinit_delayed_work(struct delayed_work *dwork)
{
  if(osdep_service.rtw_deinit_delayed_work)
  osdep_service.rtw_deinit_delayed_work(dwork);
  else
  OSDEP_DBG("Not implement osdep service: rtw_deinit_delayed_work");

  return;
}

int rtw_queue_delayed_work(struct workqueue_struct *wq,
    struct delayed_work *dwork, u32 delay, void* context)
{
  if(osdep_service.rtw_queue_delayed_work)
  osdep_service.rtw_queue_delayed_work(wq, dwork, delay, context);
  else
  OSDEP_DBG("Not implement osdep service: rtw_queue_delayed_work");

  return;
}

BOOLEAN rtw_cancel_delayed_work(struct delayed_work *dwork)
{
  if(osdep_service.rtw_cancel_delayed_work)
  osdep_service.rtw_cancel_delayed_work(dwork);
  else
  OSDEP_DBG("Not implement osdep service: rtw_cancel_delayed_work");

  return;
}
#endif
void rtw_thread_enter( char *name )
{
  if ( osdep_service.rtw_thread_enter )
    osdep_service.rtw_thread_enter( name );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_thread_enter" );
}

void rtw_thread_exit( )
{
  if ( osdep_service.rtw_thread_exit )
    osdep_service.rtw_thread_exit( );
  else
    OSDEP_DBG( "Not implement osdep service: rtw_thread_exit" );
}

u8 rtw_get_scheduler_state( )
{
  // OS_SCHEDULER_NOT_STARTED	0
  // OS_SCHEDULER_RUNNING		1
  // OS_SCHEDULER_SUSPENDED	2
  // OS_SCHEDULER_UNREACHABLE	3
  if ( osdep_service.rtw_get_scheduler_state )
    return osdep_service.rtw_get_scheduler_state( );
  else
  {
    OSDEP_DBG( "Not implement osdep service: rtw_get_scheduler_state" );
    return 3;
  }
}

#define _OSDEP_API_C_

extern _LONG_CALL_ char *_strcpy(char *dest, const char *src);
extern _LONG_CALL_ VOID *_memset(void *dst0, int Val,SIZE_T length);

u8*
RtlMalloc(
    IN u32 sz
)
{
  u8 *pbuf=NULL;
#ifndef PLATFORM_FREERTOS
  u32 v32=0;
#endif

#ifdef PLATFORM_FREERTOS
  SaveAndCli( );
#else
  SaveAndCli(v32);
#endif

  pbuf = RtlKmalloc(sz, GFP_ATOMIC);

#ifdef PLATFORM_FREERTOS
  RestoreFlags( );
#else
  RestoreFlags(v32);
#endif

  return pbuf;

}

u8*
RtlZmalloc(
    IN u32 sz
)
{
#ifdef PLATFORM_FREERTOS
  u8 *pbuf;

  pbuf= RtlMalloc(sz);

  if (pbuf != NULL)
  {
    _memset(pbuf, 0, sz);
  }

  return pbuf;
#else
  u8 *pbuf;

  pbuf= RtlMalloc(sz);

  if (pbuf != NULL)
  {
    _memset(pbuf, 0, sz);
  }

  return pbuf;
#endif
}

VOID
RtlMfree(
    IN u8 *pbuf,
    IN u32 sz
)
{
  RtlKfree(pbuf);
}

VOID*
RtlMalloc2d(
    IN u32 h,
    IN u32 w,
    IN u32 size
)
{
  u32 j;

  VOID **a = (VOID **) RtlZmalloc( h*sizeof(VOID *) + h*w*size );
  if(a == NULL)
  {
    DBG_ERROR_LOG("%s: alloc memory fail!\n", __FUNCTION__);
    return NULL;
  }

  for( j=0; j<h; j++ )
  a[j] = ((char *)(a+h)) + j*w*size;

  return a;
}

VOID
RtlMfree2d(
    IN VOID *pbuf,
    IN u32 h,
    IN u32 w,
    IN u32 size
)
{
  RtlMfree((u8 *)pbuf, h*sizeof(VOID*) + w*h*size);
}

VOID
RtlInitSema(
    IN _Sema *sema,
    IN u32 init_val
)
{
#ifdef PLATFORM_FREERTOS
  *sema = xSemaphoreCreateCounting(MAX_SEMA_COUNT, init_val);
#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_ECOS)
  SemaInit(sema, init_val);
#endif
}

VOID
RtlFreeSema(
    IN _Sema *sema
)
{
  vSemaphoreDelete(*sema);
}

VOID
RtlUpSema(
    IN _Sema *sema
)
{
#ifdef PLATFORM_FREERTOS
  xSemaphoreGive(*sema);
#endif

#ifdef PLATFORM_ECOS
  sema_post(sema);
#endif

}

VOID
RtlUpSemaFromISR(
    IN _Sema *sema
)
{
#ifdef PLATFORM_FREERTOS
  signed portBASE_TYPE xHigherPriorityTaskWoken=pdFALSE;

  xSemaphoreGiveFromISR(*sema, &xHigherPriorityTaskWoken);
//    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  if (pdFALSE != xHigherPriorityTaskWoken)
  {
    taskYIELD();
  }
#endif

#ifdef PLATFORM_ECOS
  sema_post(sema);
#endif

}

u32
RtlDownSema(
    IN _Sema *sema
)
{
#ifdef PLATFORM_FREERTOS
  xSemaphoreTake(*sema, portMAX_DELAY);
  return _SUCCESS;
#endif

#ifdef PLATFORM_ECOS
  SemaWait(sema);
  return _SUCCESS;
#endif

}

u32
RtlDownSemaWithTimeout(
    IN _Sema *sema,
    IN u32 ms
)
{

#ifdef PLATFORM_FREERTOS
  u32 timeout = ms/portTICK_RATE_MS;

  if (xSemaphoreTake(*sema, timeout) == pdTRUE)
  {
    return _SUCCESS;
  }
  else
  {
    return _FAIL;
  }
#endif

#ifdef PLATFORM_ECOS
  // TODO:
  SemaWait(sema);
  return _SUCCESS;
#endif

}

VOID
RtlMutexInit(
    IN _Mutex *pmutex
)
{
#ifdef PLATFORM_FREERTOS
  *pmutex = xSemaphoreCreateMutex();
#endif

#ifdef PLATFORM_ECOS
  SemaInit(pmutex, 1);
#endif
}

VOID
RtlMutexFree(
    IN _Mutex *pmutex
)
{
  vSemaphoreDelete(*pmutex);
}

VOID
RtlSpinlockInit(
    IN _Lock *plock
)
{
  SpinLockInit(plock);
}

VOID
RtlSpinlockFree(
    IN _Lock *plock
)
{
}

VOID
RtlSpinlock(
    IN _Lock *plock
)
{
  SpinLock(plock);
}

VOID
RtlSpinunlock(
    IN _Lock *plock
)
{
  SpinUnlock(plock);
}

VOID
RtlSpinlockEx(
    IN _Lock *plock
)
{

}

VOID
RtlSpinunlockEx(
    IN _Lock *plock
)
{

}

#if 0
VOID
RtlInitQueue(
    IN _QUEUE *pqueue
)
{

  RtlInitListhead(&(pqueue->Queue));

  RtlSpinlockInit(&(pqueue->Lock));

}

u32
RtlQueueEmpty(
    IN _QUEUE *pqueue
)
{
  return (RtlIsListEmpty(&(pqueue->Queue)));
}

u32
RtlendOfQueueSearch(
    IN _LIST *head,
    IN _LIST *plist)
{
  if (head == plist)
  return _TRUE;
  else
  return _FALSE;
}
#endif

u32 RtlGetCurrentTime( VOID )
{
  return JIFFIES;
}

VOID
RtlSleepSchedulable(
    IN u32 ms
)
{

#ifdef PLATFORM_LINUX

  u32 delta;

  delta = (ms * HZ)/1000;	//(ms)
  if (delta == 0)
  {
    delta = 1;	// 1 ms
  }
  set_current_state(TASK_INTERRUPTIBLE);
  if (schedule_timeout(delta) != 0)
  {
    return;
  }
  return;

#endif
#ifdef PLATFORM_FREEBSD
  DELAY(ms*1000);
  return;
#endif

#ifdef PLATFORM_WINDOWS

  NdisMSleep(ms*1000); //(us)*1000=(ms)

#endif

}

VOID
RtlMsleepOS(
    IN u32 ms
)
{
#ifdef PLATFORM_FREERTOS
  u32 Dealycount = ms/portTICK_RATE_MS;
  if (Dealycount > 0)
  {
    vTaskDelay(Dealycount);
  }
  else
  {
    vTaskDelay(1);
  }

#endif
}

VOID
RtlUsleepOS(
    IN u32 us
)
{
#ifdef PLATFORM_FREERTOS
  u32 Dealycount = us/portTICK_RATE_MS*1000;
  if (Dealycount > 0)
  {
    vTaskDelay(Dealycount);
  }
  else
  {
    vTaskDelay(1);
  }
#endif
}

VOID
RtlMdelayOS(
    IN u32 ms
)
{
  Mdelay((unsigned long)ms);
}

VOID
RtlUdelayOS(
    IN u32 us
)
{
  Udelay((unsigned long)us);
}

VOID RtlYieldOS( VOID )
{
}

#if defined(__ICCARM__)
u64
RtlModular64(
    IN u64 n,
    IN u64 base
)
{
  unsigned int __base = (base);
  unsigned int __rem;
  //(void)(((typeof((n)) *)0) == ((__uint64_t *)0));
  if (((n) >> 32) == 0)
  {
    __rem = (unsigned int)(n) % __base;
    (n) = (unsigned int)(n) / __base;
  }
  else
  __rem = __Div64_32(&(n), __base);
  return __rem;

}
#else
u64
RtlModular64(
    IN u64 x,
    IN u64 y
)
{
  return DO_DIV(x, y);
}
#endif

/******************************************************************************
 * Function: RtlTimerCallbckEntry
 * Desc: This function is a timer callback wrapper. All OS timer callback
 *      will call this function and then call the real callback function inside
 *      this function.
 *
 * Para:
 * 	 pxTimer: The FreeRTOS timer handle which is expired and call this callback.
 *
 * Return: None
 *
 ******************************************************************************/
#ifdef PLATFORM_FREERTOS
void
RtlTimerCallbckEntry (
    IN xTimerHandle pxTimer
)
{
  PRTL_TIMER pTimer;

  if (NULL == pxTimer)
  {
    MSG_TIMER_ERR("RtlTimerCallbckEntry: NULL Timer Handle Err!\n");
    return;
  }

  pTimer = (PRTL_TIMER) pvTimerGetTimerID( pxTimer );
  pTimer->CallBackFunc(pTimer->Context);
}
#endif  // end of "#ifdef PLATFORM_FREERTOS"

/******************************************************************************
 * Function: RtlTimerCreate
 * Desc: To create a software timer.
 *
 * Para:
 * 	 pTimerName: A string for the timer name.
 * 	 TimerPeriodMS: The timer period, the unit is milli-second.
 *   CallbckFunc: The callback function of this timer.
 *   pContext: A pointer will be used as the parameter to call the timer
 *              callback function.
 *   isPeriodical: Is this timer periodical ? (Auto reload after expired)
 * Return: The created timer handle, a pointer. It can be used to delete the
 *          timer. If timer createion failed, return NULL.
 *
 ******************************************************************************/
PRTL_TIMER
RtlTimerCreate(
    IN char *pTimerName,
    IN u32 TimerPeriodMS,
    IN RTL_TIMER_CALL_BACK CallbckFunc,
    IN void *pContext,
    IN u8 isPeriodical
)
{
  PRTL_TIMER pTimer;
  u32 timer_ticks;
  int i;

  pTimer = (PRTL_TIMER)RtlZmalloc(sizeof(RTL_TIMER));
  if (NULL == pTimer)
  {
    MSG_TIMER_ERR("RtlTimerCreate: Alloc Mem Err!\n");
    return NULL;
  }

  if (portTICK_RATE_MS >= TimerPeriodMS)
  {
    timer_ticks = 1;    // at least 1 system tick
  }
  else
  {
    timer_ticks = TimerPeriodMS/portTICK_RATE_MS;
  }

#ifdef PLATFORM_FREERTOS
  pTimer->TimerHandle = xTimerCreate ((const char*)(pTimer->TimerName), timer_ticks,
      (portBASE_TYPE)isPeriodical, (void *) pTimer, RtlTimerCallbckEntry);
#endif
#ifdef PLATFORM_ECOS
// TODO: create a timer
#endif

#ifdef PLATFORM_FREERTOS    // if any RTOS is used
  if (pTimer->TimerHandle)
  {
    pTimer->msPeriod = TimerPeriodMS;
    pTimer->CallBackFunc = CallbckFunc;
    pTimer->Context = pContext;
    pTimer->isPeriodical = isPeriodical;
    // copy the timer name
    if (NULL != pTimerName)
    {
      for(i = 0; i < sizeof(pTimer->TimerName); i++)
      {
        pTimer->TimerName[i] = pTimerName[i];
        if(pTimerName[i] == '\0')
        {
          break;
        }
      }
    }
    else
    {
      _strcpy((char*)(pTimer->TimerName), "None");
    }
    MSG_TIMER_INFO("RtlTimerCreate: SW Timer Created: Name=%s Period=%d isPeriodical=%d\n",
        pTimer->TimerName, pTimer->msPeriod, pTimer->isPeriodical);
  }
  else
#endif
  {
    RtlMfree((u8 *)pTimer, sizeof(RTL_TIMER));
    pTimer = NULL;
    MSG_TIMER_ERR("RtlTimerCreate: OS Create Timer Failed!\n");
  }

  return (pTimer);
}

/******************************************************************************
 * Function: RtlTimerDelete
 * Desc: To delete a created software timer.
 *
 * Para:
 * 	 pTimerHdl: The timer to be deleted
 *
 * Return: None
 *
 ******************************************************************************/
VOID
RtlTimerDelete(
    IN PRTL_TIMER pTimerHdl
)
{
#ifdef PLATFORM_FREERTOS
  portBASE_TYPE ret;
#endif

  if (NULL == pTimerHdl)
  {
    MSG_TIMER_ERR("RtlTimerDelete: NULL Timer Handle!\n");
    return;
  }

  MSG_TIMER_INFO("RtlTimerDelete: Name=%s\n", pTimerHdl->TimerName);

#ifdef PLATFORM_FREERTOS
  /* try to delete the soft timer and wait max RTL_TIMER_API_MAX_BLOCK_TICKS
   to send the delete command to the timer command queue */
  ret = xTimerDelete(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS);
  if (pdPASS != ret)
  {
    MSG_TIMER_ERR("RtlTimerDelete: Delete OS Timer Failed!\n");
  }
#endif

#ifdef PLATFORM_ECOS
  // TODO: call OS delete timer
#endif
  RtlMfree((u8 *)pTimerHdl, sizeof(RTL_TIMER));

}

/******************************************************************************
 * Function: RtlTimerStart
 * Desc: To start a created timer..
 *
 * Para:
 * 	 pTimerHdl: The timer to be started.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
u8
RtlTimerStart(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
)
{
#ifdef PLATFORM_FREERTOS
  u8 ret=_FAIL;
  portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

  if (isFromISR)
  {
    if (pdPASS == xTimerStartFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
    {
      // start OS timer successful
      if (pdFALSE != HigherPriorityTaskWoken)
      {
        taskYIELD();
      }
      ret = _SUCCESS;
    }
    else
    {
      MSG_TIMER_ERR("RtlTimerStart: Start Timer(%s) from ISR failed\n", pTimerHdl->TimerName);
    }
  }
  else
  {
    if (pdPASS == xTimerStart(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS))
    {
      ret = _SUCCESS;
    }
    else
    {
      MSG_TIMER_ERR("RtlTimerStart: Start Timer(%s) failed\n", pTimerHdl->TimerName);
    }
  }

  MSG_TIMER_INFO("RtlTimerStart: SW Timer %s Started\n", pTimerHdl->TimerName);

  return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerStop
 * Desc: To stop a running timer..
 *
 * Para:
 * 	 pTimerHdl: The timer to be stoped.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
u8
RtlTimerStop(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
)
{
#ifdef PLATFORM_FREERTOS
  u8 ret=_FAIL;
  portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

  if (isFromISR)
  {
    if (pdPASS == xTimerStopFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
    {
      // start OS timer successful
      if (pdFALSE != HigherPriorityTaskWoken)
      {
        taskYIELD();
      }
      ret = _SUCCESS;
    }
  }
  else
  {
    if (pdPASS == xTimerStop(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS))
    {
      ret = _SUCCESS;
    }
  }

  if (_FAIL == ret)
  {
    MSG_TIMER_ERR("RtlTimerStop: Stop Timer(%s) Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
  }

  MSG_TIMER_INFO("RtlTimerStop: SW Timer %s Stoped\n", pTimerHdl->TimerName);

  return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerReset
 * Desc: To reset a timer. A reset will get a re-start and reset
 *          the timer ticks counting. A running timer expired time is relative
 *          to the time when Reset function be called. Please ensure the timer
 *          is in active state (Started). A stopped timer also will be started
 *          when this function is called.
 *
 * Para:
 * 	 pTimerHdl: The timer to be reset.
 *	isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
u8
RtlTimerReset(
    IN PRTL_TIMER pTimerHdl,
    IN u8 isFromISR
)
{
#ifdef PLATFORM_FREERTOS
  u8 ret=_FAIL;
  portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

  if (isFromISR)
  {
    if (pdPASS == xTimerResetFromISR(pTimerHdl->TimerHandle,&HigherPriorityTaskWoken))
    {
      // start OS timer successful
      if (pdFALSE != HigherPriorityTaskWoken)
      {
        taskYIELD();
      }
      ret = _SUCCESS;
    }
  }
  else
  {
    if (pdPASS == xTimerReset(pTimerHdl->TimerHandle, RTL_TIMER_API_MAX_BLOCK_TICKS))
    {
      ret = _SUCCESS;
    }
  }

  if (_FAIL == ret)
  {
    MSG_TIMER_ERR("RtlTimerReset: Reset Timer(%s) Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
  }

  MSG_TIMER_INFO("RtlTimerReset: SW Timer %s Reset\n", pTimerHdl->TimerName);

  return ret;
#endif
}

/******************************************************************************
 * Function: RtlTimerChangePeriod
 * Desc: To change the period of a timer that was created previously.
 *
 * Para:
 * 	 pTimerHdl: The timer handle to be changed the priod.
 *   NewPeriodMS: The new timer period, in milli-second.
 *	 isFromISR: The flag to indicate that is this function is called from an ISR.
 *
 * Return: _SUCCESS or _FAIL
 *
 ******************************************************************************/
u8
RtlTimerChangePeriod(
    IN PRTL_TIMER pTimerHdl,
    IN u32 NewPeriodMS,
    IN u8 isFromISR
)
{
#ifdef PLATFORM_FREERTOS
  u32 timer_ticks;
  u8 ret=_FAIL;
  portBASE_TYPE HigherPriorityTaskWoken=pdFALSE;

  if (portTICK_RATE_MS >= NewPeriodMS)
  {
    timer_ticks = 1;    // at least 1 system tick
  }
  else
  {
    timer_ticks = NewPeriodMS/portTICK_RATE_MS;
  }

  if (isFromISR)
  {
    if (pdPASS == xTimerChangePeriodFromISR(pTimerHdl->TimerHandle, timer_ticks, &HigherPriorityTaskWoken))
    {
      // start OS timer successful
      if (pdFALSE != HigherPriorityTaskWoken)
      {
        taskYIELD();
      }
      ret = _SUCCESS;
    }
  }
  else
  {
    if (pdPASS == xTimerChangePeriod(pTimerHdl->TimerHandle, timer_ticks, RTL_TIMER_API_MAX_BLOCK_TICKS))
    {
      ret = _SUCCESS;
    }
  }

  if (_FAIL == ret)
  {
    MSG_TIMER_ERR("RtlTimerChangePeriod: Change Timer(%s) Period Failed, IsFromISR=%d\n", pTimerHdl->TimerName, isFromISR);
  }
  else
  {
    pTimerHdl->msPeriod = NewPeriodMS;
    MSG_TIMER_INFO("RtlTimerChangePeriod: SW Timer %s change period to %d\n", pTimerHdl->TimerName, pTimerHdl->msPeriod);
  }

  return ret;
#endif
}

#define _MAILBOX_C_

/******************************************************************************
 * Function Prototype Declaration
 ******************************************************************************/
static PRTL_MAILBOX RtlMBoxIdToHdl(
    IN u8 MBoxId
);

PRTL_MAILBOX RtlMailboxCreate(
    IN u8 MboxID,
    IN u32 MboxSize,
    IN _Sema *pWakeSema
);

VOID RtlMailboxDel(
    IN PRTL_MAILBOX MboxHdl
);

u8 RtlMailboxSendToBack(
    IN u8 MboxID,
    IN MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
);

u8 RtlMailboxSendToFront(
    IN u8 MboxID,
    IN MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
);

u8 RtlMailboxReceive(
    IN u8 MboxID,
    OUT MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
);

u8 RtlMailboxPeek(
    IN u8 MboxID,
    OUT MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
);

u32 RtlMailboxMsgWaiting(
    IN u8 MboxID,
    IN u8 IsFromISR
);

/******************************************************************************
 * Global Variable Declaration
 ******************************************************************************/
static RTL_MBOX_ROOT MBox_Entry;

/******************************************************************************
 * External Function & Variable Declaration
 ******************************************************************************/

/******************************************************************************
 * Function: RtlMBoxIdToHdl
 * Desc: Map a mailbox ID to the mailbox pointer.
 * Para:
 *	MBoxId: The Mailbox ID
 * Return: The pointer of the mailbox. If didn't found match mailbox,
 *			return NULL.
 *
 ******************************************************************************/
static PRTL_MAILBOX RtlMBoxIdToHdl(
    IN u8 MBoxId
)
{
  RTL_MAILBOX *pMbox=NULL;
  RTL_MAILBOX *pTmpMbox;
  _LIST *pHead;
  _LIST *pList;

  // if the Mailbox root entry initialed ? if not, initial it
  if (!MBox_Entry.isInitialed)
  {
    RtlMutexInit(&MBox_Entry.Mutex);// Init the Mutex for the mailbox add/delete procedure protection
    RtlInitListhead(&MBox_Entry.mbox_list);// Init the link list head to chain all created mailbox
    MBox_Entry.isInitialed = 1;
    MSG_MBOX_INFO("MBox Entry Initial...\n");
  }

  pHead = &MBox_Entry.mbox_list;
  RtlDownMutex(&MBox_Entry.Mutex);
  pList = RtlListGetNext(&MBox_Entry.mbox_list);
  while (pList != pHead)
  {
    pTmpMbox = CONTAINER_OF(pList, RTL_MAILBOX, mbox_list);
    if (MBoxId == pTmpMbox->mbox_id)
    {
      pMbox = pTmpMbox;
      break;
    }
    pList = RtlListGetNext(pList);
  }
  RtlUpMutex(&MBox_Entry.Mutex);

  return pMbox;
}

/******************************************************************************
 * Function: RtlMailboxCreate
 * Desc: To create a mailbox with a given mailbox ID and size
 * Para:
 * 	MboxID: A number to identify this created mailbox. A message block can
 *          be send to a mailbox by a given MboxID. The MboxID must be unique
 *          in the whole system. If this MboxID is conflict with a created
 *          mailbox, the mailbox creation will fail and return NULL.
 *  MboxSize: The size of this mailbox to be created. It means maximum number
 *          of message blocks can be stored in this mailbox.
 *  pWakeSema: The semaphore to wake up the receiving task to receive the new
 *          message. If the receiving task doesn't need a semaphore to wakeup
 *          it, then just let this pointer is NULL.
 * Return: The created mailbox pointer. If it failed, return NULL.
 ******************************************************************************/
PRTL_MAILBOX RtlMailboxCreate(
    IN u8 MboxID,
    IN u32 MboxSize,
    IN _Sema *pWakeSema
)
{
  PRTL_MAILBOX pMBox=NULL;

  // if the Mailbox root entry initialed ? if not, initial it
  if (!MBox_Entry.isInitialed)
  {
    RtlMutexInit(&MBox_Entry.Mutex);// Init the Mutex for the mailbox add/delete procedure protection
    RtlInitListhead(&MBox_Entry.mbox_list);// Init the link list head to chain all created mailbox
    MBox_Entry.isInitialed = 1;
    MSG_MBOX_INFO("MBox Entry Initial...\n");
  }

  // check if this mailbox ID is ocupied ?
  pMBox = RtlMBoxIdToHdl(MboxID);
  if (NULL != pMBox)
  {
    MSG_MBOX_ERR("RtlMailboxCreate: The Mailbox ID %d is used by someone!!\n", MboxID);
    return NULL;
  }

  pMBox = (RTL_MAILBOX *)RtlZmalloc(sizeof(RTL_MAILBOX));
  if (NULL==pMBox)
  {
    MSG_MBOX_ERR("RtlMailboxCreate: MAlloc Failed\n");
    return NULL;
  }

  RtlInitListhead(&pMBox->mbox_list);// Init the link list to be chained into the created mailbox list
  pMBox->mbox_id = MboxID;
  pMBox->pWakeSema = pWakeSema;
#ifdef PLATFORM_FREERTOS
  pMBox->mbox_hdl = xQueueCreate(MboxSize, sizeof(MSG_BLK));
  if (NULL == pMBox->mbox_hdl)
  {
    MSG_MBOX_ERR("RtlMailboxCreate: xQueueCreate Failed\n");
    RtlMfree((void *)pMBox, sizeof(RTL_MAILBOX));
    return NULL;
  }
#endif
#ifdef PLATFORM_ECOS
// TODO: Create mailbox
#endif

  // Add this mailbox to the link list of created mailbox
  RtlDownMutex(&MBox_Entry.Mutex);
  RtlListInsertTail(&pMBox->mbox_list, &MBox_Entry.mbox_list);
  RtlUpMutex(&MBox_Entry.Mutex);

  MSG_MBOX_INFO("A Mailbox Created: Size=%d\n", MboxSize);

  return pMBox;
}

/******************************************************************************
 * Function: RtlMailboxDel
 * Desc: To delete a mailbox by a given mailbox handle.
 * Para:
 *	MboxHdl: The handle of the mailbox to be deleted.
 * Return: None.
 ******************************************************************************/
VOID RtlMailboxDel(
    IN PRTL_MAILBOX MboxHdl
)
{
  if (NULL == MboxHdl)
  {
    MSG_MBOX_ERR("RtlMailboxDel: Try to delete a NULL mailbox\n");
    return;
  }

  // Remove this mailbox from the link list of created mailbox
  RtlDownMutex(&MBox_Entry.Mutex);
  RtlListDelete(&MboxHdl->mbox_list);
  RtlUpMutex(&MBox_Entry.Mutex);

  // delete the Queue/Mailbox
#ifdef PLATFORM_FREERTOS
  vQueueDelete((xQueueHandle)(MboxHdl->mbox_hdl));
#endif
#ifdef PLATFORM_ECOS
  // TODO: Delete mailbox
#endif

  RtlMfree((void *)MboxHdl, sizeof(RTL_MAILBOX));
}

/******************************************************************************
 * Function: RtlMailboxSendToBack
 * Desc: To put a message block to the tail of a given mailbox.
 * Para:
 *  MboxID: The identifier of the target mailbox.
 *  pMsg: The pointer of the message block to be put into the mailbox.
 *  MSToWait: If the mailbox is full, this value gives a time to wait to put
 *            this message. The time unit is millisecond.
 *            The special values are:
 *               0: no waiting;
 *               0xffffffff: wait without timeout.
 *            If the waiting is timeout, the message sending is failed and
 *            return _FAIL.
 *  IsFromISR: Is this function is called from an ISR ?
 * Return: _SUCCESS or _FAIL.
 ******************************************************************************/
u8 RtlMailboxSendToBack(
    IN u8 MboxID,
    IN MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
)
{
  RTL_MAILBOX *pMbox=NULL;
  u32 wait_ticks;
#ifdef PLATFORM_FREERTOS
  portBASE_TYPE ret;
#endif

  pMbox = RtlMBoxIdToHdl(MboxID);

  if (NULL == pMbox)
  {
    MSG_MBOX_ERR("RtlMailboxSendToBack: Didn't find matched MBoxID=%d\n", MboxID);
    return _FAIL;
  }

#ifdef PLATFORM_FREERTOS
  if (MBOX_WAIT_NO_TIMEOUT == MSToWait)
  {
    wait_ticks = portMAX_DELAY;
  }
  else if (MBOX_WAIT_NONE == MSToWait)
  {
    wait_ticks = 0;
  }
  else
  {
    wait_ticks = ((MSToWait/portTICK_RATE_MS)>0)?(MSToWait/portTICK_RATE_MS):(1);
  }

  if (IsFromISR)
  {
    ret = xQueueSendToBackFromISR(pMbox->mbox_hdl, (void *)pMsg, NULL);//(portTickType) wait_ticks);
  }
  else
  {
    ret = xQueueSendToBack(pMbox->mbox_hdl, (void *)pMsg, (portTickType) wait_ticks);
  }

  if(ret != pdPASS )
  {
    // send message to the queue failed
    MSG_MBOX_ERR("RtlMailboxSendToBack: Put Msg to Queue Failed, MBoxID=%d\n", MboxID);
    ret = _FAIL;
  }
  else
  {
    // try to give a semaphore to wake up the receiving task
    if (pMbox->pWakeSema)
    {
      RtlUpSema(pMbox->pWakeSema);
    }
    ret = _SUCCESS;
  }

  return ret;
#endif

#ifdef PLATFORM_ECOS
  // TODO: Put the message to a mailbox
#endif

}

/******************************************************************************
 * Function: RtlMailboxSendToFront
 * Desc: To put a message block to the head of a mailbox.
 * Para:
 *  MboxID: The identifier of the target mailbox.
 *  pMsg: The pointer of the message block to be put into the mailbox.
 *  MSToWait: If the mailbox is full, this value gives a time to wait to put
 *            this message. The time unit is millisecond.
 *            The special values are:
 *               0: no waiting;
 *               0xffffffff: wait without timeout.
 *            If the waiting is timeout, the message sending is failed and
 *            return _FAIL.
 *  IsFromISR: Is this function is called from an ISR ?
 * Return: _SUCCESS or _FAIL.
 ******************************************************************************/
u8 RtlMailboxSendToFront(
    IN u8 MboxID,
    IN MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
)
{
  RTL_MAILBOX *pMbox=NULL;
  u32 wait_ticks;
#ifdef PLATFORM_FREERTOS
  portBASE_TYPE ret;
#endif

  pMbox = RtlMBoxIdToHdl(MboxID);

  if (NULL == pMbox)
  {
    MSG_MBOX_ERR("RtlMailboxSendToBack: Didn't find matched MBoxID=%d\n", MboxID);
    return _FAIL;
  }

#ifdef PLATFORM_FREERTOS
  if (MBOX_WAIT_NO_TIMEOUT == MSToWait)
  {
    wait_ticks = portMAX_DELAY;
  }
  else if (MBOX_WAIT_NONE == MSToWait)
  {
    wait_ticks = 0;
  }
  else
  {
    wait_ticks = ((MSToWait/portTICK_RATE_MS)>0)?(MSToWait/portTICK_RATE_MS):(1);
  }

  if (IsFromISR)
  {
    ret = xQueueSendToFrontFromISR(pMbox->mbox_hdl, (void *)pMsg, NULL);//(portTickType) wait_ticks);
  }
  else
  {
    ret = xQueueSendToFront(pMbox->mbox_hdl, (void *)pMsg, (portTickType) wait_ticks);
  }

  if(ret != pdPASS )
  {
    // send message to the queue failed
    MSG_MBOX_ERR("RtlMailboxSendToBack: Put Msg to Queue Failed, MBoxID=%d\n", MboxID);
    ret = _FAIL;
  }
  else
  {
    // try to give a semaphore to wake up the receiving task
    if (pMbox->pWakeSema)
    {
      RtlUpSema(pMbox->pWakeSema);
    }
    ret = _SUCCESS;
  }

  return ret;
#endif

#ifdef PLATFORM_ECOS
  // TODO: eCos has no API to put message to the head of a mailbox
#endif

}

/******************************************************************************
 * Function: RtlMailboxSendToFront
 * Desc: To get a message block from a given mailbox.
 * Para:
 *  MboxID: The identifier of the target mailbox.
 *  pMsg: The message block to store the gotten message.
 *  MSToWait: If the mailbox is full, this value gives a time to wait to put
 *            this message. The time unit is millisecond.
 *            The special values are:
 *               0: no waiting;
 *               0xffffffff: wait without timeout.
 *            If the waiting is timeout, the message sending is failed and
 *            return _FAIL.
 *  IsFromISR: Is this function is called from an ISR ?
 * Return: _SUCCESS or _FAIL.
 ******************************************************************************/
u8 RtlMailboxReceive(
    IN u8 MboxID,
    OUT MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
)
{
  RTL_MAILBOX *pMbox=NULL;
  u32 wait_ticks;
#ifdef PLATFORM_FREERTOS
  portBASE_TYPE ret;
#endif

  pMbox = RtlMBoxIdToHdl(MboxID);

  if (NULL == pMbox)
  {
    MSG_MBOX_ERR("RtlMailboxReceive: Didn't find the MBox with ID=%d\n", MboxID);
    return _FAIL;
  }

#ifdef PLATFORM_FREERTOS
  if (MBOX_WAIT_NONE == MSToWait)
  {
    wait_ticks = 0;
  }
  else if (MBOX_WAIT_NO_TIMEOUT == MSToWait)
  {
    wait_ticks = portMAX_DELAY;
  }
  else
  {
    wait_ticks = ((MSToWait/portTICK_RATE_MS)>0)?(MSToWait/portTICK_RATE_MS):(1);
  }

  if (IsFromISR)
  {
    ret = xQueueReceiveFromISR(pMbox->mbox_hdl, (void *)pMsg, NULL);//( portTickType ) wait_ticks);
  }
  else
  {
    ret = xQueueReceive(pMbox->mbox_hdl, (void *)pMsg, ( portTickType ) wait_ticks);

  }

  if(ret != pdTRUE )
  {
    // receive message failed
    if (0 != MSToWait)
    {
      MSG_MBOX_ERR("RtlMailboxReceive: Receive Msg Failed, MBoxID=%d\n", MboxID);
    }
    ret = _FAIL;
  }
  else
  {
    ret = _SUCCESS;
  }

  return ret;
#endif

#ifdef PLATFORM_ECOS
  // TODO: Get a message from the mailbox
#endif

}

/******************************************************************************
 * Function: RtlMailboxPeek
 * Desc: To copy the head message from a given mailbox without move this
 *       message block out from the mailbox.
 * Para:
 *  MboxID: The identifier of the target mailbox.
 *  pMsg: The message block to store the gotten message.
 *  MSToWait: If the mailbox is full, this value gives a time to wait to put
 *            this message. The time unit is millisecond.
 *            The special values are:
 *               0: no waiting;
 *               0xffffffff: wait without timeout.
 *            If the waiting is timeout, the message sending is failed and
 *            return _FAIL.
 *  IsFromISR: Is this function is called from an ISR ?
 * Return: _SUCCESS or _FAIL.
 ******************************************************************************/
u8 RtlMailboxPeek(
    IN u8 MboxID,
    OUT MSG_BLK *pMsg,
    IN u32 MSToWait,
    IN u8 IsFromISR
)
{
  RTL_MAILBOX *pMbox=NULL;
  u32 wait_ticks;
#ifdef PLATFORM_FREERTOS
  portBASE_TYPE ret;
#endif

  pMbox = RtlMBoxIdToHdl(MboxID);

  if (NULL == pMbox)
  {
    MSG_MBOX_ERR("RtlMailboxPeek: Didn't find the MBox with ID=%d\n", MboxID);
    return _FAIL;
  }

#ifdef PLATFORM_FREERTOS
  if (MBOX_WAIT_NONE == MSToWait)
  {
    wait_ticks = 0;
  }
  else if (MBOX_WAIT_NO_TIMEOUT == MSToWait)
  {
    wait_ticks = portMAX_DELAY;
  }
  else
  {
    wait_ticks = ((MSToWait/portTICK_RATE_MS)>0)?(MSToWait/portTICK_RATE_MS):(1);
  }

  if (IsFromISR)
  {
//        ret = xQueuePeekFromISR(pMbox->mbox_hdl, (void *)pMsg, ( portTickType ) wait_ticks);
    // TODO: check why we have no "xQueuePeekFromISR"
    MSG_MBOX_ERR("RtlMailboxPeek: Current version has no 'xQueuePeekFromISR'\n");
    ret = pdFALSE;
  }
  else
  {
    ret = xQueuePeek(pMbox->mbox_hdl, (void *)pMsg, ( portTickType ) wait_ticks);

  }

  if(ret != pdTRUE )
  {
    // receive message failed
    MSG_MBOX_ERR("RtlMailboxReceive: Receive Msg Failed, MBoxID=%d\n", MboxID);
    ret = _FAIL;
  }
  else
  {
    ret = _SUCCESS;
  }

  return ret;
#endif

#ifdef PLATFORM_ECOS
  // TODO: Get a message from the mailbox
#endif

}

/******************************************************************************
 * Function: RtlMailboxMsgWaiting
 * Desc: To get the number of message blocks are storing in a given mailbox.
 * Para:
 *  MboxID: The identifier of the target mailbox.
 *  IsFromISR: Is this function is called from an ISR ?
 * Return: The number of message blocks are storing in this mailbox.
 ******************************************************************************/
u32 RtlMailboxMsgWaiting(
    IN u8 MboxID,
    IN u8 IsFromISR
)
{
  RTL_MAILBOX *pMbox=NULL;
  u32 msg_num=0;

  pMbox = RtlMBoxIdToHdl(MboxID);

  if (NULL == pMbox)
  {
    MSG_MBOX_ERR("RtlMailboxMsgWaiting: Didn't find the MBox with ID=%d\n", MboxID);
    return 0;
  }

#ifdef PLATFORM_FREERTOS
  if (IsFromISR)
  {
    msg_num = uxQueueMessagesWaitingFromISR(pMbox->mbox_hdl);
  }
  else
  {
    msg_num = uxQueueMessagesWaiting(pMbox->mbox_hdl);
  }
#endif

#ifdef PLATFORM_ECOS
  // TODO: call eCos API to implement this function
#endif

  return msg_num;

}

//------------------------------------------------------
#define DEVICE_MUTEX_IS_INIT(device)	(mutex_init & (1<<device))
#define DEVICE_MUTEX_SET_INIT(device)	(mutex_init |= (1<<device))
#define DEVICE_MUTEX_CLR_INIT(device)	(mutex_init &= (~(1<<device)))

static u32 mutex_init = 0;
static _mutex device_mutex[ RT_DEV_LOCK_MAX ];

//======================================================
static void device_mutex_init( RT_DEV_LOCK_E device )
{
  if ( !DEVICE_MUTEX_IS_INIT( device ) )
  {
    _lock lock;
    _irqL irqL;
    rtw_enter_critical( &lock, &irqL );
    if ( !DEVICE_MUTEX_IS_INIT( device ) )
    {
      rtw_mutex_init( &device_mutex[ device ] );
      DEVICE_MUTEX_SET_INIT( device );
    }
    rtw_exit_critical( &lock, &irqL );
  }
}

//======================================================
static void device_mutex_free( RT_DEV_LOCK_E device )
{
  if ( DEVICE_MUTEX_IS_INIT( device ) )
  {
    _lock lock;
    _irqL irqL;
    rtw_enter_critical( &lock, &irqL );
    if ( !DEVICE_MUTEX_IS_INIT( device ) )
    {
      rtw_mutex_free( &device_mutex[ device ] );
      DEVICE_MUTEX_CLR_INIT( device );
    }
    rtw_exit_critical( &lock, &irqL );
  }
}

//======================================================
void device_mutex_lock( RT_DEV_LOCK_E device )
{
  device_mutex_init( device );
  while ( rtw_mutex_get_timeout( &device_mutex[ device ], 10000 ) < 0 )
    printf( "device lock timeout: %d\n", device );
}

//======================================================
void device_mutex_unlock( RT_DEV_LOCK_E device )
{
  device_mutex_init( device );
  rtw_mutex_put( &device_mutex[ device ] );
}
