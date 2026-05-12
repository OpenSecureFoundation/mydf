#ifndef DISK_INFO_H
#define DISK_INFO_H
typedef struct {
unsigned long blocks;
unsigned long free_blocks;
unsigned long avail_blocks;
unsigned long blocks_size;
} DiskInfo;
int get_disk_info(const char *path, DiskInfo *info);
#endif
