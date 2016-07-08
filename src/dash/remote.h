#ifndef REMOTE_H
#define REMOTE_H
/*
 * Tries to ssh into the remote.
 * Returns true if successful, false if not.
 */
 bool try_connect();

/*
 * Start the remote exec.
 */
void start_remote();

/*
 * Kills the ssh session, therefore killing the remote process.
 */
void kill_remote();
#endif
