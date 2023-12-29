#define FPS_LIMIT 10

#include <iostream>
#include <type.h>
#include <cst.h>
#include <affichage.h>
#include <fstream>
#include <mingl/mingl.h>
#include <thread>

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/gui/text.h"

using namespace std;

/**
 * @brief procédure initialisant les paramètres du joueur au sein du jeu
 * @param param
 * @authors A.Casali, P-A.Rigat
 */
void initParams (CMyParam & param)
{
    //touche du joueur
    param.mapParamChar["toucheHaut"] = 'z';
    param.mapParamChar["toucheGauche"] = 'q';
    param.mapParamChar["toucheBas"] = 'x';
    param.mapParamChar["toucheDroite"] = 'd';
    param.mapParamChar["toucheHautGauche"] = 'a';
    param.mapParamChar["toucheGaucheBas"] = 'w';
    param.mapParamChar["toucheBasDroite"] = 'c';
    param.mapParamChar["toucheDroiteHaut"] = 'e';
    param.mapParamChar["toucheSelect"] = 's';

    //taille de la grille - on suppose que c'est un rectangle
    param.mapParamUnsigned["nbColonnes"] = 10;
    param.mapParamUnsigned["nbLignes"] = 10;

    //
    param.mapParamUnsigned["nbMax"] = 5;
    param.mapParamUnsigned["scoreMax"] = 350;
    param.mapParamUnsigned["deplacementMax"] = 15;
}

/**
 * @brief procédure permettant de charger les paramètres de jeu d'un joueur depuis un fichier yaml
 * @param params
 * @param fichier
 * @author A.Casali
 */
void chargerParametre(CMyParam & params, const string & fichier){
    ifstream ifs (fichier);
    if (!ifs) return;
    string cle;
    while (ifs>>cle){
        if(params.mapParamUnsigned.find(cle) != params.mapParamUnsigned.end()){
            char deuxPts;
            ifs >> deuxPts;
            unsigned val;
            ifs >> val;
            params.mapParamUnsigned[cle]=val;
        }
        else if (params.mapParamChar.find(cle) != params.mapParamChar.end()){
            char deuxPts;
            ifs >> deuxPts;
            char val;
            ifs >> val;
            params.mapParamChar[cle]=val;
        }
        else {
            string tmp;
            getline(ifs, tmp);
        }
    }
}

/**
 * @brief fonction permettant de génerer un nouveau nombre aléatoire
 * @param nb1
 * @param nb2
 * @param nbMax
 */
//renvoie un nombre random différent de ceux passer en paramètre
unsigned nouvRdm(unsigned & nb1, unsigned & nb2, const unsigned & nbMax){
    unsigned rdm = (rand()%nbMax)+1;
    while(rdm == nb1 || rdm == nb2)
        rdm = (rand()%nbMax)+1; // tant que rdm est égal à nb1 ou nb2, rdm "change" de valeur
    return rdm;
}

/**
 * @brief procédure générant une matrice carrée remplie de nombre aléatoire
 * @param mat
 * @param nbMax
 */
//initialisation de la grille de jeu avec maximum 2 nombre aligné
void initMat (CMatrice & mat, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice,
             const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10){
    mat.resize(nbLignes); // Ajuste le nombre de ligne de la matrice
    for (unsigned i = 0 ; i < nbLignes ; ++i) mat[i].resize(nbColonnes); // Ajuste le nombre de colonne de la matrice
    for (unsigned i = 0 ; i < nbLignes ; ++i){
        for (unsigned j = 0 ; j < nbColonnes ; ++j){
            unsigned comboHaut = 0;
            unsigned comboCote = 0;
            if (i > 1 && mat[i - 1][j] == mat[i - 2][j]) comboHaut = mat[i - 1][j];
            // comboHaut vaut 0 si les 2 nombres au dessus sont différent ou sinon le contenu de la case au dessus
            if (j > 1 && mat[i][j - 1] == mat[i][j - 2]) comboCote = mat[i][j - 1];
            // comboCote vaut 0 si les 2 nombres à côté sont différent ou sinon le contenu de la case à côté
            mat[i][j] = nouvRdm(comboCote, comboHaut, nbMax); // le contenu de la case est différent de comboHaut et comboCote
        }
    }
}

