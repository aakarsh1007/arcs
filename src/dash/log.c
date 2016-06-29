#include "common.h"
#include <stdarg.h>
#include "log.h"
#include <string.h>

#define LOGFILE "out.log"

void logm(char *messg) {
	FILE *file = fopen(LOGFILE, "at");
	if (!file)
		file = fopen(LOGFILE, "wt");
	if (!file) {
		printf("Can't open log!\n");
		return;
	}

	fprintf(file, "%s", messg);

	fclose(file);
}
