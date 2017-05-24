QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

HEADERS += \
    field/field.hpp \
    matrix/matrix.hpp \
    object/object.hpp \
    tile/tile.hpp \
    generate_map/generatemap.hpp \
    generate_objects/generateobjects.hpp \
    do_step/dostep.hpp \
    model/model.hpp \
    item/item.hpp \
    model_manager/modelmanager.hpp \
    game_item/gameitem.hpp \
    entity/entity.hpp \
    config/tile_ids.hpp \
    debug.h \
    animation_state/animationstate.hpp \
    qsfmlwidget/qsfmlwidget.hpp \
    do_step/cachedfunction.hpp \
    gamewindow/gamewindow.hpp \
    ../../lib/qcustomplot/qcustomplot.h

SOURCES += \
    field/field.cpp \
    object/object.cpp \
    do_step/dostep.cpp \
    tile/tile.cpp \
    generate_map/generatemap.cpp \
    generate_objects/generateobjects.cpp \
    main.cpp \
    model/model.cpp \
    item/item.cpp \
    model_manager/modelmanager.cpp \
    game_item/gameitem.cpp \
    entity/entity.cpp \
    animation_state/animationstate.cpp \
    qsfmlwidget/qsfmlwidget.cpp \
    gamewindow/gamewindow.cpp \
    ../../lib/qcustomplot/qcustomplot.cpp

LIBS += -lX11
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

QMAKE_CXX = g++-6
CONFIG += c++14 
INCLUDEPATH += /usr/include/lua5.3 \
               /usr/include/sol \
               /usr/include/qcustomplot

LIBS += -llua5.3


DISTFILES += \
    config/id_manager.lua \
    config/mm_config.lua \
    config/window_config.lua
