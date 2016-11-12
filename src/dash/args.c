#include "common.h"
#include <string.h>
#include <getopt.h>

void log_args(struct runtime_args *args);

/*
 * Duplicates a string and returns a newly allocated pointer.
 */
char *scp(char *s) {
	char *out = calloc(1, 1 + strlen(s));
	strcpy(out, s);
	return out;
}

void parse_args(struct runtime_args *args, int argc, char **argv) {
	// Note, this uses the GNU implementation of getopt
	// Non-GNU libraries or headers will not compile/link
	int c;
	char *jsopt = 0, *r_addropt = 0, *r_useropt = 0, *r_execopt = 0,
		 *r_viewer_ip = 0;

	struct option long_options[] = {{"js-path", 1, 0, 'j'},
									{"remote", 1, 0, 'r'},
									{"user", 1, 0, 'u'},
									{"viewer", 1, 0, 'v'}};

	int opt_index;
	while ((c = getopt_long(argc, argv, "j:r:u:v:", long_options,
							&opt_index)) != -1) {

		switch (c) {
		case 'j':
			jsopt = scp(optarg);
			break;
		case 'r':
			r_addropt = scp(optarg);
			break;
		case 'u':
			r_useropt = scp(optarg);
			break;
		case 'v':
			r_viewer_ip = scp(optarg);
			break;
		case '?':
		default:
			fprintf(stderr, "Invalid arguments!\n");
			exit(EXIT_FAILURE);
		}
	}

	args->js_path = jsopt;
	args->r_addr = r_addropt;
	args->r_user = r_useropt;
	args->r_viewer_ip = r_viewer_ip;

	if (optind < argc) {
		fprintf(stderr, "Invalid arguments!\n");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	log_args(args);
#endif
}

void free_args(struct runtime_args *args) {
	if (args->js_path != NULL)
		free(args->js_path);
	if (args->r_addr != NULL)
		free(args->r_addr);
	if (args->r_user != NULL)
		free(args->r_user);
	if (args->r_viewer_ip != NULL)
		free(args->r_viewer_ip);
}

void logarg(char *key, char *val) {
	slog(400, SLOG_INFO, "[%s = %s]", key, val);
}

void log_args(struct runtime_args *args) {
	if (args->js_path != NULL) {
		logarg("js_path", args->js_path);
	}
	if (args->r_addr != NULL) {
		logarg("r_addr", args->r_addr);
	}
	if (args->r_user != NULL) {
		logarg("r_user", args->r_user);
	}
	if (args->r_viewer_ip != NULL) {
		logarg("r_viewer_ip", args->r_viewer_ip);
	}
}
