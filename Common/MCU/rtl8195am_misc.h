#ifndef __RTL8195AM_MISC_H__
#define __RTL8195AM_MISC_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

// ToDo
typedef fpos_t _fpos_t;
typedef unsigned long __ULong;
typedef struct _Bigint _Bigint;
typedef struct _reent _reent;
typedef size_t _ssize_t;

#ifndef _READ_WRITE_RETURN_TYPE
#define _READ_WRITE_RETURN_TYPE         _ssize_t
#endif

#ifndef _READ_WRITE_BUFSIZE_TYPE
#define _READ_WRITE_BUFSIZE_TYPE        int
#endif

#define __rom_mallocr_init              __rom_mallocr_init_v1_00
#define __rtl_Balloc                    __rtl_Balloc_v1_00
#define __rtl_Bfree                     __rtl_Bfree_v1_00
#define __rtl_calloc_r                  __rtl_calloc_r_v1_00
#define __rtl_cfree_r                   __rtl_cfree_r_v1_00
#define __rtl_cmp                       __rtl_cmp_v1_00
#define __rtl_d2b                       __rtl_d2b_v1_00
#define __rtl_dadd                      __rtl_dadd_v1_00
#define __rtl_dcmpeq                    __rtl_dcmpeq_v1_00
#define __rtl_dcmpgt                    __rtl_dcmpgt_v1_00
#define __rtl_dcmplt                    __rtl_dcmplt_v1_00
#define __rtl_ddiv                      __rtl_ddiv_v1_00
#define __rtl_diff                      __rtl_diff_v1_00
#define __rtl_dmul                      __rtl_dmul_v1_00
#define __rtl_dsub                      __rtl_dsub_v1_00
#define __rtl_dtoa_r                    __rtl_dtoa_r_v1_00
#define __rtl_dtoi                      __rtl_dtoi_v1_00
#define __rtl_fflush_r                  __rtl_fflush_r_v1_00
#define __rtl_free_r                    __rtl_free_r_v1_00
#define __rtl_hi0bits                   __rtl_hi0bits_v1_00
#define __rtl_i2b                       __rtl_i2b_v1_00
#define __rtl_itod                      __rtl_itod_v1_00
#define __rtl_lshift                    __rtl_lshift_v1_00
#define __rtl_malloc_r                  __rtl_malloc_r_v1_00
#define __rtl_memalign_r                __rtl_memalign_r_v1_00
#define __rtl_memchr                    __rtl_memchr_v1_00
#define __rtl_memcpy                    __rtl_memcpy_v1_00
#define __rtl_memmove                   __rtl_memmove_v1_00
#define __rtl_memset                    __rtl_memset_v1_00
#define __rtl_mult                      __rtl_mult_v1_00
#define __rtl_multadd                   __rtl_multadd_v1_00
#define __rtl_pow5mult                  __rtl_pow5mult_v1_00
#define __rtl_pvalloc_r                 __rtl_pvalloc_r_v1_00
#define __rtl_realloc_r                 __rtl_realloc_r_v1_00
#define __rtl_sbrk_r                    __rtl_sbrk_r_v1_00
#define __rtl_sclose                    __rtl_sclose_v1_00
#define __rtl_seofread                  __rtl_seofread_v1_00
#define __rtl_sread                     __rtl_sread_v1_00
#define __rtl_sseek                     __rtl_sseek_v1_00
#define __rtl_strcmp                    __rtl_strcmp_v1_00
#define __rtl_swrite                    __rtl_swrite_v1_00
#define __rtl_uitod                     __rtl_uitod_v1_00
#define __rtl_uitof                     __rtl_uitof_v1_00
#define __rtl_valloc_r                  __rtl_valloc_r_v1_00
#define __rtl_vfprintf_r                __rtl_vfprintf_r_v1_00

extern uint32_t __rtl_errno;            // 0x10000bc4

extern _LONG_CALL_ _Bigint * __rtl_Balloc_v1_00( _reent * ptr, int k );
extern _LONG_CALL_ _Bigint * __rtl_d2b_v1_00( _reent * ptr, double _d, int * e, int * bits );
extern _LONG_CALL_ _Bigint * __rtl_diff_v1_00( struct _reent* ptr, _Bigint * a, _Bigint * b );
extern _LONG_CALL_ _Bigint * __rtl_i2b_v1_00( _reent * ptr, int i );
extern _LONG_CALL_ _Bigint * __rtl_lshift_v1_00( _reent * ptr, _Bigint * b, int k );
extern _LONG_CALL_ _Bigint * __rtl_mult_v1_00( _reent * ptr, _Bigint * a, _Bigint * b );
extern _LONG_CALL_ _Bigint * __rtl_multadd_v1_00( _reent * ptr, _Bigint * b, int m, int a );
extern _LONG_CALL_ _Bigint * __rtl_pow5mult_v1_00( _reent * ptr, _Bigint * b, int k );
extern _LONG_CALL_ _fpos_t __rtl_sseek_v1_00( _reent * ptr, void * cookie, _fpos_t offset, int whence );

