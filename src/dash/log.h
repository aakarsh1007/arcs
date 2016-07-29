#ifndef LOG_H
#define LOG_H
/*
 * Writes the string to the logfile (out.log default).
 * Opens and closes with each call, don't call often.
 */
 void logm(char *messg);
#endif
