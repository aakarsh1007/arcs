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

volatile struct js_status status = {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0};

struct thread_data {
	char *path;
	void (*update)(int16_t, uint8_t, uint8_t);
};

struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t number;
};

struct js_status get_js_status() {
	return status;
}

void js_update(int16_t value, uint8_t type, uint8_t number) {

	//NOTE: https://www.kernel.org/doc/Documentation/input/joystick-api.txt

	//	printf("JS_UPDATE[val: %d, type: %d, number: %d]\n", (int32_t) value, (int32_t) type,(int32_t) number);
	if (type > 2) { //Initial sequence, ignore for now
		type -= 0x80;
	}

	if (type == 1) {
		//Button
		if (number == 0)
			status.btn_a = value;
		else if (number == 1)
			status.btn_b = value;
		else if (number == 2)
			status.btn_x = value;
		else if (number == 3)
			status.btn_y = value;
		else if (number == 4)
			status.btn_left_shoulder = value;
		else if (number == 5)
			status.btn_right_shoulder = value;
		else if (number == 6)
			status.btn_back = value;
		else if (number == 7)
			status.btn_start = value;
		else if (number == 8)
			status.btn_guide = value;
		else if (number == 9)
			status.btn_left_stick = value;
		else if (number == 10)
			status.btn_right_stick = value;
		else {
			logm("Unknown js value type %d number %d\n",
					(int32_t) type, (int32_t) number);
//			screen_close();
//			exit(EXIT_FAILURE);
		}
	} else if (type == 2) {
		//Axis
		if (number == 0)
			status.axis_left_x = -((float) value) / ((float) SHRT_MIN);
		else if (number == 1)
			status.axis_left_y = ((float) value) / ((float) SHRT_MIN);
		else if (number == 2)
			status.axis_left_trigger = ((float) value) / ((float) SHRT_MIN);
		else if (number == 3)
			status.axis_right_x = -((float) value) / ((float) SHRT_MIN);
		else if (number == 4)
			status.axis_right_y = ((float) value) / ((float) SHRT_MIN);
		else if (number == 5)
			status.axis_right_trigger = ((float) value) / ((float) SHRT_MIN);
		else if (number == 6)
			status.axis_dpad_x = -((float) value) / ((float) SHRT_MIN);
		else if (number == 7)
			status.axis_dpad_y = ((float) value) / ((float) SHRT_MIN);
		else {
			logm("Unknown js value type %d number %d\n",
					(int32_t) type, (int32_t) number);
			screen_close();
			exit(EXIT_FAILURE);
		}
	} else {
		logm("Unknown js input type %d\n", type);
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
		td->update(event.value, event.type, event.number);
	}
	close(fd);

	free(p);
	pthread_exit(NULL);
}

bool js_connect(char *path, void (*update)(int16_t, uint8_t, uint8_t)) {
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

