#ifndef COMMS_H
#define COMMS_H

#include "arcs_net.h"

void init_comms();

void close_comms();

// DTR is for dash to remote
#define DTR_PORT 30000

#endif
