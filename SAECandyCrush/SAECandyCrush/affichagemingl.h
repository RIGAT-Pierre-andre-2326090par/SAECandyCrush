#ifndef AFFICHAGEMINGL_H
#define AFFICHAGEMINGL_H

#include <string>

#include <cst.h>
#include <mingl/mingl.h>
#include <mingl/graphics/idrawable.h>

/**
 * @brief affichage de la matrice avec des cercles de couleurs différentes, représentant le contenu des cases
 * @param Mat: matrice gérer par une fonction appelé par la fonction main
 * @param window: fenêtre active où le texte va être affiché
 * @authors A.Nurdin, A.Goncalves, P-A.Rigat
 */
void  afficheMatriceMingl (const CMatrice & Mat , MinGL & window);

/**
 * @brief dessine un rectangle de couleur bleu avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du rectangle
 * @param y: ordonnée de l'origine du rectangle
 * @author P-A.Rigat
 */
void dessinerRectangle (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief dessine un cercle de couleur rouge avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du cercle
 * @param y: ordonnée de l'origine du cercle
 * @author P-A.Rigat
 */
void dessinerCercle (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief dessine un triangle de couleur verte avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du triangle
 * @param y: ordonnée de l'origine du triangle
 * @author P-A.Rigat
 */
void dessinerTriangle (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief dessine une croix de couleur jaune avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de la croix
 * @param y: ordonnée de l'origine de la croix
 * @author P-A.Rigat
 */
void dessinerCroix (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief dessine un curseur(composé de 4 triangles) de couleur blanche avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du curseur
 * @param y: ordonnée de l'origine du curseur
 * @author P-A.Rigat
 */
void dessinerCurseur (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief dessine une étoile de couleur violette avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'étoile
 * @param y: ordonnée de l'origine de l'étoile
 * @author P-A.Rigat
 */
void dessinerEtoile (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche le texte txt en blanc au coordonné x, y
 * @param window: fenêtre active où le texte va être affiché
 * @param txt: texte à afficher
 * @param x: absisse de l'origine du texte
 * @param y: ordonnée de l'origine du texte
 * @author P-A.Rigat
 */
void afficheText (MinGL & window, const std::string & txt, const unsigned & x, const unsigned & y);

/**
 * @brief permet de déplacer le curseur dans la fenêtre mingl
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @param param: structure de variable gérer par la fonction main
 * @param curs2: booléen permettant de savoir si il y a une case sélectionné ou non
 * @bug certaines détections sont mal placées
 * @authors A.Casali, P-A.Rigat
 */
void faitUnMouvementMinGL (CMatrice & mat, MinGL & window, size_t & numLigne,
                          size_t & numCol, unsigned & nbDeplacement, CMyParam & param,
                          bool & curs2);

/**
 * @brief affiche la tête de Baptiste avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineBaptiste (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche la tête d'Alex avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineAlex (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche la tête de Pierre-André avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessinePierre (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche la tête de Cyril avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCyril (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche la tête d'Arnaud avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineArnaud (MinGL & window, const unsigned & x, const unsigned & y);

/**
 * @brief affiche la tête de A.Casali avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCasali (MinGL & window, const unsigned & x, const unsigned & y);

#endif // AFFICHAGEMINGL_H
