#include "common.h"
#include "comms.h"
#include "drivetrain.h"
#include "tank.h"

void tank_init() {
	drive_update(0, 0);
}

void tank_update() {
//	slog(400, SLOG_INFO, "L: %f R: %f", last_pack.js_state.axis_left_y, last_pack.js_state.axis_right_y);
	drive_update(last_pack.js_state.axis_left_y, last_pack.js_state.axis_right_y);
}
