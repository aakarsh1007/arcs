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
	render_mode = false;
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	int stat = curs_set(0);
#ifdef DEBUG
	if (stat == ERR) {
		slog(200, SLOG_ERROR,
			 "This terminal does not appear to support ncurses control");
	}
#endif
	if (has_colors() == FALSE) {
		slog(100, SLOG_FATAL, "Terminal does not support color");
		screen_close();
		exit(EXIT_FAILURE);
	}
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
}

void screen_close() {
	nocbreak();
	echo();
	endwin();
}

void screen_start_render() {
#ifdef DEBUG
	if (render_mode)
		slog(300, SLOG_WARN, "Called %s dring render mode", __FUNCTION__);
#endif
	render_mode = true;
	clear();
	draw_logo();
}

void screen_end_render() {
#ifdef DEBUG
	if (!render_mode)
		slog(300, SLOG_WARN, "Call %s outside of render mode", __FUNCTION__);
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
	if (x < 0 || y < 0)
		slog(300, SLOG_WARN, "Negative location passed to %s", __FUNCTION__);
#endif
	mvprintw(y + PROPS_Y, x + PROPS_X, str);
}

void screen_print_header(int x, int y, char *str) {
#ifdef DEBUG
	if (x < 0 || y < 0)
		slog(300, SLOG_WARN, "Negative location passed to %s", __FUNCTION__);
#endif
	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(y + PROPS_Y, x + PROPS_X, str);
	attroff(COLOR_PAIR(2) | A_BOLD);
}
