#include "disk_info.h"
#include <sys/statvfs.h>
int get_disk_info(const char *path, DiskInfo *info)
{
    struct statvfs disk;

    if (statvfs(path, &disk) != 0)
        return -1;

    info->total = disk.f_blocks * disk.f_frsize;
    info->avail = disk.f_bavail * disk.f_frsize;
    info->free  = disk.f_bfree * disk.f_frsize;
    info->used  = info->total - info->avail;

    info->inodes_total = disk.f_files;
    info->inodes_free  = disk.f_ffree;
    info->inodes_used  = disk.f_files - disk.f_ffree;

    return 0;
}
