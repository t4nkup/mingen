#include "mingen.h"

#ifndef FUNC
#define FUNC

// 
//  FN:  this is an extern struct that will we will treat as a global manager
//

struct FN 
{
    struct _array 
    {
        array* (*new) (int size, type value);
        void (*add) (array* array, int length, void* data);
        void (*set) (array* array, int index, int length, void* data);
        void* (*get) (array* array, int index);
        void (*remove) (array* array, int index, int length);
    } 
    array;

    struct _chunk 
    {
        chunk* (*new) (int x, int y, int z);
        void (*draw) (chunk* chunk);
        void (*build) (chunk* chunk);
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
        game* (*new) (char* name);
        void (*load) ();
        void (*unload) ();
    } 
    game;

    struct _graphics 
    {
        GLFWwindow* window;
        unsigned int shader;

        void (*setup) ();
        void (*render) ();
        void (*unload) ();
    } 
    gfx;

    struct _grid 
    {
        grid* (*new) (int size);
        void (*set) (grid* grid, int x, int y, int z, void* data);
        void* (*get) (grid* grid, int x, int y, int z);
        void (*remove) (grid* grid, int x, int y, int z);
    } 
    grid;

    struct _input 
    {
        button A;

        void (*read) ();
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

        void (*start) ();
        void (*stop) ();
        void (*tick) ();
    } 
    loop;

    struct _map 
    {
        map* (*new) (char* name);
        void (*load) ();
        void (*unload) ();
        void (*mapgen) ();
    } 
    map;

    struct _mesh 
    {
        mesh* (*new) ();
        void (*draw) (mesh* mesh);
    } 
    mesh;

    struct _network 
    {

    } 
    net;

    struct _shape
    {
        struct cube { void* (*new) (int material, int orientation); void (*build) (); } cube;
        struct ramp { void (*build) (); } ramp;
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

    struct _utility
    {
        size_t memory;

        void (*delete) (void* object);
        void (*log) (void* data, const char* file, int line);
        void (*logval) (void* data, type type, const char* file, int line);
        void (*logmem) (const char* file, int line);
        char* (*load) (char* filename);
        void (*uid) (uid id);
    }
    utility;
};

#endif