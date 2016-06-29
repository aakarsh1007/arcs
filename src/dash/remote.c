#include "common.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define DEFAULT_ADDR "192.168.1.44"
#define DEFAULT_USER "pi"
#define ADDR_BUFSIZE 32
#define DEFAULT_EXE "/var/arcs/arcs"

pid_t pid;

bool try_connect() {
	char *addr = r_args->r_addr == NULL ? DEFAULT_ADDR : r_args->r_addr;
	char *user = r_args->r_user == NULL ? DEFAULT_USER : r_args->r_user;

	int statval;

	pid = fork();
	if(pid == -1) {
		fprintf(stderr, "Can't fork\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0) {
		char arg[ADDR_BUFSIZE];
#ifdef DEBUG
		if(strlen(addr) + strlen(user) + 2 > ADDR_BUFSIZE) {
			logm("Too large ssh address\n");
			exit(EXIT_FAILURE);
		}
#endif
		snprintf(arg, ADDR_BUFSIZE, "%s@%s", user, addr);
		char *args[] = {"ssh", arg, "exit",  0};
		char *env[] = {0};
		execve("/usr/bin/ssh", args, env);
	}
	else {
		waitpid(pid, &statval, 0);
		if(WIFEXITED(statval))
			return (WEXITSTATUS(statval) == 0);
		else
			return false;
	}

	exit(EXIT_FAILURE);
}

void start_remote() {
	char *addr = r_args->r_addr == NULL ? DEFAULT_ADDR : r_args->r_addr;
	char *user = r_args->r_user == NULL ? DEFAULT_USER : r_args->r_user;
	char *exec = r_args->r_exec == NULL ? DEFAULT_EXE : r_args->r_exec;

	pid = fork();
	if(pid == -1) {
		fprintf(stderr, "Can't fork\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0) {
		char arg[ADDR_BUFSIZE];
#ifdef DEBUG
		if(strlen(addr) + strlen(user) + 2 > ADDR_BUFSIZE) {
			logm("Too large ssh address\n");
			exit(EXIT_FAILURE);
		}
#endif
		snprintf(arg, ADDR_BUFSIZE, "%s@%s", user, addr);
		char *args[] = {"ssh", "-t", arg, exec,  0};
		char *env[] = {0};
		execve("/usr/bin/ssh", args, env);
	}
}

void kill_remote() {
	kill(pid, SIGKILL);
}
