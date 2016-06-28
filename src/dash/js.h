struct js_status get_js_status();

struct js_event {
	uint32_t time;
	int16_t value;
	uint8_t type;
	uint8_t number;
};

struct js_status {
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

void js_update(struct js_event);


bool js_connect(char *path, void (*update)(struct js_event));