/**
 * @brief procédure modifiant la matrice en supprimant des éléments identiques alignés horizontalement par nombre de 3 à 5
 * @param mat
 * @param numLigne
 * @param numColonne
 * @param combien
 * @author A.Casali
 */
void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){
    for (size_t j (numColonne); j < numColonne + combien; ++j){
        for (size_t i (numLigne); i > 0; --i){
            mat [i][j] = mat[i-1][j];
        }
        mat [0][j] =  KAIgnorer;
    }
}

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés horizontalement dans la matrice
 * @param mat
 * @param score
 * @return
 * @author A.Casali
 */
bool detectionExplositionUneBombeHorizontale (CMatrice & mat, unsigned & score){
    bool auMoinsUneExplosion (false);
    for (size_t numLigne (0); numLigne < mat.size(); ++numLigne){
        for (size_t numCol (0); numCol < mat[numLigne].size(); ++numCol){
            if (KAIgnorer == mat [numLigne][numCol]) continue;
            size_t combienALaSuite (1);
            while (numCol < mat[numLigne].size() &&
                   mat[numLigne][numCol] == mat[numLigne][numCol + combienALaSuite])
                ++combienALaSuite;
            //si on a au moins 3 chiffres identiques a la suite
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                explositionUneBombeHorizontale (mat, numLigne, numCol, combienALaSuite);
                score += 10 * (combienALaSuite - 2);
            }
        }
    }
    return auMoinsUneExplosion;
}

/**
 * @brief procédure modifiant la matrice en supprimant des éléments identiques alignés verticalement par nombre de 3 à 5
 * @param mat
 * @param numLigne
 * @param numColonne
 * @param combien
 */
void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,
                                  const size_t & numColonne, const size_t & combien){
    for (size_t j (numLigne); j < numLigne + combien; ++j){
        for (size_t i (numLigne); i > 0; --i){
            mat [i][j] = mat[i][j-1];}
        mat [j][numColonne] =  KAIgnorer;}
}

/**
 * @brief fonction détectant la présence de 3 à 5 éléments identiques alignés verticalement dans la matrice
 * @param mat
 * @param score
 * @return
 */
bool detectionExplositionUneBombeVerticale (CMatrice & mat, unsigned & score){
    bool auMoinsUneExplosion (false);
    for (size_t numCol (0); numCol < mat[0].size(); ++numCol) {
        for (size_t numLigne (0); numLigne < mat.size(); ++numLigne) {
            if (KAIgnorer == mat [numLigne][numCol]) continue;
            size_t combienALaSuite (1);
            while (numLigne + combienALaSuite < mat.size() &&
                   mat[numLigne][numCol] == mat[numLigne + combienALaSuite][numCol])
                ++combienALaSuite;
            //si on a au moins 3 chiffres identiques a la suite
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                explositionUneBombeVerticale (mat, numLigne, numCol, combienALaSuite);
                score += 10 * (combienALaSuite - 2);
            }
        }
    }
    return auMoinsUneExplosion;
}

/**
 * @brief remplace toutes les cases vides par des nombres aléatoires
 * @param mat
 * @param vid
 * @param nbMax
 */
void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer,
                        const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    for (unsigned i = 0 ; i < mat.size() ; ++i){
        for (unsigned j = 0 ; j < mat[i].size() ; ++j){ // pour chaque case de chaque ligne de la matrice
            if (mat[i][j] == vid) { // si la case est pleine,
                unsigned Haut = mat[i + 1][j]; // le contenu de la case du haut
                unsigned Cote = mat[i][j + 1]; // le contenu de la case sur le côté
                mat[i][j] = nouvRdm(Haut, Cote, nbMax); // le contenu de la case est différent de Haut et Cote
            }
        }
    }
}

