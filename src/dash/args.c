#include "common.h"
#include <string.h>
#include <getopt.h>

void log_args(struct runtime_args *args);

char *scp(char *s) {
	char *out = calloc(1, 1 + strlen(s));
	strcpy(out, s);
	return out;
}

void parse_args(struct runtime_args *args, int argc, char **argv) {
	// Note, this uses the GNU implementation of getopt
	// Non-GNU librarys or headers will not compile/link
	int c;
	char *jsopt = 0, *r_addropt = 0, *r_useropt = 0, *r_execopt = 0;

	struct option long_options[] = {{"js-path", 1, 0, 'j'},
									{"remote", 1, 0, 'r'},
									{"user", 1, 0, 'u'},
									{"exec", 1, 0, 'e'}};

	int opt_index;
	while ((c = getopt_long(argc, argv, "j:r:u:e:", long_options,
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
		case 'e':
			r_execopt = scp(optarg);
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
	args->r_exec = r_execopt;

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
	if (args->r_exec != NULL)
		free(args->r_exec);
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
	if (args->r_exec != NULL) {
		logarg("r_exec", args->r_exec);
	}
}
