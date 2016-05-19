#ifndef SMEM_TARGET_H
#define SMEM_TARGET_H

/*===========================================================================

                    Shared Memory Target Specific Header File


 Copyright (c) 2011-2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/mproc/smem/honeybadger/smem_target.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/18/14   bm      Initial version for Honeybadger family support
===========================================================================*/


/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "comdef.h"
#include "msmhwiobase.h"
#include "smem_hwio.h"
#include "HALhwio.h"
#include <stdint.h>

/*--------------------------------------------------------------------------
  Variable Declarations
---------------------------------------------------------------------------*/

/*===========================================================================
                           MACRO DEFINITIONS
===========================================================================*/

#if defined(IMAGE_RPM_PROC)
#define SMEM_RPM_PROC
#define SMEM_THIS_HOST SMEM_RPM
#elif defined(RIVA_BRINGUP_VIRTIO)
#define SMEM_RIVA_PROC
#define SMEM_THIS_HOST SMEM_WCN
#elif defined(IMAGE_MODEM_PROC)
#define SMEM_MODEM_PROC
#define SMEM_THIS_HOST SMEM_MODEM
#elif defined(IMAGE_APPS_PROC)
#define SMEM_APPS_PROC
#define SMEM_THIS_HOST SMEM_APPS
#elif defined(MPROC_LPASS_PROC)
#define SMEM_LPASS_PROC
#define SMEM_THIS_HOST SMEM_ADSP
#endif

/* -------------------------------------------------------------
   Shared memory access macros for Modem, Scorpion and QDSP6
   ------------------------------------------------------------- */
#define SMEM_MEMSET_SMEM( addr, val, size )     memset( addr, val, size )

/** Defines the spinlock identifier for each processor */
#if defined(SMEM_APPS_PROC)
#define SMEM_SPINLOCK_PID             ( 1 )
#elif defined(SMEM_MODEM_PROC)
#define SMEM_SPINLOCK_PID             ( 2 )
#elif defined(SMEM_LPASS_PROC)
#define SMEM_SPINLOCK_PID             ( 3 )
#elif defined(SMEM_RIVA_PROC)
#define SMEM_SPINLOCK_PID             ( 5 )
#elif defined(SMEM_RPM_PROC)
#define SMEM_SPINLOCK_PID             ( 6 )
#else
#error "SMEM_SPINLOCK_PID not defined"
#endif

/*-------------------------------------------------------------
   RPM Message RAM Memory physical/virt base address and size
 ------------------------------------------------------------- */
/* Honeybadger MSG RAM SIZE is 0x6000 */
#define SMEM_RPM_MSG_RAM_SIZE        0x6000

#ifdef SMEM_RPM_PROC
/** Defines the RPM Msg RAM starting virtual address 
 * +0x8000 as address in the msmhwiobase.h for RPM is
 * wrong */
#define SMEM_RPM_MSG_RAM_BASE        (RPM_MSG_RAM_BASE + 0x8000)

/** Defines the RPM Msg RAM starting physical address 
 * +0x8000 as address in the msmhwiobase.h for RPM is
 * wrong */
#define SMEM_RPM_MSG_RAM_BASE_PHYS   (RPM_MSG_RAM_BASE_PHYS + 0x8000)

#else  /** For all other peripherals */

/** Different macro names are being used in msmhwiobase.h on different
 *  procs to export RPM MSG RAM's base/size info */

/** Defines the RPM Msg RAM starting virtual address */
#define SMEM_RPM_MSG_RAM_BASE        RPM_SS_MSG_RAM_START_ADDRESS_BASE

/** Defines the RPM Msg RAM starting physical address */
#define SMEM_RPM_MSG_RAM_BASE_PHYS   RPM_SS_MSG_RAM_START_ADDRESS_BASE_PHYS

#endif

/** Defines invalid address */
#define SMEM_INVALID_ADDR               ((void *)(-1))

/** Mask for smallest possible page mapping size. */
#define SMEM_PAGE_ALIGN_MASK            0x00000FFF

/* Index of the TCSR_TZ_WONCE_n register where the address of the SMEM target
 * info will be saved by SBL. */
#define SMEM_TARG_INFO_REG_BASE_IDX     0

