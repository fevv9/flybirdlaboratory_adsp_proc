#ifndef SNS_MEMMGR_H
#define SNS_MEMMGR_H

/*============================================================================
  @file sns_memmgr.h

  @brief
  Defines the sensors memory manager interface.

  <br><br>

  DEPENDENCIES:

Copyright (c) 2010, 2012-2014 Qualcomm Technologies, Inc. All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
  ============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. Please
  use ISO format for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/common/util/memmgr/inc/sns_memmgr.h#2 $
  $DateTime: 2014/12/05 22:23:15 $

  when       who    what, where, why
  ---------- --- -----------------------------------------------------------
  2014-10-27 hw  Divide BigImage heap to two parts: default heap and memheap. Each
                 will have size of 512K. Also add lowmem callback function support
  2014-08-25 vy  uImage heap size to 44K
  2014-08-25 vy  uImage heap size to 40K
  2014-08-15 asj Modified to use internal function instead of macros.
  2014-06-20 sc  Make this header file common between ADSP and AP
  2014-06-12 vy  uImage heap size to 32K
  2014-06-05 vy  Updated SNS_OS_U_MALLOC to return int
  2014-05-29 pn  Reduced uImage heap size to 32K
  2014-02-26 MW  Added SNS_OS_MEMSCPY
  2012-11-21 vh  Added SNS_OS_MEMSET for SNS_OS_MALLOC
  2012-11-15 ps  Replaced default heap id with sensors head id for SNS_OS_MALLOC
  2011-11-30 jtl Updating macors for USE_NATIVE_MALLOC to work with heap
                 analysis changes
  2011-11-22 br  Differenciated between USE_NATIVE_MEMCPY and USE_NATIVE_MALLOC
  2011-11-14 jhh Added heap memory analysis feature
  2010-11-03 jtl Implementing USE_NATIVE_MALLOC macro handling
  2010-08-30 JTL Moving init function decl into sns_init.h
  2010-08-26 jtl Added header comments

  ============================================================================*/
/*=====================================================================
                       INCLUDES
=======================================================================*/
#include "sns_common.h"
#include "sns_debug_str.h"

#if (defined USE_NATIVE_MEMCPY || defined USE_NATIVE_MALLOC)
#  include "stdlib.h"
#  include "string.h"
#endif
#if !(defined USE_NATIVE_MEMCPY && defined USE_NATIVE_MALLOC)
#  include "mem_cfg.h"
#endif /* USE_NATIVE_MALLOC */

#if defined(QDSP6)
#include "memheap.h"
#include "sns_memheap_lite.h"
extern mem_heap_type     sns_heap_state;
extern mem_heap_totals_type sns_heap_total;

/* check sensors' heap status for every 1000 times of allocations. This avoid checking status for
 * everytime using sensors heap malloc, which will result in huge latency */
#define SNS_HEAP_CHECK_COUNTER 1000

/* return the current size (in unit of bytes) of used heap in sensors' heap */
uint32_t sns_memmgr_sensor_heap_usage(void);
#endif

/* Define the size of the heap to be used in uImage */
#ifdef SNS_HIMEM_UIMG
#define SNS_UIMAGE_HEAP_SIZE (75 * 1024) // in bytes
#else
#define SNS_UIMAGE_HEAP_SIZE (34 * 1024) // in bytes
#endif

/*=====================================================================
                    INTERNAL DEFINITIONS AND TYPES
=======================================================================*/
/* used to set debugging level (0~2) */
#define SNS_DEBUG   0
#define SNS_MAX_NUM_MEMMGR_CLIENTS 5
/*
 * memmgr callback function type. used by other sensors' module to register
 * callback function to memmgr
 */
typedef void (*sns_memmgr_lowmem_cb_t)(void);

/* low memory callback function structure */
typedef struct sns_memmgr_lowmem_cb_s
{
  uint8 num_clients;
  sns_memmgr_lowmem_cb_t cb_func[SNS_MAX_NUM_MEMMGR_CLIENTS];
} sns_memmgr_lowmem_cb_s;

sns_memmgr_lowmem_cb_s sns_default_heap_lowmem_cb;
sns_memmgr_lowmem_cb_s sns_sensors_heap_lowmem_cb;

