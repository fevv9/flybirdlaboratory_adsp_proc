/***********************************************************************
 * rfs_osal.h
 *
 * OS abstraction layer.
 * Copyright (C) 2014 QUALCOMM Technologies, Inc.
 *
 * Using this file allows us to compile RFS API code without any sort of
 * dependency on underlying operating system.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/storage/rfs/src/rfs_osal.h#1 $ $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-04-04   dks   Featurize compilation
2014-01-27   dks   Create

===========================================================================*/

#ifndef __RFS_OSAL_H__
#define __RFS_OSAL_H__

#include "rfs_config_i.h"
#include "comdef.h"

#include <pthread.h>

typedef pthread_mutex_t rfs_osal_mutex_handle;

void rfs_osal_mutex_init (rfs_osal_mutex_handle *lock_handle);
void rfs_osal_mutex_lock (rfs_osal_mutex_handle *lock_handle);
void rfs_osal_mutex_unlock (rfs_osal_mutex_handle *lock_handle);

#endif /* not __RFS_OSAL_H__ */
