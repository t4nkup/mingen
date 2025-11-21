#include "mingen.h"

#ifndef _DEFS
#define _DEFS

typedef struct array array;
typedef struct button button;
typedef struct chunk chunk;
typedef struct float3 float3;
typedef struct game game;
typedef struct grid grid;
typedef struct hash hash;
typedef struct int3 int3;
typedef struct map map;
typedef struct mesh mesh;
typedef struct shape shape;
typedef struct transform transform;

//
//  ARRAY:  a list of data, it can be a list of a primitive type or a struct such as component
//

typedef struct array
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    int length;                 // how many elements are in the array
    int size;                   // how many bytes each element uses
    void* data;                 // a void pointer to the start of the array in memory
} 
array;

//
//  BUTTON:  represents a key on the keyboard or a button on a gamepad
//

typedef struct button
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    bool pressed;               // true on the frame that a button was pressed (less than 0.2s)
    bool up;                    // true on the frame that a button was released
    bool down;                  // true all frames where button is down
    float timer;                // tracks how long the button was down for
} 
button;

//
//  CHUNK:  a group (10x10x10) of shapes that represents a section of the map terrain
//          a player can choose how many chunks they want displayed at any given time 
//          to match their PC performance
//

typedef struct chunk
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    int busy;                   // whether the chunk is currently drawing
    int loaded;                 // whether the chunk is currently loaded
    int x, y, z;                // represents the world position of the chunk
    mesh* mesh;                 // each chunk will have a mesh that is a combination of its shapes
    void**** shape;             // a grid of shapes indexed by their xyz position in the chunk
} 
chunk;

//
//  FLOAT3:  3 floats (xyz) for world positions, transforms, etc
//

typedef struct float3 
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    float x, y, z;              // the XYZ variables for the float3
} 
float3;

//
//  GAME:  a "game" that a user creates and other players can join.
//

typedef struct game
{
    unsigned char type;         // the struct "type" which we can read with void pointer
    int ID;                     // the ID of the game
    char* name;                 // a string to name the game with

    array* mapIDs;              // an array of map IDs
    array* maps;                // an array of maps assigned to the game
} 
game;

//
//  GRID:  a 3D list of data similar to array, elements are indexed by position [x][y][z]
//

typedef struct grid
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    int size;                   // how big our grid will be, ex: 10x10x10
    void**** data;              // a 3D void pointer for each element that we can access with data[0][0][0]
} 
grid;

//
//  HASH:  a hashtable where we can store object data with keys
//

typedef struct hash
{

}
hash;

//
//  INT3:  3 integers (xyz) for world positions, etc
//

typedef struct int3 
{ 
    unsigned char type;         // the struct "type" which we can read with void pointer
    int x, y, z;                // the XYZ variables for the int3
} 
int3;

//
//  MAP:  a "level" or "scene" for a game.  a game can have multiple maps
//        each map will have its size predetermined and will consist of an array of chunks
//

typedef struct map
{
    unsigned char type;         // the struct "type" which we can read with void pointer
    int ID;                     // an ID for the map
    char* name;                 // a string to name the map with

    int size;                   // how many chunks the map will have in XZ directions
    int height;                 // how many chunks the map will have in the Y direction
    int scale;                  // how many nodes per chunk

    array*** grid;              // a multidimensional array which holds an array of object IDs indexed by position
    grid objects;               // a collection of all the objects assigned to this map

    array* chunks;              // an array of all the chunks assigned to the map
}
map;

//
//  MESH:  a collection of vertices, uvs, indices, etc, that we can draw with openGL
//

typedef struct mesh
{ 
    // when we want to draw something with openGL we need to create a "vertex array object" and 
    // a "vertex buffer object", these objects live in the GPU.  when we tell openGL to create them for our mesh
    // it will return an integer that represents the object which we will use whenever we need to update/draw the mesh

    unsigned char type;         // the struct "type" which we can read with void pointer

    unsigned int VAO;           // an ID that openGL gives us that points to our vertex array object for this mesh
    unsigned int VBO;           // an ID that openGL gives us that points to our vertex buffer object for this mesh
    unsigned int EBO;           // an ID that openGL gives us that points to our index buffer for this mesh
    
    int VBOSize;                // tells us how many bytes the VBO currently has allocated
    int EBOSize;                // tells us how many bytes the EBO currently has allocated

    array* vertex;              // an array of float3 where 3 = a vertex
    array* index;               // an array of int that represents the order of triangle drawing
    array* uv;                 
} 
mesh;

//
//  SHAPE:  a "shape" which could be a cube, ramp, wall, roofing, yada yada yada
//          the shape will occupy a space inside a chunk and tell the chunk how to build its mesh
//

typedef struct shape
{
    unsigned char type;         // the struct "type" which we can read with void pointer
    int ID;                     // what type of shape it is
    int material;               // what texture the shape will use
    int orientation;            // what orientation (rotation) the shape will display in
}
shape;

//
//  TRANSFORM:  a transform is a combination of position/rotation/scale 
//              which tells us how to draw an object in the world
//

typedef struct transform
{
    unsigned char type;         // the struct "type" which we can read with void pointer
    float3 position;            // the xyz world position
    float3 rotation;            // the xyz euler rotation of the object
    float3 scale;               // the xyz scale of the object
}
transform;

#endif