#define SNS_DEFAULT_HEAP_LOW_MEM_THRESH (512 * 1024)
#define SNS_SENSORS_HEAP_LOW_MEM_THRESH (400 * 1024) // 80% of sensor heap usage
#define SNS_SENSORS_HEAP_MEDIUM_MEM_THRESH (320 * 1024) // 60% of sensor heap usage

/* Heap type used for sensors */
typedef enum{
  SNS_DEFAULT_HEAP_TYPE,
  SNS_SENSORS_HEAP_TYPE
}sns_heap_type;

/* verbose level set up */
#ifdef SNS_DEBUG
 #if SNS_DEBUG == 0
  #define DBG_PRINT1(x) (void)0
  #define DBG_PRINT2(x) (void)0
 #else
  #if SNS_DEBUG == 1
#include <stdio.h>
#ifdef _WIN32
   #define DBG_PRINT1(x) (void)(sns_trace x)
   #define DBG_PRINT2(x) (void)0
#else
   #define DBG_PRINT1(x) (void)(printf x)
   #define DBG_PRINT2(x) (void)0
#endif /* _WIN32 */
   #define OI_DEBUG
  #elif SNS_DEBUG == 2
#include <stdio.h>
#ifdef _WIN32
   #define DBG_PRINT1(x) (void)(sns_trace x)
   #define DBG_PRINT2(x) (void)0
#else
   #define DBG_PRINT1(x) (void)(printf x)
   #define DBG_PRINT2(x) (void)(printf x)
#endif /* _WIN32 */
   #define OI_DEBUG
  #endif
 #endif
#endif

#ifdef SNS_MEMMGR_PROFILE_ON
#define SNS_OS_MEMSTAT_SUMMARY_POOLS(pool_id)     SUMMARY_DUMP(pool_id)
#define SNS_OS_MEMSTAT_DETAIL_POOLS(pool_id)      DETAIL_DUMP(pool_id)

typedef enum {
  POOL_16_BYTE,
  POOL_24_BYTE,
  POOL_32_BYTE,
  POOL_64_BYTE,
  POOL_128_BYTE,
  POOL_256_BYTE,
  POOL_512_BYTE,
  POOL_1024_BYTE,
  POOL_ALL
} mem_pool_e;
#else
#define SNS_OS_MEMSTAT_SUMMARY_POOLS(pool_id)     (void)0
#define SNS_OS_MEMSTAT_DETAIL_POOLS(pool_id)      (void)0
#endif

#ifdef USE_NATIVE_MEMCPY
#  define SNS_OS_MEMCOPY(to,from,size)  memcpy(to, from, size)
#  define SNS_OS_MEMSET(block,val,size) memset(block, val, size)
#  define SNS_OS_MEMZERO(block,size)    memset(block, 0, size)
#  define SNS_OS_MEMCMP(s1,s2,n)        memcmp(s1, s2, n)
#  define SNS_OS_MEMSCPY(dst, dst_size, src, copy_size)  memscpy(dst, dst_size, src, copy_size)
#else
#  define SNS_OS_MEMCOPY(to,from,size)  OI_MemCopy(to, from, size)
#  define SNS_OS_MEMSET(block,val,size) OI_MemSet(block, val, size)
#  define SNS_OS_MEMZERO(block,size)    OI_MemZero(block, size)
#  define SNS_OS_MEMCMP(s1,s2,n)        OI_MemCmp(s1, s2, n)
#  define SNS_OS_MEMSCPY(dst, dst_size, src, copy_size)  OI_MemCopy(dst, src, copy_size)
#endif

#ifdef USE_NATIVE_MALLOC
#  define SNS_OS_MALLOC(module,size)    malloc(size)
#  define SNS_OS_SENSOR_HEAP_MALLOC(module,size)    malloc(size)
#  define SNS_OS_U_MALLOC(module,size)    malloc(size)
#  define SNS_OS_ANY_MALLOC(module,size)  malloc(size)
#  define SNS_OS_FREE(block)            free(block)
#  define SNS_OS_SENSOR_HEAP_FREE(block)            free(block)
#  define SNS_OS_U_FREE(block)            free(block)
#  define SNS_OS_ANY_FREE(block)          free(block)
#  define SNS_OS_SENSOR_HEAP_ANY_FREE(block)      free(block)
#  define SNS_OS_IS_UHEAP_PTR(ptr)        (0)
#  define SNS_OS_CHGLLOC(new_mod,block)
#elif defined(QDSP6)

