// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Zebra dataplane plugin for DPDK based hw offload
 *
 * Copyright (C) 2021 Nvidia
 * Donald Sharp
 */
#include "config.h" /* Include this explicitly */
#include <zebra.h>
#include "command.h"
#include "zebra/ctc/zebra_dplane_ctc.h"

#define ZD_STR "Zebra dataplane information\n"
#define ZD_CTC_STR "CTC offload information\n"


#ifndef VTYSH_EXTRACT_PL
#include "zebra/ctc/zebra_dplane_ctc_vty_clippy.c"
#endif


DEFPY (zd_ctc_show_interfaces, zd_ctc_show_interfaces_cmd,
       "show dplane ctc interface",
       SHOW_STR ZD_STR ZD_CTC_STR "show centec interface\n")
{
	zd_ctc_ifc_show(vty);
	return CMD_SUCCESS;
}


void zd_ctc_vty_init(void)
{
	install_element(VIEW_NODE, &zd_ctc_show_interfaces_cmd);
}
