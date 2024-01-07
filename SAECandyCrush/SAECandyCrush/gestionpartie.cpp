#include <iostream>
#include <fstream>

#include <affichage.h>

using namespace std;

/**
 * @brief procédure initialisant les paramètres du joueur au sein du jeu
 * @param param: structure de variable gérer par la fonction main
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

    // variable limitant le nombre de niveaux
    param.mapParamUnsigned["nbNiveaux"] = 16;

    //taille de la grille pour chaque niveau
    param.mapParamVecUnsigned["nbColonnesV"] = {10, 8, 10, 8, 9, 7, 9, 7, 6, 5, 6, 6, 4, 3, 4, 3};
    param.mapParamVecUnsigned["nbLignesV"] = {10, 10, 8, 8, 9, 9, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3};

    //des variables utiles pour chaque niveau
    param.mapParamVecUnsigned["nbMaxV"] = {5, 4, 3, 2, 5, 4, 3, 2, 5, 4, 3, 2, 5, 4, 3, 2};
    param.mapParamVecUnsigned["scoreMaxV"] = {150, 200, 200, 250, 250, 300, 300, 350, 350, 400, 400, 450, 450, 500, 500, 550, 550, 600};
    param.mapParamVecUnsigned["deplacementMaxV"] = {15, 14, 12, 13, 11, 10, 8, 9, 7, 7, 6, 6, 6, 5, 5, 4};
}

/**
 * @brief procédure permettande d'enlever le caractère ':' d'une chaine de caractère passer en paramètre
 * @param str: chaine de caractère à traiter
 * @return la chaine de caractère sans le caractère ':'
 * @author P-A.Rigat
 */
string strSansDeuxPts(const string & str) {
    string tmp;
    for (unsigned i = 0 ; i < str.size() ; ++i)
        if (str[i] != ':') tmp.push_back(str[i]);
    return tmp;
}

/**
 * @brief procédure permettant de charger les paramètres de jeu d'un joueur depuis un fichier yaml
 * @param params: structure de variable gérer par la fonction main
 * @param fichier: chemin du fichier yaml cible
 * @authors A.Casali, P-A.Rigat
 */
void chargerParametre(CMyParam & params, const string & fichier){
    ifstream ifs (fichier);
    if (!ifs) return;
    string cle;
    while (ifs>>cle){
        cle = strSansDeuxPts(cle);
        if(params.mapParamUnsigned.find(cle) != params.mapParamUnsigned.end()){
            unsigned val;
            ifs >> val;
            params.mapParamUnsigned[cle]=val;
            cout << cle << ": " << val << endl;
        }
        else if (params.mapParamChar.find(cle) != params.mapParamChar.end()){
            char val;
            ifs >> val;
            params.mapParamChar[cle]=val;
            cout << cle << ": " << val << endl;
        }
        else if (params.mapParamVecUnsigned.find(cle) != params.mapParamVecUnsigned.end()){
            vector <unsigned> val;
            string valTmp;
            string tmp;
            getline(ifs,tmp);
            for (unsigned i = 0; i < tmp.size(); ++i){
                if (tmp[i] >= 48 && tmp[i] <= 57) valTmp.push_back(tmp[i]);
                else if (tmp[i] == ',') {
                    val.push_back(stoul(valTmp));
                    valTmp = "";
                }
            }
            params.mapParamVecUnsigned[cle] = val;
            cout << cle << ": " << val[0] << "...(vec)" << endl;
        }
        else {
            string tmp;
            getline(ifs, tmp);
            cout << tmp << "(marche pas)" << endl;
        }
    }
}

/**
 * @brief fonction qui renvoie un nouveau nombre aléatoire entre 1 et nbMax différent de nb1 et nb2
 * @param nb1: premier nombre dont le nouveaux nombre aléatoire doit être différent
 * @param nb2: second nombre dont le nouveaux nombre aléatoire doit être différent
 * @param nbMax: le nouveaux nombre aléatoire doit être inclut entre 1 et nbMax
 * @return rdm: nombre aléatoire entre 1 et nbMax différent de nb1 et nb2
 * @author P-A.Rigat
 */
