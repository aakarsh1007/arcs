#include "common.h"
#include <sys/time.h>
#include <stdint.h>
#include "timing.h"

int64_t microtime() {
	struct timeval tv;
	if (gettimeofday(&tv, 0)) {
		slog(300, SLOG_WARN, "Failed gettimeofday");
	}
	return (int64_t)tv.tv_usec + (int64_t)1000000 * (int64_t)tv.tv_sec;
}
