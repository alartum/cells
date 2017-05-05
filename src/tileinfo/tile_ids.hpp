#ifndef HEADER_TILE_IDS_INCLUDED
#define HEADER_TILE_IDS_INCLUDED

// Файл с испльзуемыми ID фоновых объектов, т.е. "Tile"
#define TILE_UNDEFINED_ID       0x0
#define TILE_WATER_ID           0x1
#define TILE_GRASS_ID           0x2

#define OBJECT_UNDEFINED_ID             0xFFFFFF

#define OBJECT_GRASS_EATING_ID          0x101   // Травоядный
#define OBJECT_GRASS_EATING_LEADER_ID   0x102   // Лидер травоядных

#define OBJECT_PREDATOR_ID              0x201   // Хищник
#define OBJECT_PREDATOR_LEADER_ID       0x202   // Лидер хищников

#define OBJECT_CORPSE_ID                0x103   // Труп


#define IS_PREDATOR(x)                  (0x200 & x)
#define IS_GRASS_EATING(x)              (0x100 & x)
#define IS_OBJECT(x)                    (0xffffff00 & x)
#define IS_TILE(x)                      (0xff & x)
// ... ids here

#endif
