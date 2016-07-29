#include "common.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define _POSIX_SOURCE
#include <signal.h>

#define DEFAULT_ADDR "192.168.1.44"
#define DEFAULT_USER "pi"
#define ADDR_BUFSIZE 32
#define DEFAULT_EXE "/var/arcs/arcs"

pid_t pid = 0;

char *addrstr() {
	return r_args->r_addr == NULL ? DEFAULT_ADDR : r_args->r_addr;
}

char *userstr() {
	return r_args->r_user == NULL ? DEFAULT_USER : r_args->r_user;
}

bool try_connect() {
	char *addr = addrstr();
	char *user = userstr();

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
			slog(100, SLOG_FATAL, "Strings too large in %s", __FUNCTION__);
			exit(EXIT_FAILURE);
		}
#endif
		snprintf(arg, ADDR_BUFSIZE, "%s@%s", user, addr);
		char *args[] = {"ssh", "-o", "ConnectTimeout=2", arg, "exit",  0};
		char *env[] = {0};
		execve("/usr/bin/ssh", args, env);
	}
	else {
		waitpid(pid, &statval, 0);
		pid = 0;
		if(WIFEXITED(statval))
			return (WEXITSTATUS(statval) == 0);
		else
			return false;
	}

	exit(EXIT_FAILURE);
}

void start_remote() {
	char *addr = addrstr();
	char *user = userstr();
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
			slog(100, SLOG_FATAL, "Strings too large in %s", __FUNCTION__);
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
	if(pid != 0)
		kill(pid, SIGKILL);
	pid = 0;
}
