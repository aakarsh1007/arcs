#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"
#include <string.h>

#define STR_BUF_SIZE 48 //Needs to be enough for js path

void write_interface(struct iface_args *);
void add_prop(int, int, char*, char*);
char * bstr(char *, bool);
char * fstr(char *, float);

void redraw(struct iface_args *props) {
	screen_start_render();
	write_interface(props);
	screen_end_render();
}

void write_js(struct iface_args *props) {
	char val[STR_BUF_SIZE];

	screen_print_header(0, 0, "Gamepad");
	add_prop(0, 1, "Gamepad", props->js);

	add_prop(0, 3, "A Button", bstr(val, props->jsstat.btn_a));
	add_prop(0, 4, "B Button", bstr(val, props->jsstat.btn_b));
	add_prop(0, 5, "X Button", bstr(val, props->jsstat.btn_x));
	add_prop(0, 6, "Y Button", bstr(val, props->jsstat.btn_y));
	add_prop(0, 7, "Left Shoulder", bstr(val, props->jsstat.btn_left_shoulder));
	add_prop(0, 8, "Right Shoulder", bstr(val, props->jsstat.btn_right_shoulder));
	add_prop(0, 9, "Back Button", bstr(val, props->jsstat.btn_back));
	add_prop(0, 10, "Start Button", bstr(val, props->jsstat.btn_start));
	add_prop(0, 11, "Guide Button", bstr(val, props->jsstat.btn_guide));
	add_prop(0, 12, "Left Stick", bstr(val, props->jsstat.btn_left_stick));
	add_prop(0, 13, "Right Stick", bstr(val, props->jsstat.btn_right_stick));

	add_prop(0, 14, "Left X Axis", fstr(val, props->jsstat.axis_left_x));
	add_prop(0, 15, "Left Y Axis", fstr(val, props->jsstat.axis_left_y));
	add_prop(0, 16, "Left Trigger", fstr(val, props->jsstat.axis_left_trigger));
	add_prop(0, 17, "Right X Axis", fstr(val, props->jsstat.axis_right_x));
	add_prop(0, 18, "Right Y Axis", fstr(val, props->jsstat.axis_right_y));
	add_prop(0, 19, "Right Trigger", fstr(val, props->jsstat.axis_right_trigger));
	add_prop(0, 20, "D-Pad X Axis", fstr(val, props->jsstat.axis_dpad_x));
	add_prop(0, 21, "D-Pad Y Axis", fstr(val, props->jsstat.axis_dpad_y));

	screen_print_header(0, 23, "Network");
	add_prop(0, 24, "Remote", props->remote);
}

void write_interface(struct iface_args *props) {
	write_js(props);
}

void add_prop(int x, int y, char *name, char *value) {
	char total[STR_BUF_SIZE];

#ifdef DEBUG
	if(strlen(name) > 16) {
		logm("Name is too long!\n");
	}
	if(strlen(value) > 16) {
		logm("Value is too long!\n");
	}
#endif
	snprintf(total, STR_BUF_SIZE, "[%-16s %16s]", name, value);
	screen_print(x, y, total);
}

char * bstr(char *str, bool val) {
	strcpy(str, val ? "true" : "false");
	return str;
}

char * fstr(char *str, float val) {
	snprintf(str, STR_BUF_SIZE, "%.3f", val);
	return str;
}
