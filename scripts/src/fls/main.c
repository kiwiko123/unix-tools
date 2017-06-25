// FLS(1)
// 
// NAME
//      fls - full ls
//
// SYNOPSIS
//      fls [path ...]
//
// DESCRIPTION
//      Lists the full/absolute path to each immediate file/directory found in the argument path(s).
//      If no arguments are given, the contents of the current directory are displayed.
//
//      Currently, fls supports no options/flags.
//
// Author: Geoffrey Ko (2017)
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "fls.h"


int main(int argc, char** argv)
{
    if (argc == 1)  // no arguments
    {
        char* cargv[3] = {argv[0], ".", NULL};
        process_argv(argc + 1, cargv);
    }
    else
    {
        process_argv(argc, argv);
    }

    return 0;
}
