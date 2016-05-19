/*
==============================================================================

FILE:         HALclkGCC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GCC clocks.

   List of clock domains:
   -HAL_clk_mGCCXOClkDomain
   -HAL_clk_mGCCSLEEPCLKClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/src/gcc/HALclkGCC.c#1 $

when          who     what, where, why
--------      ---     ----------------------------------------------------------- 
10/31/2012            Auto-generated.

==============================================================================
            Copyright (c) 2012 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup1_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP1_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP1_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp1_qup2_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP2_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP2_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp1_qup3_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP3_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP3_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp1_qup4_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP4_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP4_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp1_qup5_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP5_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP5_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP5_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp1_qup6_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP6_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP6_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup1_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP1_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP1_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup2_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP2_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP2_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup3_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP3_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP3_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup4_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP4_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP4_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup5_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP5_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP5_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP5_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_blsp2_qup6_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP6_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP6_I2C_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
#if 0
  {
    /* .szClockName      = */ "gcc_pdm_xo4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PDM_XO4_CBCR), HWIO_OFFS(GCC_PDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PDM_XO4_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_rpm_timer_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_TIMER_CBCR), HWIO_OFFS(GCC_RPM_MISC), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_TIMER_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_spdm_ff_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_FF_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_FF_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_XO_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_xo_div4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_XO_DIV4_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_XO_DIV4_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
};


/*
 * HAL_clk_mGCCXOClkDomain
 *
 * XO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCXOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GCC_XO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mXOClkDomainClks)/sizeof(HAL_clk_mXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


                                    
/*                           
 *  HAL_clk_mSLEEPCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLEEPCLKClkDomainClks[] =
{
#if 0
  {
    /* .szClockName      = */ "gcc_usb30_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB30_SLEEP_CBCR), HWIO_OFFS(GCC_USB_30_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB30_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb_hsic_io_cal_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_HSIC_IO_CAL_SLEEP_CBCR), HWIO_OFFS(GCC_USB_HS_HSIC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_HSIC_IO_CAL_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb_hs_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB_HS_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_USB_HS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB_HS_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb2a_phy_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB2A_PHY_SLEEP_CBCR), HWIO_OFFS(GCC_USB2A_PHY_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB2A_PHY_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_usb2b_phy_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB2B_PHY_SLEEP_CBCR), HWIO_OFFS(GCC_USB2B_PHY_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB2B_PHY_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc1_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc2_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC2_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_SDCC2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC2_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc3_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC3_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_SDCC3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC3_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_sdcc4_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC4_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_SDCC4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC4_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
  {
    /* .szClockName      = */ "gcc_blsp1_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_SLEEP_CBCR), HWIO_OFFS(GCC_BLSP1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP1_SLEEP_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_blsp2_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_SLEEP_CBCR), HWIO_OFFS(GCC_BLSP2_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BLSP2_SLEEP_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
  {
    /* .szClockName      = */ "gcc_bam_dma_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BAM_DMA_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_BAM_DMA_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, BAM_DMA_INACTIVITY_TIMERS_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BAM_DMA_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#if 0
  {
    /* .szClockName      = */ "gcc_tsif_inactivity_timers_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TSIF_INACTIVITY_TIMERS_CBCR), HWIO_OFFS(GCC_TSIF_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TSIF_INACTIVITY_TIMERS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_rpm_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_SLEEP_CBCR), HWIO_OFFS(GCC_RPM_MISC), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_im_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GCC_IM_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IM_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_bimc_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_SLEEP_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
  {
    /* .szClockName      = */ "gcc_ddr_dim_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DDR_DIM_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DDR_DIM_SLEEP_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL
  },
#endif
};


/*
 * HAL_clk_mGCCSLEEPCLKClkDomain
 *
 * SLEEP CLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSLEEPCLKClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GCC_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLEEPCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLEEPCLKClkDomainClks)/sizeof(HAL_clk_mSLEEPCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


