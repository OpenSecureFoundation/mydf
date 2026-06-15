#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/statvfs.h>
#include <mntent.h>
void afficher_info_fs(const char *path)
{
    struct statvfs buf;

    if (statvfs(path, &buf) != 0) {
        fprintf(stderr, "Erreur pour %s: %s\n", path, strerror(errno));
        return;
    }

    unsigned long block_size = buf.f_frsize ? buf.f_frsize : buf.f_bsize;
    unsigned long total_kb   = (buf.f_blocks * block_size) / 1024;
    unsigned long used_kb    = ((buf.f_blocks - buf.f_bfree) * block_size) / 1024;
    unsigned long avail_kb   = (buf.f_bavail * block_size) / 1024;
    int           use_pct    = (buf.f_blocks > 0)
                               ? (int)(((buf.f_blocks - buf.f_bfree) * 100ULL) / buf.f_blocks)
                               : 0;

    printf("%-25s %10lu %10lu %10lu %5d%%\n",
           path, total_kb, used_kb, avail_kb, use_pct);
}



       
