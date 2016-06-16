#include "common.h"
#include <ncurses.h>
#include <string.h>
#include "screen.h"

#define LOGO_X 1
#define LOGO_Y 1
#define PROPS_X 1
#define PROPS_Y 8
#define PROPS_NAME_MAX_LEN 18
#define PROPS_VAL_MAX_LEN 18

void draw_logo();
void draw_props(lnk_list*);

void screen_init() {
#ifdef DEBUG
	logm("Initializting screen\n");
#endif
	initscr();
	cbreak();
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

void screen_render(lnk_list *list) {
	clear();
	draw_logo();
	draw_props(list);
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

void draw_props(lnk_list *list) {
	int32_t len = list_len(list);
	for (int32_t i = 0; i < len; i++) {
		struct dash_property *dp = list_get(list, i);
		if (strlen(dp->name) == 0)
			continue; //Spacer

		if (strlen(dp->name) > PROPS_NAME_MAX_LEN) {
			logm("Name %s larger than limit. Exiting\n",
					dp->name);
			screen_close();
			exit(EXIT_FAILURE);
		}
		if (strlen(dp->value) > PROPS_VAL_MAX_LEN) {
			logm("Value %s larger than limit. Exiting\n",
					dp->value);
			screen_close();
			exit(EXIT_FAILURE);
		}

		if (strlen(dp->value) == 0) {
			//Title, not property
			attron(A_BOLD|COLOR_PAIR(2));
			mvprintw(i + PROPS_Y, PROPS_X, dp->name);
			attroff(A_BOLD|COLOR_PAIR(2));
		} else {
			char tmp[PROPS_NAME_MAX_LEN + PROPS_VAL_MAX_LEN + 4];
			sprintf((char*) tmp, "[%-18s %18s]", dp->name,
					dp->value);
			mvprintw(i + PROPS_Y, PROPS_X, (char*) tmp);
		}
	}
}
