#include <iostream>
#include <vector>

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
const unsigned KMagenta (35);
const unsigned KCyan    (36);
const unsigned KBGNoir    (40);
const unsigned KBGRouge   (41);
const unsigned KGBBleu    (44);
const unsigned KBGCyan    (46);
const unsigned KBGGrisClair(47);

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

//***********************************************************************************/
//***********************    R1.01 – Prog#10 Exercice 2   ***************************/
//***********************************************************************************/

typedef ushort contenueDUneCase;
typedef vector <contenueDUneCase> CVLigne; // un type représentant une ligne de la grille
typedef vector <CVLigne> CMatrice; // un type représentant la grille

const contenueDUneCase KAIgnorer = 0;
const contenueDUneCase KPlusGrandNombreDansLaMatrice = 4;

//initialisation de la grille de jeu
void initMat (CMatrice & mat, const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10,
             const unsigned & nbMax = KPlusGrandNombreDansLaMatrice){

    mat.resize(nbLignes); // Ajuste le nombre de ligne de la matrice
    for (unsigned i = 0 ; i < nbLignes ; ++i) mat[i].resize(nbColonnes); // Ajuste le nombre de colonne de la matrice
    for (unsigned i = 0 ; i < nbLignes ; ++i){
        for (unsigned j = 0 ; j < nbColonnes ; ++j){ //Pour chaque élément de la matrice
            mat[i][j] = (rand()%nbMax)+1; //L'élément de la matrice sera une valeur aléatoire comprise entre 1 et le nbMax
        }
    }
}

//renvoie un nombre aléatoire différent de celui passer en paramètre
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
void  afficheMatriceV0 (const CMatrice & Mat) {
    clearScreen();
    couleur (KReset);
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            if (Mat[i][j]==0) couleur(KReset); // Si l'élément = 0, alors la couleur sera la couleur par défaut du terminal
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j]<<' '; // Affiche la matrice élément par élément
        }
        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
        cout << endl ;
    }
}

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur
//pour signifier que la case est a KAIgnorer
void  afficheMatriceV1 (const CMatrice & Mat) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << "  ";
    }
    cout << ' ' << endl ;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << "  ";
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset); // Enlève la couleur bleue pour l'affiche d'un élément
            if (Mat[i][j]==0) couleur(KReset); // Si l'élément = 0, alors la couleur sera la couleur par défaut du terminal
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j] << ' ';
        }
        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
        cout << endl ;
    }
}

// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
//pour signifier que la case est a KAIgnorer
void  afficheMatriceV2 (const CMatrice & Mat) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    cout << "  ";
    for (size_t i = 0 ; i < Mat.size() ; ++i) cout << ' ' << i + 1;
    cout << endl ;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        if (i + 1 != Mat.size()) cout << ' ' << i + 1;
        else cout << i + 1;
        couleur(KReset);
        cout << ' ';
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset); // Enlève la couleur bleue pour afficher un élément
            if (Mat[i][j]==0) couleur(KReset); // Si l'élément = 0, alors la couleur sera la couleur par défaut du terminal
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j] << ' ';
        }
        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
        cout << endl ;
    }
}

// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur
// pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent
void  afficheMatriceV3 (const CMatrice & Mat, const size_t numLigne, const size_t numCol) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    cout << "  ";
    for (size_t i = 0 ; i < Mat.size() ; ++i) cout << ' ' << i + 1;
    cout << endl ;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        if (i + 1 != Mat.size()) cout << ' ' << i + 1;
        else cout << i + 1;
        couleur(KReset);
        cout << ' ';
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            // Enlève la couleur bleue pour afficher un élément
            if (i == numLigne && j == numCol){
                couleur(KNoir);
                couleur(KBGGrisClair);
            }
            else{
                if (Mat[i][j]==0) couleur (KReset); // Si l'élément = 0, alors la couleur sera la couleur par défaut du terminal
                if (Mat[i][j]==1) couleur (KCyan); // Si l'élément = 1, alors la couleur sera cyan
                if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
                if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
                if (Mat[i][j]==4) couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
                if (Mat[i][j]==5) couleur (KMagenta); // Si l'élément = 5, alors la couleur sera magenta
                if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            }
            cout <<  Mat[i][j] ;
            couleur(KReset);
            cout << ' ';
        }

        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
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
    //analyse case par case
    for (unsigned numLigne = 1 ; numLigne < mat.size() ; ++numLigne){
        for (unsigned numCol = 0 ; numCol < mat[numLigne].size() ; ++numCol){
            size_t combienALaSuite (1);
            if (mat[numLigne][numCol] == mat[numLigne-1][numCol]){
                ++combienALaSuite;
            }
            //si on a au moins 3 chiffres identiques a la suite
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

bool detectionExplositionUneBombeVertical (CMatrice & mat){
    bool auMoinsUneExplosion (false);
    for (unsigned numCol= 0 ; numCol < mat.size() ; ++numCol){
        for (unsigned numLigne = 0 ; numLigne < mat[numCol].size() ; ++numLigne){
            size_t combienALaSuite (1);
            if (numLigne != 0){
                if (mat[numCol][numLigne] == mat[numCol-1][numLigne]){
                    ++combienALaSuite;
                }
            }
            //si on a aun moins 3 chiffres identiques a la suite.
            if (combienALaSuite >= 3){
                auMoinsUneExplosion = true;
                cout << "on a une suite en position numLigne = " << numLigne
                     << "; colonne = " << numCol
                     << "; sur  " << combienALaSuite << " cases" << endl;
                cout << string (20, '-') << endl << "matrice avant suppresion" << endl;
                afficheMatriceV1(mat);
                explositionUneBombeVertical (mat, numCol, numLigne, combienALaSuite);
                cout << string (20, '-') << endl << "matrice après suppresion" << endl;
                afficheMatriceV1(mat);
            }
        }
    }
    return auMoinsUneExplosion;
}

void detectionExplositionBombe (CMatrice & mat){
    detectionExplositionUneBombeHorizontale(mat);
    detectionExplositionUneBombeVertical(mat);
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
    swap(mat[numLigne][numCol], mat[numLigne + nouvellePositionLigne][numCol + nouvellePositionColonne]);
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
        case 'q':
            if (numCol != mat[0].size() - 1) swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
            break;
        case 'z':
            if (numLigne != mat.size() - 1) swap(mat[numLigne][numCol],mat[numLigne - 1][numCol]);
            break;
        case 'd':
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
        size_t numLigne = 0;
        cout << numLigne;
        cout << ", numero de colonne : ";
        size_t numCol = 0;
        cout << numCol;
        cout << ", Sens du deplacement : (A|Z|E|Q|D|W|X|C) : " << endl;
        char deplacement;
        cin >> deplacement;
        faitUnMouvement (mat, deplacement, numLigne, numCol);
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

void affichePave() {
    cout << "quel exercice voulez vous voir ?" << endl
         << "1: exercice 1, génère et affiche une matrice rempli de nombre aléatoire entre 1 et " << KPlusGrandNombreDansLaMatrice << '.' << endl
         << "2: exercice 2, génère et affiche une matrice rempli de nombre aléatoire entre 1 et " << KPlusGrandNombreDansLaMatrice
         << " et détecte si il y a plus de 3 nombres alignés horizontalement." << endl
         << "3: exercice 3, génère et affiche une matrice rempli de nombre aléatoire entre 1 et " << KPlusGrandNombreDansLaMatrice
         << " et détecte si il y a plus de 3 nombres alignés horizontalement. si il y a détection, il enleve les nombres alignés et fait tomber les nombres au dessus."
         << "4: exercice 4, génère et affiche une matrice rempli de nombre aléatoire entre 1 et " << KPlusGrandNombreDansLaMatrice
         << " et détecte si il y a plus de 3 nombres alignés horizontalement. si il y a détection, il enleve les nombres alignés et fait tomber les nombres au dessus. fait un mouvement et répète indéfiniment le déplacement." << endl
         << "0: une petite partie ?" << endl
         << "-1: sortie du programme";
}

int main() {
    // ---------Exercice 1 -----------------//
    //return ppalExo01();
    //--------------------------------------//

    // ---------Exercice 2 -----------------//
    //return ppalExo02();
    //-------------------------------------//

    // ---------Exercice 3 -----------------//
    //return ppalExo03();
    //-------------------------------------//

    // ---------Exercice 4 -----------------//
    //return ppalExo04();
    //-------------------------------------//

    //return partiNumberCrush();

    int select = -2;
    affichePave();
    while (true) {
        cin >> select;
        if (select == -1) break;
        else if (select == 0) partiNumberCrush();
        else if (select == 1) ppalExo01();
        else if (select == 2) ppalExo02();
        else if (select == 3) ppalExo03();
        else if (select == 4) ppalExo04();
        else cout << "oops" << endl;
        //clearScreen();
        affichePave();
    }
    return 0;
}
