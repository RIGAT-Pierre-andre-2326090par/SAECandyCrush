#define FPS_LIMIT 10

#include <iostream>
#include <thread>

#include <affichagemingl.h>
#include <affichage.h>
#include <gestionpartie.h>
#include <tp.h>

#include <mingl/gui/sprite.h>

using namespace std;

/**
 * @brief fonction lançant une version lite du candy crush pour les tests
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @return 0
 * @authors A.Nurdin, A.Goncalves, P-A.Rigat, C.Tamine, B.Gaston
 */
int partiNumberCrush(unsigned & score, unsigned & nbDeplacement, CMyParam & param){
    unsigned i = 0 ;
    while (i < param.mapParamUnsigned["nbNiveaux"]) {
        CMatrice mat;
        initMat(mat, param.mapParamVecUnsigned["nbMaxV"][i],
                param.mapParamVecUnsigned["nbLignesV"][i],
                param.mapParamVecUnsigned["nbColonnesV"][i]);
        size_t numCol = (param.mapParamVecUnsigned["nbLignesV"][i] / 2) - 1;
        size_t numLigne = (param.mapParamVecUnsigned["nbColonnesV"][i] / 2) - 1;
        nbDeplacement = param.mapParamVecUnsigned["deplacementMaxV"][i];
        score=0;
        while(true){
            while (detectionExplositionBombe(mat, score, KAIgnorer, param.mapParamVecUnsigned["nbMax"][i]) || zeroVidSousNb(mat))
                continue;
            afficheMatriceV2 (mat);
            cout << "Score : " << score << endl;
            cout << "Nombre de déplacement restant : " <<  nbDeplacement << endl;
            if (score >= param.mapParamVecUnsigned["scoreMaxV"][0]){
                cout << "Tu as gagné !" << endl;
                    break;
            }
            if (nbDeplacement ==0){
                cout << "Tu n'as plus de déplacements, payer 5€ pour 5 déplacements supplémentaires ?(signé EA)" << endl;
                    break;
            }
            cout << "Fait un mouvement ";
            cout << "numero de ligne : ";
            cout << numLigne + 1;
            cout << ", numero de colonne : ";
            cout << numCol + 1 << endl;
            cout << "Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
            char deplacement;
            cin >> deplacement;
            if (detectionExplositionBombe(mat,score, KAIgnorer, param.mapParamVecUnsigned["nbMaxV"][i])) continue;
            else {
                // On gère les déplacements du curseur et les mouvements dans la grille
                faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement, param);
            }
        }
        if (nbDeplacement == 0 || score >= param.mapParamVecUnsigned["scoreMaxV"][i]) {
            cout << "tu as perdu..." << endl;
            break;
        }
        else ++i;
    }
    return 0;
}

/**
 * @brief fonction de lancement du jeu du candy crush
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
 * @return 0
 * @authors A.Nurdin, A.Goncalves, P-A.Rigat, C.Tamine, B.Gaston
 */
