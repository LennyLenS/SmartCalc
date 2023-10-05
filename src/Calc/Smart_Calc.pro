#-------------------------------------------------
#
# Project created by QtCreator 2023-07-10T03:24:32
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Smart_Calc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    validator.c \
    ../polish.c \
    graphwindow.cpp \
    lib_qcustomplot/qcustomplot.cpp \

HEADERS += \
        mainwindow.h \
    validator.h \
    ../polish.h \
    graphwindow.h \
    lib_qcustomplot/qcustomplot.h \

FORMS += \
        mainwindow.ui \
    graphwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

SUBDIRS += \
    Smart_Calc.pro \
    Smart_Calc.pro \
    Smart_Calc.pro
