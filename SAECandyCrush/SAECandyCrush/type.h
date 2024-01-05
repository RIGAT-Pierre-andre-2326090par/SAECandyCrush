#include <string>
#include <vector>
#include <map>
#ifndef TYPE_H
#define TYPE_H

/**
 * @brief définition d'une ligne
 */
typedef std::vector <char> CVLine; // un type représentant une ligne de la grille

/**
 * @brief définion d'un grille
 */
typedef std::vector <CVLine> CMatrix; // un type représentant la grille

/**
 * @brief définition de la position dans la grille
 */
typedef std::pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille


/**
 * @brief définition d'un case
 */
typedef unsigned short contenueDUneCase;

/**
 * @brief définition d'une ligne
 */
typedef std::vector <contenueDUneCase> CVLigne; // un type représentant une ligne de la grille

/**
 * @brief définition d'une grille
 */
typedef std::vector <CVLigne> CMatrice; // un type représentant la grille

/**
 * @brief la classe position
 */
struct position {
    std::size_t _ligne;
    std::size_t _colonne;
};

/**
 * @brief la classe param
 */
struct CMyParam {
std::map <std::string, char> mapParamChar;
std::map <std::string, unsigned> mapParamUnsigned;
std::map <std::string, std::vector <unsigned>> mapParamVecUnsigned;
};

#endif // TYPE_H
