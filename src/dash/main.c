#include "common.h"
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"

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
	p[0]->name="Name 1";
	p[0]->value="Value 1";
	p[1]->name="Name 2";
	p[1]->value="Value 2";
	screen_render(p,2);
	getch();
#ifdef DEBUG
	fprintf(stdout, "Exiting\n");
#endif
	screen_close();
}