#define SNS_OS_FREE(block)            qurt_elite_memory_free(block)
#define SNS_OS_SENSOR_HEAP_FREE(block)     mem_free(&sns_heap_state, block)

static inline void *SNS_OS_MALLOC(uint8_t module, uint32_t size)
{
  void *buffer = NULL;
  uint32_t i;

  /* check if curre_heap usage is beyond the low memory threshold. If it is, call callback function
   * to address the state before really running out of memory */
  if(qurt_elite_globalstate.avs_stats.curr_heap > SNS_DEFAULT_HEAP_LOW_MEM_THRESH)
  {
    UMSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO, "calling callback function - heap size %d, peak heap %d, callback func num %d",
           qurt_elite_globalstate.avs_stats.curr_heap,
           qurt_elite_globalstate.avs_stats.peak_heap,
           sns_default_heap_lowmem_cb.num_clients );
    for( i = 0; i < sns_default_heap_lowmem_cb.num_clients; i++ )
    {
      if(NULL != sns_default_heap_lowmem_cb.cb_func[i])
      {
        UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO,
               "default heap calling callback function i=%d", i );
        (*sns_default_heap_lowmem_cb.cb_func[i])();
      }
    }
  }

  buffer = qurt_elite_memory_malloc(size, sns_heap_id);
  if (buffer != NULL)
  {
     SNS_OS_MEMSET(buffer, 0, size);
  }
  else
  {
  	 UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO, "SNS_OS_MALLOC failed - size %d",size);
  }
  return buffer;
}

static inline void *SNS_OS_SENSOR_HEAP_MALLOC(uint8_t module, uint32_t size)
{
  static uint32_t counter = 0;
  uint32_t i, heap_usage;
  void *buffer = NULL;

  /* the checkCounter will be dynamically changing depending the state of memory usage */
  static uint32_t checkCounter = SNS_HEAP_CHECK_COUNTER;

  if( counter > checkCounter )
  {
    heap_usage = sns_memmgr_sensor_heap_usage();
    if( heap_usage > SNS_SENSORS_HEAP_LOW_MEM_THRESH )
    {
      UMSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO,
             "sam heap calling callback function - heap usage %d, largest_free %d, checkCounter %d,",
             (uint32_t)heap_usage,
             (uint32_t)sns_heap_state.largest_free_block,
             checkCounter );
      for( i = 0; i < sns_sensors_heap_lowmem_cb.num_clients; i++ )
      {
        if(NULL != sns_sensors_heap_lowmem_cb.cb_func[i])
        {
          UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO,
                "sam heap calling callback function i=%d", i );
          (sns_sensors_heap_lowmem_cb.cb_func[i])();
        }
      }
     }
     else if( heap_usage > SNS_SENSORS_HEAP_MEDIUM_MEM_THRESH )
     {
       checkCounter = SNS_HEAP_CHECK_COUNTER >> 1;
     }
     else
     {
       checkCounter = SNS_HEAP_CHECK_COUNTER;
     }
    counter = 0;
  }
  counter++;
  buffer = mem_malloc(&sns_heap_state, size);

  if (buffer != NULL)
  {
    SNS_OS_MEMSET(buffer, 0, size);
  }
  else
  {
  	UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO, "SNS_OS_SENSOR_HEAP_MALLOC failed - size %d",size);
  }
  return buffer;
}

#ifdef SNS_USES_ISLAND  /* for uImage on ADSP */
extern sns_mem_heap_type sns_uheap;
extern mem_magic_number_struct sns_uheap_magic;
extern uint32 sns_uheap_magic_num[SNS_MAX_HEAP_INIT];
extern uint16 sns_uheap_magic_num_idx_array[SNS_MAX_HEAP_INIT];
extern uint8  sns_uheap_mem[SNS_UIMAGE_HEAP_SIZE];

#define  SNS_OS_IS_UHEAP_PTR(ptr) (((uint8_t *)ptr) > ((uint8_t *)sns_uheap_mem) && ((uint8_t *)ptr) < (((uint8_t *)sns_uheap_mem) + sizeof(sns_uheap_mem)))

