#pragma once
#include "arcs_net.h"

/*
 * Sets up socket to remote.
 */
void connect_comms();

/*
 * Close socket.
 */
void disconnect_comms();

/*
 * Sends a packet to the remote with the js_state.
 * Needs to be called after connect_comms().
 */
void update_comms(struct js_state, comm_mode_t, bool use_viewer,
				  char *viewer_ip);

/*
 * Returns string with remote IP address.
 */
char *addrstr();

extern comm_mode_t mode;
