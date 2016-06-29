struct kb_status {
	bool close_request;
};

bool kb_connect();

struct kb_status get_kb_status();

extern pthread_mutex_t kb_lock;
