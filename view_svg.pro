QT += core gui widgets svg svgwidgets

CONFIG += c++17

TARGET = SVGViewer
TEMPLATE = app

SOURCES += \
        main.cpp\
        mainwindow.cpp \
        zoomgraphicsview.cpp

HEADERS += \
        mainwindow.h \
        snapgraphicssvgitem.h \
        zoomgraphicsview.h

FORMS += \
        mainwindow.ui

# Для автоматического поиска изображений
DISTFILES += \
    img/example.svg
