HEADERS += \
    field/field.hpp \
    matrix/matrix.hpp \
    object/object.hpp \
    tile/tile.hpp \
    tileinfo/tileinfo.hpp \
    generate_map/generatemap.hpp \
    generate_objects/generateobjects.hpp \
    do_step/dostep.hpp \
    model/model.hpp \
    item/item.hpp

SOURCES += \
    field/field.cpp \
    object/object.cpp \
    do_step/dostep.cpp \
    tile/tile.cpp \
    tileinfo/tileinfo.cpp \
    generate_map/generatemap.cpp \
    generate_objects/generateobjects.cpp \
    main.cpp \
    model/model.cpp \
    item/item.cpp

LIBS += -lX11 -lsfml-graphics -lsfml-window -lsfml-system
