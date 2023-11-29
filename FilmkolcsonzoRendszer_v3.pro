QT += core gui

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle


SOURCES += \
        administrator.cpp \
        elofizetes.cpp \
        elofizeto.cpp \
        felhasznalo.cpp \
        film.cpp \
        hiba.cpp \
        main.cpp \
        mukodteto.cpp \
        segito.cpp \
        vasarlo.cpp


DISTFILES += \
    ../build-Filmkolcsonzo_Rendszer_QT-Desktop_Qt_6_1_3_MinGW_64_bit-Debug/adminok.json \
    ../build-Filmkolcsonzo_Rendszer_QT-Desktop_Qt_6_1_3_MinGW_64_bit-Debug/elofizetok.json \
    ../build-Filmkolcsonzo_Rendszer_QT-Desktop_Qt_6_1_3_MinGW_64_bit-Debug/segitok.json \
    ../build-Filmkolcsonzo_Rendszer_QT-Desktop_Qt_6_1_3_MinGW_64_bit-Debug/vasarlok.json

HEADERS += \
    administrator.h \
    elofizetes.h \
    elofizeto.h \
    felhasznalo.h \
    film.h \
    hiba.h \
    mukodteto.h \
    segito.h \
    vasarlo.h



