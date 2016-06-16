#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"

#define PROP_NUM 23

typedef struct dash_property dp;

struct dash_property ** create_interface(struct properties props, dp* array[]);

char* fstring(float);

void redraw(struct properties props) {
	dp* array[PROP_NUM];
	struct dash_property ** tmp = create_interface(props, array);
	screen_render(tmp, PROP_NUM);

	for (int32_t i = 15; i < 23; i++) {
			free(array[i]->value);
	}

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

	for(uint32_t i = 15; i < 23; i++) {
		array[i]->value = malloc(20);
	}
	array[15]->name="Axis Left X";
	sprintf(array[15]->value, "%.3f", props.jsstat.axis_left_x);
	array[16]->name="Axis Left Y";
	sprintf(array[16]->value, "%.3f", props.jsstat.axis_left_y);
	array[17]->name="Axis Left Trigger";
	sprintf(array[17]->value, "%.3f", props.jsstat.axis_left_trigger);
	array[18]->name="Axis Right X";
	sprintf(array[18]->value, "%.3f", props.jsstat.axis_right_x);
	array[19]->name="Axis Right Y";
	sprintf(array[19]->value, "%.3f", props.jsstat.axis_right_y);
	array[20]->name="Axis Right Trigger";
	sprintf(array[20]->value, "%.3f", props.jsstat.axis_right_trigger);
	array[21]->name="Axis D-Pad X";
	sprintf(array[21]->value, "%.3f", props.jsstat.axis_dpad_x);
	array[22]->name="Axis D-Pad Y";
	sprintf(array[22]->value, "%.3f", props.jsstat.axis_dpad_y);

	return array;
}
