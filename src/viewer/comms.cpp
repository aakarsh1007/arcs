#include "comms.hpp"

#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <iostream>

using namespace std;

struct lidar_data lidar_data; // packet number set to 0
pthread_mutex_t comms_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_t commsthread;

int sockfd;
struct sockaddr_in serv_sock;

void *comms_loop(void *td) {
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		std::cerr << "Failed to create server socket" << std::endl;
	}

	memset((char *)&serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_port = htons(VIEWER_PORT);
	serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&serv_sock,
			 sizeof(struct sockaddr_in)) == -1) {
		std::cout << "Failed to bind server socket" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (true) {
		struct pack_viewer p;
		struct sockaddr_in client;
		if (recvfrom(sockfd, &p, sizeof(struct pack_viewer), 0,
					 (struct sockaddr *)&client,
					 (socklen_t *)sizeof(struct sockaddr)) == -1) {
			// std::cerr << "Failed to recv packet" << std::endl;
		}

		int32_t sum = 0;
		for (int i = 0; i < 360; i++) {
			sum += p.lidar_data.dist[i];
		}

//		std::cout << "Received packet " << p.pack_num << " with sum " << sum
//				  << std::endl;

		lidar_data = p.lidar_data;
	}
}

void init_comms() {
	memset(&lidar_data, 0, sizeof(lidar_data));
	pthread_mutex_lock(&comms_lock);

	int stat = pthread_create(&commsthread, NULL, comms_loop, NULL);
	if (stat) {
		std::cerr << "Failed to create comms thread" << std::endl;
	}

	pthread_mutex_unlock(&comms_lock);
}

void close_comms() { pthread_cancel(commsthread); }
