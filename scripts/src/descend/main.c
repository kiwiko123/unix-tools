#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "descend.h"


int main(int argc, char** argv)
{
	int opt;
	int depth = -1;
	unsigned int index = 1;

	while ((opt = getopt(argc, argv, ":d:")) != -1)
	{
		switch (opt)
		{
			case 'd':
				depth = atoi(optarg);
				++index;
				break;
			default:
				fatal("invalid option");
		}
		++index;
	}

	descend_from(index >= argc ? "." : argv[index], depth);
	
	return 0;
}
