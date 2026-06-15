#ifndef DISK_INFO_H
#define DISK_INFO_H

#include <sys/statvfs.h>

typedef struct {
    unsigned long total;
    unsigned long avail;
    unsigned long free;
    unsigned long used;

    unsigned long inodes_total;
    unsigned long inodes_free;
    unsigned long inodes_used;
} DiskInfo;

int get_disk_info(const char *path, DiskInfo *info);

#endif
