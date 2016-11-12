#include "common.h"
#include "comms.h"
#include <wiringPi.h>
#include "drivetrain.h"
#include "command_manager.h"
#include "lidar.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "leds.h"

int viewer_pack_num = 1;

void close_arcs();

void sig_catch(int sig) {
	slog(400, SLOG_INFO, "SIGHUP, closing", sig);
	close_arcs();
}

void init() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");
	if (signal(SIGHUP, sig_catch) == SIG_ERR) {
		slog(100, SLOG_FATAL, "Can't catch SIGHUP");
		exit(EXIT_FAILURE);
	}

	wiringPiSetup();
	init_leds();
	drive_init();
	init_lidar();
	start_comms();
	command_init();
}

int main() {
	init();

	while (1) {
		usleep(10000);

		command_update();
		update_comms_led();

		struct pack_viewer p;
		memcpy(&p.lidar_data, &lidar_data, sizeof(lidar_data));
		p.pack_num = viewer_pack_num++;
		send_viewer(p);
	}

	slog(400, SLOG_INFO, "Exiting");

	close_arcs();
}

void close_arcs() {
	drive_close();
	close_comms();
	close_lidar();
	close_leds();
	exit(EXIT_SUCCESS);
}
