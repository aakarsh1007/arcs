#include "common.h"
#include <string.h>
#include <getopt.h>

void log_args(struct runtime_args *args);

void parse_args(struct runtime_args *args, int argc, char **argv) {
	//Note, this uses the GNU implementation of getopt
	//Non-GNU librarys or headers will not compile/link
	int c;
	char *jsopt = 0;

	struct option long_options[] = {
		{"js-path", 1, 0, 'j'}
	};

	int opt_index;
	while((c = getopt_long(argc, argv, "j:", long_options,
		&opt_index)) != -1) {

		switch(c) {
		case 'j':
			jsopt = optarg;
			break;
		case '?':
		default:
			fprintf(stderr, "Invalid arguments!\n");
			exit(EXIT_FAILURE);
		}
	}

	args->js_path = jsopt;

	if(optind < argc) {
		fprintf(stderr, "Invalid arguments!\n");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	log_args(args);
#endif
}

void log_args(struct runtime_args *args) {
	logm("Runtime args: ");
	if(args->js_path != NULL) {
		logm("[js-path=");
		logm(args->js_path);
		logm("]");
	}
	logm("\n");
}
