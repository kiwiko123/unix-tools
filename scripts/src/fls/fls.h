#ifndef FLS_H
#define FLS_H


void print_path(const char* path, unsigned int argc, char* const* argv, unsigned int i);

void print_dir_entry(const char* path, const char* d_name, const char* prepend);

void full_list_directory(const char* path, unsigned int argc, char* const* argv, unsigned int i);

void analyze_path(const char* path, unsigned int argc, char* const* argv, unsigned int i);

void eval_real_path(unsigned int argc, char* const* argv, unsigned int i);

void process_argv(unsigned int argc, char* const* argv);

#endif // FLS_H
