#define FPS_LIMIT 60

#include <type.h>
#include <cst.h>
#include <affichage.h>
#include <mingl/mingl.h>

#include <mingl/shape/rectangle.h>
#include <mingl/shape/circle.h>
#include <mingl/shape/line.h>
#include <mingl/shape/triangle.h>
#include <mingl/gui/text.h>
#include <mingl/gui/sprite.h>

using namespace std;

// ce fichier contient toutes les fonctions MinGL utile au main

/**
 * @brief dessine un rectangle de couleur bleu avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du rectangle
 * @param y: ordonnée de l'origine du rectangle
 * @author P-A.Rigat
 */
void dessinerRectangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Rectangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KBlue);
}

/**
 * @brief dessine un cercle de couleur rouge avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du cercle
 * @param y: ordonnée de l'origine du cercle
 * @author P-A.Rigat
 */
void dessinerCercle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Circle(nsGraphics::Vec2D(x + 25, y + 25), 25, nsGraphics::KRed);
}

/**
 * @brief dessine un triangle de couleur verte avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du triangle
 * @param y: ordonnée de l'origine du triangle
 * @author P-A.Rigat
 */
void dessinerTriangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 25, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KGreen);
}

/**
 * @brief dessine une croix de couleur jaune avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de la croix
 * @param y: ordonnée de l'origine de la croix
 * @author P-A.Rigat
 */
void dessinerCroix (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Line(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KYellow, 5.f);
    window << nsShape::Line(nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::KYellow, 5.f);
}

/**
 * @brief dessine un curseur(composé de 4 triangles) de couleur blanche avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine du curseur
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
 * @brief affiche le texte txt en blanc au coordonné x, y
 * @param window: fenêtre active où le texte va être affiché
 * @param txt: texte à afficher
 * @param x: absisse de l'origine du texte
 * @param y: ordonnée de l'origine du texte
 * @author P-A.Rigat
 */
