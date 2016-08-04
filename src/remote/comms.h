#ifndef COMMS_H
#define COMMS_H

#include "arcs_net.h"

void init_comms();

void close_comms();

void update_comms();

void start_comms();

extern struct pack last_pack;

#endif
