#include "mingen.h"

#ifndef _DEFS
#define _DEFS

//
//  INT3:  3 integers (xyz) for world positions, etc
//

typedef struct { int x, y, z; } int3;

//
//  FLOAT3:  3 floats (xyz) for world positions, etc
//

typedef struct { float x, y, z; } float3;

//
//  BUTTON:  represents a key on the keyboard or a button on a gamepad
//

typedef struct 
{ 
    bool pressed;               // true on the frame that a button was pressed (less than 0.2s)
    bool up;                    // true on the frame that a button was released
    bool down;                  // true all frames where button is down
    float timer;                // tracks how long the button was down for
} 
button;

//
//  COMPONENT:  represents various data we can save for an object
//

typedef struct 
{ 
    int type;                   // what kind of component it is: we can figure out how to read it with this
    void* address;              // void pointer to the start of the component in memory
} 
component;

//
//  ARRAY:  a list of data, it can be a list of a primitive type or a struct such as component
//

typedef struct 
{ 
    int length;                 // how many elements are in the array
    int size;                   // how many bytes each element uses
    void* data;                 // a void pointer to the start of the array in memory
} 
array;

typedef struct { int length; int size; int capacity; array* ids; array* data; } collection;

//
//  MESH:  a collection of vertices, uvs, indices, etc, that we can draw with openGL
//

typedef struct 
{ 
    // when we want to draw something with openGL we need to create a "vertex array object" and 
    // a "vertex buffer object", these objects live in the GPU.  when we tell openGL to create them for our mesh
    // it will return an integer that represents the object which we will use whenever we need to update/draw the mesh

    unsigned int VAO;           // an ID that openGL gives us that points to our vertex array object for this mesh
    unsigned int VBO;           // an ID that openGL gives us that points to our vertex buffer object for this mesh
    unsigned int EBO;           // an ID that openGL gives us that points to our index buffer for this mesh
    
    array* vertex;              // an array of float3 that represents a vertex
    array* index;               // an array of int that represents the order of triangle drawing
    array* uv;                 
} 
mesh;

//
//  CHUNK:  a group (10x10x10) of shapes that represents a section of the map terrain
//          a player can choose how many chunks they want displayed at any given time 
//          to match their PC performance
//

typedef struct 
{ 
    int busy;                   // whether the chunk is currently drawing
    int loaded;                 // whether the chunk is currently loaded
    int x, y, z;                // represents the world position of the chunk
    mesh* mesh;                 // each chunk will have a mesh that is a combination of its shapes
    array*** shapes;            // an array of shapes indexed by their xyz position in the chunk
} 
chunk;

//
//  MAP:  a "level" or "scene" for a game.  a game can have multiple maps
//        each map will have its size predetermined and will consist of an array of chunks
//

typedef struct
{
    int ID;                     // an ID for the map
    char* name;                 // a string to name the map with

    int size;                   // how many chunks the map will have in XZ directions
    int height;                 // how many chunks the map will have in the Y direction
    int scale;                  // how many nodes per chunk

    array*** grid;              // a multidimensional array which holds an array of object IDs indexed by position
    collection objects;         // a collection of all the objects assigned to this map

    array* chunks;              // an array of all the chunks assigned to the map
}
map;

//
//  GAME:  a "game" that a user creates and other players can join.
//

typedef struct 
{
    int ID;                     // the ID of the game
    char* name;                 // a string to name the game with

    array* mapIDs;              // an array of map IDs
    array* maps;                // an array of maps assigned to the game
} 
game;

#endif