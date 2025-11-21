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
//  ADD:  adds more elements to the grid resizing it in the process
//

// static void _grid_add(grid* a, int length, void* data)
// {
//     a->data = realloc(a->data, (a->length + length) * a->size);
//     memcpy(a->data + (a->length * a->size), data, length * a->size);
//     a->length += length;
// }

// //
// //  SET:  assigns a new piece of data at index
// //

// static void _grid_set(grid* a, int index, int length, void* data)
// {
//     memcpy(a->data + (index * a->size), data, length * a->size);
// }

// //
// //  REMOVE:  removes an element in the grid at index
// //

// static void _grid_remove(grid* a, int index, int length)
// {
//     memcpy(a->data + (index * a->size), a->data + ((index + length) * a->size), (a->length - length) * a->size);
//     a->length -= length;
// }

// //
// //  RESIZE:  resizes an grid to a new length
// //

// static void _grid_resize(grid* a, int length)
// {
//     a->length = length;
//     a->data = realloc(a->data, length * a->size);
// }

//
//  FREE:  frees up the grid memory
//

static void _grid_free(grid* a)
{
    free(a->data);
    free(a);
}

//
//  GRID.C:     a helper module for managing 3D arrays
//              we can have an array of primitives and also custom 
//              types such as component
//

void _init_grid(FN* fn)
{
    fn->grid.new = &_grid_new;
    // fn->grid.add = &_grid_add;
    // fn->grid.set = &_grid_set;
    // fn->grid.remove = &_grid_remove;
    // fn->grid.resize = &_grid_resize;
    fn->grid.free = &_grid_free;
}