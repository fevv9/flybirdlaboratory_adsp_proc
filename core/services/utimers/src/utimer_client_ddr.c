/*=============================================================================

                UTimer_Client_DDR.c

GENERAL DESCRIPTION
      UTimer Client Process Code that goes to main image

EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

      Copyright (c) 2009 - 2014
      by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/services/utimers/src/utimer_client_ddr.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
6/9/14   ab      Add file that provides MultiPD changes
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "err.h"
#include "utimer.h"
#include "utimer_qdi_v.h"
#include "utimer_client_v.h"
//Enable this header once qurt supports signal2 in uimage
//#include "qurt_signal2.h"

/*****************************************************************************/
/*                          DATA DECLARATIONS                                */
/*****************************************************************************/

/* Current Process idx */
extern int utimer_client_pid;

/* Qdi Timer Client Handle to communicate with Guest os layer */
extern int utimer_client_qdi_handle;


/*==============================================================================

                     CALLBACK IMPLEMENTATION

=============================================================================*/


/*===========================================================================
DESCRIPTION
   Creates worker thread that waits inside Guest OS for callback details.
   Once the thread gets callback details it will either signal or call the
   callback depending on the callback type.
===========================================================================*/
extern void UTimerCallbackHandler(void *parameter);

extern uint8 utimer_client_stack_arr[UTIMER_CLIENT_STACK_SIZE];
extern qurt_thread_t      utimer_worker_thread_id;
   
int uCreateWorkerThread(unsigned int process_idx)
{
   int ret_value = 0;
   qurt_thread_attr_t tattr;
   unsigned int stackbase;
   char thread_name[20];
  
   snprintf(thread_name, sizeof(thread_name), "UTIMER_CLIENT_%u", process_idx);
   stackbase = (unsigned int)&utimer_client_stack_arr;
   qurt_thread_attr_init (&tattr);
   qurt_thread_attr_set_stack_size (&tattr, (UTIMER_CLIENT_STACK_SIZE -8));
   qurt_thread_attr_set_stack_addr (&tattr, (void*)((stackbase + 7) & (~7)) );
   qurt_thread_attr_set_priority (&tattr, UTIMER_CLIENT_PRI-1);
   qurt_thread_attr_set_tcb_partition(&tattr, 1); // This task should reside in TCM Memory
   qurt_thread_attr_set_name(&tattr, thread_name);
   ret_value =  qurt_thread_create(&utimer_worker_thread_id, &tattr, UTimerCallbackHandler, NULL);
  
   return ret_value;
}  /* uCreateWorkerThread() */


#ifdef FEATURE_UTIMER_CLIENT_TEST
/*===========================================================================
DESCRIPTION
   Creates Test Thread for testing Qurt timer apis and their delays
===========================================================================*/
extern uint8 utimer_client_test_stack_arr[UTIMER_CLIENT_TEST_STACK_SIZE];

extern qurt_thread_t      utimer_test_id;

/* Defined in timer_client_test.c */
extern void utimer_client_test
(
  void *parameter
);

int UtimerCreateTestThread(void)
{
   int ret_value = 0;
   qurt_thread_attr_t tattr;
   
   unsigned int stackbase;
  
   stackbase = (unsigned int)&utimer_client_test_stack_arr;
   qurt_thread_attr_init (&tattr);
   qurt_thread_attr_set_stack_size (&tattr, (UTIMER_CLIENT_TEST_STACK_SIZE -8));
   qurt_thread_attr_set_stack_addr (&tattr, (void*)((stackbase +7) &(~7)) );
   qurt_thread_attr_set_tcb_partition(&tattr, 1); // This task should reside in TCM Memory
   qurt_thread_attr_set_priority (&tattr, UTIMER_TEST_PRI-1);
   qurt_thread_attr_set_name(&tattr,"UTIMER_TEST_CLIENT");
   ret_value =  qurt_thread_create(&utimer_test_id, &tattr, utimer_client_test, NULL);
  
   return ret_value;
}  /* UtimerCreateTestThread() */
#endif /* #ifdef FEATURE_UTIMER_CLIENT_TEST */

/*===========================================================================

FUNCTION    UTIMER_CLIENT_INIT

DESCRIPTION
  Initialize the UTimer Client service.

DEPENDENCIES
  None.

RETURN VALUE
  
SIDE EFFECTS
  None

===========================================================================*/
void utimer_client_init(void) 
{
   //unsigned int ret;
 
   utimer_client_pid = qurt_getpid();
    
   utimer_client_qdi_handle = qurt_qdi_open(UTIMER_DRIVER_NAME);
   if(utimer_client_qdi_handle < 0)
   {
      //printf("utimer_client_init: qdi_open failed");
      ERR_FATAL("utimer_client_init :qdi_open failed\n", 0, 0, 0);
      return;
   }
   
   /* 0 is considered as Guest OS Process ID */
   if(utimer_client_pid != 0)
   {
      if(uCreateWorkerThread(utimer_client_pid) != 0)
      {
          //printf("utimer_client_init: uCreateWorkerThread failed\n");
          ERR_FATAL("utimer_client_init: uCreateWorkerThread failed\n", 0, 0, 0);
          return;
      }
   }
 
  /* For testing only */
#ifdef FEATURE_UTIMER_CLIENT_TEST    
   if(UtimerCreateTestThread() != 0)
   {
       //printf("utimer_client_init : UtimerCreateTestThread failed\n");
       return;
   }
#endif /* #ifdef FEATURE_UTIMER_CLIENT_TEST */

   return;
}  /* utimer_client_init */