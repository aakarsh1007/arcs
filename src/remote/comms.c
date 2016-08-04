#include "common.h"
#include "comms.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

int sockfd;
struct sockaddr_in serv_sock;
struct pack last_pack;
pthread_mutex_t comm_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t commthread;

void init_comms() {
	if ((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		slog(100, SLOG_FATAL, "Failed to create server socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_port = htons(DTR_PORT);
	serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, &serv_sock, sizeof(struct sockaddr_in)) == -1) {
		slog(100, SLOG_FATAL, "Failed to bind server socket to port %d", DTR_PORT);
		exit(EXIT_FAILURE);
	}
}

void close_comms() {
	close(sockfd);
}

void update_comms() {
	struct pack p;
	struct sockaddr_in client;
	if(recvfrom(sockfd, &p, sizeof(struct pack), 0, &client, sizeof(struct sockaddr_in)) == -1) {
		//slog(300, SLOG_WARN, "recvfrom fail: %s", strerror(errno));
	}

	if(p.pack_num <= last_pack.pack_num) {
		return;
	}

	last_pack = p;
}

void *comm_loop(void *td) {
	while(1)
		update_comms();
}

void start_comms() {
	pthread_mutex_lock(&comm_lock);

	int stat = pthread_create(&commthread, NULL, comm_loop, NULL);
	if(stat) {
		slog(100, SLOG_FATAL, "Can't create comm thread");
	}

	pthread_mutex_unlock(&comm_lock);
}
