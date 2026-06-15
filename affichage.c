#include <stdio.h>
#include <mntent.h>
#include <string.h>

#include "disk_calc.h"
#include "disk_convert.h"
#include "options.h"

/* ===================== */
/* GET FS TYPE           */
/* ===================== */
const char *get_fs_type(const char *path)
{
    FILE *fp = setmntent("/proc/mounts", "r");
    struct mntent *ent;

    if (!fp)
        return "unknown";

    while ((ent = getmntent(fp)) != NULL)
    {
        if (strcmp(ent->mnt_dir, path) == 0)
        {
            endmntent(fp);
            return ent->mnt_type;
        }
    }

    endmntent(fp);
    return "unknown";
}

/* ===================== */
/* HEADER                */
/* ===================== */
void afficher_entete(const Options *opt)
{
    if (opt->posix_format)
    {
        printf("Filesystem           1024-blocks      Used Available Capacity Mounted on\n");
        printf("-------------------- ------------- -------- ---------- --------- ----------\n");
        return;
    }

    if (opt->show_inode)
    {
        printf("%-20s %10s %10s %10s\n",
               "Filesystem", "Inodes", "Used", "Free");
        printf("-------------------- ---------- ---------- ----------\n");
        return;
    }

    printf("%-20s %10s %10s %10s %5s\n",
           "Filesystem", "Total", "Used", "Avail", "Use%");
    printf("-------------------- ---------- ---------- ---------- ------\n");
}

/* ===================== */
/* HUMAN FORMAT          */
/* ===================== */


/* ===================== */
/* PRINT LINE            */
/* ===================== */
void afficher_ligne_disque(const char *path, DiskCalc *result, const Options *opt)
{
    char t1[32], t2[32], t3[32];

    /* ===================== */
    /* -T TYPE FS           */
    /* ===================== */
    if (opt->show_type)
    {
        printf("%-20s %-10s %10lu %10lu %10lu %3d%%\n",
               path,
               get_fs_type(path),
               result->total,
               result->used,
               result->avail,
               result->percent);
        return;
    }

    /* ===================== */
    /* -i INODES            */
    /* ===================== */
    if (opt->show_inode)
    {
        printf("%-20s %10lu %10lu %10lu\n",
               path,
               result->inodes_total,
               result->inodes_used,
               result->inodes_free);
        return;
    }

    /* ===================== */
    /* -P POSIX MODE        */
    /* ===================== */
    if (opt->posix_format)
    {
        printf("%-20s %10lu %10lu %10lu %3d%% %s\n",
               path,
               result->total / 1024,
               result->used / 1024,
               result->avail / 1024,
               result->percent,
               path);
        return;
    }

    /* ===================== */
    /* -h HUMAN             */
    /* ===================== */
    if (opt->human_readable)
    {
        format_human_readable(result->total, t1);
        format_human_readable(result->used, t2);
        format_human_readable(result->avail, t3);

        printf("%-20s %10s %10s %10s %3d%%\n",
               path, t1, t2, t3, result->percent);
        return;
    }

    /* ===================== */
    /* DEFAULT              */
    /* ===================== */
    printf("%-20s %10lu %10lu %10lu %3d%%\n",
           path,
           result->total,
           result->used,
           result->avail,
           result->percent);
}
