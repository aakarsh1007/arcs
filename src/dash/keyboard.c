#include "common.h"
#include "keyboard.h"
#include <ncurses.h>

#define CLOSE_CODE 3
#define DONE_CODE 4

pthread_mutex_t kb_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t kbthread;

volatile struct kb_status kb_stat = {false};

void * kb_loop(void *td) {
	//Note: See header for all keys (line 1413 latest version)

	int c;
	while(1) {
		c = getch();

		switch(c) {
			case CLOSE_CODE:
			case DONE_CODE:
			case 'q':
				pthread_mutex_lock(&kb_lock);
				kb_stat.close_request = true;
				pthread_mutex_unlock(&kb_lock);
				break;
			default:
				break;
		}
	}

	pthread_exit(NULL);
}

struct kb_status get_kb_status() {
	return kb_stat;
}	

bool kb_connect() {
	pthread_mutex_lock(&kb_lock);

	int stat = pthread_create(&kbthread, NULL, kb_loop, NULL);
	if(stat) {
		logm("Error creating kb thread");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&kb_lock);
	return true;
}
