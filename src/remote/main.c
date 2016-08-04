#include "common.h"
#include "comms.h"

int main() {
	slog_init("arcs", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-remote");

	init_comms();

	while(1)
		update_comms();

	slog(400, SLOG_INFO, "Exiting");
	close_comms();
}
