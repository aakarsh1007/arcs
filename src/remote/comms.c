#include "common.h"
#include "comms.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int sockfd;
struct sockaddr_in serv_sock;

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

	slog(400, SLOG_INFO, "Created server socket");
}

void close_comms() {
	close(sockfd);
}
