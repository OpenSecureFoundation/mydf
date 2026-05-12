#include "disk_info.h"
#include <sys/statvfs.h>
int get_disk_info( const char *path, DiskInfo *info){
struct statvfs disk;
if (statvfs(path,&disk)!=0)
return -1;
info->blocks=disk.f_blocks;
info->free_blocks=disk.f_bfree;
info->avail_blocks=disk.f_bavail;
info->blocks_size=disk.f_frsize;
return 0;
}
