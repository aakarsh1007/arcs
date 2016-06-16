#include "common.h"
#include <stdarg.h>
#include "log.h"

#define LOGFILE "out.log"


void logm(char *messg, ...) {
	FILE *file = fopen(LOGFILE, "at");
	if (!file)
		file = fopen(LOGFILE, "wt");
	if (!file) {
		printf("Can't open log!");
		return;
	}

	va_list args;

	fprintf(file, messg, args);

	fclose(file);
}