extern _LONG_CALL_ _READ_WRITE_RETURN_TYPE __rtl_seofread_v1_00( struct _reent * _ptr, _PTR cookie, char * buf, _READ_WRITE_BUFSIZE_TYPE len);
extern _LONG_CALL_ _READ_WRITE_RETURN_TYPE __rtl_sread_v1_00( _reent * ptr, void * cookie, char * buf,
_READ_WRITE_BUFSIZE_TYPE n );
extern _LONG_CALL_ _READ_WRITE_RETURN_TYPE __rtl_swrite_v1_00( _reent * ptr, void * cookie, char const * buf,
_READ_WRITE_BUFSIZE_TYPE n );

extern _LONG_CALL_ double __rtl_dadd_v1_00( double a, double b );
extern _LONG_CALL_ double __rtl_ddiv_v1_00( double a, double b );
extern _LONG_CALL_ double __rtl_dmul_v1_00( double a, double b );
extern _LONG_CALL_ double __rtl_dsub_v1_00( double a, double b );
extern _LONG_CALL_ double __rtl_itod_v1_00( int lval );
extern _LONG_CALL_ double __rtl_uitod_v1_00( unsigned int lval );
extern _LONG_CALL_ float __rtl_uitof_v1_00( unsigned int lval );
extern _LONG_CALL_ int __rtl_cmp_v1_00( _Bigint * a, _Bigint * b );
extern _LONG_CALL_ int __rtl_dcmpeq_v1_00( double a, double b );
extern _LONG_CALL_ int __rtl_dcmpgt_v1_00( double a, double b );
extern _LONG_CALL_ int __rtl_dcmplt_v1_00( double a, double b );
extern _LONG_CALL_ int __rtl_dtoi_v1_00( double d );
extern _LONG_CALL_ int __rtl_fflush_r_v1_00( _reent * ptr, register FILE * fp );
extern _LONG_CALL_ int __rtl_hi0bits_v1_00( register __ULong x );
extern _LONG_CALL_ int __rtl_sclose_v1_00( _reent * ptr, void * cookie );
extern _LONG_CALL_ int __rtl_strcmp_v1_00( const char * s1, const char * s2 );
extern _LONG_CALL_ int __rtl_vfprintf_r_v1_00( struct _reent *, FILE *, const char *, va_list );
extern _LONG_CALL_ void * __rtl_memchr_v1_00( const void * src_void, int c, size_t length );
extern _LONG_CALL_ void * __rtl_memcpy_v1_00( void * __restrict dst0, const void * __restrict src0, size_t len0 );
extern _LONG_CALL_ void * __rtl_memmove_v1_00( void * dst_void, const void * src_void, size_t length );
extern _LONG_CALL_ void * __rtl_memset_v1_00( void * m, int c, size_t n );
extern _LONG_CALL_ void * __rtl_sbrk_r_v1_00( _reent * ptr, ptrdiff_t incr );
extern _LONG_CALL_ void __rom_mallocr_init_v1_00( void );
extern _LONG_CALL_ void __rtl_Bfree_v1_00( _reent * ptr, _Bigint * v );
extern _LONG_CALL_ void __rtl_cfree_r_v1_00( void * mem );
extern _LONG_CALL_ void __rtl_free_r_v1_00( RARG void* mem );
extern _LONG_CALL_ void* __rtl_calloc_r_v1_00( RARG size_t n, size_t elem_size );
extern _LONG_CALL_ void* __rtl_malloc_r_v1_00( RARG size_t bytes );
extern _LONG_CALL_ void* __rtl_memalign_r_v1_00( RARG size_t alignment, size_t bytes );
extern _LONG_CALL_ void* __rtl_pvalloc_r_v1_00( RARG size_t bytes );
extern _LONG_CALL_ void* __rtl_realloc_r_v1_00( RARG void* oldmem, size_t bytes );
extern _LONG_CALL_ void* __rtl_valloc_r_v1_00( RARG size_t bytes );

