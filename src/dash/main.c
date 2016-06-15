#include "common.h"
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"
#include "io.h"

int main() {
#ifdef DEBUG
	fprintf(stdout, "Started dashboard\n");
#endif
	screen_init();
	struct dash_property p1 = {"",""};
	struct dash_property p2 = {"",""};
	printf("%p\n",&p1);
	struct dash_property* p[2];
	p[0]=&p1;
	p[1]=&p2;
	p[0]->name="Local";
	p[0]->value="";
	p[1]->name="Gamepad";
	char *js = found_js();
	if(js==NULL)
		p[1]->value="Not found";
	else
		p[1]->value=js;
	screen_render(p,2);
	getch();
#ifdef DEBUG
	fprintf(stdout, "Exiting\n");
#endif
	screen_close();
}
