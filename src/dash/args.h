struct runtime_args {
	char *js_path;
};

void parse_args(struct runtime_args *, int argc, char **argv);

extern struct runtime_args *r_args;
