#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"

#define PROP_NUM 23

lnk_list * create_interface(struct properties props);

char* fstring(float);

void redraw(struct properties props) {
	lnk_list * list = create_interface(props);
	screen_render(list);
	list_itterate(list, free);
}

lnk_list * create_interface(struct properties props) {

	struct dash_property *tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Local", "" };
	lnk_list *out = list_create(tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Gamepad", props.js };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "", "" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Input", "" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "A Button", props.jsstat.btn_a ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "B Button", props.jsstat.btn_b ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "X Button", props.jsstat.btn_x ?
			"true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Y Button", props.jsstat.btn_y ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Left Shoulder", props.jsstat.btn_left_shoulder ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Right Shoulder", props.jsstat.btn_right_shoulder ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Back Button", props.jsstat.btn_back ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Start Button", props.jsstat.btn_start ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Guide Button", props.jsstat.btn_guide ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Left Stick Button", props.jsstat.btn_left_stick ? "true" : "false" };
	list_append(out, tmp);

	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property) { "Right Stick Button", props.jsstat.btn_right_stick ? "true" : "false" };
	list_append(out, tmp);

//
////	for(uint32_t i = 15; i < 23; i++) {
////		array[i]->value = malloc(20);
////	}
////	array[15]->name="Axis Left X";
////	sprintf(array[15]->value, "%.3f", props.jsstat.axis_left_x);
////	array[16]->name="Axis Left Y";
////	sprintf(array[16]->value, "%.3f", props.jsstat.axis_left_y);
////	array[17]->name="Axis Left Trigger";
////	sprintf(array[17]->value, "%.3f", props.jsstat.axis_left_trigger);
////	array[18]->name="Axis Right X";
////	sprintf(array[18]->value, "%.3f", props.jsstat.axis_right_x);
////	array[19]->name="Axis Right Y";
////	sprintf(array[19]->value, "%.3f", props.jsstat.axis_right_y);
////	array[20]->name="Axis Right Trigger";
////	sprintf(array[20]->value, "%.3f", props.jsstat.axis_right_trigger);
////	array[21]->name="Axis D-Pad X";
////	sprintf(array[21]->value, "%.3f", props.jsstat.axis_dpad_x);
////	array[22]->name="Axis D-Pad Y";
////	sprintf(array[22]->value, "%.3f", props.jsstat.axis_dpad_y);
//
//	return array;

	return out;
}
