#include "common.h"
#include "io.h"

#define JS_DEFAULT "/dev/input/js0"

char * found_js() {
	char *fpath = r_args->js_path == NULL ? JS_DEFAULT : r_args->js_path;

	FILE * f;
	if ((f = fopen(fpath, "r"))) {
		fclose(f);
		return fpath;
	}
	return NULL;
}
