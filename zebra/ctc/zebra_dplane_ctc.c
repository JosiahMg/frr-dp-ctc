// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Sample plugin for the FRR zebra dataplane.
 *
 * Copyright (c) 2019 Volta Networks, Inc.
 */

/*
 * Should be possible to build this plugin using this sort of command:
 *
 *    gcc -I ~/work/frr/ -I ~/work/frr/lib -I ~/work/frr/zebra \
 *        -g -O0 -o sample_plugin.so -shared -fPIC sample_plugin.c
 *
 * where 'frr' is a configured and built frr sandbox.
 *
 * Run zebra with '-M /path/to/sample_plugin.so' to load the module.
 */
#include "config.h" /* Include this explicitly */
#include "lib/zebra.h"
#include "lib/libfrr.h"
#include "zebra/zebra_dplane.h"
#include "zebra/debug.h"
#include "zebra/ctc/zebra_dplane_ctc.h"

static const char *plugin_name = "zebra_dplane_ctc";

static struct zebra_dplane_provider *prov_p;

/* init sdk hardware */
int ctc_sdk_entry(void) 
{
	int32_t ret = 0;
	uint8_t ctc_shell_mode = 0;
	uint8_t ctcs_api_en = 0;
	printf("%s\n", "----------- ctc sdk entry init begin -----------");
	ret = userinit(ctc_shell_mode, ctcs_api_en, NULL);
	printf("%s\n", "----------- ctc sdk entry init end -----------");
	return ret;
}


/* mh
	init vtysh cmd
*/
static int zd_ctc_init(void)
{
	zd_ctc_vty_init();
	return 0;
}


void zd_ctc_ifc_show(struct vty *vty)
{
	int32_t ret = 0;
	vty_out(vty, "%30s\n%30s\n", "Dataplane Centec Interface",
		"=======================");
	ret = sys_usw_mac_show_port_maclink(0);
    if (ret < 0)
    {
        vty_out(vty, "%30s\n", "port mac link error");
    }
	else
	{
		vty_out(vty, "%30s\n", "port mac link success");
	}

}


/*
 * Startup/init callback, called from the dataplane.
 */
static int zd_ctc_start(struct zebra_dplane_provider *prov)
{
	int ret = 0;
	/* init sdk hardware */
	ret = ctc_sdk_entry();
	ret = zd_ctc_init();
	/* init vty. */
	return ret;
}


/*
 * Shutdown/cleanup callback, called from the dataplane pthread.
 */
static int zd_ctc_fini(struct zebra_dplane_provider *prov, bool early)
{
	/* Nothing special to do. */
	return 0;
}

/*
 * Callback from the dataplane to process incoming work; this runs in the
 * dplane pthread.
 */
static int zd_ctc_process(struct zebra_dplane_provider *prov)
{
	int counter, limit;
	struct zebra_dplane_ctx *ctx;

	limit = dplane_provider_get_work_limit(prov_p);

	/* Respect the configured limit on the amount of work to do in
	 * any one call.
	 */
	for (counter = 0; counter < limit; counter++) {
		ctx = dplane_provider_dequeue_in_ctx(prov_p);
		if (!ctx)
			break;

		/* Just set 'success' status and return to the dataplane */
		dplane_ctx_set_status(ctx, ZEBRA_DPLANE_REQUEST_SUCCESS);
		dplane_provider_enqueue_out_ctx(prov_p, ctx);
	}

	return 0;
}

/*
 * Init entry point called during zebra startup. This is registered during
 * module init.
 */
static int zd_ctc_plugin_init(struct event_loop *tm)
{
	int ret;

	/* Note that we don't use or store the thread_master 'tm'. We
	 * don't use the zebra main pthread: our plugin code will run in
	 * the zebra dataplane pthread context.
	 */

	/* Register the plugin with the dataplane infrastructure. We
	 * register to be called before the kernel, and we register
	 * our init, process work, and shutdown callbacks.
	 */
	ret = dplane_provider_register(plugin_name, DPLANE_PRIO_PRE_KERNEL,
				       DPLANE_PROV_FLAGS_DEFAULT,
				       zd_ctc_start,
				       zd_ctc_process,
				       zd_ctc_fini,
				       NULL,
				       &prov_p);

	if (IS_ZEBRA_DEBUG_DPLANE)
		zlog_debug("sample plugin register => %d", ret);

	return 0;
}


/*
 * Base FRR loadable module info: basic info including module entry-point.
 */
static int zd_ctc_module_init(void)
{
	hook_register(frr_late_init, zd_ctc_plugin_init);
	return 0;
}

FRR_MODULE_SETUP(
	.name = "dplane_sample",
	.version = "0.0.1",
	.description = "Dataplane Sample Plugin",
	.init = zd_ctc_module_init,
);
