#include "common.h"
#include "comms.h"
#include <wiringPi.h>
#include "drivetrain.h"

int main() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");
	
	wiringPiSetup();

	drive_init();

	init_comms();
	start_comms();

	while(1) {
		float rt = (-last_pack.js_state.axis_right_trigger + 1.0) /2.0;
		float lt = (-last_pack.js_state.axis_left_trigger + 1.0) /2.0;
		float ljx = -last_pack.js_state.axis_left_x;
		drive_update(rt-lt-ljx, rt-lt+ljx);
	}

	slog(400, SLOG_INFO, "Exiting");

	drive_close();
	close_comms();
}
