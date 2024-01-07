#ifndef GESTIONPARTIE_H
#define GESTIONPARTIE_H

#include <type.h>
#include <cst.h>

/**
 * @brief procédure initialisant les paramètres du joueur au sein du jeu
 * @param param: structure de variable gérer par la fonction main
 * @authors A.Casali, P-A.Rigat
 */
void initParams (CMyParam & param);

/**
 * @brief procédure permettande d'enlever le caractère ':' d'une chaine de caractère passer en paramètre
 * @param str: chaine de caractère à traiter
 * @return la chaine de caractère sans le caractère ':'
 * @author P-A.Rigat
 */
std::string strSansDeuxPts (const std::string & str);

/**
 * @brief procédure permettant de charger les paramètres de jeu d'un joueur depuis un fichier yaml
 * @param params: structure de variable gérer par la fonction main
 * @param fichier: chemin du fichier yaml cible
 * @authors A.Casali, P-A.Rigat
 */
void chargerParametre(CMyParam & params, const std::string & fichier);

/**
 * @brief fonction qui renvoie un nouveau nombre aléatoire entre 1 et nbMax différent de nb1 et nb2
 * @param nb1: premier nombre dont le nouveaux nombre aléatoire doit être différent
 * @param nb2: second nombre dont le nouveaux nombre aléatoire doit être différent
 * @param nbMax: le nouveaux nombre aléatoire doit être inclut entre 1 et nbMax
 * @return rdm: nombre aléatoire entre 1 et nbMax différent de nb1 et nb2
 * @author P-A.Rigat
 */
unsigned nouvRdm(unsigned & nb1, unsigned & nb2, const unsigned & nbMax);

/**
 * @brief procédure générant une matrice remplie de nombre aléatoire entre 1 et nbMax
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param nbMax: les nombres aléatoire sont compris entre 1 et nbMax(par défaut 4)
 * @param nbLignes: nombre de ligne de la matrice mat
 * @param nbColonnes: nombre de colonne de la matrice mat
 * @authors A.Casali, P-A.Rigat
 */
void initMat (CMatrice & mat, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice,
             const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10);

/**
 * @brief procédure modifiant la matrice en supprimant des éléments identiques alignés horizontalement par nombre de 3 à 5
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du premier nombre servant de repère pour l'explosion de la bombe
 * @param numColonne: ordonnée du premier nombre servant de repère pour l'explosion de la bombe
 * @param combien: nombre de chiffre aligné horizontalement
 * @author A.Casali
 */
void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien);

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés horizontalement dans la matrice
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @return true si il y a au moins une explosion, false sinon
 * @authors A.Casali, P-A.Rigat
 */
bool detectionExplositionUneBombeHorizontale (CMatrice & mat, unsigned & score);

/**
 * @brief procédure modifiant la matrice en supprimant des éléments identiques alignés verticalement par nombre de 3 à 5
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du premier nombre servant de repère pour l'explosion de la bombe
 * @param numColonne: ordonnée du premier nombre servant de repère pour l'explosion de la bombe
 * @param combien: nombre de chiffre aligné verticalement
 * @authors P-A.Rigat, A.Nurdin
 */
void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,
                                  const size_t & numColonne, const size_t & combien);

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés verticalement dans la matrice
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @return true si il y a au moins un explosion, false sinon
 * @authors P-A.Rigat, A.Nurdin
 */
bool detectionExplositionUneBombeVerticale (CMatrice & mat, unsigned & score);

/**
 * @brief remplace toutes les cases vides par des nombres aléatoires
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @param nbMax: les nombres aléatoire sont compris entre 1 et nbMax(par défaut 4)
 * @author P-A.Rigat
 */
void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer,
                        const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

/**
 * @brief fonction permettant de déplacer vers le bas tous les éléments flottant après une explosion jusqu'à être côte à côte d'un élément juste en dessous d'eux ou au fond de la matrice si il n'y a pas d'éléments en dessous
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @return true si un ou plusieurs élément on été déplacé, false sinon
 * @author P-A.Rigat
 */
bool zeroVidSousNb (CMatrice & mat, const unsigned & vid = KAIgnorer);

/**
 * @brief fonction détectant si une explosion verticale ou horizontale est présente dans la matrcie à l'aide des deux autres fonctions de détection
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @param plusGrandNb: les nombres aléatoire sont compris entre 1 et plusGrandNb(par défaut 4)
 * @return true si il y a eu au moins une explosion vertical ou horizontal, false sinon
 * @author P-A.Rigat
 */
bool detectionExplositionBombe (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                               const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice);

/**
 * @brief procédure permettant au joueur de se déplacer dans la grille et de déplacer l'élément qu'il a séléctionné
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param deplacment: caractère indiquant l'action choisi
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 */
void faitUnMouvement (CMatrice & mat, const char & deplacment, size_t & numLigne,
                     size_t & numCol, unsigned & nbDeplacement, CMyParam & param);

#endif // GESTIONPARTIE_H
