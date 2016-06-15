#include "common.h"
#include "io.h"

#define JS_NAME "/dev/input/js0"

char * found_js() {
	FILE * f;
	if ((f = fopen(JS_NAME, "r"))) {
		fclose(f);
		return JS_NAME;
	}
	return NULL;
}
