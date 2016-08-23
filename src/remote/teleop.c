#include "common.h"
#include "comms.h"
#include "drivetrain.h"
#include <math.h>
#include "teleop.h"

void teleop_init() {
	drive_update(0, 0);
}

void teleop_update() {
	float l, r;
	float fw = last_pack.js_state.axis_right_y;
	float dir = last_pack.js_state.axis_left_x;

	l = fw + dir;
	r = fw - dir;

	float max = fabs(l) > fabs(r) ? l : r;
	max = fabs(max);

	if(max > 1) {
		float div = 1 / max;
		l *= div;
		r *= div;
	}

	drive_update(l, r);
}
