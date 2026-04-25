#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
	int human_readable;
	int show_all;
	int show_type;
	int show_inode:
	char *type_include;
	char *type_exclude;
} Options;

Options parse_options( int argc, char *argv[]);

#endif


