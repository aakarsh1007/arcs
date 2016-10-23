#pragma once

#include <pthread.h>
#include "arcs_net.h"

void init_lidar();

void close_lidar();

extern pthread_mutex_t lidar_lock;

extern struct lidar_data lidar_data;
