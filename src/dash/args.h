#ifndef ARGS_H
#define ARGS_H
struct runtime_args {
	char *js_path;
	char *r_addr;
	char *r_user;
	char *r_exec;
};

/*
 * Uses GNU getopt to parse arguments.
 * Takes the arguments passed to the program and the runtime_args
 * struct to put the data in to.
 */
void parse_args(struct runtime_args *, int argc, char **argv);

/*
 * Free all arguments.
 */
void free_args(struct runtime_args *);

extern struct runtime_args *r_args;
#endif
