#ifndef DISK_CALC_H
#define DISK_CALC_H

#include "disk_info.h"

typedef struct {
    unsigned long total;
    unsigned long used;
    unsigned long avail;
    int percent;

    unsigned long inodes_total;
    unsigned long inodes_used;
    unsigned long inodes_free;
} DiskCalc;

DiskCalc calculate_disk_usage(DiskInfo *info);

#endif
