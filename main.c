#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"
#include "disk_info.h"
#include "disk_calc.h"
#include "affichage.h"

#define MAX_SEEN 1024

/* ===================== */
/* FS À IGNORER PAR DÉFAUT */
/* ===================== */
static int is_virtual_fs(const char *type)
{
    return (
        strcmp(type, "proc") == 0 ||
        strcmp(type, "sysfs") == 0 ||
        strcmp(type, "tmpfs") == 0 ||
        strcmp(type, "devtmpfs") == 0 ||
        strcmp(type, "cgroup") == 0 ||
        strcmp(type, "pstore") == 0 ||
        strcmp(type, "bpf") == 0 ||
        strcmp(type, "autofs") == 0
    );
}

/* ===================== */
/* DEDUP SIMPLE (mount ID) */
/* ===================== */
static int seen_id(char seen[][64], int count, const char *id)
{
    for (int i = 0; i < count; i++)
        if (strcmp(seen[i], id) == 0)
            return 1;
    return 0;
}

/* ===================== */
/* PARSE mountinfo       */
/* ===================== */
static void parse_line(char *line,
                        char *id,
                        char *mountpoint,
                        char *fstype)
{
    char *save;
    char *tok;
    int field = 0;

    tok = strtok_r(line, " ", &save);

    while (tok)
    {
        field++;

        if (field == 1)
            strcpy(id, tok);

        if (field == 5)
            strcpy(mountpoint, tok);

        if (strcmp(tok, "-") == 0)
        {
            tok = strtok_r(NULL, " ", &save);
            if (tok)
                strcpy(fstype, tok);
            break;
        }

        tok = strtok_r(NULL, " ", &save);
    }
}

int main(int argc, char *argv[])
{
    Options opt = parse_options(argc, argv);

    FILE *fp = fopen("/proc/self/mountinfo", "r");
    if (!fp)
    {
        perror("mountinfo");
        return 1;
    }

    afficher_entete(&opt);

    char seen[MAX_SEEN][64];
    int seen_count = 0;

    char line[1024];

    while (fgets(line, sizeof(line), fp))
    {
        char id[64] = {0};
        char mountpoint[512] = {0};
        char fstype[64] = {0};

        parse_line(line, id, mountpoint, fstype);

        /* ===================== */
        /* -l local only         */
        /* ===================== */
        if (opt.local_only && strchr(mountpoint, ':'))
            continue;

        /* ===================== */
        /* -t / -x               */
        /* ===================== */
        if (opt.type_include &&
            strcmp(fstype, opt.type_include) != 0)
            continue;

        if (opt.type_exclude &&
            strcmp(fstype, opt.type_exclude) == 0)
            continue;

        /* ===================== */
        /* -a (default filter)   */
        /* ===================== */
        if (!opt.show_all && is_virtual_fs(fstype))
            continue;

        /* ===================== */
        /* DEDUP                 */
        /* ===================== */
        if (seen_id(seen, seen_count, id))
            continue;

        if (seen_count < MAX_SEEN)
            strcpy(seen[seen_count++], id);

        /* ===================== */
        /* DISK INFO            */
        /* ===================== */
        DiskInfo info;
        if (get_disk_info(mountpoint, &info) != 0)
            continue;

        DiskCalc res = calculate_disk_usage(&info);

        afficher_ligne_disque(mountpoint, &res, &opt);
    }

    fclose(fp);
    return 0;
}