/**
 * @brief fonction détectant si une explosion verticale ou horizontale est présente dans la matrcie à l'aide des deux autres fonctions de détection
 * @param mat
 * @param score
 * @param vid
 * @param plusGrandNb
 * @return act
 */
bool detectionExplositionBombe (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                               const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice){

    bool act (detectionExplositionUneBombeVerticale(mat, score) or
             detectionExplositionUneBombeHorizontale(mat, score));
    if (act) remplaceVideParRdm(mat, vid, plusGrandNb);
    return act;
}

/**
 * @brief fonction permettant de déplacer vers le bas tous les éléments flottant après une explosion jusqu'à être côte à côte d'un élément juste en dessous d'eux ou au fond de la matrice si il n'y a pas d'éléments en dessous
 * @param mat
 * @param vid
 * @return auMoinsUnMov
 */
bool zeroVidSousNb (CMatrice & mat, const unsigned & vid = KAIgnorer) {
    bool auMoinsUnMov = false;
    for (unsigned i = 0 ; i < mat.size() - 1 ; ++i) {
        for (unsigned j = 0 ; j < mat[0].size() ; ++j) {
            if (mat[i][j] != vid && mat[i + 1][j] == vid){
                swap(mat[i][j],mat[i + 1][j]);
                auMoinsUnMov = true;
            }
        }
    }
    return auMoinsUnMov;
}

/**
 * @brief procédure permettant au joueur de se déplacer dans la grille et de déplacer l'élément qu'il a séléctionné
 * @param mat
 * @param deplacment
 * @param numLigne
 * @param numCol
 * @param nbDeplacement
 */
void faitUnMouvement (CMatrice & mat, const char & deplacment, size_t & numLigne,
                     size_t & numCol, unsigned & nbDeplacement, CMyParam & param) {

    size_t nouvellePositionLigne (numLigne), nouvellePositionColonne (numCol);
    if (tolower(deplacment) == param.mapParamChar["toucheBasDroite"]) {
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheBas"]) {
        if (numLigne < mat.size() - 1) ++nouvellePositionLigne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheGaucheBas"]) {
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheGauche"]) {
        if (numCol != 0) --nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheHautGauche"]) {
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheHaut"]) {
        if (numLigne != 0) --nouvellePositionLigne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheDroiteHaut"]) {
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheDroite"]) {
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
    }
    else if (tolower(deplacment) == param.mapParamChar["toucheSelect"]) {
        char inp;
        cin >> inp;
        if (tolower(inp) == param.mapParamChar["toucheBas"]) {
            if (numLigne != 0){
                swap(mat[numLigne][numCol],mat[numLigne + 1][numCol]);
                --nbDeplacement;
            }
        }
        if (tolower(inp) == param.mapParamChar["toucheDroite"]) {
            if (numCol != mat[0].size() - 1){
                swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
                --nbDeplacement;
            }
        }
        if (tolower(inp) == param.mapParamChar["toucheHaut"]) {
            if (numLigne != mat.size() - 1){
                swap(mat[numLigne][numCol],mat[numLigne - 1][numCol]);
                --nbDeplacement;
            }
        }
        if (tolower(inp) == param.mapParamChar["toucheGauche"]) {
            if (numCol != 0) {
                swap(mat[numLigne][numCol],mat[numLigne][numCol - 1]);
                --nbDeplacement;
            }
        }
        else cout<<"Tu dois choisir entre Z ou Q ou D ou X"<<endl;
    }
    else cout<<"Tu dois choisir entre A ou Z ou E ou Q ou D ou X ou C ou W ou S pour déplacer le curseur"<<endl;

    numCol = nouvellePositionColonne;
    numLigne = nouvellePositionLigne;
}

/**
 * @brief fonction lançant une version lite du candy crush pour les tests
 * @param score
 * @param nbDeplacement
 * @return 0
 */
