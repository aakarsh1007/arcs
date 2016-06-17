#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t num;
};

int main(int argc, char **argv) {
	int fd = open("/dev/input/js0", O_RDONLY);
	
	if(argc > 2) {
		fprintf(stderr, "Too many args!\njoystick [--no-axis|-n]\n");
		exit(-1);
	}

	bool axis = true;

	if(argc == 2) {
		if((strcmp(argv[1],"--no-axis")==0) || (strcmp(argv[1],"-n") == 0))
			axis = false;
		else {
			fprintf(stderr, "Unknown arg %s\njoystick [--no-axis|-n]\n", argv[1]);
			exit(-1);
		}
	}

	while(1) {
		struct js_event event;
		read(fd,&event,sizeof(struct js_event));
	if(!axis && event.type==2) continue;
		printf("time: %d, value: %d, type: %d, num: %d\n", (uint32_t) event.time, (int32_t) event.value, (uint32_t) event.type, (uint32_t) event.num);
	}	
	close(fd);
}
