#include <vector>
#ifndef TYPE_H
#define TYPE_H

typedef std::vector <char> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMatrix; // un type représentant la grille
typedef std::pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

typedef unsigned short contenueDUneCase;
typedef std::vector <contenueDUneCase> CVLigne; // un type représentant une ligne de la grille
typedef std::vector <CVLigne> CMatrice; // un type représentant la grille

#endif // TYPE_H
