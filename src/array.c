#include "../include/mingen.h"

//
//  NEW:  creates a new array with a specified size where size = # of bits per element
//

static array* _array_new(int count, int size)
{
    array* a = malloc(sizeof(array));
    a->count = count;
    a->size = size;
    a->data = malloc(count * size);
    return a;
}

//
//  ADD:  adds more elements to the array resizing it in the process
//

static void _array_add(array* a, int count, void* data)
{
    a->data = realloc(a->data, (a->count + count) * a->size);
    memcpy(a->data + (a->count * a->size), data, count * a->size);
    a->count += count;
}

//
//  SET:  assigns a new piece of data at index
//

static void _array_set(array* a, int index, int count, void* data)
{
    memcpy(a->data + (index * a->size), data, count * a->size);
}

//
//  REMOVE:  removes an element in the array at index
//

static void _array_remove(array* a, int index, int count)
{
    memcpy(a->data + (index * a->size), a->data + ((index + count) * a->size), (a->count - count) * a->size);
    a->count -= count;
}

//
//  RESIZE:  resizes an array to a new count
//

static void _array_resize(array* a, int count)
{
    a->count = count;
    a->data = realloc(a->data, count * a->size);
}

//
//  FREE:  frees up the array memory
//

static void _array_free(array* a)
{
    free(a->data);
    free(a);
}

//
//  ARRAY.C:  a helper module for managing arrays
//            we can have an array of primitives and also custom types
//

void _init_array(FN* fn)
{
    fn->array.new = &_array_new;
    fn->array.add = &_array_add;
    fn->array.set = &_array_set;
    fn->array.remove = &_array_remove;
    fn->array.resize = &_array_resize;
    fn->array.free = &_array_free;
}