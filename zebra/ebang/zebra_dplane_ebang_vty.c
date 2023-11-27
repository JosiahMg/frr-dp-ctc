// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Zebra dataplane plugin for DPDK based hw offload
 *
 * Copyright (C) 2021 Nvidia
 * Donald Sharp
 */
#include <zebra.h>
#include "command.h"
#include "lib/json.h"
#include "zebra/ebang/zebra_dplane_ebang.h"

#define ZD_STR "Zebra dataplane information\n"
#define ZD_EBANG_STR "EBANG offload information\n"


DEFPY (zd_ebang_show_interfaces,
       zd_ebang_show_interfaces_cmd,
       "show dplane ebang interfaces",
       SHOW_STR
       ZD_STR
       ZD_EBANG_STR
       "show interface\n"
       "Centec interfaces\n")
{
	zd_ebang_ifc_show(vty);
	return CMD_SUCCESS;
}


void zd_ebang_vty_init(void)
{
	install_element(VIEW_NODE, &zd_ebang_show_interfaces_cmd);
}