int partiNumberCrush(unsigned & score, unsigned & nbDeplacement, CMyParam & param){
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;
    while(true){
        while (detectionExplositionBombe(mat, score) || zeroVidSousNb(mat))
            continue;
        afficheMatriceV2 (mat);
        cout << "Score : " << score << endl;
        cout << "Nombre de déplacement restant : " <<  nbDeplacement << endl;
        if (score >= param.mapParamUnsigned["scoreMax"]){
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
        faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement, param);
    }
    return 0;
}

/**
 * @brief fonction de lancement du jeu du candy crush
 * @param score
 * @param nbDeplacement
 * @return 0
 */
int partiCasaliCrush(unsigned & score, unsigned & nbDeplacement, CMyParam & param){
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;
    while(true){
        while (detectionExplositionBombe(mat, score) || zeroVidSousNb(mat))
            continue;
        afficheMatriceV3 (mat, numLigne, numCol);
        cout << "Score : " << score << endl;
       cout << "Nombre de déplacement restant : " <<  nbDeplacement << endl;
        if (score >= param.mapParamUnsigned["scoreMax"]){
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
        faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement, param);
    }
    return 0;
}

/********ici débute le Mingl*********/

void dessinerRectangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Rectangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KBlue);
}

void dessinerCercle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Circle(nsGraphics::Vec2D(x + 25, y + 25), 25, nsGraphics::KRed);
}

void dessinerTriangle (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 25, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KGreen);
}

void dessinerCroix (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Line(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::KYellow, 5.f);
    window << nsShape::Line(nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x, y + 50), nsGraphics::KYellow, 5.f);
}

void dessinerCurseur (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x, y + 10), nsGraphics::Vec2D(x + 10, y), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 40, y), nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x + 50, y + 10), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x, y + 40), nsGraphics::Vec2D(x + 10, y + 50), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::Vec2D(x + 50, y + 40), nsGraphics::Vec2D(x + 40, y + 50), nsGraphics::KWhite);
}

void dessinerCurseur2 (MinGL & window, const unsigned & x, const unsigned & y) {
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y), nsGraphics::Vec2D(x, y + 10), nsGraphics::Vec2D(x + 10, y), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 40, y), nsGraphics::Vec2D(x + 50, y), nsGraphics::Vec2D(x + 50, y + 10), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x, y + 50), nsGraphics::Vec2D(x, y + 40), nsGraphics::Vec2D(x + 10, y + 50), nsGraphics::KWhite);
    window << nsShape::Triangle(nsGraphics::Vec2D(x + 50, y + 50), nsGraphics::Vec2D(x + 50, y + 40), nsGraphics::Vec2D(x + 40, y + 50), nsGraphics::KWhite);
}

void afficheText(MinGL & window, const string & txt, const unsigned & x, const unsigned & y) {
    window << nsGui::Text(nsGraphics::Vec2D(x, y), txt, nsGraphics::KWhite);
}

/**
 * @brief permet de déplacer le curseur dans la fenètre mingl
 * @param mat
 * @param numLigne
 * @param numCol
 * @param nbDeplacement
 * @param param
 */
void faitUnMouvementMinGL (CMatrice & mat, MinGL & window, size_t & numLigne,
                          size_t & numCol, unsigned & nbDeplacement, CMyParam & param,
                          bool & curs2, unsigned & time) {

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
    else if (window.isPressed({param.mapParamChar["toucheSelect"], false}))
        curs2 = !curs2;
    else afficheText(window, "Tu dois choisir entre A ou Z ou E ou Q ou D ou X ou C ou W ou S pour déplacer le curseur", 510, 0);

    numCol = nouvellePositionColonne;
    numLigne = nouvellePositionLigne;
}

