#include "common.h"
#include "js.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "screen.h"

pthread_t jsthread;

volatile struct js_status status = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

struct thread_data {
	char *path;
	void (*update)(struct js_event);
};

struct js_status get_js_status() {
	return status;
}

void js_update(struct js_event event) {

	//NOTE: https://www.kernel.org/doc/Documentation/input/joystick-api.txt

	if (event.type > 2) { //Initial sequence, ignore for now
		event.type -= 0x80;
	}

	if (event.type == 1) {
		//Button
		if (event.number == 0)
			status.btn_a = event.value;
		else if (event.number == 1)
			status.btn_b = event.value;
		else if (event.number == 2)
			status.btn_x = event.value;
		else if (event.number == 3)
			status.btn_y = event.value;
		else if (event.number == 4)
			status.btn_left_shoulder = event.value;
		else if (event.number == 5)
			status.btn_right_shoulder = event.value;
		else if (event.number == 6)
			status.btn_back = event.value;
		else if (event.number == 7)
			status.btn_start = event.value;
		else if (event.number == 8)
			status.btn_guide = event.value;
		else if (event.number == 9)
			status.btn_left_stick = event.value;
		else if (event.number == 10)
			status.btn_right_stick = event.value;
		else {
			logm("Unknown js event.value type %d event.number %d\n",
					(int32_t) event.type, (int32_t) event.number);
//			screen_close();
//			exit(EXIT_FAILURE);
		}
	} else if (event.type == 2) {
		//Axis
		if (event.number == 0)
			status.axis_left_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 1)
			status.axis_left_y = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 2)
			status.axis_left_trigger = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 3)
			status.axis_right_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 4)
			status.axis_right_y = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 5)
			status.axis_right_trigger = ((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 6)
			status.axis_dpad_x = -((float) event.value) / ((float) SHRT_MIN);
		else if (event.number == 7)
			status.axis_dpad_y = ((float) event.value) / ((float) SHRT_MIN);
		else {
			logm("Unknown js event.value type %d event.number %d\n",
					(int32_t) event.type, (int32_t) event.number);
			screen_close();
			exit(EXIT_FAILURE);
		}
	} else {
		logm("Unknown js input type %d\n", event.type);
		screen_close();
		exit(EXIT_FAILURE);
	}
}

void * loop(void *p) {
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

bool js_connect(char *path, void (*update)(struct js_event)) {
	struct thread_data* td = malloc(sizeof(struct thread_data));
	td->path = path;
	td->update = update;
	int status = pthread_create(&jsthread, NULL, loop, (void*) td);
	if (status) {
		logm("Error creating js thread\n");
		exit(EXIT_FAILURE);
	}
	return true;
}

