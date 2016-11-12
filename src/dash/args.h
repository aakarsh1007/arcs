#pragma once

struct runtime_args {
	char *js_path;
	char *r_addr;
	char *r_user;
	char *r_viewer_ip;
};

void parse_args(struct runtime_args *, int argc, char **argv);

/*
 * Free all arguments.
 */
void free_args(struct runtime_args *);

extern struct runtime_args *r_args;
