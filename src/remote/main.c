#include "common.h"
#include "comms.h"
#include <wiringPi.h>
#include "drivetrain.h"
#include "command_manager.h"

int main() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");
	
	wiringPiSetup();

	drive_init();

	start_comms();

	command_init();

	while(1) {
		command_update();
	}

	slog(400, SLOG_INFO, "Exiting");

	drive_close();
	close_comms();
}
