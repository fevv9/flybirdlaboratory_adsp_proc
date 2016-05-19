#ifndef __DOG_HAL_8974_H__
#define __DOG_HAL_8974_H__
/*
===========================================================================
*/
/**
  @file dog_hal_8974.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6SS_CSR

  'Include' filters applied: WDOG[LPASS_QDSP6SS_CSR]
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2014 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hal_8974_lpass.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/**
Instructions to Generate Content:

1. Browser to http://go/ipcat
2. Select to Generate HWIO
3. File Name : dog_hal_hwio.h
4. Filter for Appropriate Register Blocks such as LPASS_QDSP_CSR, MSS_QDSP6SS_CSR, QDSP6SS_CSR, ... Select Generate Offsets and Include Field Values
5. Select Generate
6. Copy Results to Clipboard
7. Paste to this File Between "Book Ends"
8. Save
*/

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_CSR_REG_BASE                                          (LPASS_BASE      + 0x00280000)
#define LPASS_QDSP6SS_CSR_REG_BASE_OFFS                                     0x00280000

#define HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR                                  (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OFFS                                  (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR                                    (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OFFS                                    (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK                                           0x7
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR                                 (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_OFFS                                 (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK                                 0xf81fffff
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_BMSK               0x80000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_SHFT                     0x1f
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_BMSK           0x40000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_SHFT                 0x1e
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_BMSK           0x20000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_SHFT                 0x1d
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_BMSK            0x10000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_SHFT                  0x1c
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_BMSK            0x8000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_SHFT                 0x1b
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_BMSK                        0x1ffffe
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_SHFT                             0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                    0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                    0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK                                 0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK                            0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK                                 0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK                            0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR                               (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OFFS                               (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002014)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK                                  0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_BMSK                             0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR                              (LPASS_QDSP6SS_CSR_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OFFS                              (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_RMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR                                   (LPASS_QDSP6SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OFFS                                   (LPASS_QDSP6SS_CSR_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK                                     0x1fffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_TEST_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_BMSK                         0x100000
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_SHFT                             0x14
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_BMSK                           0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_SHFT                               0x0


#endif /* __DOG_HAL_8974_H__ */
