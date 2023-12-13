TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        affichage.cpp \
        main.cpp
        
include(../MinGL2_IUT_AIX-master/mingl.pri)

HEADERS += \
    affichage.h \
    cst.h \
    type.h
