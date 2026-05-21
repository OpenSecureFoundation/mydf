#ifndef DISPLAY_H // si DISPLAY_H n'existe pas encore on le cree
#define DISPLAY_H // on cree DISPLAY_H pour eviter les doublons 
#include <disk_calc.h> //pour utiliser disk_calc
#include <disk_convert.h> //pour utiliser disk_convert



// Structure qui contient les options de l'utilisateur
typedef struct {
    int human_readable;            // 1 = affichage lisible (G/M/K), 0 = octets
} Options;


// declaration de trois fonctions d'affichage
void afficher_entete(const Options *options); // affiche le titre du tableau
void afficher_ligne_disque(const char *chemin, DiskCalc *result, const Options *options) ;// afficche une ligne par disque 

#endif // FIN DE LA PROTECTION CONTRE LES DOUBLONS
