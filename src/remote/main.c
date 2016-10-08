#include "common.h"
#include "comms.h"
#include <wiringPi.h>
#include "drivetrain.h"
#include "command_manager.h"
#include <signal.h>
#include <unistd.h>

void close_arcs();

void sig_catch(int sig) {
	slog(400, SLOG_INFO, "SIGHUP, closing", sig);
	close_arcs();
}

int main() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");
	if (signal(SIGHUP, sig_catch) == SIG_ERR) {
		slog(100, SLOG_FATAL, "Can't catch SIGHUP");
		exit(EXIT_FAILURE);
	}

	wiringPiSetup();

	drive_init();

	start_comms();

	command_init();

	while (1) {
		command_update();
		struct pack_rtd p;
		p.pack_num = 1;
		p.test = 5.0;
		send_dash(p);
	}

	slog(400, SLOG_INFO, "Exiting");

	close_arcs();
}

void close_arcs() {
	drive_close();
	close_comms();
	exit(EXIT_SUCCESS);
}
