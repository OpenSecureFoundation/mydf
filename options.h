#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    int show_all;
    int human_readable;
    int show_inode;
    int local_only;
    int show_type;
    int posix_format;
    int show_total;

    char *type_include;
    char *type_exclude;

    char **paths;
    int path_count;
} Options;

/* fonctions */
Options parse_options(int argc, char *argv[]);
void print_usage(const char *progname);

#endif
