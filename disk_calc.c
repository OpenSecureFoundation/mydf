#include "disk_calc.h"

DiskCalc calculate_disk_usage(DiskInfo *info) {
    DiskCalc result;

    result.total = info->blocks * info->blocks_size;

   unsigned long free_bytes = info->free_blocks * info->blocks_size;

   result.avail = info->avail_blocks * info->blocks_size;

   result.used = result.total - free_bytes;

   if (result.total > 0)
       result.percent = (int)((result.used * 100) / result.total);
   else
       result.percent = 0;

   return result;
}
