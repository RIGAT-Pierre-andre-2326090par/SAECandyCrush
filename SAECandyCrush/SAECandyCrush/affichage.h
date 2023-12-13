#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <type.h>
#include <cst.h>

// Ce document header contient l'appel aux fonctions d'affichage

void clearScreen();
void couleur(const unsigned & coul);
void afficheMatriceV0(const CMatrice & Mat);
void afficheMatriceV1(const CMatrice & Mat);
void afficheMatriceV2(const CMatrice & Mat);
void afficheMatriceV3(const CMatrice & Mat, const size_t numLigne, const size_t numCol);

#endif // AFFICHAGE_H
