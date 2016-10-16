#include "common.h"
#include "keyboard.h"
#include <ncurses.h>
#include "comms.h"

#define CLOSE_CODE 3
#define DONE_CODE 4

pthread_mutex_t kb_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t kbthread;

struct kb_status kb_stat = {false, false, false};

void *kb_loop(void *td) {
	int c;
	while (1) {
		c = getch();
		switch (c) {
		case CLOSE_CODE:
		case DONE_CODE:
		case 'q':
			pthread_mutex_lock(&kb_lock);
			kb_stat.close_request = true;
			pthread_mutex_unlock(&kb_lock);
			break;
		case 'r':
			slog(400, SLOG_INFO, "Restarting networking");
			pthread_mutex_lock(&kb_lock);
			kb_stat.refresh_net = true;
			pthread_mutex_unlock(&kb_lock);
			break;
		case 0x20:
			// Space bar stop
			mode = MODE_DISABLED;
		case 'v':
			kb_stat.use_viewer = !kb_stat.use_viewer;
		default:
			// ASCII numbers to mode
			if (c >= 0x30 && c <= 0x39)
				mode = c - 0x30;
			break;
		}
	}

	pthread_exit(NULL);
}

struct kb_status *get_kb_status() {
	return &kb_stat;
}

void kb_connect() {
	pthread_mutex_lock(&kb_lock);

	int stat = pthread_create(&kbthread, NULL, kb_loop, NULL);
	if (stat) {
		slog(100, SLOG_FATAL, "Can't create kb thread");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&kb_lock);
}
