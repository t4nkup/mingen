#include "../include/mingen.h"

//
//  NEW:  creates a new 3D grid where size = its dimensions ex: (10x10x10)
//        each element will hold a void pointer which can point to anything
//        we just keep track of what data is inside ourselves to cast
//

static grid* _grid_new(int size)
{
    grid* g = malloc(sizeof(grid));
    g->size = size;
    g->data = malloc(size * sizeof(void***));
    for (int x = 0; x < size; x++) {
        g->data[x] = malloc(size * sizeof(void**));
        for (int y = 0; y < size; y++) {
            g->data[x][y] = calloc(size, sizeof(void*));
        }
    }
    return g;
}

//
//  SET:  assigns a new piece of data at index
//

static void _grid_set(grid* g, int x, int y, int z, void* data)
{
    delete(g->data[x][y][z]);
    g->data[x][y][z] = data;
}

//
//  GET:  returns the pointer at index
//

static void* _grid_get(grid* g, int x, int y, int z)
{
    return g->data[x][y][z];
}

//
//  REMOVE:  removes an element in the grid at index
//

static void _grid_remove(grid* g, int x, int y, int z)
{
    delete(g->data[x][y][z]);
    g->data[x][y][z] = NULL;
}

//
//  GRID.C:     a helper module for managing 3D arrays
//              we can have an array of primitives and also custom 
//              types such as component
//

void _init_grid()
{
    fn.grid.new = &_grid_new;
    fn.grid.set = &_grid_set;
    fn.grid.get = &_grid_get;
    fn.grid.remove = &_grid_remove;
}