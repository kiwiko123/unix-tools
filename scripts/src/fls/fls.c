#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fls.h"


void print_path(const char* path, unsigned int argc, char* const* argv, unsigned int i)
{
    if (argc > 2)
    {
        printf("%s:\n", argv[i]);
    }

    printf("%s ", path);

    if (i < argc - 1)
    {
        printf("\n\n");
    }
}

void print_dir_entry(const char* path, const char* d_name, const char* prepend)
{
    if (strcmp(d_name, ".") != 0 && strcmp(d_name, "..") != 0)
    {
        printf("%s", prepend);
        char buf[FILENAME_MAX];
        snprintf(buf, FILENAME_MAX, "%s/%s", path, d_name);
        printf("%s", buf);
    }
}

void full_list_directory(const char* path, unsigned int argc, char* const* argv, unsigned int i)
{
    DIR* dir = opendir(path);
    if (!dir)
    {
        char error_buf[2048];
        snprintf(error_buf, 2048, "opendir(3): failed to open path \"%s\"", path);
        perror(error_buf);
        exit(-1);
    }

    struct dirent* entry = readdir(dir);
    if (entry)
    {
        while (entry && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0))
        {
            entry = readdir(dir);
        }

        if (entry)
        {
            print_dir_entry(path, entry->d_name, "");
        }

        while ((entry = readdir(dir)))
        {
            print_dir_entry(path, entry->d_name, "\n");
        }
    }

    int cstatus = closedir(dir);
    if (cstatus == -1)
    {
        char error_buf[2048];
        snprintf(error_buf, 2048, "closedir(3): failed to close directory \"%s\"", path);
        perror(error_buf);
        exit(-1);
    }
}

void analyze_path(const char* path, unsigned int argc, char* const* argv, unsigned int i)
{
    struct stat st;
    int status = stat(path, &st);
    if (status == -1)
    {
        char error_buf[2048];
        snprintf(error_buf, 2048, "stat(2): failed to stat path \"%s\"", path);
        perror(error_buf);
        exit(-1);
    }

    if (S_ISDIR(st.st_mode))
    {
        full_list_directory(path, argc, argv, i); 
    }
    else
    {
        print_path(path, argc, argv, i);
    }
}

void eval_real_path(unsigned int argc, char* const* argv, unsigned int i)
{
    char* buf = realpath(argv[i], NULL);
    if (buf)
    {
        analyze_path(buf, argc, argv, i);
        free(buf);
    }
    else
    {
        char error_buf[2048];
        snprintf(error_buf, 2048, "realpath(3): \"%s\" not a valid path", argv[i]);
        perror(error_buf);
        exit(-1);
    }
}

void process_argv(unsigned int argc, char* const* argv)
{
    unsigned int i = 1;
    if (argc <= 2)
    {
        eval_real_path(argc, argv, i);
    }
    else
    {
        printf("%s:\n", argv[i]);
        eval_real_path(argc, argv, i++);

        for (; argv[i]; ++i)
        {
            printf("\n\n%s:\n", argv[i]);
            eval_real_path(argc, argv, i);
        }
    }
    printf("\n");
}


