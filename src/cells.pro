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
    moving_entity/movingentity.hpp \
    tileinfo/tile_ids.hpp

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
    moving_entity/movingentity.cpp

LIBS += -lX11
LIBS += -lsfml-graphics -lsfml-window -lsfml-system
LIBS += -lre2
