#include <affichage.h>
#include <mingl/mingl.h>

#include <mingl/shape/rectangle.h>
#include <mingl/shape/circle.h>
#include <mingl/shape/line.h>
#include <mingl/shape/triangle.h>
#include <mingl/gui/text.h>
#include <mingl/gui/sprite.h>

using namespace std;

// Ce document cpp est un document regroupant toutes les fonctions/procédures d'affichage de la matrice dans une fenêtre MinGL, permettant de réduire le code du main

/**
 * @brief Affichage de la matrice avec des cercles de couleurs différentes, représentant le contenu des cases
 * @param Mat: matrice gérée par une fonction appelée par la fonction main
 * @param window: fenêtre active où le texte va être affiché
 * @authors A.Nurdin, A.Goncalves, P-A.Rigat
 */
void  afficheMatriceMingl (const CMatrice & Mat, MinGL & window) {
    for (size_t i = 0 ; i < Mat.size() ; ++i) {
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j) {
            if (Mat[i][j]==1)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KCyan); // Si l'élément = 1, alors la couleur sera cyan
            else if (Mat[i][j]==2)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KRed); // Si l'élément = 2, alors la couleur sera rouge
            else if (Mat[i][j]==3)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KGreen); // Si l'élément = 3, alors la couleur sera verte
            else if (Mat[i][j]==4)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KYellow); // Si l'élément = 4, alors la couleur sera jaune
            else if (Mat[i][j]==5)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            else if (Mat[i][j]==6)
                window << nsShape::Circle(nsGraphics::Vec2D(j * 50 + 25, i * 50 + 25), 25, nsGraphics::KBlue); // Si l'élément = 6, alors la couleur sera bleu
        }
    }
}

/**
 * @brief Dessine un rectangle de couleur bleue avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine du rectangle
 * @param y: ordonnée de l'origine du rectangle
 * @author P-A.Rigat
 */
void dessinerRectangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Rectangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KBlue);
}

/**
 * @brief Dessine un cercle de couleur rouge avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine du cercle
 * @param y: ordonnée de l'origine du cercle
 * @author P-A.Rigat
 */
void dessinerCercle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Circle(nsGraphics::Vec2D(x + 25, y + 25), 25, nsGraphics::KRed);
}

/**
 * @brief Dessine un triangle de couleur verte avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine du triangle
 * @param y: ordonnée de l'origine du triangle
 * @author P-A.Rigat
 */
void dessinerTriangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 25, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KGreen);
}

/**
 * @brief Dessine une croix de couleur jaune avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de la croix
 * @param y: ordonnée de l'origine de la croix
 * @author P-A.Rigat
 */
void dessinerCroix (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Line(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KYellow, 5.f);
    window << nsShape::Line(nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::KYellow, 5.f);
}

/**
 * @brief Dessine une étoile de couleur violette avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'étoile
 * @param y: ordonnée de l'origine de l'étoile
 * @author P-A.Rigat
 */
void dessinerEtoile (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 25, y), nsGraphics::Vec2D(x + 35, y + 30), nsGraphics::Vec2D(x + 14, y + 30), nsGraphics::KPurple);
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y + 20), nsGraphics::Vec2D(x + 32, y + 20), nsGraphics::Vec2D(x + 25, y + 38), nsGraphics::KPurple);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 50, y + 20), nsGraphics::Vec2D(x + 18, y + 20), nsGraphics::Vec2D(x + 25, y + 38), nsGraphics::KPurple);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 42 , y + 50), nsGraphics::Vec2D(x + 14, y + 30), nsGraphics::Vec2D(x + 32, y + 20), nsGraphics::KPurple);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 7, y + 50), nsGraphics::Vec2D(x + 18, y + 20), nsGraphics::Vec2D(x + 35, y + 30), nsGraphics::KPurple);
}

/**
 * @brief Dessine un curseur (composé de 4 triangles) de couleur blanche avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine du curseur
 * @param y: ordonnée de l'origine du curseur
 * @author P-A.Rigat
 */
