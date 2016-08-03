#include "common.h"
#include "arcs_net.h"
#include "comms.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

struct sockaddr_in remote_sock;
int sockfd;

void connect_comms() {
	if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		slog(100, SLOG_FATAL, "Failed to create socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &remote_sock, 0, sizeof(struct sockaddr_in));
	remote_sock.sin_family = AF_INET;
	remote_sock.sin_port = htons(DTR_PORT);

	if(inet_aton(r_args->r_addr, &remote_sock) == 0) {
		slog(100, SLOG_FATAL, "Error setting remote IP");
		exit(EXIT_FAILURE);
	}
}

void desconnect_comms() {
	close(sockfd);
}

void update_comms(struct js_state js_state) {

}
