#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "descend.h"

#ifndef max
	#define max(a,b) (((a) >= (b)) ? (a) : (b))
#endif


const char _PROGRAM[] = "descend";


void fatal(const char* message)
{
	char buf[512];
	snprintf(buf, 512, "%s: %s\n", _PROGRAM, message);
	perror(buf);
	exit(-1);
}

bool is_dir(const char* path)
{
	struct stat st;
	if (stat(path, &st) == -1)
	{
		fatal("failed to stat path");
	}
	return S_ISDIR(st.st_mode);
}

void descend_from(const char* path, int depth)
{
	DIR* dir = opendir(path);
	if (!dir)
	{
		fatal("failed to open directory");
	}

	struct dirent* entry;
	while ((entry = readdir(dir)) && depth != 0)
	{
		// if name != '.' or name != '..':
		// if not (name == '.' or name == '..')
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
		{
			continue;
		}
		char buf[1024];
		if (strcmp(path, "."))
		{
			snprintf(buf, 1024, "%s/%s", path, entry->d_name);
		}
		else
		{
			strncpy(buf, entry->d_name, max(1024, strlen(entry->d_name)));
		}
		printf("%s", buf);
		if (is_dir(buf))
		{
			printf("/\n");
			descend_from(buf, depth - 1);
		}
		else
		{
			printf("\n");
		}
	}
	if (closedir(dir) == -1)
	{
		fatal("failed to close directory");
	}
}
