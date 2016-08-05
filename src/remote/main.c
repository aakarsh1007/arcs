#include "common.h"
#include "comms.h"
#include <wiringPi.h>
#include "drivetrain.h"
#include <math.h>

int main() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");
	
	wiringPiSetup();

	drive_init();

	start_comms();

	while(1) {
		float l, r;
		float fw = last_pack.js_state.axis_right_y;
		float dir = last_pack.js_state.axis_left_x;

		l = fw + dir;
		r = fw - dir;

		drive_update(l, r);
	}

	slog(400, SLOG_INFO, "Exiting");

	drive_close();
	close_comms();
}
