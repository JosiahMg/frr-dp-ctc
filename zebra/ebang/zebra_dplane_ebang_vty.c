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
#include "zebra/ebang/zebra_dplane_ebang.h"

#define ZD_STR "Zebra dataplane information\n"
#define ZD_EBANG_STR "EBANG offload information\n"


#ifndef VTYSH_EXTRACT_PL
// #include "zebra/ebang/zebra_dplane_ebang_vty_clippy.c"
#endif


DEFUN (zd_ebang_show_interfaces, zd_ebang_show_interfaces_cmd,
       "show dplane ebang interfaces",
       SHOW_STR ZD_STR ZD_EBANG_STR "show centec interface\n")
{
	zd_ebang_ifc_show(vty);
	return CMD_SUCCESS;
}


void zd_ebang_vty_init(void)
{
       printf("%s\n", "--------------------- zd ebang vty init ---------------------");
	install_element(VIEW_NODE, &zd_ebang_show_interfaces_cmd);
}
