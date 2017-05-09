#ifndef HEADER_TILE_IDS_INCLUDED
#define HEADER_TILE_IDS_INCLUDED

// Error handlers
#define OBJECT_UNDEFINED_ID     0xFFFFFF
#define TILE_UNDEFINED_ID       0x0
#define STATE_UNDEFINED_ID      0xFFFFFF

// Файл с испльзуемыми ID фоновых объектов, т.е. "Tile"
#define TILE_WATER_ID           0x1
#define TILE_GRASS_ID           0x2



#define OBJECT_GRASS_EATING_ID          0x101   // Травоядный
#define OBJECT_GRASS_EATING_LEADER_ID   0x102   // Лидер травоядных

#define OBJECT_PREDATOR_ID              0x201   // Хищник
#define OBJECT_PREDATOR_LEADER_ID       0x202   // Лидер хищников

#define OBJECT_CORPSE_ID                0x103   // Труп


#define IS_PREDATOR(x)                  (0x200 & x)
#define IS_GRASS_EATING(x)              (0x100 & x)
#define IS_OBJECT(x)                    (0xffffff00 & x)
#define IS_TILE(x)                      (0xff & x)
#define STATE_MASK(x)                   (0xfffffff00 & x)
#define DIR_MASK(x)                     (0xff & x)
#define DIR_UP                          (0x1)
#define DIR_RIGHT                       (0x2)
#define DIR_DOWN                        (0x4)
#define DIR_LEFT                        (0x8)
#define DIR_ADD                         (0x10)

#define STATE_WALK                      (0x100)
#define STATE_IDLE                      (0x200)
// ... ids here

#endif
