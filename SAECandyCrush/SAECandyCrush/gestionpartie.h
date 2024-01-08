#ifndef GESTIONPARTIE_H
#define GESTIONPARTIE_H

#include <cst.h>

void initParams (CMyParam & param);

std::string strSansDeuxPts (const std::string & str);

void chargerParametre(CMyParam & params, const std::string & fichier);

unsigned nouvRdm(unsigned & nb1, unsigned & nb2, const unsigned & nbMax);

void initMat (CMatrice & mat, const unsigned & nbMax = KPlusGrandNombreDansLaMatrice,
             const size_t & nbLignes = 10,
             const size_t & nbColonnes = 10);

void explositionUneBombeHorizontale (CMatrice & mat, const size_t & numLigne,
                                    const size_t & numColonne, const size_t & combien);

bool detectionExplositionUneBombeHorizontale (CMatrice & mat, unsigned & score);

void explositionUneBombeVerticale (CMatrice & mat, const size_t & numLigne,
                                  const size_t & numColonne, const size_t & combien);

bool detectionExplositionUneBombeVerticale (CMatrice & mat, unsigned & score);

void remplaceVideParRdm(CMatrice & mat, const unsigned & vid = KAIgnorer,
                        const unsigned & nbMax = KPlusGrandNombreDansLaMatrice);

bool zeroVidSousNb (CMatrice & mat, const unsigned & vid = KAIgnorer);

bool detectionExplositionBombe (CMatrice & mat, unsigned & score, const unsigned & vid = KAIgnorer,
                               const unsigned & plusGrandNb = KPlusGrandNombreDansLaMatrice);

void faitUnMouvement (CMatrice & mat, const char & deplacment, size_t & numLigne,
                     size_t & numCol, unsigned & nbDeplacement, CMyParam & param);

#endif // GESTIONPARTIE_H
