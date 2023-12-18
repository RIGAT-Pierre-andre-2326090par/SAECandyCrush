#include <iostream>
#include <type.h>
#include <cst.h>
#include <affichage.h>
#include <mingl/mingl.h>

using namespace std;

//initialisation de la grille de jeu
void initMat (CMatrice & mat, const size_t & nbLignes = 10,
              const size_t & nbColonnes = 10,
              const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    mat.resize(nbLignes); // Ajuste le nombre de ligne de la matrice
    for (size_t i = 0 ; i < nbLignes ; ++i) mat[i].resize(nbColonnes); // Ajuste le nombre de colonne de la matrice
    for (size_t i = 0 ; i < nbLignes ; ++i){
        for (size_t j = 0 ; j < nbColonnes ; ++j){
            mat[i][j] = (rand()%nbMax)+1; //L'élément de la matrice sera une valeur comprise entre 1 et le nbMax
        }
    }
}

//renvoie un nombre random différent de ceux passer en paramètre
unsigned nouvRdm(unsigned & nb1, unsigned & nb2, const unsigned & nbMax){
    unsigned rdm = (rand()%nbMax)+1;
    while(rdm == nb1 || rdm == nb2)
        rdm = (rand()%nbMax)+1; // tant que rdm est égal à nb1 ou nb2, rdm "change" de valeur
    return rdm;
}

//initialisation de la grille de jeu avec maximum 2 nombre aligné
void initMatV2 (CMatrice & mat, const size_t & nbLignes = 10,
               const size_t & nbColonnes = 10,
               const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){
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

void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                     const size_t & numColonne, const size_t & combien){
    for (size_t j (numColonne); j < numColonne + combien; ++j){
        for (size_t i (numLigne); i > 0; --i){
            mat [i][j] = mat[i-1][j];
        }
        mat [0][j] =  KAIgnorer;
    }
}

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
                cout << "une explosion horizontal, une !" << endl;
                score += 10 * (combienALaSuite - 2);
            }
        }
    }
    return auMoinsUneExplosion;
}

void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){
    for (size_t i (numLigne); i < numLigne + combien; ++i){
        for (size_t j (numColonne); j > combien - 1; --j){
            mat [i][j] = mat[i][j - combien];
        }
        mat [i][0] =  KAIgnorer;
    }
}

bool detectionExplositionUneBombeVerticale (CMatrice & mat, unsigned & score){
    bool auMoinsUneExplosion (false);
    for (size_t numLigne (0); numLigne < mat.size(); ++numLigne){
        for (size_t numCol (0); numLigne < mat[numLigne].size(); ++numCol){
            if (KAIgnorer == mat [numLigne][numCol]) continue;
            size_t combienALaSuite (1);
            while (numLigne < mat.size() &&
                   mat[numLigne][numCol] == mat[numLigne + combienALaSuite][numCol])
                ++combienALaSuite;
            //si on a au moins 3 chiffres identiques a la suite
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                explositionUneBombeVerticale (mat, numLigne, numCol, combienALaSuite);
                cout << "une explosion vertical, une !" << endl;
                score += 10 * (combienALaSuite - 2);
                afficheMatriceV1(mat);
            }

        }
    }
    return auMoinsUneExplosion;
}

void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer,
                        const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    for (unsigned i = 0 ; i < mat.size() ; ++i){
        for (unsigned j = 0 ; j < mat[i].size() ; ++j){
            if (mat[i][j] == vid) {
                unsigned Haut = mat[i + 1][j];
                unsigned Cote = mat[i][j + 1];
                mat[i][j] = nouvRdm(Haut, Cote, nbMax); // le contenu de la case est différent de Haut et Cote
            }
        }
    }
}

bool detectionExplositionBombe (CMatrice & mat, unsigned & score) {

    bool act (/*detectionExplositionUneBombeVerticale(mat, score) or*/
              detectionExplositionUneBombeHorizontale(mat, score));
    return act;
}

bool detectionExplositionBombeV2 (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                               const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice){

    bool act (/*detectionExplositionUneBombeVerticale(mat, score) or*/
             detectionExplositionUneBombeHorizontale(mat, score));
    if (act) remplaceVideParRdm(mat, vid, plusGrandNb);
    return act;
}

void zeroVidSousNb (CMatrice & mat, const unsigned & vid = KAIgnorer) {
    for (unsigned i = 0 ; i < mat.size() - 1 ; ++i) {
        for (unsigned j = 0 ; j < mat[0].size() ; ++j) {
            if (mat[i][j] != vid && mat[i + 1][j] == vid)
                swap(mat[i][j],mat[i + 1][j]);
        }
    }
}

//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 3   ***************************/
//***********************************************************************************/

void faitUnMouvement (CMatrice & mat, const char & deplacment, const size_t & numLigne,
                      const size_t & numCol) {

    size_t nouvellePositionLigne (numLigne), nouvellePositionColonne (numCol);
    switch (tolower(deplacment)) {
    case 'a':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != 0) ++nouvellePositionColonne;
        break;
    case 'z':
        if (numLigne != 0) ++nouvellePositionLigne;
        break;
    case 'e':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'd':
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'c':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'x':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        break;
    case 'w':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        if (numCol != 0) ++nouvellePositionColonne;
        break;
    case 'q':
        if (numCol != 0) ++nouvellePositionColonne;
        break;
    default:
        cout<<"Tu choisis A ou Z ou E ou Q ou D ou X ou C ou V pour déplacer le curseur"<<endl;
        break;
    }
    swap(mat[numLigne][numCol],mat[numLigne+nouvellePositionLigne][numCol+nouvellePositionColonne]);
}

