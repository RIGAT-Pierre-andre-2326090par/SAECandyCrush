#ifndef AFFICHAGEMINGL_H
#define AFFICHAGEMINGL_H

#include <string>
#include <mingl/graphics/idrawable.h>
#include <type.h>
#include <cst.h>
#include <mingl/mingl.h>

void dessinerRectangle (MinGL & window, const unsigned & x, const unsigned & y);

void dessinerCercle (MinGL & window, const unsigned & x, const unsigned & y);

void dessinerTriangle (MinGL & window, const unsigned & x, const unsigned & y);

void dessinerCroix (MinGL & window, const unsigned & x, const unsigned & y);

void dessinerCurseur (MinGL & window, const unsigned & x, const unsigned & y);

void afficheText(MinGL & window, const std::string & txt, const unsigned & x, const unsigned & y);

void faitUnMouvementMinGL (CMatrice & mat, MinGL & window, size_t & numLigne,
                          size_t & numCol, unsigned & nbDeplacement, CMyParam & param,
                          bool & curs2);

void dessineBaptiste (MinGL & window, const unsigned & x, const unsigned & y);

void dessineAlex (MinGL & window, const unsigned & x, const unsigned & y);

void dessinePierre (MinGL & window, const unsigned & x, const unsigned & y);

void dessineCyril (MinGL & window, const unsigned & x, const unsigned & y);

void dessineArnaud (MinGL & window, const unsigned & x, const unsigned & y);

void dessineCasali (MinGL & window, const unsigned & x, const unsigned & y);

#endif // AFFICHAGEMINGL_H
