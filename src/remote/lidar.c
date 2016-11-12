#include "common.h"
#include "lidar.h"
#include "xv11lidar.h"
#include <string.h>

#define LIDAR_TTY "/dev/ttyAMA0"
#define READS_PER_FRAME 4

struct lidar_data lidar_data;
pthread_mutex_t lidar_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t lidarthread;

/*
 * 1-90 value
 */
const int capture_frames = 15;
struct xv11lidar_data xv11_data;
struct laser_frame *frames;

void process_frame(struct laser_frame frame) {
	pthread_mutex_lock(&lidar_lock);
	lidar_data.speed = frame.speed;
	uint16_t index = frame.index - 0xA0;
	for (int i = 0; i < READS_PER_FRAME; i++) {
		if (frame.readings[i].distance > 10)
			lidar_data.dist[index * READS_PER_FRAME + i] =
				frame.readings[i].distance;
	}
	pthread_mutex_unlock(&lidar_lock);
}

void *lidar_loop(void *td) {

	int stat;

	while (true) {
		stat = ReadLaser(&xv11_data, frames);

		if (stat)
			continue;

		for (int i = 0; i < capture_frames; i++) {
			process_frame(frames[i]);
		}
	}

	return NULL;
}

void init_lidar() {
	memset(&lidar_data, 0, sizeof(lidar_data));
	pthread_mutex_lock(&lidar_lock);

	frames = calloc(capture_frames, sizeof(struct laser_frame));

	if (!frames)
		slog(100, SLOG_FATAL, "Can't allocate laser_frames");

	int stat = InitLaser(&xv11_data, LIDAR_TTY, capture_frames);
	if (stat != SUCCESS) {
		slog(100, SLOG_FATAL, "Failed to InitLaser");
		exit(EXIT_FAILURE);
	}

	stat = pthread_create(&lidarthread, NULL, lidar_loop, NULL);
	if (stat) {
		slog(100, SLOG_FATAL, "Can't create lidar thread");
	}

	pthread_mutex_unlock(&lidar_lock);
}

void close_lidar() {
	pthread_cancel(lidarthread);
	CloseLaser(&xv11_data);
}
