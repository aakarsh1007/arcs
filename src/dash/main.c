#include "common.h"
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "js.h"
#include "interface.h"

int main() {
#ifdef DEBUG
	logm("Started dashboard\n");
#endif
	screen_init();

	char *js = found_js();
	if (js != NULL) {
		js_connect(js, js_update);
	}

	struct properties *props = malloc(sizeof(struct properties));
	props->js = (js == NULL) ? "Not found" : js;

	while (1) {
		usleep(10000);
		props->jsstat = get_js_status();
		redraw(props);
	}

#ifdef DEBUG
	logm("Exiting\n");
#endif
	free(props);
	screen_close();
	return 0;
}
