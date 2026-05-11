
#include <stdio.h>

void to_human_readable(unsigned long long octets, char *out, int out_size) {
     const char *unites[]  = {"B", "K", "M", "G", "T"};
     int idx = 0;
     double val = (double)octets;

     while (val >= 1024.0 && idx < 4) {
         val /= 1024.0;
         idx++;
     }

     if (idx == 0) {
         snprintf(out, out_size, "%.0f%s", val, unites[idx]);
     } else {
         snprintf(out, out_size, "%.1f%s", val, unites[idx]);
     }
}

int main() {
    printf("PARTIE 4 : CONVERSION EN FORMAT LISIBLE \n\n");

    unsigned long long valeurs[]  = {
        512,
        1024,
        1536,
        1048576,
        1073741824,
        5368709120,
        1099511627776,
    };

    printf("%20s = %10s\n", "Octets", "Format lisible");
    printf("%20s = %10s\n", "------", "------------");

    for (int i = 0; i < 7; i++) {
         char resultat[10];
         to_human_readable (valeurs[i], resultat, sizeof(resultat));
         printf("%20llu = %10s\n", valeurs[i], resultat);
   }

   printf("\n");
   return 0;
}