/**
 * @brief partiMinglCrush
 * @param score
 * @param nbDeplacement
 * @param param
 * @return 0
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
    while (nbDeplacement > 0 || score < param.mapParamUnsigned["scoreMax"] || window.isOpen() )
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On affiche la grille puis le curseur
        afficheMatriceV3(mat,numLigne,numCol);
        for (unsigned i = 0 ; i < mat.size() ; ++i) {
            for (unsigned j = 0 ; j < mat[i].size() ; ++j) {
                if (mat[i][j] == 1) dessinerRectangle(window, j * 50, i * 50);
                if (mat[i][j] == 2) dessinerCercle(window, j * 50, i * 50);
                if (mat[i][j] == 3) dessinerTriangle(window, j * 50, i * 50);
                if (mat[i][j] == 4) dessinerCroix(window, j * 50, i * 50);
            }
        }
        dessinerCurseur(window, numCol * 50, numLigne * 50);

        // on affiche les scores et le nombre de déplacement restant
        afficheText(window, "coucou", 0, 0);

        // si il y a des combos, on supprime les combos et on continue
        if (detectionExplositionBombe(mat,score)) continue;

        // On gère les déplacements du curseur et les mouvements dans la grille
        faitUnMouvementMinGL(mat, window, numLigne, numCol, nbDeplacement, param, curs2, time);

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

int partiMinglTeteCrush (unsigned & score, unsigned & nbDeplacement, CMyParam & param) {
    // Initialise le système
    MinGL window("NumberCrushT", nsGraphics::Vec2D(500, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Instancie le sprite
    /*nsGui::Sprite alex("¡", nsGraphics::Vec2D(195,195)); // faudrait remplacer ¡ par le chemin des photos
    nsGui::Sprite pierre("¡", nsGraphics::Vec2D(195,195));
    nsGui::Sprite cyril("¡", nsGraphics::Vec2D(195,195));
    nsGui::Sprite arnaud("¡", nsGraphics::Vec2D(195,195));
    nsGui::Sprite bapt("¡", nsGraphics::Vec2D(195,195));*/

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //On initialise la partie de Number Crush
    CMatrice mat;
    initMat(mat, param.mapParamUnsigned["nbMax"],
            param.mapParamUnsigned["nbLignes"],
            param.mapParamUnsigned["nbColonnes"]);
    size_t numCol = (param.mapParamUnsigned["nbLignes"] / 2) - 1;
    size_t numLigne = (param.mapParamUnsigned["nbColonnes"] / 2) - 1;


    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (nbDeplacement > 0 || score > 0 || window.isOpen() )
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On affiche la grille puis le curseur
        afficheMatriceV3(mat,numLigne,numCol);
        for (unsigned i = 0 ; i < mat.size() ; ++i) {
            for (unsigned j = 0 ; j < mat[i].size() ; ++j) { // Les ? c'est le temps de savoir qui va ou.
                /*if (mat[i][j] == 1) ?;
                if (mat[i][j] == 2) ?;
                if (mat[i][j] == 3) ?;
                if (mat[i][j] == 4) ?;*/
            }
        }
        dessinerCurseur(window, numCol * 50, numLigne * 50);

        // On gère les déplacements du curseur et les mouvements dans la grille
        //faitUnMouvementMinGL(mat, window, numLigne, numCol, nbDeplacement, param);

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
 * @brief main.cpp
 * @return 0
 */
int main() {
    srand(time(NULL));

    CMyParam param;
    initParams(param);
    //chargerParametre(param, "../SAECandyCrush/build.yaml");

    unsigned score=0;
    unsigned nbDeplacement=param.mapParamUnsigned["deplacementMax"];
    unsigned mode ; // Initialisation du mode de jeu, soit avec MinGl, soit avec le terminal
    bool test = false;
    while (test == false)
    {
        cout <<" Sur quel mode de jeu voulez vous jouer ? :" << endl << endl << "1 : mode avec MinGl" << '\t' << "2 : mode avec les nombres" << endl ;
        cin >> mode ;
        if (mode ==1 || mode==2) test = true ;
        else cout << "Ce mode de jeu n'existe pas rééssayez !" << endl;
    }
    if (mode == 1) return partiMinglCrush(score, nbDeplacement, param);
    else if (mode == 2) return partiCasaliCrush(score, nbDeplacement, param); //Lance la partie sur le terminal
    else return 0;
}
