#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <type.h>
#include <cst.h>
#include <mingl/mingl.h>

// Ce document header contient l'appel aux fonctions d'affichage

void clearScreen(); // Reset l'écran

void couleur(const unsigned & coul); // Affiche un texte en couleur

void afficheMatriceV0(const CMatrice & Mat, MinGL & window); // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche

void afficheMatriceV1(const CMatrice & Mat); // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur
//pour signifier que la case est a KAIgnorer

void afficheMatriceV2(const CMatrice & Mat); // affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
//pour signifier que la case est a KAIgnorer

void afficheMatriceV3(const CMatrice & Mat, const size_t numLigne, const size_t numCol); // affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
// pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent

#endif // AFFICHAGE_H
