#ifndef TP_H
#define TP_H

#include <cst.h>

unsigned nouvRdm(unsigned & nb, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

void initMatV2 (CMatrice & mat, const size_t & nbLignes = 10,
               const size_t & nbColonnes = 10,
               const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

bool detectionExplositionUneBombeHorizontale (CMatrice & mat);

bool detectionExplositionUneBombeVertical (CMatrice & mat);

void detectionExplositionBombe (CMatrice & mat);

void faitUnMouvement (CMatrice & mat, const char & deplacment, const size_t & numLigne,
                     const size_t & numCol);

void faitUnMouvementV2 (CMatrice & mat, const char & deplacment, size_t & numLigne,
                       size_t & numCol);

int ppalExo01 ();

int ppalExo02 ();

int ppalExo03 ();

int ppalExo04 ();

int partiNumberCrush();

void affichePave();

int tp();

#endif // TP_H
