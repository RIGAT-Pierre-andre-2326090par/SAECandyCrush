#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <cst.h>

// Ce document header contient l'appel aux fonctions d'affichage

/**
 * @brief remonte l'écran de façon à donner l'impression que l'écran ai été effacé
 * @author A.Casali
 */
void clearScreen(); // Reset l'écran

/**
 * @brief applique la couleur donné à une partie du terminal
 * @param coul: couleur des caractères à venir
 * @author A.Casali
 */
void couleur(const unsigned & coul); // Affiche un texte en couleur

/**
 * @brief affichage de la matrice avec une couleur différente pour chaque nombre
 * @param Mat: matrice gérer par une fonction appelé par la fonction main
 * @param window: fenêtre active où le texte va être affiché
 * @authors A.Nurdin, A.Goncalves, P-A.Rigat
 */
void afficheMatriceV0(const CMatrice & Mat); // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche

/**
 * @brief affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur différente pour signifier que la case est a KAIgnorer
 * @param Mat: matrice gérer par une fonction appelé par la fonction main
 * @author A.Nurdin
 */
void afficheMatriceV1(const CMatrice & Mat); // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur
//pour signifier que la case est a KAIgnorer

/**
 * @brief affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur différente pour signifier que la case est a KAIgnorer
 * @param Mat: matrice gérer par une fonction appelé par la fonction main
 * @author A.Nurdin
 */
void afficheMatriceV2(const CMatrice & Mat); // affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
//pour signifier que la case est a KAIgnorer

/**
 * @brief affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur différente pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent
 * @param Mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse de la position de la case sélectionner
 * @param numCol: ordonnée de la position de la case sélectionner
 * @authors A.Nurdin, P-A.Rigat
 */
void afficheMatriceV3(const CMatrice & Mat, const size_t numLigne, const size_t numCol); // affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
// pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent

#endif // AFFICHAGE_H
