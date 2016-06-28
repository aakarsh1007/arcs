/**
 * Captures the screen and setup ncurses settings
 */
void screen_init();

/**
 * Closes the screen
 */
void screen_close();

void screen_start_render();

void screen_end_render();

void screen_print(int, int, char*);

void screen_print_header(int, int, char*);
