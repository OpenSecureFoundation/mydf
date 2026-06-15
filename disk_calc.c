#include "disk_calc.h"
#include "disk_info.h"

DiskCalc calculate_disk_usage(DiskInfo *info)
{
    DiskCalc result = {0};

    result.total = info->total;
    result.avail = info->avail;
    result.used  = info->used;

    if (result.total > 0)
        result.percent = (result.used * 100) / result.total;
    else
        result.percent = 0;

    result.inodes_total = info->inodes_total;
    result.inodes_free  = info->inodes_free;
    result.inodes_used  = info->inodes_used;

    return result;
}
