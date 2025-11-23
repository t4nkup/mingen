#include "mingen.h"

#ifndef _FN
#define _FN

// 
//  FN:  this is our manager class that will hold references to all of
//       our modules.  the modules will mostly just hold function pointers
//       so we can easily call stuff throughout the program
//

typedef struct FN FN;

struct FN 
{
    struct _array 
    {
        array* (*new) (int byte);
        void (*add) (array* array, int length, void* data);
        void (*set) (array* array, int index, int length, void* data);
        void* (*get) (array* array, int index);
        void (*remove) (array* array, int index, int length);
    } 
    array;

    struct _chunk 
    {
        chunk* (*new) (FN* fn, int x, int y, int z);
        void (*draw) (FN* fn, chunk* chunk);
        void (*build) (FN* fn, chunk* chunk);
    } 
    chunk;

    struct _data 
    {
        game* game;
        map* map;
    } 
    data;

    struct _game 
    {
        game* (*new) (FN* fn, int ID, char* name);
        void (*load) (FN* fn);
        void (*unload) (FN* fn);
    } 
    game;

    struct _graphics 
    {
        GLFWwindow* window;
        unsigned int shader;

        void (*setup) (FN* fn);
        void (*render) (FN* fn);
        void (*unload) (FN* fn);
    } 
    gfx;

    struct _grid 
    {
        grid* (*new) (int size);
        void (*set) (FN* fn, grid* grid, int x, int y, int z, void* data);
        void* (*get) (grid* grid, int x, int y, int z);
        void (*remove) (FN* fn, grid* grid, int x, int y, int z);
    } 
    grid;

    struct _input 
    {
        button A;

        void (*read) (FN* fn);
    } 
    input;

    struct _list 
    {
        list* (*new) (int size);
        void (*add) (list* list, void* data);
        void (*set) (list* list, int index, void* data);
        void* (*get) (list* list, int index);
        void (*remove) (list* list, int index);
    } 
    list;
    
    struct _loop 
    {
        int isPaused;
        double current, previous, delta;

        void (*start) (FN* fn);
        void (*stop) (FN* fn);
        void (*tick) (FN* fn);
    } 
    loop;

    struct _map 
    {
        map* (*new) (FN* fn, int ID, char* name);
        void (*load) (FN* fn);
        void (*unload) (FN* fn);
        void (*mapgen) (FN* fn);
    } 
    map;

    struct _mesh 
    {
        mesh* (*new) (FN* fn);
        void (*draw) (FN* fn, mesh* mesh);
    } 
    mesh;

    struct _network 
    {

    } 
    network;

    struct _shape
    {
        struct cube { void* (*new) (int material, int orientation); void (*build) (FN* fn); } cube;
        struct ramp { void (*build) (FN* fn); } ramp;
    } 
    shape;

    struct _sound 
    {

    } 
    sound;

    struct _table
    {
        table* (*new) (int max);
        uint32_t (*hash) (uid uid);
        int (*compare) (uid a, uid b);
        void (*insert) (table* table, uid uid, void* data);
        void* (*get) (table* table, uid key);
        void (*remove) (table* table, uid key);
    }
    table;

    void (*free) (void* object);
    void (*log) (char* message);
    void (*logint) (int value);
    void (*logfloat) (float value);
    char* (*readfile) (char* filename);
};

#endif