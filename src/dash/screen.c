#include "common.h"
#include <ncurses.h>
#include <string.h>
#include "screen.h"

#define LOGO_X 1
#define LOGO_Y 1
#define PROPS_X 1
#define PROPS_Y 8

#ifdef DEBUG
bool render_mode;
#endif

void draw_logo();

void screen_init() {
#ifdef DEBUG
	logm("Initializting screen\n");
#endif
	render_mode = false;
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	int stat = curs_set(0);
#ifdef DEBUG
	if (stat == ERR) {
		logm("This terminal does not support setting cursor visibility\n");
	}
#endif
	if (has_colors() == FALSE) {
		logm("Color not supported, exiting.\n");
		screen_close();
		exit(EXIT_FAILURE);
	}
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
#ifdef DEBUG
	logm("Screen created\n");
#endif
}

void screen_close() {
	nocbreak();
	echo();
	endwin();
}

void screen_start_render() {
#ifdef DEBUG
	if(render_mode)
		logm("Called screen_start_render during render mode\n");
#endif
	render_mode = true;
	clear();
	draw_logo();
}

void screen_end_render() {
#ifdef DEBUG
	if(!render_mode)
		logm("Called screen_end_render when not in render mode\n");
#endif
	render_mode = false;
	refresh();
}

void draw_logo() {
	attron(COLOR_PAIR(1));
	mvprintw(0 + LOGO_Y, 0 + LOGO_X, "    /\\                 ");
	mvprintw(1 + LOGO_Y, 0 + LOGO_X, "   /  \\   _ __ ___ ___ ");
	mvprintw(2 + LOGO_Y, 0 + LOGO_X, "  / /\\ \\ | '__/ __/ __|");
	mvprintw(3 + LOGO_Y, 0 + LOGO_X, " / ____ \\| | | (__\\__ \\");
	mvprintw(4 + LOGO_Y, 0 + LOGO_X, "/_/    \\_\\_|  \\___|___/");
	attroff(COLOR_PAIR(1));
}

void screen_print(int x, int y, char *str) {
#ifdef DEBUG
	if(x < 0 || y < 0)
		logm("Negative location passed to screen_print\n");
#endif
	mvprintw(y + PROPS_Y, x + PROPS_X, str);
}

void screen_print_header(int x, int y, char *str) {
#ifdef DEBUG
	if(x < 0 || y < 0)
		logm("Negative location passed to screen_print_header\n");
#endif
	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(y + PROPS_Y, x + PROPS_X, str);
	attroff(COLOR_PAIR(2) | A_BOLD);
}
