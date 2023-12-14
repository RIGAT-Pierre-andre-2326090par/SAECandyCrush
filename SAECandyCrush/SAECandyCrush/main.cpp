#include <iostream>
#include <vector>
#include <iomanip>
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
    for (unsigned i = 0 ; i < nbLignes ; ++i) mat[i].resize(nbColonnes); // Ajuste le nombre de colonne de la matrice
    for (unsigned i = 0 ; i < nbLignes ; ++i){
        for (unsigned j = 0 ; j < nbColonnes ; ++j){
            mat[i][j] = (rand()%nbMax)+1; //L'élément de la matrice sera une valeur comprise entre 1 et le nbMax
        }
    }
}


//renvoie un nombre random différent de celui passer en paramètre
unsigned nouvRdm(unsigned & nb, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){
    unsigned rdm = (rand()%nbMax)+1;
    while(rdm == nb) rdm = (rand()%nbMax)+1;
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
            unsigned rdm = (rand()%nbMax)+1; //L'élément de la matrice sera une valeur comprise entre 1 et le nbMax
            if (i > 1 && j > 1 && (mat[i-1][j] == mat[i-2][j] || mat[i][j-1] == mat[i][j-2])
                    && (rdm == mat[i-1][j] || rdm == mat[i][j-1])) mat[i][j] = nouvRdm(rdm);
            else mat[i][j] = rdm;
        }
    }
}



void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                     const size_t & numColonne, const size_t & combien){
    for (size_t j (numColonne); j < numColonne + combien; ++j){
        for (size_t i (numLigne); i>0; --i){
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
                cout << "on a une suite en position numLigne = " << numLigne
                     << "; colonne = " << numCol
                     << "; sur  " << combienALaSuite << " cases" << endl;
                cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                afficheMatriceV2(mat);
                explositionUneBombeHorizontale (mat, numLigne, numCol, combienALaSuite);
                cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                afficheMatriceV2(mat);
                score=score+10;
                cout << "Score : " << score;
            }
        }
    }
    return auMoinsUneExplosion;
}

void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){
    for (size_t i (numLigne); i < numLigne + combien; ++i){
        for (size_t j (numColonne); j>0; --j){
            mat [i][j] = mat[i][j-1];
        }
        mat [i][0] =  KAIgnorer;
    }
}

bool detectionExplositionUneBombeVerticale (CMatrice & mat, unsigned & score){
    bool auMoinsUneExplosion (false);
    for (size_t numCol (0); numCol < mat.size(); ++numCol){
        for (size_t numLigne (0); numLigne < mat[numCol].size(); ++numLigne){
            if (KAIgnorer == mat [numLigne][numCol]) continue;
            size_t combienALaSuite (1);
            while (numLigne < mat[numCol].size() &&
                   mat[numLigne][numCol] == mat[numLigne + combienALaSuite][numCol])
                ++combienALaSuite;
            //si on a au moins 3 chiffres identiques a la suite
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                cout << "on a une suite en position numLigne = " << numLigne
                     << "; colonne = " << numCol
                     << "; sur  " << combienALaSuite << " cases" << endl;
                cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                afficheMatriceV2(mat);
                explositionUneBombeVerticale(mat, numLigne, numCol, combienALaSuite);
                cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                            afficheMatriceV2(mat);
                score=score+10;
                cout << "Score : " << score;
            }
        }
    }
    return auMoinsUneExplosion;
}

void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){
    for (unsigned i = 0 ; i < mat.size() ; ++i){
        for (unsigned j = 0 ; j < mat[i].size() ; ++j){
            if (mat[i][j] == vid) mat[i][j] = (rand()%nbMax)+1;
        }
    }
}

void detectionExplositionBombe (CMatrice & mat, unsigned & score){
    bool act = detectionExplositionUneBombeHorizontale(mat, score);
    bool act = detectionExplositionUneBombeVerticale(mat, score);
    if (act) remplaceVideParRdm(mat);
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
    case 's':
        char inp;
        cin >> inp;
        switch(tolower(inp)){
        case 'z':
            if (numLigne != 0) swap(mat[numLigne][numCol],mat[numLigne + 1][numCol]);
            break;
        case 'd':
            if (numCol != mat[0].size() - 1) swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
            break;
        case 'x':
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
        cout<<"Tu choisis A ou Z ou E ou Q ou D ou X ou C ou V pour déplacer le curseur ou S pour échanger 2 cases"<<endl;
        break;
    }
}

void faitUnMouvementV2 (CMatrice & mat, const char & deplacment, size_t & numLigne,
                        size_t & numCol) {

    size_t nouvellePositionLigne (numLigne), nouvellePositionColonne (numCol);
    switch (tolower(deplacment)) {
    case 'c':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != 0) ++nouvellePositionColonne;
        break;
    case 'x':
        if (numLigne != 0) ++nouvellePositionLigne;
        break;
    case 'w':
        if (numLigne != 0) ++nouvellePositionLigne;
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'q':
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'a':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        if (numCol != mat[0].size() - 1) --nouvellePositionColonne;
        break;
    case 'z':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        break;
    case 'e':
        if (numLigne != mat.size() - 1) --nouvellePositionLigne;
        if (numCol != 0) ++nouvellePositionColonne;
        break;
    case 'd':
        if (numCol != 0) ++nouvellePositionColonne;
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

int ppalExo01 (unsigned & score){
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
    initMatV2(mat);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        detectionExplositionBombe(mat, score);
        afficheMatriceV3 (mat, numLigne, numCol);
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

int main() {
    srand(time(NULL));
    unsigned score=0;
    unsigned deplacement=0;
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

    return partiNumberCrush(score);

    //return 0;
}
