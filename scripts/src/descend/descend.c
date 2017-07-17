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
static const char* _PROGRAM = "descend";
static bool _PERSIST = false;

void fatal(const char* message)
{
	if (!_PERSIST)
	{
		char buf[_ERRBUFSIZ];
		snprintf(buf, _ERRBUFSIZ, "%s: %s\n  ", _PROGRAM, message);
		perror(buf);
		exit(-1);
	}
}

bool is_dir(const char* path)
{
	struct stat st;
	if (stat(path, &st) == -1)
	{
		char errbuf[_ERRBUFSIZ];
		snprintf(errbuf, _ERRBUFSIZ, "failed to stat path: \"%s\"", path);
		fatal(errbuf);
	}
	return S_ISDIR(st.st_mode);
}

void descend_from(const char* path, int depth, bool persist, bool show_hidden)
{
	_PERSIST = persist;
	DIR* dir = opendir(path);
	if (!dir)
	{
		if (_PERSIST)
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

		// if path == '.':
		//   print full/relative/path/to/entry
		// else:
		//   print entry
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
		if (is_dir(buf))
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
		char errbuf[_ERRBUFSIZ];
		snprintf(errbuf, _ERRBUFSIZ, "failed to close directory: \"%s\"", path);
		_PERSIST = true;	// let fatal() kill program if unmanaged resources exist
		fatal(errbuf);
	}
}
