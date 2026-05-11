
#include <stdio.h>
#include <sys/statvfs.h>

void to_human_readable(unsigned long long octets, char *out, int out_size) {
     const char *unites[] = {"B", "K", "M", "G", "T"};
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

int main(int argc, char *argv[]) {
    const char *chemin = "/";

   if (argc > 1) {
       chemin = argv[1];
   }

   struct statvfs st;

   if (statvfs(chemin, &st) != 0) {
       printf("Erreur de lecture\n");
       return 1;
   }

   unsigned long long total = (unsigned long long)st.f_blocks * st.f_frsize;
   unsigned long long free_root = (unsigned long long)st.f_bfree * st.f_frsize;
   unsigned long long free_user = (unsigned long long)st.f_bavail * st.f_frsize;
   unsigned long long used = total - free_user;
   int percent;

   if (total == 0) {
       percent = 0;
   } else {
       percent = (int)((used * 100) / total);
   }

   char total_str[10], used_str[10], free_str[10];
   to_human_readable(total, total_str, sizeof(total_str)),
   to_human_readable(used, used_str, sizeof(used_str));
   to_human_readable(free_user, free_str, sizeof(free_str));

   printf("\n mydf - Systeme de fichiers \n");
   printf("%-20s %8s %8s %8s %s\n", "Point montage", "Total", "Utilise", "Libre", "Use%%");
   printf("%-20s %8s %8s %8s %s\n", "------------------", "-----", "--------", "-----", "-----");
   printf("%-20s %8s %8s %8s %3d%%\n", chemin, total_str, used_str, free_str, percent);

  printf("--- Remarque ---\n");
  printf("bfree (libre pour root) : %llu octets\n", free_root);
  printf("bavail (libre pour user) : %llu octets\n", free_user);
  printf("Difference (reserve 5%%) : %llu octets\n\n", free_root - free_user);

  return 0;
}
