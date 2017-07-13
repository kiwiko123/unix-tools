#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "descend.h"

#define _ERRBUFSIZ 512
const char _PROGRAM[] = "descend";


void fatal(const char* message)
{
	char buf[_ERRBUFSIZ];
	snprintf(buf, _ERRBUFSIZ, "%s: %s\n  ", _PROGRAM, message);
	perror(buf);
	exit(-1);
}

bool is_dir(const char* path, bool persist)
{
	struct stat st;
	if (stat(path, &st) == -1)
	{
		if (persist)
		{
			return false;
		}
		char errbuf[_ERRBUFSIZ];
		snprintf(errbuf, _ERRBUFSIZ, "failed to stat path: \"%s\"", path);
		fatal(errbuf);
	}
	return S_ISDIR(st.st_mode);
}

void descend_from(const char* path, int depth, bool persist, bool show_hidden)
{
	DIR* dir = opendir(path);
	if (!dir)
	{
		if (persist)
		{
			return;
		}
		char errbuf[_ERRBUFSIZ];
		snprintf(errbuf, _ERRBUFSIZ, "failed to open directory: \"%s\"", path);
		fatal(errbuf);
	}

	struct dirent* entry;
	while ((entry = readdir(dir)) && depth != 0)
	{
		// if name != '.' or name != '..' \
		//   or \
		// not show_hidden and name.startswith('.')
		if ((!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) || (!show_hidden && entry->d_name[0] == '.'))
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
			snprintf(buf, 1024, "%s", entry->d_name);
		}

		printf("%s", buf);
		if (is_dir(buf, persist))
		{
			printf("/\n");
			descend_from(buf, depth - 1, persist, show_hidden);
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