unsigned nouvRdm(unsigned & nb1, unsigned & nb2, const unsigned & nbMax){
    unsigned rdm = (rand()%nbMax)+1;
    while(rdm == nb1 || rdm == nb2)
        rdm = (rand()%nbMax)+1; // tant que rdm est égal à nb1 ou nb2, rdm change de valeur
    return rdm;
}

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
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du premier nombre servant de repère pour l'explosion de la bombe
 * @param numColonne: ordonnée du premier nombre servant de repère pour l'explosion de la bombe
 * @param combien: nombre de chiffre aligné horizontalement
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
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @return true si il y a au moins une explosion, false sinon
 * @authors A.Casali, P-A.Rigat
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
            // si on a 5 chiffres identiques à la suite, on créer un 6 et on fait pété
            if (combienALaSuite >= 5) {
                auMoinsUneExplosion = true;
                explositionUneBombeHorizontale(mat, numLigne, numCol, combienALaSuite);
                mat[numLigne][numCol] = 6;
                score += 10 * (combienALaSuite - 2);
            }
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
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param numLigne: absisse du premier nombre servant de repère pour l'explosion de la bombe
 * @param numColonne: ordonnée du premier nombre servant de repère pour l'explosion de la bombe
 * @param combien: nombre de chiffre aligné verticalement
 * @authors P-A.Rigat, A.Nurdin
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
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @return true si il y a au moins un explosion, false sinon
 * @authors P-A.Rigat, A.Nurdin
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
            // si on a 5 chiffres identiques à la suite, on créer un 6 et on fait pété
            if (combienALaSuite >= 5) {
                auMoinsUneExplosion = true;
                explositionUneBombeVerticale (mat, numLigne, numCol, combienALaSuite);
                mat[numLigne][numCol] = 6;
                score += 10 * (combienALaSuite - 2);
            }
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
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @param nbMax: les nombres aléatoire sont compris entre 1 et nbMax(par défaut 4)
 * @author P-A.Rigat
 */
void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer,
                        const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    for (unsigned i = 0 ; i < mat.size() - 1 ; ++i){
        for (unsigned j = 0 ; j < mat[i].size() - 1; ++j){ // pour chaque case de chaque ligne de la matrice
            if (mat[i][j] == vid) { // si la case est vide,
                mat[i][j] = (rand()%nbMax)+1; //la case a un nouveau contenu
            }
        }
    }
}

/**
 * @brief fonction permettant de déplacer vers le bas tous les éléments flottant après une explosion jusqu'à être côte à côte d'un élément juste en dessous d'eux ou au fond de la matrice si il n'y a pas d'éléments en dessous
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @return true si un ou plusieurs élément on été déplacé, false sinon
 * @author P-A.Rigat
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
 * @brief fonction détectant si une explosion verticale ou horizontale est présente dans la matrcie à l'aide des deux autres fonctions de détection
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param score: entier naturel permettant de savoir si le joueur a gagner, gérer par la fonction main
 * @param vid: valeur d'une case vide(par défaut 0)
 * @param plusGrandNb: les nombres aléatoire sont compris entre 1 et plusGrandNb(par défaut 4)
 * @return true si il y a eu au moins une explosion vertical ou horizontal, false sinon
 * @author P-A.Rigat
 */
bool detectionExplositionBombe (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                               const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice){

    bool act (detectionExplositionUneBombeVerticale(mat, score) or
             detectionExplositionUneBombeHorizontale(mat, score));
    if (act) remplaceVideParRdm(mat, vid, plusGrandNb);
    zeroVidSousNb(mat);
    return act;
}

/**
 * @brief procédure permettant au joueur de se déplacer dans la grille et de déplacer l'élément qu'il a séléctionné
 * @param mat: matrice gérer par une fonction appelé par la fonction main
 * @param deplacment: caractère indiquant l'action choisi
 * @param numLigne: absisse du curseur
 * @param numCol: ordonnée du curseur
 * @param nbDeplacement: nombre de déplacement restant, gérer par la fonction main
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
