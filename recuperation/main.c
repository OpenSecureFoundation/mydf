#include<stdio.h>
#include "disk_info.h"
int main(){
DiskInfo info;
if (get_disk_info("/",&info)!=0)
{
printf("Erreur lors de la lecture du disque");
return 1;
}
printf("Nombre total de blocks:%lu\n", info.blocks);
printf("Blocks libres:%lu\n", info.free_blocks);
printf("blocks disponibles:%lu\n",info.avail_blocks);
printf("Taille d'un block :%lu octets\n", info.blocks_size);
return 0;
}
