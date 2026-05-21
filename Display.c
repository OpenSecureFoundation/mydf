#include <stdio.h> // pour utiliser printf et snprintf
#include <string.h> // pour utiliser strcmp
#include <disk_calc.h> //pour utiliser disk_calc
#include <disk_convert.h> //pour utiliser disk_convert


// Structure qui contient les options taper par l'utilisateur
typedef struct {
    int human_readable;            // 1 = affichage lisible (G/M/K), 0 = octets
} Options;




// AFFICHAGE DE L'EN-TÊTE DU TABLEAU : affiche la premiere ligne du tableau avec les noms des colones 

void afficher_entete(const Options *options) {
    
    if (options->human_readable) {
        // En-tête pour format COURT (G/M/K) 
        printf("%-20s %8s %8s %8s %s\n",
               "Point montage",  //colone 1 nom du disque
               "Total",    //colone 2 taille totale
               "Utilise", //colone 3 espace utilisé
               "Libre",  //colone 4 espace libre
               "Use%"); //colone 5 pourcentage
    } else {
        // En-tête pour format LONG (octets complets)
        printf("%-20s %15s %15s %15s %s\n",
               "Point montage", "Total", "Utilise", "Libre", "Use%");
    }
    
    // Ligne de séparation
    printf("%-20s %8s %8s %8s %s\n",
           "--------------", "-----", "--------", "-----", "------");
}


// AFFICHAGE D'UNE LIGNE DE DONNEES POUR UN DISQUE (utilise la structure DiskCalc

void afficher_ligne_disque(const char *chemin, DiskCalc *result, const Options *options) {
    
    if (options->human_readable) {
        // MODE LISIBLE : on convertit les octets en G/M/K
        char taille_totale[16];
        char espace_utilise[16];
        char espace_disponible[16];
        
        // on appelle la foncton de conversion de la coequipière
        format_human_readable(result->total, taille_totale);//convertie total en texte
        format_human_readable(result-> used, espace_utilise); //convertit used en texte 
        format_human_readable(result->free_user, espace_disponible); // convertit free_user en texte
        
        // Affichage avec tailles en G/M/K
        printf("%-20s %8s %8s %8s %3d%%\n",
               chemin, taille_totale, espace_utilise, espace_disponible, result->percent);
               
    } else {
        // MODE NORMAL : affichage des octets bruts
        printf("%-20s %11lld %11lld %11lld %3d%%\n",
               chemin, result->total, result->used, result->free_user, result->percent);
    }
}



