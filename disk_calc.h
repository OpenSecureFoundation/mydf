#ifndef DISK_CALC_H
#define DISK_CALC_H

#include "disk_info.h"

typedef struct {
    unsigned long total;
    unsigned long used;
    unsigned long avail;
    int           percent;
} DiskCalc;

DiskCalc calculate_disk_usage(DiskInfo *info);

#endif
