#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "options.h"

/* Options longues (--help, --total...) */
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
}; /* la derniere ligne  prend tjr ses valeurs pour indiquer la fin du tableau*/

void print_usage(const char *progname)
{
    fprintf(stderr,
        "Usage: %s [OPTION]... [CHEMIN]...\n"
        "  -a, --all              inclut les pseudo-filesystems\n"
        "  -h, --human-readable   tailles lisibles (1K, 2M, 3G)\n"
        "  -i, --inodes           affiche les inodes\n"
        "  -l, --local            filesystems locaux uniquement\n"
        "  -P, --portability      format POSIX\n"
        "  -T, --print-type       affiche le type de filesystem\n"
        "  -t, --type=TYPE        affiche uniquement ce type\n"
        "  -x, --exclude-type=TYPE exclut ce type\n"
        "      --total            affiche un total\n"
        "      --help             affiche cette aide\n",
        progname);
    exit(0);
}

Options parse_options(int argc, char *argv[])
{
    Options opt;
    int c;

    /* On met tout à zéro pour partir d'un état propre */
    memset(&opt, 0, sizeof(Options));

    while ((c = getopt_long(argc, argv, "ahilPTt:x:", long_opts, NULL)) != -1)
    {
        switch (c)
        {
            case 'a': opt.show_all       = 1;      break;
            case 'h': opt.human_readable = 1;      break;
            case 'i': opt.show_inode     = 1;      break;
            case 'l': opt.local_only     = 1;      break;
            case 'P': opt.posix_format   = 1;      break;
            case 'T': opt.show_type      = 1;      break;
            case 't': opt.type_include   = optarg; break;
            case 'x': opt.type_exclude   = optarg; break;
            case  1 : opt.show_total     = 1;      break;
            case  2 : print_usage(argv[0]);        break;
            case '?':
                fprintf(stderr, "Essayez '%s --help'\n", argv[0]);
                exit(1);
        }
    }

    /* Récupère les chemins libres (ex: /home /tmp) */
    opt.paths      = &argv[optind];
    opt.path_count = argc - optind;

    return opt;
}
