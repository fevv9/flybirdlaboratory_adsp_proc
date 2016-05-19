#ifndef PD_MON_RESTART_H
#define PD_MON_RESTART_H
/** vi: tw=128 ts=3 sw=3 et
@file dog_hal.c
@brief This file contains the API details for the Dog Services, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/api/pd_mon_restart.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "comdef.h"

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

FUNCTIONS
  pd_mon_restart_dalcfg_check

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/**
Initialize PD MON Restart Dal Config and check if PD restart is enabled.
@return
0 - PD restart Disabled.
1 - PD restart Enabled

*/

uint32 pd_mon_restart_dalcfg_check(void);

#endif /* PD_MON_RESTART */
