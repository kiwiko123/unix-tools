#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "descend.h"


int main(int argc, char** argv)
{
	int opt;
	int depth = -1;
	bool persist = false;
	bool show_hidden = false;

	while ((opt = getopt(argc, argv, "d:hp")) != -1)
	{
		switch (opt)
		{
			case 'd':
				depth = atoi(optarg);
				break;
			case 'h':
				show_hidden = true;
				break;
			case 'p':
				persist = true;
				break;
			default:
				fatal("invalid option");
		}
	}

	descend_from(optind >= argc ? "." : argv[optind], depth, persist, show_hidden);
	return 0;
}