int partiCasaliCrush(unsigned & score, unsigned & nbDeplacement, CMyParam & param){
    unsigned i = 0 ;
    while (i < param.mapParamUnsigned["nbNiveaux"]) {
        CMatrice mat;
        initMat(mat, param.mapParamVecUnsigned["nbMaxV"][i],
                param.mapParamVecUnsigned["nbLignesV"][i],
                param.mapParamVecUnsigned["nbColonnesV"][i]);
        size_t numCol = (param.mapParamVecUnsigned["nbLignesV"][i] / 2) - 1;
        size_t numLigne = (param.mapParamVecUnsigned["nbColonnesV"][i] / 2) - 1;
        nbDeplacement = param.mapParamVecUnsigned["deplacementMaxV"][i];
        score=0;
        while(true){
            afficheMatriceV3 (mat, numLigne, numCol);
            cout << "Score : " << score << endl;
           cout << "Nombre de déplacement restant : " <<  nbDeplacement << endl;
            if (score >= param.mapParamVecUnsigned["scoreMaxV"][i]){
                cout << "Tu as gagné !" << endl;
                    break;
            }
            if (nbDeplacement ==0){
                cout << "Tu n'as plus de déplacements, payer 5€ pour 5 déplacements supplémentaires ?(signé EA)" << endl;
                    break;
            }
            cout << "Fait un mouvement ";
            cout << "numero de ligne : ";
            cout << numLigne + 1;
            cout << ", numero de colonne : ";
            cout << numCol + 1 << endl;
            cout << "Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
            char deplacement;
            cin >> deplacement;
            if (detectionExplositionBombe(mat,score, KAIgnorer, param.mapParamVecUnsigned["nbMaxV"][i])) continue;
            else {
                // On gère les déplacements du curseur et les mouvements dans la grille
                faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement, param);
            }

        }
        if (nbDeplacement == 0 || score >= param.mapParamVecUnsigned["scoreMaxV"][i]) {
            cout << "tu as perdu..." << endl;
            break;
        }
        else ++i;
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
int partiMinglCrush (unsigned & score, unsigned & nbDeplacement, CMyParam & param) {
    // Initialise le système
    MinGL window("NumberCrush", nsGraphics::Vec2D(500, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // Pour chaque niveau
    unsigned i = 0 ;
    while (i < param.mapParamUnsigned["nbNiveaux"]) {

        //On initialise la partie de Number Crush
        CMatrice mat;
        initMat(mat, param.mapParamVecUnsigned["nbMaxV"][i],
                param.mapParamVecUnsigned["nbLignesV"][i],
                param.mapParamVecUnsigned["nbColonnesV"][i]);
        size_t numCol = (param.mapParamVecUnsigned["nbLignesV"][i] / 2) - 1;
        size_t numLigne = (param.mapParamVecUnsigned["nbColonnesV"][i] / 2) - 1;
        nbDeplacement = param.mapParamVecUnsigned["deplacementMaxV"][i];
        score=0;

        //quelque variable utile
        bool curs2 = false;
        unsigned time = 0;

        // On fait tourner la boucle tant que la fenêtre est ouverte
        while (nbDeplacement > 0 && score <= param.mapParamVecUnsigned["scoreMaxV"][i] && window.isOpen() )
        {
            // Récupère l'heure actuelle
            chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

            // On efface la fenêtre
            window.clearScreen();

            // si le timer est suppérieur à 0, continue
            if (time > 0) continue;

            // On affiche la grille puis le curseur dans le terminal
            afficheMatriceV3(mat, numLigne, numCol);

            // on affiche le score et le nombre de déplacement restant dans le terminal
            cout << "Score = " << score << endl
                 << "Deplacement Restant = " << nbDeplacement << endl;

            // On affiche la grille puis le curseur dans une interface MinGl
            for (unsigned i = 0 ; i < mat.size() ; ++i) {
                for (unsigned j = 0 ; j < mat[i].size() ; ++j) {
                    if (mat[i][j] == 1) dessinerRectangle(window, j * 50, i * 50);
                    if (mat[i][j] == 2) dessinerCercle(window, j * 50, i * 50);
                    if (mat[i][j] == 3) dessinerTriangle(window, j * 50, i * 50);
                    if (mat[i][j] == 4) dessinerCroix(window, j * 50, i * 50);
                    if (mat[i][j] == 5) dessinerEtoile(window, j * 50, i * 50);
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
                if (detectionExplositionBombe(mat,score, KAIgnorer, param.mapParamVecUnsigned["nbMaxV"][i])) continue;
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
        if (nbDeplacement == 0 || score >= param.mapParamVecUnsigned["scoreMaxV"][i]) {
            cout << "tu as perdu..." << endl;
            break;
        }
        else ++i;
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

    // Pour chaque niveau
    unsigned i = 0 ;
    while (i < param.mapParamUnsigned["nbNiveaux"]) {

        //On initialise la partie de Number Crush
        CMatrice mat;
        initMat(mat, param.mapParamVecUnsigned["nbMaxV"][i],
                param.mapParamVecUnsigned["nbLignesV"][i],
                param.mapParamVecUnsigned["nbColonnesV"][i]);
        size_t numCol = (param.mapParamVecUnsigned["nbLignesV"][i] / 2) - 1;
        size_t numLigne = (param.mapParamVecUnsigned["nbColonnesV"][i] / 2) - 1;
        nbDeplacement = param.mapParamVecUnsigned["deplacementMaxV"][i];
        score=0;

        //quelque variable utile
        bool curs2 = false;
        unsigned time = 0;

        // On fait tourner la boucle tant que la fenêtre est ouverte
        while (nbDeplacement > 0 && score <= param.mapParamVecUnsigned["scoreMaxV"][i] && window.isOpen() )
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
            afficheMatriceMingl(mat, window);
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
            if (detectionExplositionBombe(mat,score, KAIgnorer, param.mapParamVecUnsigned["nbMaxV"][i])) continue;
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
        if (nbDeplacement == 0 || score >= param.mapParamVecUnsigned["scoreMaxV"][i]) {
            cout << "tu as perdu..." << endl;
            break;
        }
        else ++i;
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

    // Pour chaque niveau
    unsigned i = 0 ;
    while (i < param.mapParamUnsigned["nbNiveaux"]) {

        // On initialise la partie de Number Crush
        CMatrice mat;
        initMat(mat, param.mapParamVecUnsigned["nbMaxV"][i],
                param.mapParamVecUnsigned["nbLignesV"][i],
                param.mapParamVecUnsigned["nbColonnesV"][i]);
        size_t numCol = (param.mapParamVecUnsigned["nbLignesV"][i] / 2) - 1;
        size_t numLigne = (param.mapParamVecUnsigned["nbColonnesV"][i] / 2) - 1;
        nbDeplacement = param.mapParamVecUnsigned["deplacementMaxV"][i];
        score=0;

        // Quelques variables utiles
        bool curs2 = false;
        //unsigned time = 0;

        // On fait tourner la boucle tant que la fenêtre est ouverte ou que le joueur n'a pas gagné ni perdu
        while (nbDeplacement > 0 && score <= param.mapParamVecUnsigned["scoreMaxV"][i] && window.isOpen())
        {
            // Récupère l'heure actuelle
            chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

            // On efface la fenêtre
            window.clearScreen();

            // On affiche le fond
            window << nsGui::Sprite ("../SAECandyCrush/im/fond.si2", nsGraphics::Vec2D(0, 0));

            // On affiche la grille, le score et le nombre de déplacement restant dans le terminal
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

            // On affiche le score et le nombre de déplacement restant dans une interface MinGl
            string strScore = "Score = ";
            strScore += to_string(score);
            afficheText(window, strScore, 10, 520);

            string strDeplacement = "Deplacement restant = ";
            strDeplacement += to_string(nbDeplacement);
            afficheText(window, strDeplacement, 10, 540);

            // Si il y a des combos, on supprime les combos et on continue
            if (detectionExplositionBombe(mat,score, KAIgnorer, param.mapParamVecUnsigned["nbMaxV"][i])) continue;
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
        if (nbDeplacement == 0 || score >= param.mapParamVecUnsigned["scoreMaxV"][i]) {
            cout << "tu as perdu..." << endl;
            break;
        }
        else ++i;
    }
    return 0;
}

/**
 * @brief la fonction main permettant de choisir le mode de jeux
 * @return 0
 * @authors A.Nurdin, P-A.Rigat, C.Tamine
 */
int main() {
    srand(time(NULL));

    CMyParam param;
    initParams(param);
    chargerParametre(param, "../SAECandyCrush/build.yaml");

    unsigned score=0;
    unsigned nbDeplacement=param.mapParamUnsigned["deplacementMax"];
    unsigned mode ; // Initialisation du mode de jeu, soit avec MinGl, soit avec le terminal
    bool test = false;
    while (test == false)
    {
        cout <<" Sur quel mode de jeu voulez-vous jouer ? :" << endl << endl << "1 : mode avec MinGl" << '\t' << "2 : mode avec les nombres" << endl ;
        cin >> mode ;
        if (mode >= 1 && mode <= 5) test = true ;
        else {
            clearScreen();
            cout << "Ce mode de jeu n'existe pas, rééssayez !" << endl;
        }
    }
    if (mode == 1) return partiMinglCrush2(score, nbDeplacement, param); // Lance la partie avec MinGL
    else if (mode == 2) return partiCasaliCrush(score, nbDeplacement, param); //Lance la partie sur le terminal
    else if (mode == 3) return tp(); // Lance le programme du tp
    else if (mode == 4) return partiMinglTeteCrush(score, nbDeplacement, param); // Une version bonus :)
    else if (mode == 5) return partiMinglCrush(score, nbDeplacement, param);
    else if (mode == 6) return partiNumberCrush(score, nbDeplacement, param);
    else return 0;
}
