#include "../include/mingen.h"

//
//  NEW:  creates a new array with a specified size where size = # of bits per element
//

static array* _array_new(int length, int size)
{
    array *a = malloc(sizeof(array));
    a->length = length;
    a->size = size;
    a->data = malloc(length * size);
    return a;
}

//
//  ADD:  adds more elements to the array resizing it in the process
//

static void _array_add(array *array, int length, void *data)
{
    array->data = realloc(array->data, (array->length + length) * array->size);
    memcpy(array->data + (array->length * array->size), data, length * array->size);
    array->length += length;
}

//
//  SET:  assigns a new piece of data at index
//

static void _array_set(array *array, int index, int length, void *data)
{
    memcpy(array->data + (index * array->size), data, length * array->size);
}

//
//  REMOVE:  removes an element in the array at index
//

static void _array_remove(array *array, int index, int length)
{
    memcpy(array->data + (index * array->size), array->data + ((index + length) * array->size), (array->length - length) * array->size);
    array->length -= length;
}

//
//  RESIZE:  resizes an array to a new length
//

static void _array_resize(array *array, int length)
{
    array->length = length;
    array->data = realloc(array->data, length * array->size);
}

//
//  FREE:  frees up the array memory
//

static void _array_free(array *array)
{
    free(array->data);
    free(array);
}

//
//  ARRAY.C:    a helper module for managing arrays
//              we can have an array of primitives and also custom 
//              types such as component

void _init_array(FN *fn)
{
    fn->array.new = &_array_new;
    fn->array.add = &_array_add;
    fn->array.set = &_array_set;
    fn->array.remove = &_array_remove;
    fn->array.resize = &_array_resize;
    fn->array.free = &_array_free;
}