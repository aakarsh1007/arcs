#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"

#define PROP_NUM 15

typedef struct dash_property dp;

struct dash_property ** create_interface(struct properties props, dp* array[]);

void redraw(struct properties props) {
	dp* array[PROP_NUM];
	struct dash_property ** tmp = create_interface(props, array);
	screen_render(tmp, PROP_NUM);
	for (int32_t i = 0; i < PROP_NUM; i++) {
		free(array[i]);
	}
}

struct dash_property ** create_interface(struct properties props, dp* array[]) {
	for (int32_t i = 0; i < PROP_NUM; i++) {
		array[i] = calloc(1, sizeof(dp));
	}
	*array[0] = (dp ) { "Local", "" };
	*array[1] = (dp ) { "Gamepad", props.js };
	*array[2] = (dp ) { "", "" };
	*array[3] = (dp ) { "Input", "" };
	*array[4] = (dp ) { "A Button", props.jsstat.btn_a ? "true" : "false" };
	*array[5] = (dp ) { "B Button", props.jsstat.btn_b ? "true" : "false" };
	*array[6] = (dp ) { "X Button", props.jsstat.btn_x ? "true" : "false" };
	*array[7] = (dp ) { "Y Button", props.jsstat.btn_y ? "true" : "false" };
	*array[8] = (dp ) { "Left Shoulder", props.jsstat.btn_left_shoulder ? "true" : "false" };
	*array[9] = (dp ) { "Right Shoulder", props.jsstat.btn_right_shoulder ? "true" : "false" };
	*array[10] = (dp ) { "Back Button", props.jsstat.btn_back ? "true" : "false" };
	*array[11] = (dp ) { "Start Button", props.jsstat.btn_start ? "true" : "false" };
	*array[12] = (dp ) { "Guide Button", props.jsstat.btn_guide ? "true" : "false" };
	*array[13] = (dp ) { "Left Stick Button", props.jsstat.btn_left_stick ? "true" : "false" };
	*array[14] = (dp ) { "Right Stick Button", props.jsstat.btn_right_stick ? "true" : "false" };

	return array;
}
