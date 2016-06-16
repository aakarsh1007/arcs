#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"
#include <string.h>

#define VALUE_MEM_SIZE 24

lnk_list * create_interface(struct properties props);
lnk_list * add_prop(lnk_list*, char *, char *);
char * boolstr( bool);
char* fstring(float);
void freevalstr(void *);


void redraw(struct properties props) {
	lnk_list * list = create_interface(props);
	screen_render(list);
	list_itterate(list, freevalstr);
	list_itterate(list, free);
	list_free(list);
}

lnk_list * create_interface(struct properties props) {

	lnk_list *out = NULL;

	char *js = calloc(1, VALUE_MEM_SIZE);
	strcpy(js,props.js);
	out = add_prop(out, "Gamepad", js);

	char *blk = calloc(1, VALUE_MEM_SIZE);
	strcpy(blk,"");
	add_prop(out, "", blk);

	blk = calloc(1, VALUE_MEM_SIZE);
	strcpy(blk,"");
	add_prop(out, "Input", blk);

	add_prop(out, "A Button", boolstr(props.jsstat.btn_a));

	add_prop(out, "B Button", boolstr(props.jsstat.btn_b));

	add_prop(out, "X Button", boolstr(props.jsstat.btn_x));

	add_prop(out, "Y Button", boolstr(props.jsstat.btn_y));

	add_prop(out, "Left Shoulder", boolstr(props.jsstat.btn_left_shoulder));

	add_prop(out, "Right Shoulder", boolstr(props.jsstat.btn_right_shoulder));

	add_prop(out, "Back Button", boolstr(props.jsstat.btn_back));

	add_prop(out, "Start Button", boolstr(props.jsstat.btn_start));

	add_prop(out, "Guide Button", boolstr(props.jsstat.btn_guide));

	add_prop(out, "Left Stick Button", boolstr(props.jsstat.btn_left_stick));

	add_prop(out, "Right Stick Button", boolstr(props.jsstat.btn_right_stick));

	char *tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_left_x);
	add_prop(out,"Axis Left X",tmp);

	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_left_y);
	add_prop(out,"Axis Left Y",tmp);

	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_left_trigger);
	add_prop(out,"Axis Left Trigger",tmp);

	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_right_x);
	add_prop(out,"Axis Right X",tmp);


	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_right_y);
	add_prop(out,"Axis Right Y",tmp);

	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_right_trigger);
	add_prop(out,"Axis Right Trigger",tmp);


	tmp = calloc(1, VALUE_MEM_SIZE);
	sprintf(tmp, "%.3f", props.jsstat.axis_dpad_x);
	add_prop(out,"Axis D-Pad X",tmp);

	//There is a bug somewhere, this stops it
	tmp = calloc(1, VALUE_MEM_SIZE);
	float f = props.jsstat.axis_dpad_y;
	if(f < -1.5 || f > 1.5) {
		logm("Invalid f %f",f);
		f = 0.0;
	}
	sprintf(tmp, "%.3f", f);
	add_prop(out,"Axis D-Pad Y",tmp);

	return out;
}

inline char * boolstr(bool b) {
	char *tmp = calloc(1, VALUE_MEM_SIZE);
	strcpy(tmp,b ? "true" : "false");
	return tmp;
}

lnk_list * add_prop(lnk_list *list, char *name, char *value) {
	struct dash_property *tmp;
	tmp = malloc(sizeof(struct dash_property));
	*tmp = (struct dash_property ) { name, value };
	if (list == NULL)
		list = list_create(tmp);
	else
		list_append(list, tmp);
	return list;
}

void freevalstr(void *val) {
	struct dash_property* ptr = (struct dash_property *)val;
	free(ptr->value);
}
