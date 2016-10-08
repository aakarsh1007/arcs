#include "common.h"
#include "comms.h"
#include "drivetrain.h"
#include "tank.h"
#include "timing.h"

void tank_init() { drive_update(0, 0); }

void tank_update() {
	int64_t s_time = microtime();
	drive_update(last_pack.js_state.axis_left_y,
				 last_pack.js_state.axis_right_y);
	int64_t e_time = microtime();

	int64_t diff_time = e_time - s_time;
	diff_time /= 1000;
	if (diff_time > 500)
		slog(400, SLOG_INFO, "Long drive update %d", diff_time);
}
