#include <sys/time.h>
#include <stdint.h>
#include "timing.h"

int64_t microtime() {
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_usec;
}
