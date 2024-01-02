#include <string>
#include <vector>
#include <map>
#ifndef TYPE_H
#define TYPE_H

typedef std::vector <char> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMatrix; // un type représentant la grille
typedef std::pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

typedef unsigned short contenueDUneCase;
typedef std::vector <contenueDUneCase> CVLigne; // un type représentant une ligne de la grille
typedef std::vector <CVLigne> CMatrice; // un type représentant la grille

struct position {
    std::size_t _ligne;
    std::size_t _colonne;
};

struct CMyParam {
std::map <std::string, char> mapParamChar;
std::map <std::string, unsigned> mapParamUnsigned;
std::map <std::string, std::vector <unsigned> > mapParamVecUnsigned;
};
#endif // TYPE_H
