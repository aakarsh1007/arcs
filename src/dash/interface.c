#include "common.h"
#include "screen.h"
#include "interface.h"

#define PROP_NUM 2

typedef struct dash_property dp;

struct dash_property ** create_interface(struct properties props, dp* array[]);

void redraw(struct properties props) {
	dp* array[PROP_NUM];
	struct dash_property ** tmp = create_interface(props, array);
	screen_render(tmp, PROP_NUM);
	for(int32_t i = 0; i < PROP_NUM; i++) {
			free(array[i]);
		}
}


struct dash_property ** create_interface(struct properties props, dp* array[]) {
	for(int32_t i = 0; i < PROP_NUM; i++) {
		array[i] = calloc(1, sizeof(dp));
	}
	*array[0] = (dp) {"Local", ""};
	*array[1] = (dp) {"Gamepad", props.js};
	return array;
}
