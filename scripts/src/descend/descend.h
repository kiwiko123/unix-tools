#ifndef _DESCEND_H
#define _DESCEND_H

#include <stdbool.h>

/* Prints a formatted message to the screen.
 * Exits the program with a status of -1.
 */
void fatal(const char* message);

/* Returns true if 'path' points to a directory, or false if not.
 */
bool is_dir(const char* path);

/* Recursively descends from 'path', printing entries.
 * Stops after 'depth' levels, or continues to completion if depth == -1.
 */
void descend_from(const char* path, int depth, bool show_hidden);

#endif // _DESCEND_H