extern char * __rtl_dtoa_r_v1_00( _reent * ptr, double _d, int mode, int ndigits, int * decpt, int * sign,
  char * * rve );

extern _LONG_CALL_ u32 HalDelayUs( u32 us );
extern _LONG_CALL_ u32 HalGetCpuClk( VOID );
extern _LONG_CALL_ u8 HalGetRomInfo( VOID );
VOID HalSetResetCause( IN HAL_RESET_REASON reason );
HAL_RESET_REASON HalGetResetCause( VOID );

extern _LONG_CALL_ROM_ void *_memset( void *s, int c, SIZE_T n );
extern _LONG_CALL_ROM_ void *_memcpy( void *s1, const void *s2, SIZE_T n );
#if defined(CONFIG_RELEASE_BUILD_LIBRARIES) && (!defined(E_CUT_ROM_DOMAIN))
// we built A/B/C cut ROM Lib with this wrong declaration, we need to keep the same for compatible
extern _LONG_CALL_ROM_ int *_memcmp( const void *av, const void *bv, SIZE_T len );
#else
extern _LONG_CALL_ROM_ int _memcmp( const void *av, const void *bv, SIZE_T len );
#endif
extern _LONG_CALL_ROM_ SIZE_T _strlen( const char *s );
extern _LONG_CALL_ROM_ int _strcmp( const char *cs, const char *ct );

extern unsigned int rand_x;

u32 Rand2( void );
u32 Rand( VOID );

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct LIST_HEADER
{
  struct LIST_HEADER *Next, *Prev;
};

typedef struct LIST_HEADER _LIST;

#define RTL_LIST_CONTAINOR(ptr, type, member) \
        ((type *)((char *)(ptr)-(SIZE_T)(&((type *)0)->member)))

#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member) \
        ((type *)((char *)(ptr)-(SIZE_T)(&((type *)0)->member)))
#endif

#define list_entry(ptr, type, member) \
    CONTAINER_OF(ptr, type, member)

#define list_first_entry(ptr, type, member) \
        list_entry((ptr)->Next, type, member)

#define list_next_entry(pos, member, type) \
        list_entry((pos)->member.Next, type, member)

#define list_for_each_entry(pos, head, member, type) \
        for (pos = list_first_entry(head, type, member); \
             &pos->member != (head); \
             pos = list_next_entry(pos, member, type))
#define list_for_each(pos, head) \
        for (pos = (head)->Next; pos != (head); pos = pos->Next)

#define RTL_LIST_HEAD_INIT(name) { &(name), &(name) }

