#ifndef INTERFACE_H
#define INTERFACE_H
struct iface_args {
	char *js;
	struct js_status jsstat;
};

/*
 * Updates the interface based on the properties passed to it.
 */
void redraw(struct iface_args *props);
#endif
