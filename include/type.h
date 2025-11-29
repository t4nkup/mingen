#include "mingen.h"

#ifndef TYPE
#define TYPE

//
//  ARRAY:  a list of data for primitive types
//

typedef struct array
{ 
    type type; 
    type value;                 // if the array holds value types (int, float, etc) 
    int count;                  // how many elements are in the array
    int size;                   // the current allocated size of the array
    int byte;                   // how many bytes each element uses
    void* data;                 // a void pointer to the start of the array in memory
}
array;

//
//  BUTTON:  represents a key on the keyboard or a button on a gamepad
//

typedef struct button
{ 
    bool pressed;               // true on the frame that a button was pressed (less than 0.2s)
    bool up;                    // true on the frame that a button was released
    bool down;                  // true all frames where button is down
    float timer;                // tracks how long the button was down for
} 
button;

//
//  CAMERA:  a players camera
//

typedef struct camera
{
    type type;
    vec3 position;
    float yaw, pitch;
    vec3 front, up, right;
}
camera;

//
//  CHUNK:  a group (10x10x10) of shapes that represents a section of the map terrain
//          a player can choose how many chunks they want displayed at any given time 
//          to match their PC performance
//

typedef struct chunk
{ 
    type type;
    bool busy;                  // whether the chunk is currently drawing
    bool loaded;                // whether the chunk is currently loaded
    int x, y, z;                // represents the world position of the chunk
    mesh* mesh;                 // each chunk will have a mesh that is a combination of its shapes
    grid* shape;                // a grid of shapes indexed by their xyz position in the chunk
} 
chunk;

//
//  ENTRY:  an "entry" for our hashtable implementation
//

typedef struct entry
{
    type type;
    int state;                  // 0 = empty, 1 = used, -1 = deleted
    uid key;                    // the key for this entry
    void* data;                 // the void pointer for this entries value
} 
entry;

//
//  GAME:  a "game" that a user creates and other players can join.
//

typedef struct game
{
    type type;
    uid ID;                     // the ID of the game
    char* name;                 // a string to name the game with
    list* maps;                 // an array of maps assigned to the game
} 
game;

//
//  GRID:  a 3D list of data similar to array, elements are indexed by position [x][y][z]
//

typedef struct grid
{ 
    type type;
    int size;                   // how big our grid will be, ex: 10x10x10
    void**** data;              // a 3D void pointer for each element that we can access with data[0][0][0]
} 
grid;

//
//  LIST:  a list of void pointers that point to our structs so we can group them in various ways
//

typedef struct list
{ 
    type type;
    int count;                  // how many elements are in the list
    int size;                   // the current allocated capacity of the list
    void* data;                 // a void pointer to the start of the list in memory
} 
list;

//
//  MAP:  a "level" or "scene" for a game.  a game can have multiple maps
//        each map will have its size predetermined and will consist of an array of chunks
//

typedef struct map
{
    type type; 
    uid ID;                     // an ID for the map
    char* name;                 // a string to name the map with

    int size;                   // how many chunks the map will have in XZ directions
    int height;                 // how many chunks the map will have in the Y direction
    int scale;                  // how many nodes per chunk

    list*** grid;              // a multidimensional array which holds an array of object IDs indexed by position
    grid* objects;              // a collection of all the objects assigned to this map

    list* chunks;              // an array of all the chunks assigned to the map
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

    type type; 

    unsigned int VAO;           // an ID that openGL gives us that points to our vertex array object for this mesh
    unsigned int VBO;           // an ID that openGL gives us that points to our vertex buffer object for this mesh
    unsigned int EBO;           // an ID that openGL gives us that points to our index buffer for this mesh
    
    int VBOSize;                // tells us how many bytes the VBO currently has allocated
    int EBOSize;                // tells us how many bytes the EBO currently has allocated

    array* vertex;              // an array of floats for our vertices
    array* uv;                  // an array of floats that represent UV values
    array* index;               // an array of int that represents the order of triangle drawing
} 
mesh;

//
//  SHAPE:  a "shape" which could be a cube, ramp, wall, roofing, yada yada yada
//          the shape will occupy a space inside a chunk and tell the chunk how to build its mesh
//

typedef struct shape
{
    type type; 
    type ID;                    // what type of shape it is
    int material;               // what texture the shape will use
    int orientation;            // what orientation (rotation) the shape will display in
}
shape;

//
//  TABLE:  a hashtable where we can store object data with keys
//

typedef struct table
{
    type type;
    int count;                  // how many elements are in the hashtable
    int size;                   // the max # of elements the hashtable can currently hold
    entry* entry;               // an array of entries
}
table;

//
//  TRANSFORM:  a transform is a combination of position/rotation/scale 
//              which tells us how to draw an object in the world
//

typedef struct transform
{
    type type; 
    vec3 position;            // the xyz world position
    vec3 rotation;            // the xyz euler rotation of the object
    vec3 scale;               // the xyz scale of the object
}
transform;

#endif