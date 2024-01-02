#include <iostream>
#include <type.h>
#include <cst.h>
#include <affichage.h>
#include <mingl/mingl.h>

#include <mingl/shape/circle.h>

using namespace std;

//Ce document cpp est un document regroupant toutes les fonctions/procédures d'affichage de la matrice, permettant de réduire le code du main


/**
 * @brief clearScreen
 * @author A.Casali
 */
void clearScreen () {
    cout << "\033[H\033[2J";
}

/**
 * @brief couleur
 * @param coul
 * @author A.Casali
 */
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche
/*void  afficheMatriceV0 (const CMatrice & Mat) {
    clearScreen();
    couleur (KReset);
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            if (Mat[i][j]==KAIgnorer) couleur(KNoir); // Si l'élément = 0, alors la couleur sera la couleur noire, permettant de cacher le 0
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j]; // Affiche la matrice élément par élément
            couleur(KReset);
            cout << " | ";
        }
        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
        cout << endl ;
    }
}*/
void  afficheMatriceV0 (const CMatrice & Mat , MinGL & window) {
    for (size_t i = 0 ; i < Mat.size() ; ++i) {
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j) {
            if (Mat[i][j]==KAIgnorer){ couleur(KNoir);} // Si l'élément = 0, alors la couleur sera la couleur noire, permettant de cacher le 0
            else if (Mat[i][j]==1)
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

// affichage de la matrice sans les numéros de lignes / colonnes en haut / à gauche, mais avec un fond de couleur différente pour signifier que la case est a KAIgnorer
void  afficheMatriceV1 (const CMatrice & Mat) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << " ";
    }
    cout << " " <<endl;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        cout << "  ";
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset); // Enlève la couleur bleue pour l'affiche d'un élément
            if (Mat[i][j]==KAIgnorer) couleur(KNoir); //  Si l'élément = 0, alors la couleur sera la couleur noire, permettant de cacher le 0
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j];
            couleur(KReset);
            cout << " | ";
        }
        cout << endl ;
    }
}

// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur différente pour signifier que la case est a KAIgnorer
void  afficheMatriceV2 (const CMatrice & Mat) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    cout << " ";
    for (size_t i = 0 ; i < Mat.size() ; ++i) cout << "  |" << i + 1;
    cout << " | " << endl;
    for (size_t i = 0 ; i < Mat.size() ; ++i)
    {
        couleur(44);
        if (i + 1 != Mat.size()) cout << ' ' << i + 1;
        else cout << i + 1;
        couleur(KReset);
        cout << " | ";
        for ( size_t j = 0 ; j < Mat[i].size() ; ++j){
            couleur(KReset); // Enlève la couleur bleue pour afficher un élément
            if (Mat[i][j]==KAIgnorer) couleur(KNoir); //  Si l'élément = 0, alors la couleur sera la couleur noire, permettant de cacher le 0
            if (Mat[i][j]==1) couleur(KCyan); // Si l'élément = 1, alors la couleur sera cyan
            if (Mat[i][j]==2) couleur (KRouge); // Si l'élément = 2, alors la couleur sera rouge
            if (Mat[i][j]==3) couleur (KVert); // Si l'élément = 3, alors la couleur sera verte
            if (Mat[i][j]==4)couleur (KJaune); // Si l'élément = 4, alors la couleur sera jaune
            if (Mat[i][j]==5) couleur(KMagenta); // Si l'élément = 5, alors la couleur sera magenta
            if (Mat[i][j]==6) couleur (KBleu); // Si l'élément = 6, alors la couleur sera bleu
            cout <<  Mat[i][j];
            couleur(KReset);
            cout << " | ";
        }
        couleur(KReset); // On reset la couleur afin de ne pas avoir du texte affiché en jaune
        cout << endl ;
    }
}

// affichage de la matrice avec les numéros de lignes / colonnes en haut / à gauche et avec un fond de couleur différente pour signifier que la case est a KAIgnorer et la case sélectionner a un fond de couleur différent
void  afficheMatriceV3 (const CMatrice & Mat, const size_t numLigne, const size_t numCol) {
    clearScreen();
    couleur (44); // Affiche la couleur bleue
    cout << "  ";
    for (size_t i = 0 ; i < Mat[0].size() ; ++i) cout << ' ' << i + 1;
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
                if (Mat[i][j]==KAIgnorer) couleur (KNoir); //  Si l'élément = 0, alors la couleur sera la couleur noire, permettant de cacher le 0
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
