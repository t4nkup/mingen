#include "mingen.h"

#ifndef _DEFS
#define _DEFS

// 
//  DEFS:   these are all of our various type definitions that we 
//          will need throughout the program
//

typedef struct { int x, y, z; } int3;
typedef struct { float x, y, z; } float3;

typedef struct { int type; void *address; } component;
typedef struct { int length; int size; void *data; } array;

typedef struct { int length; int size; int capacity; array *ids; array *data; } collection;
typedef struct { array *vertex; array *index; array *uv; } mesh;
typedef struct { int busy; int loaded; int x, y, z; mesh *mesh; } chunk;

typedef struct
{
    int ID;                     // an ID for the map
    char *name;                 // a string to name the map with

    int size;                   // how many chunks the map will have in XZ directions
    int height;                 // how many chunks the map will have in the Y direction
    int scale;                  // how many nodes per chunk

    array ***grid;              // a multidimensional array which holds an array of object IDs indexed by position
    collection objects;         // a collection of all the objects assigned to this map

    array *chunks;              // an array of all the chunks assigned to the map
}
map;

typedef struct 
{
    int ID;                     // the ID of the game
    char *name;                 // a string to name the game with

    array *mapIDs;              // an array of map IDs
    array *maps;                // an array of maps assigned to the game
} 
game;

#endif