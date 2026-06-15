# mydf

##  Description
**mydf** est une réimplémentation en langage C de la commande Linux `df`.

La commande `df` permet d’afficher l’utilisation des systèmes de fichiers (espace disque utilisé, disponible, taux d’utilisation, etc.).

Ce projet a pour objectif de reproduire un comportement similaire à `df` tout en respectant une architecture modulaire et pédagogique.

---

##  Objectifs du projet
- Comprendre la gestion des systèmes de fichiers sous Linux
- Manipuler les structures système liées au stockage
- Implémenter une commande système en C
- Gérer les options utilisateur
- Structurer un projet en modules indépendants

---

##  Architecture du projet

Le projet est divisé en 5 modules :

### 1.  Récupération
Récupération des informations des systèmes de fichiers (blocs, inodes, points de montage, etc.).

### 2.  Calculs et conversions
Traitement des données et conversion des tailles en formats lisibles (Ko, Mo, Go).

### 3. Affichage
Affichage des résultats sous forme de tableau similaire à `df`.

### 4. Options
Gestion des options utilisateur.

### 5.  Gestion des erreurs
Gestion des erreurs liées aux options invalides ou aux accès système.

---

## Compilation

```bash
gcc *.c -o mydf
