#ifndef KEYBOARD_H
#define KEYBOARD_H
struct kb_status {
	bool close_request;
	bool refresh_net;
	bool use_viewer;
};

/*
 * Creates a thread to handle keyboard input.
 * Exits if can't create thread.
 */
void kb_connect();

/*
 * Returns the kb_status.
 */
struct kb_status *get_kb_status();

extern pthread_mutex_t kb_lock;
#endif
