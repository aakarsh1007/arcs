#include "common.h"
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "js.h"
#include "interface.h"

struct runtime_args *r_args;

int main(int argc, char **argv) {
#ifdef DEBUG
	logm("\nStarted dashboard\n");
#endif
	r_args = calloc(1, sizeof(struct runtime_args));
	parse_args(r_args, argc, argv);

	screen_init();

	char *js = found_js();
	if (js != NULL) {
		js_connect(js, js_update);
	}

	struct iface_args *props = calloc(1, sizeof(struct iface_args));
	props->js = (js == NULL) ? "Not found" : js;

	while (1) {
		if(props->jsstat.btn_a && props->jsstat.btn_y)
			break;
		usleep(10000);
		pthread_mutex_lock(&js_lock);
		props->jsstat = get_js_status();
		redraw(props);
		pthread_mutex_unlock(&js_lock);
	}

#ifdef DEBUG
	logm("Exiting\n");
#endif
	free(props);
	free(r_args);
	screen_close();
	return 0;
}
