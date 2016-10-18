#pragma once
#include "arcs_net.h"

struct iface_args {
	char *js;
	struct js_state jsstat;
	char *remote;
	comm_mode_t mode;
	bool use_viewer;
	char *viewer_ip;
};

/*
 * Updates the interface based on the properties passed to it.
 */
void redraw(struct iface_args *props);
