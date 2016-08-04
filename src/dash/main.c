#include "common.h"
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "js.h"
#include "interface.h"
#include "keyboard.h"
#include "remote.h"
#include "comms.h"

struct runtime_args *r_args;

int main(int argc, char **argv) {
	slog_init("dash", "slog.cfg", 400, 500, 1);
	slog(400, SLOG_INFO, "Starting arcs-dash");


	r_args = calloc(1, sizeof(struct runtime_args));
	parse_args(r_args, argc, argv);
	
	bool valid_remote = false;

	screen_init();

	kb_connect();

	connect_comms();

	char *js = found_js();
	if (js != NULL) {
		js_connect(js);
	}

	struct iface_args *props = calloc(1, sizeof(struct iface_args));
	props->js = (js == NULL) ? "Not found" : js;

	while (1) {
		if(props->jsstat.btn_guide) {
			slog(400, SLOG_INFO, "Quit due to guide button press");
			break;
		}
		pthread_mutex_lock(&kb_lock);
		if(get_kb_status()->close_request) {
			slog(400, SLOG_INFO, "Quit due to keyboard press");
			break;
		}
		if(get_kb_status()->refresh_net) {
			kill_remote();
			valid_remote = try_connect();
			if(valid_remote)
				start_remote();
			get_kb_status()->refresh_net = false;
		}
		pthread_mutex_unlock(&kb_lock);
		usleep(10000);
		pthread_mutex_lock(&js_lock);
		props->jsstat = get_js_state();
		props->remote = valid_remote ? addrstr() : "No Connection";
		redraw(props);

		if(valid_remote)
			update_comms(get_js_state());

		pthread_mutex_unlock(&js_lock);
	}
	slog(400, SLOG_INFO, "Exiting");

	kill_remote();
	free(props);
	free(r_args);
	screen_close();
	disconnect_comms();
	return 0;
}
