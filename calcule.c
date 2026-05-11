
#include <stdio.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[]) {
    const char *chemin = "/";

    if (argc > 1) {
        chemin = argv[1];
    }
    struct statvfs st;
    if (statvfs(chemin, &st) !=0) {
        printf("Erreur de lecture\n");
        return 1;
    }

    unsigned long long total;
    unsigned long long free_root;
    unsigned long long free_user;
    unsigned long long used;
    int percent;


    total = (unsigned long long)st.f_blocks * st.f_frsize;
    free_root = (unsigned long long)st.f_bfree * st.f_frsize;
    free_user =(unsigned long long)st.f_bavail * st.f_frsize;
    used = total - free_user;

   if (total == 0) {
       percent = 0;
   } else {
       percent = (int)((used * 100) / total);
   }

   printf("\n PARTIE 3: CALCULS BRUTS (en octets) \n");
   printf("Chemin : %s\n\n", chemin);
   printf(" Total (f_blocks * f_frsize) :%llu octets\n", total);
   printf("Libre pour root (f_bree) : %llu octets\n", free_user);
   printf("Libre pour user (f_bavail) : %llu octets\n", used);
   printf("pourcentage d'utilisation : %d%%\n\n", percent);
   
   printf(" DIFFERENCE ENTRE bfree ET bavail \n");
   printf(" bfree = %llu octets (tous les blocs libres)\n", free_root);
   printf(" bavail = %llu octets (blocs disponibles pour l'utilisation)\n", free_user);
   printf(" Difference = %llu octets (reserve de 5%% generqle;ent)\n\n", free_root - free_user);

   return 0;
}
