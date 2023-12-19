#include <iostream>
#include <type.h>
#include <cst.h>
#include <affichage.h>
#include <fstream>
#include <mingl/mingl.h>
using namespace std;
/**
 * @brief initParams
 * @param param
 */
void initParams (CMyParam & param)
{
//touche du joueur
param.mapParamChar["toucheHaut"] = 'z';
param.mapParamChar["toucheGauche"] = 'q';
param.mapParamChar["toucheBas"] = 'x';
param.mapParamChar["toucheDroite"] = 'd';

//taille de la grille - on suppose que c'est un rectangle
param.mapParamUnsigned["nbColonnes"] = 10;
param.mapParamUnsigned["nbLignes"] = 10;

}

/**
 * @brief nouvRdm
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
 * @brief initMat
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
 * @brief explositionUneBombeHorizontale
 * @param mat
 * @param numLigne
 * @param numColonne
 * @param combien
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
 * @brief detectionExplositionUneBombeHorizontale
 * @param mat
 * @param score
 * @return
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
 * @brief explositionUneBombeVerticale
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
 * @brief detectionExplositionUneBombeVerticale
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
                afficheMatriceV2(mat);
                explositionUneBombeVerticale (mat, numLigne, numCol, combienALaSuite);
                afficheMatriceV2(mat);
                score += 10 * (combienALaSuite - 2);
            }
        }
    }
    return auMoinsUneExplosion;
}

/**
 * @brief remplaceVideParRdm
 * @param mat
 * @param vid
 * @param nbMax
 */
// remplace toutes les cases vides par des nombres aléatoires
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
 * @brief detectionExplositionBombe
 * @param mat
 * @param score
 * @param vid
 * @param plusGrandNb
 * @return
 */
bool detectionExplositionBombe (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                                  const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice){

    bool act (detectionExplositionUneBombeVerticale(mat, score) or
              detectionExplositionUneBombeHorizontale(mat, score));
    if (act) remplaceVideParRdm(mat, vid, plusGrandNb);
    return act;
}

/**
 * @brief zeroVidSousNb
 * @param mat
 * @param vid
 * @return
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
 * @brief faitUnMouvement
 * @param mat
 * @param deplacment
 * @param numLigne
 * @param numCol
 * @param nbDeplacement
 */
void faitUnMouvement (CMatrice & mat, const char & deplacment, size_t & numLigne,
                        size_t & numCol, unsigned & nbDeplacement) {

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
            if (numLigne != 0){
                swap(mat[numLigne][numCol],mat[numLigne + 1][numCol]);
                --nbDeplacement;
            }
            break;
        case 'd':
            if (numCol != mat[0].size() - 1){
                swap(mat[numLigne][numCol],mat[numLigne][numCol + 1]);
                --nbDeplacement;
            }
            break;
        case 'z':
            if (numLigne != mat.size() - 1){

                swap(mat[numLigne][numCol],mat[numLigne - 1][numCol]);
                --nbDeplacement;
            }
            break;
        case 'q':
            if (numCol != 0) {
                swap(mat[numLigne][numCol],mat[numLigne][numCol - 1]);
                --nbDeplacement;
            }
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

/**
 * @brief chargerParametre
 * @param params
 * @param fichier
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
 * @brief partiNumberCrush
 * @param score
 * @param nbDeplacement
 * @return
 */
int partiNumberCrush(unsigned & score, unsigned & nbDeplacement){
    CMatrice mat;
    initMat(mat);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        while (detectionExplositionBombe(mat, score) or zeroVidSousNb(mat))
            continue;
        afficheMatriceV2 (mat);
        cout << "Score : " << score << endl;
       cout << "Nombre de déplacement restant : " <<  nbDeplacement << endl;
        if (score >= 100){
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
        faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement);
    }
    return 0;
}

/**
 * @brief partiCasaliCrush
 * @param score
 * @param nbDeplacement
 * @return
 */
int partiCasaliCrush(unsigned & score, unsigned & nbDeplacement){
    CMatrice mat;
    CMyParam params;
    initParams(params);
    chargerParametre(params, "./build.yaml");
    initMat(mat);
    size_t numCol = 4;
    size_t numLigne = 4;
    while(true){
        while (detectionExplositionBombe(mat, score) or zeroVidSousNb(mat))
            continue;
        afficheMatriceV3 (mat, numLigne, numCol);
        cout << "Score : " << score << endl;
        if (score >= 350){
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
        faitUnMouvement (mat, deplacement, numLigne, numCol, nbDeplacement);
    }
    return 0;
}
/**
 * @brief main
 * @return
 */
int main() {
    srand(time(NULL));

    unsigned score=0;
    unsigned nbDeplacement=15;

    return partiCasaliCrush(score, nbDeplacement);

    //return 0;
}
