/*
 * This is a file that is refferenced by both dash and remote by a relative
 * symbolic link.
 * All shared networking structures and constants should be defined here.
 */

#ifndef ARCS_NET_H
#define ARCS_NET_H

// DTR is dash to remote
#define REMOTE_PORT 30000
#define VIEWER_PORT 30001

#define MODE_DISABLED 0
#define MODE_TELEOP 1
#define MODE_TANK 2

#define MODE_DISABLED_STR "DISABLED"
#define MODE_TELEOP_STR "TELEOP"
#define MODE_TANK_STR "TANK"

#define IP_ARRAY_LEN 18

typedef uint8_t comm_mode_t;

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

struct pack_dtr {
	/*
	 * pac_num is the number of the packet.
	 * If pack_num is not the largest recived packet it is droped.
	 */
	uint64_t pack_num;

	comm_mode_t mode;
	struct js_state js_state;

	bool use_viewer;
	char viewer_ip[IP_ARRAY_LEN];
};

struct pack_viewer {
	uint64_t pack_num;

	float test;
};

#endif
