#include "common.h"
#include "comms.h"
#include "teleop.h"
#include "disabled.h"
#include "tank.h"
#include "leds.h"

uint32_t started_flags;

bool has_started(comm_mode_t val) { return (started_flags >> val) & 0x1; }

void start_mode(comm_mode_t val) {
	started_flags = started_flags | (0x1 << val);
}

void command_init() { started_flags = 0; }

void command_update() {
	comm_mode_t mode = last_pack.mode;
	if (has_started(mode)) {
		slog(400, SLOG_INFO, "Starting mode %d", (int)mode);
		if (mode == MODE_DISABLED)
			disabled_init();
		else if (mode == MODE_TELEOP)
			teleop_init();
		else if (mode == MODE_TANK)
			tank_init();
		else {
			slog(300, SLOG_ERROR, "Trying to start non existant mode %d",
				 (int)mode);
		}
	}

	if (mode == MODE_DISABLED) {
		status_led_disabled();
		disabled_update();
	}
	if (mode == MODE_TELEOP) {
		status_led_teleop();
		teleop_update();
	}
	if (mode == MODE_TANK) {
		status_led_teleop();
		tank_update();
	}
}
