/*
 * Comms recives packets from the dashboard.
 * Runs in a seperate thread.
 */
#pragma once

#include "arcs_net.h"

void close_comms();

/*
 * Start comms thread, will update last_pack.
 */
void start_comms();

/*
 * Sends a pack_viewer struct to the viewer.
 */
void send_viewer(struct pack_viewer);

extern struct pack_dtr last_pack;
