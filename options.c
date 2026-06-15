#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "options.h"

/* ========================= */
/* OPTIONS LONGUES          */
/* ========================= */

static struct option long_opts[] = {
    { "all",          no_argument,       NULL, 'a' },
    { "human-readable", no_argument,     NULL, 'h' },
    { "inodes",       no_argument,       NULL, 'i' },
    { "local",        no_argument,       NULL, 'l' },
    { "portability",  no_argument,       NULL, 'P' },
    { "print-type",   no_argument,       NULL, 'T' },
    { "type",         required_argument, NULL, 't' },
    { "exclude-type", required_argument, NULL, 'x' },
    { "total",        no_argument,       NULL,  1  },
    { "help",         no_argument,       NULL,  2  },
    { NULL,           0,                 NULL,  0  }
};

/* ========================= */
/* USAGE                    */
/* ========================= */

void print_usage(const char *progname)
{
    fprintf(stderr,
        "Usage: %s [OPTION]... [FILESYSTEM]...\n"
        "  -a, --all              include pseudo-filesystems\n"
        "  -h, --human-readable   human readable sizes\n"
        "  -i, --inodes           show inode information\n"
        "  -l, --local            show only local filesystems\n"
        "  -P, --portability      POSIX output format\n"
        "  -T, --print-type       print filesystem type\n"
        "  -t, --type=TYPE        show only TYPE filesystem\n"
        "  -x, --exclude-type=TYPE exclude TYPE filesystem\n"
        "      --total            display total summary\n"
        "      --help             display this help\n",
        progname);

    exit(0);
}

/* ========================= */
/* PARSING OPTIONS          */
/* ========================= */

Options parse_options(int argc, char *argv[])
{
    Options opt;
    int c;

    memset(&opt, 0, sizeof(opt));

    while ((c = getopt_long(argc, argv, "ahilPTt:x:", long_opts, NULL)) != -1)
    {
        switch (c)
        {
            case 'a':
                opt.show_all = 1;
                break;

            case 'h':
                opt.human_readable = 1;
                break;

            case 'i':
                opt.show_inode = 1;
                break;

            case 'l':
                opt.local_only = 1;
                break;

            case 'P':
                opt.posix_format = 1;
                break;

            case 'T':
                opt.show_type = 1;
                break;

            case 't':
                opt.type_include = optarg;
                break;

            case 'x':
                opt.type_exclude = optarg;
                break;

            case 1:
                opt.show_total = 1;
                break;

            case 2:
                print_usage(argv[0]);
                break;

            case '?':
            default:
                fprintf(stderr, "Try '%s --help'\n", argv[0]);
                exit(1);
        }
    }

    /* arguments restants = filesystems */
    opt.paths = &argv[optind];
    opt.path_count = argc - optind;

    return opt;
}
