// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Zebra dataplane plugin for CTC based hw offload
 *
 * Copyright (C) 2021 Nvidia
 * Anuradha Karuppiah
 */

#ifndef _ZEBRA_DPLANE_CTC_H
#define _ZEBRA_DPLANE_CTC_H

#include "sal.h"        /* centec sdk */
#include "api/include/ctc_api.h"
#include "api/include/ctcs_api.h"
#include "ctc_api.h"	/* centec sdk */
#include <zebra.h>


extern void zd_ctc_vty_init(void);
extern void zd_ctc_ifc_show(struct vty *vty);

/* centec sdk init */
extern int32_t userinit(uint8_t ctc_shell_mode, uint8_t ctcs_api_en, void* p_init_config);
extern int32_t sys_usw_mac_show_port_maclink(uint8_t lchip);

extern struct zebra_privs_t zserv_privs;
#endif
