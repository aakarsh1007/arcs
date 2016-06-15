#include "common.h"
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "interface.h"

int main() {
#ifdef DEBUG
	fprintf(stdout, "Started dashboard\n");
#endif
	screen_init();

	struct properties props;
	char *js = found_js();
	props.js = (js == NULL) ? "Not found" : js;
	redraw(props);

	getch();
#ifdef DEBUG
	fprintf(stdout, "Exiting\n");
#endif
	screen_close();
}
