// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Zebra dataplane plugin for DPDK based hw offload
 *
 * Copyright (C) 2021 Nvidia
 * Anuradha Karuppiah
 */

#ifndef _ZEBRA_DPLANE_EBANG_H
#define _ZEBRA_DPLANE_EBANG_H

#include <zebra.h>

extern void zd_ebang_vty_init(void);
extern void zd_ebang_ifc_show(struct vty *vty);
#endif
