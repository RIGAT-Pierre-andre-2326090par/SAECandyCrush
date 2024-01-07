#ifndef CST_H
#define CST_H

#include <type.h>
// Ce document contient les constantes utilisées dans main et affichage

/**
 * @brief code pour afficher la couleur par défaut du terminal
 * @author A.Casali
 */
const unsigned KReset   (0);

/**
 * @brief code pour afficher la couleur noir dans le terminal
 * @author A.Casali
 */
const unsigned KNoir    (30);

/**
 * @brief code pour afficher la couleur rouge dans le terminal
 * @author A.Casali
 */
const unsigned KRouge   (31);

/**
 * @brief code pour afficher la couleur vert dans le terminal
 * @author A.Casali
 */
const unsigned KVert    (32);

/**
 * @brief code pour afficher la couleur jaune dans le terminal
 * @author A.Casali
 */
const unsigned KJaune   (33);

/**
 * @brief code pour afficher la couleur bleu dans le terminal
 * @author A.Casali
 */
const unsigned KBleu    (34);

/**
 * @brief code pour afficher la couleur magenta dans le terminal
 * @author A.Casali
 */
const unsigned KMagenta (35);

/**
 * @brief code pour afficher la couleur cyan dans le terminal
 * @author A.Casali
 */
const unsigned KCyan    (36);

/**
 * @brief code pour afficher la couleur gris clair dans l'arrière plan du terminal
 * @author P-A.Rigat
 */
const unsigned KBGGrisClair(47);

/**
 * @brief contenu d'un case vide
 * @author A.Casali
 */
const contenueDUneCase KAIgnorer = 0;

/**
 * @brief valeur maximal que peut prendre le contenu d'un case
 * @author A.Casali
 */
const contenueDUneCase KPlusGrandNombreDansLaMatrice = 4;

#endif // CST_H

