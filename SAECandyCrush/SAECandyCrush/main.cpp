#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

//****************************************** *****************************************/
//***********************    R1.01 – Prog#10 Exercice 1   ***************************/
//***********************************************************************************/


void clearScreen () {
    cout << "\033[H\033[2J";
}

const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
const unsigned KBGNoir    (40);
const unsigned KBGRouge   (41);
const unsigned KGBBleu    (44);
const unsigned KBGCyan    (46);

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}


//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 2   ***************************/
//***********************************************************************************/
/*
 *
*/

typedef ushort contenueDUneCase;
typedef vector <contenueDUneCase> CVLigne; // un type représentant une ligne de la grille
typedef vector <CVLigne> CMatrice; // un type représentant la grille

const contenueDUneCase KAIgnorer = 0;
const contenueDUneCase KPlusGrandNombreDansLaMatrice = 4;

//initialisation de la grille de jeu
void initMat (CMatrice & mat, const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10,
             const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    mat.resize(nbLignes);
    for (unsigned i = 0 ; i < nbLignes ; ++i) mat[i].resize(nbColonnes);
    for (unsigned i = 0 ; i < nbLignes ; ++i){
        for (unsigned j = 0 ; j < nbColonnes ; ++j){
            mat[i][j] = rand()%(nbMax + 1);
        }
    }
}

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
void  afficheMatriceV0 (const CMatrice & Mat) {
    clearScreen();
    couleur (KReset);
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            cout <<  Mat[i][j]<<' ';
        }
        cout << endl ;
    }
}

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur
//pour signifier que la case est a KAIgnorer
void  afficheMatriceV1 (const CMatrice & Mat) {
    clearScreen();
    couleur (44);
    cout << "* ";
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << "  ";
    }
    cout << endl ;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << "  ";
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset);
            cout <<  Mat[i][j] << ' ';
        }
        cout << endl ;
    }
}
//.
// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
//pour signifier que la case est a KAIgnorer
void  afficheMatriceV2 (const CMatrice & Mat) {
    clearScreen();
    couleur (44);
    cout << "* ";
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << i << ' ';
    }
    cout << endl ;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << i;
        couleur(KReset);
        cout << ' ';
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset);
            cout <<  Mat[i][j] << ' ';
        }
        cout << endl ;
    }
}


//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 2   ***************************/
//***********************************************************************************/

void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){

    for (unsigned i = 0 ; i < numLigne - combien ; ++i){
        mat[numLigne + i][numColonne] = mat[numLigne + i + 3][numColonne];
    }
    for (unsigned i = 0 ; i < combien ; ++i){
        mat[numLigne + i][numColonne] = KAIgnorer;
    }
}

bool detectionExplositionUneBombeHorizontale (CMatrice & mat){
    bool auMoinsUneExplosion (false);
    for (unsigned numLigne = 0 ; numLigne < mat.size() ; ++numLigne){
        for (unsigned numCol = 0 ; numCol < mat[numLigne].size() ; ++numCol){
            size_t combienALaSuite (1);
            if (numLigne != 0){
                if (mat[numLigne][numCol] == mat[numLigne-1][numCol]){
                    ++combienALaSuite;
                }
            }
            //si on a aun moins 3 chiffres identiques a la suite
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                cout << "on a une suite en position numLigne = " << numLigne
                     << "; colonne = " << numCol
                     << "; sur  " << combienALaSuite << " cases" << endl;
                cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                afficheMatriceV1(mat);
                        explositionUneBombeHorizontale (mat, numLigne, numCol, combienALaSuite);
                        cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                        afficheMatriceV1(mat);
            }
        }
    }
    return auMoinsUneExplosion;
}

void explositionUneBombeVertical    (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien){

    for (unsigned i = 0 ; i < numLigne - combien ; ++i){
        mat[numColonne + i][numLigne] = mat[numColonne + i + 3][numLigne];
    }
    for (unsigned i = 0 ; i < combien ; ++i){
        mat[numColonne + i][numLigne] = KAIgnorer;
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
        //TODO
        break;
    case 'z':
        //TODO
        break;
        //TODO : completer les autres mouvements
    default:
        cout<<"Tu choisis A ou Z ou E  ou Q ou D ou X ou C ou V"<<endl;
        break;
    }
    //faire la permutaion entre les 2 cases
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
        size_t numLigne;
        cout << numLigne;
        cout << "numero de colonne : ";
        size_t numCol;
        cout << numCol;
        cout << "Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
        char deplacement;
        cin >> deplacement;
        faitUnMouvement (mat, deplacement, numLigne, numCol);
        detectionExplositionUneBombeHorizontale (mat);
        afficheMatriceV2 (mat);
    }
    return 0;
}


int main() {

    // ---------Exercice 2 -----------------//
    //    clearScreen();

    //    CMatrice mat (10, CVLine (10, kEmpty));
    //    mat [0][mat.size()-1] = kTokenPlayer1;
    //    mat [mat.size()-1][0] = kTokenPlayer2;
    //    showMatrix(mat);
    //-------------------------------------//
    //return 0;704008

    // ---------Exercice 2 -----------------//
    //return ppalExo02();
    //-------------------------------------//

    // ---------Exercice 3 -----------------//
    //return ppalExo03();
    //-------------------------------------//

    // ---------Exercice 3 -----------------//
    //return ppalExo04();
    //-------------------------------------//

    CMatrice mat;
    initMat(mat);
    afficheMatriceV2(mat);
    if (detectionExplositionUneBombeHorizontale(mat)){

    }

    return 0;
}
