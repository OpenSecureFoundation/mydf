#ifndef DISPLAY_H
#define DISPLAY_H

#include "disk_calc.h"
#include "disk_convert.h"
#include "options.h"   

void afficher_entete(const Options *options);
void afficher_ligne_disque(const char *chemin, DiskCalc *result, const Options *options);

#endif
