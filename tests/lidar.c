#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define START_CODE 0xfa

struct __attribute__((__packed__)) lidar_data {
	uint32_t value; //Placeholder, needs to be 4 bytes
};

struct __attribute__((__packed__)) lidar_packet {
	uint8_t start;
	uint8_t index;
	uint8_t speed_l;
	uint8_t speed_h;
	struct lidar_data data1;
	struct lidar_data data2;
	struct lidar_data data3;
	struct lidar_data data4;
	uint8_t check_l;
	uint8_t check_h;
};

void each(struct lidar_packet p) {
	printf("Start: %d, Index: %d\n", (int32_t) p.start, ((int32_t) p.index) - 0xa0);
}

int main(int argc, char **argv) {

	if(sizeof(struct lidar_packet) != 22)
		fprintf(stderr, "Invalid packet size");
	if(argc != 2) {
		fprintf(stderr, "Needs one argument!\n");
		exit(EXIT_FAILURE);
	}

	struct lidar_packet p;
	int fd = open(argv[1], O_RDONLY);
	int32_t readnum = 0;

	while(1) {
		if(readnum < 3) {
			uint8_t in;
			if(read(fd, &in, sizeof(uint8_t)) == 0)
				break;
//			printf("%o\n", in);
			if(in == EOF)
				break;
			if(in == START_CODE) {
				readnum++;
				read(fd, &p, sizeof(struct lidar_packet) - sizeof(uint8_t));
				continue;
			}
			readnum = 0;
			read(fd, &p, sizeof(uint8_t));
		}
		else {
			if(0 == read(fd, &p, sizeof(struct lidar_packet))) break;
			if(p.start != START_CODE) {
				readnum = 0;
				continue;
			}

			each(p);
		}
	}
	printf("Done!");
}