void afficheText(MinGL & window, const string & txt, const unsigned & x, const unsigned & y) {
    window << nsGui::Text(nsGraphics::Vec2D(x, y), txt, nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
}

/**
 * @brief permet de déplacer le curseur dans la fenêtre mingl
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @param param: structure de variable gérer par la fonction main
 * @param curs2: booléen permettant de savoir si il y a une case sélectionné ou non
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
        curs2 = !curs2;
    }
    else afficheText(window, "Tu dois choisir entre A ou Z ou E ou Q ou D ou X ou C ou W ou S pour déplacer le curseur", 510, 0);

    numCol = nouvellePositionColonne;
    numLigne = nouvellePositionLigne;
}

/**
 * @brief affiche la tête de Baptiste avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineBaptiste (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/batist.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête d'Alex avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineAlex (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/alex.si2", nsGraphics::Vec2D(x, y));
}
/**
 * @brief affiche la tête de Pierre-André avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessinePierre (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/peterandrew.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête de Cyril avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCyril (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/dric.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête d'Arnaud avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineArnaud (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/arno.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief affiche la tête de A.Casali avec comme origine x, y
 * @param window: fenêtre active où la forme va être dessiné
 * @param x: absisse de l'origine de l'image
 * @param y: ordonnée de l'origine de l'image
 * @author P-A.Rigat
 */
void dessineCasali (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsGui::Sprite ("../SAECandyCrush/im/casali.si2", nsGraphics::Vec2D(x, y));
}

/**
 * @brief gère une fenêtre MinGL ainsi qu'une partie de NumberCrush avec un affichage de forme
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @param param: structure de variable gérer par la fonction main
 * @return 0
 * @bug pas de forme pour le nombre 5
 * @authors A.Goncalves, P-A.Rigat
 */
int partiMinglCrush (unsigned & score, unsigned & nbDeplacement, CMyParam & param) {
    // Initialise le système
    MinGL window("NumberCrush", nsGraphics::Vec2D(500, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //On initialise la partie de Number Crush
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;

    //quelque variable utile
    bool curs2 = false;
    unsigned time = 0;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (nbDeplacement > 0 && score <= param.mapParamUnsigned["scoreMax"] && window.isOpen() )
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // si le timer est suppérieur à 0, continue
        if (time > 0) continue;

        // On affiche la grille puis le curseur dans le terminal
        afficheMatriceV3(mat, numLigne, numCol);

        // On affiche la grille puis le curseur dans une interface MinGl
        for (unsigned i = 0 ; i < mat.size() ; ++i) {
            for (unsigned j = 0 ; j < mat[i].size() ; ++j) {
                if (mat[i][j] == 1) dessinerRectangle(window, j * 50, i * 50);
                if (mat[i][j] == 2) dessinerCercle(window, j * 50, i * 50);
                if (mat[i][j] == 3) dessinerTriangle(window, j * 50, i * 50);
                if (mat[i][j] == 4) dessinerCroix(window, j * 50, i * 50);
            }
        }
        dessinerCurseur(window, numCol * 50, numLigne * 50);

        // on affiche le score et le nombre de déplacement restant dans le terminal
        cout << "Score = " << score << endl
             << "Deplacement Restant = " << nbDeplacement << endl;

        // on affiche le score et le nombre de déplacement restant dans une interface MinGl
        string strScore = "Score = ";
        strScore += to_string(score);
        afficheText(window, strScore, 10, 520);

        string strDeplacement = "Deplacement restant = ";
        strDeplacement += to_string(nbDeplacement);
        afficheText(window, strDeplacement, 10, 540);

        // si il y a des combos, on supprime les combos et on continue
        if (detectionExplositionBombe(mat,score)) continue;

        // On gère les déplacements du curseur et les mouvements dans la grille
        faitUnMouvementMinGL(mat, window, numLigne, numCol, nbDeplacement, param, curs2);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}

/**
 * @brief gère une fenêtre MinGL ainsi qu'une partie de NumberCrush avec un affichage de forme
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @param param: structure de variable gérer par la fonction main
 * @return 0
 * @authors A.Goncalves, P-A.Rigat
 */
int partiMinglCrush2 (unsigned & score, unsigned & nbDeplacement, CMyParam & param) {
    // Initialise le système
    MinGL window("NumberCrush", nsGraphics::Vec2D(500, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //On initialise la partie de Number Crush
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;

    //quelque variable utile
    bool curs2 = false;
    unsigned time = 0;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (nbDeplacement > 0 && score <= param.mapParamUnsigned["scoreMax"] && window.isOpen() )
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // si le timer est suppérieur à 0, continue
        if (time > 0) continue;

        // On affiche la grille puis le curseur dans le terminal
        afficheMatriceV3(mat, numLigne, numCol);

        // On affiche la grille puis le curseur dans une interface MinGl
        afficheMatriceV0(mat, window);
        dessinerCurseur(window, numCol * 50, numLigne * 50);

        // on affiche le score et le nombre de déplacement restant dans le terminal
        cout << "Score = " << score << endl
             << "Deplacement Restant = " << nbDeplacement << endl;

        // on affiche le score et le nombre de déplacement restant dans une interface MinGl
        string strScore = "Score = ";
        strScore += to_string(score);
        afficheText(window, strScore, 10, 520);

        string strDeplacement = "Deplacement restant = ";
        strDeplacement += to_string(nbDeplacement);
        afficheText(window, strDeplacement, 10, 540);

        // si il y a des combos, on supprime les combos et on continue
        if (detectionExplositionBombe(mat,score)) continue;

        // On gère les déplacements du curseur et les mouvements dans la grille
        faitUnMouvementMinGL(mat, window, numLigne, numCol, nbDeplacement, param, curs2);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}

/**
 * @brief gère une fenêtre ainsi qu'une partie de NumberCrush avec les têtes de l'équipes et de A.Casali
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @param param: structure de variable gérer par la fonction main
 * @return 0
 * @authors A.Goncalves, P-A.Rigat
 */
int partiMinglTeteCrush (unsigned & score, unsigned & nbDeplacement, CMyParam & param) {
    // Initialise le système
    MinGL window("NumberCrushT", nsGraphics::Vec2D(500, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //On initialise la partie de Number Crush
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;

    // Quelque variable utile
    bool curs2 = false;
    //unsigned time = 0;

    // On fait tourner la boucle tant que la fenêtre est ouverte ou que le joueur n'a pas gagné ni perdu
    while (nbDeplacement > 0 || score > 0 || window.isOpen() )
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // on affiche le fond
        window << nsGui::Sprite ("../SAECandyCrush/im/fond.si2", nsGraphics::Vec2D(0, 0));

        // on affiche la grille, le score et le nombre de déplacement restant dans le terminal
        afficheMatriceV3(mat,numLigne,numCol);
        cout << "Score = " << score << endl
             << "Deplacement Restant = " << nbDeplacement << endl;

        // On affiche la grille puis le curseur dans une interface MinGL
        for (unsigned i = 0 ; i < mat.size() ; ++i) {
            for (unsigned j = 0 ; j < mat[i].size() ; ++j) {
                if (mat[i][j] == 1) dessineAlex(window, j * 50, i * 50);
                if (mat[i][j] == 2) dessineArnaud(window, j * 50, i * 50);
                if (mat[i][j] == 3) dessineBaptiste(window, j * 50, i * 50);
                if (mat[i][j] == 4) dessineCyril(window, j * 50, i * 50);
                if (mat[i][j] == 5) dessinePierre(window, j * 50, i * 50);
                if (mat[i][j] == 6) dessineCasali(window, j * 50, i * 50);
            }
        }
        dessinerCurseur(window, numCol * 50, numLigne * 50);

        // on affiche le score et le nombre de déplacement restant dans une interface MinGl
        string strScore = "Score = ";
        strScore += to_string(score);
        afficheText(window, strScore, 10, 520);

        string strDeplacement = "Deplacement restant = ";
        strDeplacement += to_string(nbDeplacement);
        afficheText(window, strDeplacement, 10, 540);

        // si il y a des combos, on supprime les combos et on continue
        if (detectionExplositionBombe(mat,score)) continue;
        else {
            // On gère les déplacements du curseur et les mouvements dans la grille
            faitUnMouvementMinGL(mat, window, numLigne, numCol, nbDeplacement, param, curs2);
        }

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}