#define RTL_INIT_LIST_HEAD(ptr) do { \
  (ptr)->Next = (ptr); (ptr)->Prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline__ VOID __List_Add( IN struct LIST_HEADER * New, IN struct LIST_HEADER * Prev,
  IN struct LIST_HEADER * Next )
{
  Next->Prev = New;
  New->Next = Next;
  New->Prev = Prev;
  Prev->Next = New;
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline__ VOID __List_Del( IN struct LIST_HEADER * Prev, IN struct LIST_HEADER * Next )
{
  Next->Prev = Prev;
  Prev->Next = Next;
}

/**
 * ListDel - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
static __inline__ VOID ListDel( IN struct LIST_HEADER *Entry )
{
  __List_Del( Entry->Prev, Entry->Next );
}

/**
 * ListDelInit - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static __inline__ VOID ListDelInit( IN struct LIST_HEADER *Entry )
{
  __List_Del( Entry->Prev, Entry->Next );
  RTL_INIT_LIST_HEAD( Entry );

}

/**
 * ListEmpty - tests whether a list is empty
 * @head: the list to test.
 */
static __inline__ u32 ListEmpty( IN struct LIST_HEADER *Head )
{
  return Head->Next == Head;
}

/**
 * ListSplice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static __inline__ VOID ListSplice( IN struct LIST_HEADER *List, IN struct LIST_HEADER *Head )
{
  struct LIST_HEADER *First = List->Next;

  if ( First != List )
  {
    struct LIST_HEADER *Last = List->Prev;
    struct LIST_HEADER *At = Head->Next;

    First->Prev = Head;
    Head->Next = First;

    Last->Next = At;
    At->Prev = Last;
  }
}

static __inline__ VOID ListAdd( IN struct LIST_HEADER *New, IN struct LIST_HEADER *head )
{
  __List_Add( New, head, head->Next );
}

static __inline__ VOID ListAddTail( IN struct LIST_HEADER *New, IN struct LIST_HEADER *head )
{
  __List_Add( New, head->Prev, head );
}

static __inline VOID RtlInitListhead( IN _LIST *list )
{
  RTL_INIT_LIST_HEAD( list );
}

/*
 For the following list_xxx operations,
 caller must guarantee the atomic context.
 Otherwise, there will be racing condition.
 */
static __inline u32 RtlIsListEmpty( IN _LIST *phead )
{
  if ( ListEmpty( phead ) )
    return _TRUE;
  else
    return _FALSE;
}

static __inline VOID RtlListInsertHead( IN _LIST *plist, IN _LIST *phead )
{
  ListAdd( plist, phead );
}

static __inline VOID RtlListInsertTail( IN _LIST *plist, IN _LIST *phead )
{
  ListAddTail( plist, phead );
}

static __inline _LIST *RtlListGetNext( IN _LIST *plist )
{
  return plist->Next;
}

static __inline VOID RtlListDelete( IN _LIST *plist )
{
  ListDelInit( plist );
}

extern _LONG_CALL_ROM_ char *_strncpy( char *dest, const char *src, size_t count );
extern _LONG_CALL_ROM_ char *_strcpy( char *dest, const char *src );
extern _LONG_CALL_ROM_ size_t _strlen( const char *s );
extern _LONG_CALL_ROM_ size_t _strnlen( const char *s, size_t count );
extern _LONG_CALL_ROM_ int _strcmp( const char *cs, const char *ct );
extern _LONG_CALL_ROM_ int _strncmp( const char *cs, const char *ct, size_t count );
extern _LONG_CALL_ROM_ int _sscanf( const char *buf, const char *fmt, ... );
extern _LONG_CALL_ROM_ char *_strsep( char **s, const char *ct );
extern _LONG_CALL_ROM_ char *skip_spaces( const char *str );
extern _LONG_CALL_ROM_ int skip_atoi( const char **s );
extern _LONG_CALL_ROM_ int _vsscanf( const char *buf, const char *fmt, va_list args );
extern _LONG_CALL_ROM_ unsigned long long simple_strtoull( const char *cp, char **endp, unsigned int base );
extern _LONG_CALL_ROM_ long simple_strtol( const char *cp, char **endp, unsigned int base );
extern _LONG_CALL_ROM_ long long simple_strtoll( const char *cp, char **endp, unsigned int base );
extern _LONG_CALL_ROM_ unsigned long simple_strtoul( const char *cp, char **endp, unsigned int base );
extern _LONG_CALL_ROM_ const char *_parse_integer_fixup_radix( const char *s, unsigned int *base );
extern _LONG_CALL_ROM_ unsigned int _parse_integer( const char *s, unsigned int base, unsigned long long *p );
extern _LONG_CALL_ROM_ u64 div_u64( u64 dividend, u32 divisor );
extern _LONG_CALL_ROM_ s64 div_s64( s64 dividend, s32 divisor );
extern _LONG_CALL_ROM_ u64 div_u64_rem( u64 dividend, u32 divisor, u32 *remainder );
extern _LONG_CALL_ROM_ s64 div_s64_rem( s64 dividend, s32 divisor, s32 *remainder );
extern _LONG_CALL_ROM_ char *_strpbrk( const char *cs, const char *ct );
extern _LONG_CALL_ROM_ char *_strchr( const char *s, int c );
extern _LONG_CALL_ROM_ void prvStrCpy( IN u8 *pDES, IN const u8 *pSRC );
extern _LONG_CALL_ROM_ u32 prvStrLen( IN const u8 *pSRC );
extern _LONG_CALL_ROM_ u8 prvStrCmp( IN const u8 *string1, IN const u8 *string2 );
extern _LONG_CALL_ROM_ u8* StrUpr( IN u8 *string );
extern _LONG_CALL_ROM_ int prvAtoi( IN const char * s );
extern _LONG_CALL_ROM_ const char * prvStrStr( IN const char * str1, IN const char * str2 );

#ifndef strtoul
#define strtoul(str, endp, base)       simple_strtoul(str, endp, base)
#endif
#ifndef strtol
#define strtol(str, endp, base)        simple_strtol(str, endp, base)
#endif

VOID RtlMemcpy( VOID* dec, VOID* sour, u32 sz );
u32 RtlMemcmp( VOID *dst, VOID *src, u32 sz );
VOID RtlMemset( VOID *pbuf, u32 c, u32 sz );

s8 *
RtlStrncpy(
    IN s8 *dest,
    IN const s8 *src,
    IN SIZE_T count
);

s8 *
RtlStrcpy(
    IN s8 *dest,
    IN const s8 *src
);

SIZE_T
RtlStrlen(
    IN const s8 *s
);

SIZE_T
RtlStrnlen(
    IN const s8 *s,
    IN SIZE_T count
);

int
RtlStrcmp(
    IN const s8 *cs,
    IN const s8 *ct

);

int
RtlStrncmp(
    IN const s8 *cs,
    IN const s8 *ct,
    IN SIZE_T count
);

//
// string operation
//
#define strlen(str)						prvStrLen((const u8*)str)
#define strcmp(str1, str2)				prvStrCmp((const u8*)str1, (const u8*)str2)
#define sscanf(src, format...)				//TODO
#define strtok(str, delim)				prvStrTok(str, delim)
#define strcpy(dst, src)					prvStrCpy((u8 *)dst, (const u8*)src)
#define atoi(str)						prvAtoi(str)
#define strstr(str1, str2)					prvStrStr(str1, str2)

//
// standard i/o
//
#define snprintf							DiagSnPrintf
#define sprintf							prvDiagSPrintf
#define printf 							prvDiagPrintf

//
// memory management
//
#define malloc 							pvPortMalloc
#define free							vPortFree

extern int __rtl_errno;

void init_rom_libgloss_ram_map( void );

//
// RTL library functions for Libc::stdio
//

extern int rtl_printf(IN const char* fmt, ...);
extern int rtl_vprintf( const char *fmt, void *param );
extern int rtl_sprintf( char* str, const char* fmt, ... );
extern int rtl_snprintf( char* str, size_t size, const char* fmt, ... );
extern int rtl_vsnprintf( char *str, size_t size, const char *fmt, void *param );

//
// RTL library functions for string
//

extern void * rtl_memchr( const void * src_void, int c, size_t length );
extern int rtl_memcmp( const void * m1, const void * m2, size_t n );
extern void * rtl_memcpy( void * dst0, const void * src0, size_t len0 );
extern void * rtl_memmove( void * dst_void, const void * src_void, size_t length );
extern void * rtl_memset( void * m, int c, size_t n );
extern char * rtl_strcat( char * s1, const char * s2 );
extern char * rtl_strchr( const char *s1, int i );
extern int rtl_strcmp( const char *s1, const char *s2 );
extern char* rtl_strcpy( char *dst0, const char *src0 );
extern size_t rtl_strlen( const char *str );
extern char * rtl_strncat( char * s1, const char * s2, size_t n );
extern int rtl_strncmp( const char *s1, const char *s2, size_t n );
extern char * rtl_strncpy( char * dst0, const char * src0, size_t count );
extern char * rtl_strstr( const char *searchee, const char *lookfor );
extern char * rtl_strsep( char **source_ptr, const char *delim );
extern char * rtl_strtok( char * s, const char * delim );

//
// RTL library functions for math
//

extern double rtl_fabs( double );
extern float rtl_fabsf( float a );
extern float rtl_cos_f32( float a );
extern float rtl_sin_f32( float a );

extern float rtl_fadd( float a, float b );
extern float rtl_fsub( float a, float b );
extern float rtl_fmul( float a, float b );
extern float rtl_fdiv( float a, float b );

extern int rtl_fcmplt( float a, float b );
extern int rtl_fcmpgt( float a, float b );

//
// RTL eabi functions

extern double rtl_ftod( float f );

extern double rtl_ddiv( double a, double b );

//
// Macro Library Functions
//

typedef union
{
  float value;
  u32 word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)					\
do {								\
  ieee_float_shape_type gf_u;					\
  gf_u.value = (d);						\
  (i) = gf_u.word;						\
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)					\
do {								\
  ieee_float_shape_type sf_u;					\
  sf_u.word = (i);						\
  (d) = sf_u.value;						\
} while (0)

static inline
float rtl_nanf( void )
{
  float x;

  SET_FLOAT_WORD( x, 0x7fc00000 );
  return x;
}

//
// Library Test functions
//

extern int rtl_lib_test(IN u16 argc, IN u8 *argv[]);
extern int rtl_math_test(IN u16 argc, IN u8 *argv[]);
extern int rtl_string_test(IN u16 argc, IN u8 *argv[]);

//
// Macro functions
//

#undef dbg_printf
#define dbg_printf(fmt, args...) \
	     	rtl_printf("%s():%d : " fmt "\n", __FUNCTION__, __LINE__, ##args);

#undef err_printf
#define err_printf(fmt, args...) \
	     	rtl_printf("%s():%d : " fmt "\n", __FUNCTION__, __LINE__, ##args);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_MISC_H__ */
