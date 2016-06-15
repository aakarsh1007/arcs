#include "common.h"
#include <ncurses.h>
#include <string.h>
#include "screen.h"

#define LOGO_X 1
#define LOGO_Y 1
#define PROPS_X 1
#define PROPS_Y 8
#define PROPS_NAME_MAX_LEN 12
#define PROPS_VAL_MAX_LEN 12

void draw_logo();
void draw_props(struct dash_property** props, int32_t len);

void screen_init() {
#ifdef DEBUG
	fprintf(stdout, "Initializting screen\n");
#endif
	initscr();
	cbreak();
	noecho();
	int stat = curs_set(0);
#ifdef DEBUG
	if(stat == ERR) {
		fprintf(stderr, "This terminal does not support setting cursor visibility\n");
	}
#endif
	if(has_colors() == FALSE) {
		fprintf(stderr, "Color not supported, exiting.\n");
		screen_close();
		exit(EXIT_FAILURE);
	}
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
#ifdef DEBUG
	fprintf(stdout, "Screen created\n");
#endif
}

void screen_close() {
	nocbreak();
	echo();
	endwin();
}

void screen_render(struct dash_property** props, int32_t len) {
	clear();
	draw_logo();
	draw_props(props, len);
	refresh();
}

void draw_logo() {
	attron(COLOR_PAIR(1));
	mvprintw(0+LOGO_Y, 0+LOGO_X, "    /\\                 ");
	mvprintw(1+LOGO_Y, 0+LOGO_X, "   /  \\   _ __ ___ ___ ");
	mvprintw(2+LOGO_Y, 0+LOGO_X, "  / /\\ \\ | '__/ __/ __|");
	mvprintw(3+LOGO_Y, 0+LOGO_X, " / ____ \\| | | (__\\__ \\");
	mvprintw(4+LOGO_Y, 0+LOGO_X, "/_/    \\_\\_|  \\___|___/");
	attroff(COLOR_PAIR(1));
}

void draw_props(struct dash_property** props, int32_t len) {
	if(props == NULL) {
		fprintf(stderr, "NULL props value");
		screen_close();
		exit(EXIT_FAILURE);
	}
	for(int32_t i = 0; i < len; i++) {
		if(strlen(props[i]->name) > PROPS_NAME_MAX_LEN) {
			fprintf(stderr, "Name %s larger than limit. Exiting\n", props[i]->name);
			screen_close();
			exit(EXIT_FAILURE);
		}
		if(strlen(props[i]->value) > PROPS_VAL_MAX_LEN) {
			fprintf(stderr, "Value %s larger than limit. Exiting\n", props[i]->value);
			screen_close();
			exit(EXIT_FAILURE);
		}
		mvprintw(i+PROPS_Y, PROPS_X, props[i]->name);
		mvprintw(i+PROPS_Y, PROPS_X+PROPS_NAME_MAX_LEN, props[i]->value);
	}
}
