#ifndef TP_H
#define TP_H

#include <cst.h>

/**
 * @brief génère un nombre aléatoire entre 1 et nbMax et différent de nb
 * @param nb: nombre dont le nombre renvoyé doit être différent
 * @param nbMax:  le nombre aléatoire sera générer entre 1 et nbMax
 * @return un nombre aléatoire entre 1 et nbMax et différent de nb
 * @author P-A.Rigat
 */
unsigned nouvRdm(unsigned & nb, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

/**
 * @brief génère une matrice mat de dimension nbLignes x nbColonnes rempli de nombre aléatoire entre 1 et nbMax, et avec moins de 3 chiffres aligné verticalement ou horizontalement
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param nbLignes: nombre de ligne de la matrice mat
 * @param nbColonnes: nombre de colonne de la matrice mat
 * @param nbMax: les nombres aléatoire sont compris entre 1 et nbMax(par défaut 4)
 */
void initMatV2 (CMatrice & mat, const size_t & nbLignes = 10,
               const size_t & nbColonnes = 10,
               const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés horizontalement dans la matrice
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @return true si il y a au moins une explosion, false sinon
 * @authors A.Casali
 */
bool detectionExplositionUneBombeHorizontale (CMatrice & mat);

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés verticalement dans la matrice
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @return true si il y a au moins un explosion, false sinon
 * @authors P-A.Rigat, A.Nurdin
 */
bool detectionExplositionUneBombeVertical (CMatrice & mat);

/**
 * @brief fonction détectant si une explosion verticale ou horizontale est présente dans la matrcie à l'aide des deux autres fonctions de détection
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @author P-A.Rigat
 */
void detectionExplositionBombe (CMatrice & mat);

/**
 * @brief procédure permettant au joueur d'échanger 2 éléments dans la grille
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param deplacment: caractère indiquant l'action choisi
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 */
void faitUnMouvement (CMatrice & mat, const char & deplacment, const size_t & numLigne,
                     const size_t & numCol);

/**
 * @brief procédure permettant au joueur de se déplacer dans la grille et de déplacer l'élément qu'il a séléctionné
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param deplacment: caractère indiquant l'action choisi
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 */
void faitUnMouvementV2 (CMatrice & mat, const char & deplacment, size_t & numLigne,
                       size_t & numCol);

/**
 * @brief l'exercice 1 du TP
 * @return 0
 */
int ppalExo01 ();

/**
 * @brief l'exercice 2 du TP
 * @return 0
 */
int ppalExo02 ();

/**
 * @brief l'exercice 3 du TP
 * @return 0
 */
int ppalExo03 ();

/**
 * @brief l'exercice 4 du TP
 * @return 0
 */
int ppalExo04 ();

/**
 * @brief gère une parti de number crush dans le terminal
 * @return 0
 */
int partiNumberCrush();

/**
 * @brief affiche un pavé qui explique que choisir
 */
void affichePave();

/**
 * @brief permet de tester les exos et une version primitive de number crush
 * @return 0
 */
int tp();

#endif // TP_H
