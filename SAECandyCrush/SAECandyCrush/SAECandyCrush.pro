TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        affichage.cpp \
        affichagemingl.cpp \
        gestionpartie.cpp \
        main.cpp
        
HEADERS += \
    affichage.h \
    affichagemingl.h \
    cst.h \
    gestionpartie.h \
    type.h

include(../MinGL2_IUT_AIX-master/mingl.pri)
