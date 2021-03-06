#include "common.h"
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "js.h"
#include "interface.h"
#include "keyboard.h"
#include "comms.h"
#include "arcs_net.h"

struct runtime_args *r_args;
comm_mode_t mode;

int main(int argc, char **argv) {
	slog_init("dash", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-dash");

	r_args = calloc(1, sizeof(struct runtime_args));
	parse_args(r_args, argc, argv);
	bool valid_viewer = r_args->r_viewer_ip != NULL;

	mode = MODE_DISABLED;

	screen_init();
	kb_connect();
	connect_comms();

	char *js = found_js();
	if (js != NULL) {
		js_connect(js);
	}

	struct iface_args *props = calloc(1, sizeof(struct iface_args));
	props->js = (js == NULL) ? "Not found" : js;

	while (true) {
		if (props->jsstat.btn_guide) {
			slog(400, SLOG_INFO, "Quit due to guide button press");
			break;
		}
		pthread_mutex_lock(&kb_lock);
		if (get_kb_status()->close_request) {
			slog(400, SLOG_INFO, "Quit due to keyboard press");
			break;
		}
		pthread_mutex_unlock(&kb_lock);
		usleep(10000);
		pthread_mutex_lock(&js_lock);
		props->jsstat = get_js_state();
		props->remote = addrstr();
		props->mode = mode;
		props->use_viewer = valid_viewer && get_kb_status()->use_viewer;
		props->viewer_ip = valid_viewer ? r_args->r_viewer_ip : "NULL";
		redraw(props);

		update_comms(get_js_state(), mode,
					 valid_viewer && get_kb_status()->use_viewer,
					 r_args->r_viewer_ip);

		pthread_mutex_unlock(&js_lock);
	}
	slog(400, SLOG_INFO, "Exiting");

	free(props);
	free(r_args);
	screen_close();
	disconnect_comms();
	return 0;
}
