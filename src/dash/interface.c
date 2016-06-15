#include "common.h"
#include "screen.h"
#include "js.h"
#include "interface.h"

#define PROP_NUM 5

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
	*array[4] = (dp ) { "A", props.jsstat.btn_a ? "true" : "false" };
	return array;
}
