/*
 * The command manager starts and updates commands.
 */
#pragma once

/*
 * Initialize command manager.
 * Sets the started flags to false.
 */
void command_init();

/*
 * Updates the current command based on the mode.
 * Will init the command if it has not been started yet.
 */
void command_update();
