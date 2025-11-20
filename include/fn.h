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
        array* (*new) (int length, int size);
        void (*add) (array* array, int length, void* data);
        void (*set) (array* array, int index, int length, void* data);
        void (*remove) (array* array, int index, int length);
        void (*resize) (array* array, int length);
        void (*free) (array* array);
    } 
    array;

    struct _chunk 
    {
        chunk* (*new) (FN* fn, int x, int y, int z);
        void (*draw) (FN* fn, chunk* chunk);
        void (*build) (FN* fn, chunk* chunk);
    } 
    chunk;

    struct _collection 
    {

    } 
    collection;

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

    struct _input 
    {
        button A;

        void (*read) (FN* fn);
    } 
    input;
    
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
        void (*free) (FN* fn, mesh* mesh);
    } 
    mesh;

    struct _network 
    {

    } 
    network;

    struct _shape
    {
        struct solid { void (*build) (FN* fn); } solid;
        struct ramp { void (*build) (FN* fn); } ramp;
    } 
    shape;

    struct _sound 
    {

    } 
    sound;

    struct _utility 
    {
        void (*log) (char* message);
        void (*logint) (int value);
        void (*logfloat) (float value);
        void (*logarray) (array* array, array_type type);
        char* (*readfile) (char* filename);
    } 
    util;
};

#endif