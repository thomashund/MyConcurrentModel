#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T09:57:24
#
#-------------------------------------------------

QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = LQGridEditor
TEMPLATE = app

CONFIG += c++1z

include(src/GridEditor/GridEdit.pri)
include(src/LongQtMain/LongQtMain.pri)
include(src/Grapher/Grapher.pri)
include(src/Utils.pri)
include(../LongQt-model/src/model.pri)

RESOURCES = LongQt.qrc

windows {
    RC_FILE = LongQt.rc
    QMAKE_CXXFLAGS += -std:c++17
}
macx {
    QMAKE_MAC_SDK = macosx10.12
    ICON = LongQtIcon.icns
}
linux {
    debug {
        QMAKE_CXXFLAGS += -g
        QMAKE_CXXFLAGS_RELEASE -= -O2
    }
    relase {
        QMAKE_CXXFLAGS += -static
    }
    TARGET = $$TARGET".out"

    DESTDIR = ./build
    OBJECTS_DIR = ./build/obj
    MOC_DIR = ./build/obj
    RCC_DIR = ./build/obj
    UI_DIR = ./build/obj
}

SOURCES += \
    src/LQGridEditorMain.cpp

