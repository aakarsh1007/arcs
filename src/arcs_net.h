/*
 * This is a file that is refferenced by both dash and remote by a relative symbolic link.
 * All shared networking structures and constants should be defined here.
 */

#ifndef ARCS_NET_H
#define ARCS_NET_H

// DTR is dash to remote
#define DTR_PORT 30000

#define MODE_DISABLED 0
#define MODE_TELEOP 1

struct js_state {
	bool btn_a;
	bool btn_b;
	bool btn_x;
	bool btn_y;
	bool btn_left_shoulder;
	bool btn_right_shoulder;
	bool btn_back;
	bool btn_start;
	bool btn_guide;
	bool btn_left_stick;
	bool btn_right_stick;

	float axis_left_x;
	float axis_left_y;
	float axis_left_trigger;
	float axis_right_x;
	float axis_right_y;
	float axis_right_trigger;
	float axis_dpad_x;
	float axis_dpad_y;
};

struct pack {
	/*
	 * pac_num is the number of the packet.
	 * If pack_num is not the largest recived packet it is droped.
	 */
	uint64_t pack_num;

	uint8_t mode;
	struct js_state js_state;
};

#endif
