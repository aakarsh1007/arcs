#pragma once

struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t number;
};

#include "arcs_net.h"

/*
 * Starts a thread to get joystick input.
 * All data is put into js_state.
 */
bool js_connect(char *path);

extern pthread_mutex_t js_lock;

/*
 * Returns a pointer to the js_state struct with all input data.
 */
struct js_state get_js_state();