void *sns_memmgr_int_u_malloc(uint8_t module, uint32_t size);
int sns_memmgr_int_u_free(void *ptr);
void * sns_memmgr_int_any_malloc(uint8_t module, uint32_t size);
void sns_memmgr_int_any_free(void *ptr);
void sns_memmgr_sensor_heap_int_any_free(void *ptr);
void sns_memmgr_free_spillover_buffer(void * ptr);
void sns_memmgr_free_sensor_heap_spillover_buffer(void * ptr);
void sns_memmgr_add_to_spillover_list(void *memPtr);

#define SNS_OS_U_FREE(p)        sns_memmgr_int_u_free(p)
#define SNS_OS_U_MALLOC(m, s)   sns_memmgr_int_u_malloc(m, s)
#define SNS_OS_ANY_FREE(p)      sns_memmgr_int_any_free(p)
#define SNS_OS_SENSOR_HEAP_ANY_FREE(p)      sns_memmgr_sensor_heap_int_any_free(p)
#define SNS_OS_ANY_MALLOC(m, s) sns_memmgr_int_any_malloc(m, s)

#else /* SNS_USES_ISLAND not defined */
#define SNS_OS_U_MALLOC(module,size)    SNS_OS_MALLOC(module, size)
#define SNS_OS_ANY_MALLOC(module,size)  SNS_OS_MALLOC(module, size)
#define SNS_OS_U_FREE(block)            SNS_OS_FREE(block)
#define SNS_OS_ANY_FREE(block)          SNS_OS_FREE(block)
#define SNS_OS_SENSOR_HEAP_ANY_FREE(block)          SNS_OS_SENSOR_HEAP_FREE(block)
#define SNS_OS_IS_UHEAP_PTR(ptr)        (0)
#endif /* End SNS_USES_ISLAND */

#else /* neither USES_NATIVE_MALLOC nor QDSP6 is defined */

#define SNS_OS_MALLOC(module, size)    OI_Malloc(module, size)
#define SNS_OS_SENSOR_HEAP_MALLOC(module, size)    OI_Malloc(module, size)
#define SNS_OS_U_MALLOC(module, size)  OI_Malloc(module, size)
#define SNS_OS_ANY_MALLOC(module, size)  OI_Malloc(module, size)
#define SNS_OS_FREE(block)              _OI_FreeIf(block)
#define SNS_OS_U_FREE(block)            _OI_FreeIf(block)
#define SNS_OS_ANY_FREE(block)          _OI_FreeIf(block)
#define SNS_OS_SENSOR_HEAP_ANY_FREE(block)          _OI_FreeIf(block)
#define SNS_OS_IS_UHEAP_PTR(ptr)        (0)
#define SNS_OS_CHGALLOC(new_mod,block) OI_Realloc(new_mod,block)

#endif /* USE_NATIVE_MALLOC */

/*=====================================================================
                          FUNCTIONS
=======================================================================*/

/*===========================================================================

  FUNCTION:   sns_heap_init

  ===========================================================================*/
/*!
  @brief Initializes separate heap for Sensors

  This function will create a separate Heap for Sensors.

  'sns_heap_id' is heap ID for memory allocations from Sensors code.

*/
/*=========================================================================*/
sns_err_code_e sns_heap_init(void);


/*===========================================================================

  FUNCTION:   sns_heap_destroy

  ===========================================================================*/
/*!
    Destorys the Sensors heap manager created by sns_heap_init
*/
/*=========================================================================*/
sns_err_code_e sns_heap_destroy(void);

/*===========================================================================

  FUNCTION:   sns_memmgr_lowmem_cb_register

  ===========================================================================*/
/*!
  @brief Registers a callback to be called in out of memory conditions

  The implementation of this callback should free any unneeded or "low priority"
  memory.

  @param[i] cb: The callback function
  @param[i] heapType: Heap the callback function wants to register on

  @return
  SNS_SUCCESS if the callback is successfully registered

*/
/*=========================================================================*/
sns_err_code_e
sns_memmgr_lowmem_cb_register( sns_memmgr_lowmem_cb_t cb, sns_heap_type heapType );

#endif /* SNS_MEMMGR_H */
