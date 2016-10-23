#pragma once

#include "arcs_net.h"
#include <pthread.h>

void init_comms();

void close_comms();

extern struct lidar_data lidar_data;

extern pthread_mutex_t comms_lock;
