#include "common.h"
#include "comms.h"
#include "drivetrain.h"
#include <math.h>
#include "teleop.h"

void teleop_init() { drive_update(0, 0); }

void teleop_update() {
	// http://home.kendra.com/mauser/Joystick.html

	float y = last_pack.js_state.axis_right_y * 100;
	float x = last_pack.js_state.axis_left_x * 100;

	x = -x;
	float v = (100 - abs(x)) * (y / 100) + y;
	float w = (100 - abs(y)) * (x / 100) + x;
	float r = (v + w) / 2;
	float l = (v - w) / 2;

	r /= 100;
	l /= 100;

	drive_update(l, r);
}