void faitUnMouvementV2 (CMatrice & mat, const char & deplacment, size_t & numLigne,
                        size_t & numCol) {

    size_t nouvellePositionLigne (numLigne), nouvellePositionColonne (numCol);
    switch (tolower(deplacment)) {
    case 'c':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
        break;
    case 'x':
        if (numLigne < mat.size() - 1) ++nouvellePositionLigne;
        break;
    case 'w':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
        break;
    case 'q':
        if (numCol != 0) --nouvellePositionColonne;
        break;
    case 'a':
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol != 0) --nouvellePositionColonne;
        break;
    case 'z':
        if (numLigne != 0) --nouvellePositionLigne;
        break;
    case 'e':
        if (numLigne != 0) --nouvellePositionLigne;
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
        break;
    case 'd':
        if (numCol < mat[0].size() - 1) ++nouvellePositionColonne;
        break;
    case 's':
        char inp;
        cin >> inp;
        switch(tolower(inp)){
        case 'x':
            if (numLigne != 0) swap(mat[numLigne][numCol],mat[numLigne + 1][numCol]);
            break;
        case 'd':
            if (numCol != mat[0].size() - 1) swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
            break;
        case 'z':
            if (numLigne != mat.size() - 1) swap(mat[numLigne][numCol],mat[numLigne - 1][numCol]);
            break;
        case 'q':
            if (numCol != 0) swap(mat[numLigne][numCol],mat[numLigne][numCol - 1]);
            break;
        default:
            cout<<"Tu choisis Z ou Q ou D ou X"<<endl;
            break;
        }
        break;
    default:
        cout<<"Tu choisis A ou Z ou E ou Q ou D ou X ou C ou V pour déplacer le curseur ou S pour dé"<<endl;
        break;
    }
    numCol = nouvellePositionColonne;
    numLigne = nouvellePositionLigne;
}

int ppalExo01 (){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV0 (mat);
    //detectionExplositionUneBombeHorizontale (mat);
    return 0;
}

int ppalExo02 (unsigned & score){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV1 (mat);
    detectionExplositionUneBombeHorizontale (mat, score);
    detectionExplositionUneBombeVerticale (mat, score);
    afficheMatriceV1 (mat);
    return 0;
}

int ppalExo03 (unsigned & score){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV1 (mat);
    while (detectionExplositionUneBombeHorizontale (mat, score)) {
        mat[5][8] = 4;
        afficheMatriceV1 (mat);
    }
    return 0;
}

int ppalExo04 (unsigned & score){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    detectionExplositionUneBombeHorizontale (mat, score);
    detectionExplositionUneBombeVerticale (mat, score);
    afficheMatriceV2 (mat);
    //condition de victoire a trouver
    while (true) {
        cout << "Fait un mouvement ";
        cout << "numero de ligne : ";
        size_t numLigne = 1;
        cout << numLigne;
        cout << ", numero de colonne : ";
        size_t numCol = 1;
        cout << numCol;
        cout << ", Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
        char deplacement;
        cin >> deplacement;
        faitUnMouvementV2 (mat, deplacement, numLigne, numCol);
        detectionExplositionUneBombeHorizontale (mat, score);
        detectionExplositionUneBombeVerticale (mat, score);
        afficheMatriceV2 (mat);
    }
    return 0;
}

int partiNumberCrush(unsigned & score){
    CMatrice mat;
    initMat(mat);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        zeroVidSousNb(mat);
        while (detectionExplositionBombe(mat, score)) continue;
        afficheMatriceV3 (mat, numLigne, numCol);
        cout << "Score : " << score << endl;
        if (score >= 100) break;
        cout << "Fait un mouvement ";
        cout << "numero de ligne : ";
        cout << numLigne + 1;
        cout << ", numero de colonne : ";
        cout << numCol + 1 << endl;
        cout << "Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
        char deplacement;
        cin >> deplacement;
        faitUnMouvementV2 (mat, deplacement, numLigne, numCol);
    }
    return 0;
}

int partiCasaliCrush(unsigned & score, unsigned & nbDeplacement){
    CMatrice mat;
    unsigned nbL = 10;
    unsigned nbC = 5;
    initMatV2(mat, nbL, nbC, KPlusGrandNombreDansLaMatriceCasaliCrush);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        zeroVidSousNb(mat);
        while (detectionExplositionBombeV2(mat, score)) continue;
        afficheMatriceV3 (mat, numLigne, numCol);
        cout << "Score : " << score << endl;
        if (score >= 100) break;
        cout << "Fait un mouvement ";
        cout << "numero de ligne : ";
        cout << numLigne + 1;
        cout << ", numero de colonne : ";
        cout << numCol + 1 << endl;
        cout << "Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
        char deplacement;
        cin >> deplacement;
        faitUnMouvementV2 (mat, deplacement, numLigne, numCol, nbDeplacement);
    }
    return 0;
}

int main() {
    srand(time(NULL));
    unsigned score=0;
    unsigned nbDeplacement=15;
    //unsigned deplacement=0;

    // ---------Exercice 2 -----------------//
    //    clearScreen();

    //    CMatrice mat (10, CVLine (10, kEmpty));
    //    mat [0][mat.size()-1] = kTokenPlayer1;
    //    mat [mat.size()-1][0] = kTokenPlayer2;
    //    showMatrix(mat);
    //-------------------------------------//
    //return 0;

    // ---------Exercice 1 -----------------//
    //return ppalExo01(score);
    //--------------------------------------//

    // ---------Exercice 2 -----------------//
    //return ppalExo02(score);
    //-------------------------------------//

    // ---------Exercice 3 -----------------//
    //return ppalExo03(score);
    //-------------------------------------//

    // ---------Exercice 4 -----------------//
    //return ppalExo04(score);
    //-------------------------------------//

    //return partiNumberCrush(score);

    return partiCasaliCrush(score, nbDeplacement);

    //return 0;
}
