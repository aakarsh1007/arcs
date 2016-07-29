#include "common.h"
#include <ncurses.h>
#include "screen.h"
#include "io.h"
#include "js.h"
#include "interface.h"
#include "keyboard.h"
#include "remote.h"

struct runtime_args *r_args;

int main(int argc, char **argv) {
#ifdef DEBUG
	logm("\nStarted dashboard\n");
#endif

	r_args = calloc(1, sizeof(struct runtime_args));
	parse_args(r_args, argc, argv);
	
	bool valid_remote = false;

	valid_remote = try_connect();
#ifdef DEBUG
	if(valid_remote)
		logm("Connected");
	else
		logm("Not connected");
#endif

	screen_init();

	kb_connect();

	char *js = found_js();
	if (js != NULL) {
		js_connect(js);
	}

	struct iface_args *props = calloc(1, sizeof(struct iface_args));
	props->js = (js == NULL) ? "Not found" : js;

	while (1) {
		if(props->jsstat.btn_guide) {
#ifdef DEBUG
			logm("End due to guide button press\n");
#endif
			break;
		}
		pthread_mutex_lock(&kb_lock);
		if(get_kb_status()->close_request) {
#ifdef DEBUG
			logm("End due to keyboard press\n");
#endif
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
		props->jsstat = get_js_status();
		props->remote = valid_remote ? addrstr() : "Invalid Addr";
		redraw(props);
		pthread_mutex_unlock(&js_lock);
	}

#ifdef DEBUG
	logm("Exiting\n");
#endif
	kill_remote();
	free(props);
	free(r_args);
	screen_close();
	return 0;
}
