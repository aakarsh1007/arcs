/*
 * Comms recives packets from the dashboard.
 * Runs in a seperate thread.
 */

#ifndef COMMS_H
#define COMMS_H

#include "arcs_net.h"

void close_comms();

/*
 * Start comms thread, will update last_pack.
 */
void start_comms();

void send_dash(struct pack_rtd);

extern struct pack_dtr last_pack;

#endif
