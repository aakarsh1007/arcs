struct runtime_args {
	char *js_path;
};

/*
 * Uses GNU getopt to parse arguments.
 * Takes the arguments passed to the program and the runtime_args
 * struct to put the data in to.
 */
void parse_args(struct runtime_args *, int argc, char **argv);

extern struct runtime_args *r_args;
