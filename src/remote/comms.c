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
#include "arcs_net.h"

int sockfd;
struct sockaddr_in serv_sock;
struct pack_dtr last_pack;
pthread_mutex_t comm_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t commthread;

struct sockaddr_in viewer_sock;
int sockfd_dash;
uint64_t dash_pack_num;

bool viewer_ready = false;

void init_comms();
void *comm_loop(void *);

void init_viewer_comms(char *ip) {
	dash_pack_num = 0;
	if ((sockfd_dash = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		slog(100, SLOG_FATAL, "Failed to create viewer socket");
		exit(EXIT_FAILURE);
	}
	memset((char *)&viewer_sock, 0, sizeof(viewer_sock));
	viewer_sock.sin_family = AF_INET;
	viewer_sock.sin_port = htons(VIEWER_PORT);

	viewer_sock.sin_addr.s_addr = inet_addr(ip);
}

void init_local_comms() {
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		slog(100, SLOG_FATAL, "Failed to create server socket");
		exit(EXIT_FAILURE);
	}

	memset((char *)&serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_port = htons(REMOTE_PORT);
	serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&serv_sock,
			 sizeof(struct sockaddr_in)) == -1) {
		slog(100, SLOG_FATAL, "Failed to bind server socket to port %d",
			 REMOTE_PORT);
		exit(EXIT_FAILURE);
	}
}

void init_comms() { init_local_comms(); }

void send_viewer(struct pack_viewer pack) {
	if (!last_pack.use_viewer)
		return;

	if (!viewer_ready) {
		init_viewer_comms(last_pack.viewer_ip);
		viewer_ready = true;
	}

	if (sendto(sockfd_dash, &pack, sizeof(struct pack_viewer), 0,
			   (struct sockaddr *)&viewer_sock, sizeof(viewer_sock)) == -1)
		slog(300, SLOG_ERROR, "Failed to send packet");
}

void close_comms() {
	close(sockfd);
	close(sockfd_dash);
}

void update_comms() {
	struct pack_dtr p;
	struct sockaddr_in client;
	if (recvfrom(sockfd, &p, sizeof(struct pack_dtr), 0,
				 (struct sockaddr *)&client,
				 (socklen_t *)sizeof(struct sockaddr)) == -1) {
	}

	if (p.pack_num <= last_pack.pack_num) {
		return;
	}

	last_pack = p;
}

void *comm_loop(void *td) {
	while (1) {
		update_comms();
	}
}

void start_comms() {
	init_comms();
	pthread_mutex_lock(&comm_lock);

	int stat = pthread_create(&commthread, NULL, comm_loop, NULL);
	if (stat) {
		slog(100, SLOG_FATAL, "Can't create comm thread");
	}

	pthread_mutex_unlock(&comm_lock);
}
