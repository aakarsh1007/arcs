#include "common.h"
#include "drivetrain.h"
#include "comms.h"

void disabled_init() { drive_update(0, 0); }

void disabled_update() { drive_update(0, 0); }