void dessinerCurseur (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x, y + 10), nsGraphics::Vec2D(x + 10, y), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 40, y), nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x + 50, y + 10), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x, y + 40), nsGraphics::Vec2D(x + 10, y + 50), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::Vec2D(x + 50, y + 40), nsGraphics::Vec2D(x + 40, y + 50), nsGraphics::KWhite);
}

/**
 * @brief affiche le texte txt en blanc aux coordonnées x, y
 * @param window: fenêtre active où le texte va être affiché
 * @param txt: texte à afficher
 * @param x: abscisse de l'origine du texte
 * @param y: ordonnée de l'origine du texte
 * @author P-A.Rigat
 */
void afficheText(MinGL & window, const string & txt, const unsigned & x, const unsigned & y) {
    window << nsGui::Text(nsGraphics::Vec2D(x, y), txt, nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
}

/**
 * @brief Permet de déplacer le curseur dans la fenêtre mingl
 * @param mat: matrice gérée par une fonction appelé par la fonction main
 * @param numLigne: abscisse du curseur
 * @param numCol: ordonnée du curseur
 * @param nbDeplacement: nombre de déplacements restants, gérée par la fonction main
 * @param param: structure de variable gérée par la fonction main
 * @param curs2: booléen permettant de savoir s'il y a une case sélectionnée ou non
 * @bug certaines détections sont mal placées
 * @authors A.Casali, P-A.Rigat
 */
void faitUnMouvementMinGL (CMatrice & mat, MinGL & window, size_t & numLigne,
                          size_t & numCol, unsigned & nbDeplacement, CMyParam & param,
                          bool & curs2) {

    size_t nouvellePositionLigne (numLigne), nouvellePositionColonne (numCol);
    if (window.isPressed({param.mapParamChar["toucheBasDroite"], false})) {
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
    }
    else if (window.isPressed({param.mapParamChar["toucheBas"], false})) {
        if (numLigne < mat.size() - 1) ++nouvellePositionLigne;
        if (curs2) {
            swap(mat[numLigne][numCol],mat[numLigne + 1][numCol]);
            --nbDeplacement;
            curs2 = !curs2;
        }
    }
    else if (window.isPressed({param.mapParamChar["toucheGaucheBas"], false})) {
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
    }
    else if (window.isPressed({param.mapParamChar["toucheGauche"], false})) {
        if (numCol != 0) --nouvellePositionColonne;
        if (curs2) {
            swap(mat[numLigne][numCol],mat[numLigne][numCol - 1]);
            --nbDeplacement;
            curs2 = !curs2;
        }
    }
    else if (window.isPressed({param.mapParamChar["toucheHautGauche"], false})) {
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
    }
    else if (window.isPressed({param.mapParamChar["toucheHaut"], false})) {
        if (numLigne != 0) --nouvellePositionLigne;
        if (curs2) {
            swap(mat[numLigne][numCol],mat[numLigne - 1][numCol]);
            --nbDeplacement;
            curs2 = !curs2;
        }
    }
    else if ((window.isPressed({param.mapParamChar["toucheDroiteHaut"], false}))) {
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
    }
    else if (window.isPressed({param.mapParamChar["toucheDroite"], false})) {
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
        if (curs2) {
            swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
            --nbDeplacement;
            curs2 = !curs2;
        }
    }
    else if (window.isPressed({param.mapParamChar["toucheSelect"], false})) {
        curs2 = true;
    }
    else afficheText(window, "Tu dois choisir entre A ou Z ou E ou Q ou D ou X ou C ou W ou S pour déplacer le curseur", 510, 0);

    numCol = nouvellePositionColonne;
    numLigne = nouvellePositionLigne;
}

/**
 * @brief Affiche la tête de Baptiste avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineBaptiste (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/batist.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête d'Alex avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineAlex (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/alex.si2", nsGraphics::Vec2D(x, y));
}
/**
 * @brief affiche la tête de Pierre-André avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessinePierre (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/peterandrew.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête de Cyril avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCyril (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/dric.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête d'Arnaud avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineArnaud (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/arno.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête de A.Casali avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessinée
 * @param x: abscisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCasali (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/casali.si2", nsGraphics::Vec2D(x, y));
}
