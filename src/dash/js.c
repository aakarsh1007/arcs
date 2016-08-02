#include "common.h"
#include "js.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "screen.h"

pthread_t jsthread;
pthread_mutex_t js_lock = PTHREAD_MUTEX_INITIALIZER;

volatile struct js_state js_state = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

struct thread_data {
	char *path;
	void (*update)(struct js_event);
};

struct js_state get_js_state() {
	return js_state;
}

void js_update(struct js_event event) {

	//NOTE: https://www.kernel.org/doc/Documentation/input/joystick-api.txt

	pthread_mutex_lock(&js_lock);
	if (event.type > 2) { //Initial sequence, ignore for now
		event.type -= 0x80;
	}

	if (event.type == 1) {
		//Button
		if (event.number == 0)
			js_state.btn_a = event.value;
		else if (event.number == 1)
			js_state.btn_b = event.value;
		else if (event.number == 2)
			js_state.btn_x = event.value;
		else if (event.number == 3)
			js_state.btn_y = event.value;
		else if (event.number == 4)
			js_state.btn_left_shoulder = event.value;
		else if (event.number == 5)
			js_state.btn_right_shoulder = event.value;
		else if (event.number == 6)
			js_state.btn_back = event.value;
		else if (event.number == 7)
			js_state.btn_start = event.value;
		else if (event.number == 8)
			js_state.btn_guide = event.value;
		else if (event.number == 9)
			js_state.btn_left_stick = event.value;
		else if (event.number == 10)
			js_state.btn_right_stick = event.value;
		else {
			slog(200, SLOG_ERROR, "Unknown js type 1 event %d", event.number);
		}
	} else if (event.type == 2) {
		//Axis
		if (event.number == 0)
			js_state.axis_left_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 1)
			js_state.axis_left_y = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 2)
			js_state.axis_left_trigger = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 3)
			js_state.axis_right_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 4)
			js_state.axis_right_y = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 5)
			js_state.axis_right_trigger = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 6)
			js_state.axis_dpad_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 7)
			js_state.axis_dpad_y = ((float) event.value) / ((float) SHRT_MIN);
		else {
			slog(200, SLOG_ERROR, "Unknown js type 2 event %d", event.number);
		}
	} else {
		slog(100, SLOG_FATAL, "Unknown event type %d", event.type);
		screen_close();
		exit(EXIT_FAILURE);
	}
	pthread_mutex_unlock(&js_lock);
}

void * js_loop(void *p) {
	struct thread_data* td = (struct thread_data*) p;
	int fd = open(td->path, O_RDONLY);
	while (true) {
		struct js_event event;
		int ret = read(fd, &event, sizeof(event));
		if (ret == 0) {
			//Nothing
		}
		td->update(event);
	}
	close(fd);

	free(p);
	pthread_exit(NULL);
}

bool js_connect(char *path) {
	pthread_mutex_lock(&js_lock);

	struct thread_data* td = malloc(sizeof(struct thread_data));
	td->path = path;
	td->update = js_update;
	int stat = pthread_create(&jsthread, NULL, js_loop, (void*) td);
	if (stat) {
		slog(100, SLOG_FATAL, "Can't create js thread");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&js_lock);
	return true;
}

