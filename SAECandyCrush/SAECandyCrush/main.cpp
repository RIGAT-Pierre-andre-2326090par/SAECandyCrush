#include <iostream>
#include <vector>
#include <iomanip>
#include <type.h>
#include <cst.h>
#include <mingl/mingl.h>
#include <affichage.h>

using namespace std;

//****************************************** *****************************************/
//***********************    R1.01 – Prog#10 Exercice 1   ***************************/
//***********************************************************************************/

/*void clearScreen () {
    cout << "\033[H\033[2J";
}



void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}*/

//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 2   ***************************/
//***********************************************************************************/


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

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche


// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur
//pour signifier que la case est a KAIgnorer


// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
//pour signifier que la case est a KAIgnorer

// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
// pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent


//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 2   ***************************/
//***********************************************************************************/


void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){
    for (size_t j (numColonne); j < numColonne + combien; ++j){
        for (size_t i (numLigne); i>0; --i){
            mat [i][j] = mat[i-1][j];
        }
        mat [0][j] =  KAIgnorer;
    }
}

bool detectionExplositionUneBombeHorizontale (CMatrice & mat){
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
        }
    }
}
return auMoinsUneExplosion;
}

void detectionExplositionBombe (CMatrice & mat){
    detectionExplositionUneBombeHorizontale(mat);
    //detectionExplositionUneBombeVertical(mat);
}

void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){
    for (unsigned i = 0 ; i < mat.size() ; ++i){
        for (unsigned j = 0 ; j < mat[i].size() ; ++j){
            if (mat[i][j] == vid) mat[i][j] = (rand()%nbMax)+1;
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

int ppalExo01 (){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV0 (mat);
    //detectionExplositionUneBombeHorizontale (mat);
    return 0;
}

int ppalExo02 (){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV1 (mat);
    detectionExplositionUneBombeHorizontale (mat);
    afficheMatriceV1 (mat);
    return 0;
}

int ppalExo03 (){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    afficheMatriceV1 (mat);
    while (detectionExplositionUneBombeHorizontale (mat)) {
        mat[5][8] = 4;
        afficheMatriceV1 (mat);
    }
    return 0;
}

int ppalExo04 (){
    CMatrice mat;
    initMat(mat);
    // affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
    detectionExplositionUneBombeHorizontale (mat);
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
        detectionExplositionUneBombeHorizontale (mat);
        afficheMatriceV2 (mat);
    }
    return 0;
}

int partiNumberCrush(){
    CMatrice mat;
    initMatV2(mat);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        detectionExplositionUneBombeHorizontale (mat);
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
    //return ppalExo01();
    //--------------------------------------//

    // ---------Exercice 2 -----------------//
    return ppalExo02();
    //-------------------------------------//

    // ---------Exercice 3 -----------------//
    //return ppalExo03();
    //-------------------------------------//

    // ---------Exercice 4 -----------------//
    //return ppalExo04();
    //-------------------------------------//

    return partiNumberCrush();

    //return 0;
}