/* Bear family and beyond
 *           : SMEM Base Address + SMEM Size - SMEM_TOC_SIZE + 
 *              sizeof(smem_toc_type) + 
*              (sizeof(smem_toc_entry_type) * toc->num_entries)
 */

#define SMEM_TARG_INFO_ADDR             \
  (uintptr_t)(HWIO_INI(TCSR_TZ_WONCE_n, SMEM_TARG_INFO_REG_BASE_IDX) | \
    (((uint64)HWIO_INI(TCSR_TZ_WONCE_n, SMEM_TARG_INFO_REG_BASE_IDX+1)) << 32))

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================
  FUNCTION  spin_lock_internal
===========================================================================*/
/**
  Acquires spinlock by writing a non-zero value to the hardware mutex.
 
  Mutex characteristics:
   - Each Mutex has a separate read/write Mutex-register
   - Each Mutex-register can hold an integer value
   - '0' value = Mutex is free/unlocked
   - Non-zero value = Mutex is locked
 
  Locking the Mutex:
   - If Mutex is unlocked and PID is written, then the mutex is locked
   - If Mutex is locked and PID is written, then mutex register is not updated and
     the mutex remains locked
 
  A more detailed description can be found in System FPB (80-VR139-1A Rev. A)
  documentation.

  @param[in] lock      Spinlock id.

  @return
  None

  @dependencies 
  None.

  @sideeffects
  Locks the hardware mutex.
*/
/*==========================================================================*/
void spin_lock_internal( uint32 lock );

/*===========================================================================
  FUNCTION  spin_unlock_internal
===========================================================================*/
/**
  Releases spinlock by writing zero to the hardware mutex.
 
  Mutex characteristics:
   - Each Mutex has a separate read/write Mutex-register
   - Each Mutex-register can hold an integer value
   - '0' value = Mutex is free/unlocked
   - Non-zero value = Mutex is locked
 
  Locking the Mutex:
   - If '0' is written, then mutex register is updated and the mutex is
     unlocked
 
  A more detailed description can be found in System FPB (80-VR139-1A Rev. A)
  documentation.

  @param[in] lock      Spinlock id.

  @return
  None

  @dependencies 
  None.

  @sideeffects
  Unlocks the hardware mutex.
*/
/*==========================================================================*/
void spin_unlock_internal( uint32 lock );

/*===========================================================================
  FUNCTION  spin_lock_get
===========================================================================*/
/**
  This function retrieves the HW mutex value of the specified lock.
 
  Mutex characteristics:
   - Each Mutex has a separate read/write Mutex-register
   - Each Mutex-register can hold an integer value
   - '0' value = Mutex is free/unlocked
   - Non-zero value = Mutex is locked
 
  A more detailed description can be found in System FPB (80-VR139-1A Rev. A)
  documentation.

  @param[in] lock      Spinlock id.

  @return
  None

  @dependencies 
  None.

  @sideeffects
  None.
*/
/*==========================================================================*/
uint32 spin_lock_get( uint32 lock );

/*===========================================================================
  FUNCTION  spin_lock_internal_asm
===========================================================================*/
/**
  Acquires spinlock by performing an exclusive memory operation on the lock 
  location in shared memory.
 
  @param[in] lock      Spinlock id.

  @return
  None

  @dependencies 
  None.
*/
/*==========================================================================*/
void spin_lock_internal_asm( uint32 lock );

/*===========================================================================
  FUNCTION  spin_unlock_internal_asm
===========================================================================*/
/**
  Releases spinlock by writing 0 to the lock location in shared memory.
  
  @param[in] lock      Spinlock id.

  @return
  None

  @dependencies 
  None.
*/
/*==========================================================================*/
void spin_unlock_internal_asm( uint32 lock );

/*===========================================================================
  FUNCTION  spin_lock_get_asm
===========================================================================*/
/**
  This function retrieves the value of the specified lock.

  @param[in] lock      Spinlock id.

  @return
  Returns the value at the specified lock location.

  @dependencies 
  None.
*/
/*==========================================================================*/
uint32 spin_lock_get_asm( uint32 lock );

#endif /* SMEM_TARGET_H */
