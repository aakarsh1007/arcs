#pragma once

/*
 * Captures the screen and setup ncurses settings.
 * Also configures ncurses for keyboard input.
 */
void screen_init();

/*
 * Closes the screen, make sure to call before exit.
 */
void screen_close();

/*
 * Start render mode.
 * Should only be called outside of render mode.
 */
void screen_start_render();

/*
 * Ends render mode, draws to screen.
 * Should only be called inside render mode.
 */
void screen_end_render();

/*
 * Prints a string to screen at point x, y.
 * Automaticly shifts location so (0, 0) should be start.
 */
void screen_print(int, int, char *);

/*
 * Prints string at location, with header format.
 */
void screen_print_header(int, int, char *);
