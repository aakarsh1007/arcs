struct dash_property {
	char* name;
	char* value;
};

/**
 * Captures the screen and setup ncurses settings
 */
void screen_init();

/**
 * Closes the screen
 */
void screen_close();

/**
 * Renders the screen with the properties.
 * Takes an array of properties and an int32 for length.
 */
void screen_render(struct dash_property**, int32_t);
