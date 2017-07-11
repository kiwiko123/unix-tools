#ifndef _DESCEND_H
#define _DESCEND_H

#include <stdbool.h>

void fatal(const char* message);

bool is_dir(const char* path);

void descend_from(const char* path, int depth);

#endif // _DESCEND_H
